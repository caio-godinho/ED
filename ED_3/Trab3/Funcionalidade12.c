#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grafo.h"
#include "FuncoesComuns.h"
#include "structs.h"
#include "ListaEncadeadaVertice.h"
#include "ListaEncadeadaAresta.h"


//retorna vertice conectado que foi buscado
ElemVertice *encontra_vertice_buscado(ListaVertice* li, int idConecta){
  if(li == NULL){
    return 0;
  }
  
  ElemVertice *no = *li;
  
  while(no != NULL && no->dados.idConecta != idConecta){
    no = no->prox;
  }
  return no;  
}


void conta_ciclos(ElemVertice *vertices, ElemAresta *arestas, Grafo *grafo, int *contador){
  arestas = *vertices->dados.arestas;

  //enquanto tiver elementos na aresta, busca os vertices conectados
  while(arestas != NULL){
    ElemVertice *vertice_buscado = encontra_vertice_buscado(grafo->vertices, arestas->dados.destino);

    //vertice preto, encontrou ciclo
    if(vertice_buscado->dados.cor == 2){
      (*contador)++;
    }

    //vertice ja foi visitado
    if(vertice_buscado->dados.cor != 0){
      arestas = arestas->prox;
      continue;
    }
    
    //vertice branco, chama a função novamente com o vertice buscado
    vertices->dados.cor = 1;//vertice visitado fica cinza
    conta_ciclos(vertice_buscado, arestas, grafo, contador);
    arestas = arestas->prox;
  }
  vertices->dados.cor = 2;//todos os vertices conectados ja foram buscados, fica preto
}


void funcionalidade12() {
  FILE *arquivoEntrada;
  char nomeArqEntrada[100];
  int contador = 0;

  //abre e confere status do arquivo de entrada
  arquivoEntrada = inicializa_arquivo(nomeArqEntrada, "rb");

  //cria grafo com as informações contidas no arquivo de entrada
  Grafo *grafo = arquivo_no_grafo(arquivoEntrada, nomeArqEntrada);

  ElemVertice *vertice = *grafo->vertices;
  ElemAresta *aresta;

  //faz contagem da quantidade de ciclos simples no grafo
  conta_ciclos(vertice, aresta, grafo, &contador);
  printf("Quantidade de ciclos: %d", contador);
  
  //fecha arquivo
  libera_grafo(grafo);
  fclose(arquivoEntrada);
}