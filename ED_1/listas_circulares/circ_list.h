#ifndef CIRC_LIST_H
#define CIRC_LIST_H

#include<stdbool.h>

typedef struct _circ_node CircNode;
typedef struct _circ_list CircList;
CircNode *CircNode_create(int val);
void CircNode_destroy(CircNode *node);
CircList *CircList_create();
void CircList_destroy(CircList *list);
bool CircList_is_empty(const CircList *list);
void CircList_add_first(CircList *list, int val);
void CircList_add_last(CircList *list, int val);
void CircList_print(CircList *list);
void CircList_inverted_print(CircList *list);
void CircList_remove(CircList *list, int val);

#endif