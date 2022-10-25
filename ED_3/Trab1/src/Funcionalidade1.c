#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
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


int confere_string(const char *string) {
    char vazio[3];                      //string que indica campo vazio no arquivo csv
    strcpy(vazio, ",");

    if(strncmp(vazio, string, 1) == 0 || strncmp("\n", string, 1) == 0)  //confere se o proximo caractere eh ",", ou seja, se o proximo campo eh vazio 
        return 0;
    
    return 1;                           //caso o proximo campo nao seja vazio, retorna 1
}


void tira_virgula(char *resto_string) {
    char aux[50];
    int i;
    for(i = 0; i < (strlen(resto_string) - 1); i++) {
        aux[i] = resto_string[i+1];
        resto_string[i] = aux[i];
    }
    resto_string[i] = '\0';
}


void dados_no_registro(char *linha, registro *reg) {
    char *resto_string;     //ponteiro que aponta para resto da string que ainda nao foi "fatiado" pelo strtok_r
    char *dado;

    //le idConecta
    dado = strtok_r(linha,",", &resto_string);      //le idConecta
    reg->idConecta = atoi(dado);                    //atribui valor do idConecta ao campo correspondente no registro

    //le nomePoPs
    if(confere_string(resto_string) == 0) {         //confere se o proximo campo a ser lido eh vazio
        strcpy(reg->nomePoPs, "\0");
        tira_virgula(resto_string);                 //"apaga" proxima virgula, pois o campo eh nulo
    } else {
        dado = strtok_r(NULL,",", &resto_string);   //coloca informacao em "dado"
        strcpy(reg->nomePoPs, dado);                //coloca informacao no registro
    }

    //le nomePais
    if(confere_string(resto_string) == 0) {
        strcpy(reg->nomePais, "\0");
        tira_virgula(resto_string);
    } else {
        dado = strtok_r(NULL,",", &resto_string);
        strcpy(reg->nomePais, dado);
    }

    //le siglaPais
    if(confere_string(resto_string) == 0) {
        strcpy(reg->siglaPais, "\0");
        tira_virgula(resto_string);
    } else {
        dado = strtok_r(NULL,",", &resto_string);
        strcpy(reg->siglaPais, dado);
    }

    //le idPoPsConectado
    if(confere_string(resto_string) == 0) {
        reg->idPoPsConectado = -1;                  //atribui valor -1 para inteiro caso o campo seja vazio
        tira_virgula(resto_string);
    } else {
        dado = strtok_r(NULL,",", &resto_string);
        reg->idPoPsConectado =  atoi(dado);
    }

    //le unidadeMedida
    if(confere_string(resto_string) == 0) {
        strcpy(reg->unidadeMedida, "\0");
        tira_virgula(resto_string);
    } else {
        dado = strtok_r(NULL,",", &resto_string);
        strcpy(reg->unidadeMedida, dado);
    }

    //le velocidade
    if(confere_string(resto_string) == 0) {
        reg->velocidade = -1;  //valor nulo
    } else {
        dado = strtok_r(NULL,",", &resto_string);
        reg->velocidade =  atoi(dado);
    }
    //printf("%d,%s,%s,%s,%d,%s,%d\n", reg->idConecta, reg->nomePoPs, reg->nomePais, reg->siglaPais, reg->idPoPsConectado, reg->unidadeMedida, reg->velocidade);
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

    fwrite(&(reg->idPoPsConectado), sizeof(int), 1, arquivo_bin);

    //unidademedida
    if(strcmp(reg->unidadeMedida, "\0") == 0){ //valor nulo
        fwrite(LIXO, sizeof(char), 1, arquivo_bin);
    }
    else{
        fwrite(reg->unidadeMedida, sizeof(char), 1, arquivo_bin);
    }

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


//le arquivo.csv e escreve dados em arquivo binario
void funcionalidade1() {
    //Abre arquivos de entrada e saida
    FILE *arquivo_entrada;
    FILE *arquivo_saida;
    char nome_ArqEntrada[30];
    char nome_ArqSaida[30];
    readline(nome_ArqEntrada);
    readline(nome_ArqSaida);
    if(abre_arquivo(&arquivo_entrada, nome_ArqEntrada, "r") == -1)  //Abre arquivo; se houver falha, retorna
        return;
    if(abre_arquivo(&arquivo_saida, nome_ArqSaida, "wb+") == -1)   
        return;

    //cria cabecalho do arquivo binario
    cabecalho cab;    
    cria_cabecalho(arquivo_saida, &cab);

    //cria variavel que ira guardar dados do arquivo csv
    registro *reg = (registro*) malloc(sizeof(registro));


    //le arq csv e escreve em bin
    char linha[100];
    fgets(linha, 100, arquivo_entrada); //pula primeira linha do csv
    while(fgets(linha, 100, arquivo_entrada) != NULL) {
      //le dados do arquivo csv: le uma linha do arquivo csv, coloca em um vetor (string), usa funcoes da string.h para manipular ele e colocar informacoes na variavel "reg"
      //e coloca  no arquivo bin
      dados_no_registro(linha, reg);
      imprime_arq_bin(arquivo_saida, reg);
      cab.proxRRN++;
      //imprime dados no arquivo binario
    }

    int num_bytes = cab.proxRRN*64;
    if(num_bytes%960 == 0){
        cab.nroPagDisco = num_bytes/960 +1;
    }
    else{
        cab.nroPagDisco = (num_bytes/960) + 2;
    }

    cab.status = '1';

    fseek(arquivo_saida, 0, SEEK_SET);
    fwrite(&cab.status, sizeof(char), 1, arquivo_saida);

    fseek(arquivo_saida, 5, SEEK_SET);
    fwrite(&cab.proxRRN, sizeof(int), 1, arquivo_saida);

    fseek(arquivo_saida, 13, SEEK_SET);
    fwrite(&cab.nroPagDisco, sizeof(int), 1, arquivo_saida);

    //Chama binarioNaTela
    fclose(arquivo_saida);
    
    binarioNaTela(nome_ArqSaida);
    
    free(reg);
    fclose(arquivo_entrada);
}
