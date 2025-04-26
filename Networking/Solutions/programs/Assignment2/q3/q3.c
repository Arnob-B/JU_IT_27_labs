#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_SEQ_NUM 8  // Window size
#define TIMEOUT_SEC 1
#define TIMEOUT_USEC 0
#define MAX_RETRIES 5
#define PACKET_LOSS_RATE 10  // Simulated packet loss (%)

// Packet structure for all implementations
typedef struct {
    int seq_num;     // Sequence number
    int ack_num;     // Acknowledgment number
    int data_size;   // Size of data
    bool is_ack;     // Is this an ACK packet
    bool is_nack;    // Is this a NACK packet (used only in NACK-based)
    char data[BUFFER_SIZE];  // Data buffer
} Packet;

// Function prototypes
void initPacket(Packet *packet);
void printPacket(Packet *packet, bool isSending);
int sendPacket(int sockfd, Packet *packet, struct sockaddr *addr, socklen_t addr_len);
int receivePacket(int sockfd, Packet *packet, struct sockaddr *addr, socklen_t *addr_len, int timeout_sec, int timeout_usec);
bool isPacketLost();

// Simulation Modes
typedef enum {
    NON_NACK,
    NACK_BASED,
    PIGGYBACKED
} Mode;

// Implementation of the three protocol variants
void senderNonNACK(int sockfd, struct sockaddr *addr, socklen_t addr_len, char *message);
void receiverNonNACK(int sockfd, struct sockaddr *addr, socklen_t addr_len);

void senderNACKBased(int sockfd, struct sockaddr *addr, socklen_t addr_len, char *message);
void receiverNACKBased(int sockfd, struct sockaddr *addr, socklen_t addr_len);

void senderPiggybacked(int sockfd, struct sockaddr *addr, socklen_t addr_len, char *message);
void receiverPiggybacked(int sockfd, struct sockaddr *addr, socklen_t addr_len);

// Main function
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s [sender|receiver] [non-nack|nack|piggybacked] [message]\n", argv[0]);
        return 1;
    }

    int sockfd;
    struct sockaddr_in addr;

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);

    // Set timeout for socket operations
    struct timeval tv;
    tv.tv_sec = TIMEOUT_SEC;
    tv.tv_usec = TIMEOUT_USEC;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    // Seed random number generator
    srand(time(NULL));

    Mode mode;
    if (strcmp(argv[2], "non-nack") == 0) {
        mode = NON_NACK;
    } else if (strcmp(argv[2], "nack") == 0) {
        mode = NACK_BASED;
    } else if (strcmp(argv[2], "piggybacked") == 0) {
        mode = PIGGYBACKED;
    } else {
        printf("Invalid mode. Use non-nack, nack, or piggybacked\n");
        return 1;
    }

    if (strcmp(argv[1], "sender") == 0) {
        // Sender Mode
        if (argc < 4) {
            printf("Sender needs a message to send. Usage: %s sender [mode] [message]\n", argv[0]);
            return 1;
        }
        
        addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Send to localhost
        
        switch (mode) {
            case NON_NACK:
                senderNonNACK(sockfd, (struct sockaddr *)&addr, sizeof(addr), argv[3]);
                break;
            case NACK_BASED:
                senderNACKBased(sockfd, (struct sockaddr *)&addr, sizeof(addr), argv[3]);
                break;
            case PIGGYBACKED:
                senderPiggybacked(sockfd, (struct sockaddr *)&addr, sizeof(addr), argv[3]);
                break;
        }
    } else if (strcmp(argv[1], "receiver") == 0) {
        // Receiver Mode
        addr.sin_addr.s_addr = INADDR_ANY;  // Receive from any address
        
        // Bind the socket
        if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
            perror("Bind failed");
            exit(EXIT_FAILURE);
        }
        
        printf("Receiver started on port %d using %s mode\n", PORT, argv[2]);
        
        switch (mode) {
            case NON_NACK:
                receiverNonNACK(sockfd, (struct sockaddr *)&addr, sizeof(addr));
                break;
            case NACK_BASED:
                receiverNACKBased(sockfd, (struct sockaddr *)&addr, sizeof(addr));
                break;
            case PIGGYBACKED:
                receiverPiggybacked(sockfd, (struct sockaddr *)&addr, sizeof(addr));
                break;
        }
    } else {
        printf("Invalid role. Use sender or receiver\n");
        return 1;
    }

    close(sockfd);
    return 0;
}

// Initialize a packet with default values
void initPacket(Packet *packet) {
    packet->seq_num = 0;
    packet->ack_num = 0;
    packet->data_size = 0;
    packet->is_ack = false;
    packet->is_nack = false;
    memset(packet->data, 0, BUFFER_SIZE);
}

// Print packet information
void printPacket(Packet *packet, bool isSending) {
    char *action = isSending ? "Sending" : "Received";
    char *type = "DATA";
    
    if (packet->is_ack) {
        type = "ACK";
    } else if (packet->is_nack) {
        type = "NACK";
    }
    
    printf("%s %s packet - SEQ: %d, ACK: %d, Size: %d\n", 
           action, type, packet->seq_num, packet->ack_num, packet->data_size);
    
    if (!packet->is_ack && !packet->is_nack && packet->data_size > 0) {
        printf("  Data: %.*s\n", packet->data_size, packet->data);
    }
}

// Send a packet with simulated packet loss
int sendPacket(int sockfd, Packet *packet, struct sockaddr *addr, socklen_t addr_len) {
    // Simulate packet loss
    if (isPacketLost()) {
        printf("[SIMULATED] Packet lost (SEQ: %d)\n", packet->seq_num);
        return 0;  // Simulate successful send but packet is lost
    }
    
    printPacket(packet, true);
    return sendto(sockfd, packet, sizeof(Packet), 0, addr, addr_len);
}

