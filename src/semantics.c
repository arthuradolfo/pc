#include "semantics.h"
#include "cc_misc.h"
#include <stdio.h>

void remove_collisions_funcs_params(comp_dict_item_t * item)
{
  comp_dict_item_t* ptaux;
  while (item != NULL) {
    ptaux = item;
    free_stack(ptaux->value);
    item = item->next;
    dict_remove(funcs_params, ptaux->key);
  }
}

void clearFuncParams()
{
    //remover todas as entradas da tabela antes de libera-la
    st_value_t* entrada;
    if (!funcs_params) return;

    int i, l;
    for (i = 0, l = funcs_params->size; i < l; i++) {
      if (funcs_params->data[i]) {
        if(funcs_params->data[i]->next) {
          remove_collisions_funcs_params(funcs_params->data[i]->next);
        }
        entrada = dict_get(funcs_params, funcs_params->data[i]->key);
        free_stack(funcs_params->data[i]->value);
        dict_remove(funcs_params, funcs_params->data[i]->key);
      }
    }
    dict_free(funcs_params);
}

void printFuncsParams()
{
  printf("\nprintFuncsParams: \n");

  if (!funcs_params) return;

  int i, l;
  stack_t* entrada;
  for (i = 0, l = funcs_params->size; i < l; ++i) {
    if (funcs_params->data[i]) {
      entrada = dict_get(funcs_params, funcs_params->data[i]->key);
      printf("Função %s: \n", funcs_params->data[i]->key);
      stack_print_params(entrada);
    }
  }
}

void putToFuncsParams(char *func_name, st_value_t *st_param)
{
  if(!funcs_params) return;
  stack_t *aux_stack = dict_get(funcs_params, func_name);
  if(aux_stack) {
    stack_push(st_param, aux_stack);
  }
  else {
    aux_stack = new_stack();
    stack_push(st_param, aux_stack);
    dict_put(funcs_params, func_name, aux_stack);
  }
}

void put_items_stack(stack_t* stack) {
  int *a = (int*) malloc(sizeof(int));
  *a = 10;
  int *b = (int*) malloc(sizeof(int));
  *b = 15;
  printf("stack_push: %d\n", stack_push(a, stack));
  printf("stack_push: %d\n", stack_push(b, stack));
}

void stack_print_params(stack_t *stack_aux) {
  if(!stack_aux) printf("stack is null\n");
  stack_item_t *aux_item = stack_aux->data;
  st_value_t *aux;
  printf("Conteudo da pilha:\n");
  while(aux_item) {
    aux = aux_item->value;
    printf("%d\n", aux->semantic_type);
    aux_item = aux_item->next;
  }
}

void pop_and_free_scope()
{
	stack_item_t *item;
	stack_t *aux_stack = get_scope_stack();
	stack_pop(&item, &aux_stack);
	free(item);
}

void clear_scope_stack_values()
{
  stack_item_t *item;
	stack_pop(&item, &scope_stack);
	while(item) {
    comp_dict_t* symbols_table = item->value;
    clearGeneralST(symbols_table);
		stack_pop(&item, &scope_stack);
	}
}

void set_current_type_decl(char* type_decl)
{
  if (current_type_decl != NULL)
    free(current_type_decl);
  current_type_decl = strdup(type_decl);
}

char* get_current_type_decl()
{
  return current_type_decl;
}

void set_current_func_decl(char* func_decl)
{
  if (current_func_decl != NULL)
    free(current_func_decl);
  current_func_decl = strdup(func_decl);
}

char* get_current_func_decl()
{
  return current_func_decl;
}

stack_t* get_scope_stack()
{
  return scope_stack;
}

void print_semantic_type(int semantic_type)
{
  printf("[type %d] ", semantic_type);
  switch (semantic_type)
  {
    case SMTC_VOID: printf("void "); break;
    case SMTC_INT: printf("int "); break;
    case SMTC_FLOAT: printf("float "); break;
    case SMTC_CHAR: printf("char "); break;
    case SMTC_STRING: printf("string "); break;
    case SMTC_BOOL: printf("bool "); break;
    case SMTC_USER_TYPE_VAR: printf("user type "); break;
    case SMTC_NO_COERCION: printf("no coercion "); break;
  }
}

void print_semantic_type_ln(int semantic_type)
{
  printf("[type %d] ", semantic_type);
  switch (semantic_type)
  {
    case SMTC_VOID: printf("void"); break;
    case SMTC_INT: printf("int"); break;
    case SMTC_FLOAT: printf("float"); break;
    case SMTC_CHAR: printf("char"); break;
    case SMTC_STRING: printf("string"); break;
    case SMTC_BOOL: printf("bool"); break;
    case SMTC_USER_TYPE_VAR: printf("user type"); break;
    case SMTC_NO_COERCION: printf("no coercion"); break;
  }
  printf("\n");
}

