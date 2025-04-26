// client side
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h> // exit , bzero
#include <strings.h>
#include <sys/socket.h> // socket, sockaddr_in
#include <unistd.h>     // close
int main() {
  printf("----socket server ----\n");
  int serverSocketFD, clientSocketFD;
  struct sockaddr_in serverAddress, clientAddress;
  socklen_t clientAddressLength;
  serverSocketFD =
      socket(AF_INET, SOCK_STREAM, 0); // constants defined in  sys/socket.h
  if (serverSocketFD == -1) {
    printf("socket creation failed 😥, exiting !!!");
    exit(1);
  }
  printf("socket created 👍\n");

  // bind
  bzero(&serverAddress, sizeof(serverAddress)); // strings.h
  serverAddress.sin_family = AF_INET;
  // serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);                // htonl
  // , INADDR_ANY -> arpa/inet.h
  serverAddress.sin_addr.s_addr =
      inet_addr("127.0.0.1");           // htonl , INADDR_ANY -> arpa/inet.h
  serverAddress.sin_port = htons(4444); // htons -> arpa/inet.h
  if (bind(serverSocketFD, (struct sockaddr *)&serverAddress,
           sizeof(serverAddress)) != 0) {
    printf("socket binding failed 😥, exiting !!!");
    exit(1);
  }
  printf("socket bound 👍\n");

  // listen
  if (listen(serverSocketFD, 1) != 0) {
    printf("socket listening failed 😥, exiting !!!");
    exit(1);
  }
  printf("socket listening 👍\n");
  // accepting
  bzero(&clientAddress, sizeof(clientAddress));
  clientSocketFD = accept(serverSocketFD, (struct sockaddr *)&clientAddress,
                          &clientAddressLength);
  if (clientSocketFD == -1) {
    printf("accepting client failed 😥, exiting !!!");
    exit(1);
  }
  printf("client accepted 😸\n");

  // write
  char buffer[] = "welcome home 󰮧";
  write(clientSocketFD, buffer, sizeof(buffer));

  // close connection  -> unistd.h
  close(clientSocketFD);
  close(serverSocketFD);
}
