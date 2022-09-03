#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circuito.h"

int main(int argc, char *argv[]) {
    FILE *f = fopen("circuit.txt", "r");

    char pai[10];
    char filho[10];
    char lado[3];
    ArvBin *raiz = cria_ArvBin();

    while(!feof(f)) {
        fscanf(f, "%s", filho);
        if(strcmp(filho, "$END00") == 0) {
            break;
        }
        fscanf(f, "%s", lado);
        fscanf(f, "%s", pai);

        insere_ArvBin(raiz, pai, lado, filho);
    }

    confere_folhas(raiz); 

    char no[20];
    int valor;
    int flag = 0;
    for(int i = 0; i < 4; i++) {
        scanf("%s %d", no, &valor);
        insere_valor_INP(raiz, valor, no, flag);
    }
    insere_valor_NOT(raiz, flag);
    insere_valor_AND(raiz, flag);
    insere_valor_OR(raiz, flag);
    insere_valor_OUTPUT(raiz);
    imprime_saida(raiz);

    libera_ArvBin(raiz);
    free(f);

    return 0;
}