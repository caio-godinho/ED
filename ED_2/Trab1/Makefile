all: exec

run:
	./exec

funcoes.o: funcoes.c
	gcc -c funcoes.c -o funcoes.o

main.o: main.c
	gcc -c main.c -o main.o

exec: funcoes.o main.o
	gcc funcoes.o main.o -o exec