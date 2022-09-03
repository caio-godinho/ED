all: arq

run:
	./arq

arq.o: arq.c
	gcc -o arq.o -c arq.c

func.o: func.c
	gcc -o func.o -c func.c

arq: arq.o func.o
	gcc -o arq func.o arq.o

clean:
	rm *.o
	rm arq