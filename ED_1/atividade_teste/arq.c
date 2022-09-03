#include "stdio.h"
#include "stdlib.h"
#include "func.h"

FILE *Arq;
int valor;

int main()
{
    char linha1[256];
    char linha2[256];

    Arq=fopen("arq.txt","rt");//rt == read text
    if (Arq==NULL) { printf("ERRO!\n"); exit(1); }

    fgets(linha1,255,Arq);
    fgets(linha2,255,Arq);

    func(linha1, linha2);

    return 0;
}