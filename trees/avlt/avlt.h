#ifndef AVLT_H
    #define AVLT_H

    #include "item.h"
    #include <stdbool.h>

    typedef struct avlt AVLT;

    AVLT *avlt_create(void);
    void avlt_destroy(AVLT **tree);

    bool avlt_insert(AVLT *tree, ITEM *item);
    ITEM *avlt_remove(AVLT *tree, int key);
    ITEM *avlt_search(AVLT *tree, int key);

    void avlt_print_pre_order(AVLT *tree);
    void avlt_print_in_order(AVLT *tree);
    void avlt_print_post_order(AVLT *tree);
#endif