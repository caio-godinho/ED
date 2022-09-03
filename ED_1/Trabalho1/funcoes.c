#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _lista{
    char tipo[10];
    int tamanho;
    float *valores;
} Lista;


Lista **aloc(int n){
    Lista **p = (Lista **) calloc(n, sizeof(Lista *));

    for(int i = 0; i < n; i++){
        p[i] = (Lista *) calloc(1, sizeof(Lista));
        p[i]->valores = (float *) calloc(1024, sizeof(float));
       
        for(int j = 0; j < 1024; j++){
            p[i]->valores[j] = -1;//colocando os valores da lista iguais a -1, pois a lista acaba com 0.
        }
    }

    return p;
}


Lista **le_listas(Lista **p, int n){
    int j = -1;

    for(int i = 0; i < n; i++){
        do{
            j++;
            scanf("%f", &p[i]->valores[j]);
        }while(p[i]->valores[j] != 0);

        p[i]->tamanho = j;
        j = -1;
    }

    for(int i = 0; i < n; i++){
        do{
            j++;
            if(p[i]->valores[j] != (int)p[i]->valores[j]){
                strcpy(p[i]->tipo, "float");
            }
        }while(p[i]->valores[j] != 0);

        j = -1;
    }

    return p;
}


Lista **ordena_listas(Lista **p, int n){
    float menor;
    float aux;
    float *endereco_aux;
    int j;

    for(int i = 0; i < n; i++){
        j = 0;
        while(j != p[i]->tamanho){
            endereco_aux = NULL;
            menor = p[i]->valores[j];
            for(int k = 0; (k + j) < p[i]->tamanho; k++){
                if(menor > p[i]->valores[k + j]){
                    menor = p[i]->valores[k + j];
                    endereco_aux = &(p[i]->valores[k + j]);
                }
            }
            aux = p[i]->valores[j];
            p[i]->valores[j] = menor;
            if(endereco_aux != NULL){
                *endereco_aux = aux;
            }
            j++;
        }
    }

    return p;
}


Lista *merge_sort(Lista *l1, Lista *l2){
    Lista *lista_merge = calloc(1, sizeof(Lista));
    lista_merge->valores = realloc(lista_merge->valores, 1024 * 2 * sizeof(float));//alocando espaço para juntar 2 listas, cada uma com espaço para 1024 floats.
    
    int size = (l1->tamanho) + (l2->tamanho);
    lista_merge->tamanho = size;

    int contA = 0; 
    int contB = 0;
    int contC = 0;
    
    while(contC != size){
        if(l1->valores[contA] <= l2->valores[contB] && contA != l1->tamanho || (contB == l2->tamanho)){
            lista_merge->valores[contC] = l1->valores[contA];
            contA++;
        }else{
            lista_merge->valores[contC] = l2->valores[contB];
            contB++;
        }
        contC++;
    }
    
    lista_merge->valores[contC + 1] = 0;
    return lista_merge;
}


void imprime_merge(Lista *merge, Lista **p, int n){
    int k = 0;
    int x = 0;

    for(int i = 0; i < n; i++){//conferindo se há um float nas listas.
        if(strcmp(p[i]->tipo, "float") == 0){
            x = 1;
            break;
        }
    }

        if(x == 1){
            while(merge->valores[k] != 0){
                printf("%.1f ", merge->valores[k]);
                k++;
            }

        } else {
            while(merge->valores[k] != 0){
                printf("%d ", (int)merge->valores[k]);
                k++;
            }
        }
    
    puts("");
}


void imprime_merge_inverso(Lista *merge, Lista **p, int n){
    int k = merge->tamanho;
    int x = 0;

    for(int i = 0; i < n; i++){//conferindo se há um float nas listas.
        if(strcmp(p[i]->tipo, "float") == 0){
            x = 1;
            break;
        }
    }

        if(x == 1){
            while(k != 0){
                k--;//decrementa primeiro para não imprimir o zero.
                printf("%.1f ", merge->valores[k]);
                
            }

        } else {
            while(k != 0){
                k--;
                printf("%d ", (int)merge->valores[k]);
            }
        }
    
    puts("");
}


void destroy_caso4(Lista *l1, Lista *l2){
    free(l1);
    free(l2);
}