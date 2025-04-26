/* sender.c - Sender-side implementation */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

/* Protocol constants */
#define MAX_FRAME_SIZE 1024
#define MAX_DATA_SIZE 1000
#define HEADER_SIZE 8
#define FOOTER_SIZE 4
#define MAGIC_START 0xAA55
#define MAGIC_END 0x55AA

/* Frame structure */
typedef struct {
	uint16_t magic_start;    // Start delimiter (MAGIC_START)
	uint16_t sequence_num;   // Sequence number
	uint16_t data_length;    // Length of data
	uint16_t checksum;       // Header checksum
	uint8_t data[MAX_DATA_SIZE]; // Actual data
	uint32_t frame_checksum; // Frame checksum
	uint16_t magic_end;      // End delimiter (MAGIC_END)
} Frame;

/* Event types */
typedef enum {
	EVENT_NONE = 0,
	EVENT_DATA_AVAILABLE,
	EVENT_FRAME_SENT,
	EVENT_ERROR
} EventType;

/* Global variables */
static EventType pending_event = EVENT_NONE;
static uint8_t data_buffer[MAX_DATA_SIZE];
static size_t data_buffer_size = 0;
static uint16_t sequence_counter = 0;
static int output_fd = -1;  // File descriptor for output

/* Helper functions */
uint16_t CalculateHeaderChecksum(Frame* frame) {
	uint16_t sum = 0;
	sum += frame->magic_start;
	sum += frame->sequence_num;
	sum += frame->data_length;
	return ~sum; // One's complement
}

uint32_t CalculateFrameChecksum(Frame* frame) {
	uint32_t sum = 0;
	uint8_t* ptr = (uint8_t*)frame;

	// Calculate checksum up to data
	for (size_t i = 0; i < HEADER_SIZE + frame->data_length; i++) {
		sum += ptr[i];
	}

	// Add magic end in calculation
	sum += MAGIC_END & 0xFF;
	sum += (MAGIC_END >> 8) & 0xFF;

	return sum;
}

/* Wait for an event to occur - in this case, check if we have data to send */
EventType WaitForEvent(void) {
	/* In a real implementation, this might wait for I/O events */
	return pending_event;
}

/* Get data from the application layer */
uint8_t* GetData(size_t* data_size) {
	if (pending_event == EVENT_DATA_AVAILABLE && data_buffer_size > 0) {
		*data_size = data_buffer_size;
		pending_event = EVENT_NONE; // Clear the event
		return data_buffer;
	}

	*data_size = 0;
	return NULL;
}

/* Create a properly formatted frame from data */
Frame* MakeFrame(uint8_t* data, size_t data_size) {
	if (data == NULL || data_size == 0 || data_size > MAX_DATA_SIZE) {
		return NULL;
	}

	Frame* frame = (Frame*)malloc(sizeof(Frame));
	if (frame == NULL) {
		return NULL;
	}

	// Initialize the frame
	memset(frame, 0, sizeof(Frame));

	// Set frame headers
	frame->magic_start = MAGIC_START;
	frame->sequence_num = sequence_counter++;
	frame->data_length = (uint16_t)data_size;

	// Copy data
	memcpy(frame->data, data, data_size);

	// Calculate checksums
	frame->checksum = CalculateHeaderChecksum(frame);

	// Set the end delimiter
	frame->magic_end = MAGIC_END;

	// Calculate frame checksum (must be last)
	frame->frame_checksum = CalculateFrameChecksum(frame);

	return frame;
}

/* Send a frame over the communication medium */
bool SendFrame(Frame* frame) {
	if (frame == NULL || output_fd < 0) {
		return false;
	}

	printf("Sending frame: seq=%u, len=%u bytes\n", 
			frame->sequence_num, frame->data_length);

	// Write the entire frame to the output file descriptor
	size_t total_size = HEADER_SIZE + frame->data_length + FOOTER_SIZE;
	ssize_t written = write(output_fd, frame, total_size);

	if (written != total_size) {
		printf("Error sending frame: wrote %zd of %zu bytes\n", written, total_size);
		return false;
	}

	printf("Frame sent successfully\n");
	pending_event = EVENT_FRAME_SENT;
	return true;
}

int main(int argc, char* argv[]) {
	// Check command line arguments
	if (argc != 2) {
		printf("Usage: %s <output_file>\n", argv[0]);
		return 1;
	}

	// Open the output file (or named pipe in a real implementation)
	output_fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_fd < 0) {
		perror("Failed to open output file");
		return 1;
	}

	printf("Sender started. Output to: %s\n", argv[1]);

	// Test message
	const char* test_message = "Hello, this is a test message for our protocol.";
	size_t message_len = strlen(test_message);

	// Copy to our buffer and signal an event
	memcpy(data_buffer, test_message, message_len);
	data_buffer_size = message_len;
	pending_event = EVENT_DATA_AVAILABLE;

	// Main sending loop
	int messages_sent = 0;
	while (messages_sent < 3) {  // Send 3 test messages
		if (WaitForEvent() == EVENT_DATA_AVAILABLE) {
			size_t data_size;
			uint8_t* data = GetData(&data_size);

			if (data != NULL) {
				Frame* frame = MakeFrame(data, data_size);
				if (frame != NULL) {
					if (SendFrame(frame)) {
						messages_sent++;

						// For demonstration: modify the message a bit each time
						snprintf((char*)data_buffer, MAX_DATA_SIZE, 
								"Test message #%d from sender", messages_sent + 1);
						data_buffer_size = strlen((char*)data_buffer);
						pending_event = EVENT_DATA_AVAILABLE;
					}
					free(frame); // Clean up
				}
			}
		}

		// Small delay to prevent spinning
		usleep(100000);  // 100ms
	}

	// Close output file
	close(output_fd);
	printf("Sender finished\n");

	return 0;
}
