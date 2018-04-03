#ifndef LIST_NODE_STRUCT
#define LIST_NODE_STRUCT


//seperated all the struct to make it look clean, I guess!
// this one is the node in the linked list.
struct node {
  struct user_data user;
  struct node *next;
};

#endif
