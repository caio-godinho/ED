#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "circ_list.h"

typedef struct _circ_node {
    int val;
    struct _circ_node *prev;
    struct _circ_node *next;
} CircNode;

typedef struct _circ_list {
    CircNode *begin;
    CircNode *end;
    size_t size;
} CircList;

CircNode *CircNode_create(int val) {
    CircNode *node = (CircNode*) calloc(1, sizeof(CircNode));
    node->val = val;
    node->next = node;
    node->prev = node;

    return node;
}

void CircNode_destroy(CircNode *node) {
    free(node);
}

CircList *CircList_create() {
    CircList *list = (CircList*) calloc(1, sizeof(CircList));
    list->begin = NULL;
    list->end = NULL;
    list->size = 0;

    return list;
}

void CircList_destroy(CircList *list) {
    CircNode *aux_node = list->begin;
    CircNode *prev_node = NULL;

    for(int i = 0; i < list->size; i++) {
        prev_node = aux_node;
        aux_node = aux_node->next;
        CircNode_destroy(prev_node);
    }
    free(list);
}

bool CircList_is_empty(const CircList *list) {//vazia == 1; !vazia == 0;
    return list->size == 0;
}

void CircList_add_first(CircList *list, int val) {
    CircNode *node = CircNode_create(val);

    if(CircList_is_empty(list)) {
        list->end = node;
    }
    else {
        list->begin->prev = node;
        node->next = list->begin;
        node->prev = list->end;
        list->end->next = node;
    }
    list->begin = node;
    list->size++;
}

void CircList_add_last(CircList *list, int val) {
    CircNode *node = CircNode_create(val);

    if(CircList_is_empty(list)) {
        list->begin = node;
        list->end = node;
    }
    else {
        list->end->next = node;
        list->begin->prev = node;
        node->prev = list->end;
        node->next = list->begin;
    }
    list->end = node;
    list->size++;
}

void CircList_print(CircList *list) {
    if(CircList_is_empty(list)) {
        puts("Lista vazia");
        return;
    }

    CircNode *aux;
    aux = list->begin;
    do {
        printf("%d\n", aux->val);
        aux = aux->next;
    } while(aux != list->begin);

    printf("List->begin = %d\nList->end = %d\n", list->begin->val, list->end->val);
    printf("Size: %ld\n", list->size);
}

void CircList_inverted_print(CircList *list) {
    if(CircList_is_empty(list)) {
        puts("Lista vazia");
        return;
    }
    CircNode *aux;
    aux = list->end;
    do {
        printf("%d\n", aux->val);
        aux = aux->prev;
    } while(aux != list->end);

    printf("Size: %ld\n", list->size);
}

void CircList_remove(CircList *list, int val) {
    if(CircList_is_empty(list)) {
        puts("Lista Vazia");
        return;
    }

    CircNode *node = list->begin;
    if(list->begin->val == val) {//elemento está no começo da lista
        if(list->size == 1) {//só há um nó na lista
            list->begin = NULL;
            list->end = NULL;
        }
        else {//há mais de um nó na lista
            list->begin = node->next;
            list->begin->prev = list->end;
            list->end->next = list->begin;
        }
    }
    else {
        while(node->val != val) {
            node = node->next;
            if(node == list->begin) {//vasculhou lista toda e não encontrou o valor a ser retirado
                puts("Valor não encontrado");
                return;
            }
        }
        if(node == list->end) {//nó está no final da  lista
            list->end = node->prev;
        }
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    CircNode_destroy(node);
    list->size--;
}