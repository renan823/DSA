#ifndef ITEM_H
    #define ITEM_H

    typedef struct item ITEM;

    ITEM* item_create(int key, void *value);
    void item_destroy(ITEM **item);

    int item_get_key(ITEM *item);
    void item_set_key(ITEM *item, int key);

    void *item_get_value(ITEM *item);
    void item_set_value(ITEM *item, void *value);
#endif