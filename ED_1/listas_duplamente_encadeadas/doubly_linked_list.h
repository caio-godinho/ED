#ifndef _DOUBLY_LINKED_LIST_H_
#define _DOUBLY_LINKED_LIST_H_

#include <stdbool.h>

typedef struct _doubly_linked_list List;

typedef struct doubly_node Node;

List *List_create();

Node *Node_create(int val);

void List_destroy(List *list);

void List_add_node_first(List *L, int val);

void List_add_node_last(List *L, int val);

void My_List_remove(List *L, int val);

void List_remove(List *L, int val);

void List_print(List *L);

void List_inverted_print(List *L);

bool List_is_empty(const List *L);

#endif