int get_coercion_needed(int first_type, int second_type)
{
  // printf("[Linha %d] check_coercion_needed : ", comp_get_line_number());
  // print_semantic_type(first_type); printf("e ");
  // print_semantic_type_ln(second_type);

  if (first_type == second_type) return SMTC_NO_COERCION;

  if ((first_type == SMTC_FLOAT && second_type == SMTC_INT) || (first_type == SMTC_INT && second_type == SMTC_FLOAT))
  {
    return SMTC_FLOAT;
  }
  if ((first_type == SMTC_BOOL && second_type == SMTC_INT) || (first_type == SMTC_INT && second_type == SMTC_BOOL))
  {
    return SMTC_INT;
  }
  if ((first_type == SMTC_FLOAT && second_type == SMTC_BOOL) || (first_type == SMTC_BOOL && second_type == SMTC_FLOAT))
  {
    return SMTC_FLOAT;
  }

  //tipos incompatives

  if (first_type == SMTC_CHAR || second_type == SMTC_CHAR)
  {
    printf("[ERRO SEMANTICO] [Linha %d] Coercao impossivel do tipo char : ", comp_get_line_number());
    print_semantic_type(first_type); printf("e ");
    print_semantic_type_ln(second_type);
    exit(SMTC_ERROR_CHAR_TO_X);
  }
  if (first_type == SMTC_STRING || second_type == SMTC_STRING)
  {
    printf("[ERRO SEMANTICO] [Linha %d] Coercao impossivel do tipo string : ", comp_get_line_number());
    print_semantic_type(first_type); printf("e ");
    print_semantic_type_ln(second_type);
    exit(SMTC_ERROR_STRING_TO_X);
  }
}

int infere_type(int first_type, int second_type)
{
  if (first_type == second_type) return first_type;

  if ((first_type == SMTC_FLOAT && second_type == SMTC_INT) || (first_type == SMTC_INT && second_type == SMTC_FLOAT))
  {
    return SMTC_FLOAT;
  }
  if ((first_type == SMTC_BOOL && second_type == SMTC_INT) || (first_type == SMTC_INT && second_type == SMTC_BOOL))
  {
    return SMTC_INT;
  }
  if ((first_type == SMTC_FLOAT && second_type == SMTC_BOOL) || (first_type == SMTC_BOOL && second_type == SMTC_FLOAT))
  {
    return SMTC_FLOAT;
  }

  //tipos incompatives

  if (first_type == SMTC_CHAR || second_type == SMTC_CHAR)
  {
    printf("[ERRO SEMANTICO] [Linha %d] Coercao impossivel do tipo char : ", comp_get_line_number());
    print_semantic_type(first_type); printf("e ");
    print_semantic_type_ln(second_type);
    exit(SMTC_ERROR_CHAR_TO_X);
  }
  if (first_type == SMTC_STRING || second_type == SMTC_STRING)
  {
    printf("[ERRO SEMANTICO] [Linha %d] Coercao impossivel do tipo string : ", comp_get_line_number());
    print_semantic_type(first_type); printf("e ");
    print_semantic_type_ln(second_type);
    exit(SMTC_ERROR_STRING_TO_X);
  }
  if (first_type == SMTC_USER_TYPE_VAR || second_type == SMTC_USER_TYPE_VAR)
  {
    printf("[ERRO SEMANTICO] [Linha %d] Coercao impossivel do tipo user type : ", comp_get_line_number());
    print_semantic_type(first_type); printf("e ");
    print_semantic_type_ln(second_type);
    exit(SMTC_ERROR_STRING_TO_X);
  }
}

int infere_primitive_return_type(int first_type, int second_type)
{
  if (first_type == second_type) return first_type;

  if ((first_type == SMTC_FLOAT && second_type == SMTC_INT) || (first_type == SMTC_INT && second_type == SMTC_FLOAT))
  {
    return SMTC_FLOAT;
  }
  if ((first_type == SMTC_BOOL && second_type == SMTC_INT) || (first_type == SMTC_INT && second_type == SMTC_BOOL))
  {
    return SMTC_INT;
  }
  if ((first_type == SMTC_FLOAT && second_type == SMTC_BOOL) || (first_type == SMTC_BOOL && second_type == SMTC_FLOAT))
  {
    return SMTC_FLOAT;
  }

  //tipos incompatives
  printf("[ERRO SEMANTICO] [Linha %d] Retorno deveria ser do tipo ~%s~, mas foi do tipo ~%s~\n",
      comp_get_line_number(),
      semantic_type_to_string(first_type),
      semantic_type_to_string(second_type));
  exit(SMTC_ERROR_WRONG_PAR_RETURN);
}

