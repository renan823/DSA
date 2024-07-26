all: float_vector.o main.o
	gcc main.o float_vector.o -o vectors -std=c99 -Wall -pedantic-errors
float_vector.o:
	gcc -c float_vector.c
main.o:
	gcc -c main.c
clean:
	rm *.o vectors