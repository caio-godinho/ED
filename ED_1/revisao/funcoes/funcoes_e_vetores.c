#include<stdio.h>
#include<stdlib.h>

void print_vetor(const int *v, int tamanho){//pode ser *v ou v[], tanto faz. //const int *v, pois a funcao apenas imprime.
    for(int i = 0; i < tamanho; i++){
        printf("&v[%d] = %p, v[%d] = %d\n", i, &v[i], i, v[i]);
    }
}


void desaloca_vetor(int *v){
    free(v);
}

int main(int argc, char *argv[]){
    puts("## VETOR ESTÁTICO\n");
    int vetor_s[] = {1,2,3,4,5};

    print_vetor(vetor_s, 5);

    puts("\n## VETOR DINAMICO\n");
    int *vetor_d = (int *) calloc(5, sizeof(int));

    for(int i = 0; i < 5; i++){
        vetor_d[i] = i*100;
    }

    print_vetor(vetor_d, 5);

    desaloca_vetor(vetor_d);

    return 0;
}