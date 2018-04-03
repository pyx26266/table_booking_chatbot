#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <netinet/ip.h>
#include <record_list/record_linked_list.h>
#include <basic_socket_functions/sock_functions.h>
#include "symbols.h"

struct node *start = NULL;

// pseudo random generator (expected),
// currently returns timestamp of 32bit long
// as it is guranteed to return unique value each time.
// NOT taking the consideration of millions of request per sec.
int random_generator();

// just to avoid redundant code this function is used
void handle_client_disconnect(int sockfd);

int main(int argc, char const *argv[]) {
  if (argc < 2)
    error("usage: ./server.out <port number>");

  int server_sockfd = setupListener(strtol(argv[1], NULL, 10));
  if (server_sockfd == ERROR) {
    error("Error creating socket!");
  }

  struct sockaddr_in address;
  int addrlen = sizeof(address);

  // this is my signature nothing special.
  while (TRUE && !FALSE) {
    int client_sockfd = accept(server_sockfd, (struct sockaddr *)&address,
                                                      (socklen_t*)&addrlen);

    printf("\nGot connection from: %s", inet_ntoa(address.sin_addr));
    printf(":%d\n", htons(address.sin_port));

    int option = recvInt(client_sockfd);
    if (option == ERROR) {
      // thought to include continue in the function
      // but continue only works inside loop :|
      handle_client_disconnect(client_sockfd);
      continue;
    }

    // to store new data from client
    struct user_data user;
    // to store pointer of existing data in record list
    struct user_data *user_ptr;

    switch (option) {
      // option 1.
      // to book seats
      case 1:
        sendInt(client_sockfd, GET_DATA);

        if (recvRecord(client_sockfd, &user) == ERROR) {
          handle_client_disconnect(client_sockfd);
          continue;
        }

        user.ref_number = random_generator();
        printf("Recieved Record");
        displayRecord(user);
        insertRecord(&start, user);
        sendInt(client_sockfd, user.ref_number);
        break;

      // option 2.
      // to send record with given ref. number.
      case 2:
        sendInt(client_sockfd, GET_VIEW);

        user.ref_number = recvInt(client_sockfd);
        if (user.ref_number == ERROR) {
          handle_client_disconnect(client_sockfd);
          continue;
        }

        user_ptr = getRecord(start, user.ref_number);
        if (user_ptr == NULL){
          // false sends 0 as a signal that record not exist
          // cause -1 is used for error and positive int for
          // the record to exist.
          sendInt(client_sockfd, FALSE);
          printf("Record not found...\n");
        } else {
          sendInt(client_sockfd, TRUE);
          // it sends the user data not the pointer
          // see clearly, obvious list is only on server side.
          sendRecord(client_sockfd, *user_ptr);
        }
        break;

      //option 3.
      // to delete a record with given ref. number.
      case 3:
        sendInt(client_sockfd, DEL_REC);

        user.ref_number = recvInt(client_sockfd);
        if (user.ref_number == ERROR) {
          handle_client_disconnect(client_sockfd);
          continue;
        }

        // record is sent for a confirmation to delete
        user_ptr = getRecord(start, user.ref_number);
        if (user_ptr == NULL) {
          printf("Nothing to delete...\n");
        } else {
          sendRecord(client_sockfd, *user_ptr);
          // remember, client sends 0 as succcess
          // cause strcmp returns 0 on match.
          int response = recvInt(client_sockfd);
          if (response == ERROR) {
            handle_client_disconnect(client_sockfd);
            continue;
          // thats why we have used !response
          } else if (!response) {
            deleteRecord(&start, user.ref_number);
            printf("Record deleted successfully.\n");
          } else {
            printf("Record not deleted.\n");
          }
        }

        break;
      default:
        printf("Invalid option %d\n", option);
        break;
    }
    // close the connection after each query.
    close(client_sockfd);
  }

  return 0;
}


int random_generator() {
  return time(0);
}

void handle_client_disconnect(int sockfd) {
  printf("Client closed the connection!\n");
  close(sockfd);
}
