#include "cc_list.h"
st_stack_t* new_stack(void) {
	st_stack_t *stack = (st_stack_t*) malloc(sizeof(st_stack_t));
	stack->empty = 1;
	stack->data = NULL;
	return stack;
}


st_stack_item_t* new_stack_item(void) {
	st_stack_item_t *item = (st_stack_item_t*) malloc(sizeof(st_stack_item_t));
	item->value = NULL;
	item->next = NULL;
	item->prev = NULL;
	return item;
}


int stack_pop(st_stack_item_t **data, st_stack_t **stack) {
	if(!data || !stack) return STACK_ERROR_NULL_PARAM;
	if((*stack)->empty) {
		*data = NULL;
		return 0;
	}
	else {
		if(!(*stack)->data->next) {
			*data = (*stack)->data;
			(*stack)->data = NULL;
			(*stack)->empty = 1;
		}
		else {
			*data = (*stack)->data;
			(*stack)->data = (*stack)->data->next;
			(*stack)->data->prev = NULL;
			(*data)->next = NULL;
		}
		return 0;
	}
}


int stack_push(void *value, st_stack_t *stack) {
	st_stack_item_t *aux_item;
	st_stack_item_t *data;
	if(!value || !stack) return STACK_ERROR_NULL_PARAM;
	data = new_stack_item();
	data->value = value;
	data->next = NULL;
	if(stack->empty) {
		stack->data = data;
		stack->empty = 0;
	}
	else {
		aux_item = stack->data;
		data->next = aux_item;
		stack->data = data;
		aux_item->prev = stack->data;
	}
	return 0;
}


void free_stack(st_stack_t *stack) {
	st_stack_item_t *aux_item;
	stack_pop(&aux_item, &stack);
	while(aux_item) {
		free(aux_item);
		stack_pop(&aux_item, &stack);
	}
	free(stack);
}