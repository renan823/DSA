all: stack.o main.o
	gcc stack.o main.o -Wall -std=c99 -o stack

stack.o:
	gcc -c stack.c

main.o:
	gcc -c main.c

run:
	./stack

clean:
	rm *.o stack

