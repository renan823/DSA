all: item.o avlt.o main.o
	gcc item.o avlt.o main.o -Wall -std=c99 -o ex 

item.o:
	gcc -c item.c 

avlt.o:
	gcc -c avlt.c 

main.o:
	gcc -c main.c 

run:
	./ex

clean:
	rm *.o ex