#ifndef SYMBOLS_TABLE_H
#define SYMBOLS_TABLE_H

#include <stdbool.h>
#include "cc_list.h"
#include "cc_dict.h"

union Value {
	int i;
	float f;
	bool b;
	char c;
	char *s;
};

typedef struct vector_size_t {
	int size;
	int vector_dimension;
} st_vector_size;

typedef struct symbolsTable_value {
    int line;
    int token_type;

    /**
     * Uma das constantes de semantic.h
     */
		int semantic_type;

    /**
	   * Quando semantic_type for SMTC_USER_TYPE_VAR,
	   * esse campo tem o nome do tipo de usuario.
	   * Senão, deve ser NULL.
	   */
    char* semantic_user_type;

		/**
		 * Deslocamento relativo de rbss ou rarp
		 */
    int offset_address;

    /**
     * Base do deslocamento relativo do calculo do endereco: rbss ou rarp
     */
    int address_base;

    /**
     * Define se representa uma variavel, um vetor ou uma funcao
     */
    int var_vec_or_fun;

    /**
		 * Tamanho em bytes da variável
		 */
    int size;

    /**
     * Tamanho em bytes da string (se for string), pode ser menor ou igual a size
		 */
		int count_char;

    /**
     * Define quantas dimensões um vetor possui
     */
    int vector_dimension;

		/**
		 * Pilha de dimensoes dos vetores multidimensionais
		 */
		stack_t* vector_sizes;

    union Value value;
} st_value_t;

/**
  * @var comp_dict_t symbolsTable Gerencia a tabela de simbolos
  */
comp_dict_t* symbolsTable;

int endOffsetGlobalSymbolsTable;

comp_dict_t* pointersToFreeTable;

comp_dict_t* get_symbols_table();

void concatTokenType(char *key, int token_type);
void clearPointerToFreeTable();
void clearSymbolsTable();
void removeQuotes(char *key);
void remove_collisions(comp_dict_item_t * item);
void remove_collisions_funcs_params(comp_dict_item_t * item);
void remove_collisions_pointer_to_free(comp_dict_item_t * item);
void setEntryValue(st_value_t* entryValue, char* value);
st_value_t* putToSymbolsTable(char* key, int line, int token_type);
void putToFuncsParams(char *func_name, st_value_t *st_param);

/**
 * Imprime tabela de simbolos
 */
void print_st(comp_dict_t* st);

void remove_collisions_general_st(comp_dict_t *st, comp_dict_item_t * item);

void clearGeneralST(comp_dict_t *st);

/**
 * Inicializa um st_value_t com tds os campos
 */
st_value_t* new_st_value();

/**
 * Limpa um st_value_t
 */
void clear_st_value(st_value_t*);

int calculateGlobalAddress(int size);

int calculateLocalAddress(int size);

#endif