// Receive a packet with timeout
int receivePacket(int sockfd, Packet *packet, struct sockaddr *addr, socklen_t *addr_len, int timeout_sec, int timeout_usec) {
    // Set timeout
    fd_set read_fds;
    struct timeval tv;
    
    FD_ZERO(&read_fds);
    FD_SET(sockfd, &read_fds);
    
    tv.tv_sec = timeout_sec;
    tv.tv_usec = timeout_usec;
    
    int ret = select(sockfd + 1, &read_fds, NULL, NULL, &tv);
    if (ret < 0) {
        perror("Select error");
        return -1;
    } else if (ret == 0) {
        // Timeout occurred
        return 0;
    }
    
    // Receive the packet
    int bytes = recvfrom(sockfd, packet, sizeof(Packet), 0, addr, addr_len);
    if (bytes > 0) {
        printPacket(packet, false);
    }
    
    return bytes;
}

// Simulate packet loss
bool isPacketLost() {
    return (rand() % 100) < PACKET_LOSS_RATE;
}

/*
 * Implementation of Non-NACK based Go-back-N
 * In this implementation, the receiver only sends ACKs for correctly received packets.
 * The sender uses a timer to detect lost packets and retransmits all unacknowledged packets.
 */
void senderNonNACK(int sockfd, struct sockaddr *addr, socklen_t addr_len, char *message) {
    int base = 0;          // First unacknowledged packet
    int nextSeqNum = 0;    // Next sequence number to be used
    int messageLen = strlen(message);
    int chunkSize = BUFFER_SIZE / 2;  // Size of data chunks
    int numPackets = (messageLen + chunkSize - 1) / chunkSize;  // Ceiling division
    
    Packet packets[MAX_SEQ_NUM];  // Buffer for sent packets
    Packet ackPacket;             // Buffer for received ACKs
    socklen_t len = addr_len;
    int retries = 0;
    
    printf("Sending message of length %d in %d packets using Non-NACK mode\n", messageLen, numPackets);
    
    // Send packets within window
    while (base < numPackets) {
        // Send new packets within window
        while (nextSeqNum < base + MAX_SEQ_NUM && nextSeqNum < numPackets) {
            // Prepare packet
            initPacket(&packets[nextSeqNum % MAX_SEQ_NUM]);
            packets[nextSeqNum % MAX_SEQ_NUM].seq_num = nextSeqNum;
            
            // Calculate data size for this packet
            int offset = nextSeqNum * chunkSize;
            packets[nextSeqNum % MAX_SEQ_NUM].data_size = (offset + chunkSize <= messageLen) ? 
                                                         chunkSize : messageLen - offset;
            
            // Copy data
            memcpy(packets[nextSeqNum % MAX_SEQ_NUM].data, 
                   message + offset, 
                   packets[nextSeqNum % MAX_SEQ_NUM].data_size);
            
            // Send packet
            if (sendPacket(sockfd, &packets[nextSeqNum % MAX_SEQ_NUM], addr, addr_len) < 0) {
                perror("Send failed");
            }
            
            nextSeqNum++;
        }
        
        // Try to receive ACK
        int result = receivePacket(sockfd, &ackPacket, addr, &len, TIMEOUT_SEC, TIMEOUT_USEC);
        
        if (result > 0 && ackPacket.is_ack) {
            // Valid ACK received
            if (ackPacket.ack_num >= base) {
                printf("Moving window: base %d -> %d\n", base, ackPacket.ack_num + 1);
                base = ackPacket.ack_num + 1;  // Move window
                retries = 0;  // Reset retry counter
            }
        } else {
            // Timeout or invalid packet
            retries++;
            if (retries > MAX_RETRIES) {
                printf("Maximum retries reached. Terminating.\n");
                return;
            }
            
            printf("Timeout/Invalid packet. Retransmitting unacknowledged packets (%d to %d)\n", 
                  base, nextSeqNum - 1);
            
            // Retransmit all unacknowledged packets
            for (int i = base; i < nextSeqNum; i++) {
                printf("Retransmitting packet %d\n", i);
                if (sendPacket(sockfd, &packets[i % MAX_SEQ_NUM], addr, addr_len) < 0) {
                    perror("Retransmission failed");
                }
            }
        }
    }
    
    printf("All packets sent and acknowledged. Transmission complete.\n");
}

void receiverNonNACK(int sockfd, struct sockaddr *addr, socklen_t addr_len) {
    int expectedSeqNum = 0;  // Next expected sequence number
    Packet receivedPacket;
    Packet ackPacket;
    socklen_t len = addr_len;
    char receivedData[65536] = {0};  // Buffer for complete message (arbitrary large size)
    int totalDataSize = 0;
    
    printf("Receiver started (Non-NACK mode)\n");
    
    while (1) {
        // Receive a packet
        int result = receivePacket(sockfd, &receivedPacket, addr, &len, 5, 0);  // 5-second timeout for inactivity
        
        if (result <= 0) {
            if (result == 0) {
                // Timeout, check if we have received any data
                if (totalDataSize > 0) {
                    printf("Receiver timeout. Transmission appears complete.\n");
                    printf("Received message: %s\n", receivedData);
                    break;
                }
                continue;  // Keep waiting if no data received yet
            } else {
                perror("Receive error");
                continue;
            }
        }
        
        // Process received packet
        if (receivedPacket.seq_num == expectedSeqNum) {
            // Expected packet received
            printf("Received expected packet %d\n", expectedSeqNum);
            
            // Copy data to buffer
            memcpy(receivedData + totalDataSize, receivedPacket.data, receivedPacket.data_size);
            totalDataSize += receivedPacket.data_size;
            
            // Send ACK
            initPacket(&ackPacket);
            ackPacket.is_ack = true;
            ackPacket.ack_num = expectedSeqNum;
            
            if (sendPacket(sockfd, &ackPacket, addr, len) < 0) {
                perror("ACK send failed");
            }
            
            expectedSeqNum++;  // Increment expected sequence number
        } else {
            // Unexpected packet received, send ACK for last correctly received packet
            printf("Received out-of-order packet %d, expected %d\n", receivedPacket.seq_num, expectedSeqNum);
            
            initPacket(&ackPacket);
            ackPacket.is_ack = true;
            ackPacket.ack_num = expectedSeqNum - 1;
            
            if (sendPacket(sockfd, &ackPacket, addr, len) < 0) {
                perror("ACK send failed");
            }
        }
    }
}

/*
 * Implementation of NACK-based Go-back-N
 * In this implementation, the receiver sends ACKs for correctly received packets
 * and NACKs for out-of-order packets. The sender retransmits on receiving a NACK.
 */
