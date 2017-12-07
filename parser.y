/*
  Arthur Adolfo 						- 	00262515
  Gabriel de Souza Seibel 	- 	00262513
*/
%code requires{
#include "parser.h" //arquivo automaticamente gerado pelo bison
#include "main.h"
#include "cc_ast.h"
#include "syntax_tree.h"
#include "symbols_table.h"
#include "semantics.h"
#include "tac.h"
#include "cc_misc.h" //arquivo com funcoes de auto incremento
}

%union
{
	comp_tree_t *tree;
	int semantic_type;
	int size;
	void *valor_lexico;   /* Pointer to run-time expression operator */
	st_vector_size *vector_size;
}

/* Declaração dos tokens da linguagem */
%token TK_PR_INT
%token TK_PR_FLOAT
%token TK_PR_BOOL
%token TK_PR_CHAR
%token TK_PR_STRING
%token TK_PR_IF
%token TK_PR_THEN
%token TK_PR_ELSE
%token TK_PR_WHILE
%token TK_PR_DO
%token TK_PR_INPUT
%token TK_PR_OUTPUT
%token TK_PR_RETURN
%token TK_PR_CONST
%token TK_PR_STATIC
%token TK_PR_FOREACH
%token TK_PR_FOR
%token TK_PR_SWITCH
%token TK_PR_CASE
%token TK_PR_BREAK
%token TK_PR_CONTINUE
%token TK_PR_CLASS
%token TK_PR_PRIVATE
%token TK_PR_PUBLIC
%token TK_PR_PROTECTED
%token TK_OC_LE
%token TK_OC_GE
%token TK_OC_EQ
%token TK_OC_NE
%token TK_OC_AND
%token TK_OC_OR
%token TK_OC_SL
%token TK_OC_SR
%token TK_LIT_INT
%token TK_LIT_FLOAT
%token TK_LIT_FALSE
%token TK_LIT_TRUE
%token TK_LIT_CHAR
%token TK_LIT_STRING
%token TK_IDENTIFICADOR
%token TOKEN_ERRO


%type<valor_lexico> TK_IDENTIFICADOR
%type<valor_lexico> TK_LIT_INT
%type<valor_lexico> TK_LIT_FLOAT
%type<valor_lexico> TK_LIT_FALSE
%type<valor_lexico> TK_LIT_TRUE
%type<valor_lexico> TK_LIT_CHAR
%type<valor_lexico> TK_LIT_STRING
%type<vector_size> vector_declaration
%type<vector_size> vector_declaration_loop
%type<tree> prime_programa
%type<tree> programa
%type<tree> def_function
%type<tree> func_name
%type<tree> func_name_user
%type<tree> body
%type<tree> command_sequence
%type<tree> command_in_block
%type<tree> simple_command
%type<tree> action_command
%type<tree> attribution_command
%type<tree> flux_command
%type<tree> iteration_command
%type<tree> for_command_sequence
%type<tree> foreach_expression_sequence
%type<tree> condition_command
%type<tree> selection_command
%type<tree> shift_command
%type<tree> io_command
%type<tree> input_command
%type<tree> output_command
%type<tree> def_local_var
%type<tree> function_call
%type<tree> attribution_vector
%type<tree> attribution_vector_loop
%type<tree> expression
%type<tree> sub_expression
%type<tree> sub_expression_1
%type<tree> sub_expression_chain
%type<tree> expression_sequence
%type<tree> unary_operator
%type<tree> operator
%type<tree> logic_operator
%type<tree> literal
%type<tree> block
%type<semantic_type> primitive_type
%type<size> type_fields
%type<size> type_field

%%
/* Regras (e ações) da gramática */

// programa

prime_programa: programa
{
	$$ = tree_new();
	set_ast_root($$);
	$$->value = new_ast_node_value(AST_PROGRAMA, SMTC_VOID, NULL, NULL);

	if ($1) {
		tree_insert_node($$, $1);
		//concatena codigo
		ast_node_value_t* program = $1->value;
		ast_node_value_t* head = $$->value;
		stack_push_all_tacs(head->tac_stack, program->tac_stack);
	}

	gv_declare(AST_PROGRAMA, $$, NULL);
	putToGraphviz($$);

	//associa tabela de simbolos ao nodo AST
	((ast_node_value_t*)$$->value)->symbols_table = getCurrentST();
	#ifdef DEBUG
		print_st(((ast_node_value_t*)$$->value)->symbols_table);
	#endif
}

programa: %empty { $$ = NULL; }
programa: def_type programa { if ($2) $$ = $2; else $$ = NULL; }
programa: def_global_var programa { if ($2) $$ = $2; else $$ = NULL; }
programa: def_function programa
{
	if ($2) {
		tree_insert_node($1,$2);
		//concatena codigo
		ast_node_value_t* more_program = $2->value;
		ast_node_value_t* head = $$->value;
		stack_push_all_tacs(head->tac_stack, more_program->tac_stack);
	}
	$$ = $1;
}


//declaracao de globais

vector_declaration: '[' TK_LIT_INT ']' vector_declaration_loop
{
	st_vector_size *vector_size = (st_vector_size*) malloc(sizeof(vector_size));
	st_value_t* st_entry_lit_int = $2;
	vector_size->size = st_entry_lit_int->value.i*$4->size;
	vector_size->vector_dimension = $4->vector_dimension+1;
	free($4);
	$$ = vector_size;

	stack_push(&st_entry_lit_int->value.i ,current_vector_stack);
}


vector_declaration_loop: '[' TK_LIT_INT ']' vector_declaration_loop
{
	st_vector_size *vector_size = (st_vector_size*) malloc(sizeof(vector_size));
	st_value_t* st_entry_lit_int = $2;
	vector_size->size = st_entry_lit_int->value.i*$4->size;
	vector_size->vector_dimension = $4->vector_dimension+1;
	free($4);
	$$ = vector_size;

	stack_push(&st_entry_lit_int->value.i ,current_vector_stack);
}
vector_declaration_loop: %empty
{
	st_vector_size *vector_size = (st_vector_size*) malloc(sizeof(vector_size));
	vector_size->size = 1;
	vector_size->vector_dimension = 0;
	$$ = vector_size;
}

