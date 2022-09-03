#include<stdio.h>
#include<stdlib.h>
#include<time.h>

long int **aloc_matrix(long int **matrix, long int n) {
    matrix = (long int **) calloc(n, sizeof(long int *));
    for(long int i = 0; i<n; i++) {
        matrix[i] = (long int *) calloc(2, sizeof(long int));//Neste trabalho a matriz tem apenas 2 colunas
    }
    return matrix;
}


void free_matrix(long int **matrix, long int n) {
    for(long int i=0; i<n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


int tamanho_texto(FILE *arq_txt) {//CONTA NUMERO DE CARACTERES DO ARQUIVO
    int tamanho = 0;
    while(fgetc(arq_txt) != EOF) {
        tamanho++;
    }
    return tamanho;
}


void CtrlF(FILE *arquivo_texto, FILE *arquivo_trechos, FILE *arquivo_saida) {//ACHA POSICAO DOS FRAGMENTOS (TRECHOS) NO GENOMA
    int tamanho = tamanho_texto(arquivo_texto);//PEGA QUANTIDADE DE CARACTERES NO ARQUIVO GENOMA
    char *texto = malloc(sizeof(char) * (tamanho+1));
    rewind(arquivo_texto);
    fgets(texto, tamanho, arquivo_texto);

    long int i = 0;
    long int j = 0;
    char *trecho = (char *) malloc(sizeof(char) * 5000);
    while(fgets(trecho, 5000, arquivo_trechos) != NULL) {
        i = 0;
        while(texto[i] != '\0') {
            while((trecho[j] != '\0' || trecho[j] != '\n') && (texto[i+j] == trecho[j])) {
                j++;
            }
            if(trecho[j] == '\n') {
                fprintf(arquivo_saida, "%ld,%ld\n", (i+1), (i+j));//IMPRIME EM POS_FRAGMENTOS
                //PRIMEIRO VALOR É (i+1) POIS i COMEÇA EM 0 E O ARQUIVO COMEÇA A CONTAR CARACTERES A PARTIR DO 1
                //SEGUNDO VALOR SERIA (i+j-1), POIS O '\0' FAZ PARTE DO "trecho", ENTÃO j == (tamanho_real_do_fragmento + 1)
                //MAS O LIMITE SUPERIOR COMEÇA EM (i+1), ENTÃO ((i+1)+j-1) == (i+j)
            }
            i++;
            j = 0;
        }
    }
    free(texto);
    free(trecho);
}


int get_digito(long int **A, long int posicao, long int i) {
    long int digito;
    digito = (A[i][0])/posicao;
    digito = digito%10;

    return (int) digito;
}


void OrdenaDigitos(long int **A, long int n, long int posicao) {//Ordena A com relação aos dígitos da primeira coluna
    int B[10] = {0};
    int digito;
    
    for(long int i=0; i<n; i++) {
        digito = get_digito(A, posicao, i);
        B[digito]++;
    }
    for(int i=1; i<10; i++) {
        B[i] = B[i] + B[i-1];
    }

    long int **C = aloc_matrix(C, n);

    for(long int i=(n-1); i>=0; i--) {
        digito = get_digito(A, posicao, i);
        B[digito]--;
        C[B[digito]][0] = A[i][0];
        C[B[digito]][1] = A[i][1];
    }

    for(long int i=0; i<n; i++) {
        A[i][0] = C[i][0];
        A[i][1] = C[i][1];
    }

    free_matrix(C, n);
}


long int get_maior(long int **A, long int n) {
    long int maior = A[0][0];
    for(long int i=0; i<n; i++) {
        if(A[i][0] > maior) {
            maior = A[i][0];
        }
    }
    return maior;
}


void OrdenaNumeros(long int **A, long int n) {
    long int posicao = 1;
    long int maior = get_maior(A, n);
    while((maior/posicao) > 0) {
        OrdenaDigitos(A, n, posicao);
        posicao = posicao * 10;
    }
}


void ContagemIntersecoes(FILE *pos_genes, FILE *pos_fragmentos, long int n_genes, long int n_fragmentos, FILE *arqOUT){
    long int **Matriz_pos_genes = aloc_matrix(Matriz_pos_genes, n_genes);
    long int **Matriz_pos_fragmentos = aloc_matrix(Matriz_pos_fragmentos, n_fragmentos);
    long int *contagens = (long int *) calloc(sizeof(long int), n_genes);
    
    rewind(pos_genes);
    rewind(pos_fragmentos);
    for(long int i = 0; i < n_genes; i++){
        fscanf(pos_genes,"%ld,%ld", &(Matriz_pos_genes[i][0]), &(Matriz_pos_genes[i][1]));
    }
    for(long int j = 0; j < n_fragmentos; j++){
        fscanf(pos_fragmentos,"%ld,%ld", &(Matriz_pos_fragmentos[j][0]), &(Matriz_pos_fragmentos[j][1]));
    }

    /*printf("%ld\n", n_genes);
    double time = 0.0;
    clock_t begin = clock();*/
    OrdenaNumeros(Matriz_pos_genes,n_genes);
    /*clock_t end = clock();
    time += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time);*/

    OrdenaNumeros(Matriz_pos_fragmentos,n_fragmentos);

    /*FILE *Fgenes = fopen("pos_genes_grande_ordenado.txt", "w");
    FILE *Ffragmentos = fopen("pos_fragmentos_pequeno_ordenado.txt", "w");
    for(int i = 0; i < n_genes; i++) {
        fprintf(Fgenes,"%ld,%ld\n", A[i][0], A[i][1]);
    }
    for(int i = 0; i < n_fragmentos; i++) {
        fprintf(Ffragmentos,"%ld,%ld\n", B[i][0], B[i][1]);
    }
    fclose(Fgenes);
    fclose(Ffragmentos);*/

    long int primeiro_iB = 0;
    for(long int iA = 0; iA < n_genes; iA++){
        for(long int iB = primeiro_iB; iB < n_fragmentos; iB++) {
            if((Matriz_pos_genes[iA][1] < Matriz_pos_fragmentos[iB][0]) || (Matriz_pos_genes[iA][0] > Matriz_pos_fragmentos[iB][1])) {
                if(contagens[iA] == 0)
                    primeiro_iB = iB;
            }else{
                contagens[iA]++;
            }
            if((contagens[iA] == 0) && (primeiro_iB == (n_fragmentos-1)))
                primeiro_iB = 0;//RESETA primeiro_iB QUANDO GENE NÃO TEM NENHUMA INTERSECAO PARA NÃO ZERAR CONTAGEM DOS PRÓXIMOS GENES
        }
    }
    
    for(int i = 0; i < n_genes; i++){
        fprintf(arqOUT, "%ld\n", contagens[i]);//IMPRIME NUMERO DE INTERSECCOES NO ARQUIVO DE SAIDA
    }

    free(contagens);
    free_matrix(Matriz_pos_genes, n_genes);
    free_matrix(Matriz_pos_fragmentos, n_fragmentos);
}


int n_linhas(FILE *arq_txt) {
    int linhas = 1;
    char ch = getc(arq_txt);
    while(ch != EOF) {
        if(ch == '\n') {
            linhas++;
        }
        ch = getc(arq_txt);
    }

    return linhas;
}


void ContagemLeituras(FILE *arquivo_genoma, FILE *arquivo_pos_genes, FILE *arquivo_fragmentos, FILE *arquivo_pos_fragmentos, long int n_genes, long int n_fragmentos, FILE *arquivo_saida) {
    CtrlF(arquivo_genoma, arquivo_fragmentos, arquivo_pos_fragmentos);
    rewind(arquivo_pos_fragmentos);
    n_fragmentos = n_linhas(arquivo_pos_fragmentos) - 1;//SUBTRAI 1 POIS CONSIDERA QUE ULTIMA LINHA DO ARQUIVO É VAZIA
    ContagemIntersecoes(arquivo_pos_genes, arquivo_pos_fragmentos, n_genes, n_fragmentos, arquivo_saida);
}