int get_type_size(int semantic_type)
{
  switch (semantic_type)
  {
    default:
    case SMTC_VOID: return SMTC_VOID_SIZE;
    case SMTC_INT: return SMTC_INT_SIZE;
    case SMTC_FLOAT: return SMTC_FLOAT_SIZE;
    case SMTC_CHAR: return SMTC_CHAR_SIZE;
    case SMTC_BOOL: return SMTC_BOOL_SIZE;
    case SMTC_STRING: return SMTC_STRING_SIZE;
  }
}

void set_st_semantic_type_and_size_primitive(int semantic_type, st_value_t* symbols_table_entry)
{
  //associa tipo semantico na tabela de simbolos
  symbols_table_entry->semantic_type = semantic_type;
  //declara como variavel
  symbols_table_entry->var_vec_or_fun = SMTC_VARIABLE;
  //associa tamanho na tabela de simbolos
  symbols_table_entry->size = get_type_size(semantic_type);
}

void set_st_semantic_type_and_size_vector(int semantic_type, int length, int vector_dimension, st_value_t* symbols_table_entry)
{
  //associa tipo semantico na tabela de simbolos
  symbols_table_entry->semantic_type = semantic_type;
  //declara como vetor
  symbols_table_entry->var_vec_or_fun = SMTC_VECTOR;
  //associa tamanho na tabela de simbolos
  symbols_table_entry->size = get_type_size(semantic_type) * length;
  //associa dimensao do vetor na tabela de simbolos
  symbols_table_entry->vector_dimension = vector_dimension;
}

void set_st_semantic_type_and_size_primitive_function(int semantic_type, st_value_t* symbols_table_entry)
{
  //associa tipo semantico na tabela de simbolos
  symbols_table_entry->semantic_type = semantic_type;
  //declara como variavel
  symbols_table_entry->var_vec_or_fun = SMTC_FUNCTION;
  //associa tamanho na tabela de simbolos
  symbols_table_entry->size = get_type_size(semantic_type);
}

void set_st_semantic_type_and_size_user_type_function(char* type_name, st_value_t* variable_entry)
{
  st_value_t* type_entry = search_id_in_global_st(type_name);

  //associa tipo semantico na tabela de simbolos
  variable_entry->semantic_type = SMTC_USER_TYPE_VAR;
  //associa nome do tipo de usuario
  variable_entry->semantic_user_type = strdup(type_name);
  //declara como variavel
  variable_entry->var_vec_or_fun = SMTC_FUNCTION;
  //associa tamanho na tabela de simbolos
  variable_entry->size = type_entry->size;
}

void set_st_semantic_type_and_size_user_type(char* type_name, st_value_t* variable_entry)
{
  st_value_t* type_entry = search_id_in_global_st(type_name);

  //associa tipo semantico na tabela de simbolos
  variable_entry->semantic_type = SMTC_USER_TYPE_VAR;
  //associa nome do tipo de usuario
  variable_entry->semantic_user_type = strdup(type_name);
  //declara como variavel
  variable_entry->var_vec_or_fun = SMTC_VARIABLE;
  //associa tamanho na tabela de simbolos
  variable_entry->size = type_entry->size;
}

void set_st_semantic_type_and_size_vector_user_type(char* type_name, st_value_t* variable_entry, int length, int vector_dimension)
{
  st_value_t* type_entry = search_id_in_global_st(type_name);

  //associa tipo semantico na tabela de simbolos
  variable_entry->semantic_type = SMTC_USER_TYPE_VAR;
  //associa nome do tipo de usuario
  variable_entry->semantic_user_type = strdup(type_name);
  //declara como variavel
  variable_entry->var_vec_or_fun = SMTC_VECTOR;
  //associa tamanho na tabela de simbolos
  variable_entry->size = type_entry->size * length;
  //associa dimensao do vetor na tabela de simbolos
  variable_entry->vector_dimension = vector_dimension;
}

void set_st_semantic_type_and_size_primitive_field(int semantic_type, st_value_t* symbols_table_entry)
{
  //associa tipo semantico na tabela de simbolos
  symbols_table_entry->semantic_type = semantic_type;
  //declara como variavel
  symbols_table_entry->var_vec_or_fun = SMTC_VARIABLE;
  //associa class do campo
  symbols_table_entry->semantic_user_type = strdup(get_current_type_decl());
  //associa tamanho na tabela de simbolos
  symbols_table_entry->size = get_type_size(semantic_type);
}

void set_st_semantic_type_and_size_vector_field(int semantic_type, int length, int vector_dimension, st_value_t* symbols_table_entry)
{
  //associa tipo semantico na tabela de simbolos
  symbols_table_entry->semantic_type = semantic_type;
  //declara como vetor
  symbols_table_entry->var_vec_or_fun = SMTC_VECTOR;
  //associa class do campo
  symbols_table_entry->semantic_user_type = strdup(get_current_type_decl());
  //associa tamanho na tabela de simbolos
  symbols_table_entry->size = get_type_size(semantic_type) * length;
  //associa dimensao do vetor na tabela de simbolos
  symbols_table_entry->vector_dimension = vector_dimension;
}

