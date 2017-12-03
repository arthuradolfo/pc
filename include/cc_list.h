#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STACK_ERROR_NULL_PARAM -1

typedef struct stack_item {
	void *value;
	int endOffsetSymbolsTable;
	struct stack_item *next;
	struct stack_item *prev;
} stack_item_t;


typedef struct stack {
	int empty;
	struct stack_item *data;
} stack_t;

stack_t* new_stack(void);
stack_item_t* new_stack_item(void);
int stack_pop(stack_item_t **data, stack_t **stack);
int stack_push(void *value, stack_t *stack);
void free_stack(stack_t *stack);
void stack_print(stack_t *stack_aux);

/**
 * Retorna o campo void* value do item stack_item_t do topo de stack
 */
void* pop_value(stack_t** stack);

/**
 * Inverte uma pilha
 */
void reverse_stack(stack_t** stack);