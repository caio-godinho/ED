#include<stdio.h>

int main(int argc, char *argv[]){
    FILE *f = fopen("arquivos2.txt", "r");

    char texto[100];
    char nome[50];
    int idade;
    float altura;

    fscanf(f, "%s %s", texto, nome);
    printf("%s %s\n", texto, nome);

    fscanf(f, "%s %d", texto, &idade);
    printf("%s %d\n", texto, idade);

    fscanf(f, "%s %f", texto, &altura);
    printf("%s %.2f\n", texto, altura);
}