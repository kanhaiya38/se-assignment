#include <stdio.h>
#include <stdlib.h>

#include "../headers/stack.h"

void init(stack *s) {
	*s = NULL;

	// printf("stack initialised\n");
}

void push(stack *s, values pushval) {
	node *temp = (node *)malloc(sizeof(node));

	temp->val.num = pushval.num;

	temp->val.row = pushval.row;

	temp->val.col = pushval.col;

	temp->next = *s;

	*s = temp;

	// printf("(%d, %d, %d) is pushed into stack\n",
	// (*s)->val.row, (*s)->val.col, (*s)->val.num);
}

values pop(stack *s) {
	node *temp = *s;

	values popval;

	popval = (*s)->val;

	*s = (*s)->next;

	free(temp);

	// printf("(%d, %d, %d) is poped from stack\n",
	// popval.row, popval.col, popval.num);

	return popval;
}

int isempty(stack *s) { return (*s) == NULL; }

int isfull(stack *s) { return 0; }