#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include "../record_list/user_struct.h" // this way of adding header is temprory fix

#include "sock_functions.h"

// solution to all problem
// just exit printing an error msg ;)
void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}


void sendRecord(int sockfd, struct user_data u) {
  int n = write(sockfd, &u, sizeof(struct user_data));
  if (n < 0)
      error("ERROR writing int to server socket");
}

int recvRecord(int sockfd, struct user_data *u) {
  int n = read(sockfd, u, sizeof(struct user_data));

  // Not what we were expecting. Client likely disconnected.
  if (n < 0 || n != sizeof(struct user_data))
      return -1;

  return 1;
}

int sendInt(int sockfd, int msg) {
  int n = write(sockfd, &msg, sizeof(int));
    if (n < 0)
        error("ERROR sending int to client");
}

int recvInt(int cli_sockfd) {
  int msg = 0;
  int n = read(cli_sockfd, &msg, sizeof(int));

  // Not what we were expecting. Client likely disconnected.
  if (n < 0 || n != sizeof(int))
      return -1;

  return msg;
}

int setupListener(int port_number) {
    int sockfd;
    struct sockaddr_in serv_addr;
    int option = 1;
    // Get a socket to listen on
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    if (sockfd < 0)
        error("ERROR opening listener socket.");

    // Zero out the memory for the server information
    memset(&serv_addr, 0, sizeof(serv_addr));

	  // set up the server info
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port_number);

    // Bind the server info to the listener socket.
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR binding listener socket.");


    listen(sockfd, 5);
    printf("Serving at %s port %d\n", inet_ntoa(serv_addr.sin_addr), port_number);

    // Return the socket number.
    return sockfd;
}

int connectToServer(char *s_addr, int portno) {
  struct sockaddr_in serv_addr;
  struct hostent *server;

  // Get a socket.
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
      error("ERROR opening socket for server.");

  // Get the address of the server.
  server = gethostbyname(s_addr);

  if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
  }

// Zero out memory for server info.
memset(&serv_addr, 0, sizeof(serv_addr));

// Set up the server info.
  serv_addr.sin_family = AF_INET;
  memmove(server->h_addr, &serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(portno);

// Make the connection.
  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
      error("ERROR connecting to server");

  return sockfd;
}
