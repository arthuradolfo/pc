#include "symbols_table.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

comp_dict_t* get_symbols_table()
{
  return symbolsTable;
}

/**
 * Coloca o token na tabela de simbolos
 * @param char* key
 * @param int line
 * @int token_type
 * @return st_value_t* entryValue
 */
st_value_t* putToSymbolsTable(char* key, int line, int token_type)
{
  if (!symbolsTable) return NULL;


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

  st_value_t* getEntry = dict_get(symbolsTable, key_aux);
  if(getEntry) {
    free(key_aux);
    if(token_type == POA_IDENT || token_type == POA_LIT_STRING) {
      free(entryValue->value.s);
    }
    free(entryValue);
    getEntry->line = line;
    return getEntry;
  }
  else {
    dict_put(symbolsTable, key_aux, entryValue);
    free(key_aux);
    return entryValue;
  }
}

void getAndPrintSomeEntries()
{
  printf("\ngetAndPrintSomeEntries: \n");

  if (!symbolsTable) return;

  st_value_t* entradaAdolfo = dict_get(symbolsTable, "Arthur");
  st_value_t* entradaSeibel = dict_get(symbolsTable, "Seibel");
  st_value_t* entradaLeticia = dict_get(symbolsTable, "Leticia");
  st_value_t* entradaPablo = dict_get(symbolsTable, "Pablo");

  printf("Get entrada Adolfo: linha %d\n", entradaAdolfo->line);
  printf("Get entrada Seibel: linha %d\n", entradaSeibel->line);
  printf("Get entrada Leticia: linha %d\n", entradaLeticia->line);
  printf("Get entrada Pablo: linha %d\n", entradaPablo->line);
}

void printSymbolsTable()
{
  printf("\nprintSymbolsTable: \n");

  if (!symbolsTable) return;

  int i, l;
  st_value_t* entrada;
  for (i = 0, l = symbolsTable->size; i < l; ++i) {
    if (symbolsTable->data[i]) {
      entrada = dict_get(symbolsTable, symbolsTable->data[i]->key);
      printf("Chave %s Valor %d\n", symbolsTable->data[i]->key, entrada->line);
    }
  }
}



/**
  * Libera os espacos de memoria ocupados pelos ponteiros da tabela de simbolos
  */
void clearSymbolsTable()
{
    //remover todas as entradas da tabela antes de libera-la
    st_value_t* entrada;
    if (!symbolsTable) return;

    int i, l;
    for (i = 0, l = symbolsTable->size; i < l; i++) {
      if (symbolsTable->data[i]) {
        if(symbolsTable->data[i]->next) {
          remove_collisions(symbolsTable->data[i]->next);
        }
        entrada = dict_get(symbolsTable, symbolsTable->data[i]->key);
        if(entrada->token_type == POA_IDENT || entrada->token_type == POA_LIT_STRING) {
          free(entrada->value.s);
        }
        if (entrada->semantic_user_type) free(entrada->semantic_user_type);
        if (entrada->vector_sizes) free_stack(entrada->vector_sizes);
        free(symbolsTable->data[i]->value);
        dict_remove(symbolsTable, symbolsTable->data[i]->key);
      }
    }
    dict_free(symbolsTable);
}

/**
  * Libera os espacos de memoria ocupados pelos ponteiros da tabela de ponteiros a serem liberados
  */
void clearPointerToFreeTable()
{
    //remover todas as entradas da tabela antes de libera-la
    st_value_t* entrada;
    if (!pointersToFreeTable) return;

    int i, l;
    for (i = 0, l = pointersToFreeTable->size; i < l; i++) {
      if (pointersToFreeTable->data[i]) {
        if(pointersToFreeTable->data[i]->next) {
          remove_collisions_pointer_to_free(pointersToFreeTable->data[i]->next);
        }
        dict_remove(pointersToFreeTable, pointersToFreeTable->data[i]->key);
      }
    }
    dict_free(pointersToFreeTable);
}

