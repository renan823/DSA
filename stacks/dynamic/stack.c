#include "stack.h"
#include "type.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct node {
    Type value;
    Node *next;
};

struct stack {
    Node *top;
    int size;
};

void *_allocate(int items, unsigned long int size) {
    void *memory;

    if ((memory = malloc(items * size)) == NULL) {
        fprintf(stderr, "ERROR: Not enough memory!\n");
        exit(EXIT_FAILURE);
    }

    return(memory);
}

void _destroy_node(Node *node) {
    if (node->next == NULL) {
        return;
    }

    _destroy_node(node->next);
    free(node->next);
}

Stack *create_stack() {
    Stack *stack = (Stack *) _allocate(1, sizeof(Stack));

    stack->size = 0;
    stack->top = NULL;

    return(stack);
}

void destroy_stack(Stack *stack) {
    _destroy_node(stack->top);

    free(stack->top);
    free(stack);
}

bool stack_is_empty(Stack *stack) {
    return(stack->top == NULL);
}

void stack_push(Stack *stack, Type value) {
    Node *node = (Node *) _allocate(1, sizeof(Node));

    node->value = value;
    node->next = stack->top;

    stack->top = node;
}

Type *stack_pop(Stack *stack) {
    if (stack_is_empty(stack)) {
        fprintf(stderr, "ERROR: The stack is empty!\n");
        return(NULL);
    }

    Node *top = stack->top;
    Type *value = &(top->value);

    stack->top = top->next;

    free(top);

    return(value);
}

Type *stack_peek(Stack *stack) {
    return(&(stack->top->value));
}

int stack_size(Stack *stack) {
    return(stack->size);
}

void stack_print(Stack *stack) {
    Node *node = stack->top;

    printf("Stack {\n");

    do {//adjust % operator to item type!
        printf("   %f\n", node->value);
        
        node = node->next;
    } while(node != NULL);

    printf("}\n");
}