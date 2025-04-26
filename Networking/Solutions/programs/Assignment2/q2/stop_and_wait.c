/*
 * stop_and_wait.c - Implementation of the Stop-and-Wait Protocol
 * 
 * This implementation demonstrates both noiseless and noisy channel scenarios
 * with functionality for sender and receiver sides.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

/* Protocol configuration */
#define MAX_DATA_SIZE 1024
#define HEADER_SIZE 8
#define FOOTER_SIZE 4
#define MAX_FRAME_SIZE (HEADER_SIZE + MAX_DATA_SIZE + FOOTER_SIZE)
#define ACK_FRAME_SIZE 8

#define MAGIC_START 0xAA55
#define MAGIC_END 0x55AA
#define ACK_MAGIC 0x5AA5

#define MAX_RETRANSMIT 5     // Maximum number of retransmissions
#define TIMEOUT_MS 1000      // Timeout in milliseconds

/* Frame structure */
typedef struct {
    uint16_t magic_start;     // Start delimiter (MAGIC_START)
    uint8_t seq_num;          // Sequence number (0 or 1)
    uint8_t frame_type;       // 0 for data, 1 for ACK
    uint16_t data_length;     // Length of data
    uint16_t checksum;        // Header checksum
    uint8_t data[MAX_DATA_SIZE]; // Actual data
    uint32_t frame_checksum;  // Frame checksum
    uint16_t magic_end;       // End delimiter (MAGIC_END)
} Frame;

/* ACK frame structure */
typedef struct {
    uint16_t magic;           // ACK_MAGIC
    uint8_t ack_num;          // Acknowledged sequence number
    uint8_t reserved;         // Reserved for future use
    uint32_t checksum;        // ACK frame checksum
} AckFrame;

/* Channel simulation options */
typedef struct {
    bool noisy;              // Is the channel noisy?
    float loss_probability;  // Probability of losing a frame
    float corrupt_probability; // Probability of corrupting a frame
} ChannelOptions;

/* Global variables */
static uint8_t current_seq_num = 0;
static ChannelOptions channel_opts = {false, 0.0, 0.0};  // Default: noiseless

/* Helper functions */
uint16_t calculate_header_checksum(Frame* frame) {
    uint16_t sum = 0;
    sum += frame->magic_start;
    sum += frame->seq_num;
    sum += frame->frame_type;
    sum += frame->data_length;
    return ~sum;  // One's complement
}

uint32_t calculate_frame_checksum(Frame* frame) {
    uint32_t sum = 0;
    uint8_t* ptr = (uint8_t*)frame;
    
    // Calculate checksum up to data
    for (size_t i = 0; i < HEADER_SIZE; i++) {
        sum += ptr[i];
    }
    
    // Add data bytes
    for (size_t i = 0; i < frame->data_length; i++) {
        sum += frame->data[i];
    }
    
    // Add magic end
    sum += MAGIC_END & 0xFF;
    sum += (MAGIC_END >> 8) & 0xFF;
    
    return sum;
}

uint32_t calculate_ack_checksum(AckFrame* ack) {
    uint32_t sum = 0;
    sum += ack->magic;
    sum += ack->ack_num;
    sum += ack->reserved;
    return sum;
}

/* Create a data frame */
Frame* create_data_frame(uint8_t* data, uint16_t data_length) {
    if (data == NULL || data_length == 0 || data_length > MAX_DATA_SIZE) {
        return NULL;
    }
    
    Frame* frame = (Frame*)malloc(sizeof(Frame));
    if (frame == NULL) {
        return NULL;
    }
    
    // Initialize frame
    memset(frame, 0, sizeof(Frame));
    
    // Set header fields
    frame->magic_start = MAGIC_START;
    frame->seq_num = current_seq_num;
    frame->frame_type = 0;  // Data frame
    frame->data_length = data_length;
    
    // Copy data
    memcpy(frame->data, data, data_length);
    
    // Calculate checksums
    frame->checksum = calculate_header_checksum(frame);
    frame->magic_end = MAGIC_END;
    frame->frame_checksum = calculate_frame_checksum(frame);
    
    return frame;
}

