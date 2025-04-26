#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TOTAL_FRAMES 10
#define WINDOW_SIZE 4
#define LOSS_PROBABILITY 20  // % chance a frame is "lost"

typedef struct {
    int seqNum;
    bool acked;
} Frame;

// Simulate frame loss
bool isFrameLost() {
    return (rand() % 100) < LOSS_PROBABILITY;
}

// Send a frame
void sendFrame(Frame* frame) {
    printf("Sending Frame #%d", frame->seqNum);
    if (isFrameLost()) {
        printf(" -> [LOST]\n");
    } else {
        printf(" -> [SENT]\n");
    }
}

// Receive a frame
void receiveFrame(Frame* frame, bool received[], bool sendNACK) {
    if (!isFrameLost()) {
        received[frame->seqNum] = true;
        printf("Received Frame #%d\n", frame->seqNum);
    } else {
        if (sendNACK)
            printf("Frame #%d lost. Sending NACK.\n", frame->seqNum);
        else
            printf("Frame #%d lost. Will wait for timeout.\n", frame->seqNum);
    }
}

// Non-NACK based Selective Repeat
void selectiveRepeatNonNACK() {
    printf("\n=== Selective Repeat - Non-NACK Based ===\n");
    Frame sender[TOTAL_FRAMES];
    bool received[TOTAL_FRAMES] = { false };

    for (int i = 0; i < TOTAL_FRAMES; ++i) {
        sender[i].seqNum = i;
        sender[i].acked = false;
    }

    int base = 0;
    while (base < TOTAL_FRAMES) {
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; ++i) {
            if (!sender[i].acked) {
                sendFrame(&sender[i]);
                receiveFrame(&sender[i], received, false);
                if (received[i]) {
                    sender[i].acked = true;
                    printf("ACK received for Frame #%d\n", i);
                } else {
                    printf("Timeout. Retransmitting Frame #%d later.\n", i);
                }
            }
        }
        // Slide the window
        while (base < TOTAL_FRAMES && sender[base].acked) base++;
    }
}

// NACK-based Selective Repeat
void selectiveRepeatNACK() {
    printf("\n=== Selective Repeat - NACK Based ===\n");
    Frame sender[TOTAL_FRAMES];
    bool received[TOTAL_FRAMES] = { false };

    for (int i = 0; i < TOTAL_FRAMES; ++i) {
        sender[i].seqNum = i;
        sender[i].acked = false;
    }

    int base = 0;
    while (base < TOTAL_FRAMES) {
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; ++i) {
            if (!sender[i].acked) {
                sendFrame(&sender[i]);
                receiveFrame(&sender[i], received, true);
                if (received[i]) {
                    sender[i].acked = true;
                    printf("ACK received for Frame #%d\n", i);
                } else {
                    printf("Retransmitting Frame #%d due to NACK.\n", i);
                    sendFrame(&sender[i]);
                    receiveFrame(&sender[i], received, true);
                    if (received[i]) {
                        sender[i].acked = true;
                        printf("ACK received for Frame #%d\n", i);
                    }
                }
            }
        }
        while (base < TOTAL_FRAMES && sender[base].acked) base++;
    }
}

// Piggybacked ACK version
void selectiveRepeatPiggybacked() {
    printf("\n=== Selective Repeat - Piggybacked ACK ===\n");
    Frame sender[TOTAL_FRAMES];
    bool received[TOTAL_FRAMES] = { false };
    bool piggybackedACKs[TOTAL_FRAMES] = { false };

    for (int i = 0; i < TOTAL_FRAMES; ++i) {
        sender[i].seqNum = i;
        sender[i].acked = false;
    }

    int base = 0;
    while (base < TOTAL_FRAMES) {
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; ++i) {
            if (!sender[i].acked) {
                sendFrame(&sender[i]);
                receiveFrame(&sender[i], received, false);
                if (received[i]) {
                    piggybackedACKs[i] = true;
                }
            }
        }

        // Simulate piggybacked ACKs
        for (int i = 0; i < TOTAL_FRAMES; ++i) {
            if (piggybackedACKs[i] && !sender[i].acked) {
                sender[i].acked = true;
                printf("Received piggybacked ACK for Frame #%d\n", i);
            }
        }

        while (base < TOTAL_FRAMES && sender[base].acked) base++;
    }
}

int main() {
    srand(time(NULL));

    selectiveRepeatNonNACK();
    selectiveRepeatNACK();
    selectiveRepeatPiggybacked();

    return 0;
}

