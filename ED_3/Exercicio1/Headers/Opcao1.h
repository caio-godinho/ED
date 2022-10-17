
#ifndef OPCAO1_H
#define OPCAO1_H
#include "structRegistro.h"
#include <stdio.h>

void Opcao1(char *nome_arquivo);
void escreve_string(char *string, int tamanho, int n_lixo, FILE *arquivo);
void escreve_numero(int num, FILE *arquivo);
void escreve_registro(Registro registro, FILE *arquivo);
void le_um_registro(Registro registro);
void gravar_dados(Registro registros[], FILE *arquivo, int nregistros);

#endif