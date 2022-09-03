#include<stdio.h>
#include<stdlib.h>

int **create_matrix(int nrows, int ncols){
    int **m = (int **) calloc(nrows, sizeof(int *));
    if(m == NULL){
        puts("deu ruim");
        exit(-1);
    }
    for(int i = 0; i < nrows; i++){
        m[i] = (int *) calloc(ncols, sizeof(int));
        if(m[i] == NULL){
            puts("deu ruim");
            exit(-1);
        }
    }

    return m;
}

void atribuir_valores(int **m, int nrows, int ncols){
    int count = 0;
    for(int i = 0; i < nrows; i++){
        for(int j = 0; j < ncols; j++){
            m[i][j] = count++;
        }
    }
}

void print_matrix(const int **m, int nrows, int ncols){
    for(int i = 0; i < nrows; i++){
        for(int j = 0; j < ncols; j++){
            printf("%2d ", m[i][j]);
        }
        puts("");
    }
}

void destroy_matrix(int **m, int nrows){
    for(int i = 0; i < nrows; i++){
        free(m[i]);
    }

    free(m);
}

int main(int argc, char *argv[]){
    if(argc != 3){//se o número de argumentos for menor que 3...
        printf("ERRO\nEntrada deve ser: %s nrows ncols\n", argv[0]);//argv[0] sempre é o comando ./(nome do executável)
        exit(-1);
    }

    int nrows = atoi(argv[1]);
    int ncols = atoi(argv[2]);
    
    printf("nrows == %d  ncols == %d\n", nrows, ncols);

    int **m = create_matrix(nrows, ncols);
    print_matrix((const int **) m, nrows, ncols);//adicionou-se uma "máscara" ao m, para que ele seja considerado "const".
    puts("");
    atribuir_valores(m, nrows, ncols);
    print_matrix((const int **) m, nrows, ncols);
    destroy_matrix(m, nrows);
}