#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: %s <server_ip> <port>\n", argv[0]);
    exit(1);
  }
  int sockFD;
  struct sockaddr_in serverAddr;
  // creation
  sockFD = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockFD == -1) {
    printf("socket creation failed");
    exit(-1);
  }

  printf("socket created\n");
  int port = atoi(argv[2]);
  bzero(&serverAddr, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
  serverAddr.sin_port = htons(port);

  char buffer[100000] = "hello from client";
  socklen_t serverAddrSize;
  serverAddrSize = sizeof(serverAddr);
  int bytesSend = sendto(sockFD, buffer, strlen(buffer), 0,
                         (struct sockaddr *)&serverAddr, serverAddrSize);
  if (bytesSend == -1) {
    printf("did not send msg");
    exit(1);
  }
  printf("message sent");

  return 0;
}
