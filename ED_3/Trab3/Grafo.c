#include <stdio.h>
#include <stdlib.h>
#include "ListaEncadeadaAresta.h"
#include "ListaEncadeadaVertice.h"
#include "FuncoesComuns.h"
#include "structs.h"

typedef struct {
    int numVertices;
    ListaVertice *vertices;  //lista ordenada encadeada de vértices
} Grafo;


Grafo *cria_grafo() {
    Grafo *grafo = (Grafo*) malloc(sizeof(Grafo));
    grafo->vertices = cria_lista_vertice();
    grafo->numVertices = 0;
    return grafo;
}

void libera_grafo(Grafo *grafo) {
    libera_lista_vertice(grafo->vertices);
    free(grafo);
}


void cria_aresta(Vertice *origem, Vertice *destino, int velocidade, const char unidadeMedida) {
    Aresta arestaAux;

    if(unidadeMedida == 'G')  //converte velocidade para Mbps se estiver em Gbps
        velocidade = velocidade * 1024;

    arestaAux.peso = velocidade;
    arestaAux.destino = destino->idConecta;
    insere_lista_ordenada_aresta(origem->arestas, arestaAux);
    arestaAux.destino = origem->idConecta;
    insere_lista_ordenada_aresta(destino->arestas, arestaAux);

    origem->grau++;
    destino->grau++;
}

void insere_vertice(Grafo *grafo, registro registroAux, const char *nomeArquivo) {
    Vertice *referencia_origem;
    Vertice *referencia_destino;
    int idConecta = registroAux.idConecta;
    int velocidade = registroAux.velocidade;
    int idPoPsConectado = registroAux.idPoPsConectado;
    char unidadeMedida = registroAux.unidadeMedida[0];

    if(consulta_lista_vertice(grafo->vertices, idConecta, &referencia_origem) == -1) {   //se vertice buscado não foi encontrado
        Vertice origem;
        origem.arestas = cria_lista_aresta();
        origem.grau = 0;
        registro_no_vertice(registroAux, &origem); //copia informações do registro para o vértice a ser inserido
        insere_lista_ordenada_vertice(grafo->vertices, origem, &referencia_origem);
        grafo->numVertices++;
    }

    if(consulta_lista_vertice(grafo->vertices, idPoPsConectado, &referencia_destino) == -1) {    //se vertice buscado não foi encontrado
        Vertice destino;
        destino.arestas = cria_lista_aresta();
        destino.grau = 0;
        FILE *arquivoAux = fopen(nomeArquivo, "rb");

        registroAux = busca_registro(arquivoAux, idPoPsConectado);
        registro_no_vertice(registroAux, &destino);
        insere_lista_ordenada_vertice(grafo->vertices, destino, &referencia_destino);

        fclose(arquivoAux);
        grafo->numVertices++;
    }
    //cria aresta
    cria_aresta(referencia_origem, referencia_destino, velocidade, unidadeMedida);
}

Grafo *arquivo_no_grafo(FILE *arquivoEntrada, char *nomeArqEntrada) {
    char c;
    registro registroAux;
    int TAM_registro_atual;
    Grafo *grafo = cria_grafo();

    //pula primeira página de disco
    fseek(arquivoEntrada, TAM_PagDisco, SEEK_SET);

    //loop de inserção
    while(fread(&c, sizeof(char), 1, arquivoEntrada) != 0) {  //enquanto arquivo de entrada não terminar
        fseek(arquivoEntrada, -1, SEEK_CUR);
        le_registro(arquivoEntrada, &registroAux, &TAM_registro_atual);
        if(registroAux.idPoPsConectado != -1 && registroAux.velocidade != -1) //se idPoPsConectado e velocidade forem válidos
            insere_vertice(grafo, registroAux, nomeArqEntrada);
        fseek(arquivoEntrada, TAM_registro-TAM_registro_atual, SEEK_CUR);  //pula para próximo registro
    }

    return grafo;
}

void imprime_grafo(Grafo *grafo) {
    ElemVertice *elem_vertice_aux = *grafo->vertices;
    ElemAresta *elem_aresta_aux;

    while(elem_vertice_aux != NULL) {
        elem_aresta_aux = *elem_vertice_aux->dados.arestas;
        while(elem_aresta_aux != NULL) {
            printf("%d %s %s %s %d %dMbps\n", elem_vertice_aux->dados.idConecta, elem_vertice_aux->dados.nomePoPs, elem_vertice_aux->dados.nomePais, elem_vertice_aux->dados.siglaPais, elem_aresta_aux->dados.destino, elem_aresta_aux->dados.peso);
            elem_aresta_aux = elem_aresta_aux->prox;
        }
        elem_vertice_aux = elem_vertice_aux->prox;
    }
}


