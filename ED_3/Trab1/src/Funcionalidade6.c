#include "Funcionalidade1.h"
#include "Funcionalidade2.h"
#include "Funcoes_Fornecidas.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void escreve_cabecalho(cabecalho *cab, FILE *arquivo_entrada, FILE* arquivo_saida){ //transfere dados do arquivo bin passado para a saida com os arquivos compactados
  fseek(arquivo_entrada, 0, SEEK_SET);
  fread(&cab->status, sizeof(char), 1, arquivo_entrada);
  if(cab->status == '0'){
      msg_erro();
      exit(0);
  }
  fread(&cab->topo, sizeof(int), 1, arquivo_entrada);
  fread(&cab->proxRRN, sizeof(int), 1, arquivo_entrada);
  fread(&cab->nroRegRem, sizeof(int), 1, arquivo_entrada);
  fread(&cab->nroPagDisco, sizeof(int), 1, arquivo_entrada);
  fread(&cab->qttCompacta, sizeof(int), 1, arquivo_entrada);

  fwrite(&cab->status, sizeof(char), 1, arquivo_saida);
  fwrite(&cab->topo, sizeof(int), 1, arquivo_saida);
  fwrite(&cab->proxRRN, sizeof(int), 1, arquivo_saida);
  fwrite(&cab->nroRegRem, sizeof(int), 1, arquivo_saida);
  fwrite(&cab->nroPagDisco, sizeof(int), 1, arquivo_saida);
  fwrite(&cab->qttCompacta, sizeof(int), 1, arquivo_saida);
  for(int i = 0; i < (TAM_PagDisco-TAM_cabecalho); i++)    //escreve lixo no espaco restante da pagina de disco
    fwrite("$", sizeof(char), 1, arquivo_saida);   
}
int compacta_arquivo(cabecalho cab, registro *reg, FILE *arquivo_entrada, FILE *arquivo_saida){ // ignora os arquivos marcados como 1 no campo removido e escreve no arquivo saida
    int RRN_disponivel = 0;
    int offset;
    char removido;
    for(int i = 0; i < cab.proxRRN; i++){
      offset = 960 + 64*i;
      fseek(arquivo_entrada, offset, SEEK_SET);
      fread(&removido, sizeof(char), 1, arquivo_entrada);
      if(removido == '1'){ // se o registro estiver removido, pula para o proximo loop/registro e não o imprime no arquivo saida
          continue;
      }

      fseek(arquivo_entrada, 4, SEEK_CUR);

      fread(&(reg->idConecta), sizeof(int), 1, arquivo_entrada);
      fread(reg->siglaPais, sizeof(char), 2, arquivo_entrada);
      reg->siglaPais[2] = '\0';
      fread(&(reg->idPoPsConectado), sizeof(int), 1, arquivo_entrada);
      fread(reg->unidadeMedida, sizeof(char), 1, arquivo_entrada);
      reg->unidadeMedida[1] = '\0';
      fread(&(reg->velocidade), sizeof(int), 1, arquivo_entrada);
      
      int j = 0;
      do{
          fread(&reg->nomePoPs[j], 1, 1, arquivo_entrada);
          j++;
      }while(reg->nomePoPs[j - 1] != '|');
      reg->nomePoPs[j - 1] = '\0';

      int k = 0;
      do{
          fread(&reg->nomePais[k], 1, 1, arquivo_entrada);
          k++;
      }while(reg->nomePais[k - 1] != '|');
      reg->nomePais[k - 1] = '\0';

      imprime_arq_bin(arquivo_saida, reg); // escreve na saida o arquivo compactado
      RRN_disponivel++;

  }  
  return RRN_disponivel;
}

void funcionalidade6(){
    char nome_ArqEntrada[30];
    readline(nome_ArqEntrada);
  
    FILE *arquivo_entrada = fopen(nome_ArqEntrada, "rb");
    FILE *arquivo_saida = fopen("binario_compactado.bin", "wb+");
    if(arquivo_entrada == NULL){
        printf("Falha no processamento do arquivo");
        return;
    }

    registro *reg = (registro*) malloc(sizeof(registro));
    cabecalho cab;
    escreve_cabecalho(&cab, arquivo_entrada, arquivo_saida);
    cab.proxRRN = compacta_arquivo(cab, reg, arquivo_entrada, arquivo_saida); // funcao retorna o proxRRN e escreve o arquivo compactado na saida
    cab.qttCompacta++; //funcao de compactar foi chamada
    cab.topo = -1;
    cab.nroRegRem = 0;
  
    int num_bytes = cab.proxRRN*TAM_registro; // calcula as pag de disco do arquivo ja compactado
    if(num_bytes%TAM_PagDisco == 0){
        cab.nroPagDisco = (num_bytes/TAM_PagDisco) + 1;
    }
    else{
        cab.nroPagDisco = (num_bytes/TAM_PagDisco) + 2;
    }

    // ESCREVE OS DADOS DO CABECALHO Q FORAM ATUALIZADOS  
    fseek(arquivo_saida, 1, SEEK_SET);
    fwrite(&cab.topo, sizeof(int), 1, arquivo_saida);

    fseek(arquivo_saida, 5, SEEK_SET);
    fwrite(&cab.proxRRN, sizeof(int), 1, arquivo_saida);  

    fseek(arquivo_saida, 9, SEEK_SET);
    fwrite(&cab.nroRegRem, sizeof(int), 1, arquivo_saida);    

    fseek(arquivo_saida, 13, SEEK_SET);
    fwrite(&cab.nroPagDisco, sizeof(int), 1, arquivo_saida);  
  
    fseek(arquivo_saida, 17, SEEK_SET);
    fwrite(&cab.qttCompacta, sizeof(int), 1, arquivo_saida);

    fclose(arquivo_entrada);
    fclose(arquivo_saida);
    binarioNaTela("binario_compactado.bin");
    free(reg);
}