/**
 * Converte o token para o tipo especificado e insere no campo value da entrada da tabela de simbolos
 * @param st_value_t* entryValue
 * @param char* value
 */
void setEntryValue(st_value_t* entryValue, char* value) {
  switch(entryValue->token_type) {
    case POA_LIT_INT:
      entryValue->value.i = atoi(value);
      free(value);
      break;

    case POA_LIT_FLOAT:
      entryValue->value.f = atof(value);
      free(value);
      break;

    case POA_LIT_CHAR:
      entryValue->value.c = *value;
      free(value);
      break;

    case POA_LIT_STRING:
      entryValue->value.s = value;
      break;

    case POA_LIT_BOOL:
      if(strcmp(value, "true") == 0) {
        entryValue->value.b = true;
      }
      else {
        entryValue->value.b = false;
      }
      free(value);
      break;

    case POA_IDENT:
      entryValue->value.s = value;
      break;

    default:
      break;
  }
}

/**
 * Remove aspas simples e duplas dos tokens tipo TK_LIT_STRING e TK_LIT_CHAR
 * @param char* key
 */
void removeQuotes(char *key) {
  int i = 0, string = 0;
  while(i < strlen(key)) {
    if(key[i] == '"' || key[i] == '\'') {
      string = 1;
      if(key[i+1] == '"') {
        key[i] = '\0';
      }
      else {
        key[i] = key[i+1];
      }
      key[strlen(key)-1] = '\0';
    }
    else if(string == 1) {
      key[i] = key[i+1];
    }
    i++;
  }
}

/**
  * Concatena tipo do token ao key
  * @param char* key
  * @param int token_type
  */
void concatTokenType(char *key, int token_type) {
  char *token_str = (char *) malloc(sizeof(char)*2);
  sprintf(token_str, "%d", token_type);
  strcat(key, token_str);
  free(token_str);
}

/**
  * Da free em ponteiros das entradas da tabela de simbolos que estao no ponteiro next (quando a colisao de entradas)
  * @param comp_dict_item_t* item
  */
void remove_collisions(comp_dict_item_t * item)
{
  comp_dict_item_t* ptaux;
  st_value_t* entrada;
  while (item != NULL) {
    ptaux = item;
    entrada = dict_get(symbolsTable, ptaux->key);
    if(entrada->token_type == POA_IDENT || entrada->token_type == POA_LIT_STRING) {
      free(entrada->value.s);
    }
    if (entrada->semantic_user_type) free(entrada->semantic_user_type);
    if (entrada->vector_sizes) free_stack(entrada->vector_sizes);
    free(ptaux->value);
    item = item->next;
    dict_remove(symbolsTable, ptaux->key);
  }
}

void remove_collisions_pointer_to_free(comp_dict_item_t * item)
{
  comp_dict_item_t* ptaux;
  while (item != NULL) {
    ptaux = item;
    item = item->next;
    dict_remove(pointersToFreeTable, ptaux->key);
  }
}

void putSomeEntries(comp_dict_t* symbols_table)
{

  if (!symbolsTable) return;

  st_value_t* valueAdolfo = (st_value_t*) malloc(sizeof(st_value_t));
  valueAdolfo->line = 41;
  st_value_t* valueSeibel = (st_value_t*) malloc(sizeof(st_value_t));
  valueSeibel->line = 42;
  st_value_t* valueLeticia = (st_value_t*) malloc(sizeof(st_value_t));
  valueLeticia->line = 43;
  st_value_t* valuePablo = (st_value_t*) malloc(sizeof(st_value_t));
  valuePablo->line = 44;

  dict_put(symbolsTable, "Arthur", valueAdolfo);
  dict_put(symbolsTable, "Seibel", valueSeibel);
  dict_put(symbolsTable, "Leticia", valueLeticia);
  dict_put(symbolsTable, "Pablo", valuePablo);
}

/**
  * Libera os espacos de memoria ocupados pelos ponteiros da tabela de simbolos
  */
