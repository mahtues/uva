#include <stdlib.h>

typedef struct _stack_t {
	void* pool[25];
	int mallocd;
	int top;
} stack_t;

int stack_init(stack_t* stack)
{
	if (!stack)
		return -1;

	stack->top = -1;
	stack->mallocd = 0;

	return 0;
}

int stack_push(stack_t* stack, void* data)
{
	if (!stack)
		return -1;

	if (!data)
		return -1;

	stack->top++;
	stack->pool[stack->top] = data;

	return 0;
}

void* stack_top(stack_t* stack)
{
	if (!stack)
		return NULL;

	if (stack->top < 0)
		return NULL;

	return stack->pool[stack->top];
}

void* stack_pop(stack_t* stack)
{
	void* data;

	if (!stack)
		return NULL;

	if (stack->top < 0)
		return NULL;

	data = stack->pool[stack->top];

	stack->top--;

	return data;
}

stack_t* stack_new()
{
	stack_t* new_stack = NULL;

	new_stack = (stack_t*) malloc(sizeof(stack_t));
	if (!new_stack)
		return NULL;

	stack_init(new_stack);

	new_stack->mallocd = 1;

	return new_stack;
}

/* pop everything first */
int stack_destroy(stack_t* stack)
{
	if (!stack)
		return -1;

	if (!stack->mallocd)
		return -1;

	free(stack);

	return 0;
}
