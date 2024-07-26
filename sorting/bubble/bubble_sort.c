#include <stdio.h>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void bubble(int *v, int n) {
	int swaps;
	do {
		swaps = 0;
		for (int i = 0; i < n-1; i++)  {
			if (v[i] > v[i+1]) {
				swap(&v[i], &v[i+1]);
				swaps++;
			}
		}
	} while (swaps);
}

int main(void) {
	int n = 6;
    int v[6] = {93, 0, 25, 2, 11, 53};

    bubble(v, n);

    for (int i = 0; i < n; i++) {
    	printf("%d\n", v[i]);
    }
}

/*
Bubble sorting is a simple method for sorting numbers.
It's called "bubble" because it "floats" a number to another position,
swapping values until no more swaps are necessary.
*/