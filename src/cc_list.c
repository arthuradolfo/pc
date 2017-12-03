#include "cc_list.h"
stack_t* new_stack(void) {
	stack_t *stack = (stack_t*) malloc(sizeof(stack_t));
	stack->empty = 1;
	stack->data = NULL;
	return stack;
}


stack_item_t* new_stack_item(void) {
	stack_item_t *item = (stack_item_t*) malloc(sizeof(stack_item_t));
	item->value = NULL;
	item->endOffsetSymbolsTable = 0;
	item->next = NULL;
	item->prev = NULL;
	return item;
}

void* pop_value(stack_t** stack)
{
  stack_item_t* item = new_stack_item();
  if (stack_pop(&item, stack) != 0)
  {
    printf("Erro de stack_pop()\n");
    exit(EXIT_FAILURE);
  }
  return (item) ? item->value : NULL;
}

int stack_pop(stack_item_t **data, stack_t **stack) {
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


int stack_push(void *value, stack_t *stack) {
	stack_item_t *aux_item;
	stack_item_t *data;
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


void free_stack(stack_t *stack) {
	stack_item_t *aux_item;
	stack_pop(&aux_item, &stack);
	while(aux_item) {
		free(aux_item);
		stack_pop(&aux_item, &stack);
	}
	free(stack);
}

void reverse_stack(stack_t** stack)
{
  stack_t* reversed = new_stack();
  stack_item_t* item = (*stack)->data;

  while (item) {
    stack_push(item->value, reversed);
    item = item->next;
  }

  free_stack(*stack);
  *stack = reversed;
}

void stack_print(stack_t *stack_aux)
{
  if (!stack_aux) {
    printf("stack is null\n");
    return;
  }
  stack_item_t *aux_item = stack_aux->data;
  printf("Conteudo da pilha:\n");
  while(aux_item) {
    printf("%d\n", *((int*)aux_item->value));
    aux_item = aux_item->next;
  }
}