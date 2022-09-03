#include<stdio.h>

int valor;

void func(char str1[], char str2[]){
    scanf("%d",&valor);
    if (valor == 1)
    {
        printf("%s",str1);
    }
    else
    if (valor == 2)
    {
        printf("%s",str2);
    }
    else
        printf("Entrada Invalida\n");
}