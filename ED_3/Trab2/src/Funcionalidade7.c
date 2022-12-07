#include <stdio.h>
#include <stdlib.h>
#include "Funcoes_comuns.h"
#include "Funcoes_Fornecidas.h"
#include "structs.h"
#include "ArvoreB.h"


/*Indexa os registros de um arquivo binário de dados em um arquivo de índices do tipo Árvore-B*/
void funcionalidade7() {
    /*Lê o nome dos arquivos de entrada e saída e os abre*/
    FILE *arquivo_entrada;
    FILE *arquivo_saida;
    char nome_ArqEntrada[30];
    char nome_ArqSaida[30];
    readline(nome_ArqEntrada);
    readline(nome_ArqSaida);

    if(abre_arquivo(&arquivo_entrada, nome_ArqEntrada, "rb") == -1)  //Abre arquivo; se houver falha, retorna
        return;
    if(abre_arquivo(&arquivo_saida, nome_ArqSaida, "wb+") == -1)   
        return;

    cabecalho cab;
    le_cabecalho(&cab, arquivo_entrada); /*copia cabeçalho do arquivo de dados em "cab"; confere se o "status" do arquivo é válido*/
    cabecalhoB cabB;
    criaCabecalhoB(arquivo_saida, &cabB); /*escreve cabeçalho do arquivo de índices e guarda os dados na variável "cabB"*/

    fseek(arquivo_entrada, TAM_PagDisco, SEEK_SET); //pula cabeçalho no arquivo de entrada

    int RRN_Dados = 0;  //RRN do próximo registro a ser lido do arquivo de dados
    char removido;
    elemento elem;
    elemento elemPromo;
    int filhoDirPromo = -1;

    /*indexa primeira chave no arquivo de índices*/
    inserePrimeiraChave(arquivo_entrada, arquivo_saida, &RRN_Dados, &cabB);

    fseek(arquivo_entrada, TAM_PagDisco + (RRN_Dados*TAM_registro), SEEK_SET);  //pula para próximo registro a ser lido do arquivo de dados

    /*laço de repetição: lê um registro do arquivo de dados e insere idConecta e RRN correspondentes no arquivo de índices*/
    while(fread(&removido, sizeof(char), 1, arquivo_entrada) != 0) {
        if(removido ==  '1') { //se registro foi removido, le o próximo
            RRN_Dados++;
            fseek(arquivo_entrada, TAM_PagDisco + (RRN_Dados*TAM_registro), SEEK_SET); //pula para próximo registro do arquivo de dados
            continue;
        }
        
        leElemento(arquivo_entrada, &elem, RRN_Dados); //le idConecta e RRN de registro no arquivo de entrada e coloca em "elem"
        
        /*começa o algorítmo de inserção pelo nó raíz. Se necessário, cria novo nó raíz*/
        if(insercao_recursivo(arquivo_saida, &elem, &elemPromo, &filhoDirPromo, cabB.noRaiz, &(cabB.RRNproxNo), &cabB) == PROMOCAO) {
            No raiz;
            criaNoRaiz(elemPromo, cabB.noRaiz, filhoDirPromo, cabB.RRNproxNo, (cabB.alturaArvore+1), &raiz); //cria nó para ser a nova raíz; (cabB.RRNproxNo-1) pois cabB.RRNproxNo é incrementado na função de (split)
            fseek(arquivo_saida, TamPagDiscoB*(cabB.RRNproxNo + 1), SEEK_SET);    //vai até próximo RRN disponível para inluir um nó
            imprimeNoB(arquivo_saida, &raiz);
            cabB.noRaiz = raiz.RRNdoNo;
            cabB.alturaArvore++;
            cabB.nroChavesTotal++;
            cabB.RRNproxNo++;
        }

        RRN_Dados++;
        fseek(arquivo_entrada, TAM_PagDisco + (RRN_Dados*TAM_registro), SEEK_SET);  //pula para próximo registro a ser lido do arquivo de dados
    }

    /*atualiza cabeçalho*/
    cabB.status = '1';
    escreveCabecalhoB(arquivo_saida, &cabB);

    fclose(arquivo_entrada);
    fclose(arquivo_saida);

    binarioNaTela(nome_ArqSaida);
}