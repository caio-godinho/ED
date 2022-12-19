//Alunos: Caio Oliveira Godinho / (12731996) / Participação: 100% ; Guilherme Chiarotto de Moraes / (12745229) / Participação: 100%.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaEncadeadaVertice.h"
#include "ListaEncadeadaAresta.h"
#include "Grafo.h"
#include "Funcionalidade11.h"
#include "Funcionalidade12.h"
#include "Funcionalidade14.h"

int main(int argc, char *argv[]) {
  int funcionalidade;
  scanf("%d", &funcionalidade);
  switch (funcionalidade) {
    case 11:
      funcionalidade11();
      break;

    case 12:
      funcionalidade12();
      break;

    case 14:
      funcionalidade14();
      break;
    
    default:
      printf("Funcionalidade invalida.\n");
  }

  return 0;
}
