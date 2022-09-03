#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circuito.h"

struct NO{
    char nome[10];
    struct NO *esq;
    struct NO *dir;
    int valor;
};

ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada nó
    free(raiz);//libera a raiz
}

struct NO *procura_pai(ArvBin *raiz, char pai[], struct NO *no_pai) {
    if(raiz == NULL || (*raiz) == NULL || no_pai != NULL) {
        return no_pai;
    }
    if(strcmp(pai, (*raiz)->nome) == 0) {
        no_pai = *raiz;
        return *raiz;
    }
    no_pai = procura_pai(&(*raiz)->esq, pai, no_pai);
    if(no_pai != NULL) {
        return no_pai;
    }
    no_pai = procura_pai(&(*raiz)->dir, pai, no_pai);
    if(no_pai != NULL) {
        return no_pai;
    }
}

void acha_sigla(ArvBin *raiz, char *sigla) {
    for(int i = 0; i < 3; i++) {
        sigla[i] = (*raiz)->nome[i];
    }
}

void confere_folhas(ArvBin *raiz) {
    if(raiz == NULL || (*raiz) == NULL) {
        return;
    }
    if((*raiz)->esq == NULL && (*raiz)->dir == NULL) {
        char sigla[5];
        acha_sigla(raiz, sigla);
        if(strcmp(sigla, "INP") != 0) {
            printf("CIRCUIT ERROR\n");
            exit(0);
        }
    }
    confere_folhas(&(*raiz)->esq);
    confere_folhas(&(*raiz)->dir);
}

int insere_ArvBin(ArvBin* raiz, char pai[], char lado[], char filho[]){
    if(raiz == NULL)
        return 0;
    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL)
        return 0;
    strcpy(novo->nome, filho);
    novo->dir = NULL;
    novo->esq = NULL;

    if(*raiz == NULL)
        *raiz = novo;
    else{
        struct NO* no_pai = NULL;
        no_pai = procura_pai(raiz, pai, no_pai);

        if(no_pai == NULL) {
            printf("CIRCUIT ERROR\n");
            exit(0);
        }
        if(strcmp(lado, "L") == 0 || strcmp(lado, "U") == 0) {
            if(no_pai->esq != NULL) {
                printf("CIRCUIT ERROR\n");
                exit(0);
            }
            no_pai->esq = novo;
        } 
        else {
            if(no_pai->dir != NULL) {
                printf("CIRCUIT ERROR\n");
                exit(0);
            }
            no_pai->dir = novo;
        }
    }
    return 1;
}

void preOrdem_ArvAVL(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("No: %s  Valor: %d\n",(*raiz)->nome, (*raiz)->valor);
        preOrdem_ArvAVL(&((*raiz)->esq));
        preOrdem_ArvAVL(&((*raiz)->dir));
    }
}

void insere_valor_INP(ArvBin *raiz, int valor, char no[], int flag) {
    if(raiz == NULL || *raiz == NULL || flag == 1) {
        return;
    }
    if(strcmp(no, (*raiz)->nome) == 0) {
        (*raiz)->valor = valor;
        flag = 1;
        return;
    }
    insere_valor_INP(&((*raiz)->esq), valor, no, flag);
    insere_valor_INP(&((*raiz)->dir), valor, no, flag);
}

void insere_valor_NOT(ArvBin *raiz, int flag) {
    if(raiz == NULL || *raiz == NULL || flag == 2) {
        return;
    }
    char sigla[5];
    acha_sigla(raiz, sigla);
    if(strcmp(sigla, "NOT") == 0) {
        if((*raiz)->esq->valor == 1) {
            (*raiz)->valor = 0;
        } else {
            (*raiz)->valor = 1;
        }
        flag++;
        return;
    }
    insere_valor_NOT(&((*raiz)->esq), flag);
    insere_valor_NOT(&((*raiz)->dir), flag);
}

void insere_valor_AND(ArvBin *raiz, int flag) {
    if(raiz == NULL || *raiz == NULL || flag == 2) {
        return;
    }
    char sigla[5];
    acha_sigla(raiz, sigla);
    if(strcmp(sigla, "AND") == 0) {
        if((*raiz)->esq->valor == 0 || (*raiz)->dir->valor == 0) {
            (*raiz)->valor = 0;
        } else {
            (*raiz)->valor = 1;
        }
        flag++;
        return;
    }
    insere_valor_AND(&((*raiz)->esq), flag);
    insere_valor_AND(&((*raiz)->dir), flag);
}

void insere_valor_OR(ArvBin *raiz, int flag) {
    if(raiz == NULL || *raiz == NULL || flag == 1) {
        return;
    }
    char sigla[5];
    acha_sigla(raiz, sigla);
    if(strcmp(sigla, "OR-") == 0) {
        if((*raiz)->esq->valor == 0 && (*raiz)->dir->valor == 0) {
            (*raiz)->valor = 0;
        } else {
            (*raiz)->valor = 1;
        }
        flag++;
        return;
    }
    insere_valor_OR(&((*raiz)->esq), flag);
    insere_valor_OR(&((*raiz)->dir), flag);
}

void insere_valor_OUTPUT(ArvBin *raiz) {
    (*raiz)->valor = (*raiz)->esq->valor;
}

void imprime_saida(ArvBin *raiz) {
    printf("%d\n", (*raiz)->valor);
}