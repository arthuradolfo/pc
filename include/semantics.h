#ifndef SEMANTICS_H
#define SEMANTICS_H

#include "cc_list.h"
#include "cc_dict.h"
#include "symbols_table.h"
#include "syntax_tree.h"

stack_t* scope_stack;

comp_dict_t* funcs_params;

char* current_type_decl;

char* current_func_decl;


/* tipos semanticos */
#define SMTC_VOID -1
#define SMTC_INT 1
#define SMTC_FLOAT 2
#define SMTC_CHAR 3
#define SMTC_STRING 4
#define SMTC_BOOL 5
#define SMTC_USER_TYPE_VAR 6
#define SMTC_USER_TYPE_NAME 7

/* variavel, vetor ou funcao ?*/
#define SMTC_VARIABLE 1
#define SMTC_VECTOR 2
#define SMTC_FUNCTION 3

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
#define SMTC_ERROR_FIELD 15 //identificador deve ser utilizado como campo
#define SMTC_ERROR_INVALID_FIELD 16 //identificador não é campo de um dado tipo

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


void remove_collisions_funcs_params(comp_dict_item_t * item);

/**
  * Libera os espacos de memoria ocupados pelos ponteiros da tabela de simbolos
  */
void clearFuncParams();

/**
  * Coloca parametros no dicionario de parametros das funcoes
  */
void putToFuncsParams(char *func_name, st_value_t *st_param);

stack_t* get_scope_stack();

void pop_and_free_scope();

void clear_scope_stack_values();

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
 * Seta, num Value de entrada de tabela de simbolos, o tipo semantico, seu tamanho e que é uma funcao
 */
void set_st_semantic_type_and_size_primitive_function(int semantic_type, st_value_t* symbols_table_entry);

/**
 * Seta, num Value de entrada de tabela de simbolos, o tipo semantico, seu tamanho e que é uma funcao user type
 */
void set_st_semantic_type_and_size_user_type_function(char* type_name, st_value_t* variable_entry);

/**
 * Seta, num Value de entrada de tabela de simbolos de um vetor, o tipo semantico e seu tamanho
 */
void set_st_semantic_type_and_size_vector(int semantic_type, int length, int vector_dimension, st_value_t* symbols_table_entry);

/**
 * Seta, num Value de entrada de tabela de simbolos de uma variavel de tipo de usuario, o tipo semantico e seu tamanho
 */
void set_st_semantic_type_and_size_user_type(char* type_name, st_value_t* variable_entry);

/**
 * Seta, num Value de entrada de tabela de simbolos de um vetor de tipo de usuario, o tipo semantico e seu tamanho
 */
void set_st_semantic_type_and_size_vector_user_type(char* type_name, st_value_t* variable_entry, int length, int vector_dimension);

/**
 * Seta, num Value de entrada de tabela de simbolos de um campo de tipo de usuario, o tipo semantico e sua classe relacionada
 */
void set_st_semantic_type_and_size_primitive_field(int semantic_type, st_value_t* symbols_table_entry);

/**
 * Seta, num Value de entrada de tabela de simbolos de um campo de vetor, o tamanho, o tipo semantico e sua classe relacionada
 */
void set_st_semantic_type_and_size_vector_field(int semantic_type, int length, st_value_t* symbols_table_entry);

/**
* Retorna o tipo semantico de um elemento de um vetor
*/
int get_semantic_type_of_indexed_vector(int vector_semantic_type);

/**
* Retorna o tipo semantico de um vetor cujo tipo dos elementos é o passado por parametro
*/
int get_semantic_type_vector_from_element(int vector_semantic_type);

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

/**
 * Garante que, se nodos forem de tipos de usuario, o tipo de usuario é o mesmo
 */
void verify_matching_user_types(st_value_t* st_entry, ast_node_value_t* ast_expression);

/**
 * Retorna a tabela de símbolos "atual" (do topo da pilha)
 */
