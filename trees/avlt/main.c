#include "item.h"
#include "avlt.h"

#include <stdio.h>

int main(void) {
    AVLT *tree = avlt_create();

    avlt_insert(tree, item_create(33, NULL));
    avlt_insert(tree, item_create(2, NULL));
    avlt_insert(tree, item_create(24, NULL));
    avlt_insert(tree, item_create(7, NULL));
    avlt_insert(tree, item_create(42, NULL));
    avlt_insert(tree, item_create(1, NULL));

    avlt_print_in_order(tree);

    avlt_remove(tree, 33);

    printf("\n");
    avlt_print_in_order(tree);

    ITEM *item = avlt_search(tree, 5);
    if (item != NULL) {
        printf("%d\n", item_get_key(item));
    } else {
        printf("Not found\n");
    }

    avlt_print_post_order(tree);
    printf("\n");
    avlt_print_pre_order(tree);
    
    avlt_destroy(&tree);
    item_destroy(&item);

    return(0);
}