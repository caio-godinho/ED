#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

typedef struct _snode SNode;

typedef struct _linked_list LinkedList;

SNode *SNode_create(int val);

LinkedList *LinkedList_create();

void LinkedList_add_first(LinkedList *L, int val);

void LinkedList_add_last_slow(LinkedList *L, int val);

void LinkedList_add_last(LinkedList *L, int val);

void LinkedList_remove(LinkedList *L, int val);

void LinkedList_remove_all(LinkedList *L, int val);

void LinkedList_print(const LinkedList *L);

void LinkedList_destroy(LinkedList *L);

size_t LinkedList_size(LinkedList *L);

int LinkedList_first_val(LinkedList *L);

int LinkedList_last_val(LinkedList *L);

int LinkedList_get_val(LinkedList *L, int index);

void LinkedList_empty_check(LinkedList *L);

#endif