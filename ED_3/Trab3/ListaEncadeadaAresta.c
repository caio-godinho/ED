#include <stdio.h>
#include <stdlib.h>

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

ListaAresta* cria_lista_aresta(){
    ListaAresta* li = (ListaAresta*) malloc(sizeof(ListaAresta));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista_aresta(ListaAresta* li){
    if(li != NULL){
        ElemAresta* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int consulta_lista_pos_aresta(ListaAresta* li, int pos, Aresta *aresta){
    if(li == NULL || pos <= 0)
        return 0;
    ElemAresta *no = *li;
    int i = 1;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;
    }
    if(no == NULL)
        return 0;
    else{
        *aresta = no->dados;
        return 1;
    }
}

int consulta_lista_aresta(ListaAresta* li, int destino, Aresta *aresta){
    if(li == NULL)
        return 0;
    ElemAresta *no = *li;
    int i = 0;
    while(no != NULL && no->dados.destino != destino){
        no = no->prox;
        i++;
    }
    if(no == NULL)
        return -1;
    else{
        *aresta = no->dados;
        return i;
    }
}

int insere_lista_ordenada_aresta(ListaAresta* li, Aresta aresta){
    if(li == NULL)
        return 0;
    ElemAresta *no = (ElemAresta*) malloc(sizeof(ElemAresta));
    if(no == NULL)
        return 0;
    no->dados = aresta;
    if((*li) == NULL){//lista vazia: insere in�cio
        no->prox = NULL;
        *li = no;
        return 1;
    }
    else{
        ElemAresta *ant, *atual = *li;
        while(atual != NULL && atual->dados.destino < aresta.destino){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){//insere in�cio
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

int tamanho_lista_aresta(ListaAresta* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    ElemAresta* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

void imprime_lista_aresta(ListaAresta* li){
    if(li == NULL)
        return;
    ElemAresta* no = *li;
    while(no != NULL){
        printf("peso: %d  destino: %d\n", no->dados.peso, no->dados.destino);
        printf("-------------------------------\n");
        no = no->prox;
    }
}

void copia_lista_arestas(ListaAresta *fonte, ListaAresta *copia) {
    ElemAresta *aux = *fonte;
    while(aux != NULL) {
        insere_lista_ordenada_aresta(copia, aux->dados);
        aux = aux->prox;
    }
}