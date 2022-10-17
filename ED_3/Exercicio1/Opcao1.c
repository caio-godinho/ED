#include "structRegistro.h"
#include "FuncoesFornecidas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void escreve_string(char *string, int tamanho, int n_lixo, FILE *arquivo) {//escreve uma palavra num campo do arquivo binario e preenche resto do espaco com lixo
  fwrite(string, sizeof(char), tamanho, arquivo);
  fwrite(LIXO, sizeof(char), n_lixo, arquivo);
}

void escreve_numero(int num, FILE *arquivo){//escreve um numero inteiro no campo do arquivo binario
  fwrite(&num, sizeof(int), MaxTam_I, arquivo);
}

void escreve_registro(Registro registro, FILE *arquivo) {
  int tamanho;
  int n_lixo;
  
  tamanho = strlen(registro.PrimeiroNome);
  n_lixo = MaxTam_PN - (tamanho+1); //calcula quantide de lixo que deve ser escrito para ocupar espaco do campo
  escreve_string(registro.PrimeiroNome, tamanho+1, n_lixo, arquivo);

  tamanho = strlen(registro.UltimoNome);
  n_lixo = MaxTam_UN - (tamanho+1);
  escreve_string(registro.UltimoNome, tamanho+1, n_lixo, arquivo);

  tamanho = strlen(registro.Email);
  n_lixo = MaxTam_E - (tamanho+1);
  escreve_string(registro.Email, tamanho+1, n_lixo, arquivo);

  tamanho = strlen(registro.Nacionalidade);
  n_lixo = MaxTam_N - (tamanho+1);
  escreve_string(registro.Nacionalidade, tamanho+1, n_lixo, arquivo);

  escreve_numero(registro.Idade, arquivo);
}

void le_um_registro(Registro *registro) {
    scanf("%s\n", registro->PrimeiroNome);
    scanf("%s\n", registro->UltimoNome);
    scanf("%s\n", registro->Email);
    scanf("%s\n", registro->Nacionalidade);
    scanf("%d",   &registro->Idade);
}

void gravar_dados(Registro registro, FILE *arquivo, int nregistros) {
  for(int i = 0; i < nregistros; i++) {
    le_um_registro(&registro); //le o registro do telcado
    escreve_registro(registro, arquivo); //escreve registro lido no arquivo binario
  }
}


void Opcao1(char *nome_arquivo) {
  FILE *arquivo = fopen(nome_arquivo, "wb");
  if(arquivo == NULL){
    printf("Falha no processamento do arquivo");
    return;
  }
  int nregistros;
  scanf("%d", &nregistros); //recebe numero de registros a serem lidos
  Registro registro;
  gravar_dados(registro, arquivo, nregistros); //recebe registro do teclado e grava ele no arquivo binario
  fclose(arquivo);
  binarioNaTela(nome_arquivo); //faz uma operacao com arquivo binario manipulado e imprime um numero inteiro na tela
}