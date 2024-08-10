all: type.o stack.o main.o
	gcc main.o type.o stack.o -o stacks -std=c99 -Wall -pedantic-errors
type.o:
	gcc -c type.c
stack.o:
	gcc -c stack.c
main.o:
	gcc -c main.c
clean:
	rm *.o stacks