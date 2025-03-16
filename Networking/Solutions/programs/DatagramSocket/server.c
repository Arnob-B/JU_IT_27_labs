#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
int main() {
  int serverSockFD, clientSockFD;
  struct sockaddr_in serverAddr, clientAddr;
  socklen_t clientAddrSize;
  // creation
  serverSockFD = socket(AF_INET, SOCK_DGRAM, 0);
  if (serverSockFD == -1) {
    printf("socket creation failed");
    exit(-1);
  }
  printf("socket created\n");
  int port = 4444;
  bzero(&serverAddr, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  // serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons(port);

  if (bind(serverSockFD, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) !=
      0) {
    printf("binding failed");
    exit(1);
  }
  printf("binding succeeded\n");
  while (1) {
    char buffer[100000];
    clientAddrSize = sizeof(clientAddr);
    int strlen = recvfrom(serverSockFD, buffer, sizeof(buffer), 0,
                          (struct sockaddr *)&clientAddr, &clientAddrSize);
    printf("recieved connection\n");
    buffer[strlen] = 0;
    printf("message : %s\n", buffer);
  }

  return 0;
}
