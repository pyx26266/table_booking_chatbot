#ifndef STORAGE_H
#define STORAGE_H
#include "header.h"
#include <string.h>
struct node {
  struct user_data user;
  struct node *next;
};

struct node *start = NULL;
struct node *end = NULL;

void insertNode(struct user_data n) {
  struct node *temp = malloc(sizeof(struct node));

  strcpy(temp->user.user_name, n.user_name);
  temp->user.num_of_seats = n.num_of_seats;
  temp->user.time_slot_start = n.time_slot_start;
  temp->user.time_slot_end = n.time_slot_end;
  temp->user.ref_number = n.ref_number;
  temp->next = NULL;

  if (start == NULL) {
    start = end = temp;
  } else {
    temp->next = start;
    start = temp;
  }
}

struct node* getNode(int ref) {
  struct node *ptr = start;
  int found = 0;
  while (ptr) {
    if (ptr->user.ref_number == ref) {
      found = 1;
      break;
    }
    ptr = ptr->next;
  }
  if (found)
    return ptr;
  else
    return NULL;
}

#endif
