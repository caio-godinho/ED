#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include <string.h>
#include <ctype.h>
#include "Funcoes_Fornecidas.h"

void msg_erro() { 
    printf("Falha no processamento do arquivo.\n");
}

//abre arquivo com determinado modo
int abre_arquivo(FILE **fp, char *nome_arquivo, char *modo) {
    (*fp) = fopen(nome_arquivo, modo);
    if((*fp) == NULL) {
        msg_erro();
        return -1;
    }
    return 0;
}

void cria_cabecalho(FILE *arquivo_bin, cabecalho *cab) {
    //inicia variavel do tipo cabecalho
    cab->status = '0';
    cab->topo = -1;
    cab->proxRRN = 0;
    cab->nroRegRem = 0;
    cab->nroPagDisco = 0;
    cab->qttCompacta = 0;

    //escreve cabecalho no arquivo binario
    fwrite(&cab->status, sizeof(char), 1, arquivo_bin);
    fwrite(&(cab->topo), sizeof(int), 1, arquivo_bin);
    fwrite(&(cab->proxRRN), sizeof(int), 1, arquivo_bin);
    fwrite(&(cab->nroRegRem), sizeof(int), 1, arquivo_bin);
    fwrite(&(cab->nroPagDisco), sizeof(int), 1, arquivo_bin);
    fwrite(&(cab->qttCompacta), sizeof(int), 1, arquivo_bin);
    for(int i = 0; i < (TAM_PagDisco-TAM_cabecalho); i++)    //escreve lixo no espaco restante da pagina de disco
        fwrite("$", sizeof(char), 1, arquivo_bin); 
}

void imprime_arq_bin(FILE *arquivo_bin, registro *reg){
    char removido[2] = "0";
    int encadeamento = -1;
    fwrite(removido, sizeof(char), 1, arquivo_bin);
    fwrite(&encadeamento, sizeof(int), 1, arquivo_bin);
    fwrite(&(reg->idConecta), sizeof(int), 1, arquivo_bin);
    //siglaPais
    if(strcmp(reg->siglaPais, "\0") == 0){ //valor nulo
        fwrite(LIXO, sizeof(char), 2, arquivo_bin);
    }
    else{
        fwrite(reg->siglaPais, sizeof(char), 2, arquivo_bin);
    }

    //idPoPsConectado
    fwrite(&(reg->idPoPsConectado), sizeof(int), 1, arquivo_bin);

    //unidademedida
    if(strcmp(reg->unidadeMedida, "\0") == 0){ //valor nulo
        fwrite(LIXO, sizeof(char), 1, arquivo_bin);
    }
    else{
        fwrite(reg->unidadeMedida, sizeof(char), 1, arquivo_bin);
    }

    //Velocidade
    fwrite(&(reg->velocidade), sizeof(int), 1, arquivo_bin);

    //nomepops
    int tamPoPs = strlen(reg->nomePoPs);

    if(strcmp(reg->nomePoPs, "\0") == 0){ //valor nulo
        fwrite("|", 1, 1, arquivo_bin);
    }
    else{
        fwrite(reg->nomePoPs, sizeof(char), tamPoPs, arquivo_bin);
        fwrite("|", 1, 1, arquivo_bin);
    }   

    //nomePais
    int tamPais;
    tamPais = strlen(reg->nomePais);
    if(strcmp(reg->nomePais, "\0") == 0){ //valor nulo
        fwrite("|", 1, 1, arquivo_bin);
    }
    else{
        fwrite(reg->nomePais, sizeof(char), tamPais, arquivo_bin);
        fwrite("|", 1, 1, arquivo_bin);
    }

    int tam_var = tamPoPs + tamPais + 2;
    int tam_total = 20 + tam_var;

    for(int i = 0; i < (TAM_registro - tam_total); i++){   //escreve lixo no espaco restante do registro
        fwrite(LIXO, sizeof(char), 1, arquivo_bin);
    }         
}

void le_cabecalho(cabecalho *cab, FILE *arquivo){
    fseek(arquivo, 0, SEEK_SET);
    fread(&cab->status, sizeof(char), 1, arquivo);
    if(cab->status == '0'){
        msg_erro();
        exit(0);
    }
    fread(&cab->topo, sizeof(int), 1, arquivo);
    fread(&cab->proxRRN, sizeof(int), 1, arquivo);
    fread(&cab->nroRegRem, sizeof(int), 1, arquivo);
    fread(&cab->nroPagDisco, sizeof(int), 1, arquivo);
    fread(&cab->qttCompacta, sizeof(int), 1, arquivo);
}

void aloca_listaCampo(char ***lista, const int n) {
  *lista = (char**) malloc(sizeof(char *) * n);
  for(int i = 0; i < n; i++)
    (*lista)[i] = (char*) malloc(sizeof(char) * 30);
}

void destroi_listaCampo(char ***lista, const int n) {
  for(int i = 0; i < n; i++) {
    free((*lista)[i]);
    (*lista)[i] = NULL;
  }
  free(*lista);
  *lista = NULL;
}

void le_listaCampo(char **nomeCampo, char **valorCampo, const int n) {
  for (int i = 0; i < n; i++) {
    scanf("%s", nomeCampo[i]);
    if(strcmp(nomeCampo[i], "idConecta") == 0 || strcmp(nomeCampo[i],"idPoPsConectado") == 0 || strcmp(nomeCampo[i], "velocidade") == 0) {
      scanf("%s", valorCampo[i]); //se campo for um inteiro, usa scanf normal
    }
    else { //se campo for uma string entre aspas, utiliza funcao que le e tira as aspas
      scan_quote_string(valorCampo[i]);
    }
  }
}

void le_campoVariavel(FILE *arq, char *string, int *i) {
  *i = 0;
  do{
      fread(&(string[*i]), 1, 1, arq);
      (*i)++;
  }while(string[*i - 1] != '|');
  string[*i - 1] = '\0';
}