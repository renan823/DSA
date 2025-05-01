#ifndef STACK_H_
	#define STACK_H_
	
	typedef struct item ITEM;
	struct item {
		int key;
		void *value;
	};

	ITEM *NewItem(int key, void *value);
	void DestroyItem(ITEM **item);

	typedef struct stack STACK;

	STACK *NewStack();
	void DestroyStack(STACK **stack);

	void StackPush(STACK *stack, ITEM *item);
	ITEM *StackPop(STACK *stack);
	ITEM *StackPeek(STACK *stack);

	int StackSize(STACK *stack);
#endif
