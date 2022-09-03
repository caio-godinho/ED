#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _livro{
    char titulo[100];
    unsigned int num_paginas;
    float preco; //Não existe unsigned float;
} Livro;
          
void le_livro(char *titulo, unsigned int *paginas, float *preco){
    puts("Nome do livro: ");//puts imprime uma string, mas não aceita argumentos, ou seja, ela não imprime variáveis.
    getchar();//PARA LIMPAR O "\n" DO SCANF, SE NÃO ELE SERÁ LIDO PELO fgets().
    fgets(titulo, 100, stdin);//ou scanf, mas com scanf não da para usar espaço.
    puts("Numero de paginas e preco: ");
    scanf("%u %f", &(*paginas), &(*preco));
}

            //ou char nome[]
Livro *cria_livro(char *titulo, unsigned int paginas, float preco){//Criar ponteiro para struct, pois na heap tem mais espaço.
    Livro *livro = (Livro *) calloc(1, sizeof(Livro));

    strcpy(livro->titulo, titulo);
    livro->num_paginas = paginas;
    livro->preco = preco;

    return livro;
}

void print_livros(int n, Livro **livro){
    for(int i = 0; i < n; i++){
        printf("Nome: %sNumero de  paginas: %u\nPreco: R$ %.2f\n", livro[i]->titulo, livro[i]->num_paginas, livro[i]->preco);
        //Não precisa de /n após %s, pois ao ler a string digitada, ele também lê o "enter", que conta como um \n.
    }
}

void destroy(Livro **livros, int n){
    for(int i = 0; i < n; i++){
        free(livros[i]);
    }
    free(livros);
}

int main(int argc, char *argv[]){
    printf("Quantos livros voce quer? ");
    int n;
    scanf("%d", &n);

    Livro **meus_livros = (Livro **) calloc(n, sizeof(Livro *));//ponteiro para ponteiros que apontam para variáveis da struct
    char titulo[100];
    unsigned int paginas;
    float preco;

    for(int i = 0; i < n; i++){
        le_livro(titulo, &paginas, &preco);//lê as informações do livro
        meus_livros[i] = cria_livro(titulo, paginas, preco);//aloca espaço para o ponteiro e coloca as informações lidas nesse espaço.
    }
    
    print_livros(n, meus_livros);

    destroy(meus_livros, n);
}