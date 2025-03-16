// client side
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
int main() {
  int clientSocketFD;
  struct sockaddr_in serverAddress;
  // create
  clientSocketFD = socket(AF_INET, SOCK_STREAM, 0);
  if (clientSocketFD == -1) {
    printf("socket creation failed 😥, exiting !!!");
    exit(1);
  }
  printf("socket created 👍\n");

  // connect
  bzero(&serverAddress, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
  serverAddress.sin_port = htons(4444);
  if (connect(clientSocketFD, (struct sockaddr *)&serverAddress,
              sizeof(serverAddress)) != 0) {
    printf("connection failed 😥, exiting !!!");
    exit(1);
  }
  printf("connected 😸\n");

  // reading
  char buffer[1000];
  int r = -1;
  int noOfBytes = 0;
  while (r != 0) {
    r = read(clientSocketFD, buffer, sizeof(buffer));
    noOfBytes++;
  }
  printf("%d\n", noOfBytes);

  printf("message recieved %s\n", buffer);
  // close
  close(clientSocketFD);
}
