#include "float_vector.h"
#include <stdio.h>
#include <stdlib.h>

struct float_vector {
	int capacity;
	int size;
	float *data;
};

void *_allocate(int size, long int type) {
	void *vec;

	if ((vec = (void *) malloc(size * type)) == NULL) {
		printf("Error: not enough memory to alocate!\n");
		exit(1);
	}

	return(vec);
}

float *_reallocate(float *data, int size) {
	float *new_data;

	if ((new_data = realloc(data, size * sizeof(float))) == NULL) {
		printf("Error: not enough memory to alocate!\n");
		exit(1);
	}

	return(new_data);
}

/*
@brief Create a new vector (alocating memory for it).

@param capacity //vector total capacity.

@return FloatVector* //the created vector.
*/
FloatVector *vector_create(int capacity) {
	FloatVector *vec = (FloatVector *) _allocate(1, sizeof(FloatVector));

	vec->capacity = capacity;
	vec->size = 0;
	vec->data = (float *) _allocate(capacity, sizeof(float));

	return(vec);
}

/*
@brief Destroy a created vector (using free for it).

@param vec //vector memory adress.

@return void.
*/
void vector_destroy(FloatVector **vec_ref) {
    if (vec_ref == NULL || *vec_ref == NULL) {
        return;
    }

    FloatVector *vec = *vec_ref;

    if (vec->data != NULL) {
        free(vec->data);
    }

    free(vec);
    *vec_ref = NULL;
}


/*
@brief Return the vector size.

@param vec //vector to get size.

@return size //vector size.
*/
int vector_size(const FloatVector *vec) {
	return(vec->size);
}

/*
@brief Return the vector capacity.

@param vec //vector to get capacity.

@return capacity //vector capacity.
*/
int vector_capacity(const FloatVector *vec) {
	return(vec->capacity);
}

/*
@brief Return the value at the specified index. Will throw an error if the index is out of vector bounds.

@param vec //vector to get value.
@param index //value index.

@return value //the value at the specified index.
*/
float vector_at(const FloatVector *vec, int index) {
	if (index > vec->size-1 || index < 0) {
		printf("Error: index out of bounds!");
		exit(1);
	}

	return(vec->data[index]);
}

/*
@brief Return the value at the specified index. Doesn't verify vectors bounds.

@param vec //vector to get value.
@param index //value index.

@return value //the value at the specified index.
*/
float vector_get(const FloatVector *vec, int index) {
	return(vec->data[index]);
}

/*
@brief Append a value at the last position of vector. The vector will be expanted if it's full.

@param vec //vector to append value.
@param value //value to be appended.

@return void.
*/
void vector_append(FloatVector *vec, float value) {
	if (vec->capacity == vec->size) {
		//expand by 5
		vec->capacity += 5;

		vec->data = _reallocate(vec->data, vec->capacity);
	}

	vec->data[vec->size] = value;
	vec->size++;
}

/*
@brief Print the vector info.

@param vec //vector to print.

@return void.
*/
void vector_print(const FloatVector *vec) {
	printf("FloatVector {\n");

	printf("  size: %d\n", vec->size);
	printf("  capacity: %d\n  [ ", vec->capacity);

	for (int i = 0; i < vec->size; i++) {
		printf("%f ", vec->data[i]);
	}
	printf("]\n}\n");
}