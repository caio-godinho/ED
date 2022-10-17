all:  codigo

run:
	./codigo

codigo: main.o  Opcao1.o  Opcao2.o  Opcao3.o  FuncoesComuns.o FuncoesFornecidas.o
	gcc FuncoesFornecidas.o FuncoesComuns.o Opcao1.o Opcao2.o Opcao3.o main.o -o codigo -march=native 

main.o: main.c
	gcc -c main.c -o main.o -march=native 

Opcao1.o: Opcao1.c
	gcc -c Opcao1.c -o Opcao1.o -march=native 

Opcao2.o: Opcao2.c
	gcc -c Opcao2.c -o Opcao2.o -march=native 

Opcao3.o: Opcao3.c
	gcc -c Opcao3.c -o Opcao3.o -march=native 

FuncoesComuns.o: FuncoesComuns.c
	gcc -c FuncoesComuns.c -o FuncoesComuns.o -march=native 

FuncoesFornecidas.o: FuncoesFornecidas.c
	gcc -c FuncoesFornecidas.c -o FuncoesFornecidas.o -march=native 
