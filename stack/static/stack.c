#include "stack.h"
#include "item.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct stack {
    int size;
    ITEM* items[MAX_CAPACITY];
};

STACK* stack_create() {
    STACK* s = (STACK*) malloc(sizeof(STACK));

    if (s != NULL) {
        s->size = 0;
    }

    return(s);
}

void stack_destroy(STACK** stack) {
    if (*stack == NULL) {
        return;
    }

    for (int i = 0; i < (*stack)->size; i++) {
        item_destroy(&(*stack)->items[i]);
    }

    free(*stack);
    *stack = NULL;
}

bool stack_is_full(STACK* stack) {
    if (stack == NULL) {
        return(true);
    }

    return(stack->size == MAX_CAPACITY);
}

bool stack_is_empty(STACK* stack) {
    if (stack == NULL) {
        return(false);
    }

    return(stack->size == 0);
}

bool stack_push(STACK* stack, ITEM* value) {
    if (stack_is_full(stack)) {
        return(false);
    }

    stack->items[stack->size] = value;
    stack->size++;

    return(true);
}

ITEM* stack_pop(STACK* stack) {
    if (stack_is_empty(stack)) {
        return(NULL);
    }

    stack->size--;

    ITEM* item = stack->items[stack->size];
    stack->items[stack->size] = NULL;

    return(item);
}

ITEM* stack_peek(STACK* stack) {
    if (stack_is_empty(stack)) {
        return(NULL);
    }

    return(stack->items[stack->size-1]);
}

int stack_size(STACK* stack) {
    if (stack == NULL) {
        return(-1);
    }

    return(stack->size);
}

void stack_print(STACK* stack) {
    if (stack == NULL) {
        return;
    }

    printf("STACK {\n");
    printf(" size: %d\n", stack->size);
    printf(" items (keys): [ ");

    for (int i = 0; i < stack->size; i++) {
        printf("%d ", item_get_key(stack->items[i]));
    }

    printf("]\n");
    printf("}\n");
}