def_global_var: primitive_type TK_IDENTIFICADOR ';'
{
	char* id_name = $2;

	//verifica declaracao anterior do identificador
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador = putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive($1, st_identificador);

	//Calcula endereço da variável global
	st_identificador->offset_address = calculateGlobalAddress(st_identificador->size);
	//printf("offset: %d\n", st_identificador->offset_address);
	free(id_name);

	//setar base register
	st_identificador->address_base = RBSS;
}
def_global_var: primitive_type TK_IDENTIFICADOR vector_declaration ';'
{
	char* id_name = $2;

	//verifica declaracao anterior do identificador
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador =	putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);

	int size = $3->size;
	int vector_dimension = $3->vector_dimension;
	set_st_semantic_type_and_size_vector($1, size, vector_dimension, st_identificador);

	//Calcula endereço da variável global
	st_identificador->offset_address = calculateGlobalAddress(st_identificador->size);
	//printf("offset: %d\n", st_identificador->offset_address);

	free($3);
	free(id_name);

	//setar base register
	st_identificador->address_base = RBSS;

	//setar tamanho de cada dimensao do vetor
	stack_push_stacks(NULL, current_vector_stack, st_identificador->vector_sizes);
	free_stack(current_vector_stack);
	current_vector_stack = new_stack();
}
def_global_var: TK_PR_STATIC primitive_type TK_IDENTIFICADOR ';'
{
	char* id_name = $3;

	//verifica declaracao anterior do identificador
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador =	putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive($2, st_identificador);

	//Calcula endereço da variável global
	st_identificador->offset_address = calculateGlobalAddress(st_identificador->size);

	free(id_name);

	//setar base register
	st_identificador->address_base = RBSS;
}
def_global_var: TK_PR_STATIC primitive_type TK_IDENTIFICADOR vector_declaration ';'
{
	char* id_name = $3;

	//verifica declaracao anterior do identificador
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador =	putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);

	int size = $4->size;
	int vector_dimension = $4->vector_dimension;
	set_st_semantic_type_and_size_vector($2, size, vector_dimension, st_identificador);

	//Calcula endereço da variável global
	st_identificador->offset_address = calculateGlobalAddress(st_identificador->size);
	//printf("offset: %d\n", st_identificador->offset_address);

	free($4);
	free(id_name);

	//setar base register
	st_identificador->address_base = RBSS;

	//setar tamanho de cada dimensao do vetor
	stack_push_stacks(NULL, current_vector_stack, st_identificador->vector_sizes);
	free_stack(current_vector_stack);
	current_vector_stack = new_stack();
}

def_global_var: TK_IDENTIFICADOR TK_IDENTIFICADOR ';'
{
	//verifica se tipo existe
	ensure_type_declared($1);

	//verifica declaracao anterior do identificador
	char* id_name = $2;
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador =	putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_user_type($1, st_identificador);

	//Calcula endereço da variável global
	st_identificador->offset_address = calculateGlobalAddress(st_identificador->size);
	//printf("offset: %d\n", st_identificador->offset_address);

	free($1);
	free(id_name);

	//setar base register
	st_identificador->address_base = RBSS;
}
def_global_var: TK_IDENTIFICADOR TK_IDENTIFICADOR vector_declaration ';'
{
	//verifica se tipo existe
	ensure_type_declared($1);

	//verifica declaracao anterior do identificador
	char* id_name = $2;
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador =	putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);

	int size = $3->size;
	int vector_dimension = $3->vector_dimension;
	set_st_semantic_type_and_size_vector_user_type($1, st_identificador, size, vector_dimension);

	//Calcula endereço da variável global
	st_identificador->offset_address = calculateGlobalAddress(st_identificador->size);
	//printf("offset: %d\n", st_identificador->offset_address);

	free($3);
	free($1);
	free(id_name);

	//setar base register
	st_identificador->address_base = RBSS;

	//setar tamanho de cada dimensao do vetor
	stack_push_stacks(NULL, current_vector_stack, st_identificador->vector_sizes);
	free_stack(current_vector_stack);
	current_vector_stack = new_stack();
}
def_global_var: TK_PR_STATIC TK_IDENTIFICADOR TK_IDENTIFICADOR ';'
{
	//verifica se tipo ($2) existe
	ensure_type_declared($2);

	//verifica declaracao anterior do identificador
	char* id_name = $3;
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador =	putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_user_type($2, st_identificador);

	//Calcula endereço da variável global
	st_identificador->offset_address = calculateGlobalAddress(st_identificador->size);
	//printf("offset: %d\n", st_identificador->offset_address);

	free($2);
	free(id_name);

	//setar base register
	st_identificador->address_base = RBSS;
}
def_global_var: TK_PR_STATIC TK_IDENTIFICADOR TK_IDENTIFICADOR vector_declaration ';'
{
	//verifica se tipo ($2) existe
	ensure_type_declared($2);

	//verifica declaracao anterior do identificador
	char* id_name = $3;
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador =	putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);

	int size = $4->size;
	int vector_dimension = $4->vector_dimension;
	set_st_semantic_type_and_size_vector_user_type($2, st_identificador, size, vector_dimension);

	//Calcula endereço da variável global
	st_identificador->offset_address = calculateGlobalAddress(st_identificador->size);
	//printf("offset: %d\n", st_identificador->offset_address);

	free($4);
	free($2);
	free(id_name);

	//setar base register
	st_identificador->address_base = RBSS;

	//setar tamanho de cada dimensao do vetor
	stack_push_stacks(NULL, current_vector_stack, st_identificador->vector_sizes);
	free_stack(current_vector_stack);
	current_vector_stack = new_stack();
}


push_func_stack: %empty
{
	comp_dict_t *func_symbols_table = dict_new();
	stack_push(func_symbols_table, get_scope_stack());
}

func_name: primitive_type TK_IDENTIFICADOR
{
	//verifica declaracao anterior do identificador
	char* id_name = $2;
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador =	putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);

	$$ = tree_make_node(new_ast_node_value(AST_FUNCAO, SMTC_VOID, NULL, st_identificador));
	set_st_semantic_type_and_size_primitive_function($1, st_identificador);
	set_current_func_decl(id_name);

	free(id_name);
}

func_name_user: TK_IDENTIFICADOR TK_IDENTIFICADOR
{
	//verifica se tipo ($1) existe
	ensure_type_declared($1);

	//verifica declaracao anterior do identificador
	char* id_name = $2;
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador =	putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);

	$$ = tree_make_node(new_ast_node_value(AST_FUNCAO, SMTC_VOID, NULL, st_identificador));
	set_st_semantic_type_and_size_user_type_function($1, st_identificador);
	set_current_func_decl(id_name);

	free($1);
	free(id_name);
}


def_function: func_name push_func_stack '(' parameters ')' body
{
	$$ = $1;

	ast_node_value_t* head = $$->value;

	if ($6) {
		tree_insert_node($$,$6);
		//concatena codigo
		ast_node_value_t* cmd_seq = $6->value;
		stack_push_all_tacs(head->tac_stack, cmd_seq->tac_stack);
	}

	//associa tabela de simbolos ao nodo AST
	((ast_node_value_t*)$$->value)->symbols_table = getCurrentST();
	#ifdef DEBUG
		print_st(((ast_node_value_t*)$$->value)->symbols_table);
	#endif

	//ao sair da declaracao de funcao, da pop na pilha de declaracoes
	pop_and_free_scope();

	#ifdef DEBUG
		if (!head->tac_stack->empty) {
			printf("\n\n_____ CÓDIGO FUNÇÃO [linha %d]_____", comp_get_line_number());
			print_tac_stack(&head->tac_stack);
		}
	#endif
}
def_function: TK_PR_STATIC func_name push_func_stack '(' parameters ')' body
{
	$$ = $2;

	ast_node_value_t* head = $$->value;

	if ($7) {
		tree_insert_node($$,$7);
		//concatena codigo
		ast_node_value_t* cmd_seq = $7->value;
		stack_push_all_tacs(head->tac_stack, cmd_seq->tac_stack);
	}

	//associa tabela de simbolos ao nodo AST
	((ast_node_value_t*)$$->value)->symbols_table = getCurrentST();
	#ifdef DEBUG
		print_st(((ast_node_value_t*)$$->value)->symbols_table);
	#endif

	//ao sair da declaracao de funcao, da pop na pilha de declaracoes
	pop_and_free_scope();

	// if (!head->tac_stack->empty) {
	// 	printf("\n\n_____ CÓDIGO FUNÇÃO [linha %d]_____", comp_get_line_number());
	// 	print_tac_stack(&head->tac_stack);
	// }
}

