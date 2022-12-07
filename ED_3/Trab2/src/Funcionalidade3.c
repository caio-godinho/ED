#include "Funcoes_comuns.h"
#include "Funcoes_Fornecidas.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int le_registro(FILE *arquivo, registro *reg, int *TAM_reg) {
  //conefere se registro foi removido
  char removido;
  fseek(arquivo, -(sizeof(char) + sizeof(int)), SEEK_CUR);
  fread(&removido, sizeof(char), 1, arquivo);
  fseek(arquivo, sizeof(int), SEEK_CUR); //volta ponteiro para posicao inicial
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
  le_campoVariavel(arquivo, reg->nomePoPs, &j);
  int k;
  le_campoVariavel(arquivo, reg->nomePais, &k);
  
  *TAM_reg = 20 + j + k;
  
  return 0;
}

int le_campo(FILE *arq, registro *reg, char *nomeCampo, char *valorCampo) {
  int TAM_reg;
  
  fseek(arq, sizeof(int) + sizeof(char), SEEK_CUR);    //pula campo "encadeamento"

  //caso o campo procurado seja do tipo "idConecta"
  if(strcmp("idConecta",nomeCampo) == 0){
    if(fread(&reg->idConecta, sizeof(int), 1, arq) == 0)         //le idConecta; retorna 1 caso final do arquivo seja atingido
      return 1;
    fseek(arq, -sizeof(int), SEEK_CUR);
    if(reg->idConecta == atoi(valorCampo)) {                     //caso o valor seja igual
      if(le_registro(arq, reg, &TAM_reg) == 1) {                 //le o registro e coloca na variavel "reg"
        fseek(arq, 64 - (sizeof(char) + sizeof(int)), SEEK_CUR);
        return 1;                                                //retorna 1 caso registro tenha sido removido
      }                   
        fseek(arq, 64-TAM_reg, SEEK_CUR);                        //pula para proximo registro
        return 0;                                                //retorna 0, indicando que um registro buscado foi encontrado
    } else {
      fseek(arq, 64 - (sizeof(char) + sizeof(int)), SEEK_CUR);   //caso o valor seja diferente, pula para comeco do proximo registro
    }
  }

  if(strcmp("siglaPais", nomeCampo) == 0) {
    fseek(arq, sizeof(int), SEEK_CUR);
    if(fread(reg->siglaPais, sizeof(char), 2, arq) == 0)
      return 1;
    fseek(arq, -(sizeof(char)*2 + sizeof(int)), SEEK_CUR);
    if(strcmp(reg->siglaPais, valorCampo) == 0) {
      if(le_registro(arq, reg, &TAM_reg) == 1) {
        fseek(arq, 64 - (sizeof(char) + sizeof(int)), SEEK_CUR);
        return 1;
      }
      fseek(arq, 64-TAM_reg, SEEK_CUR);
      return 0;
    } else {
      fseek(arq, 64 - (sizeof(char) + sizeof(int)), SEEK_CUR);
    }
  }

  if(strcmp("idPoPsConectado",nomeCampo) == 0){
    fseek(arq, sizeof(int) + sizeof(char)*2, SEEK_CUR);
    if(fread(&reg->idPoPsConectado, sizeof(int), 1, arq) == 0)
      return 1;
    fseek(arq, -(sizeof(char)*2 + sizeof(int)*2), SEEK_CUR);
    if(reg->idPoPsConectado == atoi(valorCampo)) {
      if(le_registro(arq, reg, &TAM_reg) == 1) {
        fseek(arq, 64 - (sizeof(char) + sizeof(int)), SEEK_CUR);
        return 1;
      }
      fseek(arq, 64-TAM_reg, SEEK_CUR);
      return 0;
    } else {
      fseek(arq, 64 - (sizeof(char) + sizeof(int)), SEEK_CUR);
    }
  }

  if(strcmp("unidadeMedida",nomeCampo) == 0){
    fseek(arq, sizeof(int)*2 + sizeof(char)*2, SEEK_CUR);      //pula os campos anteriores
    if(fread(reg->unidadeMedida, sizeof(char), 1, arq) == 0)
      return 1;
    fseek(arq, -(sizeof(char)*3 + sizeof(int)*2), SEEK_CUR);    //volta para comeco do regitro (apos "removido" e "encadeamento")
    if(reg->unidadeMedida[0] == valorCampo[0]) {
      if(le_registro(arq, reg, &TAM_reg) == 1) {
        fseek(arq, 64 - (sizeof(char) + sizeof(int)), SEEK_CUR);
        return 1;
      }
      fseek(arq, 64-TAM_reg, SEEK_CUR);
      return 0;
    } else {
      fseek(arq, 64 - (sizeof(char) + sizeof(int)), SEEK_CUR);
    }
  }

  if(strcmp("velocidade",nomeCampo) == 0){
      fseek(arq, sizeof(int)*2 + sizeof(char)*3, SEEK_CUR);
      if(fread(&reg->velocidade, sizeof(int), 1, arq) == 0)
        return 1;
      fseek(arq, -(sizeof(char)*3 + sizeof(int)*3), SEEK_CUR);
      if(reg->velocidade == atoi(valorCampo)) {
        if(le_registro(arq, reg, &TAM_reg) == 1) {
          fseek(arq, 64 - (sizeof(char) + sizeof(int)), SEEK_CUR);
          return 1;
        }
        fseek(arq, 64-TAM_reg, SEEK_CUR);
        return 0;
      } else {
        fseek(arq, 64 - (sizeof(char) + sizeof(int)), SEEK_CUR);
      }
    }

  if(strcmp("nomePoPs", nomeCampo) == 0) {
    fseek(arq, sizeof(int)*3 + sizeof(char)*3, SEEK_CUR);

    int j;
    le_campoVariavel(arq, reg->nomePoPs, &j);

    fseek(arq, -(j + sizeof(int)*3 + sizeof(char)*3), SEEK_CUR);
    if(strcmp(reg->nomePoPs, valorCampo) == 0)  {
      if(le_registro(arq, reg, &TAM_reg) == 1) {
        fseek(arq, 64 - (sizeof(char) + sizeof(int)), SEEK_CUR);
        return 1;
      }
      fseek(arq, 64-TAM_reg, SEEK_CUR);
      return 0;
    } else {
      fseek(arq, 64 - (sizeof(char) + sizeof(int)), SEEK_CUR);
    }
  }

  if(strcmp("nomePais", nomeCampo) == 0) {
    fseek(arq, sizeof(int)*3 + sizeof(char)*3, SEEK_CUR);

    int j;
    le_campoVariavel(arq, reg->nomePoPs, &j);
    int k;
    le_campoVariavel(arq, reg->nomePais, &k);

    fseek(arq, -(j + k + sizeof(int)*3 + sizeof(char)*3), SEEK_CUR);
    if(strcmp(reg->nomePais, valorCampo) == 0)  {
      if(le_registro(arq, reg, &TAM_reg) == 1) {
        fseek(arq, 64 - (sizeof(char) + sizeof(int)), SEEK_CUR);
        return 1;
      }
      fseek(arq, 64-TAM_reg, SEEK_CUR);
      return 0;
    } else {
      fseek(arq, 64 - (sizeof(char) + sizeof(int)), SEEK_CUR);
    }
  }

  return 1;
}

