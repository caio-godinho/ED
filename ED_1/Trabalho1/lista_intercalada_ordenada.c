#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"funcoes.h"

int main(int argc, char *argv[]){
    int tipo_listas;
    int n_listas;

    scanf("%d", &tipo_listas);
    if(tipo_listas < 1 || tipo_listas > 3){
        printf("ENTRADA INVALIDA");
         exit(-1);
    }

    scanf("%d", &n_listas);
    if(n_listas != 2 && n_listas != 4){
        printf("ENTRADA INVALIDA");
        exit(-1);
    }
    
    Lista **listas = aloc(n_listas);
    Lista *lista_merge;
    int k;
    
    switch(tipo_listas){
        case 1:
            switch(n_listas){
                case 2:

                    listas = le_listas(listas, n_listas);
                    lista_merge = merge_sort(listas[0], listas[1]);
                    imprime_merge(lista_merge, listas, n_listas);

                    break;
                
                case 4:

                    listas = le_listas(listas, n_listas);
                    Lista *lista_merge1 = merge_sort(listas[0], listas[1]);
                    Lista *lista_merge2 = merge_sort(listas[2], listas[3]);
                    lista_merge = merge_sort(lista_merge1, lista_merge2);
                    imprime_merge(lista_merge, listas, n_listas);

                    destroy_caso4(lista_merge1, lista_merge2);

                    break;
            }
            break;

        case 2:
            switch(n_listas){
                case 2:

                    listas = le_listas(listas, n_listas);
                    listas = ordena_listas(listas, n_listas);
                    lista_merge = merge_sort(listas[0], listas[1]);
                    imprime_merge(lista_merge, listas, n_listas);

                    break;
                
                case 4:

                    listas = le_listas(listas, n_listas);
                    ordena_listas(listas, n_listas);
                    Lista *lista_merge1 = merge_sort(listas[0], listas[1]);
                    Lista *lista_merge2 = merge_sort(listas[2], listas[3]);
                    lista_merge = merge_sort(lista_merge1, lista_merge2);
                    imprime_merge(lista_merge, listas, n_listas);

                    destroy_caso4(lista_merge1, lista_merge2);

                    break;
            }
            break;
        
        case 3:
            switch(n_listas){
                case 2:

                    listas = le_listas(listas, n_listas);
                    ordena_listas(listas, n_listas);
                    lista_merge = merge_sort(listas[0], listas[1]);
                    imprime_merge_inverso(lista_merge, listas, n_listas);

                    break;
                
                case 4:

                    listas = le_listas(listas, n_listas);
                    ordena_listas(listas, n_listas);
                    Lista *lista_merge1 = merge_sort(listas[0], listas[1]);
                    Lista *lista_merge2 = merge_sort(listas[2], listas[3]);
                    lista_merge = merge_sort(lista_merge1, lista_merge2);
                    imprime_merge_inverso(lista_merge, listas, n_listas);

                    destroy_caso4(lista_merge1, lista_merge2);

                    break;
            }
            break;
    }

    for(int i = 0; i < n_listas; i++){
        free(listas[i]->valores);
        free(listas[i]);
    }
    free(listas);
    free(lista_merge->valores);
    free(lista_merge);
    }