all: list

run: 
	./list

doubly_linked_list.o: doubly_linked_list.c
	gcc -c doubly_linked_list.c -o doubly_linked_list.o

doubly_list.o: doubly_list.c
	gcc -c doubly_list.c -o doubly_list.o

list: doubly_linked_list.o doubly_list.o
	gcc doubly_linked_list.o doubly_list.o -o list

clean: 
	rm *.o
	rm list