void senderNACKBased(int sockfd, struct sockaddr *addr, socklen_t addr_len, char *message) {
    int base = 0;          // First unacknowledged packet
    int nextSeqNum = 0;    // Next sequence number to be used
    int messageLen = strlen(message);
    int chunkSize = BUFFER_SIZE / 2;  // Size of data chunks
    int numPackets = (messageLen + chunkSize - 1) / chunkSize;  // Ceiling division
    
    Packet packets[MAX_SEQ_NUM];  // Buffer for sent packets
    Packet responsePacket;        // Buffer for received ACKs/NACKs
    socklen_t len = addr_len;
    int retries = 0;
    
    printf("Sending message of length %d in %d packets using NACK-based mode\n", messageLen, numPackets);
    
    // Send packets within window
    while (base < numPackets) {
        // Send new packets within window
        while (nextSeqNum < base + MAX_SEQ_NUM && nextSeqNum < numPackets) {
            // Prepare packet
            initPacket(&packets[nextSeqNum % MAX_SEQ_NUM]);
            packets[nextSeqNum % MAX_SEQ_NUM].seq_num = nextSeqNum;
            
            // Calculate data size for this packet
            int offset = nextSeqNum * chunkSize;
            packets[nextSeqNum % MAX_SEQ_NUM].data_size = (offset + chunkSize <= messageLen) ? 
                                                         chunkSize : messageLen - offset;
            
            // Copy data
            memcpy(packets[nextSeqNum % MAX_SEQ_NUM].data, 
                   message + offset, 
                   packets[nextSeqNum % MAX_SEQ_NUM].data_size);
            
            // Send packet
            if (sendPacket(sockfd, &packets[nextSeqNum % MAX_SEQ_NUM], addr, addr_len) < 0) {
                perror("Send failed");
            }
            
            nextSeqNum++;
        }
        
        // Try to receive ACK or NACK
        int result = receivePacket(sockfd, &responsePacket, addr, &len, TIMEOUT_SEC, TIMEOUT_USEC);
        
        if (result > 0) {
            if (responsePacket.is_ack) {
                // ACK received
                if (responsePacket.ack_num >= base) {
                    printf("Moving window: base %d -> %d\n", base, responsePacket.ack_num + 1);
                    base = responsePacket.ack_num + 1;  // Move window
                    retries = 0;  // Reset retry counter
                }
            } else if (responsePacket.is_nack) {
                // NACK received, retransmit the specified packet and all following packets
                int nackSeq = responsePacket.ack_num;  // The ack_num field contains the missing sequence
                
                printf("NACK received for packet %d. Retransmitting from %d to %d\n", 
                       nackSeq, nackSeq, nextSeqNum - 1);
                
                for (int i = nackSeq; i < nextSeqNum; i++) {
                    if (sendPacket(sockfd, &packets[i % MAX_SEQ_NUM], addr, addr_len) < 0) {
                        perror("Retransmission failed");
                    }
                }
            }
        } else {
            // Timeout
            retries++;
            if (retries > MAX_RETRIES) {
                printf("Maximum retries reached. Terminating.\n");
                return;
            }
            
            printf("Timeout. Retransmitting unacknowledged packets (%d to %d)\n", 
                  base, nextSeqNum - 1);
            
            // Retransmit all unacknowledged packets
            for (int i = base; i < nextSeqNum; i++) {
                printf("Retransmitting packet %d\n", i);
                if (sendPacket(sockfd, &packets[i % MAX_SEQ_NUM], addr, addr_len) < 0) {
                    perror("Retransmission failed");
                }
            }
        }
    }
    
    printf("All packets sent and acknowledged. Transmission complete.\n");
}

void receiverNACKBased(int sockfd, struct sockaddr *addr, socklen_t addr_len) {
    int expectedSeqNum = 0;  // Next expected sequence number
    Packet receivedPacket;
    Packet responsePacket;
    socklen_t len = addr_len;
    char receivedData[65536] = {0};  // Buffer for complete message
    int totalDataSize = 0;
    
    printf("Receiver started (NACK-based mode)\n");
    
    while (1) {
        // Receive a packet
        int result = receivePacket(sockfd, &receivedPacket, addr, &len, 5, 0);  // 5-second timeout
        
        if (result <= 0) {
            if (result == 0) {
                // Timeout, check if we have received any data
                if (totalDataSize > 0) {
                    printf("Receiver timeout. Transmission appears complete.\n");
                    printf("Received message: %s\n", receivedData);
                    break;
                }
                continue;  // Keep waiting if no data received yet
            } else {
                perror("Receive error");
                continue;
            }
        }
        
        // Process received packet
        if (receivedPacket.seq_num == expectedSeqNum) {
            // Expected packet received
            printf("Received expected packet %d\n", expectedSeqNum);
            
            // Copy data to buffer
            memcpy(receivedData + totalDataSize, receivedPacket.data, receivedPacket.data_size);
            totalDataSize += receivedPacket.data_size;
            
            // Send ACK
            initPacket(&responsePacket);
            responsePacket.is_ack = true;
            responsePacket.ack_num = expectedSeqNum;
            
            if (sendPacket(sockfd, &responsePacket, addr, len) < 0) {
                perror("ACK send failed");
            }
            
            expectedSeqNum++;  // Increment expected sequence number
        } else if (receivedPacket.seq_num > expectedSeqNum) {
            // Received a future packet, send NACK for expected packet
            printf("Received out-of-order packet %d, expected %d. Sending NACK.\n", 
                   receivedPacket.seq_num, expectedSeqNum);
            
            initPacket(&responsePacket);
            responsePacket.is_nack = true;
            responsePacket.ack_num = expectedSeqNum;  // Indicating which packet is missing
            
            if (sendPacket(sockfd, &responsePacket, addr, len) < 0) {
                perror("NACK send failed");
            }
        } else {
            // Duplicate packet, ignore but send ACK for last correctly received packet
            printf("Received duplicate packet %d\n", receivedPacket.seq_num);
            
            initPacket(&responsePacket);
            responsePacket.is_ack = true;
            responsePacket.ack_num = expectedSeqNum - 1;
            
            if (sendPacket(sockfd, &responsePacket, addr, len) < 0) {
                perror("ACK send failed");
            }
        }
    }
}

