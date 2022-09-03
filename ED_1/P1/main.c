//Nome: Caio Oliveira Godinho   NUSP: 12731996   Curso: Engenharia de Computação.
//Utilizei Linux, Ubuntu 20.04 LTS, compilador gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _linha{
    char prefixo[10];
    char palavra[20];
    int num;
} Linha;


Linha **cria_lista(Linha **p){
    p = (Linha **) calloc(50, sizeof(Linha *));
    for(int i = 0; i < 50; i++){
        p[i] = (Linha *) calloc(1, sizeof(Linha));
    }

    return p;
}


Linha **le_arquivo(Linha **p, FILE *file, int *n){
    int i = 0;

    while(!feof(file)){
        fscanf(file, "%s %s %d", p[i]->prefixo, p[i]->palavra, &(p[i]->num));
        i++;
        (*n)++;
    }

    return p;
}


void copia_prefixo(Linha *p1, Linha *p2){
    strcpy(p1->prefixo, p2->prefixo);
}


void copia_palavra(Linha *p1, Linha *p2){
    strcpy(p1->palavra, p2->palavra);
}


void copia_num(Linha *p1, Linha *p2){
        p1->num = p2->num;
}

Linha **organiza_numeros(Linha **p, int n){
    int maior;
    Linha **aux = cria_lista(aux);
    int j;

    for(int i = 0; i < n; i++){
        aux[0]->num = 0;
        aux[1]->num = 0;
        maior = p[i]->num;
        for(int j = i; j < n; j++){
            if(maior < p[j]->num){
                maior = p[j]->num;
                
                copia_prefixo(aux[0], p[j]);
                copia_palavra(aux[0], p[j]);
                copia_num(aux[0], p[j]);

                copia_prefixo(aux[1], p[i]);
                copia_palavra(aux[1], p[i]);
                copia_num(aux[1], p[i]);

                if(aux[0]->num != 0){
                    copia_prefixo(p[i], aux[0]);
                    copia_palavra(p[i], aux[0]);
                    copia_num(p[i], aux[0]);
                    copia_prefixo(p[j], aux[1]);
                    copia_palavra(p[j], aux[1]);
                    copia_num(p[j], aux[1]);
                }
            }
        }
    }

    for(int i = 0; i < 50; i++){
        free(aux[i]);
    }
    free(aux);
    
    return p;
}


Linha **organiza_ordem_alfebetica(Linha **p, int n){
    int menor;
    Linha **aux = cria_lista(aux);
    int j;

    for(int i = 0; i < n; i++){
        aux[0]->num = 0;
        aux[1]->num = 0;
        menor = p[i]->palavra[0];
        for(int j = i; j < n; j++){
            if(menor > p[j]->palavra[0]){
                menor = p[j]->palavra[0];
                
                copia_prefixo(aux[0], p[j]);
                copia_palavra(aux[0], p[j]);
                copia_num(aux[0], p[j]);

                copia_prefixo(aux[1], p[i]);
                copia_palavra(aux[1], p[i]);
                copia_num(aux[1], p[i]);

                if(aux[0]->num != 0){
                    copia_prefixo(p[i], aux[0]);
                    copia_palavra(p[i], aux[0]);
                    copia_num(p[i], aux[0]);
                    copia_prefixo(p[j], aux[1]);
                    copia_palavra(p[j], aux[1]);
                    copia_num(p[j], aux[1]);
                }
            }
        }
    }

    for(int i = 0; i < 50; i++){
        free(aux[i]);
    }
    free(aux);
    
    return p;
}


void imprime(Linha **p, char entrada[], int n){
    int count = 0;

    for(int i = 0; i < n; i++){
        if(strcmp(p[i]->prefixo, entrada) == 0){//linhas estao organizadas por valor, então é só imprimir os 3 primeiros que aparecerem.
            printf("%s %d\n", p[i]->palavra, p[i]->num);
            count++;
            if(count == 3){
                break;
            }
        }
    }
}


int main(int argc, char *argv[]){
    FILE *f = fopen("arq.txt", "r");

    char entrada[10];

    scanf("%s", entrada);

    int num_linhas = 0;

    Linha **linhas = cria_lista(linhas);
    linhas = le_arquivo(linhas, f, &num_linhas);
    linhas = organiza_numeros(linhas, num_linhas);
    linhas = organiza_ordem_alfebetica(linhas, num_linhas);
    /*for(int i = 0; i < 15; i++){
        printf("%s %s %d\n", linhas[i]->prefixo, linhas[i]->palavra, linhas[i]->num);
    }*/
    imprime(linhas, entrada, num_linhas);

    for(int i = 0; i < 50; i++){
        free(linhas[i]);
    }
    free(linhas);
    fclose(f);
}