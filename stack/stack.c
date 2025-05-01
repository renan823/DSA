#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct node NODE;
struct node {
	ITEM *item;
	NODE *next;
};

struct stack {
	int size;
	NODE *top;
};

// Creates a new item
ITEM *NewItem(int key, void *value) {
	ITEM *item = (ITEM*) malloc(sizeof(ITEM));

	if (item != NULL) {
		item->key = key;
		item->value = value;
	}

	return item;
}

void DestroyItem(ITEM **item) {
	if (*item == NULL) {
		return;
	}
	
	if ((*item)->value != NULL) {
		free((*item)->value);
	}

	free(*item);
	*item = NULL;
}

// Creates stack node with the given item
NODE *_NewNode(ITEM *item) {
	NODE *node = (NODE*) malloc(sizeof(NODE));

	if (node != NULL) {
		node->item = item;
		node->next = NULL;
	}

	return node;
}

// Recusively destroies each stack node
void _DestroyNode(NODE *node) {
	if (node == NULL) {
		return;
	}

	// Go to the next
	_DestroyNode(node->next);

	// Deallocte item
	DestroyItem(&node->item);

	// Deallocate node
	free(node);
}

// Initializes an empty stack
STACK *NewStack() {
   	STACK *stack = (STACK*) malloc(sizeof(STACK));

	if (stack != NULL) {
		stack->size = 0;
		stack->top = NULL;
	}

	return stack;
}

// Destroies the stack (and its items)
void DestroyStack(STACK **stack) {
	if (*stack == NULL) {
		return;
	}

	// Remove nodes
	_DestroyNode((*stack)->top);
	
	// Deallocate stack
	free(*stack);
	*stack = NULL;
}

// Inserts the new item on the top
void StackPush(STACK *stack, ITEM *item) {
	if (stack == NULL) {
		return;
	}

	// Create a new node
	NODE *node = _NewNode(item);
	if (node == NULL) {
		return;
	}

	// Adjust pointers
	node->next = stack->top;
	stack->top = node;
	stack->size++;
}

// Removes the top item
ITEM *StackPop(STACK *stack) {
	if (stack == NULL || stack->top == NULL) {
		return NULL;
	}

	// Save item
	NODE *top = stack->top;
	ITEM *item = top->item;

	// Adjust pointer
	stack->top = top->next;
	stack->size--;

	// Remove node (keep the item!)
	free(top);

	return item;
}

// Peeks the top item
ITEM *StackPeek(STACK *stack) {
	if (stack == NULL || stack->top == NULL) {
		return NULL;
	}

	return stack->top->item;
}

// Returns the stack size
int StackSize(STACK *stack) {
	if (stack == NULL) {
		return -1;
	}

	return stack->size;
}
