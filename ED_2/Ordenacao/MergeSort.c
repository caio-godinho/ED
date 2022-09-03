//  **O(N log N)**

#include <stdio.h>

void mergeSort(int *V, int inicio, int fim) {
    int meio;
    if(inicio < fim) {
        meio = floor(((inicio+fim)/2));
        mergeSort(V, inicio, meio);
        mergeSort(V, meio+1, fim);
        merge(V, inicio, meio, fim);
    }
}