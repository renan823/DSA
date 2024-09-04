#include <stdlib.h>
#include <stdio.h>

#include "item.h"

struct item {
    int key;
    void *value;
};

ITEM *item_create(int key, void *value) {
    ITEM *item = (ITEM *) malloc(sizeof(struct item)); 

    if (item != NULL) {
        item->key = key;
        item->value = value;
    }

    return item;
}

void item_destroy(ITEM **item) {
    if (item != NULL && *item != NULL) {
        free(*item);
        *item = NULL;
    }
}

int item_get_key(ITEM *item) {
    if (item != NULL) {
        return item->key;  
    }

    return -1;  
}

void item_set_key(ITEM *item, int key) {
    if (item != NULL) {
        item->key = key;  
    }
}

void *item_get_value(ITEM *item) {
    if (item != NULL) {
        return item->value;  
    }

    return NULL;  
}

void item_set_value(ITEM *item, void *value) {
    if (item != NULL) {
        item->value = value;  
    }
}
