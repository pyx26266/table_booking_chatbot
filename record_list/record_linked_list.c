#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "record_linked_list.h"



int insertRecord(struct node **start, struct user_data n) {
  struct node *temp = malloc(sizeof(struct node));

  strcpy(temp->user.name, n.name);
  temp->user.seats = n.seats;
  temp->user.slot_start = n.slot_start;
  temp->user.slot_end = n.slot_end;
  temp->user.ref_number = n.ref_number;
  temp->next = NULL;

  if (*start == NULL) {
    *start = temp;
  } else {
    // Insert at the beginning of the list.
    temp->next = *start;
    *start = temp;
  }
}

int deleteRecord(struct node **start, int ref_number) {
  struct node *current = *start,
              *prev = *start;

  while (current) {

    if (current->user.ref_number == ref_number) {
      if (*start == current) { // For single node case
        *start = NULL;
      }
      prev->next = current->next;
      free(current);
      break;
    } else {
      prev = current;
      current = current->next;
    }
  }

}

void displayRecord(struct user_data u) {
  printf("\nName: %s\n", u.name);
  printf("Seats %d time %d to %d\n", u.seats, u.slot_start,
                                                  u.slot_end);
  printf("Reference num: %d\n", u.ref_number);
}

struct user_data* getRecord(struct node *ptr, int ref_number) {
  int found = 0;
  while (ptr) {
    if (ptr->user.ref_number == ref_number) {
      found = 1;
      break;
    }
    ptr = ptr->next;
  }
  if (found)
    return &(ptr->user);
  else
    return NULL;
}