void verify_shiftable(st_value_t* symbols_table_entry)
{
  if (symbols_table_entry->semantic_type != SMTC_INT) {
    printf("[ERRO SEMANTICO] [Linha %d] Tipo de identificador incorreto : ", comp_get_line_number());
    print_semantic_type(symbols_table_entry->semantic_type);
    printf("deveria ser "); print_semantic_type_ln(SMTC_INT);
    exit(SMTC_ERROR_WRONG_TYPE);
  }
}

bool is_marked_to_coercion(ast_node_value_t* ast_node_value)
{
  return ast_node_value->coercion != SMTC_NO_COERCION;
}

//assume tipos diferentes
bool coercion_possible(int first_type, int second_type)
{

  if (second_type == SMTC_CHAR)
  {
    printf("[ERRO SEMANTICO] [Linha %d] Coercao impossivel do tipo char : ", comp_get_line_number());
    print_semantic_type(first_type); printf("e ");
    print_semantic_type_ln(second_type);
    exit(SMTC_ERROR_CHAR_TO_X);
  }
  if (second_type == SMTC_STRING)
  {
    printf("[ERRO SEMANTICO] [Linha %d] Coercao impossivel do tipo string : ", comp_get_line_number());
    print_semantic_type(first_type); printf("e ");
    print_semantic_type_ln(second_type);
    exit(SMTC_ERROR_STRING_TO_X);
  }
  if (second_type == SMTC_USER_TYPE_VAR)
  {
    printf("[ERRO SEMANTICO] [Linha %d] Coercao impossivel do tipo user type : ", comp_get_line_number());
    print_semantic_type(first_type); printf("e ");
    print_semantic_type_ln(second_type);
    exit(SMTC_ERROR_WRONG_TYPE);
  }

  if (first_type == SMTC_CHAR || first_type == SMTC_STRING || first_type == SMTC_USER_TYPE_VAR)
  {
    printf("[ERRO SEMANTICO] [Linha %d] Coercao impossível : ", comp_get_line_number());
    print_semantic_type(first_type); printf("e ");
    print_semantic_type_ln(second_type);
    exit(SMTC_ERROR_WRONG_TYPE);
  }

  return true;
}

void mark_coercion(int prevalent_type, ast_node_value_t* ast_to_coerce)
{
  if (ast_to_coerce->semantic_type == prevalent_type)
  {
    ast_to_coerce->coercion = SMTC_NO_COERCION;
    return;
  }
  else if (coercion_possible(prevalent_type, ast_to_coerce->semantic_type))
  {
    ast_to_coerce->coercion = prevalent_type;

    #ifdef DEBUG
    {
      printf("[Linha %d] mark_coercion --- ", comp_get_line_number());
      printf(" | semantic_type: "); print_semantic_type(ast_to_coerce->semantic_type);
      printf(" => coercion: "); print_semantic_type_ln(ast_to_coerce->coercion);
    }
    #endif
  }
}

void mark_coercion_where_needed(ast_node_value_t* ast_node_1, ast_node_value_t* ast_node_2)
{

  int type_1 = is_marked_to_coercion(ast_node_1) ? ast_node_1->coercion : ast_node_1->semantic_type;
  int type_2 = is_marked_to_coercion(ast_node_2) ? ast_node_2->coercion : ast_node_2->semantic_type ;
  int resulting_type = infere_type(type_1, type_2);


  bool coercion_happened = false;
  if (type_1 != resulting_type)
  {
    ast_node_1->coercion = resulting_type;
    coercion_happened = true;
  }
  else if (type_2 != resulting_type)
  {
    ast_node_2->coercion = resulting_type;
    coercion_happened = true;
  }

  #ifdef DEBUG
  if (coercion_happened)
  {
    printf("[Linha %d] mark_coercion_where_needed --- ", comp_get_line_number());
    printf(" | type_1: "); print_semantic_type(type_1);
    printf(" | type_2: "); print_semantic_type(type_2);
    printf(" => coercion: "); print_semantic_type_ln(resulting_type);
  }
  #endif
}

void verify_matching_user_types(st_value_t* st_entry, ast_node_value_t* ast_expression)
{
  int type_1 = st_entry->semantic_type;
  int type_2 = ast_expression->semantic_type;
  char* user_type_1 = st_entry->semantic_user_type;
  char* user_type_2 = ast_expression->semantic_user_type;

  //se entrar aqui, ambos os tipos sao de user. checar se sao o mesmo tipo de user
  if (type_1 == type_2 && type_1 == SMTC_USER_TYPE_VAR)
  {
    //se os tipos nao forem de fato os mesmos
    if (strcmp(user_type_1, user_type_2) != 0)
    {
      printf("[ERRO SEMANTICO] [Linha %d] Coercao impossivel entre ~%s~ e ~%s~\n",
          comp_get_line_number(), user_type_1, user_type_2);
      exit(SMTC_ERROR_WRONG_TYPE);
    }
  }
}

