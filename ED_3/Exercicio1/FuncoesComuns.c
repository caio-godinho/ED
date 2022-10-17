#include "structRegistro.h"
#include <stdio.h>

void le_numero(int *num, FILE *arquivo, int Tam){//le um numero inteiro do arquivo binario
  fread(num, sizeof(int), Tam, arquivo);
}

void le_string(char *string, FILE *arquivo, int Tam) {//le uma palavra do arquivo binario
  fread(string, sizeof(char), Tam, arquivo);
}

void imprime_registro(Registro registro) {//imprime registro na tela
  printf("Firstname: %s\nLastname: %s\nEmail: %s\nNationality: %s\nAge: %d\n\n", registro.PrimeiroNome,registro.UltimoNome,registro.Email,registro.Nacionalidade,registro.Idade);
}