/* Create an ACK frame */
AckFrame* create_ack_frame(uint8_t ack_num) {
    AckFrame* ack = (AckFrame*)malloc(sizeof(AckFrame));
    if (ack == NULL) {
        return NULL;
    }
    
    // Initialize ACK frame
    memset(ack, 0, sizeof(AckFrame));
    
    // Set fields
    ack->magic = ACK_MAGIC;
    ack->ack_num = ack_num;
    ack->reserved = 0;
    
    // Calculate checksum
    ack->checksum = calculate_ack_checksum(ack);
    
    return ack;
}

/* Validate a received frame */
bool validate_frame(Frame* frame) {
    // Check magic numbers
    if (frame->magic_start != MAGIC_START || frame->magic_end != MAGIC_END) {
        printf("Magic number mismatch\n");
        return false;
    }
    
    // Check header checksum
    uint16_t calculated_header_checksum = calculate_header_checksum(frame);
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
    uint32_t calculated_frame_checksum = calculate_frame_checksum(frame);
    if (calculated_frame_checksum != frame->frame_checksum) {
        printf("Frame checksum mismatch\n");
        return false;
    }
    
    return true;
}

/* Validate a received ACK frame */
bool validate_ack_frame(AckFrame* ack) {
    // Check magic number
    if (ack->magic != ACK_MAGIC) {
        printf("ACK magic number mismatch\n");
        return false;
    }
    
    // Verify checksum
    uint32_t calculated_checksum = calculate_ack_checksum(ack);
    if (calculated_checksum != ack->checksum) {
        printf("ACK checksum mismatch\n");
        return false;
    }
    
    return true;
}

/* Simulate channel noise */
bool simulate_channel_noise(void* data, size_t size, bool is_data_frame) {
    if (!channel_opts.noisy) {
        return true;  // Noiseless channel, frame passes through
    }
    
    // Simulate frame loss
    float loss_roll = (float)rand() / RAND_MAX;
    if (loss_roll < channel_opts.loss_probability) {
        printf("Channel: Frame lost in transit\n");
        return false;
    }
    
    // Simulate corruption
    float corrupt_roll = (float)rand() / RAND_MAX;
    if (corrupt_roll < channel_opts.corrupt_probability) {
        printf("Channel: Frame corrupted in transit\n");
        // Corrupt one random byte in the frame
        uint8_t* bytes = (uint8_t*)data;
        size_t corrupt_pos = rand() % size;
        bytes[corrupt_pos] ^= 0xFF;  // Flip all bits in the byte
    }
    
    return true;
}

/* Sender operation - send a frame and wait for ACK */
bool sender_send_frame(uint8_t* data, uint16_t data_length, void* channel_send, void* channel_receive) {
    int retransmit_count = 0;
    Frame* frame = NULL;
    AckFrame* ack = NULL;
    bool success = false;
    
    // Function pointers for channel operations
    bool (*send_to_channel)(void*, size_t) = channel_send;
    bool (*receive_from_channel)(void*, size_t*) = channel_receive;
    
    // Create the data frame
    frame = create_data_frame(data, data_length);
    if (frame == NULL) {
        printf("Failed to create frame\n");
        return false;
    }
    
    // Calculate total frame size
    size_t frame_size = HEADER_SIZE + frame->data_length + FOOTER_SIZE;
    
    // Allocate memory for the ACK
    ack = (AckFrame*)malloc(sizeof(AckFrame));
    if (ack == NULL) {
        free(frame);
        return false;
    }
    
    // Main send-and-wait loop
    while (retransmit_count <= MAX_RETRANSMIT) {
        printf("Sender: Sending frame with seq_num=%d, attempt %d\n", 
               current_seq_num, retransmit_count + 1);
        
        // Send the frame
        if (!send_to_channel(frame, frame_size)) {
            printf("Sender: Frame lost in transit\n");
            goto retry;
        }
        
        // Set timeout
        struct timeval start_time, current_time;
        gettimeofday(&start_time, NULL);
        
        // Wait for ACK with timeout
        bool ack_received = false;
        while (!ack_received) {
            // Check if we've timed out
            gettimeofday(&current_time, NULL);
            long elapsed_ms = (current_time.tv_sec - start_time.tv_sec) * 1000 + 
                             (current_time.tv_usec - start_time.tv_usec) / 1000;
            if (elapsed_ms > TIMEOUT_MS) {
                printf("Sender: ACK timeout\n");
                break;
            }
            
            // Try to receive ACK
            size_t ack_size = sizeof(AckFrame);
            if (receive_from_channel(ack, &ack_size)) {
                // Validate ACK
                if (validate_ack_frame(ack)) {
                    if (ack->ack_num == current_seq_num) {
                        printf("Sender: Received valid ACK for seq_num=%d\n", current_seq_num);
                        ack_received = true;
                        success = true;
                        // Toggle sequence number for next frame
                        current_seq_num = (current_seq_num + 1) % 2;
                        break;
                    } else {
                        printf("Sender: Received ACK for wrong sequence number\n");
                    }
                } else {
                    printf("Sender: Received invalid ACK\n");
                }
            }
            
            // Small delay to prevent CPU hogging
            usleep(10000);  // 10ms
        }
        
        if (success) {
            break;
        }
        
    retry:
        retransmit_count++;
        if (retransmit_count > MAX_RETRANSMIT) {
            printf("Sender: Max retransmissions reached, giving up\n");
            break;
        }
        
        // Small delay before retransmission
        usleep(100000);  // 100ms
    }
    
    // Clean up
    free(frame);
    free(ack);
    
    return success;
}

