all: lista

run:
	./lista

funcoes.o: funcoes.c
	gcc -o funcoes.o -c funcoes.c

lista_intercalada_ordenada.o: lista_intercalada_ordenada.c
	gcc -o lista_intercalada_ordenada.o -c lista_intercalada_ordenada.c

lista: funcoes.o lista_intercalada_ordenada.o
	gcc -o lista funcoes.o lista_intercalada_ordenada.o