/*
 * Implementation of Piggybacked Go-back-N
 * In this implementation, both sender and receiver can send data.
 * ACKs are piggybacked on data packets when possible.
 */
void senderPiggybacked(int sockfd, struct sockaddr *addr, socklen_t addr_len, char *message) {
    int base = 0;          // First unacknowledged packet
    int nextSeqNum = 0;    // Next sequence number to be used
    int messageLen = strlen(message);
    int chunkSize = BUFFER_SIZE / 2;  // Size of data chunks
    int numPackets = (messageLen + chunkSize - 1) / chunkSize;  // Ceiling division
    
    Packet packets[MAX_SEQ_NUM];  // Buffer for sent packets
    Packet receivedPacket;        // Buffer for received packets/ACKs
    socklen_t len = addr_len;
    int retries = 0;
    
    // For receiving data (as a receiver)
    int expectedSeqNum = 0;
    char receivedData[65536] = {0};
    int totalDataSize = 0;
    
    printf("Bidirectional communication with piggybacked ACKs\n");
    printf("Sending message of length %d in %d packets\n", messageLen, numPackets);
    
    while (base < numPackets || totalDataSize == 0) {
        // Send new packets within window
        while (nextSeqNum < base + MAX_SEQ_NUM && nextSeqNum < numPackets) {
            // Prepare packet
            initPacket(&packets[nextSeqNum % MAX_SEQ_NUM]);
            packets[nextSeqNum % MAX_SEQ_NUM].seq_num = nextSeqNum;
            
            // Piggyback ACK if we've received data
            if (expectedSeqNum > 0) {
                packets[nextSeqNum % MAX_SEQ_NUM].is_ack = true;
                packets[nextSeqNum % MAX_SEQ_NUM].ack_num = expectedSeqNum - 1;
                printf("Piggybacking ACK %d on data packet %d\n", 
                       expectedSeqNum - 1, nextSeqNum);
            }
            
            // Calculate data size for this packet
            int offset = nextSeqNum * chunkSize;
            packets[nextSeqNum % MAX_SEQ_NUM].data_size = (offset + chunkSize <= messageLen) ? 
                                                         chunkSize : messageLen - offset;
            
            // Copy data
            memcpy(packets[nextSeqNum % MAX_SEQ_NUM].data, 
                   message + offset, 
                   packets[nextSeqNum % MAX_SEQ_NUM].data_size);
            
            // Send packet
            if (sendPacket(sockfd, &packets[nextSeqNum % MAX_SEQ_NUM], addr, addr_len) < 0) {
                perror("Send failed");
            }
            
            nextSeqNum++;
        }
        
        // Receive response (data with piggybacked ACK or just ACK)
        int result = receivePacket(sockfd, &receivedPacket, addr, &len, TIMEOUT_SEC, TIMEOUT_USEC);
        
        if (result > 0) {
            // Check for ACK (piggybacked or not)
            if (receivedPacket.is_ack) {
                if (receivedPacket.ack_num >= base) {
                    printf("Moving window: base %d -> %d\n", base, receivedPacket.ack_num + 1);
                    base = receivedPacket.ack_num + 1;  // Move window
                    retries = 0;  // Reset retry counter
                }
            }
            
            // Check for data
            if (receivedPacket.data_size > 0) {
                // Process as a receiver
                if (receivedPacket.seq_num == expectedSeqNum) {
                    // Expected data packet
                    printf("Received data packet %d\n", expectedSeqNum);
                    
                    // Copy data
                    memcpy(receivedData + totalDataSize, receivedPacket.data, receivedPacket.data_size);
                    totalDataSize += receivedPacket.data_size;
                    
                    expectedSeqNum++;
                    
                    // If we don't have any new data to send, send a pure ACK
                    if (nextSeqNum >= base + MAX_SEQ_NUM || nextSeqNum >= numPackets) {
                        Packet ackPacket;
                        initPacket(&ackPacket);
                        ackPacket.is_ack = true;
                        ackPacket.ack_num = expectedSeqNum - 1;
                        
                        printf("Sending pure ACK %d\n", expectedSeqNum - 1);
                        if (sendPacket(sockfd, &ackPacket, addr, len) < 0) {
                            perror("ACK send failed");
                        }
                    }
                }
            }
        } else {
            // Timeout
            if (base < numPackets) {  // Only if we still have data to send
                retries++;
                if (retries > MAX_RETRIES) {
                    printf("Maximum retries reached.\n");
                    break;
                }
                
                printf("Timeout. Retransmitting unacknowledged packets (%d to %d)\n", 
                      base, nextSeqNum - 1);
                
                // Retransmit all unacknowledged packets
                for (int i = base; i < nextSeqNum; i++) {
                    // Update ACK number if needed
                    if (expectedSeqNum > 0) {
                        packets[i % MAX_SEQ_NUM].is_ack = true;
                        packets[i % MAX_SEQ_NUM].ack_num = expectedSeqNum - 1;
                    }
                    
                    printf("Retransmitting packet %d\n", i);
                    if (sendPacket(sockfd, &packets[i % MAX_SEQ_NUM], addr, len) < 0) {
                        perror("Retransmission failed");
                    }
                }
            } else if (totalDataSize > 0) {
                // We've sent all our data and received some data
                printf("All data sent. Received message: %s\n", receivedData);
                break;
            }
        }
    }
    
    printf("Communication complete.\n");
    if (totalDataSize > 0) {
        printf("Received message: %s\n", receivedData);
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_SEQ_NUM 8  // Window size
#define TIMEOUT_SEC 1
#define TIMEOUT_USEC 0
#define MAX_RETRIES 5
#define PACKET_LOSS_RATE 10  // Simulated packet loss (%)

// Packet structure for all implementations
typedef struct {
    int seq_num;     // Sequence number
    int ack_num;     // Acknowledgment number
    int data_size;   // Size of data
    bool is_ack;     // Is this an ACK packet
    bool is_nack;    // Is this a NACK packet (used only in NACK-based)
    char data[BUFFER_SIZE];  // Data buffer
} Packet;

// Function prototypes
void initPacket(Packet *packet);
void printPacket(Packet *packet, bool isSending);
int sendPacket(int sockfd, Packet *packet, struct sockaddr *addr, socklen_t addr_len);
int receivePacket(int sockfd, Packet *packet, struct sockaddr *addr, socklen_t *addr_len, int timeout_sec, int timeout_usec);
bool isPacketLost();

// Simulation Modes
typedef enum {
    NON_NACK,
    NACK_BASED,
    PIGGYBACKED
} Mode;

// Implementation of the three protocol variants
void senderNonNACK(int sockfd, struct sockaddr *addr, socklen_t addr_len, char *message);
void receiverNonNACK(int sockfd, struct sockaddr *addr, socklen_t addr_len);

void senderNACKBased(int sockfd, struct sockaddr *addr, socklen_t addr_len, char *message);
void receiverNACKBased(int sockfd, struct sockaddr *addr, socklen_t addr_len);

void senderPiggybacked(int sockfd, struct sockaddr *addr, socklen_t addr_len, char *message);
void receiverPiggybacked(int sockfd, struct sockaddr *addr, socklen_t addr_len);

// Main function
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s [sender|receiver] [non-nack|nack|piggybacked] [message]\n", argv[0]);
        return 1;
    }

    int sockfd;
    struct sockaddr_in addr;

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);

    // Set timeout for socket operations
    struct timeval tv;
    tv.tv_sec = TIMEOUT_SEC;
    tv.tv_usec = TIMEOUT_USEC;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    // Seed random number generator
    srand(time(NULL));

    Mode mode;
    if (strcmp(argv[2], "non-nack") == 0) {
        mode = NON_NACK;
    } else if (strcmp(argv[2], "nack") == 0) {
        mode = NACK_BASED;
    } else if (strcmp(argv[2], "piggybacked") == 0) {
        mode = PIGGYBACKED;
    } else {
        printf("Invalid mode. Use non-nack, nack, or piggybacked\n");
        return 1;
    }

    if (strcmp(argv[1], "sender") == 0) {
        // Sender Mode
        if (argc < 4) {
            printf("Sender needs a message to send. Usage: %s sender [mode] [message]\n", argv[0]);
            return 1;
        }
        
        addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Send to localhost
        
        switch (mode) {
            case NON_NACK:
                senderNonNACK(sockfd, (struct sockaddr *)&addr, sizeof(addr), argv[3]);
                break;
            case NACK_BASED:
                senderNACKBased(sockfd, (struct sockaddr *)&addr, sizeof(addr), argv[3]);
                break;
            case PIGGYBACKED:
                senderPiggybacked(sockfd, (struct sockaddr *)&addr, sizeof(addr), argv[3]);
                break;
        }
    } else if (strcmp(argv[1], "receiver") == 0) {
        // Receiver Mode
        addr.sin_addr.s_addr = INADDR_ANY;  // Receive from any address
        
        // Bind the socket
        if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
            perror("Bind failed");
            exit(EXIT_FAILURE);
        }
        
        printf("Receiver started on port %d using %s mode\n", PORT, argv[2]);
        
        switch (mode) {
            case NON_NACK:
                receiverNonNACK(sockfd, (struct sockaddr *)&addr, sizeof(addr));
                break;
            case NACK_BASED:
                receiverNACKBased(sockfd, (struct sockaddr *)&addr, sizeof(addr));
                break;
            case PIGGYBACKED:
                receiverPiggybacked(sockfd, (struct sockaddr *)&addr, sizeof(addr));
                break;
        }
    } else {
        printf("Invalid role. Use sender or receiver\n");
        return 1;
    }

    close(sockfd);
    return 0;
}

