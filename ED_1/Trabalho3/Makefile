all: circuito

run:
	./circuito

circuito: main.o circuito.o
	gcc main.o circuito.o -o circuito

main.o: main.c
	gcc -c main.c -o main.o

circuito.o: circuito.c
	gcc -c circuito.c -o circuito.o