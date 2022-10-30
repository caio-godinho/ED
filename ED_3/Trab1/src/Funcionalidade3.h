#ifndef _FUNCIONALIDADE3_
#define _FUNCIONALIDADE3_

#include "structs.h"

void le_campoVariavel(FILE *arq, char *string, int *i);
int le_registro(FILE *arquivo, registro *reg, int *TAM_reg);
int le_campo(FILE *arq, registro *reg, char *nomeCampo, char *valorCampo);
void print_registro(const registro reg);
void busca_registros(FILE *arquivo_entrada, char *nomeCampo, char *valorCampo, cabecalho cab, int *numReg);
void aloca_listaCampo(char ***lista, const int n);
void destroi_listaCampo(char ***lista, const int n);
void le_listaCampo(char **nomeCampo, char **valorCampo, const int n);
void funcionalidade3();

#endif