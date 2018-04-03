#ifndef USER_STRUCT_H
#define USER_STRUCT_H

// this one is for storing user data in a node
// no need to allocate dynamically in the node.
struct user_data {
  char name[50];
  int seats;
  int slot_start;
  int slot_end;
  int ref_number;
};

#endif
