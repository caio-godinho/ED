#ifndef _FUNCIONALIDADE6_
#define _FUNCIONALIDADE6_
#include "structs.h"

void escreve_cabecalho(cabecalho *cab, FILE *arquivo_entrada, FILE* arquivo_saida);
int compacta_arquivo(cabecalho cab, registro *reg, FILE *arquivo_entrada, FILE *arquivo_saida);
void funcionalidade6();

#endif