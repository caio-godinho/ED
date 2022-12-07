#ifndef __ARVOREB__
#define __ARVOREB__

#include <stdio.h>

//Ordem da árvore-B
#define ORDEM 5

//Caractere utilizado para representar o lixo
#define LIXOB  "$"

//Tamanho das páginas de disco, do registro de cabeçalho e dos nós
#define TamPagDiscoB 65

//Quantidade de bytes preechidos pelos campos do cabecalhoB
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

No *criaNo(int numElem, int numPont);
void imprimeNoB(FILE *arq, No *no);
void escreveCabecalhoB(FILE *arq, cabecalhoB *cab);
void criaCabecalhoB(FILE *arq, cabecalhoB *cab);
int insercao_recursivo(FILE *arq, elemento *elem, elemento *elemPromo, int *filhoDirPromo, const int RRN, int *RRNproxNo, cabecalhoB *cabB);
void leElemento(FILE *arquivo_entrada, elemento *elem, const int RRN);
void inserePrimeiraChave(FILE *arquivo_entrada, FILE *arquivo_saida, int *RRN, cabecalhoB *cabB);
void criaNoRaiz(elemento elem, int filhoEsq, int filhoDir, int RRN, int altura, No *raiz);
void leCabecalhoB(cabecalhoB *cab, FILE *arq);

#endif