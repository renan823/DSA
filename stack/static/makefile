all: stack.o main.o
	gcc main.o item.o stack.o -o stacks -std=c99 -Wall -pedantic-errors

stack.o:
	gcc -c stack.c

main.o:
	gcc -c main.c

run:
	./stacks
	
clean:
	rm main.o stack.o stacks