comp_dict_t* getCurrentST()
{
  if(!scope_stack->empty) return scope_stack->data->value;
  else return symbolsTable;
}

int getCurrentSTEndOffset()
{
  if(!scope_stack->empty) return scope_stack->data->endOffsetSymbolsTable;
  else return endOffsetGlobalSymbolsTable;
}

void setCurrentSTEndOffset(int offset) {
  if(!scope_stack->empty) scope_stack->data->endOffsetSymbolsTable = offset;
  else endOffsetGlobalSymbolsTable = offset;
}

st_value_t* putToCurrentST(char* key, int line, int token_type)
{
  comp_dict_t* currentST = getCurrentST();

  if (!currentST) return NULL;

  char *value;
  char *key_aux = (char *) malloc((strlen(key)+2)*sizeof(char));
  removeQuotes(key);

  strcpy(key_aux, key);

  value = strdup(key);

  concatTokenType(key_aux, token_type);

  st_value_t* entryValue = new_st_value();
  entryValue->line = line;
  entryValue->token_type = token_type;

  setEntryValue(entryValue, value);

  st_value_t* getEntryPointerToFree = dict_get(pointersToFreeTable, key);
  if(getEntryPointerToFree) {
    getEntryPointerToFree->line = line;
  }
  else {
    dict_put(pointersToFreeTable, key, entryValue);
  }

  st_value_t* getEntry = dict_get(currentST, key_aux);
  if(getEntry) {
    free(key_aux);
    free_stack(entryValue->vector_sizes);
    if(token_type == POA_IDENT || token_type == POA_LIT_STRING) {
     free(entryValue->value.s);
    }
    free(entryValue);
    getEntry->line = line;
    return getEntry;
  }
  else {
    dict_put(currentST, key_aux, entryValue);
    free(key_aux);
    return entryValue;
  }
}

st_value_t* search_id_in_current_st(char* key)
{
  st_value_t *entry_aux = NULL;
  char* full_key = (char*) malloc((strlen(key)+2)*sizeof(char));
  strcpy(full_key, key);
  concatTokenType(full_key, POA_IDENT);
  entry_aux = dict_get(getCurrentST(), full_key);
  free(full_key);
  return entry_aux;
}

st_value_t* search_id_in_stack_sts(char* key)
{
  st_value_t *entry_aux = NULL;
  char* full_key = (char*) malloc((strlen(key)+2)*sizeof(char));
  strcpy(full_key, key);
  concatTokenType(full_key, POA_IDENT);
  stack_item_t *item_aux = scope_stack->data;
  while(item_aux) {
    entry_aux = dict_get(item_aux->value, full_key);
    if(entry_aux) {
      free(full_key);
      return entry_aux;
    }
    item_aux = item_aux->next;
  }
  entry_aux = dict_get(symbolsTable, full_key);
  free(full_key);
  return entry_aux;
}

st_value_t* search_id_in_global_st(char* key)
{
  st_value_t *entry_aux = NULL;
  char* full_key = (char*) malloc((strlen(key)+2)*sizeof(char));
  strcpy(full_key, key);
  concatTokenType(full_key, POA_IDENT);
  entry_aux = dict_get(symbolsTable, full_key);
  free(full_key);
  return entry_aux;
}

stack_t* ensure_number_of_parameters(char *func_name, comp_tree_t *tree)
{
  stack_t* stack = dict_get(funcs_params, func_name);
  stack_item_t* aux_item;
  ast_node_value_t *node_aux;
  int count_tree = 0;
  while(tree) {
    node_aux = tree->value;
    if(node_aux->syntactic_type != AST_CHAMADA_DE_FUNCAO || tree->childnodes != 1) count_tree++;
    tree = tree->first;
  }
  int count = 0;
  if(stack) {
    if (stack->empty)
    {
      printf("[ERRO SEMANTICO] [Linha %d] Função ~%s~ não possui parâmetros, %d fornecido(s)\n",
          comp_get_line_number(), func_name, count_tree);
      exit(SMTC_ERROR_EXCESS_ARGS);
    }
    else {
      aux_item = stack->data;
      while(aux_item) {
        count++;
        aux_item = aux_item->next;
      }
      if(count > count_tree) {
        printf("[ERRO SEMANTICO] [Linha %d] Função ~%s~ possui %d parâmetros, %d fornecido(s)\n",
            comp_get_line_number(), func_name, count, count_tree);
        exit(SMTC_ERROR_MISSING_ARGS);
      }
      else if(count < count_tree) {
        printf("[ERRO SEMANTICO] [Linha %d] Função ~%s~ possui %d parâmetros, %d fornecido(s)\n",
            comp_get_line_number(), func_name, count, count_tree);
        exit(SMTC_ERROR_EXCESS_ARGS);
      }
    }
  }
  else {
      printf("[ERRO SEMANTICO] [Linha %d] Função ~%s~ não possui parâmetros, %d fornecido(s)\n",
          comp_get_line_number(), func_name, count_tree);
      exit(SMTC_ERROR_EXCESS_ARGS);
  }
  return stack;
}

