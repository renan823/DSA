#include "stack.h"
#include "type.h"

#include <stdio.h>

int main(void) {
    Stack *s = create_stack(4);

    stack_pop(s);

    stack_push(s, 17);
    stack_print(s);
    stack_push(s, 9);
    stack_push(s, 13);
    stack_print(s);
    stack_push(s, 4);
    stack_push(s, 11);

    printf("Is empty ? %s\n", stack_is_empty(s) ? "Yes" : "No");

    stack_print(s);

    stack_pop(s);

    stack_print(s);

    destroy_stack(s);

    return(0);
}