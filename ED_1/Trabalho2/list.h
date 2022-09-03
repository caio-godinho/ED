#ifndef _LIST_
#define _LIST_
#include <stdio.h>

typedef struct {
    float X, Y, Z;
    int R, G, B;
    int ID;       // Valor: conteúdo da célula   Valor[lin,col] do tipo int
} Tipo_Dado;

//Definição do tipo lista
struct elemento{
    struct elemento *ant;
    Tipo_Dado dado;
    struct elemento *prox;
};

typedef struct elemento Elem;

typedef struct elemento *Lista;

Lista *cria_lista();

void libera_lista(Lista* li);

void insere_lista_final(Lista* li, Tipo_Dado dt, int *count);

void insere_lista_inicio(Lista *li, Tipo_Dado dt, int *count);

void imprime_lista(Lista* li);

void insere_lista_ordenada(Lista* li, Tipo_Dado dt, char *eixo, int *count);

void procura_lista_X(Elem **ante, Elem **atual, Tipo_Dado dt, int **count);

void procura_lista_Y(Elem **ante, Elem **atual, Tipo_Dado dt, int **count);

void procura_lista_Z(Elem **ante, Elem **atual, Tipo_Dado dt, int **count);

void le_dados(Lista *li, FILE *f, int *count);

Elem *PI_func(Lista *li, int *count);

#endif