def_function: func_name_user push_func_stack '(' parameters ')' body
{
	$$ = $1;

	ast_node_value_t* head = $$->value;

	if ($6) {
		tree_insert_node($$,$6);
		//concatena codigo
		ast_node_value_t* cmd_seq = $6->value;
		stack_push_all_tacs(head->tac_stack, cmd_seq->tac_stack);
	}

	//associa tabela de simbolos ao nodo AST
	((ast_node_value_t*)$$->value)->symbols_table = getCurrentST();
	#ifdef DEBUG
		print_st(((ast_node_value_t*)$$->value)->symbols_table);
	#endif

	//ao sair da declaracao de funcao, da pop na pilha de declaracoes
	pop_and_free_scope();

	// if (!head->tac_stack->empty) {
	// 	printf("\n\n_____ CÓDIGO FUNÇÃO [linha %d]_____", comp_get_line_number());
	// 	print_tac_stack(&head->tac_stack);
	// }

}
def_function: TK_PR_STATIC func_name_user push_func_stack '(' parameters ')' body
{
	$$ = $2;

	ast_node_value_t* head = $$->value;

	if ($7) {
		tree_insert_node($$,$7);
		//concatena codigo
		ast_node_value_t* cmd_seq = $7->value;
		stack_push_all_tacs(head->tac_stack, cmd_seq->tac_stack);
	}

	//associa tabela de simbolos ao nodo AST
	((ast_node_value_t*)$$->value)->symbols_table = getCurrentST();
	#ifdef DEBUG
		print_st(((ast_node_value_t*)$$->value)->symbols_table);
	#endif

	//ao sair da declaracao de funcao, da pop na pilha de declaracoes
	pop_and_free_scope();

	// if (!head->tac_stack->empty) {
	// 	printf("\n\n_____ CÓDIGO FUNÇÃO [linha %d]_____", comp_get_line_number());
	// 	print_tac_stack(&head->tac_stack);
	// }
}

body: '{' command_sequence '}'
{
	$$ = tree_make_node(new_ast_node_value(AST_BLOCO, SMTC_VOID, NULL, NULL));
	ast_node_value_t* head = $$->value;

	if ($2) {
		tree_insert_node($$,$2);
		//concatena codigo
		ast_node_value_t* cmd_seq = $2->value;
		stack_push_all_tacs(head->tac_stack, cmd_seq->tac_stack);
	}

	// if (!head->tac_stack->empty) {
	// 	printf("\n\n_____ CÓDIGO BODY [linha %d]_____", comp_get_line_number());
	// 	print_tac_stack(&head->tac_stack);
	// }
}

parameters: %empty
parameters: parameter
parameters: parameter parameter_chain

parameter_chain: ',' parameter
parameter_chain: ',' parameter parameter_chain

parameter: primitive_type TK_IDENTIFICADOR
{
	//verifica declaracao anterior do identificador
	char* id_name = $2;
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive($1, st_identificador);

    putToFuncsParams(get_current_func_decl(), st_identificador);

	//Calcula endereço da variável global
	st_identificador->offset_address = calculateLocalAddress(st_identificador->size);
	//printf("local offset: %d\n", st_identificador->offset_address);

	free(id_name);
}
parameter: TK_PR_CONST primitive_type TK_IDENTIFICADOR
{
	//verifica declaracao anterior do identificador
	char* id_name = $3;
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive($2, st_identificador);
	putToFuncsParams(get_current_func_decl(), st_identificador);

	//Calcula endereço da variável global
	st_identificador->offset_address = calculateLocalAddress(st_identificador->size);
	//printf("local offset: %d\n", st_identificador->offset_address);

	free(id_name);
}
parameter: TK_IDENTIFICADOR TK_IDENTIFICADOR
{
	//verifica se tipo existe
	ensure_type_declared($1);

	//verifica declaracao anterior do identificador
	char* id_name = $2;
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_user_type($1, st_identificador);
	putToFuncsParams(get_current_func_decl(), st_identificador);

	//Calcula endereço da variável global
	st_identificador->offset_address = calculateLocalAddress(st_identificador->size);
	//printf("local offset: %d\n", st_identificador->offset_address);

	free($1);
	free(id_name);
}
parameter: TK_PR_CONST TK_IDENTIFICADOR TK_IDENTIFICADOR
{
	//verifica se tipo existe
	ensure_type_declared($2);

	//verifica declaracao anterior do identificador
	char* id_name = $3;
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_user_type($2, st_identificador);
	putToFuncsParams(get_current_func_decl(), st_identificador);

	//Calcula endereço da variável global
	st_identificador->offset_address = calculateLocalAddress(st_identificador->size);
	//printf("local offset: %d\n", st_identificador->offset_address);

	free($2);
	free(id_name);
}

command_sequence: %empty { $$ = NULL; }
command_sequence: command_in_block ';' command_sequence
{
	if ($1) {
		$$ = $1;
		if ($3) {
			tree_insert_node($$,$3);
			//concatenar codigo
			ast_node_value_t* head = $$->value;
			ast_node_value_t* cmd_list = $3->value;
  		stack_push_all_tacs(head->tac_stack, cmd_list->tac_stack);
		}
	} else {
		$$ = $3;
	}
}
command_sequence: case_command ':' command_sequence { $$ = $3; }
case_command: TK_PR_CASE TK_LIT_INT

command_in_block: simple_command
{
	$$ = $1;
	//ast_node_value_t* ast_node_value_head = $$->value;
	//print_tac_stack(&(ast_node_value_head->tac_stack));
}
command_in_block: io_command { $$ = $1; }
command_in_block: action_command { $$ = $1; }

push_block_stack: '{'
{
	comp_dict_t *func_symbols_table = dict_new();
	stack_push(func_symbols_table, get_scope_stack());
}

simple_command: attribution_command { $$ = $1; }
simple_command: function_call { $$ = $1; }
simple_command: shift_command { $$ = $1; }
simple_command: def_local_var { $$ = $1; }
simple_command: flux_command { $$ = $1; }
simple_command: block { $$ = $1; }

block: push_block_stack command_sequence '}'
{
	$$ = tree_make_node(new_ast_node_value(AST_BLOCO, SMTC_VOID, NULL, NULL));
	ast_node_value_t* head = $$->value;

	if ($2) {
		tree_insert_node($$,$2);
		//concatenar de codigo
		ast_node_value_t* cmd_seq = $2->value;
		stack_push_all_tacs(head->tac_stack, cmd_seq->tac_stack);
	}

	// if (!head->tac_stack->empty) {
	// 	printf("\n\n_____ CÓDIGO BLOCK [linha %d]_____", comp_get_line_number());
	// 	print_tac_stack(&head->tac_stack);
	// }

	//associa tabela de simbolos ao nodo AST
	((ast_node_value_t*)$$->value)->symbols_table = getCurrentST();
	#ifdef DEBUG
		print_st(((ast_node_value_t*)$$->value)->symbols_table);
	#endif

	pop_and_free_scope();
}

io_command: input_command { $$ = $1; }
io_command: output_command { $$ = $1; }

