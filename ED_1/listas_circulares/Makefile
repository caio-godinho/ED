run:
	./list

all: list

circ_list.o: circ_list.c
	gcc -c circ_list.c -o circ_list.o

main.o: main.c
	gcc -c main.c -o main.o

list: circ_list.o main.o
	gcc main.o circ_list.o -o list

clean:
	rm *.o
	rm list