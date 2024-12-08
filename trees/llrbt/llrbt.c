#include "item.h"
#include "llrbt.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define RED 'r'
#define BLACK 'b'

// Structs
typedef struct llrbt_node LLRBT_NODE;

struct llrbt_node {
    ITEM *item;
    LLRBT_NODE *left;
    LLRBT_NODE *right;
    char color;
};

struct llrbt {
    LLRBT_NODE *root;
};

// Helpers

/*
    Allocate a new LLRBT node.
    If node isn't NULL, its values are initialized.
    The node starts with RED color.
    The created node is returned.
*/
LLRBT_NODE *_llrbt_create_node(ITEM *item) {
    LLRBT_NODE *node = (LLRBT_NODE*) malloc(sizeof(LLRBT_NODE));

    if (node != NULL) {
        node->left = NULL;
        node->right = NULL;
        node->color = RED;
        node->item = item;
    }

    return(node);
}

/*
    Recursivelly destroys LLRBT nodes.
    Starting from any node (usually the root), each child
    will be destroyed, freeing its memory space.
    Node's content (item) will also be destroyed.
*/
void _llrbt_destroy_node(LLRBT_NODE *root) {
    if (root == NULL) {
        return;
    }

    //post-order traversal
    _llrbt_destroy_node(root->left);
    _llrbt_destroy_node(root->right);

    item_destroy(&root->item);
    free(root);
}

/*
    Check if an LLRBT node is RED.
    If the node is NULL, return false (NULL nodes are BLACK).
    Otherwise, compare the color of the node to RED and return the result.
*/
bool _llrbt_is_red(LLRBT_NODE *node) {
    if (node == NULL) {
        return(false);
    }

    return(node->color == RED);
}

/*
    Check if an LLRBT node is BLACK.
    If the node is NULL, return true (NULL nodes are BLACK).
    Otherwise, compare the color of the node to BLACK and return the result.
*/
bool _llrbt_is_black(LLRBT_NODE *node) {
    if (node == NULL) {
        return(true);
    }

    return(node->color == BLACK);
}

/*
    Rotates an LLRBT node to the right.
    The newest affected node will be rotated to maintain the LLBRT balance.
    Rotation occurs by changing node's pointers.
    Their colors will also change.
*/
void _llrbt_rotate_right(LLRBT_NODE **root) {
    LLRBT_NODE *node = (*root)->left;

    // Rotate
    (*root)->left = node->right;
    node->right = *root;

    // Ajdust colors
    (*root)->color = node->color;
    node->color = RED;

    *root = node;
}

/*
    Rotates an LLRBT node to the left.
    The newest affected node will be rotated to maintain the LLBRT balance.
    Rotation occurs by changing node's pointers.
    Their colors will also change.
*/
void _llrbt_rotate_left(LLRBT_NODE **root) {
    LLRBT_NODE *node = (*root)->right;

    // Rotate
    (*root)->right = node->left;
    node->left = *root;

    // Adjust colors
    (*root)->color = node->color;
    node->color = RED;

    *root = node;
}

/*
    Switch LLRBT node colors.
    The color switch occurs to maintain the LLRBT balance.
*/
void _llrbt_switch_colors(LLRBT_NODE **root) {
    (*root)->color = RED;
    (*root)->left->color = BLACK;
    (*root)->right->color = BLACK;
}

/*
    Traverse through the LLRBT.
    Each node wil be visited in the order root -> left -> right.
*/
void _llrbt_pre_order_traversal(LLRBT_NODE *root) {
    if (root == NULL) {
        return;
    }

    printf("%d\n", item_get_key(root->item));
    _llrbt_pre_order_traversal(root->left);
    _llrbt_pre_order_traversal(root->right);
}

/*
    Traverse through the LLRBT.
    Each node wil be visited in the order left -> root -> right.
*/
void _llrbt_in_order_traversal(LLRBT_NODE *root) {
    if (root == NULL) {
        return;
    }

    _llrbt_in_order_traversal(root->left);
    printf("%d\n", item_get_key(root->item));
    _llrbt_in_order_traversal(root->right);
}

/*
    Traverse through the LLRBT.
    Each node wil be visited in the order left -> right -> root.
*/
void _llrbt_post_order_traversal(LLRBT_NODE *root) {
    if (root == NULL) {
        return;
    }

    _llrbt_post_order_traversal(root->left);
    _llrbt_post_order_traversal(root->right);
    printf("%d\n", item_get_key(root->item));
}

/*
    Swaps the root node with the left node with the highest value.
    Also adjusts pointers to avoid data loss.
*/
void _llrbt_swap_max_left(LLRBT_NODE **root, LLRBT_NODE **node) {
    if ((*root)->right->right != NULL) {
        _llrbt_swap_max_left(root, &(*root)->right);
    }

    (*root)->item = (*node)->item;

    LLRBT_NODE *temp = *node;
    *node = (*node)->left;

    free(temp);
}

/*
    Traverse through the LLRBT using binary search.
    The given key will be searched using shortest paths.
    The found node will be returned (NULL if it does not exists).
*/
ITEM *_llrbt_binary_search(LLRBT_NODE *root, int key) {
    if (root == NULL) {
        return(NULL);
    }

    if (item_get_key(root->item) > key) {
        return(_llrbt_binary_search(root->left, key));
    }

    if (item_get_key(root->item) < key) {
        return(_llrbt_binary_search(root->right, key));
    }

    return(root->item);
}

