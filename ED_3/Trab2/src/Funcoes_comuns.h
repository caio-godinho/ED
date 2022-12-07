#ifndef _FUNCCOMUNS_
#define _FUNCCOMUNS_

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

void msg_erro();

int abre_arquivo(FILE **fp, char *nome_arquivo, char *modo);

void cria_cabecalho(FILE *arquivo_bin, cabecalho *cab);

void imprime_arq_bin(FILE *arquivo_bin, registro *reg);

void le_cabecalho(cabecalho *cab, FILE *arquivo);

void aloca_listaCampo(char ***lista, const int n);

void destroi_listaCampo(char ***lista, const int n);

void le_listaCampo(char **nomeCampo, char **valorCampo, const int n);

void le_campoVariavel(FILE *arq, char *string, int *i);

void print_registro(const registro reg);

#endif