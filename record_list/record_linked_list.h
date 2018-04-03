#ifndef RECORD_LINKED_LIST_H
#define RECORD_LINKED_LIST_H
#include "user_struct.h"
#include "list_node_struct.h"

// this one is for inserting the record in a list whose start is
// defined in the main program.
int insertRecord(struct node **start, struct user_data u);

// this is for deleting record, there still may be a bug inside
// be ware, I failed to find it.
int deleteRecord(struct node **start, int ref_number);

// make sure that this function returns user data struct not the node struct
// and that too a pointer as we don't want to waste memory.
struct user_data* getRecord(struct node *ptr, int ref_number);

// this is undeveloped
// it was supposed to display all record present in the list to debug easily.
// as playing with pointer is very difficult at times.
void debugDisplayAllRecord(struct node *ptr);

// this one is to display simple record given the user object (not the pointer)
// this function may not belong here but I couldn't found the best place.
void displayRecord(struct user_data u);

#endif
