#include "float_vector.h"
#include <stdio.h>

int main(void) {
	FloatVector *vec = vector_create(1);

	vector_append(vec, 1);
	vector_append(vec, 2);

	vector_print(vec);

	vector_destroy(&vec);

	return(0);
}