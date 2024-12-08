#include "item.h"
#include "avlt.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct avlt_node AVLT_NODE;

struct avlt_node {
    ITEM *item;
    AVLT_NODE *left;
    AVLT_NODE *right;
    int factor;
};

struct avlt {
    AVLT_NODE *root;
};


// Helpers

/*
    Allocate a new AVLT node.
    If node isn't NULL, its values are initialized.
    The created node is returned.
*/
AVLT_NODE *_avlt_create_node(ITEM *item) {
    AVLT_NODE *node = (AVLT_NODE*) malloc(sizeof(AVLT_NODE));

    if (node != NULL) {
        node->item = item;
        node->left = NULL;
        node->right = NULL;
        node->factor = 0;
    }

    return(node);
}

/*
    Recursivelly destroys AVLT nodes.
    Starting from any node (usually the root), each child
    will be destroyed, freeing its memory space.
    Node's content (item) will also be destroyed.
*/
void _avlt_destroy_node(AVLT_NODE *root) {
    if (root == NULL) {
        return;
    }

    _avlt_destroy_node(root->left);
    _avlt_destroy_node(root->right);

    item_destroy(&root->item);
    free(root);
}

/*
    Calculates AVLT node height.
    If node is NULL, its height is 0.
    Otherwise, return the max left/right height plus 1.
*/
int _avlt_node_height(AVLT_NODE *root) {
    if (root == NULL) {
        return(0);
    }

    int l = _avlt_node_height(root->left);
    int r = _avlt_node_height(root->right);

    return((l > r ? l : r) + 1);
}

/*
    Gets AVLT node factor.
    If node is NULL, the factor is 0.
    Otherwise, return the node factor.
*/
int _avlt_node_factor(AVLT_NODE *root) {
    if (root == NULL) {
        return(0);
    }

    return(root->factor);
}

/*
    Swaps the root node with the left node with the highest value.
    Also adjusts pointers to avoid data loss.
*/
void _avlt_swap_max_left(AVLT_NODE **root, AVLT_NODE **node) {
    if ((*node)->right != NULL) {
        _avlt_swap_max_left(root, &(*node)->right);
    }

    (*root)->item = (*node)->item;

    AVLT_NODE *temp = *node;
    *node = (*node)->left;

    free(temp);
}

/*
    Rotates an AVLT node to the left.
    The newest affected node will be rotated to maintain the AVLT balance.
    Rotation occurs by changing node's pointers.
    Their factors will also change..
*/
void _avlt_rotate_left(AVLT_NODE **root) {
    AVLT_NODE *node = (*root)->right;

    (*root)->right = node->left;
    node->left = *root;

    //ajdust balancing
    (*root)->factor = _avlt_node_height((*root)->left) - _avlt_node_height((*root)->right);
    node->factor = _avlt_node_height(node->left) - _avlt_node_height(node->right);

    *root = node;
}

/*
    Rotates an AVLT node to the right.
    The newest affected node will be rotated to maintain the AVLT balance.
    Rotation occurs by changing node's pointers.
    Their factors will also change..
*/
void _avlt_rotate_right(AVLT_NODE **root) {
    AVLT_NODE *node = (*root)->left;

    (*root)->left = node->right;
    node->right = *root;

    //ajdust balancing
    (*root)->factor = _avlt_node_height((*root)->left) - _avlt_node_height((*root)->right);
    node->factor = _avlt_node_height(node->left) - _avlt_node_height(node->right);

    *root = node;
}

/*
    Traverse through the AVLT.
    Each node wil be visited in the order root -> left -> right.
*/
void _avlt_pre_order_traversal(AVLT_NODE *root) {
    if (root == NULL) {
        return;
    }

    printf("%d\n", item_get_key(root->item));
    _avlt_pre_order_traversal(root->left);
    _avlt_pre_order_traversal(root->right);
}

/*
    Traverse through the AVLT.
    Each node wil be visited in the order left -> root -> right.
*/
void _avlt_in_order_traversal(AVLT_NODE *root) {
    if (root == NULL) {
        return;
    }

    _avlt_in_order_traversal(root->left);
    printf("%d\n", item_get_key(root->item));
    _avlt_in_order_traversal(root->right);
}

/*
    Traverse through the AVLT.
    Each node wil be visited in the order left -> right -> root.
*/
void _avlt_post_order_traversal(AVLT_NODE *root) {
    if (root == NULL) {
        return;
    }

    _avlt_post_order_traversal(root->left);
    _avlt_post_order_traversal(root->right);
    printf("%d\n", item_get_key(root->item));
}

/*
    Traverse through the AVLT using binary search.
    The given key will be searched using shortest paths.
    The found node will be returned (NULL if it does not exists).
*/
ITEM *_avlt_binary_search(AVLT_NODE *root, int key) {
    if (root == NULL) {
        return(NULL);
    }

    if (item_get_key(root->item) > key) {
        return(_avlt_binary_search(root->left, key));
    }

    if (item_get_key(root->item) < key) {
        return(_avlt_binary_search(root->right, key));
    }

    return(root->item);
}

