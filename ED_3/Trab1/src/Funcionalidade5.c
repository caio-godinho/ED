#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "structs.h"
#include "Funcionalidade1.h"
#include "Funcionalidade2.h"
#include "Funcionalidade3.h"
#include "Funcoes_Fornecidas.h"

void insere_registro(registro *reg, cabecalho *cab, FILE *arq) {
  //confere topo
  if(cab->topo == -1) {                      //se topo == -1, não há registros removidos; então insere no final
    fseek(arq, 0, SEEK_END);
    imprime_arq_bin(arq, reg);
    int numPagDisco = ceil(1 + ftell(arq)/960);
    
    //atualizar proxRRN e talvez o numPagDisco
    cab->proxRRN++;
    fseek(arq, sizeof(char) + sizeof(int), SEEK_SET);
    fwrite(&cab->proxRRN, sizeof(int), 1, arq);
    
    if(cab->nroPagDisco != numPagDisco) {    //atualiza nroPagDisco do cabecalho se o numero de paginas de disco aumentou
      cab->nroPagDisco = numPagDisco;
      fseek(arq, sizeof(int), SEEK_CUR);
      fwrite(&cab->nroPagDisco, sizeof(int), 1, arq);
    }
  }
    
  else {
    //se topo != -1, sobrescreve registro previamente removido
    fseek(arq, sizeof(char), SEEK_SET);
    fread(&cab->topo, sizeof(int), 1, arq);                                        //le RRN no topo da pilha de  remocao
    fseek(arq, TAM_PagDisco + cab->topo*TAM_registro + sizeof(char), SEEK_SET);    //vai ate campo "encadeamento" do regisstro a ser sobrescrito
    fread(&cab->topo, sizeof(int), 1, arq);                                        //le "encadeamento", que sera novo o topo da pilha
    fseek(arq, -(sizeof(char) + sizeof(int)), SEEK_CUR);                           //volta para comeco do registro
    imprime_arq_bin(arq, reg);                                                     //imprime registro no arquivo binario
    cab->nroRegRem--;
    
    //atualizar topo
    fseek(arq, sizeof(char), SEEK_SET);
    fwrite(&cab->topo, sizeof(int), 1, arq);
    
    //atualiza nroRegRem
    fseek(arq, sizeof(int), SEEK_CUR);
    fwrite(&cab->nroRegRem, sizeof(int), 1, arq);
  }
}

void copia_inteiro(int *campo, char *valor) {
  if(strcmp(valor, "") == 0)
    *campo = -1;
  else
    *campo = atoi(valor);
}

void copia_string(char *campo, char *valor) {
  if(strcmp(valor, "") == 0)
    strcpy(campo, "\0");
  else
    strcpy(campo, valor);
}

void funcionalidade5() {
  FILE *arquivo_entrada;
  char nome_ArqEntrada[30];
  int n;

  // le arquivo de entrada e o numero de inputs
  scanf("%s %d", nome_ArqEntrada, &n);
  if (abre_arquivo(&arquivo_entrada, nome_ArqEntrada, "rb+") == -1)
      return;

  cabecalho cab;
  //copia cabecalho para variavel "cab"; funcao confere o status 
  le_cabecalho(&cab, arquivo_entrada);

  char **idConecta;
  char **nomePoPs;
  char **nomePais;
  char **siglaPais;
  char **idPoPsConectado;
  char **unidadeMedida;
  char **velocidade;
  aloca_listaCampo(&idConecta, n);
  aloca_listaCampo(&nomePoPs, n);
  aloca_listaCampo(&nomePais, n);
  aloca_listaCampo(&siglaPais, n);
  aloca_listaCampo(&idPoPsConectado, n);
  aloca_listaCampo(&unidadeMedida, n);
  aloca_listaCampo(&velocidade, n);

  registro *reg_aux = (registro*) malloc(sizeof(registro));

  for(int i = 0; i < n; i++) {
    scan_quote_string(idConecta[i]);
    scan_quote_string(nomePoPs[i]);
    scan_quote_string(nomePais[i]);
    scan_quote_string(siglaPais[i]);
    scan_quote_string(idPoPsConectado[i]);
    scan_quote_string(unidadeMedida[i]);
    scan_quote_string(velocidade[i]);
    
    copia_inteiro(&reg_aux->idConecta, idConecta[i]);
    copia_inteiro(&reg_aux->idPoPsConectado, idPoPsConectado[i]);
    copia_inteiro(&reg_aux->velocidade, velocidade[i]);
    copia_string(reg_aux->nomePoPs, nomePoPs[i]);
    copia_string(reg_aux->nomePais, nomePais[i]);
    copia_string(reg_aux->siglaPais, siglaPais[i]);
    copia_string(reg_aux->unidadeMedida, unidadeMedida[i]);

    insere_registro(reg_aux, &cab, arquivo_entrada);
  }

  fclose(arquivo_entrada);
  binarioNaTela(nome_ArqEntrada);

  free(reg_aux);
  destroi_listaCampo(&idConecta, n);
  destroi_listaCampo(&nomePoPs, n);
  destroi_listaCampo(&nomePais, n);
  destroi_listaCampo(&siglaPais, n);
  destroi_listaCampo(&idPoPsConectado, n);
  destroi_listaCampo(&unidadeMedida, n);
  destroi_listaCampo(&velocidade, n);
}