// Initialize a packet with default values
void initPacket(Packet *packet) {
    packet->seq_num = 0;
    packet->ack_num = 0;
    packet->data_size = 0;
    packet->is_ack = false;
    packet->is_nack = false;
    memset(packet->data, 0, BUFFER_SIZE);
}

// Print packet information
void printPacket(Packet *packet, bool isSending) {
    char *action = isSending ? "Sending" : "Received";
    char *type = "DATA";
    
    if (packet->is_ack) {
        type = "ACK";
    } else if (packet->is_nack) {
        type = "NACK";
    }
    
    printf("%s %s packet - SEQ: %d, ACK: %d, Size: %d\n", 
           action, type, packet->seq_num, packet->ack_num, packet->data_size);
    
    if (!packet->is_ack && !packet->is_nack && packet->data_size > 0) {
        printf("  Data: %.*s\n", packet->data_size, packet->data);
    }
}

// Send a packet with simulated packet loss
int sendPacket(int sockfd, Packet *packet, struct sockaddr *addr, socklen_t addr_len) {
    // Simulate packet loss
    if (isPacketLost()) {
        printf("[SIMULATED] Packet lost (SEQ: %d)\n", packet->seq_num);
        return 0;  // Simulate successful send but packet is lost
    }
    
    printPacket(packet, true);
    return sendto(sockfd, packet, sizeof(Packet), 0, addr, addr_len);
}

// Receive a packet with timeout
int receivePacket(int sockfd, Packet *packet, struct sockaddr *addr, socklen_t *addr_len, int timeout_sec, int timeout_usec) {
    // Set timeout
    fd_set read_fds;
    struct timeval tv;
    
    FD_ZERO(&read_fds);
    FD_SET(sockfd, &read_fds);
    
    tv.tv_sec = timeout_sec;
    tv.tv_usec = timeout_usec;
    
    int ret = select(sockfd + 1, &read_fds, NULL, NULL, &tv);
    if (ret < 0) {
        perror("Select error");
        return -1;
    } else if (ret == 0) {
        // Timeout occurred
        return 0;
    }
    
    // Receive the packet
    int bytes = recvfrom(sockfd, packet, sizeof(Packet), 0, addr, addr_len);
    if (bytes > 0) {
        printPacket(packet, false);
    }
    
    return bytes;
}

// Simulate packet loss
bool isPacketLost() {
    return (rand() % 100) < PACKET_LOSS_RATE;
}

