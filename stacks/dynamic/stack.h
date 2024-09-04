#ifndef STACK_H
    #define STACK_H

    #include "type.h"

    #include <stdbool.h>

    typedef struct stack Stack;
    typedef struct node Node;

    Stack *create_stack();
    void destroy_stack(Stack *stack);

    bool stack_is_empty(Stack *stack);

    void stack_push(Stack *stack, Type value);
    Type *stack_pop(Stack *stack);
    Type *stack_peek(Stack *stack);
    int stack_size(Stack *stack);

    void stack_print(Stack *stack);
#endif