def_local_var: TK_IDENTIFICADOR TK_IDENTIFICADOR
{
	//verifica se tipo existe
	ensure_type_declared($1);

	//verifica declaracao anterior do identificador
	char* id_name = $2;
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_user_type($1, st_identificador);

	//Calcula endereço da variável local
	st_identificador->offset_address = calculateLocalAddress(st_identificador->size);
	//printf("local offset: %d\n", st_identificador->offset_address);
	//seta base do endereco da variavel
	st_identificador->address_base = RARP;

	free($1);
	free(id_name);

	$$ = NULL;
}
def_local_var: primitive_type TK_IDENTIFICADOR
{
	char* id_name = $2;
	ensure_identifier_not_declared(id_name);

	//insere identificador declarado na tabela de simbolos atual (topo da pilha)
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive($1, st_identificador);

	//Calcula endereço da variável local
	st_identificador->offset_address = calculateLocalAddress(st_identificador->size);
	//printf("local offset: %d\n", st_identificador->offset_address);
	//seta base do endereco da variavel
	st_identificador->address_base = RARP;

	free(id_name);

	$$ = NULL;
}
def_local_var: primitive_type TK_IDENTIFICADOR TK_OC_LE expression
{
	char* id_name = $2;
	ensure_identifier_not_declared(id_name);

	//insere identificador declarado na tabela de simbolos atual (topo da pilha)
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive($1, st_identificador);

	ast_node_value_t* ast_expression = $4->value;

	//st_value_t* entry_expression = ast_expression->symbols_table_entry;
	//st_identificador->count_char = entry_expression->count_char;
	//printf("count char: %d\n", st_identificador->count_char);

	//checar se tipos são compativeis
	mark_coercion(st_identificador->semantic_type, ast_expression);

	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, $1, NULL, st_identificador));
	$$ = tree_make_binary_node(new_ast_node_value(AST_ATRIBUICAO, SMTC_VOID, NULL, NULL), node_identificador, $4);

	//Calcula endereço da variável local
	st_identificador->offset_address = calculateLocalAddress(st_identificador->size);
	//printf("local offset: %d\n", st_identificador->offset_address);
	//seta base do endereco da variavel
	st_identificador->address_base = RARP;

	free(id_name);

	ast_node_value_t* ast_head_value = $$->value;
	ast_head_value->symbols_table_entry = st_identificador;
	generate_code_attribution_var(ast_head_value, ast_expression);
}
def_local_var: TK_PR_STATIC TK_IDENTIFICADOR TK_IDENTIFICADOR
{
	//verifica se tipo existe
	ensure_type_declared($2);

	//verifica declaracao anterior do identificador
	char* id_name = $3;
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_user_type($2, st_identificador);

	//Calcula endereço da variável local
	st_identificador->offset_address = calculateLocalAddress(st_identificador->size);
	//printf("local offset: %d\n", st_identificador->offset_address);
	//seta base do endereco da variavel
	st_identificador->address_base = RBSS;

	$$ = NULL;

	free($2);
	free(id_name);
}
def_local_var: TK_PR_STATIC primitive_type TK_IDENTIFICADOR
{
	char* id_name = $3;
	ensure_identifier_not_declared(id_name);

	//insere identificador declarado na tabela de simbolos atual (topo da pilha)
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive($2, st_identificador);

	//Calcula endereço da variável local
	st_identificador->offset_address = calculateLocalAddress(st_identificador->size);
	//printf("local offset: %d\n", st_identificador->offset_address);
	//seta base do endereco da variavel
	st_identificador->address_base = RBSS;

	$$ = NULL;

	free(id_name);
}
def_local_var: TK_PR_STATIC primitive_type TK_IDENTIFICADOR TK_OC_LE expression
{
	char* id_name = $3;
	ensure_identifier_not_declared(id_name);

	//insere identificador declarado na tabela de simbolos atual (topo da pilha)
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive($2, st_identificador);

	ast_node_value_t* ast_expression = $5->value;

	//st_value_t* entry_expression = ast_expression->symbols_table_entry;
	//st_identificador->count_char = entry_expression->count_char;
	//printf("count char: %d\n", st_identificador->count_char);

	//checar se tipos são compativeis
	mark_coercion(st_identificador->semantic_type, ast_expression);

	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, $2, NULL, st_identificador));
	$$ = tree_make_binary_node(new_ast_node_value(AST_ATRIBUICAO, SMTC_VOID, NULL, NULL), node_identificador, $5);

	//Calcula endereço da variável local
	st_identificador->offset_address = calculateLocalAddress(st_identificador->size);
	//printf("local offset: %d\n", st_identificador->offset_address);
	//seta base do endereco da variavel
	st_identificador->address_base = RBSS;

	free(id_name);

	ast_node_value_t* ast_head_value = $$->value;
	ast_head_value->symbols_table_entry = st_identificador;
	generate_code_attribution_var(ast_head_value, ast_expression);
}
def_local_var: TK_PR_CONST TK_IDENTIFICADOR TK_IDENTIFICADOR
{
	//verifica se tipo existe
	ensure_type_declared($2);

	//verifica declaracao anterior do identificador
	char* id_name = $3;
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_user_type($2, st_identificador);

	//Calcula endereço da variável local
	st_identificador->offset_address = calculateLocalAddress(st_identificador->size);
	//printf("local offset: %d\n", st_identificador->offset_address);
	//seta base do endereco da variavel
	st_identificador->address_base = RARP;

	$$ = NULL;

	free($2);
	free(id_name);
}
def_local_var: TK_PR_CONST primitive_type TK_IDENTIFICADOR
{
	char* id_name = $3;
	ensure_identifier_not_declared(id_name);

	//insere identificador declarado na tabela de simbolos atual (topo da pilha)
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive($2, st_identificador);

	//Calcula endereço da variável local
	st_identificador->offset_address = calculateLocalAddress(st_identificador->size);
	//printf("local offset: %d\n", st_identificador->offset_address);
	//seta base do endereco da variavel
	st_identificador->address_base = RARP;

	$$ = NULL;

	free(id_name);
}
def_local_var: TK_PR_CONST primitive_type TK_IDENTIFICADOR TK_OC_LE expression
{
	char* id_name = $3;
	ensure_identifier_not_declared(id_name);

	//insere identificador declarado na tabela de simbolos atual (topo da pilha)
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive($2, st_identificador);

	ast_node_value_t* ast_expression = $5->value;

	//st_value_t* entry_expression = ast_expression->symbols_table_entry;
	//st_identificador->count_char = entry_expression->count_char;
	//printf("count char: %d\n", st_identificador->count_char);

	//checar se tipos são compativeis
	mark_coercion(st_identificador->semantic_type, ast_expression);

	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, $2, NULL, st_identificador));
	$$ = tree_make_binary_node(new_ast_node_value(AST_ATRIBUICAO, SMTC_VOID, NULL, NULL), node_identificador, $5);

	//Calcula endereço da variável local
	st_identificador->offset_address = calculateLocalAddress(st_identificador->size);
	//printf("local offset: %d\n", st_identificador->offset_address);
	//seta base do endereco da variavel
	st_identificador->address_base = RARP;

	free(id_name);

	ast_node_value_t* ast_head_value = $$->value;
	ast_head_value->symbols_table_entry = st_identificador;
	generate_code_attribution_var(ast_head_value, ast_expression);
}
def_local_var: TK_PR_STATIC TK_PR_CONST TK_IDENTIFICADOR TK_IDENTIFICADOR
{
	//verifica se tipo existe
	ensure_type_declared($3);

	//verifica declaracao anterior do identificador
	char* id_name = $4;
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_user_type($3, st_identificador);

	//Calcula endereço da variável local
	st_identificador->offset_address = calculateLocalAddress(st_identificador->size);
	//printf("local offset: %d\n", st_identificador->offset_address);
	//seta base do endereco da variavel
	st_identificador->address_base = RBSS;

	$$ = NULL;

	free($3);
	free(id_name);
}
def_local_var: TK_PR_STATIC TK_PR_CONST primitive_type TK_IDENTIFICADOR
{
	char* id_name = $4;
	ensure_identifier_not_declared(id_name);

	//insere identificador declarado na tabela de simbolos atual (topo da pilha)
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive($3, st_identificador);

	//Calcula endereço da variável local
	st_identificador->offset_address = calculateLocalAddress(st_identificador->size);
	//printf("local offset: %d\n", st_identificador->offset_address);
	//seta base do endereco da variavel
	st_identificador->address_base = RBSS;

	$$ = NULL;

	free(id_name);
}
def_local_var: TK_PR_STATIC TK_PR_CONST primitive_type TK_IDENTIFICADOR TK_OC_LE expression
{
	char* id_name = $4;
	ensure_identifier_not_declared(id_name);

	//insere identificador declarado na tabela de simbolos atual (topo da pilha)
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive($3, st_identificador);

	ast_node_value_t* ast_expression = $6->value;

	//st_value_t* entry_expression = ast_expression->symbols_table_entry;
	//st_identificador->count_char = entry_expression->count_char;
	//printf("count char: %d\n", st_identificador->count_char);

	//checar se tipos são compativeis
	mark_coercion(st_identificador->semantic_type, ast_expression);

	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, $3, NULL, st_identificador));
	$$ = tree_make_binary_node(new_ast_node_value(AST_ATRIBUICAO, SMTC_VOID, NULL, NULL), node_identificador, $6);

	//Calcula endereço da variável local
	st_identificador->offset_address = calculateLocalAddress(st_identificador->size);
	//printf("local offset: %d\n", st_identificador->offset_address);
	//seta base do endereco da variavel
	st_identificador->address_base = RBSS;

	free(id_name);

	ast_node_value_t* ast_head_value = $$->value;
	ast_head_value->symbols_table_entry = st_identificador;
	generate_code_attribution_var(ast_head_value, ast_expression);
}

