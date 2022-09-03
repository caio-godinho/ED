#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct _product{
    float price;
    int serial;
    char name[20];
} Product;


typedef struct ao_node{
    struct ao_node *next;
    struct ao_node *prev;
    int count;
    Product *product;
} Node;


typedef struct ao_list{
    Node *begin;
    Node *end;
    size_t size;
    int total_cost;
} List;


Product *create_product(int serial, char *name, float price){
    Product *product = (Product*) calloc(1, sizeof(Product));
    product->serial = serial;
    product->price = price;
    strcpy(product->name, name);

    return product;
}


void destroy_product(Product *product){
    free(product);
}


void print_product(Product *product){
    printf("%d %s %.2f\n", product->serial, product->name, product->price);
}


Node *create_node(int serial, char *name, float price){
    Node *node = (Node*) calloc(1, sizeof(Node));
    node->next = NULL;
    node->prev = NULL;
    node->count = 0;
    node->product = create_product(serial, name, price);

    return node;
}

void destroy_node(Node *node){
    destroy_product(node->product);
    free(node);
}


List *create_list(){
    List *list = (List*) calloc(1, sizeof(List));
    list->begin = NULL;
    list->end = NULL;
    list->size = 0;
    list->total_cost = 0;

    return list;
}

void destroy_list(List *list){
    Node *aux = list->begin;
    Node *prev_aux = NULL;

    while(aux != NULL){
        prev_aux = aux;
        aux = aux->next;
        destroy_node(prev_aux);
    }
    free(list);
}

bool List_is_empty(List *list){
    return list->size == 0;
}


void List_add_node_last(List *L, int serial, char *name, float price){
    Node *node = create_node(serial, name, price);

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


void List_print(List *L){
    Node *aux_node = L->begin;

    printf("L->begin -> ");
    while(aux_node != NULL){
        printf("%d (%d) -> ", aux_node->product->serial, aux_node->count);
        aux_node = aux_node->next;
    }
    puts("NULL");

    if(L->end == NULL){
        puts("L->end = NULL");
    }
    else{
        printf("L->end = %d (%d)\n", L->end->product->serial, L->end->count);
    }

    printf("L->size = %ld\n\n", L->size);
}


void List_inverted_print(List *L){
    Node *aux_node =  L->end;

    printf("L->end -> ");
    while(aux_node != NULL){
        printf("%d (%d) -> ", aux_node->product->serial, aux_node->count);
        aux_node = aux_node->prev;
    }
    puts("NULL");

    if(L->end == NULL){
        puts("L->begin = NULL");
    }
    else{
        printf("L->end = %d (%d)\n", L->end->product->serial, L->end->count);
    }

    printf("L->size = %ld\n\n", L->size);
}


/*void List_acessa(List *L, int serial){
    if(List_is_empty(L) == 0){
        Node *aux = L->begin;

        while(aux->product->serial != serial){
            aux = aux->next;
            if(aux == NULL){
                puts("NUMERO DE SERIE INVALIDO");
                break;
            }
        }

        if(aux != NULL){
            printf("%d, %s, %.2f\n", aux->product->serial, aux->product->name, aux->product->price);
            aux->count++;
            Lista_organiza(L);
        }
    }
    else{
        puts("A LISTA ESTA VAZIA");
    }
}*/


void List_acessa(List *L, int serial){
    if(!List_is_empty(L)){
        Node *aux = L->begin;
        int cost = 1;

        while(aux != NULL && aux->product->serial != serial){
            cost++;
            aux = aux->next;
        }

        if(aux != NULL){//achou produto com número de série serial
            L->total_cost += cost;
            aux->count++;

            if(L->begin != aux){//se produto não é o primeiro, organiza a lista
                Node *prev_aux = aux->prev;
                while(prev_aux != NULL && prev_aux->count <= aux->count){
                    aux->prev = prev_aux->prev;
                    prev_aux->prev = aux;
                    prev_aux->next = aux->next;
                    aux->next = prev_aux;

                    if(aux->prev == NULL){//se aux é o primeiro da lista
                        L->begin = aux;
                    }
                    else{
                        aux->prev->next = aux;
                    }

                    if(prev_aux->next == NULL){//se prev_aux é o último da lista
                        L->end = prev_aux;
                    }
                    else{
                        prev_aux->next->prev = prev_aux;
                    }

                    prev_aux = aux->prev;
                }
            }
            printf("%d, %s, %.2f\n", aux->product->serial, aux->product->name, aux->product->price);
        }
        else{
            printf("Produto %d inexistente\n", serial);
        }
    }
    else{
        puts("Lista esta vazia!");
    }
}


void List_print_serial(List *L){
    Node *aux = L->begin;

    printf("\nL = (");

    while(aux != NULL){
        if(aux->next == NULL){
            printf("%d)\n", aux->product->serial);
        }
        else{
            printf("%d, ", aux->product->serial);
        }
        aux = aux->next;
    }
    printf("Custo total = %d\n", L->total_cost);
}