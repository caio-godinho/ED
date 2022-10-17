#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"structs.h"
#include"Funcoes_Fornecidas.h"


void msg_erro() { 
    printf("Falha no processamento do arquivo\n"); 
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


void cria_cabecalho(FILE *arquivo_bin) {
    //inicia variavel do tipo cabecalho
    cabecalho *cab = (cabecalho*) malloc(sizeof(cabecalho));
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


registro *cria_registro() {
    registro *reg = (registro*) malloc(sizeof(registro));
    reg->nomePoPs = (char*) malloc(sizeof(char) * 50);
    reg->nomePais = (char*) malloc(sizeof(char) * 50);
    return reg; 
}


void destroi_registro(registro **reg) {
    free((*reg)->nomePais);
    free((*reg)->nomePoPs);
    free(*reg);
}


//le arquivo.csv e escreve dados em arquivo binario
void funcionalidade1() {
    //Abre arquivos de entrada e saida
    FILE *arquivo_entrada;
    FILE *arquivo_saida;
    if(abre_arquivo(&arquivo_entrada, "topologiaRede.csv", "r") == -1)  //se  houve falha no arquivo, retorna
        return;
    if(abre_arquivo(&arquivo_saida, "topologiaRede.bin", "wb+") == -1)   
        return;

    //cria cabecalho do arquivo binario
    cria_cabecalho(arquivo_saida);

    //cria variavel que ira guardar dados do arquivo csv
    registro *reg = cria_registro();

    //le dados do arquivo csv

    
    
    //imprime dados no arquivo binario
    


    //Chama binarioNaTela
    free(arquivo_saida);
    //binarioNaTela();

    destroi_registro(&reg);
    free(arquivo_entrada);
}