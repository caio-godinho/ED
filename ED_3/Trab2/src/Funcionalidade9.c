#include <stdio.h>
#include <stdlib.h>
#include "Funcoes_comuns.h"
#include "Funcoes_Fornecidas.h"
#include "structs.h"
#include "ArvoreB.h"
#include "Funcionalidade5.h"

void funcionalidade9() {
    /*le nomes dos arquivos e número de registros a serem inseridos*/
    FILE *arquivo_dados;
    FILE *arquivo_indices;
    char nome_ArqDados[30];
    char nome_ArqIndices[30];
    int n;

    scanf("%s %s %d", nome_ArqDados, nome_ArqIndices, &n);
    if (abre_arquivo(&arquivo_dados, nome_ArqDados, "rb+") == -1)
        return;
    if (abre_arquivo(&arquivo_indices, nome_ArqIndices, "rb+") == -1)
        return;

    /*copia cabecalhos dos arquivos de dados e de índices para as variaveis "cab" e "cabB"; funções conferem os status*/
    cabecalho cab;
    cabecalhoB cabB;
    le_cabecalho(&cab, arquivo_dados);
    leCabecalhoB(&cabB, arquivo_indices);

    /*muda status para inconsistente (0)*/
    char status = '0';
    fseek(arquivo_dados, 0, SEEK_SET);
    fseek(arquivo_indices, 0 ,SEEK_SET);
    fwrite(&status, sizeof(char), 1, arquivo_dados);
    fwrite(&status, sizeof(char), 1, arquivo_indices);

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

    elemento elem;
    elemento elemPromo;
    int filhoDirPromo = -1;
    registro *reg_aux = (registro*) malloc(sizeof(registro));

    for(int i = 0; i < n; i++) {
        /*le registros a serem inseridos*/
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

        /*copia chave e RRN (do arquivo de dados) no elemento a ser inserido*/
        elem.C = reg_aux->idConecta;
        if(cab.topo == -1)
            elem.Pr = cab.proxRRN;
        else
            elem.Pr = cab.topo;

        /*insere registros no arquivo de dados*/
        insere_registro(reg_aux, &cab, arquivo_dados);

        /*insere chaves no arquivo de índices*/
        if(insercao_recursivo(arquivo_indices, &elem, &elemPromo, &filhoDirPromo, cabB.noRaiz, &(cabB.RRNproxNo), &cabB) == PROMOCAO) {
            No raiz;
            criaNoRaiz(elemPromo, cabB.noRaiz, filhoDirPromo, cabB.RRNproxNo, (cabB.alturaArvore+1), &raiz); //cria nó para ser a nova raíz; (cabB.RRNproxNo-1) pois cabB.RRNproxNo é incrementado na função de (split)
            fseek(arquivo_indices, TamPagDiscoB*(cabB.RRNproxNo + 1), SEEK_SET);    //vai até próximo RRN disponível para inluir um nó
            imprimeNoB(arquivo_indices, &raiz);
            cabB.noRaiz = raiz.RRNdoNo;
            cabB.alturaArvore++;
            cabB.nroChavesTotal++;
            cabB.RRNproxNo++;
        }
    }
    
    /*muda status do arquivo de dados para consistente (1) */
    status = '1';
    fseek(arquivo_dados, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 1, arquivo_dados);
    
    /*atualiza cabeçalho do arquivo de índices*/
    cabB.status = status;
    escreveCabecalhoB(arquivo_indices, &cabB);

    fclose(arquivo_dados);
    fclose(arquivo_indices);
    
    /*binárioNaTela*/
    binarioNaTela(nome_ArqDados);
    binarioNaTela(nome_ArqIndices);

    free(reg_aux);
    destroi_listaCampo(&idConecta, n);
    destroi_listaCampo(&nomePoPs, n);
    destroi_listaCampo(&nomePais, n);
    destroi_listaCampo(&siglaPais, n);
    destroi_listaCampo(&idPoPsConectado, n);
    destroi_listaCampo(&unidadeMedida, n);
    destroi_listaCampo(&velocidade, n);
}