/* Receiver operation - receive a frame and send ACK */
bool receiver_receive_frame(uint8_t* data_buffer, uint16_t* data_length, void* channel_receive, void* channel_send) {
    Frame* frame = NULL;
    AckFrame* ack = NULL;
    bool success = false;
    
    // Function pointers for channel operations
    bool (*receive_from_channel)(void*, size_t*) = channel_receive;
    bool (*send_to_channel)(void*, size_t) = channel_send;
    
    // Allocate memory for the frame
    frame = (Frame*)malloc(sizeof(Frame));
    if (frame == NULL) {
        return false;
    }
    
    // Receive the frame
    size_t frame_size = sizeof(Frame);  // Initially set to max size
    if (!receive_from_channel(frame, &frame_size)) {
        printf("Receiver: Failed to receive frame\n");
        free(frame);
        return false;
    }
    
    // Validate the frame
    if (!validate_frame(frame)) {
        printf("Receiver: Received invalid frame\n");
        
        // Send negative ACK (using previous sequence number)
        uint8_t expected_seq = (current_seq_num == 0) ? 1 : 0;
        ack = create_ack_frame(expected_seq);
        if (ack != NULL) {
            printf("Receiver: Sending NAK (ACK for seq_num=%d)\n", expected_seq);
            send_to_channel(ack, sizeof(AckFrame));
            free(ack);
        }
        
        free(frame);
        return false;
    }
    
    // Check sequence number
    if (frame->seq_num == current_seq_num) {
        // This is the frame we're expecting
        printf("Receiver: Received valid frame with seq_num=%d\n", current_seq_num);
        
        // Copy data to output buffer
        if (data_buffer != NULL && data_length != NULL) {
            size_t copy_size = (frame->data_length <= MAX_DATA_SIZE) ? frame->data_length : MAX_DATA_SIZE;
            memcpy(data_buffer, frame->data, copy_size);
            *data_length = copy_size;
        }
        
        // Toggle sequence number for next frame
        current_seq_num = (current_seq_num + 1) % 2;
        success = true;
    } else {
        printf("Receiver: Received duplicate frame with seq_num=%d, expected %d\n", 
               frame->seq_num, current_seq_num);
    }
    
    // Send ACK for the received frame
    ack = create_ack_frame(frame->seq_num);
    if (ack != NULL) {
        printf("Receiver: Sending ACK for seq_num=%d\n", frame->seq_num);
        send_to_channel(ack, sizeof(AckFrame));
        free(ack);
    }
    
    free(frame);
    return success;
}

