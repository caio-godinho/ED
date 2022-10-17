#include <stdio.h>
#include <stdlib.h>
#include "structRegistro.h"
#include "FuncoesComuns.h"

void le_registro(Registro *p_registro, int RRN, FILE *arquivo) {
  fseek(arquivo, RRN*Tam_Reg, SEEK_SET); //Coloca ponteiro no comeco do registro a ser lido
  
  le_string(p_registro->PrimeiroNome, arquivo, MaxTam_PN);
  le_string(p_registro->UltimoNome, arquivo, MaxTam_UN);
  le_string(p_registro->Email, arquivo, MaxTam_E);
  le_string(p_registro->Nacionalidade, arquivo, MaxTam_N);
  le_numero(&p_registro->Idade, arquivo, MaxTam_I);
}

int verifica_RRN(int RRN, FILE *arquivo){
  fseek(arquivo, 0, SEEK_END);
  int tam = ftell(arquivo);
  if(Tam_Reg*RRN >= tam){//confere se o registro de RRN desejado pode estar no arquivo
    printf("Nao foi possivel ler o arquivo");
    return 1; //registro inexistente
  }
  fseek(arquivo, 0, SEEK_SET);//volta ponteiro do arquivo para o comeco
  return 0; //registro existe
}

void Opcao3(char *nome_arquivo){
  FILE *arquivo = fopen(nome_arquivo, "rb");
  if(arquivo == NULL){
    printf("Falha no processamento do arquivo");
    return;
  }
  Registro registro;
  int RRN;
  scanf("%d", &RRN);
  int confere = verifica_RRN(RRN, arquivo); //confere se RRN eh valido
  if (confere == 1){
    fclose(arquivo);
    return;
  }
  le_registro(&registro, RRN, arquivo);//le registro com numero relativo de registro igual a RRN
  imprime_registro(registro);//imprime registro lido na tela
  fclose(arquivo);
}