/*
 * Implementation of Non-NACK based Go-back-N
 * In this implementation, the receiver only sends ACKs for correctly received packets.
 * The sender uses a timer to detect lost packets and retransmits all unacknowledged packets.
 */
void senderNonNACK(int sockfd, struct sockaddr *addr, socklen_t addr_len, char *message) {
    int base = 0;          // First unacknowledged packet
    int nextSeqNum = 0;    // Next sequence number to be used
    int messageLen = strlen(message);
    int chunkSize = BUFFER_SIZE / 2;  // Size of data chunks
    int numPackets = (messageLen + chunkSize - 1) / chunkSize;  // Ceiling division
    
    Packet packets[MAX_SEQ_NUM];  // Buffer for sent packets
    Packet ackPacket;             // Buffer for received ACKs
    socklen_t len = addr_len;
    int retries = 0;
    
    printf("Sending message of length %d in %d packets using Non-NACK mode\n", messageLen, numPackets);
    
    // Send packets within window
    while (base < numPackets) {
        // Send new packets within window
        while (nextSeqNum < base + MAX_SEQ_NUM && nextSeqNum < numPackets) {
            // Prepare packet
            initPacket(&packets[nextSeqNum % MAX_SEQ_NUM]);
            packets[nextSeqNum % MAX_SEQ_NUM].seq_num = nextSeqNum;
            
            // Calculate data size for this packet
            int offset = nextSeqNum * chunkSize;
            packets[nextSeqNum % MAX_SEQ_NUM].data_size = (offset + chunkSize <= messageLen) ? 
                                                         chunkSize : messageLen - offset;
            
            // Copy data
            memcpy(packets[nextSeqNum % MAX_SEQ_NUM].data, 
                   message + offset, 
                   packets[nextSeqNum % MAX_SEQ_NUM].data_size);
            
            // Send packet
            if (sendPacket(sockfd, &packets[nextSeqNum % MAX_SEQ_NUM], addr, addr_len) < 0) {
                perror("Send failed");
            }
            
            nextSeqNum++;
        }
        
        // Try to receive ACK
        int result = receivePacket(sockfd, &ackPacket, addr, &len, TIMEOUT_SEC, TIMEOUT_USEC);
        
        if (result > 0 && ackPacket.is_ack) {
            // Valid ACK received
            if (ackPacket.ack_num >= base) {
                printf("Moving window: base %d -> %d\n", base, ackPacket.ack_num + 1);
                base = ackPacket.ack_num + 1;  // Move window
                retries = 0;  // Reset retry counter
            }
        } else {
            // Timeout or invalid packet
            retries++;
            if (retries > MAX_RETRIES) {
                printf("Maximum retries reached. Terminating.\n");
                return;
            }
            
            printf("Timeout/Invalid packet. Retransmitting unacknowledged packets (%d to %d)\n", 
                  base, nextSeqNum - 1);
            
            // Retransmit all unacknowledged packets
            for (int i = base; i < nextSeqNum; i++) {
                printf("Retransmitting packet %d\n", i);
                if (sendPacket(sockfd, &packets[i % MAX_SEQ_NUM], addr, addr_len) < 0) {
                    perror("Retransmission failed");
                }
            }
        }
    }
    
    printf("All packets sent and acknowledged. Transmission complete.\n");
}

void receiverNonNACK(int sockfd, struct sockaddr *addr, socklen_t addr_len) {
    int expectedSeqNum = 0;  // Next expected sequence number
    Packet receivedPacket;
    Packet ackPacket;
    socklen_t len = addr_len;
    char receivedData[65536] = {0};  // Buffer for complete message (arbitrary large size)
    int totalDataSize = 0;
    
    printf("Receiver started (Non-NACK mode)\n");
    
    while (1) {
        // Receive a packet
        int result = receivePacket(sockfd, &receivedPacket, addr, &len, 5, 0);  // 5-second timeout for inactivity
        
        if (result <= 0) {
            if (result == 0) {
                // Timeout, check if we have received any data
                if (totalDataSize > 0) {
                    printf("Receiver timeout. Transmission appears complete.\n");
                    printf("Received message: %s\n", receivedData);
                    break;
                }
                continue;  // Keep waiting if no data received yet
            } else {
                perror("Receive error");
                continue;
            }
        }
        
        // Process received packet
        if (receivedPacket.seq_num == expectedSeqNum) {
            // Expected packet received
            printf("Received expected packet %d\n", expectedSeqNum);
            
            // Copy data to buffer
            memcpy(receivedData + totalDataSize, receivedPacket.data, receivedPacket.data_size);
            totalDataSize += receivedPacket.data_size;
            
            // Send ACK
            initPacket(&ackPacket);
            ackPacket.is_ack = true;
            ackPacket.ack_num = expectedSeqNum;
            
            if (sendPacket(sockfd, &ackPacket, addr, len) < 0) {
                perror("ACK send failed");
            }
            
            expectedSeqNum++;  // Increment expected sequence number
        } else {
            // Unexpected packet received, send ACK for last correctly received packet
            printf("Received out-of-order packet %d, expected %d\n", receivedPacket.seq_num, expectedSeqNum);
            
            initPacket(&ackPacket);
            ackPacket.is_ack = true;
            ackPacket.ack_num = expectedSeqNum - 1;
            
            if (sendPacket(sockfd, &ackPacket, addr, len) < 0) {
                perror("ACK send failed");
            }
        }
    }
}

/*
 * Implementation of NACK-based Go-back-N
 * In this implementation, the receiver sends ACKs for correctly received packets
 * and NACKs for out-of-order packets. The sender retransmits on receiving a NACK.
 */