attribution_vector: '[' expression ']' attribution_vector_loop
{
	//verifica se indice é int
	ast_node_value_t* ast_index = $2->value;
	mark_coercion(SMTC_INT, ast_index);
	if($4) {
		comp_tree_t* node_vetor_indexado = tree_make_binary_node(new_ast_node_value(AST_VETOR_INDEXADO, SMTC_INT,
			NULL, NULL), $2, $4);
		ast_node_value_t* ast_vector = node_vetor_indexado->value;
		ast_node_value_t* ast_aux = $4->value;
		ast_vector->vector_dimension = 1+ast_aux->vector_dimension;
		$$ = node_vetor_indexado;
	}
	else  {
		ast_index->vector_dimension = 1;
		$$ = $2;
	}

	//colocar registradore de resultado na pilha
	stack_push(ast_index, current_vector_stack);
}

attribution_vector_loop: '[' expression ']' attribution_vector_loop
{
	//verifica se indice é int
	ast_node_value_t* ast_index = $2->value;
	mark_coercion(SMTC_INT, ast_index);
	if($4) {
		comp_tree_t* node_vetor_indexado = tree_make_binary_node(new_ast_node_value(AST_VETOR_INDEXADO, SMTC_INT,
			NULL, NULL), $2, $4);
		ast_node_value_t* ast_vector = node_vetor_indexado->value;
		ast_node_value_t* ast_aux = $4->value;
		ast_vector->vector_dimension = 1+ast_aux->vector_dimension;
		$$ = node_vetor_indexado;
	}
	else  {
		ast_index->vector_dimension = 1;
		$$ = $2;
	}

	//colocar registradore de resultado na pilha
	stack_push(ast_index, current_vector_stack);
}

attribution_vector_loop: %empty {	$$ = NULL; }

attribution_command: TK_IDENTIFICADOR '=' expression
{
	//garante que identificador ja foi declarado
	st_value_t* st_identificador = ensure_variable_declared($1);

	ast_node_value_t* ast_expression = $3->value;

	//st_value_t* entry_expression = ast_expression->symbols_table_entry;
	//st_identificador->count_char = entry_expression->count_char;
	//printf("count char: %d\n", st_identificador->count_char);

	//checar se tipos são compativeis
	verify_matching_user_types(st_identificador, ast_expression);
	mark_coercion(st_identificador->semantic_type, ast_expression);

	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, st_identificador->semantic_type, st_identificador->semantic_user_type, st_identificador));
	$$ = tree_make_binary_node(new_ast_node_value(AST_ATRIBUICAO, SMTC_VOID, NULL, NULL), node_identificador, $3);

	free($1);

	ast_node_value_t* ast_head_value = $$->value;
	ast_head_value->symbols_table_entry = st_identificador;
	generate_code_attribution_var(ast_head_value, ast_expression);
}
attribution_command: TK_IDENTIFICADOR attribution_vector '=' expression
{
	//garante que identificador ja foi declarado
	st_value_t* st_identificador = ensure_vector_declared($1);

	ast_node_value_t* ast_vector = $2->value;
	ensure_vector_dimension(ast_vector->vector_dimension, st_identificador->vector_dimension, st_identificador->value.s);

	ast_node_value_t* ast_expression = $4->value;

	//st_value_t* entry_expression = ast_expression->symbols_table_entry;
	//st_identificador->count_char = entry_expression->count_char;
	//printf("count char: %d\n", st_identificador->count_char);

	//checar se tipos são compativeis
	verify_matching_user_types(st_identificador, ast_expression);
	mark_coercion(st_identificador->semantic_type, ast_expression);

	char* user_type_1 = (st_identificador->semantic_user_type != NULL) ? strdup(st_identificador->semantic_user_type) : NULL;
	char* user_type_2 = (st_identificador->semantic_user_type != NULL) ? strdup(st_identificador->semantic_user_type) : NULL;

	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, st_identificador->semantic_type, user_type_1, st_identificador));
	comp_tree_t* node_vetor_indexado = tree_make_binary_node(new_ast_node_value(AST_VETOR_INDEXADO, st_identificador->semantic_type,
			user_type_2, NULL), node_identificador, $2);

	$$ = tree_make_binary_node(new_ast_node_value(AST_ATRIBUICAO, SMTC_VOID, NULL, NULL), node_vetor_indexado, $4);

	free($1);

	generate_code_atrib_vector($$->value, current_vector_stack, st_identificador, $4->value);

	//reseta a pilha
	stack_item_t* item;
	do {
		stack_pop(&item, &current_vector_stack);
		free(item);
	} while (item);
	free_stack(current_vector_stack);
	current_vector_stack = new_stack();
}
attribution_command: TK_IDENTIFICADOR '$' TK_IDENTIFICADOR '=' expression
{
	st_value_t* st_identificador = ensure_variable_declared($1);

	st_value_t* st_campo = ensure_field_declared($3, st_identificador->semantic_user_type);

	ast_node_value_t* ast_expression = $5->value;

	//st_value_t* entry_expression = ast_expression->symbols_table_entry;
	//st_identificador->count_char = entry_expression->count_char;
	//printf("count char: %d\n", st_identificador->count_char);

	//checar se tipos são compativeis
	mark_coercion(st_campo->semantic_type, ast_expression);

	char* id_user_type = (st_identificador->semantic_user_type != NULL) ? strdup(st_identificador->semantic_user_type) : NULL;
	char* campo_user_type = (st_campo->semantic_user_type != NULL) ? strdup(st_identificador->semantic_user_type) : NULL;


	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, st_identificador->semantic_type, id_user_type, st_identificador));
	comp_tree_t* node_campo = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, st_campo->semantic_type, campo_user_type, st_campo));
	$$ = tree_make_ternary_node(new_ast_node_value(AST_ATRIBUICAO, SMTC_VOID, NULL, NULL), node_identificador, $5, node_campo);

	free($1);
	free($3);
}