void busca_registros(FILE *arquivo_entrada, char *nomeCampo, char *valorCampo, int *numReg) {
  registro reg_aux;

  //coloca ponteiro na posicao correta para ler o idConecta do primeiro Registro
  fseek(arquivo_entrada, 960, SEEK_SET);

  //laco para ler todos os registros do arquivo
  char c;
  while(fread(&c, 1, 1, arquivo_entrada) != 0) {  //confere se arquivo chegou ao fim
    fseek(arquivo_entrada, -1, SEEK_CUR);

    //le campo e confere se possui o valor buscado. Se tiver, imprime
    if(le_campo(arquivo_entrada, &reg_aux, nomeCampo, valorCampo) == 0) {
      print_registro(reg_aux);  
      (*numReg)++;
    }
  }
}

void funcionalidade3() {
  FILE *arquivo_entrada;
  char nome_ArqEntrada[30];
  int n;

  // le arquivo de entrada
  scanf("%s %d", nome_ArqEntrada, &n);
  if (abre_arquivo(&arquivo_entrada, nome_ArqEntrada, "rb") == -1)
    return;

  cabecalho cab;
  //copia cabecalho para variavel "cab"; funcao confere o status 
  le_cabecalho(&cab, arquivo_entrada);

  //cria e aloca espaco para listas que guardarao os nomes e valores dos campos a serem buscados
  char **nomeCampo;
  char **valorCampo;
  aloca_listaCampo(&nomeCampo, n);
  aloca_listaCampo(&valorCampo, n);

  //le campos a serem buscados
  le_listaCampo(nomeCampo, valorCampo, n);

  //busca e imprime na tela
  int numReg;
  for(int i = 0; i < n; i++) {
    numReg = 0;
    printf("Busca %d\n", (i+1));

    busca_registros(arquivo_entrada, nomeCampo[i], valorCampo[i], &numReg);
    
    if(numReg == 0)
      printf("Registro inexistente.\n\n");
    printf("Numero de paginas de disco: %d\n\n", cab.nroPagDisco);
  }


  destroi_listaCampo(&nomeCampo, n);
  destroi_listaCampo(&valorCampo, n);
  fclose(arquivo_entrada);
}