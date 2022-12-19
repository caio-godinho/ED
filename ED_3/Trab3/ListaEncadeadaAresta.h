#ifndef _LISTA_ARESTA_
#define _LISTA_ARESTA_

//Aresta entre dois vértices
typedef struct {
    int peso;               //peso da aresta. Neste caso, é a velocidade de transmissão, que é armazenada em Mbps
    int destino;            //idConecta do vértice de destino
} Aresta;

//Definicao do tipo lista
typedef struct elemento_aresta{
    Aresta dados;
    struct elemento_aresta *prox;
}ElemAresta;

typedef struct elemento_aresta* ListaAresta;

ListaAresta* cria_lista_aresta();

void libera_lista_aresta(ListaAresta* li);

int consulta_lista_pos_aresta(ListaAresta* li, int pos, Aresta *aresta);

int consulta_lista_aresta(ListaAresta* li, int idPoPsConectado, Aresta *aresta);

int insere_lista_ordenada_aresta(ListaAresta* li, Aresta aresta);

int tamanho_lista_aresta(ListaAresta* li);

void imprime_lista_aresta(ListaAresta* li);

void copia_lista_arestas(ListaAresta *fonte, ListaAresta *copia);

#endif