input_command: TK_PR_INPUT expression
{
	ensure_inputable($2->value);
	$$ = tree_make_unary_node(new_ast_node_value(AST_INPUT, SMTC_VOID, NULL, NULL), $2);
}

output_command: TK_PR_OUTPUT expression
{
	ensure_outputable($2->value);
	$$ = tree_make_unary_node(new_ast_node_value(AST_OUTPUT, SMTC_VOID, NULL, NULL), $2);
}

function_call: TK_IDENTIFICADOR '(' expression_sequence ')'
{
	st_value_t* st_identificador = ensure_function_declared($1);
	ensure_number_of_parameters($1, $3);
	ensure_parameters_type($1, $3);

	char* function_user_type_1 = (st_identificador->semantic_user_type != NULL) ? strdup(st_identificador->semantic_user_type) : NULL;
	char* function_user_type_2 = (st_identificador->semantic_user_type != NULL) ? strdup(st_identificador->semantic_user_type) : NULL;

	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, st_identificador->semantic_type, function_user_type_1, st_identificador));
	$$ = tree_make_binary_node(new_ast_node_value(AST_CHAMADA_DE_FUNCAO, st_identificador->semantic_type, function_user_type_2, NULL), node_identificador, $3);

	free($1);
}
function_call: TK_IDENTIFICADOR '(' ')'
{
	st_value_t* st_identificador = ensure_function_declared($1);
	ensure_function_has_no_parameters($1);


	char* function_user_type_1 = (st_identificador->semantic_user_type != NULL) ? strdup(st_identificador->semantic_user_type) : NULL;
	char* function_user_type_2 = (st_identificador->semantic_user_type != NULL) ? strdup(st_identificador->semantic_user_type) : NULL;

	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, st_identificador->semantic_type, function_user_type_1, st_identificador));
	$$ = tree_make_unary_node(new_ast_node_value(AST_CHAMADA_DE_FUNCAO, st_identificador->semantic_type, function_user_type_2, NULL), node_identificador);

	free($1);
}

shift_command: TK_IDENTIFICADOR TK_OC_SL TK_LIT_INT
{
	st_value_t* st_identificador = ensure_variable_declared($1);

	verify_shiftable(st_identificador);

	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, SMTC_INT, NULL, st_identificador));

	st_value_t* st_lit_int = $3;
	int num_shifts = st_lit_int->value.i;
	comp_tree_t* node_num_shifts = tree_make_node(new_ast_node_value(AST_LITERAL, SMTC_INT, NULL, $3));

	$$ = tree_make_binary_node(new_ast_node_value(AST_SHIFT_LEFT, st_identificador->semantic_type, NULL, NULL), node_identificador, node_num_shifts);

	free($1);
}
shift_command: TK_IDENTIFICADOR TK_OC_SR TK_LIT_INT
{
	st_value_t* st_identificador = ensure_variable_declared($1);

	verify_shiftable(st_identificador);

	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, SMTC_INT, NULL, st_identificador));

	st_value_t* st_lit_int = $3;
	int num_shifts = st_lit_int->value.i;
	comp_tree_t* node_num_shifts = tree_make_node(new_ast_node_value(AST_LITERAL, SMTC_INT, NULL, $3));

	$$ = tree_make_binary_node(new_ast_node_value(AST_SHIFT_RIGHT, st_identificador->semantic_type, NULL, NULL), node_identificador, node_num_shifts);

	free($1);
}

flux_command: condition_command
flux_command: iteration_command
flux_command: selection_command

condition_command: TK_PR_IF '(' expression ')' TK_PR_THEN block
{
	$$ = tree_make_node(new_ast_node_value(AST_IF_ELSE, SMTC_VOID, NULL, NULL));

	//pendura expression
	if ($3) tree_insert_node($$, $3);

	//pendura body do then
	if ($6)
		tree_insert_node($$, $6);
	else
		tree_insert_node($$, tree_make_node(new_ast_node_value(AST_BLOCO, SMTC_VOID, NULL, NULL)));

	mark_coercion(SMTC_BOOL, $3->value);

	generate_code_if($$->value, $3->value, $6->value);
}
condition_command: TK_PR_IF '(' expression ')' TK_PR_THEN block TK_PR_ELSE block
{
	$$ = tree_make_node(new_ast_node_value(AST_IF_ELSE, SMTC_VOID, NULL, NULL));

	//pendura expression
	if ($3) tree_insert_node($$, $3);

	//pendura body do then
	if ($6)
		tree_insert_node($$, $6);
	else
		tree_insert_node($$, tree_make_node(new_ast_node_value(AST_BLOCO, SMTC_VOID, NULL, NULL)));

	//pendura body do else
	if ($8)
		tree_insert_node($$, $8);
	else
		tree_insert_node($$, tree_make_node(new_ast_node_value(AST_BLOCO, SMTC_VOID, NULL, NULL)));

	mark_coercion(SMTC_BOOL, $3->value);

	generate_code_if_else($$->value, $3->value, $6->value, $8->value);
}

start_foreach: TK_PR_FOREACH '('
{
	//empilhar bloco
	comp_dict_t *func_symbols_table = dict_new();
	stack_push(func_symbols_table, get_scope_stack());
}
iteration_command: start_foreach TK_IDENTIFICADOR ':' foreach_expression_sequence ')' body
{
	st_value_t* st_identificador = ensure_variable_declared_foreach($2);
	$$ = tree_make_node(new_ast_node_value(AST_FOREACH, SMTC_VOID, NULL, NULL));
	char* user_type_1 = (st_identificador->semantic_user_type != NULL) ? strdup(st_identificador->semantic_user_type) : NULL;

	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, st_identificador->semantic_type, user_type_1, st_identificador));
	tree_insert_node($$, node_identificador);
	tree_insert_node($$, $4);
	tree_insert_node($$, $6);

	//associa tabela de simbolos ao nodo AST
	((ast_node_value_t*)$$->value)->symbols_table = getCurrentST();
	#ifdef DEBUG
		print_st(((ast_node_value_t*)$$->value)->symbols_table);
	#endif

	//desempilha bloco e libera sua tabela de simbolos, ja que nao vai ser pendurada
	//em ast nenhuma (ast do foreach nao foi implementada)
	pop_and_free_scope();
	free($2);

	//gera codigo
	generate_code_foreach($$->value, st_identificador, $4->value, $6->value);
}

