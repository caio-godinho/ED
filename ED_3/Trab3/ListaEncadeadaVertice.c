//TAD de lista dinâmicamente encadeada adaptado do Backes

#include <stdio.h>
#include <stdlib.h>
#include "ListaEncadeadaAresta.h"

//Cada vértice é um ponteiro para uma lista contendo suas arestas
typedef struct {
    int grau;                //Quantidade de ligações de um vértice
    int idConecta;
    char siglaPais[3];
    char nomePoPs[100];
    char nomePais[100];
    int cor;//0 branco, 1 cinza, 2 preto
    ListaAresta *arestas;    //Lista encadeada que representa arestas
} Vertice;


//Definicao do tipo lista
typedef struct elemento_vertice{
    Vertice dados;
    struct elemento_vertice *prox;
}ElemVertice;

typedef struct elemento_vertice* ListaVertice;

ListaVertice* cria_lista_vertice(){
    ListaVertice* li = (ListaVertice*) malloc(sizeof(ListaVertice));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista_vertice(ListaVertice* li){
    if(li != NULL){
        ElemVertice* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            libera_lista_aresta(no->dados.arestas);
            free(no);
        }
        free(li);
    }
}

int consulta_lista_pos_vertice(ListaVertice* li, int pos, Vertice *vertice){
    if(li == NULL || pos <= 0)
        return 0;
    ElemVertice *no = *li;
    int i = 1;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;
    }
    if(no == NULL)
        return 0;
    else{
        *vertice = no->dados;
        return 1;
    }
}

int consulta_lista_vertice(ListaVertice* li, int idConecta, Vertice **referencia){
    if(li == NULL)
        return 0;
    ElemVertice *no = *li;
    int i = 0;
    while(no != NULL && no->dados.idConecta != idConecta){
        no = no->prox;
        i++;
    }
    if(no == NULL)
        return -1;
    else{
        //vertice = no->dados;
        *referencia = &no->dados;
        return i;
    }
}

int insere_lista_ordenada_vertice(ListaVertice* li, Vertice vertice, Vertice **referencia){
    if(li == NULL)
        return 0;
    ElemVertice *no = (ElemVertice*) malloc(sizeof(ElemVertice));
    *referencia = &no->dados;
    if(no == NULL)
        return 0;
    no->dados = vertice;

    if((*li) == NULL){//lista vazia: insere in�cio
        no->prox = NULL;
        *li = no;
        return 1;
    }
    else{
        ElemVertice *ant, *atual = *li;
        while(atual != NULL && atual->dados.idConecta < vertice.idConecta){
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

int tamanho_lista_vertice(ListaVertice* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    ElemVertice* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int encontra_ultimo_idConecta(ListaVertice *li) {
    if(li == NULL)
        return 0;
    ElemVertice *no = *li;
    ElemVertice *no_prev = NULL;
    while(no != NULL){
        no_prev = no;
        no = no->prox;
    }
    return no_prev->dados.idConecta;
}

void imprime_lista_vertice(ListaVertice* li){
    if(li == NULL)
        return;
    ElemVertice* no = *li;
    while(no != NULL){
        printf("idConecta: %d   nomePoPs: %s    nomePais: %s    siglaPais: %s   grau: %d\n",no->dados.idConecta, no->dados.nomePoPs, no->dados.nomePais, no->dados.siglaPais, no->dados.grau);
        printf("-------------------------------\n");
        no = no->prox;
    }
}

void copia_lista(ListaVertice *fonte, ListaVertice *copia) {
    ElemVertice *aux = *fonte;
    ElemVertice *aux_copia = *copia;
    Vertice *ref;
    while(aux != NULL) {
        insere_lista_ordenada_vertice(copia, aux->dados, &ref);
        ref->arestas = cria_lista_aresta();
        copia_lista_arestas(aux->dados.arestas, ref->arestas);
        aux = aux->prox;
    }
}

void remove_vertice(ListaVertice *li, int idConecta) {
    if(li == NULL)
        return;

    ElemVertice *aux = *li;

    if((*li)->dados.idConecta == idConecta) {
        aux = aux->prox;
        libera_lista_aresta((*li)->dados.arestas);
        free(*li);
        *li = aux;
        return;
    }

    ElemVertice *aux_prev = NULL;
    while(aux != NULL && aux->dados.idConecta != idConecta) {
        aux_prev = aux;
        aux = aux->prox;
    }

    if(aux == NULL)
        return;
    
    aux_prev->prox = aux->prox;
    libera_lista_aresta(aux->dados.arestas);
    free(aux);
}