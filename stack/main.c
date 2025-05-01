#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	STACK *s = NewStack();
	
	ITEM *i1 = NewItem(1, NULL);
	StackPush(s, i1);

	ITEM *i2 = NewItem(2, NULL);
	StackPush(s, i2);

	ITEM *i3 = NewItem(3, NULL);
	StackPush(s, i3);

	ITEM *p1 = StackPeek(s);
	if (p1 != NULL) {
		printf("%d\n", p1->key);
	}

	StackPop(s);
	StackPop(s);

	ITEM *p2 = StackPeek(s);
	if (p2 != NULL) {
		printf("%d\n", p2->key);
	}

	DestroyStack(&s);

	return 0;
}
