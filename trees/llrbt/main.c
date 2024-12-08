#include "item.h"
#include "llrbt.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    LLRBT *tree = llrbt_create();

    llrbt_insert(tree, item_create(2, NULL));

    llrbt_print_in_order(tree);
    
    llrbt_insert(tree, item_create(13, NULL));
    llrbt_insert(tree, item_create(5, NULL));
    llrbt_insert(tree, item_create(8, NULL));
    llrbt_insert(tree, item_create(42, NULL));
    llrbt_insert(tree, item_create(7, NULL));

    printf("\n");
    llrbt_print_in_order(tree);

    llrbt_remove(tree, 8);
    printf("\n");

    llrbt_print_post_order(tree);
    
    llrbt_destroy(&tree);

    return(0);
}