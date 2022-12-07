//Alunos: Caio Oliveira Godinho / (12731996) / Participação: 100% ; Guilherme Chiarotto de Moraes / (12745229) / Participação: 100%.

#include <stdio.h>
#include "Funcionalidade1.h"
#include "Funcionalidade2.h"
#include "Funcionalidade3.h"
#include "Funcionalidade4.h"
#include "Funcionalidade5.h"
#include "Funcionalidade6.h"
#include "Funcionalidade7.h"
#include "Funcionalidade8.h"
#include "Funcionalidade9.h"
#include "Funcionalidade10.h"

int main(void) {
  int funcionalidade;
  scanf("%d", &funcionalidade);
  switch (funcionalidade) {
    case 1:
      funcionalidade1();
      break;

    case 2:
      funcionalidade2();
      break;

    case 3:
      funcionalidade3();
      break;

    case 4:
      funcionalidade4();
      break;

    case 5:
      funcionalidade5();
      break;

    case 6:
      funcionalidade6();
      break;

    case 7:
      funcionalidade7();
      break;

    case 8:
      funcionalidade8();
      break;
    
    case 9:
      funcionalidade9();
      break;

    case 10:
      funcionalidade10();
      break;

    default:
      printf("Funcionalidade invalida.\n");
  }
  
  return 0;
}