all: item.o llrbt.o main.o
	gcc item.o llrbt.o main.o -Wall -std=c99 -o ex 

item.o:
	gcc -c item.c 

llrbt.o:
	gcc -c llrbt.c 

main.o:
	gcc -c main.c 

run:
	./ex

clean:
	rm *.o ex