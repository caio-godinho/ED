#include "ao_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//PARA TESTAR, É POSSÍVEL USAR SCANF NOMRAL E O COMANDO     ./(exe) < (arquivo com entrada)
//PARA COLOCAR A SAÍDA NOS ARQUIVOS DE SAÍDA, UTILIZE       ./(exe) > (arquivo que recebe saída)
//PARA COMPARAR SAÍDA OBTIDA E SAÍDA ESPERADA, USAR         diff (arquivo_com_saída_obtida) (arquivo_com_saída_esperada)

int main(int argc, char *argv[]){ 
    FILE *f = fopen("entrada2.txt", "r");

    List *L = create_list();

    char cmd[12];
    fscanf(f,"%s", cmd);

    while(strcmp(cmd, "para") != 0){//strcmp retorna 0 se strings foram iguais
        int serial;

        if(strcmp(cmd, "add") == 0){
            char name[20];
            float price;
            fscanf(f, "%d %s %f", &serial, name, &price);
            List_add_node_last(L, serial, name, price);
        }

        else if(strcmp(cmd, "acessa") == 0){
            fscanf(f, "%d", &serial);
            List_acessa(L, serial);
        }
        
        fscanf(f, "%s", cmd);
    }

    List_print_serial(L);
    destroy_list(L);
    free(f);

    return 0;
}