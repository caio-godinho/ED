#ifndef _FUNCIONALIDADE1_
#define _FUNCIONALIDADE1_

#include "structs.h"

void msg_erro();
int abre_arquivo(FILE **fp, char *nome_arquivo, char *modo);
void cria_cabecalho(FILE *arquivo_bin, cabecalho *cab);
int confere_string(const char *string);
void tira_virgula(char *resto_string);
void tira_espaco_final(char string[100]);
void dados_no_registro(char *linha, registro *reg);
void imprime_arq_bin(FILE *arquivo_bin, registro *reg);
void funcionalidade1();

#endif