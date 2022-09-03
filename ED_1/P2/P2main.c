//Aluno: Caio Oliveira Godinho  NUSP: 12731996
//Ambiente e Compilador: Ubuntu 20.04 gcc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "P2main.h"

struct NO{
    char cidade[30];
    char estado[5];
    long int CEPI;
    long int CEPF;
    int altura;
    struct NO *esq;
    struct NO *dir;
};

ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
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

void libera_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada nó
    free(raiz);//libera a raiz
}

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

int altura_NO(struct NO* no){
    if(no == NULL)
        return -1;
    else
        return no->altura;
}

int totalNO_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_ArvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

int fatorBalanceamento_NO(struct NO* no){
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

void RotacaoLL(ArvAVL *A){//LL
    if(A != NULL && (*A)->esq != NULL) {
        struct NO *B;
        B = (*A)->esq;
        (*A)->esq = B->dir;
        B->dir = *A;
        (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
        B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
        *A = B;
    }
}

void RotacaoRR(ArvAVL *A){//RR
    if(A != NULL && (*A)->dir != NULL) {
        struct NO *B;
        B = (*A)->dir;
        (*A)->dir = B->esq;
        B->esq = (*A);
        (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
        B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
        (*A) = B;
    }
}

void RotacaoLR(ArvAVL *A){//LR
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(ArvAVL *A){//RL
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

int insere_ArvAVL(ArvAVL *raiz, long int CEPI, long int CEPF, char cidade[], char estado[]){
    int res;
    if(*raiz == NULL){//árvore vazia ou nó folha
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;

        novo->CEPI = CEPI;
        novo->CEPF = CEPF;
        strcpy(novo->cidade, cidade);
        strcpy(novo->estado, estado);
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    if(CEPI == atual->CEPI && CEPF == atual->CEPF) {
        printf("ERROR\n");
        return 0;
    }
    if(CEPI <= atual->CEPI){
        if((res = insere_ArvAVL(&(atual->esq), CEPI,  CEPF, cidade, estado)) == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                if(CEPI < (*raiz)->esq->CEPI){
                    RotacaoLL(raiz);
                }else{
                    RotacaoLR(raiz);
                }
            }
        }
    }else{
        if(CEPI > atual->CEPI){
            if((res = insere_ArvAVL(&(atual->dir), CEPI,  CEPF, cidade, estado)) == 1){
                if(fatorBalanceamento_NO(atual) >= 2){
                    if((*raiz)->dir->CEPI < CEPI){
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }
                }
            }
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return res;
}

int altura_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvAVL(&((*raiz)->esq));
    int alt_dir = altura_ArvAVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

void procura_CEP(ArvAVL *raiz, long int CEP) {
    if(raiz == NULL || (*raiz) == NULL) {
        return;
    }
    if(CEP > (*raiz)->CEPI && CEP < (*raiz)->CEPF || CEP == (*raiz)->CEPI || CEP == (*raiz)->CEPF) {
        printf("%ld %ld %s %s\n", (*raiz)->CEPI, (*raiz)->CEPF, (*raiz)->cidade, (*raiz)->estado);
        exit(0);
    }
    if(CEP < (*raiz)->CEPI) {
        procura_CEP(&((*raiz)->esq), CEP);
    }
    else if(CEP > (*raiz)->CEPF) {
        procura_CEP(&((*raiz)->dir), CEP);
    }
}

void procura_CEP_inicio(ArvAVL *raiz, long int CEP) {
    if(raiz == NULL || (*raiz) == NULL) {
        return;
    }
    procura_CEP(raiz, CEP);
    printf("FAIL\n");
}

void preOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("%ld %ld %s %s\n", (*raiz)->CEPI, (*raiz)->CEPF, (*raiz)->cidade, (*raiz)->estado);
        preOrdem_ArvAVL(&((*raiz)->esq));
        preOrdem_ArvAVL(&((*raiz)->dir));
    }
}

void emOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvAVL(&((*raiz)->esq));
        printf("%ld %ld %s %s\n", (*raiz)->CEPI, (*raiz)->CEPF, (*raiz)->cidade, (*raiz)->estado);
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
}

int main(int argc, char *argv[]) {
    char cidade[30];
    char estado[5];
    long int CEPI = -1;
    long int CEPF = -1;
    FILE *f = fopen("cepdata.txt", "r");
    ArvAVL *raiz = cria_ArvAVL();

    fscanf(f, "%ld %ld %s %s", &CEPI, &CEPF, cidade, estado);
    while(CEPI != 0 && CEPF != 0) {
        insere_ArvAVL(raiz, CEPI, CEPF, cidade, estado);
        fscanf(f, "%ld %ld %s %s", &CEPI, &CEPF, cidade, estado);
    }

    int x;
    long int CEP;
    scanf("%d", &x);

    switch (x) {
        case 1:
            printf("%d\n", totalNO_ArvAVL(raiz));
            break;

        case 2:
            printf("%d\n", altura_ArvAVL(raiz));
            break;

        case 3:
            scanf("%ld", &CEP);
            procura_CEP_inicio(raiz, CEP);
            break;
        
        case 4:
            preOrdem_ArvAVL(raiz);
            break;
        case 5:
            emOrdem_ArvAVL(raiz);
            break;

        default:
            break;
    }

    libera_ArvAVL(raiz);
    free(f);
}