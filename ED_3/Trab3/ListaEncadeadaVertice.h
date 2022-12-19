#ifndef _LISTA_VERTICES_
#define _LISTA_VERTICES_

#include "ListaEncadeadaAresta.h"

//Cada vértice é um ponteiro para uma lista contendo suas arestas
typedef struct {
    int grau;                //Quantidade de ligações de um vértice
    int idConecta;
    char siglaPais[3];
    char nomePoPs[100];
    char nomePais[100];
    int cor; //0 branco, 1 cinza, 2 preto
    ListaAresta *arestas;    //Lista encadeada que representa arestas
} Vertice;

//Definicao do tipo lista
typedef struct elemento_vertice{
    Vertice dados;
    struct elemento_vertice *prox;
}ElemVertice;

typedef struct elemento_vertice* ListaVertice;

ListaVertice* cria_lista_vertice();
void libera_lista_vertice(ListaVertice* li);
int consulta_lista_pos_vertice(ListaVertice* li, int pos, Vertice *vertice);
int consulta_lista_vertice(ListaVertice* li, int idConecta, Vertice **vertice);
int insere_lista_ordenada_vertice(ListaVertice* li, Vertice vertice, Vertice **referencia);
int tamanho_lista_vertice(ListaVertice* li);
int encontra_ultimo_idConecta(ListaVertice *li);
void imprime_lista_vertice(ListaVertice* li);
void copia_lista(ListaVertice *fonte, ListaVertice *copia);
void remove_vertice(ListaVertice *li, int idConecta);

#endif