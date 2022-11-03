#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "Funcoes_comuns.h"
#include "Funcoes_Fornecidas.h"

void incrementa_nroRegRem(FILE *arq, const int RRN)  {
    int nroRegRem;
    fseek(arq, sizeof(char) + sizeof(int)*2, SEEK_SET);
    fread(&nroRegRem, sizeof(int), 1, arq);
    nroRegRem++;
    fseek(arq, -sizeof(int), SEEK_CUR);
    fwrite(&nroRegRem, sizeof(int), 1, arq);
}

void atualiza_encadeamento(FILE *arq, const int RRN) {
    int valor_topo;                                         //variavel que guardara o RRN do proximo registro removido
    fseek(arq, sizeof(char), SEEK_SET);                     //vai para comeco do cabecalho
    fread(&valor_topo, sizeof(int), 1, arq);                //coloca valor atual do topo na variavel "valor_topo"
    fseek(arq, -sizeof(int), SEEK_CUR);                     //volta o ponteiro para escrever no topo
    fwrite(&RRN, sizeof(int), 1, arq);                      //escreve no topo o RRN do ultimo registro removido
    fseek(arq, (960 + 64*RRN) + sizeof(char), SEEK_SET);    //volta ponteiro para "encadeamento" do registro removido
    fwrite(&valor_topo, sizeof(int), 1, arq);               //escreve valor_topo (RRN do proximo registro removido) no encadeamento
}

void imprime_lixo(FILE *arq) {
    char lixo = '$';
    for(int i = 0; i < (TAM_registro - (sizeof(char) + sizeof(int))); i++) {
        fwrite(&lixo, sizeof(char), 1, arq);
    }
}

