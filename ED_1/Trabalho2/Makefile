all: exe

run:
	./exe

exe: main.o list.o
	gcc main.o list.o -o exe

list.o: list.c
	gcc -c list.c -o list.o

main.o: main.c
	gcc -c main.c -o main.o