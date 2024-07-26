#include "float_vector.h"
#include <stdio.h>

int main(void) {
	FloatVector *vec = create(1);

	append(vec, 1);
	append(vec, 2);

	print(vec);

	destroy(&vec);

	return(0);
}