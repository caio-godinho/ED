all: list

run:
	./list

list: ao_list.o main_list.o
	gcc ao_list.o main_list.o -o list

ao_list.o: ao_list.c
	gcc -c ao_list.c -o ao_list.o

main_list.o: main_list.c
	gcc -c main_list.c -o main_list.o

clean:
	rm *.o
	rm list