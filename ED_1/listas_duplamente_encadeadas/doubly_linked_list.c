#include "doubly_linked_list.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct doubly_node{
    int val;
    struct doubly_node *prev;
    struct doubly_node *next;
} Node;


typedef struct _doubly_linked_list{
    Node *begin;
    Node *end;
    size_t size;
} List;


List *List_create(){
    List *L = (List*) calloc(1, sizeof(List));
    L->begin = NULL;
    L->end = NULL;
    L->size = 0;

    return L;
}


Node *Node_create(int val){
    Node *node = (Node*) calloc(1, sizeof(Node));
    node->val = val;
    node->prev = NULL;
    node->next = NULL;

    return node;
}


void List_destroy(List *L){
    Node *aux = L->begin;
    Node *prev_aux = NULL;

    while(aux != NULL){
        prev_aux = aux;
        aux = aux->next;
        free(prev_aux);
    }
    free(L);
}


bool List_is_empty(const List *L){//retorna 1 se True (for vazia) ou 0 se False (não for vazia)
    return L->size == 0;
}


void List_add_node_first(List *L, int val){
    Node *node = Node_create(val);

    if(List_is_empty(L)){//se lista está vazia
        L->end = node;
    }
    else{//se lista não está vazia
        L->begin->prev = node;
    }
    
    node->next = L->begin;
    L->begin = node;
    L->size++;
}


void List_add_node_last(List *L, int val){
    Node *node = Node_create(val);

    if(List_is_empty(L)){
        L->begin = node;
    }
    else{
        L->end->next = node;
    }

    node->prev = L->end;
    L->end = node;
    L->size++;
}


void My_List_remove(List *L, int val){
    if(!List_is_empty(L)){//se listas não está vazia
        Node *aux_node = L->begin;

        while(aux_node->val != val && aux_node != NULL){
            aux_node = aux_node->next;
        }

        if(aux_node != NULL){
            if(aux_node->prev != NULL){//se houver nó anterior
                aux_node->prev->next = aux_node->next;
            }
            else if(aux_node->next != NULL){//se não houver nó anterior mas houver próximo nó
                aux_node->next->prev = NULL;
            }

            if(aux_node->next != NULL){//se houver próximo nó
                aux_node->next->prev = aux_node->prev;
            }
            else if(aux_node->prev != NULL){//se não houver próximo nó mas houver nó anterior
                aux_node->prev->next = NULL;
            }

            if(L->begin == aux_node){//se nó for o primeiro
                L->begin = aux_node->next;
            }
            if(L->end == aux_node){// se nó for o último
                L->end = aux_node->prev;
            }
            free(aux_node);
            L->size--;
        }
    }
}


void List_remove(List *L, int val){
    if(!List_is_empty(L)){
        Node *aux_node = L->begin;

        if(L->begin->val == val){//se o primeiro elemento deve ser removido
            L->begin = aux_node->next;

            if(L->end == aux_node){//se há apenas 1 elemento
                L->end = NULL;
            }
            else{//se há mais de um elemento
                L->begin->prev = NULL;
            }
            free(aux_node);
            L->size--;
        }
        else{//se o elemento a ser removido está no meio da lista ou é o último
            aux_node = L->begin->next;

            while(aux_node != NULL){
                if(aux_node->val == val){//se achou elemento
                    aux_node->prev->next = aux_node->next;

                    if(L->end == aux_node){//se elemento for o último
                        L->end = aux_node->prev;
                    }
                    else{//se elemento não não for o último
                        aux_node->next->prev = aux_node->prev;
                    }
                    free(aux_node);
                    aux_node = NULL;//faz apontar para NULL para sair do while
                    L->size--;
                }
                else{//se não achou elemento
                    aux_node = aux_node->next;
                }
            }
        }
    }
}


void List_print(List *L){
    Node *aux_node = L->begin;

    printf("L->begin -> ");
    while(aux_node != NULL){
        if(aux_node->next != NULL){
            printf("%d <-> ", aux_node->val);
        }
        else{
            printf("%d -> ", aux_node->val);
        }
        aux_node = aux_node->next;
    }
    puts("NULL");

    if(L->end == NULL){
        puts("L->end = NULL");
    }
    else{
        printf("L->end = %d\n", L->end->val);
    }

    printf("L->size = %ld\n\n", L->size);
}


void List_inverted_print(List *L){
    Node *aux_node =  L->end;

    printf("L->end -> ");
    while(aux_node != NULL){
        if(aux_node->prev != NULL){
            printf("%d <-> ", aux_node->val);
        }
        else{
            printf("%d -> ", aux_node->val);
        }
        aux_node = aux_node->prev;
    }
    puts("NULL");

    if(L->end == NULL){
        puts("L->begin = NULL");
    }
    else{
        printf("L->begin = %d\n", L->begin->val);
    }

    printf("L->size = %ld\n\n", L->size);
}