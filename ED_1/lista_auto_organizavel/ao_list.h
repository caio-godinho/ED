#ifndef AO_LIST
#define AO_LIST

#include <stdbool.h>

typedef struct ao_node Node;

typedef struct ao_list List;

typedef struct _product Product;

List *create_list();

void destroy_list(List *list);

Product *create_product(int serial, char *name, float price);

void destroy_product(Product *product);

void print_product(Product *product);

Node *create_node(int serial, char *name, float price);

void destroy_node(Node *node);

void List_add_node_last(List *L, int serial, char *name, float price);

void List_print(List *L);

bool List_is_empty(List *list);

void List_inverted_print(List *L);

//void List_acessa(List *L, int serial);

void List_acessa(List *L, int serial);

void List_print_serial(List *L);

#endif