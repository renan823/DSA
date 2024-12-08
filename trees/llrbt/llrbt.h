#ifndef LLRBT_H
    #define LLRBT_H

    #include "item.h"
    #include <stdbool.h>

    typedef struct llrbt LLRBT;

    LLRBT *llrbt_create(void);
    void llrbt_destroy(LLRBT **tree);

    bool llrbt_insert(LLRBT *tree, ITEM *item);
    ITEM *llrbt_remove(LLRBT *tree, int key);
    ITEM *llrbt_search(LLRBT *tree, int key);

    void llrbt_print_pre_order(LLRBT *tree);
    void llrbt_print_in_order(LLRBT *tree);
    void llrbt_print_post_order(LLRBT *tree);
#endif