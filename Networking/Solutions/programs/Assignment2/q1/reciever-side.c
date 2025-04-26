/* receiver.c - Receiver-side implementation */
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Protocol constants */
#define MAX_FRAME_SIZE 1024
#define MAX_DATA_SIZE 1000
#define HEADER_SIZE 8
#define FOOTER_SIZE 4
#define MAGIC_START 0xAA55
#define MAGIC_END 0x55AA

/* Frame structure - must match sender's definition */
typedef struct {
  uint16_t magic_start;        // Start delimiter (MAGIC_START)
  uint16_t sequence_num;       // Sequence number
  uint16_t data_length;        // Length of data
  uint16_t checksum;           // Header checksum
  uint8_t data[MAX_DATA_SIZE]; // Actual data
  uint32_t frame_checksum;     // Frame checksum
  uint16_t magic_end;          // End delimiter (MAGIC_END)
} Frame;

/* Event types */
typedef enum { EVENT_NONE = 0, EVENT_FRAME_RECEIVED, EVENT_ERROR } EventType;

/* Global variables */
static int input_fd = -1; // File descriptor for input

/* Helper functions */
uint16_t CalculateHeaderChecksum(Frame *frame) {
  uint16_t sum = 0;
  sum += frame->magic_start;
  sum += frame->sequence_num;
  sum += frame->data_length;
  return ~sum; // One's complement
}

uint32_t CalculateFrameChecksum(Frame *frame) {
  uint32_t sum = 0;
  uint8_t *ptr = (uint8_t *)frame;

  // Calculate checksum up to data
  for (size_t i = 0; i < HEADER_SIZE + frame->data_length; i++) {
    sum += ptr[i];
  }

  // Add magic end in calculation
  sum += MAGIC_END & 0xFF;
  sum += (MAGIC_END >> 8) & 0xFF;

  return sum;
}

/* Validate received frame */
bool ValidateFrame(Frame *frame) {
  // Check magic numbers
  if (frame->magic_start != MAGIC_START || frame->magic_end != MAGIC_END) {
    printf("Magic number mismatch\n");
    return false;
  }

  // Check header checksum
  uint16_t calculated_header_checksum = CalculateHeaderChecksum(frame);
  if (calculated_header_checksum != frame->checksum) {
    printf("Header checksum mismatch\n");
    return false;
  }

  // Check data length
  if (frame->data_length > MAX_DATA_SIZE) {
    printf("Data size too large\n");
    return false;
  }

  // Verify frame checksum
  uint32_t calculated_frame_checksum = CalculateFrameChecksum(frame);
  if (calculated_frame_checksum != frame->frame_checksum) {
    printf("Frame checksum mismatch\n");
    return false;
  }

  return true;
}

/* Receive a frame from the communication medium */
Frame *ReceiveFrame(void) {
  if (input_fd < 0) {
    return NULL;
  }

  Frame *frame = (Frame *)malloc(sizeof(Frame));
  if (frame == NULL) {
    return NULL;
  }

  // Read the header first to get the data length
  ssize_t read_bytes = read(input_fd, frame, HEADER_SIZE);
  if (read_bytes != HEADER_SIZE) {
    if (read_bytes == 0) {
      printf("End of file reached\n");
    } else {
      printf("Error reading header: got %zd bytes\n", read_bytes);
    }
    free(frame);
    return NULL;
  }

  // Validate header and check data length
  if (frame->magic_start != MAGIC_START || frame->data_length > MAX_DATA_SIZE) {
    printf("Invalid header or data length\n");
    free(frame);
    return NULL;
  }

  // Now read the data and footer
  size_t remaining = frame->data_length + FOOTER_SIZE;
  uint8_t *data_ptr = (uint8_t *)frame + HEADER_SIZE;

  while (remaining > 0) {
    read_bytes = read(input_fd, data_ptr, remaining);
    if (read_bytes <= 0) {
      printf("Error reading data/footer\n");
      free(frame);
      return NULL;
    }
    remaining -= read_bytes;
    data_ptr += read_bytes;
  }

  // Validate the complete frame
  if (!ValidateFrame(frame)) {
    printf("Frame validation failed\n");
    free(frame);
    return NULL;
  }

  return frame;
}

/* Extract data from a received frame */
uint8_t *ExtractData(Frame *frame, size_t *data_size) {
  if (frame == NULL) {
    *data_size = 0;
    return NULL;
  }

  *data_size = frame->data_length;

  // Allocate memory for the extracted data
  uint8_t *data =
      (uint8_t *)malloc(frame->data_length + 1); // +1 for null terminator
  if (data == NULL) {
    *data_size = 0;
    return NULL;
  }

  // Copy the data from the frame
  memcpy(data, frame->data, frame->data_length);
  data[frame->data_length] = '\0'; // Null-terminate for string display

  return data;
}

/* Deliver data to the application layer */
bool DeliverData(uint8_t *data, size_t data_size) {
  if (data == NULL || data_size == 0) {
    return false;
  }

  // In a real implementation, this would deliver the data to the application
  printf("Received message (%zu bytes): %s\n", data_size, data);

  return true;
}

int main(int argc, char *argv[]) {
  // Check command line arguments
  if (argc != 2) {
    printf("Usage: %s <input_file>\n", argv[0]);
    return 1;
  }

  // Open the input file (or named pipe in a real implementation)
  input_fd = open(argv[1], O_RDONLY);
  if (input_fd < 0) {
    perror("Failed to open input file");
    return 1;
  }

  printf("Receiver started. Input from: %s\n", argv[1]);

  // Main receiving loop
  int frames_received = 0;
  while (1) {
    Frame *frame = ReceiveFrame();
    if (frame == NULL) {
      // End of file or error
      break;
    }

    frames_received++;
    printf("Received frame #%d: seq=%u, len=%u bytes\n", frames_received,
           frame->sequence_num, frame->data_length);

    size_t data_size;
    uint8_t *data = ExtractData(frame, &data_size);

    if (data != NULL) {
      if (DeliverData(data, data_size)) {
        printf("Data delivered successfully\n");
      }
      free(data);
    }

    free(frame);
  }

  // Close input file
  close(input_fd);
  printf("Receiver finished. Processed %d frames\n", frames_received);

  return 0;
}
