#include "FuncoesFornecidas.h"
#include "Opcao1.h"
#include "Opcao2.h"
#include "Opcao3.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int opcao;
  scanf("%d ", &opcao); //Le opcao de entrada

  char nome_arquivo[30];
  readline(nome_arquivo); //Le nome do arquivo de entrada

  if(opcao == 1)
    Opcao1(nome_arquivo);
  else if(opcao == 2)
    Opcao2(nome_arquivo);
  else
    Opcao3(nome_arquivo);
  
  return 0;
}