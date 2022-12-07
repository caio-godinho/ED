#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structs.h"
#include "Funcoes_comuns.h"

/*Ordem da árvore-B*/
#define ORDEM 5

/*Caractere utilizado para representar o lixo*/
#define LIXOB  "$"

/*Tamanho das páginas de disco, do registro de cabeçalho e dos nós*/
#define TamPagDiscoB 65

/*Quantidade de bytes preechidos pelos campos do cabecalhoB*/
#define TamcabecalhoB 17

/*Indicador de promoção de um elemento na árvore-B*/
#define PROMOCAO 1

/*Indicador de que não houve promoção de um elemento na árvore-B*/
#define NAO_PROMOCAO 0

//Struct que representa cada elemento dentro de um nó
typedef struct _elemento {
  int Pr;          //RRN dos elemento no arquivo de dados
  int C;          //chave do elemento
} elemento;

//Struct que representa um nó na árvore-B
typedef struct _No {
  char folha;           //Se nó é folha(1) ou não(0) 
  int nroChavesNo;      //Número de chaves de indexação 
  int alturaNo;         //Nível em que nó se encontra na árvore
  int RRNdoNo;          //RRN do nó no arquivo de índices
  elemento elementos[ORDEM-1];  //lista de elementos
  int P[ORDEM];         //Ponteiro que guarda RRNs dos nós filhos
} No;

typedef struct _NoExt {
  char folha;           //Se nó é folha(1) ou não(0) 
  int nroChavesNo;      //Número de chaves de indexação 
  int alturaNo;         //Nível em que nó se encontra na árvore
  int RRNdoNo;          //RRN do nó no arquivo de índices
  elemento elementos[ORDEM];  //lista de elementos
  int P[ORDEM+1];         //Ponteiro que guarda RRNs dos nós filhos
} NoExtendido;

//Struct que representa o registro de cabecalhoB
typedef struct _cabecalhoB {
  char status;         //Consistência do arquivo de índice
  int noRaiz;          //RRN do nó raiz
  int nroChavesTotal;  //Número de chaves de busca
  int alturaArvore;    //Indica a altura da árvore
  int RRNproxNo;       //Indica RRN do próximo nó a ser inserido
} cabecalhoB;

/*Cria novo nó*/
No *criaNo() {
  No *no = (No*) malloc(sizeof(No));

  //Inicia valores dos campos do registro/Nó
  no->folha = 1;
  no->nroChavesNo = 0;
  no->alturaNo = -1;
  no->RRNdoNo = -1;
  
  int i;
  for(i = 0; i < (ORDEM-1); i++) {
    no->elementos[i].Pr = -1;
    no->elementos[i].C = -1;
    no->P[i] = -1;
  }
  no->P[i] = -1;
  
  return no;
}

/*Desaloca espaço de um nó*/
void destroiNo(No **no) {
  free((*no));
  *no = NULL;
}

/*Cria novo nó com uma chave e um ponteiro para filho a mais*/
NoExtendido *criaNoExtendido() {
  NoExtendido *no = (NoExtendido*) malloc(sizeof(NoExtendido));

  //Inicia valores dos campos do registro/Nó
  no->folha = 1;
  no->nroChavesNo = 0;
  no->alturaNo = -1;
  no->RRNdoNo = -1;
  
  int i;
  for(i = 0; i < ORDEM; i++) {
    no->elementos[i].Pr = -1;
    no->elementos[i].C = -1;
    no->P[i] = -1;
  }
  no->P[i] = -1;
  
  return no;
}

/*Escreve os dados de "cab" no cabeçalho do arquivo de índices*/
void escreveCabecalhoB(FILE *arq, cabecalhoB *cab) {
  fseek(arq, 0, SEEK_SET);
  //Insere no cabecalho
  fwrite(&(cab->status), sizeof(char), 1, arq);
  fwrite(&(cab->noRaiz), sizeof(int), 1, arq);
  fwrite(&(cab->nroChavesTotal), sizeof(int), 1, arq);
  fwrite(&(cab->alturaArvore), sizeof(int), 1, arq);
  fwrite(&(cab->RRNproxNo), sizeof(int), 1, arq);
}

/*Cria o cabecalhoB do arquivo de indices*/
void criaCabecalhoB(FILE *arq, cabecalhoB *cab){
  //Inicializa variaveis do cabecalho
  cab->status = '0';
  cab->noRaiz = -1;
  cab->nroChavesTotal = 0;
  cab->alturaArvore = 0;
  cab->RRNproxNo = 0;

  escreveCabecalhoB(arq, cab);
  for(int i = 0; i < (TamPagDiscoB - TamcabecalhoB); i++)
    fwrite(LIXOB, sizeof(char), 1, arq);
}

