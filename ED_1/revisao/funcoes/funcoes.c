#include<stdio.h>

void troca(int *x, int *y){
    int aux = *x;
    *x = *y;
    *y = aux;
}

int main(int argc, char *argv[]){
    int a = 10;
    int b = 20;

    troca(&a, &b);

    printf("%d %d\n", a, b);
}