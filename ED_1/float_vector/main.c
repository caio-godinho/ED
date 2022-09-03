#include<stdio.h>
#include<stdlib.h>
#include"float_vector.h"

int main(int argc, char *argv[]){//compliar: gcc main.c float_vector.o -o (nome do executável)
    float_vector *vec = create(10);
    append(vec, 1);
    append(vec, 5);
    append(vec, 7);
    append(vec, 10);
    print(vec);
    set(vec, 6, 1);
    append(vec, 16);
    print(vec);
    my_remove(vec, 0);
    print(vec);
    my_remove(vec, 3);
    print(vec);
    
    destroy(vec);
}