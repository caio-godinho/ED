#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//OBS: LETRAS MAIÚSCULAS VEM ANTES DAS MINÚSCULAS NA TABELA ASCII
struct NO{
    char palavra[20];
    int ocorr;
    int altura;
    struct NO *esq;
    struct NO *dir;
};

typedef struct NO* ArvAVL;

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

void RotacaoLL(ArvAVL *A){//LL
    //printf("RotacaoLL\n");
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
    //printf("RotacaoRR\n");
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

int fatorBalanceamento_NO(struct NO* no){
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int insere_ArvAVL_num(ArvAVL *raiz, struct NO *no){
    int res;
    if(*raiz == NULL){//árvore vazia ou nó folha
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;

        strcpy(novo->palavra, no->palavra);
        novo->ocorr = no->ocorr;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    if(no->ocorr <= atual->ocorr){
        if((res = insere_ArvAVL_num(&(atual->esq), no)) == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                if(no->ocorr < (*raiz)->esq->ocorr){
                    RotacaoLL(raiz);
                }else{
                    RotacaoLR(raiz);
                }
            }
        }
    }else{
        if(no->ocorr > atual->ocorr){
            if((res = insere_ArvAVL_num(&(atual->dir), no)) == 1){
                if(fatorBalanceamento_NO(atual) >= 2){
                    if((*raiz)->dir->ocorr < no->ocorr){
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{
            //printf("Valor duplicado!!\n");
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return res;
}

int insere_ArvAVL(ArvAVL *raiz, char palavra[]){//OBS: LETRAS MAIÚSCULAS VEM ANTES DAS MINÚSCULAS NA TABELA ASCII
    int res;
    if(*raiz == NULL){//árvore vazia ou nó folha
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;

        strcpy(novo->palavra, palavra);
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        (*raiz)->ocorr = 0;
        ((*raiz)->ocorr)++;
        return 1;
    }

    struct NO *atual = *raiz;
    if(strcmp(palavra, atual->palavra) < 0){//palavra a ser inserida vem antes na ordem alfabética
        if((res = insere_ArvAVL(&(atual->esq), palavra)) == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                if(strcmp(palavra, (*raiz)->esq->palavra) == -1){
                    RotacaoLL(raiz);
                }else{
                    RotacaoLR(raiz);
                }
            }
        }
    }else{
        if(strcmp(palavra, atual->palavra) > 0){//palavra a ser inserida vem depois na ordem alfabética
            if((res = insere_ArvAVL(&(atual->dir), palavra)) == 1){
                if(fatorBalanceamento_NO(atual) >= 2){
                    if(strcmp(palavra, (*raiz)->dir->palavra) == 1){
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{
            //printf("Valor duplicado!!\n");
            (atual->ocorr)++;
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return res;
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

void preOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("%s - Esq:",(*raiz)->palavra);
        if((*raiz)->esq == NULL) {
            printf(" # ");
        } else {
            printf(" %s ", (*raiz)->esq->palavra);
        }
        printf("- Dir:");
        if((*raiz)->dir == NULL) {
            printf(" #\n");
        } else {
            printf(" %s\n", (*raiz)->dir->palavra);
        }
        preOrdem_ArvAVL(&((*raiz)->esq));
        preOrdem_ArvAVL(&((*raiz)->dir));
    }
}

void emOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvAVL(&((*raiz)->esq));
        printf("No: %s Ocorrencias: %d\n",(*raiz)->palavra, (*raiz)->ocorr);
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
}

void insere_preOrdem_ArvAVL(ArvAVL *raiz, ArvAVL *raiz_arv) {
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        insere_ArvAVL_num(raiz_arv, (*raiz));
        insere_preOrdem_ArvAVL(&((*raiz)->esq), raiz_arv);
        insere_preOrdem_ArvAVL(&((*raiz)->dir), raiz_arv);
    }
}

void preOrdem_ArvAVL_num(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("No: %s Ocorr: %d\n", (*raiz)->palavra, (*raiz)->ocorr);
        preOrdem_ArvAVL_num(&((*raiz)->esq));
        preOrdem_ArvAVL_num(&((*raiz)->dir));
    }
}

void imprime_res(ArvAVL *raiz, int n) {
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        imprime_res(&((*raiz)->dir), n);
        if(((*raiz)->ocorr) >= n) {
            printf("No: %s Ocorr: %d\n", (*raiz)->palavra, (*raiz)->ocorr);
        }
        imprime_res(&((*raiz)->esq), n);
    }
}

void corrige_maiuscula(char palavra[]) {
    if(palavra[0] >= 'A' && palavra[0] <= 'Z') {
        palavra[0] = palavra[0] + 'a' - 'A';
    }
}


//OBS: LETRAS MAIÚSCULAS VEM ANTES DAS MINÚSCULAS NA TABELA ASCII
int main(int argc, char *argv[]) {
    FILE *f = fopen("entrada.txt", "r");
    char palavra[20];
    ArvAVL *raiz = cria_ArvAVL();
    ArvAVL *raiz2 = cria_ArvAVL();

    while(!feof(f)) {
        fscanf(f, "%s", palavra);
        if(strcmp(palavra, ",") != 0 && strcmp(palavra, ".") != 0) {
            corrige_maiuscula(palavra);
            printf("%s ", palavra);
            insere_ArvAVL(raiz, palavra);
        }
    }
    puts("");
    emOrdem_ArvAVL(raiz);
    puts("");
    preOrdem_ArvAVL(raiz);
    puts("");
    int x = altura_NO(*raiz);
    printf("Altura: %d\n", x);
    x = totalNO_ArvAVL(raiz);
    printf("Num de nos: %d\n\n", x);

    insere_preOrdem_ArvAVL(raiz, raiz2);
    preOrdem_ArvAVL_num(raiz2);

    int n;
    scanf("%d", &n);
    imprime_res(raiz2, n);

    free(f);
    libera_ArvAVL(raiz);
    libera_ArvAVL(raiz2);
}