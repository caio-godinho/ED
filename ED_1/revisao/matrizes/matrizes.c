#include<stdio.h>
#include<stdlib.h>

int **cria_matriz(int **m){
    m = malloc(2 * sizeof(int *));
    for(int i = 0; i < 2; i++){
        m[i] = malloc(2 * sizeof(int));
        for(int j = 0; j < 2; j++){
            scanf("%d", &m[i][j]);
        }
    }
    return m;
}

void destroi_matriz(int **m){
    for(int i = 0; i < 2; i++){
        free(m[i]);
    }
    free(m);
}

void print_matriz(int **m){
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            printf("%d ", m[i][j]);
        }
        puts("");
    }
}

void soma_matriz(int **m){
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            m[i][j] += 2;
        }
    }
}

int main(int argc, char *argv[]){
    int **matriz = cria_matriz(matriz);
    puts("");
    print_matriz(matriz);
    puts("");
    soma_matriz(matriz);
    print_matriz(matriz);
    destroi_matriz(matriz);
}