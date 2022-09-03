#include"funcoes.h"

int main(int argc, char *argv[]) { 
    FILE *arquivo_genoma = fopen("genoma_grande.txt", "r");
    FILE *arquivo_pos_genes = fopen("pos_genes_grande.csv", "r");
    FILE *arquivo_fragmentos = fopen("fragmentos_grande.txt", "r");
    FILE *arquivo_pos_fragmentos = fopen("arquivo_pos_fragmentos.csv", "w+");
    FILE *arquivo_saida = fopen("saida.txt", "w");

    long int n_genes = n_linhas(arquivo_pos_genes) - 1;//SUBTRAI 1 POIS CONSIDERA QUE ULTIMA LINHA DO ARQUIVO É VAZIA

    printf("%ld\n", n_genes);
    double time = 0.0;
    clock_t begin = clock();
    ContagemLeituras(arquivo_genoma, arquivo_pos_genes, arquivo_fragmentos, arquivo_pos_fragmentos, n_genes, 0, arquivo_saida);
    clock_t end = clock();
    time += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time);

    fclose(arquivo_genoma);
    fclose(arquivo_fragmentos);
    fclose(arquivo_pos_genes);
    fclose(arquivo_pos_fragmentos);
    fclose(arquivo_saida);
}