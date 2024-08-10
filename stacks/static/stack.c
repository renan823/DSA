#include "stack.h"
#include "type.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct stack {
    int capacity;
    int size;
    Type *data;
};

void *_allocate(int items, unsigned long int size) {
    void *memory;

    if ((memory = malloc(items * size)) == NULL) {
        fprintf(stderr, "ERROR: Not enough memory!\n");
        exit(EXIT_FAILURE);
    }

    return(memory);
}

Stack *create_stack(int capacity) {
    Stack *stack = (Stack *) _allocate(1, sizeof(Stack));

    stack->capacity = capacity;
    stack->size = 0;
    stack->data = (Type *) _allocate(capacity, sizeof(Type));

    return(stack);
}

void destroy_stack(Stack *stack) {
    free(stack->data);
    free(stack);
}

bool stack_is_full(Stack *stack) {
    return(stack->size == stack->capacity);
}

bool stack_is_empty(Stack *stack) {
    return(stack->size == 0);
}
    
void stack_push(Stack *stack, Type value) {
    if (stack_is_full(stack)) {
        fprintf(stderr, "ERROR: The stack is full!\n");
        return;
    }

    stack->data[stack->size] = value;
    stack->size++;
}

Type *stack_pop(Stack *stack) {
    if (stack_is_empty(stack)) {
        fprintf(stderr, "ERROR: The stack is empty!\n");
        return(NULL);
    }

    stack->size--;
    return(&(stack->data[stack->size]));
}

Type *stack_peek(Stack *stack) {
    if (stack_is_empty(stack)) {
        fprintf(stderr, "ERROR: The stack is empty!\n");
        return(NULL);
    }

    return(&(stack->data[stack->size-1]));
}

int stack_size(Stack *stack) {
    return(stack->size);
}