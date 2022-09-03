#include "simple_linked_list.h"
#include <stdio.h>

int main(int argc, char *argv[]){
    LinkedList *L = LinkedList_create();

    LinkedList_print(L);
    LinkedList_remove(L, 99);
    LinkedList_print(L);

    LinkedList_add_last(L, 10);
    LinkedList_print(L);
    puts("\nRemovendo 10");
    LinkedList_remove(L, 10);
    LinkedList_print(L);

    LinkedList_add_last(L, 10);
    LinkedList_add_last(L, 2);
    LinkedList_add_last(L, 4);
    LinkedList_print(L);
    puts("\nRemovendo 10");
    LinkedList_remove(L, 10);
    LinkedList_print(L);
    puts("\nRemovendo 2");
    LinkedList_remove(L, 2);
    LinkedList_print(L);
    puts("\nRemovendo 4");
    LinkedList_remove(L, 4);
    LinkedList_print(L);

    LinkedList_add_last(L, 10);
    LinkedList_add_last(L, 2);
    LinkedList_add_last(L, 4);
    LinkedList_add_last(L, 5);
    LinkedList_add_last(L, 7);
    LinkedList_print(L);
    puts("\nRemovendo 2");
    LinkedList_remove(L, 2);
    LinkedList_print(L);
    puts("\nRemovendo 4");
    LinkedList_remove(L, 4);
    LinkedList_print(L);

    puts("\nRemovendo 7");
    LinkedList_remove(L, 7);
    LinkedList_print(L);

    puts("\nRemovendo 99");
    LinkedList_remove(L, 99);
    LinkedList_print(L);

    LinkedList_add_last(L, 4);
    LinkedList_add_last(L, 5);
    LinkedList_add_last(L, 7);
    LinkedList_print(L);
    puts("\nRemovendo 5");
    LinkedList_remove(L, 5);
    LinkedList_print(L);

    LinkedList_add_last(L, 5);
    LinkedList_add_last(L, 4);
    LinkedList_add_last(L, 5);
    LinkedList_add_last(L, 7);
    LinkedList_print(L);
    puts("\nRemovendo 5");
    LinkedList_remove_all(L, 5);
    LinkedList_print(L);
    LinkedList_add_last(L, 4);
    LinkedList_add_last(L, 4);
    LinkedList_add_first(L, 7);
    LinkedList_add_first(L, 7);
    LinkedList_add_last(L, 7);
    LinkedList_add_first(L, 4);
    LinkedList_add_first(L, 7);
    LinkedList_add_first(L, 4);
    LinkedList_add_last(L, 2);
    LinkedList_add_first(L, 2);
    LinkedList_print(L);
    puts("\nRemovendo todos os 99");
    LinkedList_remove_all(L, 99);
    LinkedList_print(L);
    puts("\nRemovendo todos os 4");
    LinkedList_remove_all(L, 4);
    LinkedList_print(L);

    printf("Size = %ld\n",LinkedList_size(L));
    printf("First Val = %d\n",LinkedList_first_val(L));
    printf("Last Val = %d\n",LinkedList_last_val(L));
    printf("Val at index 0 = %d\n", LinkedList_get_val(L, 0));

    LinkedList_destroy(L);
}