#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "Funcoes_Fornecidas.h"

void le_cabecalho(cabecalho *cab, FILE *arquivo){
    fseek(arquivo, 0, SEEK_SET);
    fread(&cab->status, sizeof(char), 1, arquivo);
    fread(&cab->topo, sizeof(int), 1, arquivo);
    fread(&cab->proxRRN, sizeof(int), 1, arquivo);
    fread(&cab->nroRegRem, sizeof(int), 1, arquivo);
    fread(&cab->nroPagDisco, sizeof(int), 1, arquivo);
    fread(&cab->qttCompacta, sizeof(int), 1, arquivo);
}

void le_arquivo(cabecalho cab, registro *reg, FILE *arquivo){
    for(int i = 0; i < cab.proxRRN; i++){
        int offset = 960 + 64*i;
        fseek(arquivo, offset, SEEK_SET);
        char removido;
        fread(&removido, sizeof(char), 1, arquivo);
        if(removido == '1'){
            printf("Registro inexistente.\n\n");
            continue;
        }

        fseek(arquivo, 4, SEEK_CUR);

        fread(&(reg->idConecta), sizeof(int), 1, arquivo);
        fread(reg->siglaPais, sizeof(char), 2, arquivo);
        reg->siglaPais[2] = '\0';
        fread(&(reg->idPoPsConectado), sizeof(int), 1, arquivo);
        fread(reg->unidadeMedida, sizeof(char), 1, arquivo);
        reg->unidadeMedida[1] = '\0';
        fread(&(reg->velocidade), sizeof(int), 1, arquivo);
        
        int j = 0;
        do{
            fread(&reg->nomePoPs[j], 1, 1, arquivo);
            j++;
        }while(reg->nomePoPs[j - 1] != '|');
        reg->nomePoPs[j - 1] = '\0';

        int k = 0;
        do{
            fread(&reg->nomePais[k], 1, 1, arquivo);
            k++;
        }while(reg->nomePais[k - 1] != '|');
        reg->nomePais[k - 1] = '\0';

        if(reg->idConecta != -1){
            printf("Identificador do ponto: %d\n",reg->idConecta);
        }

        if(reg->nomePoPs[0] != '\0'){
            printf("Nome do ponto: %s\n", reg->nomePoPs);
        }

        if(reg->nomePais[0] != '\0'){
            printf("Pais de localizacao: %s\n", reg->nomePais);
        }

        if(reg->siglaPais[0] != '$'){
            printf("Sigla do pais: %s\n", reg->siglaPais);
        }

        if(reg->idPoPsConectado != -1){
            printf("Identificador do ponto conectado: %d\n", reg->idPoPsConectado);
        }

        if(reg->velocidade != -1 && reg->unidadeMedida[0] != '$'){
            printf("Velocidade de transmissao: %d %cbps\n", reg->velocidade, reg->unidadeMedida[0]);
        }

        printf("\n");
    }
}

void funcionalidade2(){
    char nome_ArqSaida[30];
    readline(nome_ArqSaida);
    FILE *arquivo_bin = fopen(nome_ArqSaida, "rb");
    if(arquivo_bin == NULL){
        printf("Falha no processamento do arquivo");
        return;
    }

    registro *reg = (registro*) malloc(sizeof(registro));
    cabecalho cab;
    le_cabecalho(&cab, arquivo_bin);
    le_arquivo(cab, reg, arquivo_bin);

    printf("Numero de paginas de disco: %d\n\n",cab.nroPagDisco);

    free(reg);
    fclose(arquivo_bin);
}