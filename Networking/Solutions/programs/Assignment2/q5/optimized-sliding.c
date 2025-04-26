#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define M 3                             // number of bits for seq num
#define MAX_SEQ ((1 << M) - 1)          // 2^m - 1
#define TOTAL_FRAMES 15
#define RECEIVER_BUFFER_SIZE 4         // can be 1 or MAX_SEQ

typedef struct {
	int seqNum;
	bool acked;
} Frame;

typedef struct {
	bool ack;
	bool buffer_available; // Framing bit: 1 = buffer has space, 0 = full
	int ackNum;
} ACK;

int receiverBuffer[RECEIVER_BUFFER_SIZE];
int bufferCount = 0;

bool isFrameLost() {
	return (rand() % 100) < 20;  // 20% loss probability
}

ACK receiveFrame(Frame frame) {
	ACK response;
	response.ackNum = frame.seqNum;

	if (isFrameLost()) {
		printf("Receiver: Frame #%d lost\n", frame.seqNum);
		response.ack = false;
		response.buffer_available = bufferCount < RECEIVER_BUFFER_SIZE;
	} else {
		if (bufferCount < RECEIVER_BUFFER_SIZE) {
			receiverBuffer[bufferCount++] = frame.seqNum;
			printf("Receiver: Frame #%d received and buffered (buffer: %d/%d)\n", frame.seqNum, bufferCount, RECEIVER_BUFFER_SIZE);
			response.ack = true;
		} else {
			printf("Receiver: Buffer full. Cannot accept Frame #%d\n", frame.seqNum);
			response.ack = false;
		}
		response.buffer_available = bufferCount < RECEIVER_BUFFER_SIZE;
	}

	return response;
}

void processBuffer() {
	if (bufferCount > 0) {
		printf("Receiver: Processing buffered frame #%d\n", receiverBuffer[0]);
		for (int i = 1; i < bufferCount; i++) {
			receiverBuffer[i - 1] = receiverBuffer[i];
		}
		bufferCount--;
	}
}

void slidingWindowOptimized() {
	printf("\n=== Optimized Sliding Window with Framing Bit ===\n");
	Frame sender[TOTAL_FRAMES];
	bool sent[TOTAL_FRAMES] = { false };
	bool acked[TOTAL_FRAMES] = { false };

	for (int i = 0; i < TOTAL_FRAMES; i++) {
		sender[i].seqNum = i % (MAX_SEQ + 1);
		sender[i].acked = false;
	}

	int base = 0;
	int nextFrame = 0;

	while (base < TOTAL_FRAMES) {
		// Simulate receiver processing frames in background
		if (rand() % 2) processBuffer();  // random process

		// Send frames within window size
		while (nextFrame < base + RECEIVER_BUFFER_SIZE && nextFrame < TOTAL_FRAMES) {
			if (!sent[nextFrame]) {
				printf("Sender: Sending Frame #%d\n", sender[nextFrame].seqNum);
				ACK ack = receiveFrame(sender[nextFrame]);

				if (ack.ack && ack.buffer_available) {
					printf("Sender: ACK received for Frame #%d, buffer available\n", ack.ackNum);
					sender[nextFrame].acked = true;
					sent[nextFrame] = true;
				} else if (!ack.ack && ack.buffer_available) {
					printf("Sender: NACK received, but buffer available. Will retry Frame #%d\n", sender[nextFrame].seqNum);
				} else {
					printf("Sender: Receiver buffer full. Pausing transmission.\n");
					sleep(1);
					break;
				}
			}
			nextFrame++;
		}

		// Slide window
		while (base < TOTAL_FRAMES && sender[base].acked) {
			base++;
		}

		usleep(500000);  // small delay (500ms)
	}
}

int main() {
	srand(time(NULL));

	slidingWindowOptimized();

	return 0;
}

