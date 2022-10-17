#include <stdio.h>
#include <stdlib.h>
#include "structRegistro.h"
#include "FuncoesComuns.h"

void le_arquivo(Registro registro, FILE *arquivo) {
  char c[5];
  while(fread(c, 1, 1, arquivo) != 0) {
    fseek(arquivo, -1, SEEK_CUR); //volta ponteiro para o arquivo em uma posicao por causa no criterio de parada do while, que anda com o ponteiro
    le_string(registro.PrimeiroNome, arquivo, MaxTam_PN); //le dados
    le_string(registro.UltimoNome, arquivo, MaxTam_UN);
    le_string(registro.Email, arquivo, MaxTam_E);
    le_string(registro.Nacionalidade, arquivo, MaxTam_N);
    le_numero(&registro.Idade, arquivo, MaxTam_I);
    imprime_registro(registro); //imprime dados na tela
  }
}

void Opcao2(char *nome_arquivo){
  FILE *arquivo = fopen(nome_arquivo, "rb");
  if(arquivo == NULL){
    printf("Falha no processamento do arquivo");
    return;
  }
  Registro registro;
  le_arquivo(registro, arquivo); //le arquivo de dados e imprime sua informacao na tela
  fclose(arquivo);
}