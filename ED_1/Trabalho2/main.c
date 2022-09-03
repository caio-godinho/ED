#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *f = fopen("dados3d.txt", "r");
    Lista *li1 = cria_lista();
    Lista *li2 = cria_lista();
    Lista *li3 = cria_lista();
    Lista *li4 = cria_lista();
    Lista *li5 = cria_lista();
    int count1, count2, count3, count4, count5 = 0;

    char entrada[5];
    scanf("%s", entrada);

    Tipo_Dado Dado;

    while(Dado.ID != -1) {
        fscanf(f, "%f %f %f %d %d %d %d", &(Dado.X), &(Dado.Y), &(Dado.Z), &(Dado.R), &(Dado.G), &(Dado.B), &(Dado.ID));
        if(Dado.ID != -1) {
            insere_lista_ordenada(li1, Dado, "X", &count1);
            insere_lista_ordenada(li2, Dado, "Y", &count2);
            insere_lista_ordenada(li3, Dado, "Z", &count3);
            insere_lista_inicio(li4, Dado, &count4);
            insere_lista_final(li5, Dado, &count5);
        }
    }

    if(strcmp(entrada, "LX") == 0) {
        imprime_lista(li1);
    }

    if(strcmp(entrada, "LY") == 0) {
        imprime_lista(li2);
    }

    if(strcmp(entrada, "LZ") == 0) {
        imprime_lista(li3);
    }

    if(strcmp(entrada, "LI") == 0) {
        imprime_lista(li4);
    }

    if(strcmp(entrada, "LF") == 0) {
        imprime_lista(li5);
    }

    if(strcmp(entrada, "TOT") == 0) {
        printf("LX:%d LI:%d LF:%d\n", count1, count4, count5);
    }

    if(strcmp(entrada, "PZ") == 0) {
        printf("%.5f %.5f %.5f TOTAL:1\n", (*li3)->dado.X, (*li3)->dado.Y, (*li3)->dado.Z);
    }

    if(strcmp(entrada, "PI") == 0) {
        int countPI = 0;
        Elem *P = PI_func(li4, &countPI);
        printf("%.5f %.5f %.5f TOTAL:%d\n", P->dado.X, P->dado.Y, P->dado.Z, countPI);
    }

    if(strcmp(entrada, "ID") == 0) {
        int id;
        scanf("%d", &id);

        Elem *no = *li1;
        while(no != NULL) {
            if(no->dado.ID == id) {
                printf("%.5f, %.5f, %.5f, %d, %d, %d, %d\n", no->dado.X, no->dado.Y, no->dado.Z, no->dado.R, no->dado.G, no->dado.B, no->dado.ID);
            }
            no = no->prox;
        }
    }

    if(strcmp(entrada, "CUT") == 0) {
        float maxX, maxY, maxZ, minX, minY, minZ;
        scanf("%f %f %f %f %f %f", &minX, &minY, &minZ, &maxX, &maxY, &maxZ);

        Elem *no = *li1;
        while(no != NULL) {
            if(no->dado.X >= minX && no->dado.X <= maxX && no->dado.Y >= minY && no->dado.Y <= maxY && no->dado.Z >= minZ && no->dado.Z <= maxZ) {
                printf("%.5f, %.5f, %.5f, %d, %d, %d, %d\n", no->dado.X, no->dado.Y, no->dado.Z, no->dado.R, no->dado.G, no->dado.B, no->dado.ID);
            }
            no = no->prox;
        }
    }

    libera_lista(li1);
    libera_lista(li2);
    libera_lista(li3);
    libera_lista(li4);
    libera_lista(li5);
    free(f);

    return 0;
}