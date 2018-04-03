#ifndef SOCK_FUNCTIONS_H
#define SOCK_FUNCTIONS_H

// very harsh function
// it will end up exiting the program.
void error(const char *msg);

// this one is for server as it listens on the given port
int setupListener(int port_number);

// this one is for client to connect to given port on localhost
int connectToServer(int port_number);

// this function is not mature yet
// it sends record struct as whole which won't work between two machines
// this will only work on same machine or localhost
// possible fix is to send each string and int as separate
void sendRecord(int sockfd, struct user_data u);

// same goes with this, sending whole struct is not a good idea.
// need to update this very soon
int recvRecord(int sockfd, struct user_data *u);

// function to recive and return the integer from a given socket.
// on error, it returns -1 (must be handled correctly as 0 can be a data)
int recvInt(int sockfd);

// function to send data to given socket.
// no error code returned as it exits itself printing the error msg
int sendInt(int sockfd, int msg);

/* WARNING
 * these are undeveloped functions
 * possible use is in sending record separately
 * as described above
 */

// this one is designed to recv string from given socket
int recvMsg(int sockfd, char *msg);

// this one is for sending string to given socket
int sendMsg(int sockfd, char msg);


#endif
