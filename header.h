#ifndef HEADER_H
#define HEADER_H

#define INV       0x86000000
#define GET_DATA  0x86000001

struct user_data {
  char user_name[50];
  int num_of_seats;
  int time_slot_start;
  int time_slot_end;
  int ref_number;
};

#endif
