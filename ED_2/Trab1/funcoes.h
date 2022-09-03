#ifndef FUNCOES_H
#define FUNCOES_H
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

long int **aloc_matrix(long int **matrix, long int n);

void free_matrix(long int **matrix, long int n);

int tamanho_texto(FILE *arq_txt);

void CtrlF(FILE *arquivo_texto, FILE *arquivo_trechos, FILE *arquivo_saida);

int get_digito(long int **A, long int posicao, long int i);

void OrdenaDigitos(long int **A, long int n, long int posicao);

long int get_maior(long int **A, long int n);

void OrdenaNumeros(long int **A, long int n);

void ContagemIntersecoes(FILE *arqA, FILE *arqB, long int nA, long int nB, FILE *arqOUT);

int n_linhas(FILE *arq_txt);

void ContagemLeituras(FILE *arquivo_genoma, FILE *arquivo_pos_genes, FILE *arquivo_fragmentos, FILE *arquivo_pos_fragmentos, long int n_genes, long int n_fragmentos, FILE *arquivo_saida);

#endif