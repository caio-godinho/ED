#ifndef _FUNCIONALIDADE8_
#define _FUNCIONALIDADE8_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "ArvoreB.h"

int leRegistroChave(FILE *arquivo, registro *reg, int RRN);
int leRegistro(FILE *arquivo, registro *reg, int *TAM_reg);
int leCampo(FILE *arq, registro *reg, char *nomeCampo, char *valorCampo);
void print_registro(const registro reg);
void funcionalidade8();
void BuscaRegistros(FILE *arquivo_entrada, char *nomeCampo, char *valorCampo, int *numReg);
void leListaCampo(char **nomeCampo, char **valorCampo, const int n);
void leDadosNo(FILE *arq, No *no, int RRNFilho);
void imprimeNo(No no);
int BuscaRegIndice(FILE *Indices, int chave, int RRN, int *numPagDisco);

#endif