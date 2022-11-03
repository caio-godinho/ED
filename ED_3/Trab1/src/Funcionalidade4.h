#ifndef _FUNCIONALIDADE4_
#define _FUNCIONALIDADE4_

#include <stdio.h>

void incrementa_nroRegRem(FILE *arq, const int RRN);

void atualiza_encadeamento(FILE *arq, const int RRN);

void imprime_lixo(FILE *arq);

void remove_registro(FILE *arq, char *nomeCampo, char *valorCampo);

void funcionalidade4();

#endif