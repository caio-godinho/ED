#ifndef COMUNS
#define COMUNS

#include <stdio.h>
#include "structRegistro.h"

void le_numero(int *num, FILE *arquivo, int Tam);
void le_string(char *string, FILE *arquivo, int Tam);
void imprime_registro(Registro registro);

#endif