stack_t* ensure_parameters_type(char *func_name, comp_tree_t *parameters_tree)
{
  stack_t *stack = dict_get(funcs_params, func_name);
  stack_item_t *item_aux;
  st_value_t *stack_entry_aux;
  comp_tree_t *aux = parameters_tree;
  ast_node_value_t *node_aux;
  item_aux = stack->data;
  while(item_aux->next) {
    item_aux = item_aux->next;
  }
  while(aux && item_aux) {
    stack_entry_aux = (st_value_t*) item_aux->value;
    node_aux = aux->value;
    if(node_aux->semantic_type == SMTC_USER_TYPE_VAR) {
      if(stack_entry_aux->semantic_type != SMTC_USER_TYPE_VAR) {
        printf("[ERRO SEMANTICO] [Linha %d] Tipo do parâmetro ~%s~ devia ser do tipo ~%s~, mas foi do tipo ~%s~\n",
            comp_get_line_number(), stack_entry_aux->value.s, semantic_type_to_string(stack_entry_aux->semantic_type), node_aux->semantic_user_type);
        exit(SMTC_ERROR_WRONG_TYPE_ARGS);
      }
      else {
        if(strcmp(node_aux->semantic_user_type, stack_entry_aux->semantic_user_type) != 0) {
          printf("[ERRO SEMANTICO] [Linha %d] Tipo do parâmetro ~%s~ devia ser do tipo ~%s~, mas foi do tipo ~%s~\n",
              comp_get_line_number(), stack_entry_aux->value.s, stack_entry_aux->semantic_user_type, node_aux->semantic_user_type);
          exit(SMTC_ERROR_WRONG_TYPE_ARGS);
        }
      }
    }
    else {
      if(stack_entry_aux->semantic_type == SMTC_USER_TYPE_VAR) {
        printf("[ERRO SEMANTICO] [Linha %d] Tipo do parâmetro ~%s~ devia ser do tipo ~%s~, mas foi do tipo ~%s~\n",
            comp_get_line_number(), stack_entry_aux->value.s, stack_entry_aux->semantic_user_type, semantic_type_to_string(node_aux->semantic_type));
        exit(SMTC_ERROR_WRONG_TYPE_ARGS);
      }
      if(node_aux->semantic_type != stack_entry_aux->semantic_type) {

        // if (!coercion_possible(stack_entry_aux->semantic_type, node_aux->semantic_type))
        // {
          printf("[ERRO SEMANTICO] [Linha %d] Tipo do parâmetro ~%s~ devia ser do tipo ~%s~, mas foi do tipo ~%s~\n",
            comp_get_line_number(), stack_entry_aux->value.s, semantic_type_to_string(stack_entry_aux->semantic_type), semantic_type_to_string(node_aux->semantic_type));
          exit(SMTC_ERROR_WRONG_TYPE_ARGS);
        //}
        // else
        // {
        //   node_aux->coercion = stack_entry_aux->semantic_type;
        //   #ifdef DEBUG
        //   printf("[Linha %d] No parâmetro ~%s~ houve coercao de ~%s~ para ~%s~\n",
        //     comp_get_line_number(), stack_entry_aux->value.s, semantic_type_to_string(node_aux->semantic_type), semantic_type_to_string(node_aux->coercion));
        //   #endif
        // }

      }
    }

    if(node_aux->syntactic_type == AST_CHAMADA_DE_FUNCAO) aux = aux->last;
    else aux = aux->first;
    item_aux = item_aux->prev;
  }
  return stack;
}

stack_t* ensure_function_has_no_parameters(char *func_name)
{
  stack_t* stack = dict_get(funcs_params, func_name);
  if(stack) {
    if (!stack->empty)
    {
      printf("[ERRO SEMANTICO] [Linha %d] Função ~%s~ possui parâmetros, nenhum fornecido\n",
          comp_get_line_number(), func_name);
      exit(SMTC_ERROR_MISSING_ARGS);
    }
  }
  return stack;
}

char* semantic_type_to_string(int semantic_type) {
  switch(semantic_type) {
    case SMTC_VOID:
      return "void";
    case SMTC_INT:
      return "int";
    case SMTC_FLOAT:
      return "float";
    case SMTC_CHAR:
      return "char";
    case SMTC_STRING:
      return "string";
    case SMTC_BOOL:
      return "bool";
  }
}

