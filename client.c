#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "header.h"
#include "storage.h"

int connectToServer(int port_number);
void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void displayMenu();
void writeServerInt(int sockfd, int msg);
int recvInt(int sockfd);
void sendData(int sockfd, struct user_data u);


int main(int argc, char const *argv[]) {

  int client_sockfd = connectToServer(strtol(argv[1], NULL, 10));


  while (1) {
    displayMenu();
    int response;

    scanf("%d", &response);
    printf("taken input\n");
    writeServerInt(client_sockfd, response);

    response = recvInt(client_sockfd);

    switch (response) {
      case GET_DATA:
        ;
        struct user_data user;

        printf("Enter user Name: ");
        scanf (" %[^\n]s", user.user_name);
        printf("Enter number of seats: ");
        scanf(" %d", &user.num_of_seats);
        printf("enter time slot(start[space]end): ");
        scanf(" %d %d", &user.time_slot_start, &user.time_slot_end);
        sendData(client_sockfd, user);
        user.ref_number = recvInt(client_sockfd);
        printf("Your ref number is: %d\n", user.ref_number);
    }

  }

  return 0;
}

void sendData(int sockfd, struct user_data u) {
  int n = write(sockfd, &u, sizeof(struct user_data));
  if (n < 0)
      error("ERROR writing int to server socket");
}

int recvInt(int sockfd) {
  int msg = 0;
  int n = read(sockfd, &msg, sizeof(int));

  if (n < 0 || n != sizeof(int))
      error("ERROR reading int from server socket");

  return msg;
}

void writeServerInt(int sockfd, int msg) {
  int n = write(sockfd, &msg, sizeof(int));
  if (n < 0)
      error("ERROR writing int to server socket");
}

void displayMenu() {
  printf("welcome to the booking system.\n1. Book\n2. View booking\n3. Cancel\n");
}

int connectToServer(int portno) {
  struct sockaddr_in serv_addr;
  struct hostent *server;

  /* Get a socket. */
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
      error("ERROR opening socket for server.");

  /* Get the address of the server. */
  server = gethostbyname("localhost");

  if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
  }

/* Zero out memory for server info. */
memset(&serv_addr, 0, sizeof(serv_addr));

/* Set up the server info. */
  serv_addr.sin_family = AF_INET;
  memmove(server->h_addr, &serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(portno);

/* Make the connection. */
  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
      error("ERROR connecting to server");

  return sockfd;
}
