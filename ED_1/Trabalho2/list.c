#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

Lista *cria_lista() {
    Lista *li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL) {
        *li = NULL;
    }
    return li;
}


void libera_lista(Lista *li) {
    if (li != NULL) {
        Elem *no;
        while ((*li) != NULL) {
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}


void insere_lista_final(Lista* li, Tipo_Dado dt, int *count) {
    Elem *no;

    if (li == NULL) {
        fprintf(stderr, "ERRO 32");
        exit(-1);
    }

    no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) {
        fprintf(stderr, "ERRO 36");
        exit(-1);
    }

    no->dado = dt;
    no->prox = NULL;
    (*count)++;

	if ((*li) == NULL) {   //lista vazia: insere início
        no->ant = NULL;
        *li = no;
    } else {
        Elem *aux;
        aux = *li;
        while (aux->prox != NULL) {
            aux = aux->prox;
            (*count)++;
        }
        aux->prox = no;
        no->ant = aux;
        (*count)++;
    }
}


void insere_lista_inicio(Lista *li, Tipo_Dado dt, int *count) {
    if (li == NULL) {
        fprintf(stderr, "ERRO 65");
    }

    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) {
        fprintf(stderr, "ERRO 72");
    }

    no->dado = dt;
    no->prox = (*li);
    no->ant = NULL;

	if (*li != NULL) { //lista não vazia: apontar para o anterior!
        (*li)->ant = no;
    }

    *li = no;
    (*count)++;
}


void procura_lista_X(Elem **ante, Elem **atual, Tipo_Dado dt, int **count){
    while ((*atual) != NULL && (*atual)->dado.X <= dt.X) {  // Ordena pelo eixo
        if(((*atual)->dado.X == dt.X && (*atual)->dado.Y > dt.Y) || ((*atual)->dado.X == dt.X && (*atual)->dado.Y == dt.Y && (*atual)->dado.Z > dt.Z)){
            break;
        }
        (*ante) = (*atual);
        (*atual) = (*atual)->prox;
        (**count)++;
    }
}


void procura_lista_Y(Elem **ante, Elem **atual, Tipo_Dado dt, int **count){
    while ((*atual) != NULL && (*atual)->dado.Y <= dt.Y) {  // Ordena pelo eixo
        if(((*atual)->dado.Y == dt.Y && (*atual)->dado.X > dt.X) || ((*atual)->dado.Y == dt.Y && (*atual)->dado.X == dt.X && (*atual)->dado.Z > dt.Z)){
            break;
        }
        (*ante) = (*atual);
        (*atual) = (*atual)->prox;
        (**count)++;
    }
}


void procura_lista_Z(Elem **ante, Elem **atual, Tipo_Dado dt, int **count){
    while ((*atual) != NULL && (*atual)->dado.Z <= dt.Z) {  // Ordena pelo eixo
        if(((*atual)->dado.Z == dt.Z && (*atual)->dado.X > dt.X) || ((*atual)->dado.Z == dt.Z && (*atual)->dado.X == dt.X && (*atual)->dado.Y > dt.Y)){
            break;
        }
        (*ante) = (*atual);
        (*atual) = (*atual)->prox;
        (**count)++;
    }
}


void insere_lista_ordenada(Lista* li, Tipo_Dado dt, char *eixo, int *count) {
    if (li == NULL) {
        fprintf(stderr, "ERRO 100");
    }

    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) {
        fprintf(stderr, "ERRO 105");
    }
    no->dado = dt;
    (*count)++;
    if ((*li) == NULL) {  //lista vazia: insere início
        no->prox = NULL;
        no->ant = NULL;
        *li = no;
    } else {
        Elem *ante, *atual = *li;

        if(strcmp(eixo, "X") == 0) {
            procura_lista_X(&ante, &atual, dt, &count);
        }

        if(strcmp(eixo, "Y") == 0) {
            procura_lista_Y(&ante, &atual, dt, &count);
        }

        if(strcmp(eixo, "Z") == 0) {
            procura_lista_Z(&ante, &atual, dt, &count);
        }
    
        if (atual == *li) {   //insere início
            no->ant = NULL;
            (*li)->ant = no;
            no->prox = (*li);
            *li = no;
        } else {
            no->prox = ante->prox;
            no->ant = ante;
            ante->prox = no;
            if (atual != NULL)
                atual->ant = no;
        }
    }
}


void imprime_lista(Lista *li) {
    Elem *no = *li;

    if (li == NULL) {
        return;
    }

    while (no != NULL) {
        printf("%.5f, %.5f, %.5f, %d, %d, %d, %d\n", no->dado.X, no->dado.Y, no->dado.Z, no->dado.R, no->dado.G, no->dado.B, no->dado.ID);
        no = no->prox;
    }
}


Elem *PI_func(Lista *li, int *count) {
    Elem *aux = *li;
    (*count)++;
    Elem *menor;
    menor->dado.Z = (*li)->dado.Z;

    while(aux->prox != NULL) {
        if(menor->dado.Z > aux->dado.Z) {
            menor = aux;
        }
        aux = aux->prox;
        (*count)++;
    }

    return menor;
}