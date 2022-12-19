#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"
#include "FuncoesComuns.h"

#include "ListaEncadeadaVertice.h"

void funcionalidade14() {
    FILE *arquivoEntrada;
    char nomeArqEntrada[100];

    //abre e confere status do arquivo de entrada
    arquivoEntrada = inicializa_arquivo(nomeArqEntrada, "rb");

    int n;
    scanf("%d", &n);

    //cria grafo com as informações contidas no arquivo de entrada
    Grafo *grafo = arquivo_no_grafo(arquivoEntrada, nomeArqEntrada);

    Vertice origem, destino, parada, *refOrigem, *refDestino, *refParada;
    int idOrigem, idDestino, idParada, menorDistancia;
    for(int i = 0; i < n; i++) {
        scanf("%d %d %d", &idOrigem, &idDestino, &idParada);

        if(consulta_lista_vertice(grafo->vertices, idOrigem, &refOrigem) != -1 && consulta_lista_vertice(grafo->vertices, idParada, &refParada) != -1 && consulta_lista_vertice(grafo->vertices, idDestino, &refDestino) != -1) {
            origem = *refOrigem;
            destino = *refDestino;
            parada = *refParada;
            menorDistancia = busca_menor_caminho(&origem, &parada, *grafo);
            menorDistancia += busca_menor_caminho(&parada, &destino, *grafo);
            printf("Comprimento do caminho entre %d e %d parando em %d: %dMbps\n", idOrigem, idDestino, idParada, menorDistancia);
        } else {
            menorDistancia = -1;
            printf("Comprimento do caminho entre %d e %d parando em %d: %d\n", idOrigem, idDestino, idParada, menorDistancia);
        }

    }

    libera_grafo(grafo);
    fclose(arquivoEntrada);
}