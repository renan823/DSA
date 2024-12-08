#include "stack.h"
#include "item.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

strcut node {
    ITEM* value;
    NODE* prev;
}

struct stack {
    int size;
    NODE* top;
};

STACK* stack_create() {
    STACK* s = (STACK*) malloc(sizeof(STACK));

    if (s != NULL) {
        s->size = 0;
        s->top = NULL;
    }

    return(s);
}

void stack_destroy(STACK** stack) {
    if (*stack == NULL) {
        return;
    }

    //

    free(*stack);
    *stack = NULL;
}

bool stack_is_full(STACK* stack) {
    if (stack == NULL) {
        return(true);
    }

    //full -> no memory to allocate for new nodes

    NODE* node = (NODE*) malloc(sizeof(NODE));

    if (node == NULL) {
        return(true);
    }

    free(node);
    return(false);
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