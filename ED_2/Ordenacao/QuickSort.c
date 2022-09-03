#include <stdio.h>

int particiona(int *V, int inicio, int fim) {
    int esq, dir, pivo, aux;
    esq = inicio;
    dir = fim;
    int meio = (inicio + fim)/2;
    pivo = V[meio]; //adotando primeiro elemento como pivo

    while(esq < dir) {
        while(V[esq] < pivo)
            esq++;
        while(V[dir] > pivo)
            dir--;
        if(esq < dir) {
            aux = V[esq];
            V[esq] = V[dir];
            V[dir] = aux;
        }
    }

    return dir;
}


void QuickSort(int *V, int inicio, int fim) {
    int pivo;
    if(fim > inicio) {
        pivo = particiona(V, inicio, fim);
        QuickSort(V, inicio, pivo-1);
        QuickSort(V, pivo+1, fim);
    }
}


    //DO PROFESSOR
    //ADOTA PIVO COMO O ELEMENTO DO MEIO DO VETOR
void quick_sort_original_rec(int v[], int ini, int fim) {
    int meio, pivo, aux, i, j;
    
    if (ini >= fim)
        return; // caso trivial; vetor unitario ou limites invalidos
    
    // escolhe pivo
    meio = ini + (fim - ini) / 2;
    pivo = v[meio];
    
    // coloca o pivo no lugar correto - particionamento
    i = ini;
    j = fim;
    while (1) {
        // posiciona o i
        for ( ; v[i] < pivo; i++);
        
        // posiciona o j
        for ( ; v[j] > pivo; j--);
        
        if (i == j)
            break; // terminou a iteracao
        
        // faz a troca
        aux = v[i];
        v[i] = v[j];
        v[j] = aux;
    }
    
    // processa recursivamente as duas partes
    quick_sort_original_rec(v, ini, i - 1); // metade inferior
    quick_sort_original_rec(v, i + 1, fim); // metade superior
}

void quick_sort_original(int v[], int n) {
    quick_sort_original_rec(v, 0, n - 1); // inicia recursividade
}


int main() {
    int lista[] = {1, 5, 2, 9, 50, 102, 3, 4, 66, 20, 48};
    QuickSort(lista, 0, 10);
    for(int i = 0; i < 11; i++) {
        printf("%d\n", lista[i]);
    }
}