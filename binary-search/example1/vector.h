typedef struct vector Vector;
typedef float ITEM;

Vector *create_vector(int capacity);
void destroy_vector(Vector **vec);
void vector_insert(Vector *vec, ITEM value);
void vector_remove(Vector *vec, ITEM value);
int vector_search(Vector *vec, ITEM value);
void vector_print(Vector *vec);