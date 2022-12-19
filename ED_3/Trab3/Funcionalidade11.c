#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"
#include "FuncoesComuns.h"

void funcionalidade11() {
  FILE *arquivoEntrada;
  char nomeArqEntrada[100];

  //abre e confere status do arquivo de entrada
  arquivoEntrada = inicializa_arquivo(nomeArqEntrada, "rb");

  //cria grafo com as informações contidas no arquivo de entrada
  Grafo *grafo = arquivo_no_grafo(arquivoEntrada, nomeArqEntrada);

  //imprime grafo
  imprime_grafo(grafo);

  //libera memória alocada para o grafo
  libera_grafo(grafo);

  //fecha arquivo
  fclose(arquivoEntrada);
}