#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
   // Declare Variables
   int CONNECTION_ERROR = -2;
   int SEND_ERROR = -3;
   int RECEIVE_ERROR = -4;

   char client_message[255];
   char server_message[255];

   struct sockaddr_in serverDetails;
   serverDetails.sin_family = AF_INET;
   serverDetails.sin_addr.s_addr = inet_addr("172.27.32.226");
   serverDetails.sin_port = htons(2002);

   // Create socket:

   int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

   // Send connection request to server, be sure to set port and IP the same as server-side
   if (connect(clientSocket, (struct sockaddr *)&serverDetails, sizeof(serverDetails)) < 0)
   {
      perror("connection error");
      exit(CONNECTION_ERROR);
   }
   // Get input from the user:
   memset(client_message, 0, 255);
   printf("Enter message sent to the server: ");
   fgets(client_message, 255, stdin);

   // Send the message to server:
   if (send(clientSocket, client_message, strlen(client_message), 0) < 0)
   {
      perror("send error");
      exit(SEND_ERROR);
   }

   // Receive the server's response:

   if (recv(clientSocket, server_message, 255, 0) < 0)
   {
      perror("recieve error");
      exit(RECEIVE_ERROR);
   }

   printf("Server's response: %s\n", server_message);

   // Close the socket:

   close(clientSocket);

   return 0;
}
