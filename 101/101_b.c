#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _stack_t {
	void* pool[25];
	int top;
} stack_t;

int stack_init(stack_t* stack)
{
	if (!stack)
		return -1;

	stack->top = -1;

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

typedef struct _block_t {
	int n;
	stack_t* curr_stack;
	stack_t* orig_stack;
} block_t;

typedef enum _main_action_t {
	MOVE,
	PILE,
	QUIT,
	INVALID_ACT
} main_action_t;

typedef enum _sec_action_type_t {
	ONTO,
	OVER,
	INVALID_AUX
} sec_action_t;

int main(int argc, char** argv)
{
	stack_t stack[25];
	stack_t swap_stack;
	block_t block[25];
	block_t* blk;
	
	int i;
	int blocks;
	char input[128];

	main_action_t act;
	sec_action_t aux;

	char str_act[128];
	char str_aux[128];
	int a, b;

	if(!fgets(input, 128, stdin))
		return EXIT_FAILURE;

	sscanf(input, "%d", &blocks);

	if (blocks > 25)
		return EXIT_FAILURE;

	stack_init(&swap_stack);
	for (i = 0; i < blocks; i++) {
		stack_init(&stack[i]);

		block[i].n = i;
		block[i].curr_stack = &stack[i];
		block[i].orig_stack = &stack[i];

		stack_push(&stack[i], (void*) &block[i]);
	}

	while (fgets(input, 128, stdin)) {
		act = INVALID_ACT;
		aux = INVALID_AUX;

		sscanf(input, "%s", str_act);

		if (strncmp("quit", str_act, 128) == 0) {
			act = QUIT;
			break;
		}

		sscanf(input, "%s %d %s %d", str_act, &a, str_aux, &b);

		if (strncmp("move", str_act, 128) == 0) {
			act = MOVE;
		}
		else if (strncmp("pile", str_act, 128) == 0) {
			act = PILE;
		}
		else {
			continue;
		}

		if (strncmp("onto", str_aux, 128) == 0) {
			aux = ONTO;
		}
		else if (strncmp("over", str_aux, 128) == 0) {
			aux = OVER;
		}
		else {
			continue;
		}

		if ((a < 0) || (a >= blocks))
			continue;

		if ((b < 0) || (b >= blocks))
			continue;

		if (a == b)
			continue;

		if (block[a].curr_stack == block[b].curr_stack)
			continue;

		if (act == MOVE) {
			/** return blocks on top of a to original places. */
			while (stack_top(block[a].curr_stack) != &block[a]) {
				blk = (block_t*) stack_pop(block[a].curr_stack);
				stack_push(blk->orig_stack, (void*) blk);
				blk->curr_stack = blk->orig_stack;
			}

			if (aux == ONTO) {
				/** return blocks on top of b to original places. */
				while (stack_top(block[b].curr_stack) != &block[b]) {
					blk = (block_t*) stack_pop(block[b].curr_stack);
					stack_push(blk->orig_stack, (void*) blk);
					blk->curr_stack = blk->orig_stack;
				}
			}

			blk = (block_t*) stack_pop(block[a].curr_stack);
			stack_push(block[b].curr_stack, (void*) blk);
			blk->curr_stack = block[b].curr_stack;
		}
		else if (act == PILE) {
			/** return blocks on top of a to original places. */
			do {
				blk = (block_t*) stack_pop(block[a].curr_stack);
				stack_push(&swap_stack, (void*) blk);
				blk->curr_stack = &swap_stack;
			} while (blk != &block[a]);

			if (aux == ONTO) {
				/** return blocks on top of b to original places. */
				while (stack_top(block[b].curr_stack) != &block[b]) {
					blk = (block_t*) stack_pop(block[b].curr_stack);
					stack_push(blk->orig_stack, (void*) blk);
					blk->curr_stack = blk->orig_stack;
				}
			}

			while (blk = (block_t*) stack_pop(&swap_stack)) {
				stack_push(block[b].curr_stack, (void*) blk);
				blk->curr_stack = block[b].curr_stack;
			}
		}
		else {
			continue;
		}
	}

	/** print stuff */
	for (i = 0; i < blocks; i++) {
		str_aux[0] = '\0';
		str_act[0] = '\0';

		while (blk = (block_t*) stack_pop(&stack[i])) {
			sprintf(str_aux, " %d%s", blk->n, str_act);
			strcpy(str_act, str_aux);
		}
		
		printf("%d:%s\n", i, str_act);
	}

	return EXIT_SUCCESS;
}
