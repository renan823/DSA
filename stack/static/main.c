#include "stack.h"
#include "item.h"

#include <stdio.h>

int main(void) {
    STACK* s = stack_create();

    char c1 = 'O';
    char c2 = 'i';
    char c3 = '!';

    stack_push(s, item_create(1, &c1));
    stack_push(s, item_create(2, &c2));
    stack_push(s, item_create(3, &c3));

    stack_print(s);

    stack_destroy(&s);

    return(0);
}