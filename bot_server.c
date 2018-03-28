#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"
#include "storage.h"

int setupListener(int port_number);
void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int recvMsg(int client_fd);
int writeInt(int client_fd, int msg);
int recvData(int client_fd, struct user_data *u);

int main(int argc, char const *argv[]) {
  int server_sockfd = setupListener(strtol(argv[1], NULL, 10));
  struct sockaddr_in address;
  int addrlen = sizeof(address);

  while (1) {
    int client = accept(server_sockfd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    int option = recvMsg(client);

    switch (option) {
      case 1:
        writeInt(client, GET_DATA);
        struct user_data user;
        recvData(client, &user);
        printf("Name: %s\n", user.user_name);
        printf("Seats %d time %d %d\n", user.num_of_seats, user.time_slot_start,
                                                            user.time_slot_end);
        user.ref_number = time(0);
        insertNode(user);
        writeInt(client, user.ref_number);
        break;
      case 2:
        printf("Received 2\n");
        break;
      case 3:
        printf("Recieved 3\n");
        break;
      default:
        printf("Invalid option %d\n", option);
        break;
    }
  }

  return 0;
}

int recvData(int cli_sockfd, struct user_data *u) {
  int n = read(cli_sockfd, u, sizeof(struct user_data));
  if (n < 0 || n != sizeof(struct user_data)) /* Not what we were expecting. Client likely disconnected. */
      return -1;

  return 1;
}

int writeInt(int cli_sockfd, int msg) {
  int n = write(cli_sockfd, &msg, sizeof(int));
    if (n < 0)
        error("ERROR writing int to client socket");
}



int recvMsg(int cli_sockfd) {
  int msg = 0;
  int n = read(cli_sockfd, &msg, sizeof(int));

  if (n < 0 || n != sizeof(int)) /* Not what we were expecting. Client likely disconnected. */
      return -1;

  return msg;
}

int setupListener(int port_number) {
    int sockfd;
    struct sockaddr_in serv_addr;
    int option = 1;
    /* Get a socket to listen on */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    if (sockfd < 0)
        error("ERROR opening listener socket.");

    /* Zero out the memory for the server information */
    memset(&serv_addr, 0, sizeof(serv_addr));

	/* set up the server info */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port_number);

    /* Bind the server info to the listener socket. */
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR binding listener socket.");


    listen(sockfd, 5);
    /* Return the socket number. */
    return sockfd;
}