void senderNACKBased(int sockfd, struct sockaddr *addr, socklen_t addr_len, char *message) {
    int base = 0;          // First unacknowledged packet
    int nextSeqNum = 0;    // Next sequence number to be used
    int messageLen = strlen(message);
    int chunkSize = BUFFER_SIZE / 2;  // Size of data chunks
    int numPackets = (messageLen + chunkSize - 1) / chunkSize;  // Ceiling division
    
    Packet packets[MAX_SEQ_NUM];  // Buffer for sent packets
    Packet responsePacket;        // Buffer for received ACKs/NACKs
    socklen_t len = addr_len;
    int retries = 0;
    
    printf("Sending message of length %d in %d packets using NACK-based mode\n", messageLen, numPackets);
    
    // Send packets within window
    while (base < numPackets) {
        // Send new packets within window
        while (nextSeqNum < base + MAX_SEQ_NUM && nextSeqNum < numPackets) {
            // Prepare packet
            initPacket(&packets[nextSeqNum % MAX_SEQ_NUM]);
            packets[nextSeqNum % MAX_SEQ_NUM].seq_num = nextSeqNum;
            
            // Calculate data size for this packet
            int offset = nextSeqNum * chunkSize;
            packets[nextSeqNum % MAX_SEQ_NUM].data_size = (offset + chunkSize <= messageLen) ? 
                                                         chunkSize : messageLen - offset;
            
            // Copy data
            memcpy(packets[nextSeqNum % MAX_SEQ_NUM].data, 
                   message + offset, 
                   packets[nextSeqNum % MAX_SEQ_NUM].data_size);
            
            // Send packet
            if (sendPacket(sockfd, &packets[nextSeqNum % MAX_SEQ_NUM], addr, addr_len) < 0) {
                perror("Send failed");
            }
            
            nextSeqNum++;
        }
        
        // Try to receive ACK or NACK
        int result = receivePacket(sockfd, &responsePacket, addr, &len, TIMEOUT_SEC, TIMEOUT_USEC);
        
        if (result > 0) {
            if (responsePacket.is_ack) {
                // ACK received
                if (responsePacket.ack_num >= base) {
                    printf("Moving window: base %d -> %d\n", base, responsePacket.ack_num + 1);
                    base = responsePacket.ack_num + 1;  // Move window
                    retries = 0;  // Reset retry counter
                }
            } else if (responsePacket.is_nack) {
                // NACK received, retransmit the specified packet and all following packets
                int nackSeq = responsePacket.ack_num;  // The ack_num field contains the missing sequence
                
                printf("NACK received for packet %d. Retransmitting from %d to %d\n", 
                       nackSeq, nackSeq, nextSeqNum - 1);
                
                for (int i = nackSeq; i < nextSeqNum; i++) {
                    if (sendPacket(sockfd, &packets[i % MAX_SEQ_NUM], addr, addr_len) < 0) {
                        perror("Retransmission failed");
                    }
                }
            }
        } else {
            // Timeout
            retries++;
            if (retries > MAX_RETRIES) {
                printf("Maximum retries reached. Terminating.\n");
                return;
            }
            
            printf("Timeout. Retransmitting unacknowledged packets (%d to %d)\n", 
                  base, nextSeqNum - 1);
            
            // Retransmit all unacknowledged packets
            for (int i = base; i < nextSeqNum; i++) {
                printf("Retransmitting packet %d\n", i);
                if (sendPacket(sockfd, &packets[i % MAX_SEQ_NUM], addr, addr_len) < 0) {
                    perror("Retransmission failed");
                }
            }
        }
    }
    
    printf("All packets sent and acknowledged. Transmission complete.\n");
}

void receiverNACKBased(int sockfd, struct sockaddr *addr, socklen_t addr_len) {
    int expectedSeqNum = 0;  // Next expected sequence number
    Packet receivedPacket;
    Packet responsePacket;
    socklen_t len = addr_len;
    char receivedData[65536] = {0};  // Buffer for complete message
    int totalDataSize = 0;
    
    printf("Receiver started (NACK-based mode)\n");
    
    while (1) {
        // Receive a packet
        int result = receivePacket(sockfd, &receivedPacket, addr, &len, 5, 0);  // 5-second timeout
        
        if (result <= 0) {
            if (result == 0) {
                // Timeout, check if we have received any data
                if (totalDataSize > 0) {
                    printf("Receiver timeout. Transmission appears complete.\n");
                    printf("Received message: %s\n", receivedData);
                    break;
                }
                continue;  // Keep waiting if no data received yet
            } else {
                perror("Receive error");
                continue;
            }
        }
        
        // Process received packet
        if (receivedPacket.seq_num == expectedSeqNum) {
            // Expected packet received
            printf("Received expected packet %d\n", expectedSeqNum);
            
            // Copy data to buffer
            memcpy(receivedData + totalDataSize, receivedPacket.data, receivedPacket.data_size);
            totalDataSize += receivedPacket.data_size;
            
            // Send ACK
            initPacket(&responsePacket);
            responsePacket.is_ack = true;
            responsePacket.ack_num = expectedSeqNum;
            
            if (sendPacket(sockfd, &responsePacket, addr, len) < 0) {
                perror("ACK send failed");
            }
            
            expectedSeqNum++;  // Increment expected sequence number
        } else if (receivedPacket.seq_num > expectedSeqNum) {
            // Received a future packet, send NACK for expected packet
            printf("Received out-of-order packet %d, expected %d. Sending NACK.\n", 
                   receivedPacket.seq_num, expectedSeqNum);
            
            initPacket(&responsePacket);
            responsePacket.is_nack = true;
            responsePacket.ack_num = expectedSeqNum;  // Indicating which packet is missing
            
            if (sendPacket(sockfd, &responsePacket, addr, len) < 0) {
                perror("NACK send failed");
            }
        } else {
            // Duplicate packet, ignore but send ACK for last correctly received packet
            printf("Received duplicate packet %d\n", receivedPacket.seq_num);
            
            initPacket(&responsePacket);
            responsePacket.is_ack = true;
            responsePacket.ack_num = expectedSeqNum - 1;
            
            if (sendPacket(sockfd, &responsePacket, addr, len) < 0) {
                perror("ACK send failed");
            }
        }
    }
}

/*
 * Implementation of Piggybacked Go-back-N
 * In this implementation, both sender and receiver can send data.
 * ACKs are piggybacked on data packets when possible.
 */
