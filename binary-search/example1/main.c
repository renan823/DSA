#include <stdio.h>
#include "vector.h"

int main(void) {
	Vector *vec = create_vector(10);

	vector_insert(vec, 30);
	vector_insert(vec, 0);
	vector_insert(vec, 11);
	vector_insert(vec, 25);
	vector_insert(vec, 5);
	vector_insert(vec, 10);	
	vector_insert(vec, 22);

	vector_print(vec);

	vector_remove(vec, 11);

	vector_print(vec);

	printf("returned index: %d\n", vector_search(vec, 25));
	printf("returned index: %d\n", vector_search(vec, 27));

	destroy_vector(&vec);
}