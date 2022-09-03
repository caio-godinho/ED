#include<stdio.h>
#include<stdlib.h>
#include"float_vector.h"//compilar: gcc -c (nome do arquivo).c  
//precisa do -c pois não é um programa em si, apenas um arquivo com várias funcões.

struct FloatVector{
    int capacity;
    int size;
    float *data;
};//apelido é float_vector, está no .h

float_vector *create(int capacity){//cria vetor
    float_vector *vec = (float_vector *)calloc(1, sizeof(float_vector));
    vec->size = 0;
    vec->capacity = capacity;
    vec->data = (float *)calloc(capacity, sizeof(float));

    return vec;
}

void destroy(float_vector *vec){//destrói vetor
    free(vec->data);
    free(vec);
}

int size(float_vector *vec){//retorna tamanho
    return vec->size;
}

int capacity(float_vector *vec){//retorna capacidade máxima
    return vec->capacity;
}

void append(float_vector *vec, int val){//adiciona 'val' no final do vetor
    if(vec->size == vec->capacity){
        fprintf(stderr, "O VETOR JA ESTA CHEIO!\n");
        exit(EXIT_FAILURE);
    } else{
        vec->data[vec->size] = val;
        vec->size++;
    }
}

float get(float_vector *vec, int index){//retorna valor no índice 'index'
    return vec->data[index];
}

float at(float_vector *vec, int index){//funcao get com checagem
    if(index < 0 || index >= vec->size){
        fprintf(stderr, "ERROR in function 'at'\nIndex [%d] is out of bounds\n", index);
        exit(EXIT_FAILURE);
    }
    return vec->data[index];
}

void set(float_vector *vec, int val, int index){//atribui valor 'val' no índice 'index'
    if(index < 0 || index >= vec->size){
        fprintf(stderr, "ERROR in function 'set'\nIndex is out of bounds\n");
    }
    vec->data[index] = val;
}

void my_remove(float_vector *vec, int index){
    for(int i = index; i < (vec->size - 1); i++){
        vec->data[i] = vec->data[i + 1];
    }
    vec->size--;
}

void print(float_vector *vec){//imprime vetor
    puts("--------------------------------");
    printf("Capacity: %d\n", vec->capacity);
    printf("Size: %d\n", vec->size);
    printf("Vector: ");
    for(int i = 0; i < vec->size; i++){
        printf("%.2f ", vec->data[i]);
    }
    puts("");
    puts("--------------------------------");
}