start_for: TK_PR_FOR '('
{
	//empilhar bloco
	comp_dict_t *func_symbols_table = dict_new();
	stack_push(func_symbols_table, get_scope_stack());
}
iteration_command: start_for for_command_sequence ':' expression ':' for_command_sequence ')' body
{
	$$ = tree_make_node(new_ast_node_value(AST_FOR, SMTC_VOID, NULL, NULL));
	tree_insert_node($$, $2);
	tree_insert_node($$, $4);
	tree_insert_node($$, $6);
	tree_insert_node($$, $8);

	//associa tabela de simbolos ao nodo AST
	((ast_node_value_t*)$$->value)->symbols_table = getCurrentST();
	#ifdef DEBUG
		print_st(((ast_node_value_t*)$$->value)->symbols_table);
	#endif

	mark_coercion(SMTC_BOOL, $4->value);

	//desempilha bloco e libera sua tabela de simbolos, ja que nao vai ser pendurada
	//em ast nenhuma (ast do for nao foi implementada)
	pop_and_free_scope();

	generate_code_for($$->value, $2->value, $4->value, $6->value, $8->value);
}
iteration_command: TK_PR_WHILE '(' expression ')' TK_PR_DO block
{
	$$ = tree_make_node(new_ast_node_value(AST_WHILE_DO, SMTC_VOID, NULL, NULL));

	//pendura expression
	if ($3) tree_insert_node($$, $3);

	//pendura body
	if ($6)
		tree_insert_node($$, $6);
	else
		tree_insert_node($$, tree_make_node(new_ast_node_value(AST_BLOCO, SMTC_VOID, NULL, NULL)));

	generate_code_while($$->value, $3->value, $6->value);
}
iteration_command: TK_PR_DO block TK_PR_WHILE '(' expression ')'
{
	$$ = tree_make_node(new_ast_node_value(AST_DO_WHILE, SMTC_VOID, NULL, NULL));

	//pendura body
	if ($2)
		tree_insert_node($$, $2);
	else
		tree_insert_node($$, tree_make_node(new_ast_node_value(AST_BLOCO, SMTC_VOID, NULL, NULL)));

	//pendura expression
	if ($5) tree_insert_node($$, $5);

	generate_code_do_while($$->value, $5->value, $2->value);
}

start_switch: TK_PR_SWITCH '('
{
	//empilhar bloco
	comp_dict_t *func_symbols_table = dict_new();
	stack_push(func_symbols_table, get_scope_stack());
}
selection_command: start_switch expression ')' body
{
	$$ = $4;

	//associa tabela de simbolos ao nodo AST
	((ast_node_value_t*)$$->value)->symbols_table = getCurrentST();
	#ifdef DEBUG
		print_st(((ast_node_value_t*)$$->value)->symbols_table);
	#endif

	destroyAST($2);

	//desempilha bloco e libera sua tabela de simbolos, ja que nao vai ser pendurada
	//em ast nenhuma (ast do switch nao foi implementada)
	pop_and_free_scope();
}

for_command_sequence: simple_command { $$ = $1; }
for_command_sequence: simple_command ',' for_command_sequence {
	$$ = $1;
	tree_insert_node($$,$3);
	//concatenar codigo
	ast_node_value_t* head = $$->value;
	ast_node_value_t* cmd_list = $3->value;
	stack_push_all_tacs(head->tac_stack, cmd_list->tac_stack);
}

foreach_expression_sequence: expression {
	$$ = $1;
}
foreach_expression_sequence: expression ',' foreach_expression_sequence {
	$$ = $1;
	tree_insert_node($$,$3);
	//concatenar codigo
	ast_node_value_t* head = $$->value;
	ast_node_value_t* cmd_list = $3->value;
	stack_push_all_tacs(head->tac_stack, cmd_list->tac_stack);
}

action_command: TK_PR_RETURN expression
{
	ast_node_value_t* ast_node_value_expression = $2->value;
	if(ast_node_value_expression->semantic_type != SMTC_USER_TYPE_VAR) ensure_return_type_is_correct(ast_node_value_expression);
	else ensure_return_type_user_is_correct(ast_node_value_expression);
	$$ = tree_make_unary_node(new_ast_node_value(AST_RETURN, ast_node_value_expression->semantic_type, ast_node_value_expression->semantic_user_type, NULL), $2);
}
action_command: TK_PR_CONTINUE { $$ = NULL; }
action_command: TK_PR_BREAK { $$ = NULL; }


// definicoes de tipos

start_type_decl: TK_PR_CLASS TK_IDENTIFICADOR
{
	char* id_name = $2;
	ensure_type_not_declared(id_name);

	//insere identificador declarado na tabela de simbolos global
	st_value_t* st_identificador = putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);

	st_identificador->semantic_user_type = strdup(id_name);
	st_identificador->semantic_type = SMTC_USER_TYPE_NAME;

	set_current_type_decl(id_name);

	free(id_name);
}

def_type: start_type_decl '[' type_fields ']' ';'
{
	st_value_t* st_identificador = search_id_in_global_st(get_current_type_decl());
	st_identificador->size = $3;
}
type_fields: type_field { $$ = $1; }
type_fields: type_field ':' type_fields { $$ = $1 + $3; }
type_field: encapsulation primitive_type TK_IDENTIFICADOR
{
	char* id_name = $3;
	ensure_identifier_not_declared(id_name);

	//insere identificador declarado na tabela de simbolos global
	st_value_t* st_identificador = putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive_field($2, st_identificador);

	$$ = get_type_size($2);

	free(id_name);
}
type_field: encapsulation primitive_type TK_IDENTIFICADOR vector_declaration
{
	char* id_name = $3;
	ensure_identifier_not_declared(id_name);

	//insere identificador declarado na tabela de simbolos global
	st_value_t* st_identificador = putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);

	int size = $4->size;
	int vector_dimension = $4->vector_dimension;

	set_st_semantic_type_and_size_vector_field($2, size, vector_dimension, st_identificador);

	free(id_name);
}

encapsulation: TK_PR_PROTECTED
encapsulation: TK_PR_PRIVATE
encapsulation: TK_PR_PUBLIC

primitive_type: TK_PR_INT { $$ = SMTC_INT; }
primitive_type: TK_PR_FLOAT { $$ = SMTC_FLOAT; }
primitive_type: TK_PR_BOOL { $$ = SMTC_BOOL; }
primitive_type: TK_PR_CHAR { $$ = SMTC_CHAR; }
primitive_type: TK_PR_STRING { $$ = SMTC_STRING; }


//expressions e expressions sequences

expression: sub_expression_chain { $$ = $1; }