comp_dict_t* getCurrentST();

/**
 * Coloca o token na tabela de simbolos "atual" (do topo da pilha)
 * @return st_value_t* entryValue
 */
st_value_t* putToCurrentST(char* key, int line, int token_type);

/**
 * Procura um identificador na tabela de simbolos "atual" (do topo da pilha)
 */
st_value_t* search_id_in_current_st(char* key);

/**
 * Procura um identificador na tabela de simbolos global
 */
st_value_t* search_id_in_global_st(char* key);

/**
 * Checa na tabela de simbolos global se tipo ja foi declarado.
 * Se não tiver sido, da erro
 */
st_value_t* ensure_type_declared(char* type_name);

/**
* Verifica na tabela de simbolos atual (do topo da pilha) se tipo ja foi declarado.
* Se já tiver sido, da erro.
*/
void ensure_type_not_declared(char* id_name);

/**
 * Verifica na tabela de simbolos atual (do topo da pilha) se identificador ja foi declarado.
 * Se já tiver sido, da erro.
 */
void ensure_identifier_not_declared(char* id_name);

/**
 * Verifica na tabela de simbolos atual (do topo da pilha) se identificador ja foi declarado.
 * Se não tiver sido, da erro.
 */
st_value_t* ensure_identifier_declared(char* id_name);

/**
 * Verifica na tabela de simbolos global se campo ja foi declarado.
 * Se não tiver sido, da erro.
 */
st_value_t* ensure_field_declared(char* field_name, char* related_user_type);

/**
 * Verifica na tabela de simbolos global se funcao ja foi declarada.
 * Se não tiver sido, da erro.
 */
st_value_t* ensure_function_declared(char* function_name);

/**
 * Verifica na tabela de simbolos global se variavel ja foi declarada.
 * Se não tiver sido, da erro.
 */
st_value_t* ensure_variable_declared(char* variable_name);

/**
 * Verifica na tabela de simbolos global se vetor ja foi declarado.
 * Se não tiver sido, da erro.
 */
st_value_t* ensure_vector_declared(char* vector_name);

/**
 * Verifica se expressao pode ser parametro de um input.
 * Se não puder, da erro
 */
void ensure_inputable(ast_node_value_t* expression);

/**
 * Verifica se expressao pode ser parametro de um output.
 * Se não puder, da erro
 */
void ensure_outputable(ast_node_value_t* expression);

/**
 * Retorna char* com string correspondente ao var_vec_or_fun do parametro fornecido
 */
char* var_vec_or_fun_to_string(st_value_t* st_entry);

/**
 * Retorna int com erro correspondente ao var_vec_or_fun fornecido
 */
int get_semantic_error_var_vec_or_fun(st_value_t* st_entry);

/**
 * avalia se um ast_node_value_t é uma expressao aritmética (valor int ou float)
 */
bool is_arit_expression(ast_node_value_t* ast);

/**
 * Setter pra current_type_decl
 */
void set_current_type_decl(char* type_decl);

/**
 * Getter pra current_type_decl
 */
char* get_current_type_decl();

void set_current_func_decl(char* func_decl);

char* get_current_func_decl();

char* semantic_type_to_string(int semantic_type);

void ensure_return_type_is_correct(ast_node_value_t* ast_expression);

void ensure_return_type_user_is_correct(ast_node_value_t* ast_expression);

/**
 * Infere um tipo resultante ou da erro, no contexto de um retorno de funcao
 */
int infere_primitive_type_return(int first_type, int second_type);

stack_t* ensure_number_of_parameters(char *func_name, comp_tree_t *tree);

stack_t* ensure_parameters_type(char *func_name, comp_tree_t *parameters_tree);

stack_t* ensure_function_has_no_parameters(char *func_name);

void stack_print(stack_t *stack_aux);

void stack_print_params(stack_t *stack_aux);

st_value_t* search_id_in_stack_sts(char* key);

#endif
