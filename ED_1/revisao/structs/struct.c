#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _livro{
    char titulo[100];
    unsigned int num_paginas;
    float preco; //Não existe unsigned float;
} Livro;
            //ou char nome[]
Livro *cria_livro(char *titulo, unsigned int paginas, float preco){//Criar ponteiro para struct, pois na heap tem mais espaço.
    Livro *livro = (Livro *) calloc(1, sizeof(Livro));

    strcpy(livro->titulo, titulo);
    livro->num_paginas = paginas;
    livro->preco = preco;

    return livro;
}

void print_livro(const Livro *livro){
    printf("Nome: %sNumero de  paginas: %u\nPreco: R$ %.2f\n", livro->titulo, livro->num_paginas, livro->preco);
    //Não precisa de /n após %s, pois ao ler a string digitada, ele também lê o "enter", que conta como um \n.
}

Livro *copy_livro(const Livro *livro){
    return cria_livro(livro->titulo, livro->num_paginas, livro->preco);
}

typedef struct _aluno{
    char nome[100];
    unsigned int idade;
    Livro *livro_favorito;
} Aluno;

Aluno *cria_aluno(char *nome, unsigned int idade, Livro *livro){
    Aluno *aluno = (Aluno *) calloc(1, sizeof(Aluno));
    strcpy(aluno->nome, nome);
    aluno->idade = idade;
    aluno->livro_favorito = copy_livro(livro);//Cria uma cópia do livro, para que as duas variáveis não apontem para o mesmo lugar.

    return aluno;
}

void print_aluno(const Aluno *aluno){
    printf("Nome: %s\n", aluno->nome);//usa printf, pois puts não aceita argumentos.
    printf("idade: %d\n", aluno->idade);
    puts("Livro favorito:");
    print_livro(aluno->livro_favorito);
}


int main(int argc, char *argv[]){
    char titulo[100];
    unsigned int paginas;
    float preco;
    puts("Nome do livro: ");//puts imprime uma string, mas não aceita argumentos, ou seja, ela não imprime variáveis.
    fgets(titulo, 100, stdin);//ou scanf
    puts("Numero de paginas e preco: ");
    scanf("%u %f", &paginas, &preco);

    Livro *meu_livro = cria_livro(titulo, paginas, preco);
    print_livro(meu_livro);
    puts("------------------------");

    char nome[100];
    int idade;
    printf("Nome do aluno: ");
    scanf("%s", nome);//ou fgets, mas com fgets da problema com pulo de linhas.
    printf("Idade do aluno: ");
    scanf("%d", &idade);

    Aluno *aluno = cria_aluno(nome, idade, meu_livro);
    print_aluno(aluno);

    free(meu_livro);
    free(aluno->livro_favorito);//Desalocar memória da cópia do livro.
    free(aluno);
}