/*Le o cabecalhoB e vê se o arquivo é consistente*/
void leCabecalhoB(cabecalhoB *cab, FILE *arq){
    fseek(arq, 0, SEEK_SET);
    fread(&(cab->status), sizeof(char), 1, arq);
    if(cab->status == '0'){
        msg_erro();
        exit(0); //arquivo inconsistente para execução
    }
    fread(&(cab->noRaiz), sizeof(int), 1, arq);
    fread(&(cab->nroChavesTotal), sizeof(int), 1, arq);
    fread(&(cab->alturaArvore), sizeof(int), 1, arq);
    fread(&(cab->RRNproxNo), sizeof(int), 1, arq);
}

/*escreve informações em "cab" no cabeçalho do arquivo de índices*/
void atualizaCabecalhoB(cabecalhoB *cab, FILE *arq) {
  fseek(arq, 0, SEEK_SET);
  fwrite(&cab->status, sizeof(char), 1, arq);
  fwrite(&cab->noRaiz, sizeof(int), 1, arq);
  fwrite(&cab->nroChavesTotal, sizeof(int), 1, arq);
  fwrite(&cab->alturaArvore, sizeof(int), 1, arq);
  fwrite(&cab->RRNproxNo, sizeof(int), 1, arq);
}

/*Le os dados do proximo nó do arquivo de índices*/
void leDadosNoB(FILE *arq, No *no) {
  int i;
  fread(&(no->folha), sizeof(char), 1, arq);
  fread(&(no->nroChavesNo), sizeof(int), 1, arq);
  fread(&(no->alturaNo), sizeof(int), 1, arq);
  fread(&(no->RRNdoNo), sizeof(int), 1, arq);

  for(i = 0; i < (ORDEM-1); i++) {
    fread(&(no->P[i]), sizeof(int), 1, arq);
    fread(&(no->elementos[i].C), sizeof(int), 1, arq);
    fread(&(no->elementos[i].Pr), sizeof(int), 1, arq);
  }
  fread(&(no->P[i]), sizeof(int), 1, arq);
}

/*escreve dados em "no" no arquivo de índices*/
void imprimeNoB(FILE *arq, No *no) {
  int i;
  fwrite(&no->folha, sizeof(char), 1, arq);
  fwrite(&no->nroChavesNo, sizeof(int), 1, arq);
  fwrite(&no->alturaNo, sizeof(int), 1, arq);
  fwrite(&no->RRNdoNo, sizeof(int), 1, arq);
  for(i = 0; i < (ORDEM-1); i++) {
    fwrite(&(no->P[i]), sizeof(int), 1, arq);
    fwrite(&(no->elementos[i].C), sizeof(int), 1, arq);
    fwrite(&(no->elementos[i].Pr), sizeof(int), 1, arq);
  }
  fwrite(&(no->P[i]), sizeof(int), 1, arq);
}

/*Insere um elemento e o RRN de seu filho à direita em um nó*/
//elem: elemento a se inserido
//no: nó no qual o "elem" será inserido
//RRN: endereço do filho à direita de "elem"
//nroChaves: número de chaves que "no" pode armazenar
void insereElem(elemento *elem, No *no, const int RRN, const int nroChaves) {
  elemento aux1 = *elem;
  elemento aux2;
  int RRN_aux1 = RRN;
  int RRN_aux2;
  for(int i = 0; i < nroChaves; i++) {
    if(no->elementos[i].C == -1) {
      no->elementos[i] = aux1;
      no->P[i+1] = RRN_aux1;
      break;
    }
    else if(aux1.C < no->elementos[i].C) {
      aux2 = no->elementos[i];
      no->elementos[i] = aux1;
      aux1 = aux2;

      RRN_aux2 = no->P[i+1];
      no->P[i+1] = RRN_aux1;
      RRN_aux1 = RRN_aux2;
    }
  }
}

/*Mesmo que "insereElem", mas para um nó com uma chave e um ponteiro para filho a mais*/
void insereElemExt(elemento *elem, NoExtendido *no, const int RRN, const int nroChaves) {
  elemento aux1 = *elem;
  elemento aux2;
  int RRN_aux1 = RRN;
  int RRN_aux2;
  for(int i = 0; i < nroChaves; i++) {
    if(no->elementos[i].C == -1) {
      no->elementos[i] = aux1;
      no->P[i+1] = RRN_aux1;
      break;
    }
    else if(aux1.C < no->elementos[i].C) {
      aux2 = no->elementos[i];
      no->elementos[i] = aux1;
      aux1 = aux2;

      RRN_aux2 = no->P[i+1];
      no->P[i+1] = RRN_aux1;
      RRN_aux1 = RRN_aux2;
    }
  }
}