void remove_registro(FILE *arq, char *nomeCampo, char *valorCampo) {
    registro reg_aux;

    fseek(arq, 960, SEEK_SET);                          //pula cabecalho

    char c;
    int RRN = 0;
    char removido = '1';

    while(fread(&c, 1, 1, arq) != 0) {                  //confere se arquivo chegou ao fim
        fseek(arq, -1, SEEK_CUR);

        //confere se registro foi removido
        fread(reg_aux.removido, sizeof(char), 1, arq);
        fseek(arq, -sizeof(char), SEEK_CUR);
        if(reg_aux.removido[0] ==  '1') {               //se registro ja foi removido, acaba a iteracao atual do laco
            fseek(arq, TAM_registro, SEEK_CUR);         //pula para proximo registro antes de "resetar" o laco
            RRN++;
            continue;
        }

        //se registro a ser removido for do tipo idConecta
        if(strcmp(nomeCampo, "idConecta") == 0) {
            fseek(arq, sizeof(char) + sizeof(int), SEEK_CUR);
            fread(&reg_aux.idConecta, sizeof(int), 1, arq);
            if(reg_aux.idConecta == atoi(valorCampo)) {                    //se o registro deve ser removido
                fseek(arq, -(sizeof(char) + sizeof(int)*2), SEEK_CUR);     //volta para comeco dos campos de controle do registro
                fwrite(&removido, sizeof(char), 1, arq);                   //imprime 1 na flag de removido do registro
                incrementa_nroRegRem(arq, RRN);                            //incrementa "nroRegRem" do cabecalho
                atualiza_encadeamento(arq, RRN);                           //atualiza "encadeamento" do registro e "topo" do cabecalho
                imprime_lixo(arq);                                         //imprime lixo nos campos do registro e pula para proximo registro

            } else {                                                                    //se idConecta nao tem o valor buscado
                fseek(arq, TAM_registro - (sizeof(char) + sizeof(int)*2), SEEK_CUR);    //pula para proximo registro
            }
        }

        //se registro for do tipo siglaPais
        else if(strcmp(nomeCampo, "siglaPais") == 0) {
            fseek(arq, sizeof(char) + sizeof(int)*2, SEEK_CUR);
            fread(reg_aux.siglaPais, sizeof(char), 2, arq);
            if(strcmp(reg_aux.siglaPais, valorCampo) == 0) {               //se o registro deve ser removido
                fseek(arq, -(sizeof(char)*3 + sizeof(int)*2), SEEK_CUR);   //volta para comeco dos campos de controle do registro
                fwrite(&removido, sizeof(char), 1, arq);                   //imprime 1 na flag de removido do registro
                incrementa_nroRegRem(arq, RRN);                            //incrementa "nroRegRem" do cabecalho
                atualiza_encadeamento(arq, RRN);                           //atualiza "encadeamento" do registro e "topo" do cabecalho
                imprime_lixo(arq);                                         //imprime lixo nos campos do registro e pula para proximo registro     

            } else {                                                                    //se siglaPais nao tem o valor buscado
                fseek(arq, TAM_registro - (sizeof(char)*3 + sizeof(int)*2), SEEK_CUR);  //pula para proximo registro
            }
        }

        //se registro for do tipo idPoPsConectado
        else if(strcmp(nomeCampo, "idPoPsConectado") == 0) {
            fseek(arq, sizeof(char)*3 + sizeof(int)*2, SEEK_CUR);
            fread(&reg_aux.idPoPsConectado, sizeof(int), 1, arq);
            if(reg_aux.idPoPsConectado == atoi(valorCampo)) {              //se o registro deve ser removido
                fseek(arq, -(sizeof(char)*3 + sizeof(int)*3), SEEK_CUR);   //volta para comeco dos campos de controle do registro
                fwrite(&removido, sizeof(char), 1, arq);                   //imprime 1 na flag de removido do registro
                incrementa_nroRegRem(arq, RRN);                            //incrementa "nroRegRem" do cabecalho
                atualiza_encadeamento(arq, RRN);                           //atualiza "encadeamento" do registro e "topo" do cabecalho
                imprime_lixo(arq);                                         //imprime lixo nos campos do registro e pula para proximo registro
                
            } else {                                                                    //se idConecta nao tem o valor buscado
                fseek(arq, TAM_registro - (sizeof(char)*3 + sizeof(int)*3), SEEK_CUR);  //pula para proximo registro
            }
        }

        //se registro for do tipo unidadeMedida
        else if(strcmp(nomeCampo, "unidadeMedida") == 0) {
            fseek(arq, sizeof(char)*3 + sizeof(int)*3, SEEK_CUR);
            fread(reg_aux.unidadeMedida, sizeof(char), 1, arq);
            if(reg_aux.unidadeMedida[0] ==  valorCampo[0]) {               //se o registro deve ser removido
                fseek(arq, -(sizeof(char)*4 + sizeof(int)*3), SEEK_CUR);   //volta para comeco dos campos de controle do registro
                fwrite(&removido, sizeof(char), 1, arq);                   //imprime 1 na flag de removido do registro
                incrementa_nroRegRem(arq, RRN);                            //incrementa "nroRegRem" do cabecalho
                atualiza_encadeamento(arq, RRN);                           //atualiza "encadeamento" do registro e "topo" do cabecalho
                imprime_lixo(arq);                                         //imprime lixo nos campos do registro e pula para proximo registro
                
            } else {                                                                    //se unidadeMedida nao tem o valor buscado
                fseek(arq, TAM_registro - (sizeof(char)*4 + sizeof(int)*3), SEEK_CUR);  //pula para proximo registro
            }
        }

        //se registro for do tipo velocidade
        else if(strcmp(nomeCampo, "velocidade") == 0) {
            fseek(arq, sizeof(char)*4 + sizeof(int)*3, SEEK_CUR);
            fread(&reg_aux.velocidade, sizeof(int), 1, arq);
            if(reg_aux.velocidade == atoi(valorCampo)) {                   //se o registro deve ser removido
                fseek(arq, -(sizeof(char)*4 + sizeof(int)*4), SEEK_CUR);   //volta para comeco dos campos de controle do registro
                fwrite(&removido, sizeof(char), 1, arq);                   //imprime 1 na flag de removido do registro
                incrementa_nroRegRem(arq, RRN);                            //incrementa "nroRegRem" do cabecalho
                atualiza_encadeamento(arq, RRN);                           //atualiza "encadeamento" do registro e "topo" do cabecalho
                imprime_lixo(arq);                                         //imprime lixo nos campos do registro e pula para proximo registro

            } else {                                                                      //se velocidade nao tem o valor buscado
                fseek(arq, TAM_registro - (sizeof(char)*4 + sizeof(int)*4), SEEK_CUR);    //pula para proximo registro
            }
        }

        else if(strcmp(nomeCampo, "nomePoPs") == 0) {
            int j;
            fseek(arq, sizeof(char)*4 + sizeof(int)*4, SEEK_CUR);
            le_campoVariavel(arq, reg_aux.nomePoPs, &j);
            //printf("%s\n", reg_aux.nomePoPs);
            if(strcmp(reg_aux.nomePoPs, valorCampo) == 0) {                    //se o registro deve ser removido
                fseek(arq, -(sizeof(char)*4 + sizeof(int)*4 + j), SEEK_CUR);   //volta para comeco dos campos de controle do registro
                fwrite(&removido, sizeof(char), 1, arq);                       //imprime 1 na flag de removido do registro
                incrementa_nroRegRem(arq, RRN);                                //incrementa "nroRegRem" do cabecalho
                atualiza_encadeamento(arq, RRN);                               //atualiza "encadeamento" do registro e "topo" do cabecalho
                imprime_lixo(arq);                                             //imprime lixo nos campos do registro e pula para proximo registro

            } else {                                                                          //se nomePoPs nao tem o valor buscado
                fseek(arq, TAM_registro - (sizeof(char)*4 + sizeof(int)*4 + j), SEEK_CUR);    //pula para proximo registro
            }
        }

        else if(strcmp(nomeCampo, "nomePais") == 0) {
            int j;
            int k;
            fseek(arq, sizeof(char)*4 + sizeof(int)*4, SEEK_CUR);
            le_campoVariavel(arq, reg_aux.nomePoPs, &j);
            le_campoVariavel(arq, reg_aux.nomePais, &k);
            if(strcmp(reg_aux.nomePais, valorCampo) == 0) {                        //se o registro deve ser removido
                fseek(arq, -(sizeof(char)*4 + sizeof(int)*4 + j + k), SEEK_CUR);   //volta para comeco dos campos de controle do registro
                fwrite(&removido, sizeof(char), 1, arq);                           //imprime 1 na flag de removido do registro
                incrementa_nroRegRem(arq, RRN);                                    //incrementa "nroRegRem" do cabecalho
                atualiza_encadeamento(arq, RRN);                                   //atualiza "encadeamento" do registro e "topo" do cabecalho
                imprime_lixo(arq);                                                 //imprime lixo nos campos do registro e pula para proximo registro

            } else {                                                                              //se nomePais nao tem o valor buscado
                fseek(arq, TAM_registro - (sizeof(char)*4 + sizeof(int)*4 + j + k), SEEK_CUR);    //pula para proximo registro
            }
        }

        RRN++;
    }
}

void funcionalidade4() {
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

    //muda status para inconsistente (0)
    char status = '0';
    fseek(arquivo_entrada, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 1, arquivo_entrada);
  
  
    //cria e aloca espaco para listas que guardarao os nomes e valores dos campos a serem buscados
    char **nomeCampo;
    char **valorCampo;
    aloca_listaCampo(&nomeCampo, n);
    aloca_listaCampo(&valorCampo, n);
  
    //le campos a serem buscados
    le_listaCampo(nomeCampo, valorCampo, n);

    //remove registros
    for(int i = 0; i < n; i++) {  
        remove_registro(arquivo_entrada, nomeCampo[i], valorCampo[i]);
    }

    //muda status para consistente (1)
    status = '1';
    fseek(arquivo_entrada, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 1, arquivo_entrada);
  
    fclose(arquivo_entrada);
  
    binarioNaTela(nome_ArqEntrada);

    destroi_listaCampo(&nomeCampo, n);
    destroi_listaCampo(&valorCampo, n);
}