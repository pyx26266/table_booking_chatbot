# ChatBot for Table booking
## Overview

> A chatbot program which can be used for booking and cancellation of tables in a restaurant.
If the user wants to book a table, then bot must ask
  A. user's name
  B. number of seats
  C. time slot
Then assign a booking reference number.
For cancellation, the bot will ask for the reference number and check if that number exist in its record list.
Then it should display user’s name, the number of seats and time slot (which the user gave as inputs while booking),
and ask him/her to confirm the cancellation. Implemented using C (Unix) Socket programming,
with the user as client and server as chatbot.

## Short Description:

#### Server,
  <p>
  As a chatbot, which communicates to client using some predefined codes as
  command. it can add, delete, and transfer record.
  It uses a dynamic link list to store user data in RAM only.
  File storage module can be possible update.
  </p>

#### Client,
  <p>
  As a user client, displays menu, takes input, sends it to server.
  get status and data from server coordinated using some hex constants
  as commands.
  Also to run successfully on diffrent machines the data transfer between
  server and client should be done in basic string and integer transfer
  instead of the struct type.
  </p>

To Run,
  ```bash
mkdir build
cd build
cmake ..
make

$ ./main/ChatBot 6005
$ ./main/client 6005
  ```