/*Função que executa o particionamento*/
//elemInf: elemento que será inserido
//RRNInf: RRN do filho direito de elemInf
//no_aux: nó no qual se quer inserir o elemento
//elemPromo: elemento que será promovido
//filhoDirPromo: RRN do filho à direita do elemento que será promovido
//no_novo: nó que será criado
void split(elemento *elemInf, const int RRNInf, No *no_aux, elemento *elemPromo, int *filhoDirPromo, No *no_novo, int *RRNproxNo, cabecalhoB *cabB) {
  /*cria nó que armazena um elemento e um ponteiro para filho a mais*/
  NoExtendido *no_extendido = criaNoExtendido();

  /*copia no_aux para no_extendido*/
  no_extendido->folha = no_aux->folha;
  no_extendido->RRNdoNo = no_aux->RRNdoNo;
  no_extendido->alturaNo = no_aux->alturaNo;
  no_extendido->nroChavesNo = no_aux->nroChavesNo;
  int i;
  for(i = 0; i < (ORDEM-1); i++) {
    no_extendido->elementos[i] = no_aux->elementos[i];
    no_extendido->P[i] = no_aux->P[i];
  }
  no_extendido->P[i] = no_aux->P[i];

  /*Insere "elemInf" no "no_extendido"*/
  insereElemExt(elemInf, no_extendido, RRNInf, ORDEM);

  /*elemento a ser promovido é o do "meio"*/
  int meio = ceil((double)ORDEM/2) - 1;

  *elemPromo = no_extendido->elementos[meio];

  /*Atribui o próximo RRN disponível para o endereço do novo nó e incrementa o próximo RRN disponível*/
  *filhoDirPromo = *RRNproxNo;

  (*RRNproxNo)++;

  /*copia elementos menores que o "meio" para no_aux*/
  for(int i = 0; i < (ORDEM-1); i++) {
    if(i < meio) {
      no_aux->elementos[i] = no_extendido->elementos[i];
      no_aux->P[i+1] = no_extendido->P[i+1];
    } else {
      no_aux->elementos[i].C = -1;
      no_aux->elementos[i].Pr = -1;
      no_aux->P[i+1] = -1;
    }
  }
  no_aux->nroChavesNo = meio;

  /*copia elementos maiores que o "meio" para no_novo*/
  for(int i = 0; i < (ORDEM-1); i++) {
    if(i < meio) {
      no_novo->elementos[i] = no_extendido->elementos[i + (meio+1)];
      no_novo->P[i+1] = no_extendido->P[i + 1 + (meio+1)];
    } else {
      no_novo->elementos[i].C = -1;
      no_novo->elementos[i].Pr = -1;
      no_novo->P[i+1] = -1;
    }
  }
  no_novo->P[0] = no_extendido->P[meio+1];
  no_novo->folha = no_aux->folha;
  no_novo->nroChavesNo = meio;
  no_novo->alturaNo = no_aux->alturaNo;
  no_novo->RRNdoNo = *filhoDirPromo;

  //libera espaço utilizado pelo nó extendido
  free(no_extendido);
}

