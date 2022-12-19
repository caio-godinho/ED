#ifndef _FUNCCOMUNS_
#define _FUNCCOMUNS_

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "ListaEncadeadaVertice.h"
#include "ListaEncadeadaAresta.h"

void msg_erro();
void confere_status(FILE *arquivo);
int abre_arquivo(FILE **fp, char *nome_arquivo, char *modo);
void le_campo_variavel(FILE *arq, char *string, int *i);
int le_registro(FILE *arquivo, registro *reg, int *TAM_reg);
void registro_no_vertice(const registro reg, Vertice *vertice);
int confere_idConecta(FILE *arquivo, registro *reg, int idConecta);
registro busca_registro(FILE *arquivo, int idConecta);
FILE *inicializa_arquivo(char *nomeArquivo, char *modo);

#endif