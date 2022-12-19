#ifndef _GRAFO_
#define _GRAFO_

#include <stdio.h>
#include <stdlib.h>
#include "ListaEncadeadaAresta.h"
#include "ListaEncadeadaVertice.h"
#include "structs.h"

typedef struct {
    int numVertices;
    ListaVertice *vertices;  //lista ordenada encadeada de vértices
} Grafo;

Grafo *cria_grafo();
void libera_grafo(Grafo *grafo);
Grafo *arquivo_no_grafo(FILE *arquivoEntrada, char *nomeArqEntrada);
void imprime_grafo(Grafo *grafo);
int busca_menor_caminho(const Vertice *origem, const Vertice *destino, const Grafo grafo);

#endif