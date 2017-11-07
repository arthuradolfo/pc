#ifndef __MISC_H
#define __MISC_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "cc_tree.h"
#include "cc_ast.h"
#include "cc_dict.h"

union Value {
	int i;
	float f;
	bool b;
	char c;
	char *s;
};

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
		 int size;
    union Value value;
} st_value_t;

void set_ast_root(comp_tree_t* root);
comp_tree_t* get_ast_root();
void putToGraphviz(comp_tree_t *pai);

int getLineNumber (void);
void yyerror (char const *mensagem);
void comp_print_table();
void concatTokenType(char *key, int token_type);
void clearPointerToFreeTable();
void clearSymbolsTable();
void removeQuotes(char *key);
void remove_collisions(comp_dict_item_t * item);
void remove_collisions_pointer_to_free(comp_dict_item_t * item);
void setEntryValue(st_value_t* entryValue, char* value);
st_value_t* putToSymbolsTable(char* key, int line, int token_type);
void main_init (int argc, char **argv);
void main_finalize (void);
int comp_set_line_number (char *yytext);
void destroyAST(comp_tree_t* ast);


/* -------------------------------------------------------------------------- */
/* ---------------------------------  AST ----------------------------------  */
/* -------------------------------------------------------------------------- */


/**
 * Tipos de valores de nodos de ast
 */
typedef struct ast_node_value {

  /**
   * Uma das constantes de cc_ast.h
   */
  int syntactic_type;

  /**
   * Uma das constantes de tipo de semantic.h
   */
  int semantic_type;

  /**
   * Quando semantic_type for IKS_USER_TYPE_VAR,
   * esse campo tem o nome do tipo de usuario.
   * Senão, deve ser NULL.
   */
   char* semantic_user_type;

	 /**
	  * Diferente de SMTC_NO_COERCION quando é necessaria coercao
		*/
	 int coercion;

  struct symbolsTable_value* symbols_table_entry;

} ast_node_value_t;

/**
 * Construtor para ast_node_value_t
 */
ast_node_value_t* new_ast_node_value(int syntactic_type, int semantic_type, char* semantic_user_type, struct symbolsTable_value* symbols_table_entry);


/* -------------------------------------------------------------------------- */
/* ------------------------------- semantics -------------------------------  */
/* -------------------------------------------------------------------------- */



/* tipos semanticos */
#define SMTC_VOID -1
#define SMTC_INT 1
#define SMTC_FLOAT 2
#define SMTC_CHAR 3
#define SMTC_STRING 4
#define SMTC_BOOL 5
#define SMTC_INT_VECTOR 6
#define SMTC_FLOAT_VECTOR 7
#define SMTC_CHAR_VECTOR 8
#define SMTC_STRING_VECTOR 9
#define SMTC_BOOL_VECTOR 10
#define SMTC_USER_TYPE_VAR 11
#define SMTC_USER_TYPE_VECTOR 12
#define SMTC_USER_TYPE_NAME 13
/** marcador de livre de coercao */
#define SMTC_NO_COERCION 14

/*tamanhos dos tipos*/
#define SMTC_VOID_SIZE 0
#define SMTC_INT_SIZE 4
#define SMTC_FLOAT_SIZE 8
#define SMTC_CHAR_SIZE 1
#define SMTC_BOOL_SIZE 1

/* erros semanticos */

#define SMTC_SUCCESS 0 //caso não houver nenhum tipo de erro

/* Verificação de declarações */
#define SMTC_ERROR_UNDECLARED 1 //identificador não declarado
#define SMTC_ERROR_DECLARED 2 //identificador já declarado

/* Uso correto de identificadores */
#define SMTC_ERROR_VARIABLE 3 //identificador deve ser utilizado como variável
#define SMTC_ERROR_VECTOR 4 //identificador deve ser utilizado como vetor
#define SMTC_ERROR_FUNCTION 5 //identificador deve ser utilizado como função

/* Tipos e tamanho de dados */
#define SMTC_ERROR_WRONG_TYPE 6 //tipos incompatı́veis
#define SMTC_ERROR_STRING_TO_X 7 //coerção impossı́vel do tipo string
#define SMTC_ERROR_CHAR_TO_X 8 //coerção impossı́vel do tipo char

/* Argumentos e parâmetros */
#define SMTC_ERROR_MISSING_ARGS 9 //faltam argumentos
#define SMTC_ERROR_EXCESS_ARGS 10 //sobram argumentos
#define SMTC_ERROR_WRONG_TYPE_ARGS 11 //argumentos incompatı́veis

/* Verificação de tipos em comandos */
#define SMTC_ERROR_WRONG_PAR_INPUT 12 //parâmetro não é identificador
#define SMTC_ERROR_WRONG_PAR_OUTPUT 13 //parâmetro não é literal string ou expressão
#define SMTC_ERROR_WRONG_PAR_RETURN 14 //parâmetro não é expressão compatı́vel com tipo


/* funcoes de semantica */

void print_semantic_type(int semantic_type);

/**
 * Retorna um tipo inferido pela operacao com dois tipos
 */
int get_coercion_needed(int first_type, int second_type);

/**
 * Infere o tipo necessario entre dois tipos
 */
int infere_type(int first_type, int second_type);

/**
 * Retorna tamanho de um tipo primitivo
 */
int get_type_size(int semantic_type);

/**
 * Seta, num Value de entrada de tabela de simbolos, o tipo semantico e seu tamanho
 */
void set_st_semantic_type_and_size_primitive(int semantic_type, st_value_t* symbols_table_entry);

/**
 * Seta, num Value de entrada de tabela de simbolos de um vetor, o tipo semantico e seu tamanho
 */
void set_st_semantic_type_and_size_vector(int semantic_type, int length, st_value_t* symbols_table_entry);

/**
 * Retorna o tipo semantico de um elemento de um vetor
 */
int get_semantic_type_of_indexed_vector(int vector_semantic_type);

/**
 * Retorna o tipo semantico de um vetor cujo tipo dos elementos é o passado por parametro
 */
int get_semantic_type_vector_from_element(int vector_semantic_type);

/**
 * Seta, num Value de entrada de tabela de simbolos de uma variavel de tipo de usuario, o tipo semantico e seu tamanho
 */
void set_st_semantic_type_and_size_user_type(st_value_t* type_entry, st_value_t* variable_entry);

/**
 * Seta, num Value de entrada de tabela de simbolos de um vetor de tipo de usuario, o tipo semantico e seu tamanho
 */
void set_st_semantic_type_and_size_vector_user_type(st_value_t* type_entry, st_value_t* variable_entry, int length);

/**
 * Verifica se entrada de tabela de simbolos é shiftavel. Se nao for, encerra execucao com erro
 */
void verify_shiftable(st_value_t* symbols_table_entry);

/**
 * Verifica se um ast_node_value_t tem tipo semantico compativel para um indice. Se tiver,
 * potencialmente marca uma coercao (se for bool). Se não tiver, encerra execucao com erro
 */
void verify_index(ast_node_value_t* ast_index);

/**
 * Marca na ast que deve haver uma coercao (se necessaria)
 */
void mark_coercion(int semantic_type, ast_node_value_t* ast_to_coerce);

/**
 * Marca, no nodo ast adequado, uma coercao (se necessaria)
 */
void mark_coercion_where_needed(ast_node_value_t* ast_node_1, ast_node_value_t* ast_node_2);

#endif
