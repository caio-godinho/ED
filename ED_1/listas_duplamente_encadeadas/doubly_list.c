#include "doubly_linked_list.h"
#include <stdio.h>

int main(int argc, char *argv[]){
    List *L = List_create();
    
    List_print(L);
    List_remove(L, 7);
    List_print(L);
    List_add_node_last(L, 4);
    List_print(L);
    List_add_node_last(L, 7);
    List_add_node_first(L, 2);
    List_add_node_first(L, 10);
    
    List_print(L);

    List_remove(L, 7);
    List_add_node_last(L, 5);
    List_print(L);
    List_remove(L, 2);
    List_add_node_first(L, 8);
    List_print(L);
    List_remove(L, 4);
    List_print(L);
    List_remove(L, 10);
    List_print(L);
    List_inverted_print(L);
    List_add_node_first(L, 10);
    List_print(L);
    List_add_node_last(L, 11);
    List_print(L);
    List_inverted_print(L);
    List_remove(L, 8);
    List_print(L);
    List_remove(L, 10);
    List_print(L);
    List_inverted_print(L);
    List_remove(L, 11);
    List_print(L);
    List_inverted_print(L);
    List_remove(L, 5);
    List_print(L);
    List_inverted_print(L);

    List_destroy(L);
    return 0;
}