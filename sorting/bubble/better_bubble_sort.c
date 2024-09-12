#include <stdio.h>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void bubble(int *v, int n) {
	int swaps = 1;
	for (int i = 0; i < n && swaps > 0; i++) {
		swaps = 0;
		for (int j = 0; j < n-1-i; j++)  {
			if (v[j] > v[j+1]) {
				swap(&v[j], &v[j+1]);
				swaps++;
			}
		}
	};
}

int main(void) {
	int n = 6;
    int v[6] = {93, 0, 25, 2, 11, 53};

    bubble(v, n);

    for (int i = 0; i < n; i++) {
    	printf("%d\n", v[i]);
    }
}
