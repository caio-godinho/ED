//  **O(N^2)**

#include <stdio.h>

void bubble_sort(int *v, int n) {
    int continua, aux, fim = n;

    do {
        continua = 0;
        for(int i = 0; i < fim-1; i++) {
            if(v[i] > v[i+1]) {
                aux = v[i+1];
                v[i+1] = v[i];
                v[i] = aux;
                continua = i;
            }
        }
        fim--;    
    } while (continua != 0);
}

int main(int argc, char *argv[]) {
    int v[] = {1 ,2 ,3 ,4 ,5};
    bubble_sort(v, 5);
    
    for(int i = 0; i < 5; i++) {
        printf("%d\n", v[i]);
    }
}