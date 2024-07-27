typedef struct float_vector FloatVector;

FloatVector *vector_create(int capacity);
void vector_destroy(FloatVector **vec);
int vector_size(const FloatVector *vec);
int vector_capacity(const FloatVector *vec);
float vector_at(const FloatVector *vec, int index);
float vector_get(const FloatVector *vec, int index);
void vector_append(FloatVector *vec, float value);
void vector_set(FloatVector *vec, int index, float value);
void vector_print(const FloatVector *vec);