void ensure_vector_dimension(int vector_dimension_call, int vector_dimension_var, char *name) {
  if(vector_dimension_call != vector_dimension_var) {
    printf("[ERRO SEMANTICO] [Linha %d] dimensões dos arrays não batem. Dimensão do array ~%s~ é de %d, mas foi usada uma dimensão de %d\n",
          comp_get_line_number(), name, vector_dimension_var, vector_dimension_call);
      exit(SMTC_ERROR_VECTOR);
  }
}

void ensure_return_type_is_correct(ast_node_value_t* ast_expression)
{
  st_value_t* st_prevalent = search_id_in_global_st(get_current_func_decl());
  int type_1 = st_prevalent->semantic_type;
  int type_2 = is_marked_to_coercion(ast_expression) ?
      ast_expression->coercion : ast_expression->semantic_type ;

  int resulting_type = infere_primitive_return_type(type_1, type_2);

  bool coercion_happened = false;
  if (type_1 != resulting_type)
  {
    ast_expression->coercion = resulting_type;
    coercion_happened = true;
  }

  #ifdef DEBUG
  if (coercion_happened)
  {
    printf("[Linha %d] mark_coercion_where_needed --- ", comp_get_line_number());
    printf(" | type_1: "); print_semantic_type(type_1);
    printf(" | type_2: "); print_semantic_type(type_2);
    printf(" => coercion: "); print_semantic_type_ln(resulting_type);
  }
  #endif
}

void ensure_return_type_user_is_correct(ast_node_value_t* ast_expression)
{
  st_value_t* st_tipo = search_id_in_global_st(get_current_func_decl());
  if(st_tipo->semantic_type == SMTC_USER_TYPE_VAR) {
    if (strcmp(st_tipo->semantic_user_type, ast_expression->semantic_user_type) != 0)
    {
      printf("[ERRO SEMANTICO] [Linha %d] retorno devia ser do tipo ~%s~, mas foi do tipo ~%s~\n",
          comp_get_line_number(), st_tipo->semantic_user_type, ast_expression->semantic_user_type);
      exit(SMTC_ERROR_WRONG_PAR_RETURN);
    }
  }
  else {
    printf("[ERRO SEMANTICO] [Linha %d] retorno devia ser do tipo ~%s~, mas foi do tipo ~%s~\n",
          comp_get_line_number(),  semantic_type_to_string(st_tipo->semantic_type), ast_expression->semantic_user_type);
      exit(SMTC_ERROR_WRONG_PAR_RETURN);
  }
}

st_value_t* ensure_type_declared(char* type_name)
{
  st_value_t* st_tipo = search_id_in_stack_sts(type_name);
  if (!st_tipo)
  {
    printf("[ERRO SEMANTICO] [Linha %d] Tipo ~%s~ não declarado\n", comp_get_line_number(), type_name);
    exit(SMTC_ERROR_UNDECLARED);
  }
  else if (st_tipo->semantic_type != SMTC_USER_TYPE_NAME)
  {
    printf("[ERRO SEMANTICO] [Linha %d] ~%s~ não é um tipo, deve ser usado como %s\n",
        comp_get_line_number(), type_name, var_vec_or_fun_to_string(st_tipo));
    exit(get_semantic_error_var_vec_or_fun(st_tipo));
  }
  return st_tipo;
}

void ensure_type_not_declared(char* id_name)
{
  st_value_t* st_identificador = search_id_in_global_st(id_name);
  if (st_identificador)
  {
    printf("[ERRO SEMANTICO] [Linha %d] Tipo ~%s~ já declarado na linha %d.\n",
        comp_get_line_number(), id_name, st_identificador->line);
    exit(SMTC_ERROR_DECLARED);
  }
}

void ensure_identifier_not_declared(char* id_name)
{
  st_value_t* st_identificador = search_id_in_current_st(id_name);
  if (st_identificador)
  {
    printf("[ERRO SEMANTICO] [Linha %d] Identificador ~%s~ já declarado na linha %d.\n",
        comp_get_line_number(), id_name, st_identificador->line);
    exit(SMTC_ERROR_DECLARED);
  }
}

st_value_t* ensure_variable_declared(char* variable_name)
{
  st_value_t* st_var = search_id_in_stack_sts(variable_name);
  if (!st_var)
  {
    printf("[ERRO SEMANTICO] [Linha %d] Variável ~%s~ não declarada\n", comp_get_line_number(), variable_name);
    exit(SMTC_ERROR_UNDECLARED);
  }
  else if (st_var->var_vec_or_fun != SMTC_VARIABLE)
  {
    printf("[ERRO SEMANTICO] [Linha %d] ~%s~ não é uma variável, deve ser usado como %s\n",
        comp_get_line_number(), variable_name, var_vec_or_fun_to_string(st_var));
    exit(get_semantic_error_var_vec_or_fun(st_var));
  }
  return st_var;
}

