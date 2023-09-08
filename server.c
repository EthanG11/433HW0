#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
  // Declare variables

  int BIND_ERROR = -10;
  int CREATION_ERROR = -9;
  int LISTEN_ERROR = -8;
  int ACCEPT_ERROR = -7;
  int SEND_ERROR = -6;
  int RECEIVE_ERROR = -5;

  struct sockaddr_in serverDetails;
  serverDetails.sin_family = AF_INET;
  serverDetails.sin_addr.s_addr = inet_addr("172.27.32.226");
  serverDetails.sin_port = htons(2002);

  char buffer[255];
  char server_message[] = "Hello from server";

  int serverAddressLength = sizeof(serverDetails);

  // Create socket

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
  {

    perror("Failed to create socket");
    exit(CREATION_ERROR);
  }

  // Bind to the set port and IP
  if (bind(sockfd, (struct sockaddr *)&serverDetails, serverAddressLength) < 0)
  {
    perror("Failed to bind");
    return BIND_ERROR;
  }
  printf("Done with binding with IP: %s, Port: %d\n", serverDetails.sin_addr.s_addr, 2002);

  // Listen for clients:

  if (listen(sockfd, 10) < 0)
  {
    perror("listen error");
    return LISTEN_ERROR;
  }

  // Accept an incoming connection
  int new_socket = accept(sockfd, (struct sockaddr *)&serverDetails, (socklen_t *)&serverAddressLength);
  if (new_socket < 0)
  {
    perror("accept error");
    return ACCEPT_ERROR;
  }
  printf("Client connected at IP: %s and port: %i\n", "172.27.32.226", 2002);

  // Receive client's message
  if (recv(new_socket, buffer, 255, 0) < 0)
  {
    perror("receive error");
    return RECEIVE_ERROR;
  }
  printf("Msg from client: %s\n", buffer);

  // Respond to client
  if (send(new_socket, server_message, strlen(server_message), 0) < 0)
  {
    perror("send error");
    return SEND_ERROR;
  }

  // strcpy(server_message, "##CHANGE THIS##");

  // Close the socket

  close(sockfd);
  close(new_socket);

  return 0;
}
