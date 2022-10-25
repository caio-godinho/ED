#include<stdio.h>

#define TAM_PagDisco 960
#define TAM_cabecalho 21

typedef struct { 
  //registro de cabecalho
  char status;
  int topo;
  int proxRRN;
  int nroRegRem;
  int nroPagDisco;
  int qttCompacta;

} cabecalho;


typedef struct {
  //Campos de controle para gerenciamento de registros removidos
  char removido[2];
  int encadeamento;

  //Campos de tamanho variavel
  int idConecta;
  char siglaPais[3];
  int idPoPsConectado;
  char unidadeMedida[2];
  int velocidade;

  //Campos de tamanho fixo
  char nomePoPs[100];
  char nomePais[100];

} registro;