/*
    Inserts a new node to LLRBT, maintain its balance.
    After the insertion, balancing routines check the LLRBT balance.
    If its necessary, adjust are made.
*/
void _llrbt_insert_node(LLRBT_NODE **root, LLRBT_NODE *node) {
    if (*root == NULL) {
        *root = node;
        return;
    }

    if (item_get_key((*root)->item) > item_get_key(node->item)) {
        _llrbt_insert_node(&(*root)->left, node);
    } else if (item_get_key((*root)->item) < item_get_key(node->item)) {
        _llrbt_insert_node(&(*root)->right, node);
    } else {
        return;
    }

    // Balancing

    // RED right 
    if (!_llrbt_is_red((*root)->left) && _llrbt_is_red((*root)->right)) {
        _llrbt_rotate_left(root);
    }

    // RED left and RED left again
    if (_llrbt_is_red((*root)->left) && _llrbt_is_red((*root)->left->left)) {
        _llrbt_rotate_right(root);
    }

    // RED left and RED right
    if ((_llrbt_is_red((*root)->left) && _llrbt_is_red((*root)->right))) {
        _llrbt_switch_colors(root);
    }
}

/*
    Removes an LLRBT node by key, maintain its balance.
    After the remotion, balancing routines check the LLRBT balance.
    If its necessary, adjust are made.
    The removed node's item is returned.
*/
ITEM *_llrbt_remove_node(LLRBT_NODE **root, int key) {
    if (*root == NULL) {
        return(NULL);
    }

    ITEM *removed = NULL;

    if (item_get_key((*root)->item) > key) {
        _llrbt_remove_node(&(*root)->left, key);
    }

    if (item_get_key((*root)->item) < key) {
        _llrbt_remove_node(&(*root)->right, key);
    }

    if (item_get_key((*root)->item) == key) {
        removed = (*root)->item;

        if ((*root)->left == NULL || (*root)->right == NULL) {
            LLRBT_NODE *temp = NULL;

            if ((*root)->left == NULL) {
                temp = (*root)->right;
            } else {
                temp = (*root)->left;
            }

            free(*root);
            *root = temp;
        } else {
            _llrbt_swap_max_left(root, &(*root)->left);
        }

        if (*root == NULL) {
            return(removed);
        }

        // RED right 
        if (!_llrbt_is_red((*root)->left) && _llrbt_is_red((*root)->right)) {
            _llrbt_rotate_left(root);
        }

        // RED left and RED left again
        if (_llrbt_is_red((*root)->left) && _llrbt_is_red((*root)->left->left)) {
            _llrbt_rotate_right(root);
        }

        // RED left and RED right
        if ((_llrbt_is_red((*root)->left) && _llrbt_is_red((*root)->right))) {
            _llrbt_switch_colors(root);
        }
    }

    return(removed);
}

// Interface functions

/*
    Allocates a new LLRBT.
    If tree isn't NULL, its values are initialized.
    The created LLRBT is returned.
*/
LLRBT *llrbt_create(void) {
    LLRBT *tree = (LLRBT*) malloc(sizeof(LLRBT));

    if (tree != NULL) {
        tree->root = NULL;
    }

    return(tree);
}

/*
    Destroys the LLRBT.
    Each node will alse be destroyed, starting from root.
*/
void llrbt_destroy(LLRBT **tree) {
    if (*tree == NULL) {
        return;
    }

    _llrbt_destroy_node((*tree)->root);

    free(*tree);
    *tree = NULL;
}

/*
    Inserts a new item to LLRBT.
    Returns the insertion status (success or not).
*/
bool llrbt_insert(LLRBT *tree, ITEM *item) {
    if (tree == NULL) {
        return(false);
    }

    LLRBT_NODE *node = _llrbt_create_node(item);
    if (node == NULL) {
        return(false);
    }

    _llrbt_insert_node(&tree->root, node);
    tree->root->color = BLACK;

    return(true);
}

/*
    Removes an LLRBT item by the given key.
    The removed item is returned.
*/
ITEM *llrbt_remove(LLRBT *tree, int key) {
    if (tree == NULL) {
        return(NULL);
    }

    return(_llrbt_remove_node(&tree->root, key));
}

/*
    Searches for an LLRBT node using its key.
    The found node is returned.
*/
ITEM *llrbt_search(LLRBT *tree, int key) {
    if (tree == NULL) {
        return(NULL);
    }

    return(_llrbt_binary_search(tree->root, key));
}

/*
    Print each node using "pre-order" traversal.
*/
void llrbt_print_pre_order(LLRBT *tree) {
    if (tree == NULL) {
        return;
    }

    _llrbt_pre_order_traversal(tree->root);
}

/*
    Print each node using "in-order" traversal.
*/
void llrbt_print_in_order(LLRBT *tree) {
    if (tree == NULL) {
        return;
    }

    _llrbt_in_order_traversal(tree->root);
}

/*
    Print each node using "post-order" traversal.
*/
void llrbt_print_post_order(LLRBT *tree) {
    if (tree == NULL) {
        return;
    }

    _llrbt_post_order_traversal(tree->root);
}

