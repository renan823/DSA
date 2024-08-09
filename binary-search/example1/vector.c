#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

struct vector {
	int size;
	int capacity;
	ITEM *data;
};

void *_allocate(int size, long int type) {
	void *vec;

	if ((vec = (void *) malloc(size * type)) == NULL) {
		exit(1);
	}

	return(vec);
}

/*
*/
int _binary_search(Vector *vec, ITEM value, int begin, int end) {
	int middle = (int) (begin + end) / 2;

	if (begin <= end) {
		if (vec->data[middle] == value) {
			return middle;
		} 

		if (value > vec->data[middle]) {
			return _binary_search(vec, value, middle+1, end);
		} else {
			return _binary_search(vec, value, begin, middle-1);
		}
	} else {
		return(-1); //not found
	}
}

//===================================================================

/*
@brief Create a new vector (alocating memory for it).

@param capacity //vector total capacity.

@return Vector* //the created vector.
*/
Vector *create_vector(int capacity) {
	Vector *vec = (Vector *) _allocate(1, sizeof(Vector));

	vec->size = 0;
	vec->capacity = capacity;
	vec->data = (ITEM *) _allocate(capacity, sizeof(ITEM));

	return(vec);
}

/*
@brief Destroy a created vector (using free for it).

@param vec //vector memory adress.

@return void.
*/
void destroy_vector(Vector **vec) {
	free((*vec)->data);
	free(*vec);
}

/*
@brief Insert the specified value (if the vector isn't full) while mantaining the order.

@param vec //vector to add the value.
@param valu //the value to be added.

@return void.
*/
void vector_insert(Vector *vec, ITEM value) {
	if (vec->size < vec->capacity) {
		if (vec->size == 0) {
			vec->data[0] = value;
			vec->size++;
		} else {
			int pos;

			for(int i = 0; i <= vec->size-1; i++) {
				if (vec->data[i] <= value) {
					pos = i+1;
				} else {
					break;
				}
			}

			for(int i = vec->size-1; i >= pos; i--) {
				vec->data[i+1] = vec->data[i];
			}

			vec->data[pos] = value;
			vec->size++;
		}
	}
}

/*
@brief Remove the specified value (if it's in the vector) while mantaining the order.

@param vec //vector to remove the value.
@param value //the value to be removed.

@return void.
*/
void vector_remove(Vector *vec, ITEM value) {
	int pos = _binary_search(vec, value, 0, vec->size);

	if (pos != -1) {
		for(int i = pos; i <= vec->size; i++) {
			vec->data[i] = vec->data[i+1];
		}

		vec->size--;
	}
}

/*
@brief Look for the value position in the vector. If the value isn't found, -1 is returned.

@param vec //vector to search.
@param value //value to find position.

@return position //value position in the vector.
*/
int vector_search(Vector *vec, ITEM value) {
	//could be sequencial search
	return _binary_search(vec, value, 0, vec->size);
}

/*
@brief Print vector info.

@param vec //vector to print.

@return void.
*/
void vector_print(Vector *vec) {
	printf("Vector {\n");

	printf("  size: %d\n", vec->size);
	printf("  capacity: %d\n  [ ", vec->capacity);

	for (int i = 0; i < vec->size; i++) {
		printf("%f ", vec->data[i]);
	}
	printf("]\n}\n");
}

