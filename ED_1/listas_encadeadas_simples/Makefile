all: simple_list

run:
	./simple_list

simple_linked_list.o: simple_linked_list.c
	gcc -c simple_linked_list.c -o simple_linked_list.o

test_list.o: test_list.c
	gcc -c test_list.c -o test_list.o

simple_list: simple_linked_list.o test_list.o
	gcc simple_linked_list.o test_list.o -o simple_list

clean:
	rm *.o
	rm simple_list