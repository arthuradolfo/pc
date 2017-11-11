#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STACK_ERROR_NULL_PARAM -1

typedef struct st_stack_item {
	void *value;
	struct st_stack_item *next;
} st_stack_item_t;


typedef struct st_stack {
	int empty;
	struct st_stack_item *data;
} st_stack_t;

st_stack_t* new_stack(void);
st_stack_item_t* new_stack_item(void);
int stack_pop(st_stack_item_t **data, st_stack_t **stack);
int stack_push(void *value, st_stack_t *stack);
void free_stack(st_stack_t *stack);