/*Insere um elemento (chave e ponteiro) na árvore*/
//arq: ponteiro para o arquivo de índices
//elem: elemento a ser inserido
//elemPromo: elemento a ser promovido
//filhoDirPromo: ponteiro para o filho direito do elemento promovido
//RRN: RRN do nó a ser acessado
//RRNproxNo: RRN do próximo nó a ser acessado
int insercao_recursivo(FILE *arq, elemento *elem, elemento *elemPromo, int *filhoDirPromo, const int RRN, int *RRNproxNo, cabecalhoB *cabB) {
  No no_aux;   /*no sendo analisado atualmente*/
  No no_novo;  /*novo nó resultante do split*/
  int posicao;  /*posição do nó em que chave deve ser inserida*/
  int RRNInf;  /*RRN do filho à direita do elemento promovido*/
  elemento elemInf; /*elemento promovido de um nó inferior*/
  int RETORNO;

  /*Se chegou no final da árvore, promove elemento para nó folha*/
  if(RRN == -1) {
    *elemPromo = *elem;
    *filhoDirPromo = -1;
    return PROMOCAO;
  }

  fseek(arq, TamPagDiscoB*(RRN+1), SEEK_SET); /*acessa nó de determinado RRN. (RRN+1) pois o cabeçalho tem o tamanho de uma página de disco*/
  leDadosNoB(arq, &no_aux); /*Insere dados do nó atual na variável "no_aux"*/

  for(posicao = 0; posicao < (ORDEM-1) && no_aux.elementos[posicao].C != -1 && elem->C > no_aux.elementos[posicao].C; posicao++); /*Procura nó filho em que a chave deve ser inserida*/

  RETORNO = insercao_recursivo(arq, elem, &elemInf, &RRNInf, no_aux.P[posicao], RRNproxNo, cabB); /*chama função recursivamente para nó filho*/

  if(RETORNO == NAO_PROMOCAO) /*Se nenhum elemento foi promovido, não há mais nada para fazer*/
    return NAO_PROMOCAO;
  
  else if(no_aux.nroChavesNo != (ORDEM-1)) { /*Se há espaço para inserir o elemento no nó atual*/
    insereElem(&elemInf, &no_aux, RRNInf, ORDEM-1); /*Insere elemento no nó*/
    fseek(arq, (RRN+1)*TamPagDiscoB, SEEK_SET); /*acessa nó a ser reescrito no arquivo de indices. (RRN+1) pois o cabeçalho tem o tamanho de 1 página de disco*/
    no_aux.nroChavesNo++;
    imprimeNoB(arq, &no_aux);
    cabB->nroChavesTotal++;
    return NAO_PROMOCAO;
  }

  else { /*Se não ha espaço no nó, executa "split"*/
    split(&elemInf, RRNInf, &no_aux, elemPromo, filhoDirPromo, &no_novo, RRNproxNo, cabB);

    /*escreve no_aux no nó atual*/
    fseek(arq, TamPagDiscoB*(RRN+1), SEEK_SET);
    imprimeNoB(arq, &no_aux);

    /*escreve novo_no no nó de RRN filhoDirPromo*/
    fseek(arq, TamPagDiscoB*(*filhoDirPromo+1), SEEK_SET);
    imprimeNoB(arq, &no_novo);

    return PROMOCAO;
  }
}

/*Atribui a chave e o RRN do registro buscado (no arquivo de dados) no elemento (a ser inserida no arquivo de índices)*/
void leElemento(FILE *arquivo_entrada, elemento *elem, const int RRN) {
  fseek(arquivo_entrada, TAM_PagDisco + (RRN*TAM_registro) + (sizeof(char) + sizeof(int)), SEEK_SET); //vai para idConecta do registro de RRN determinado
  fread(&(elem->C), sizeof(int), 1, arquivo_entrada); //copia idConecta para elemento
  elem->Pr = RRN; //copia RRN para elemento
}

/*Insere a primeira chave no arquivo de índices*/
void inserePrimeiraChave(FILE *arquivo_entrada, FILE *arquivo_saida, int *RRN, cabecalhoB *cabB) {
  elemento elem;
  char removido = '1';

  /*procura o primeiro registro não removido*/
  fseek(arquivo_entrada, TAM_PagDisco, SEEK_SET);
  while(removido != '0') {
    fread(&removido, sizeof(char), 1, arquivo_entrada);
    if(removido != '0') {
      fseek(arquivo_entrada, TAM_registro-sizeof(char), SEEK_CUR);
      (*RRN)++;
    }
  }

  leElemento(arquivo_entrada, &elem, *RRN);

  No *no_aux = criaNo();
  no_aux->folha = '1';
  no_aux->nroChavesNo = 1;
  no_aux->alturaNo = 1;
  no_aux->RRNdoNo = 0;
  insereElem(&elem, no_aux, -1, ORDEM-1);
  imprimeNoB(arquivo_saida, no_aux);
  
  /*atualiza cabeçalho do arquivo de índices*/
  cabB->noRaiz = 0;
  cabB->nroChavesTotal = 1;
  cabB->RRNproxNo = 1;
  cabB->alturaArvore = 1;
  atualizaCabecalhoB(cabB, arquivo_saida);

  destroiNo(&no_aux);
  (*RRN)++;
}

/*Cria nó com os cammpos de um nó raíz após o primeirp split*/
void criaNoRaiz(elemento elem, int filhoEsq, int filhoDir, int RRN, int altura, No *raiz) { 
  int i;
  for(i = 0; i < (ORDEM-1); i++) {
    raiz->elementos[i].Pr = -1;
    raiz->elementos[i].C = -1;
    raiz->P[i] = -1;
  }
  raiz->P[i] = -1;


  raiz->elementos[0].C = elem.C;
  raiz->elementos[0].Pr = elem.Pr;
  raiz->P[0] = filhoEsq;
  raiz->P[1] = filhoDir;
  raiz->folha = '0';
  raiz->nroChavesNo = 1;
  raiz->alturaNo = altura;
  raiz->RRNdoNo = RRN;
}