void senderPiggybacked(int sockfd, struct sockaddr *addr, socklen_t addr_len, char *message) {
    int base = 0;          // First unacknowledged packet
    int nextSeqNum = 0;    // Next sequence number to be used
    int messageLen = strlen(message);
    int chunkSize = BUFFER_SIZE / 2;  // Size of data chunks
    int numPackets = (messageLen + chunkSize - 1) / chunkSize;  // Ceiling division
    
    Packet packets[MAX_SEQ_NUM];  // Buffer for sent packets
    Packet receivedPacket;        // Buffer for received packets/ACKs
    socklen_t len = addr_len;
    int retries = 0;
    
    // For receiving data (as a receiver)
    int expectedSeqNum = 0;
    char receivedData[65536] = {0};
    int totalDataSize = 0;
    
    printf("Bidirectional communication with piggybacked ACKs\n");
    printf("Sending message of length %d in %d packets\n", messageLen, numPackets);
    
    while (base < numPackets || totalDataSize == 0) {
        // Send new packets within window
        while (nextSeqNum < base + MAX_SEQ_NUM && nextSeqNum < numPackets) {
            // Prepare packet
            initPacket(&packets[nextSeqNum % MAX_SEQ_NUM]);
            packets[nextSeqNum % MAX_SEQ_NUM].seq_num = nextSeqNum;
            
            // Piggyback ACK if we've received data
            if (expectedSeqNum > 0) {
                packets[nextSeqNum % MAX_SEQ_NUM].is_ack = true;
                packets[nextSeqNum % MAX_SEQ_NUM].ack_num = expectedSeqNum - 1;
                printf("Piggybacking ACK %d on data packet %d\n", 
                       expectedSeqNum - 1, nextSeqNum);
            }
            
            // Calculate data size for this packet
            int offset = nextSeqNum * chunkSize;
            packets[nextSeqNum % MAX_SEQ_NUM].data_size = (offset + chunkSize <= messageLen) ? 
                                                         chunkSize : messageLen - offset;
            
            // Copy data
            memcpy(packets[nextSeqNum % MAX_SEQ_NUM].data, 
                   message + offset, 
                   packets[nextSeqNum % MAX_SEQ_NUM].data_size);
            
            // Send packet
            if (sendPacket(sockfd, &packets[nextSeqNum % MAX_SEQ_NUM], addr, addr_len) < 0) {
                perror("Send failed");
            }
            
            nextSeqNum++;
        }
        
        // Receive response (data with piggybacked ACK or just ACK)
        int result = receivePacket(sockfd, &receivedPacket, addr, &len, TIMEOUT_SEC, TIMEOUT_USEC);
        
        if (result > 0) {
            // Check for ACK (piggybacked or not)
            if (receivedPacket.is_ack) {
                if (receivedPacket.ack_num >= base) {
                    printf("Moving window: base %d -> %d\n", base, receivedPacket.ack_num + 1);
                    base = receivedPacket.ack_num + 1;  // Move window
                    retries = 0;  // Reset retry counter
                }
            }
            
            // Check for data
            if (receivedPacket.data_size > 0) {
                // Process as a receiver
                if (receivedPacket.seq_num == expectedSeqNum) {
                    // Expected data packet
                    printf("Received data packet %d\n", expectedSeqNum);
                    
                    // Copy data
                    memcpy(receivedData + totalDataSize, receivedPacket.data, receivedPacket.data_size);
                    totalDataSize += receivedPacket.data_size;
                    
                    expectedSeqNum++;
                    
                    // If we don't have any new data to send, send a pure ACK
                    if (nextSeqNum >= base + MAX_SEQ_NUM || nextSeqNum >= numPackets) {
                        Packet ackPacket;
                        initPacket(&ackPacket);
                        ackPacket.is_ack = true;
                        ackPacket.ack_num = expectedSeqNum - 1;
                        
                        printf("Sending pure ACK %d\n", expectedSeqNum - 1);
                        if (sendPacket(sockfd, &ackPacket, addr, len) < 0) {
                            perror("ACK send failed");
                        }
                    }
                }
            }
        } else {
            // Timeout
            if (base < numPackets) {  // Only if we still have data to send
                retries++;
                if (retries > MAX_RETRIES) {
                    printf("Maximum retries reached.\n");
                    break;
                }
                
                printf("Timeout. Retransmitting unacknowledged packets (%d to %d)\n", 
                      base, nextSeqNum - 1);
                
                // Retransmit all unacknowledged packets
                for (int i = base; i < nextSeqNum; i++) {
                    // Update ACK number if needed
                    if (expectedSeqNum > 0) {
                        packets[i % MAX_SEQ_NUM].is_ack = true;
                        packets[i % MAX_SEQ_NUM].ack_num = expectedSeqNum - 1;
                    }
                    
                    printf("Retransmitting packet %d\n", i);
                    if (sendPacket(sockfd, &packets[i % MAX_SEQ_NUM], addr, len) < 0) {
                        perror("Retransmission failed");
                    }
                }
            } else if (totalDataSize > 0) {
                // We've sent all our data and received some data
                printf("All data sent. Received message: %s\n", receivedData);
                break;
            }
        }
    }
    
    printf("Communication complete.\n");
    if (totalDataSize > 0) {
        printf("Received message: %s\n", receivedData);
    }
}

void receiverPiggybacked(int sockfd, struct sockaddr *addr, socklen_t addr_len) {
    int expectedSeqNum = 0;  // Next expected sequence number
    Packet receivedPacket, sendPacket;
    socklen_t len = addr_len;
    char receivedData[65536] = {0};  // Buffer for received message
    int totalDataSize = 0;
    
    // For sending data (as a sender)
    const char *responseMessage = "This is a response message from the receiver using piggybacked protocol!";
    int base = 0;          // First unacknowledged packet for sending
    int nextSeqNum = 0;    // Next sequence number for sending
    int messageLen = strlen(responseMessage);
    int chunkSize = BUFFER_SIZE / 2;
    int numPackets = (messageLen + chunkSize - 1) / chunkSize;
    Packet packets[MAX_SEQ_NUM];  // Buffer for sent packets
    int retries = 0;
    bool startedSending = false;
    
    printf("Receiver/Sender started (Piggybacked mode)\n");
    printf("Will respond with message of length %d in %d packets\n", messageLen, numPackets);
    
    while (1) {
        // First try to receive
        int result = receivePacket(sockfd, &receivedPacket, addr, &len, 
                                  (startedSending && base < numPackets)
