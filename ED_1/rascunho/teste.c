#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int dados[2];
} Lista;

void lista(Lista l) {
    l.dados[0] = l.dados[1] = 1;
    //printf("%d %d\n", l.dados[0], l.dados[1]);
}

int main(int argc, char *argv[]){
    Lista l;
    //l.dados = malloc(sizeof(int) * 2);
    l.dados[0] = l.dados[1] = 0;
    printf("%d %d\n", l.dados[0], l.dados[1]);
    lista(l);
    printf("%d %d\n", l.dados[0], l.dados[1]);
}