void clearGeneralST(comp_dict_t *st)
{
    //remover todas as entradas da tabela antes de libera-la
    st_value_t* entrada;
    if (!st) return;

    int i, l;
    for (i = 0, l = st->size; i < l; i++) {
      if (st->data[i]) {
        if(st->data[i]->next) {
          remove_collisions_general_st(st, st->data[i]->next);
        }
        entrada = dict_get(st, st->data[i]->key);
        if(entrada->token_type == POA_IDENT || entrada->token_type == POA_LIT_STRING) {
          free(entrada->value.s);
        }
        if (entrada->semantic_user_type) free(entrada->semantic_user_type);
        if (entrada->vector_sizes) free_stack(entrada->vector_sizes);
        free(st->data[i]->value);
        dict_remove(st, st->data[i]->key);
      }
    }
    dict_free(st);
}

/**
  * Da free em ponteiros das entradas da tabela de simbolos que estao no ponteiro next (quando a colisao de entradas)
  * @param comp_dict_item_t* item
  */
void remove_collisions_general_st(comp_dict_t *st, comp_dict_item_t * item)
{
  comp_dict_item_t* ptaux;
  st_value_t* entrada;
  while (item != NULL) {
    ptaux = item;
    entrada = dict_get(st, ptaux->key);
    if(entrada->token_type == POA_IDENT || entrada->token_type == POA_LIT_STRING) {
      free(entrada->value.s);
    }
    if (entrada->semantic_user_type) free(entrada->semantic_user_type);
    if (entrada->vector_sizes) free_stack(entrada->vector_sizes);
    free(ptaux->value);
    item = item->next;
    dict_remove(st, ptaux->key);
  }
}

void comp_print_table (void)
{
  //para cada entrada na tabela de símbolos
  //Etapa 1: chame a função cc_dict_etapa_1_print_entrada
  //implemente esta função

  if (!symbolsTable) return;

  int i, l;
  st_value_t* entrada;
  for (i = 0, l = symbolsTable->size; i < l; ++i) {
    if (symbolsTable->data[i]) {
      entrada = dict_get(symbolsTable, symbolsTable->data[i]->key);
      //printf("Chave %s Valor %d\n", symbolsTable->data[i]->key, entrada->line);
      cc_dict_etapa_2_print_entrada(symbolsTable->data[i]->key, entrada->line, entrada->token_type);
    }
  }
}

void print_st(comp_dict_t* st)
{
  if (!st)
  {
    #ifdef DEBUG
      printf("Tabela NULL\n");
    #endif
    return;
  }
  printf("\nTabela:\n");


  int i, l;
  st_value_t* entrada;
  for (i = 0, l = st->size; i < l; ++i) {
    if (st->data[i]) {
      entrada = dict_get(st, st->data[i]->key);
      //printf("Chave %s Valor %d\n", st->data[i]->key, entrada->line);
      cc_dict_etapa_2_print_entrada(st->data[i]->key, entrada->line, entrada->token_type);
    }
  }
}

st_value_t* new_st_value()
{
  st_value_t * st_value = (st_value_t *) malloc(sizeof(st_value_t));
  st_value->line = 0;
  st_value->token_type = 0;
  st_value->semantic_type = SMTC_VOID;
  st_value->semantic_user_type = NULL;
  st_value->var_vec_or_fun = SMTC_VARIABLE;
  st_value->size = 0;
  st_value->vector_dimension = 0;
  st_value->value.i = 0;
  st_value->vector_sizes = new_stack();
}

void clear_st_value(st_value_t* st_value)
{
  if (st_value->semantic_user_type)
    free(st_value->semantic_user_type);
  if (st_value->value.s)
    free(st_value->value.s);
}

int calculateGlobalAddress(int size)
{
  int offset_return = endOffsetGlobalSymbolsTable;
  endOffsetGlobalSymbolsTable+=size;
  return offset_return;
}

int calculateLocalAddress(int size) {
  int offset_return = getCurrentSTEndOffset();
  setCurrentSTEndOffset(getCurrentSTEndOffset()+size);
  return offset_return;
}
