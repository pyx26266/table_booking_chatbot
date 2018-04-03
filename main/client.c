/* Author: Aman kumar Sah
 * NIT Durgapur, 20150128
 * Mob: 7864864625
 * Email: amankumar.msjps@gmail.com
 */

// This is client program working on localhost at given port.
// It gives 3 option book, view and delete a record.
// each time input is given it sends it to the server.
// And it closes the connection with each query.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/ip.h>
#include <record_list/record_linked_list.h>
#include <basic_socket_functions/sock_functions.h>
#include "symbols.h"

void displayMenu();

int main(int argc, char const *argv[]) {
  if (argc < 2)
    error("usage: ./client <port number>");
  int server_sockfd;

  while (1) {
    server_sockfd = connectToServer("localhost", strtol(argv[1], NULL, 10));
    displayMenu();

    // also to store status message while receving data.
    int response;

    printf(">>> ");
    scanf(" %d", &response);
    if (response == 4) {
      close(server_sockfd);
      exit(0);
    }

    sendInt(server_sockfd, response);

    response = recvInt(server_sockfd);
    if (response == ERROR)
      error("Server disconnected");

    // to store user data during query
    struct user_data user;

    // main logic block
    switch (response) {

      // get the user data and send it to server.
      case GET_DATA:
        printf("Enter user Name: ");
        // special regex logic to accept line with special chars.
        scanf (" %[^\n]s", user.name);
        printf("Enter number of seats: ");
        // space before '%d' is imp. to avoid skipping problem.
        scanf(" %d", &user.seats);
        printf("enter time slot(start[space]end): ");
        scanf(" %d %d", &user.slot_start, &user.slot_end);

        sendRecord(server_sockfd, user);

        // store the randomly generated integer.
        user.ref_number = recvInt(server_sockfd);
        if (user.ref_number == ERROR)
          error("Server disconnected.");

        printf("Your ref number is: %d\n", user.ref_number);
        break;
      case GET_VIEW:

        // display booking record if exist on server
        printf("Enter ref number: ");
        scanf("%d", &user.ref_number);
        sendInt(server_sockfd, user.ref_number);

        response = recvInt(server_sockfd);
        if (response == ERROR)
          error("Server disconnected.");
        else if (response) {
          recvRecord(server_sockfd, &user);
          displayRecord(user);
        } else {
          printf("Record not found...\n");
        }
        break;

      case DEL_REC:

        // delete the record if it exist on server
        printf("Enter ref num to delete: ");
        scanf(" %d", &user.ref_number);

        sendInt(server_sockfd, user.ref_number);
        response = recvRecord(server_sockfd, &user);

        if (response == ERROR)
          error("Server disconnected");
        if (response) {
          displayRecord(user);
          printf("Are you sure: (yes/No): ");
        } else {
          error("Record not found.");
        }
        char option[4];
        scanf("%s", option);

        // it actually sends 0 as confirmation
        // so must be handled correctly on server side.
        sendInt(server_sockfd, strcmp(option, "yes"));
        break;

    }

    // closing the socket after each query.
    close(server_sockfd);
  }

  return 0;
}



void displayMenu() {
  printf("\nWelcome to the booking system.\n\t1. Book\n\t2. View booking\n\t3. Cancel\n\t4. Exit\n");
}