st_value_t* ensure_variable_declared_foreach(char* variable_name)
{
  st_value_t* st_var = search_id_in_stack_sts(variable_name);
  if (!st_var)
  {
    printf("[ERRO SEMANTICO] [Linha %d] Variável ~%s~ não declarada\n", comp_get_line_number(), variable_name);
    exit(SMTC_ERROR_UNDECLARED);
  }
  return st_var;
}

st_value_t* ensure_field_declared(char* field_name, char* related_user_type)
{
  st_value_t* st_campo = search_id_in_stack_sts(field_name);
  if (!st_campo)
  {
    printf("[ERRO SEMANTICO] [Linha %d] Campo ~%s~ não declarado\n", comp_get_line_number(), field_name);
    exit(SMTC_ERROR_UNDECLARED);
  }
  else if (related_user_type)
  {
    if (strcmp(st_campo->semantic_user_type, related_user_type) != 0)
    {
      printf("[ERRO SEMANTICO] [Linha %d] ~%s~ não é campo da classe ~%s~, e sim da ~%s~\n",
          comp_get_line_number(), field_name, related_user_type, st_campo->semantic_user_type);
      exit(SMTC_ERROR_INVALID_FIELD);
    }
  }
  //related_user_type NULL
  else {
    printf("[ERRO SEMANTICO] [Linha %d] ~%s~ não é campo\n", comp_get_line_number(), field_name);
    exit(SMTC_ERROR_INVALID_FIELD);
  }
  return st_campo;
}

st_value_t* ensure_function_declared(char* function_name)
{
  st_value_t* st_identificador = search_id_in_stack_sts(function_name);
  if (!st_identificador)
  {
    printf("[ERRO SEMANTICO] [Linha %d] Função ~%s~ não declarada\n", comp_get_line_number(), function_name);
    exit(SMTC_ERROR_UNDECLARED);
  }
  else if (st_identificador->var_vec_or_fun != SMTC_FUNCTION)
  {
    printf("[ERRO SEMANTICO] [Linha %d] ~%s~ não é uma função, deve ser usado como %s\n",
        comp_get_line_number(), function_name, var_vec_or_fun_to_string(st_identificador));
    exit(get_semantic_error_var_vec_or_fun(st_identificador));
  }
  return st_identificador;
}

st_value_t* ensure_vector_declared(char* vector_name)
{
  st_value_t* st_identificador = search_id_in_stack_sts(vector_name);
  if (!st_identificador)
  {
    printf("[ERRO SEMANTICO] [Linha %d] Vetor ~%s~ não declarado\n", comp_get_line_number(), vector_name);
    exit(SMTC_ERROR_UNDECLARED);
  }
  else if (st_identificador->var_vec_or_fun != SMTC_VECTOR)
  {
    printf("[ERRO SEMANTICO] [Linha %d] ~%s~ não é um vetor, deve ser usado como %s\n",
        comp_get_line_number(), vector_name, var_vec_or_fun_to_string(st_identificador));
    exit(get_semantic_error_var_vec_or_fun(st_identificador));
  }
  return st_identificador;
}

void ensure_inputable(ast_node_value_t* expression)
{
  if (!expression->inputable)
  {
    printf("[ERRO SEMANTICO] [Linha %d] Parâmetro de input deve ser um identificador\n", comp_get_line_number());
    exit(SMTC_ERROR_WRONG_PAR_INPUT);
  }
}

void ensure_outputable(ast_node_value_t* expression)
{
  if (!expression->outputable)
  {
    printf("[ERRO SEMANTICO] [Linha %d] Parâmetro de output deve ser um literal string ou uma expressão aritmética\n",
        comp_get_line_number());
    exit(SMTC_ERROR_WRONG_PAR_OUTPUT);
  }
}

bool is_arit_expression(ast_node_value_t* ast)
{
  int sub_exp_type = is_marked_to_coercion(ast) ?
      ast->coercion : ast->semantic_type;

  return (sub_exp_type == SMTC_INT || sub_exp_type == SMTC_FLOAT);
}

bool is_arit_operator(ast_node_value_t* ast)
{
  int operator = ast->syntactic_type;
  return (operator == AST_ARIM_SOMA ||
          operator == AST_ARIM_SUBTRACAO ||
          operator == AST_ARIM_MULTIPLICACAO ||
          operator == AST_ARIM_DIVISAO );
}

char* var_vec_or_fun_to_string(st_value_t* st_entry)
{
  switch (st_entry->var_vec_or_fun) {
    case SMTC_VARIABLE: return "variável";
    case SMTC_VECTOR: return "vetor";
    case SMTC_FUNCTION: return "função";
  }
}

int get_semantic_error_var_vec_or_fun(st_value_t* st_entry)
{
  switch (st_entry->var_vec_or_fun) {
    case SMTC_VARIABLE: return SMTC_ERROR_VARIABLE;
    case SMTC_VECTOR: return SMTC_ERROR_VECTOR;
    case SMTC_FUNCTION: return SMTC_ERROR_FUNCTION;
  }
}