sub_expression_chain: sub_expression_1 { $$ = $1; }
sub_expression_chain: sub_expression_1 logic_operator sub_expression_1
{
	ast_node_value_t* ast_node_value_sub_expression = $1->value;
	ast_node_value_t* ast_node_value_sub_expression_chain = $3->value;

	//operador sobe
	$$ = $2;
	ast_node_value_t* ast_node_value_head = $$->value;

	//pendura operandos
	tree_insert_node($$, $1);
	tree_insert_node($$, $3);

	//infere tipo semantico baseado nos operandos
	ast_node_value_head->semantic_type = infere_type(ast_node_value_sub_expression->semantic_type, ast_node_value_sub_expression_chain->semantic_type);
	mark_coercion_where_needed(ast_node_value_sub_expression, ast_node_value_sub_expression_chain);

	((ast_node_value_t*) $$->value)->outputable = is_arit_expression(ast_node_value_head);

	generate_code_expression($$->value, $1->value, $2->value, $3->value);
}

sub_expression_1: sub_expression operator sub_expression_1
{
	ast_node_value_t* ast_node_value_sub_expression = $1->value;
	ast_node_value_t* ast_node_value_sub_expression_chain = $3->value;

	//operador sobe
	$$ = $2;
	ast_node_value_t* ast_node_value_head = $$->value;

	//pendura operandos
	tree_insert_node($$, $1);
	tree_insert_node($$, $3);

	//infere tipo semantico baseado nos operandos
	ast_node_value_head->semantic_type = infere_type(ast_node_value_sub_expression->semantic_type, ast_node_value_sub_expression_chain->semantic_type);
	mark_coercion_where_needed(ast_node_value_sub_expression, ast_node_value_sub_expression_chain);

	((ast_node_value_t*) $$->value)->outputable = is_arit_expression(ast_node_value_head);

	generate_code_expression($$->value, $1->value, $2->value, $3->value);
}

sub_expression_1: sub_expression { $$ = $1; }

sub_expression: unary_operator sub_expression
{
	ast_node_value_t* value_sub_expression = $2->value;
	ast_node_value_t* value_head = $$->value;

	if ($1) {
		$$ = $1;
		tree_insert_node($$, $2);
	} else {
		$$ = $2;
	}
	//infere tipo semantico baseado no operando
	value_head->semantic_type = value_sub_expression->semantic_type;
	generate_code_unary_op($$->value, $1->value, $2->value);
}
sub_expression: '(' expression ')' { $$ = $2; }
sub_expression: literal {	$$ = $1; }
sub_expression: TK_IDENTIFICADOR
{
	st_value_t* st_identificador = ensure_variable_declared($1);

	$$ = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, st_identificador->semantic_type, st_identificador->semantic_user_type, st_identificador));

	((ast_node_value_t*) $$->value)->outputable = is_arit_expression($$->value);
	((ast_node_value_t*) $$->value)->inputable = true;

	free($1);

	generate_code_load_var($$->value);
}
sub_expression: TK_IDENTIFICADOR attribution_vector
{

	st_value_t* st_identificador = ensure_vector_declared($1);

	ast_node_value_t* ast_vector = $2->value;
	ensure_vector_dimension(ast_vector->vector_dimension, st_identificador->vector_dimension, st_identificador->value.s);

	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, st_identificador->semantic_type, st_identificador->semantic_user_type, st_identificador));
	$$ = tree_make_binary_node(new_ast_node_value(AST_VETOR_INDEXADO, st_identificador->semantic_type, st_identificador->semantic_user_type, NULL), node_identificador, $2);

	((ast_node_value_t*) $$->value)->outputable = is_arit_expression($$->value);

	free($1);
}
sub_expression: function_call
{
	$$ = $1;
	((ast_node_value_t*) $$->value)->outputable = is_arit_expression($$->value);
}


literal: TK_LIT_INT {
	$$ = tree_make_node(new_ast_node_value(AST_LITERAL, SMTC_INT, NULL, $1));
	generate_code_load_literal_int($$->value);
}
literal: TK_LIT_FLOAT { $$ = tree_make_node(new_ast_node_value(AST_LITERAL, SMTC_FLOAT, NULL, $1)); }
literal: TK_LIT_CHAR { $$ = tree_make_node(new_ast_node_value(AST_LITERAL, SMTC_CHAR, NULL, $1)); }
literal: TK_LIT_TRUE {
	$$ = tree_make_node(new_ast_node_value(AST_LITERAL, SMTC_BOOL, NULL, $1));
	generate_code_load_literal_bool($$->value);
}
literal: TK_LIT_FALSE {
	$$ = tree_make_node(new_ast_node_value(AST_LITERAL, SMTC_BOOL, NULL, $1));
	generate_code_load_literal_bool($$->value);
}
literal: TK_LIT_STRING
{
	$$ = tree_make_node(new_ast_node_value(AST_LITERAL, SMTC_STRING, NULL, $1));
	((ast_node_value_t*) $$->value)->outputable = true;
	((st_value_t*) ((ast_node_value_t*) $$->value)->symbols_table_entry)->count_char = strlen(((st_value_t*) $1)->value.s);
}

operator: TK_OC_LE { $$ = tree_make_node(new_ast_node_value(AST_LOGICO_COMP_LE, SMTC_VOID, NULL, NULL)); }
operator: TK_OC_GE { $$ = tree_make_node(new_ast_node_value(AST_LOGICO_COMP_GE, SMTC_VOID, NULL, NULL)); }
operator: TK_OC_EQ { $$ = tree_make_node(new_ast_node_value(AST_LOGICO_COMP_IGUAL, SMTC_VOID, NULL, NULL)); }
operator: TK_OC_NE { $$ = tree_make_node(new_ast_node_value(AST_LOGICO_COMP_DIF, SMTC_VOID, NULL, NULL)); }
logic_operator: TK_OC_AND{ $$ = tree_make_node(new_ast_node_value(AST_LOGICO_E, SMTC_VOID, NULL, NULL)); }
logic_operator: TK_OC_OR { $$ = tree_make_node(new_ast_node_value(AST_LOGICO_OU, SMTC_VOID, NULL, NULL)); }
operator: '+' { $$ = tree_make_node(new_ast_node_value(AST_ARIM_SOMA, SMTC_VOID, NULL, NULL)); }
operator: '<' { $$ = tree_make_node(new_ast_node_value(AST_LOGICO_COMP_L, SMTC_VOID, NULL, NULL)); }
operator: '>' { $$ = tree_make_node(new_ast_node_value(AST_LOGICO_COMP_G, SMTC_VOID, NULL, NULL)); }
operator: '-' { $$ = tree_make_node(new_ast_node_value(AST_ARIM_SUBTRACAO, SMTC_VOID, NULL, NULL)); }
operator: '/' { $$ = tree_make_node(new_ast_node_value(AST_ARIM_DIVISAO, SMTC_VOID, NULL, NULL)); }
operator: '*' { $$ = tree_make_node(new_ast_node_value(AST_ARIM_MULTIPLICACAO, SMTC_VOID, NULL, NULL)); }

unary_operator: '-' { $$ = tree_make_node(new_ast_node_value(AST_ARIM_INVERSAO, SMTC_VOID, NULL, NULL)); }
unary_operator: '!' { $$ = tree_make_node(new_ast_node_value(AST_LOGICO_COMP_NEGACAO, SMTC_VOID, NULL, NULL)); }
unary_operator: '+' { $$ = NULL; }


expression_sequence: expression { $$ = $1; }
expression_sequence: expression ',' expression_sequence
{
	//sobe expressao
	$$ = $1;
	//pendura proxima
	tree_insert_node($$, $3);
}

%%
