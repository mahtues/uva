#include <stdlib.h>

typedef struct _stack_node_t {
	void* data;
	struct _stack_node_t* top;
	struct _stack_node_t* bottom;
} stack_node_t;

typedef struct _stack_t {
	struct _stack_node_t* top;
	int mallocd;
} stack_t;

int stack_init(stack_t* stack)
{
	if (!stack)
		return -1;

	stack->top = NULL;
	stack->mallocd = 0;

	return 0;
}

int stack_push(stack_t* stack, void* data)
{
	stack_node_t* new_top = NULL;
	stack_node_t* old_top = NULL;

	if (!stack)
		return -1;

	if (!data)
		return -1;

	old_top = stack->top;

	new_top = (stack_node_t*) malloc(sizeof(stack_node_t));
	if (!new_top)
		return -1;

	new_top->data = data;
	new_top->top = NULL;
	new_top->bottom = old_top;

	if (old_top)
		old_top->top = new_top;

	stack->top = new_top;

	return 0;
}

void* stack_top(stack_t* stack)
{
	if (!stack)
		return NULL;

	if (!stack->top)
		return NULL;

	return stack->top->data;
}

void* stack_pop(stack_t* stack)
{
	stack_node_t* new_top;
	stack_node_t* old_top;
	void* data;

	if (!stack)
		return NULL;

	if (!stack->top)
		return NULL;

	old_top = stack->top;
	new_top = old_top->bottom;
	
	if (new_top)
		new_top->top = NULL;

	stack->top = new_top;

	data = old_top->data;

	free(old_top);

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

	stack->top = NULL;

	free(stack);

	return 0;
}
