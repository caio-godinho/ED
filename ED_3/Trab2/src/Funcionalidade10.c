#include "Funcoes_comuns.h"
#include "Funcoes_Fornecidas.h"
#include "Funcionalidade8.h"
#include "ArvoreB.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

void print_registroIdConectado(const registro reg1) {
  if(reg1.idConecta != -1){
    printf("Identificador do ponto: %d\n",reg1.idConecta);
  }

  if(reg1.nomePoPs[0] != '\0'){
    printf("Nome do ponto: %s\n", reg1.nomePoPs);
  }

  if(reg1.nomePais[0] != '\0'){
    printf("Pais de localizacao: %s\n", reg1.nomePais);
  }

  if(reg1.siglaPais[0] != '$'){
    printf("Sigla do pais: %s\n", reg1.siglaPais);
  }

  if(reg1.idPoPsConectado != -1){
    printf("Identificador do ponto conectado: %d\n", reg1.idPoPsConectado);
  }
}

void print_registroIdPoPs(const registro reg2, const registro reg1) {
  if(reg2.nomePoPs[0] != '\0'){
    printf("Nome do ponto conectado: %s\n", reg2.nomePoPs);
  }

  if(reg2.nomePais[0] != '\0'){
    printf("Nome do pais conectado: %s\n", reg2.nomePais);
  }

  if(reg2.siglaPais[0] != '$'){
    printf("Sigla do pais: %s\n", reg2.siglaPais);
  }

  if(reg1.velocidade != -1 && reg1.unidadeMedida[0] != '$'){
   printf("Velocidade de transmissao: %d %cbps\n", reg1.velocidade, reg1.unidadeMedida[0]);
  }

  printf("\n");  
}

int BuscaRegIndiceJuncao(FILE *Indices, int chave, int RRN, int *achou){
  if(RRN == -1){
    return -1;
  }
  
  No no;
  leDadosNo(Indices, &no, RRN);
  int RRNFilho = no.P[0];

  for(int i = 0; i < no.nroChavesNo; i++){
    int ch = no.elementos[i].C;
    if(ch == chave){
      return no.elementos[i].Pr;
      (*achou)++;
      }
    else if(chave > ch){
      RRNFilho = no.P[i+1];
    }
  }
  return BuscaRegIndice(Indices, chave, RRNFilho, achou);
}

void funcionalidade10() {
  FILE *arquivo_bin1;
  char nome_ArqBin1[30];
  FILE *arquivo_bin2;
  char nome_ArqBin2[30];
  FILE *arquivo_indices;
  char nome_ArqIndices[30];
  char idPoPs[30];
  char idConecta[30];
  int numPag = 0;

  // le arquivo de entrada
  scanf("%s %s %s %s %s", nome_ArqBin1, nome_ArqBin2, idPoPs, idConecta, nome_ArqIndices);
  if (abre_arquivo(&arquivo_bin1, nome_ArqBin1, "rb") == -1)
    return;
  if (abre_arquivo(&arquivo_bin2, nome_ArqBin2, "rb") == -1)
    return;
  if (abre_arquivo(&arquivo_indices, nome_ArqIndices, "rb") == -1)
    return;

  
  cabecalho cab1;
  cabecalho cab2;
  cabecalhoB cabB;
  registro reg1;
  //copia cabecalho para variavel "cab"; funcao confere o status 
  le_cabecalho(&cab1, arquivo_bin1);
  le_cabecalho(&cab2, arquivo_bin2);
  leCabecalhoB(&cabB, arquivo_indices);
  int RRN = cabB.noRaiz;
  int qntdRRN = cab1.proxRRN;
  int achou = 0;

  
  //busca e imprime na tela
  for(int i = 0; i < qntdRRN; i++){
    int remov = leRegistroChave(arquivo_bin1, &reg1, i);
    if(remov == 1){
        continue;
    }
    int RRNReg = BuscaRegIndiceJuncao(arquivo_indices, reg1.idPoPsConectado, RRN, &achou);
    if(RRNReg == -1){
        continue;
    }
    else if (achou != 0){
        print_registroIdConectado(reg1);
        registro reg2;
        leRegistroChave(arquivo_bin2, &reg2, RRNReg);
        print_registroIdPoPs(reg2, reg1);
    }
  }
  if (achou == 0){
    printf("Registro inexistente.\n");
  }


  fclose(arquivo_bin1);
  fclose(arquivo_bin2);
  fclose(arquivo_indices);
}