/*
    Inserts a new node to AVLT, maintain its balance.
    After the insertion, balancing routines check the AVLT balance.
    If its necessary, rotations are made.
*/
void _avlt_insert_node(AVLT_NODE **root, AVLT_NODE *node) {
    if (*root == NULL) {
        *root = node;
        return;
    }

    if (item_get_key((*root)->item) > item_get_key(node->item)) {
        _avlt_insert_node(&(*root)->left, node);
    } else if (item_get_key((*root)->item) < item_get_key(node->item)) {
        _avlt_insert_node(&(*root)->right, node);
    } else {
        return;
    }

    // Adjust factor
    (*root)->factor = _avlt_node_height((*root)->left) - _avlt_node_height((*root)->right);

    // Rotate

    // Right insertion
    if (_avlt_node_factor(*root) == -2) {
        if (_avlt_node_factor((*root)->right) > 0) {
            _avlt_rotate_right(&(*root)->right);
        }
        _avlt_rotate_left(root);
    }

    // Left insertion
    if (_avlt_node_factor(*root) == 2) {
        if (_avlt_node_factor((*root)->left) < 0) {
            _avlt_rotate_left(&(*root)->left);
        }
        _avlt_rotate_right(root);
    }
}

/*
    Removes an AVLT node by key, maintain its balance.
    After the remotion, balancing routines check the AVLT balance.
    If its necessary, rotations are made.
    The removed node's item is returned.
*/
ITEM *_avlt_remove_node(AVLT_NODE **root, int key) {
    if (*root == NULL) {
        return(NULL);
    }

    ITEM *removed = NULL;

    if (item_get_key((*root)->item) > key) {
        return(_avlt_remove_node(&(*root)->left, key));
    } 

    if (item_get_key((*root)->item) < key) {
        return(_avlt_remove_node(&(*root)->right, key));
    } 

    if (item_get_key((*root)->item) == key) {
        removed = (*root)->item;

        if ((*root)->left == NULL || (*root)->right == NULL) {
            if ((*root)->left == NULL) {
                *root = (*root)->right;
            } else {
                *root = (*root)->left;
            }
        } else {
            _avlt_swap_max_left(root, &(*root)->left);
        }

        // Adjust factor
        (*root)->factor = _avlt_node_height((*root)->left) - _avlt_node_height((*root)->right);

        // Rotate

        if (_avlt_node_factor(*root) == -2) {
            if (_avlt_node_factor((*root)->right) > 0) {
                _avlt_rotate_right(&(*root)->right);
            }
            _avlt_rotate_left(root);
        }

        if (_avlt_node_factor(*root) == 2) {
            if (_avlt_node_factor((*root)->left) < 0) {
                _avlt_rotate_left(&(*root)->left);
            }
            _avlt_rotate_right(root);
        }
    }

    return(removed);
}

// Interface functions

/*
    Allocates a new AVLT.
    If tree isn't NULL, its values are initialized.
    The created AVLT is returned.
*/
AVLT *avlt_create(void) {
    AVLT *tree = (AVLT*) malloc(sizeof(AVLT));

    if (tree != NULL) {
        tree->root = NULL;
    }

    return(tree);
}

/*
    Destroys the AVLT.
    Each node will alse be destroyed, starting from root.
*/
void avlt_destroy(AVLT **tree) {
    if (*tree == NULL) {
        return;
    }

    // Destroy nodes
    _avlt_destroy_node((*tree)->root);

    free(*tree);
    *tree = NULL;
}

/*
    Inserts a new item to AVLT.
    Returns the insertion status (success or not).
*/
bool avlt_insert(AVLT *tree, ITEM *item) {
    if (tree == NULL) {
        return(true);
    }

    AVLT_NODE *node = _avlt_create_node(item);
    if (node == NULL) {
        return(false);
    }

    _avlt_insert_node(&tree->root, node);
    return(true);
}

/*
    Removes an AVLT item by the given key.
    The removed item is returned.
*/
ITEM *avlt_remove(AVLT *tree, int key) {
    if (tree == NULL) {
        return(NULL);
    }

    return(_avlt_remove_node(&tree->root, key));
}

/*
    Searches for an AVLT node using its key.
    The found node is returned.
*/
ITEM *avlt_search(AVLT *tree, int key) {
    if (tree == NULL) {
        return(NULL);
    }

    return(_avlt_binary_search(tree->root, key));
}

/*
    Print each node using "pre-order" traversal.
*/
void avlt_print_pre_order(AVLT *tree) {
    if (tree == NULL) {
        return;
    }

    _avlt_pre_order_traversal(tree->root);
}

/*
    Print each node using "in-order" traversal.
*/
void avlt_print_in_order(AVLT *tree) {
    if (tree == NULL) {
        return;
    }

    _avlt_in_order_traversal(tree->root);
}

/*
    Print each node using "post-order" traversal.
*/
void avlt_print_post_order(AVLT *tree) {
    if (tree == NULL) {
        return;
    }

    _avlt_post_order_traversal(tree->root);
}