void inicializa_distancia(unsigned long int *distancia, const Grafo grafo, const Vertice *origem) {
    Vertice *ref;
    for(int i = 0; i < grafo.numVertices; i++)
        distancia[i] = 9999999;
    
    int posicaoVertice = consulta_lista_vertice(grafo.vertices, origem->idConecta, &ref); //Encontra a posicao do vertice (no caso o vertice origem) na lista de vertices
    distancia[posicaoVertice] = 0;  //Distância do vértice de origem até ele mesmo é 0
    ElemAresta *aresta_aux = *origem->arestas;

    //coloca pesos das arestas da origem na lista de distâncias
    while(aresta_aux != NULL) {
        posicaoVertice = consulta_lista_vertice(grafo.vertices, aresta_aux->dados.destino, &ref);
        distancia[posicaoVertice] = aresta_aux->dados.peso;
        aresta_aux = aresta_aux->prox;
    }
}

int encontra_menor_distancia(unsigned long int *distancia, ListaVertice *verticesNaoAnalisados, ListaVertice *vertices)  {
    int posicao_relativa_menor = 0; //Posição relativa (na lista de vértices) do vértice com a menor distância
    int menor_distancia = 9999999; 
    int posicao_relativa;
    int idConecta_menor;
    int idConecta;
    Vertice *ref;
    ElemVertice *aux = *verticesNaoAnalisados;
    
    //Encontra o vértice ainda não analisado e com a menor distância até ele
    while(aux != NULL)  {
        idConecta = aux->dados.idConecta;
        posicao_relativa = consulta_lista_vertice(vertices, idConecta, &ref);
        if(menor_distancia > distancia[posicao_relativa]) {
            menor_distancia = distancia[posicao_relativa];
            posicao_relativa_menor = posicao_relativa;
            idConecta_menor = aux->dados.idConecta;
        }
        aux = aux->prox;
    }
    remove_vertice(verticesNaoAnalisados, idConecta_menor);
    return posicao_relativa_menor;
}

ElemVertice *encontra_vertice(int posicao_relativa, const ListaVertice *vertices) {
    ElemVertice *aux = *vertices;
    for(int i = 0 ; i < posicao_relativa; i++) {
        aux = aux->prox;
    }
    return aux;
}

int busca_menor_caminho(const Vertice *origem, const Vertice *destino, const Grafo grafo) {
    Vertice *ref;
    Vertice *atual;
    unsigned long int distancia[grafo.numVertices];  //Lista que conterá as menores distâncias até cada vértice 
    ListaVertice *verticesNaoAnalisados = cria_lista_vertice(); //Lista que guarda os vértices cujas arestas ainda não foram analisadas pelo algoritmo
    
    copia_lista(grafo.vertices, verticesNaoAnalisados);
    inicializa_distancia(distancia, grafo, origem); //Coloca pesos das arestas do vertice origem na lista de distâncias
    remove_vertice(verticesNaoAnalisados, origem->idConecta); //Retira o vértice de origem da lista
    int posicao_relativa; //Posição relativa do vértice sendo analisado
    int posicao_relativa_adjacente; //Posição relativa do vértice adjacente sendo analisado
    ElemVertice *vertice_aux; //Lista que guardará as arestas do vertice sendo analisado
    ElemAresta *aresta_aux;

    for(int i = 0; i < grafo.numVertices-1; i++) {
        //Encontra próximo vértice a ser analisado
        posicao_relativa = encontra_menor_distancia(distancia, verticesNaoAnalisados, grafo.vertices);
        vertice_aux = encontra_vertice(posicao_relativa, grafo.vertices);
        aresta_aux = *vertice_aux->dados.arestas;

        //Atualiza distâncias
        while(aresta_aux != NULL) {
            posicao_relativa_adjacente = consulta_lista_vertice(grafo.vertices, aresta_aux->dados.destino, &ref);
            if(distancia[posicao_relativa_adjacente] > (distancia[posicao_relativa] + aresta_aux->dados.peso))
                distancia[posicao_relativa_adjacente] = distancia[posicao_relativa] + aresta_aux->dados.peso;

            aresta_aux = aresta_aux->prox;
        }
    }

    int posicao_destino = consulta_lista_vertice(grafo.vertices, destino->idConecta, &ref);
    int resultado = distancia[posicao_destino];

    libera_lista_vertice(verticesNaoAnalisados);

    return resultado;
}