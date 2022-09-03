#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _linha{
    char prefixo[10];
    char palavra[20];
    int num;
} Linha;


Linha **cria_lista(Linha **p);


Linha **le_arquivo(Linha **p, FILE *file, int *n);


void copia_prefixo(Linha *p1, Linha *p2);


void copia_palavra(Linha *p1, Linha *p2);


void copia_num(Linha *p1, Linha *p2);

Linha **organiza(Linha **p, int n);


void imprime(Linha **p, char entrada[], int n);