/*
 * Channel simulation functions
 * 
 * In a real implementation, these would be replaced with actual network I/O,
 * but for this example, we're simulating the channel in memory.
 */

/* Global variables for channel simulation */
static uint8_t channel_buffer[MAX_FRAME_SIZE];
static size_t channel_data_size = 0;
static bool channel_has_data = false;

/* Reset the channel */
void channel_reset() {
    memset(channel_buffer, 0, sizeof(channel_buffer));
    channel_data_size = 0;
    channel_has_data = false;
}

/* Send data to the channel */
bool channel_send(void* data, size_t size) {
    if (channel_has_data) {
        printf("Channel: Busy, data lost\n");
        return false;
    }
    
    // Simulate channel noise
    if (!simulate_channel_noise(data, size, size > ACK_FRAME_SIZE)) {
        return false;  // Frame was "lost" in transit
    }
    
    // Copy data to channel buffer
    size_t copy_size = (size <= sizeof(channel_buffer)) ? size : sizeof(channel_buffer);
    memcpy(channel_buffer, data, copy_size);
    channel_data_size = copy_size;
    channel_has_data = true;
    
    return true;
}

/* Receive data from the channel */
bool channel_receive(void* data, size_t* size) {
    if (!channel_has_data) {
        return false;
    }
    
    // Copy data from channel buffer
    size_t copy_size = (channel_data_size <= *size) ? channel_data_size : *size;
    memcpy(data, channel_buffer, copy_size);
    *size = copy_size;
    
    // Clear channel buffer
    channel_has_data = false;
    
    return true;
}

/* Demo functions */
void test_stop_and_wait(bool noisy_channel, float loss_prob, float corrupt_prob) {
    // Set channel options
    channel_opts.noisy = noisy_channel;
    channel_opts.loss_probability = loss_prob;
    channel_opts.corrupt_probability = corrupt_prob;
    
    // Reset sequence numbers
    current_seq_num = 0;
    
    printf("\n----- Testing Stop-and-Wait Protocol -----\n");
    printf("Channel: %s\n", noisy_channel ? "Noisy" : "Noiseless");
    if (noisy_channel) {
        printf("Loss probability: %.2f, Corruption probability: %.2f\n", 
               loss_prob, corrupt_prob);
    }
    
    const char* test_messages[] = {
        "Hello, this is message 1",
        "This is the second test message",
        "Third message, a bit longer to test larger frames",
        "Final test message - Stop-and-wait protocol test"
    };
    int num_messages = sizeof(test_messages) / sizeof(test_messages[0]);
    
    for (int i = 0; i < num_messages; i++) {
        printf("\n--- Sending message %d ---\n", i + 1);
        
        // Reset channel
        channel_reset();
        
        // Send message
        size_t data_len = strlen(test_messages[i]) + 1;  // Include null terminator
        bool send_result = sender_send_frame((uint8_t*)test_messages[i], data_len, 
                                           channel_send, channel_receive);
        
        if (send_result) {
            // Reset channel for next message (simulating half-duplex)
            channel_reset();
            
            // Receive message
            uint8_t recv_buffer[MAX_DATA_SIZE];
            uint16_t recv_size = 0;
            bool recv_result = receiver_receive_frame(recv_buffer, &recv_size, 
                                                    channel_receive, channel_send);
            
            if (recv_result) {
                printf("Test: Successfully received message: '%s'\n", recv_buffer);
            } else {
                printf("Test: Failed to receive message\n");
            }
        } else {
            printf("Test: Failed to send message\n");
        }
    }
}

int main() {
    // Seed random number generator
    srand(time(NULL));
    
    // Test 1: Noiseless channel
    test_stop_and_wait(false, 0.0, 0.0);
    
    // Test 2: Noisy channel with 20% loss and 15% corruption
    test_stop_and_wait(true, 0.2, 0.15);
    
    // Test 3: Highly reliable channel with 5% loss and 5% corruption
    test_stop_and_wait(true, 0.05, 0.05);
    
    // Test 4: Unreliable channel with 40% loss and 30% corruption
    test_stop_and_wait(true, 0.4, 0.3);
    
    return 0;
}
