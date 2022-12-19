#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ListaEncadeadaVertice.h"
#include "structs.h"


void msg_erro() { 
    printf("Falha na execução da funcionalidade.\n");
}

//abre arquivo com determinado modo
void abre_arquivo(FILE **fp, const char *nome_arquivo, const char *modo) {
    (*fp) = fopen(nome_arquivo, modo);
    if((*fp) == NULL) {
        msg_erro();
        exit(0);
    }
}

//confere status do arquivo
void confere_status(FILE *arquivo)  {
  char status;
  fseek(arquivo, 0, SEEK_SET);
  fread(&status, sizeof(char), 1, arquivo);
  if(status == '0') {  //se arquivo estiver inconsistente, finaliza execuçào
    msg_erro();
    exit(0);
  }
}

void le_campo_variavel(FILE *arq, char *string, int *i) {
  *i = 0;
  do{
      fread(&(string[*i]), 1, 1, arq);
      (*i)++;
  }while(string[*i - 1] != '|');
  string[*i - 1] = '\0';
}

int le_registro(FILE *arquivo, registro *reg, int *TAM_reg) {
  //conefere se registro foi removido
  char removido;
  //fseek(arquivo, -(sizeof(char) + sizeof(int)), SEEK_CUR);
  fread(&removido, sizeof(char), 1, arquivo);
  fseek(arquivo, sizeof(int), SEEK_CUR); //pula encadeamento
  if(removido == '1')
    return 1;
  
  //le campos de tamanho fixo
  fread(&(reg->idConecta), sizeof(int), 1, arquivo);
  fread(reg->siglaPais, sizeof(char), 2, arquivo);
  reg->siglaPais[2] = '\0';
  fread(&(reg->idPoPsConectado), sizeof(int), 1, arquivo);
  fread(reg->unidadeMedida, sizeof(char), 1, arquivo);
  reg->unidadeMedida[1] = '\0';
  fread(&(reg->velocidade), sizeof(int), 1, arquivo);

  //le campos de tamanho variavel
  int j;
  le_campo_variavel(arquivo, reg->nomePoPs, &j);
  int k;
  le_campo_variavel(arquivo, reg->nomePais, &k);
  
  *TAM_reg = 20 + j + k;
  
  return 0;
}

void registro_no_vertice(const registro reg, Vertice *vertice) {
  vertice->idConecta =  reg.idConecta;
  strcpy(vertice->nomePais, reg.nomePais);
  strcpy(vertice->nomePoPs, reg.nomePoPs);
  strcpy(vertice->siglaPais, reg.siglaPais);
  vertice->cor = 0;
}

void pula_registro(FILE *arquivo, int TAM_registro_atual) {
  fseek(arquivo, TAM_registro-TAM_registro_atual, SEEK_CUR);      //pula para proximo registro
}

int confere_idConecta(FILE *arquivo, registro *reg, int idConecta) {
  int TAM_registro_atual;
  
  fseek(arquivo, sizeof(int) + sizeof(char), SEEK_CUR);       //pula campo "encadeamento" e "removido"
  fread(&reg->idConecta, sizeof(int), 1, arquivo);            //le idConecta
  fseek(arquivo, -(2*sizeof(int) + sizeof(char)), SEEK_CUR);  //reposicionando ponteiro para fazer a leitura do registro, caso necessário

  if(reg->idConecta == idConecta) {                     //caso o valor seja igual
    le_registro(arquivo, reg, &TAM_registro_atual);           //le o registro e coloca na variavel "reg"
    pula_registro(arquivo, TAM_registro_atual);               //pula para proximo registro
    return 1;                                                 //retorna 0, indicando que um registro buscado foi encontrado
  }
  
  pula_registro(arquivo, 0);   //caso o valor seja diferente, pula para comeco do proximo registro
  return 0;
}

FILE *inicializa_arquivo(char *nomeArquivo, char *modo)  {
  FILE *arquivo;
  scanf("%s", nomeArquivo);
  abre_arquivo(&arquivo, nomeArquivo, modo);
  confere_status(arquivo);
  return arquivo;
}

registro busca_registro(FILE *arquivo, int idConecta) {
  registro registroAux;
  char c;
  fseek(arquivo, TAM_PagDisco, SEEK_SET);
  while(fread(&c, sizeof(char), 1, arquivo) != 0) {
    fseek(arquivo, -1, SEEK_CUR);

    if(confere_idConecta(arquivo, &registroAux, idConecta) == 1){ //se encontrou registro buscado
      return registroAux;
    }
  }
}