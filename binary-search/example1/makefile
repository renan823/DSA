all: vector.o main.o
	gcc main.o vector.o -o vectors -std=c99 -Wall -pedantic-errors
float_vector.o:
	gcc -c vector.c
main.o:
	gcc -c main.c
clean:
	rm *.o vectors