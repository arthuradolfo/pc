/*
  Arthur Adolfo 						- 	00262515
  Gabriel de Souza Seibel 	- 	00262513
*/
%code requires{
#include "parser.h" //arquivo automaticamente gerado pelo bison
#include "main.h"
#include "cc_misc.h" //arquivo com funcoes de auto incremento
}

%union
{
	comp_tree_t *tree;
	int semantic_type;
	int size;
	void *valor_lexico;   /* Pointer to run-time expression operator */
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
%type<tree> prime_programa
%type<tree> programa
%type<tree> def_function
%type<tree> body
%type<tree> command_sequence
%type<tree> command_in_block
%type<tree> simple_command
%type<tree> action_command
%type<tree> attribution_command
%type<tree> flux_command
%type<tree> iteration_command
%type<tree> condition_command
%type<tree> selection_command
%type<tree> shift_command
%type<tree> io_command
%type<tree> input_command
%type<tree> output_command
%type<tree> def_local_var
%type<tree> function_call
%type<tree> expression
%type<tree> sub_expression
%type<tree> sub_expression_chain
%type<tree> expression_sequence
%type<tree> unary_operator
%type<tree> operator
%type<tree> literal
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
	if ($1)
		tree_insert_node($$, $1);

	gv_declare(AST_PROGRAMA, $$, NULL);
	putToGraphviz($$);
}

programa: %empty { $$ = NULL; }
programa: def_type programa { if ($2) $$ = $2; else $$ = NULL; }
programa: def_global_var programa { if ($2) $$ = $2; else $$ = NULL; }
programa: def_function programa
{
	if ($2) {
		tree_insert_node($1,$2);
	}
	$$ = $1;
}


//declaracao de globais

def_global_var: primitive_type TK_IDENTIFICADOR ';'
{
	char* id_name = $2;

	//verifica declaracao anterior do identificador
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador = putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive($1, st_identificador);
}
def_global_var: primitive_type TK_IDENTIFICADOR '[' TK_LIT_INT ']' ';'
{
	char* id_name = $2;

	//verifica declaracao anterior do identificador
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador =	putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);
	st_value_t* st_entry_lit_int = $4;
	int size = st_entry_lit_int->value.i;
	set_st_semantic_type_and_size_vector($1, size, st_identificador);
}
def_global_var: TK_PR_STATIC primitive_type TK_IDENTIFICADOR ';'
{
	char* id_name = $3;

	//verifica declaracao anterior do identificador
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador =	putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive($2, st_identificador);
}
def_global_var: TK_PR_STATIC primitive_type TK_IDENTIFICADOR '[' TK_LIT_INT ']' ';'
{
	char* id_name = $3;

	//verifica declaracao anterior do identificador
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador =	putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);

	st_value_t* st_entry_lit_int = $5;
	int size = st_entry_lit_int->value.i;
	set_st_semantic_type_and_size_vector($2, size, st_identificador);
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
}
def_global_var: TK_IDENTIFICADOR TK_IDENTIFICADOR '[' TK_LIT_INT ']' ';'
{
	//verifica se tipo existe
	ensure_type_declared($1);

	//verifica declaracao anterior do identificador
	char* id_name = $2;
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador =	putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);
	st_value_t* st_entry_lit_int = $4;
	int size = st_entry_lit_int->value.i;
	set_st_semantic_type_and_size_vector_user_type($1, st_identificador, size);
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
}
def_global_var: TK_PR_STATIC TK_IDENTIFICADOR TK_IDENTIFICADOR '[' TK_LIT_INT ']' ';'
{
	//verifica se tipo ($2) existe
	ensure_type_declared($2);

	//verifica declaracao anterior do identificador
	char* id_name = $3;
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador =	putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);
	st_value_t* st_entry_lit_int = $5;
	int size = st_entry_lit_int->value.i;
	set_st_semantic_type_and_size_vector_user_type($2, st_identificador, size);
}


// funcoes

push_func_stack: %empty
{
	comp_dict_t *func_symbols_table = dict_new();
	stack_push(func_symbols_table, get_stack());
	printf("Empilha funcao\n");
	stack_print();
}

def_function: primitive_type TK_IDENTIFICADOR '(' parameters ')' push_func_stack body
{
	//verifica declaracao anterior do identificador
	char* id_name = $2;
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador =	putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);

	$$ = tree_make_node(new_ast_node_value(AST_FUNCAO, SMTC_VOID, NULL, st_identificador));
	if ($7)
		tree_insert_node($$,$7);
	set_st_semantic_type_and_size_primitive_function($1, st_identificador);
	st_stack_item_t *item;
	st_stack_t *aux_stack = get_stack();
	stack_pop(&item, &aux_stack);
	free(item);
	printf("Desempilha funcao\n");
	stack_print();
}
def_function: TK_PR_STATIC primitive_type TK_IDENTIFICADOR '(' parameters ')' body
{
	//verifica declaracao anterior do identificador
	char* id_name = $3;
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador =	putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);

	$$ = tree_make_node(new_ast_node_value(AST_FUNCAO, SMTC_VOID, NULL, st_identificador));
	if ($7)
		tree_insert_node($$,$7);

	set_st_semantic_type_and_size_primitive_function($2, st_identificador);
}

def_function: TK_IDENTIFICADOR TK_IDENTIFICADOR '(' parameters ')' body
{
	//verifica se tipo ($1) existe
	ensure_type_declared($1);

	//verifica declaracao anterior do identificador
	char* id_name = $2;
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador =	putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);

	$$ = tree_make_node(new_ast_node_value(AST_FUNCAO, SMTC_VOID, NULL, st_identificador));
	if ($6)
		tree_insert_node($$,$6);

	set_st_semantic_type_and_size_user_type_function($1, st_identificador);
}
def_function: TK_PR_STATIC TK_IDENTIFICADOR TK_IDENTIFICADOR '(' parameters ')' body
{
	//verifica se tipo ($2) existe
	ensure_type_declared($2);

	//verifica declaracao anterior do identificador
	char* id_name = $3;
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador =	putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);

	$$ = tree_make_node(new_ast_node_value(AST_FUNCAO, SMTC_VOID, NULL, st_identificador));
	if ($7)
		tree_insert_node($$,$7);

	set_st_semantic_type_and_size_user_type_function($2, st_identificador);
}

body: '{' command_sequence '}' { $$ = $2; }

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
	
}
parameter: TK_PR_CONST primitive_type TK_IDENTIFICADOR
{
	//verifica declaracao anterior do identificador
	char* id_name = $3;
	ensure_identifier_not_declared(id_name);

	//insere identificador na tabela de simbolos global
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive($2, st_identificador);
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
}

command_sequence: %empty { $$ = NULL; }
command_sequence: command_in_block ';' command_sequence
{
	if ($1) {
		$$ = $1;
		if ($3) tree_insert_node($$,$3);
	} else {
		$$ = $3;
	}
}
command_sequence: case_command ':' command_sequence { $$ = $3; }
case_command: TK_PR_CASE TK_LIT_INT

command_in_block: simple_command { $$ = $1; }
command_in_block: io_command { $$ = $1; }
command_in_block: action_command { $$ = $1; }

push_block_stack: '{'
{
	comp_dict_t *func_symbols_table = dict_new();
	stack_push(func_symbols_table, get_stack());
	printf("Empilha bloco\n");
	stack_print();
}

simple_command: attribution_command { $$ = $1; }
simple_command: function_call { $$ = $1; }
simple_command: shift_command { $$ = $1; }
simple_command: def_local_var { $$ = $1; }
simple_command: flux_command { $$ = $1; }
simple_command: push_block_stack command_sequence '}'
{
	$$ = tree_make_node(new_ast_node_value(AST_BLOCO, SMTC_VOID, NULL, NULL));
	if ($2) tree_insert_node($$,$2);
	st_stack_item_t *item;
	st_stack_t *aux_stack = get_stack();
	stack_pop(&item, &aux_stack);
	free(item);
	printf("Desempilha bloco\n");
	stack_print();
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

	$$ = NULL;
}
def_local_var: primitive_type TK_IDENTIFICADOR
{
	char* id_name = $2;
	ensure_identifier_not_declared(id_name);

	//insere identificador declarado na tabela de simbolos atual (topo da pilha)
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive($1, st_identificador);

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

	//checar se tipos são compativeis
	mark_coercion(st_identificador->semantic_type, ast_expression);

	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, $1, NULL, st_identificador));
	$$ = tree_make_binary_node(new_ast_node_value(AST_ATRIBUICAO, SMTC_VOID, NULL, NULL), node_identificador, $4);
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

	$$ = NULL;
}
def_local_var: TK_PR_STATIC primitive_type TK_IDENTIFICADOR
{
	char* id_name = $3;
	ensure_identifier_not_declared(id_name);

	//insere identificador declarado na tabela de simbolos atual (topo da pilha)
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive($2, st_identificador);

	$$ = NULL;
}
def_local_var: TK_PR_STATIC primitive_type TK_IDENTIFICADOR TK_OC_LE expression
{
	char* id_name = $3;
	ensure_identifier_not_declared(id_name);

	//insere identificador declarado na tabela de simbolos atual (topo da pilha)
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive($2, st_identificador);

	ast_node_value_t* ast_expression = $5->value;

	//checar se tipos são compativeis
	mark_coercion(st_identificador->semantic_type, ast_expression);

	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, $2, NULL, st_identificador));
	$$ = tree_make_binary_node(new_ast_node_value(AST_ATRIBUICAO, SMTC_VOID, NULL, NULL), node_identificador, $5);
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

	$$ = NULL;
}
def_local_var: TK_PR_CONST primitive_type TK_IDENTIFICADOR
{
	char* id_name = $3;
	ensure_identifier_not_declared(id_name);

	//insere identificador declarado na tabela de simbolos atual (topo da pilha)
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive($2, st_identificador);

	$$ = NULL;
}
def_local_var: TK_PR_CONST primitive_type TK_IDENTIFICADOR TK_OC_LE expression
{
	char* id_name = $3;
	ensure_identifier_not_declared(id_name);

	//insere identificador declarado na tabela de simbolos atual (topo da pilha)
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive($2, st_identificador);

	ast_node_value_t* ast_expression = $5->value;

	//checar se tipos são compativeis
	mark_coercion(st_identificador->semantic_type, ast_expression);

	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, $2, NULL, st_identificador));
	$$ = tree_make_binary_node(new_ast_node_value(AST_ATRIBUICAO, SMTC_VOID, NULL, NULL), node_identificador, $5);
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

	$$ = NULL;
}
def_local_var: TK_PR_STATIC TK_PR_CONST primitive_type TK_IDENTIFICADOR
{
	char* id_name = $4;
	ensure_identifier_not_declared(id_name);

	//insere identificador declarado na tabela de simbolos atual (topo da pilha)
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive($3, st_identificador);

	$$ = NULL;
}
def_local_var: TK_PR_STATIC TK_PR_CONST primitive_type TK_IDENTIFICADOR TK_OC_LE expression
{
	char* id_name = $4;
	ensure_identifier_not_declared(id_name);

	//insere identificador declarado na tabela de simbolos atual (topo da pilha)
	st_value_t* st_identificador = putToCurrentST(id_name, comp_get_line_number(), POA_IDENT);
	set_st_semantic_type_and_size_primitive($3, st_identificador);

	ast_node_value_t* ast_expression = $6->value;

	//checar se tipos são compativeis
	mark_coercion(st_identificador->semantic_type, ast_expression);

	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, $3, NULL, st_identificador));
	$$ = tree_make_binary_node(new_ast_node_value(AST_ATRIBUICAO, SMTC_VOID, NULL, NULL), node_identificador, $6);
}

attribution_command: TK_IDENTIFICADOR '=' expression
{
	//garante que identificador ja foi declarado
	st_value_t* st_identificador = ensure_variable_declared($1);

	ast_node_value_t* ast_expression = $3->value;

	//checar se tipos são compativeis
	mark_coercion(st_identificador->semantic_type, ast_expression);

	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, st_identificador->semantic_type, st_identificador->semantic_user_type, st_identificador));
	$$ = tree_make_binary_node(new_ast_node_value(AST_ATRIBUICAO, SMTC_VOID, NULL, NULL), node_identificador, $3);
}
attribution_command: TK_IDENTIFICADOR '[' expression ']' '=' expression
{
	//garante que identificador ja foi declarado
	st_value_t* st_identificador = ensure_vector_declared($1);

	//verifica se indice é int
	ast_node_value_t* ast_index = $3->value;
	mark_coercion(SMTC_INT, ast_index);

	ast_node_value_t* ast_expression = $6->value;

	//checar se tipos são compativeis
	mark_coercion(st_identificador->semantic_type, ast_expression);

	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, st_identificador->semantic_type, st_identificador->semantic_user_type, st_identificador));
	comp_tree_t* node_vetor_indexado = tree_make_binary_node(new_ast_node_value(AST_VETOR_INDEXADO, st_identificador->semantic_type,
	 	st_identificador->semantic_user_type, NULL), node_identificador, $3);
	$$ = tree_make_binary_node(new_ast_node_value(AST_ATRIBUICAO, SMTC_VOID, NULL, NULL), node_vetor_indexado, $6);
}
attribution_command: TK_IDENTIFICADOR '$' TK_IDENTIFICADOR '=' expression
{
	st_value_t* st_identificador = ensure_variable_declared($1);

	st_value_t* st_campo = ensure_field_declared($3, st_identificador->semantic_user_type);

	ast_node_value_t* ast_expression = $5->value;

	//checar se tipos são compativeis
	mark_coercion(st_campo->semantic_type, ast_expression);

	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, st_identificador->semantic_type, st_identificador->semantic_user_type, st_identificador));
	comp_tree_t* node_campo = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, st_campo->semantic_type, st_campo->semantic_user_type, st_campo));
	$$ = tree_make_ternary_node(new_ast_node_value(AST_ATRIBUICAO, SMTC_VOID, NULL, NULL), node_identificador, $5, node_campo);
}

input_command: TK_PR_INPUT expression
{
	//TODO checar semantica
	$$ = tree_make_unary_node(new_ast_node_value(AST_INPUT, SMTC_VOID, NULL, NULL), $2);
}

output_command: TK_PR_OUTPUT expression_sequence
{
	//TODO checar semantica
	$$ = tree_make_unary_node(new_ast_node_value(AST_OUTPUT, SMTC_VOID, NULL, NULL), $2);
}

function_call: TK_IDENTIFICADOR '(' expression_sequence ')'
{
	st_value_t* st_identificador = ensure_function_declared($1);

	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, st_identificador->semantic_type, st_identificador->semantic_user_type, st_identificador));
	$$ = tree_make_binary_node(new_ast_node_value(AST_CHAMADA_DE_FUNCAO, st_identificador->semantic_type, st_identificador->semantic_user_type, NULL), node_identificador, $3);
}
function_call: TK_IDENTIFICADOR '(' ')'
{
	st_value_t* st_identificador = ensure_function_declared($1);

	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, st_identificador->semantic_type, st_identificador->semantic_user_type, st_identificador));
	$$ = tree_make_unary_node(new_ast_node_value(AST_CHAMADA_DE_FUNCAO, st_identificador->semantic_type, st_identificador->semantic_user_type, NULL), node_identificador);
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
}

flux_command: condition_command
flux_command: iteration_command
flux_command: selection_command

condition_command: TK_PR_IF '(' expression ')' TK_PR_THEN body
{
	$$ = tree_make_node(new_ast_node_value(AST_IF_ELSE, SMTC_VOID, NULL, NULL));

	//pendura expression
	if ($3) tree_insert_node($$, $3);

	//pendura body do then
	if ($6)
		tree_insert_node($$, $6);
	else
		tree_insert_node($$, tree_make_node(new_ast_node_value(AST_BLOCO, SMTC_VOID, NULL, NULL)));
}
condition_command: TK_PR_IF '(' expression ')' TK_PR_THEN body TK_PR_ELSE body
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
}

iteration_command: TK_PR_FOREACH '(' TK_IDENTIFICADOR ':' foreach_expression_sequence ')' body
{ $$ = NULL; if ($7) destroyAST($7); } //TODO implementar? lidar com TK_IDENTIFICADOR
iteration_command: TK_PR_FOR '(' for_command_sequence ':' expression ':' for_command_sequence ')' body
{ $$ = NULL; destroyAST($5); if ($9) destroyAST($9); }
iteration_command: TK_PR_WHILE '(' expression ')' TK_PR_DO body
{
	$$ = tree_make_node(new_ast_node_value(AST_WHILE_DO, SMTC_VOID, NULL, NULL));

	//pendura expression
	if ($3) tree_insert_node($$, $3);

	//pendura body
	if ($6)
		tree_insert_node($$, $6);
	else
		tree_insert_node($$, tree_make_node(new_ast_node_value(AST_BLOCO, SMTC_VOID, NULL, NULL)));

}
iteration_command: TK_PR_DO body TK_PR_WHILE '(' expression ')'
{
	$$ = tree_make_node(new_ast_node_value(AST_DO_WHILE, SMTC_VOID, NULL, NULL));

	//pendura body
	if ($2)
		tree_insert_node($$, $2);
	else
		tree_insert_node($$, tree_make_node(new_ast_node_value(AST_BLOCO, SMTC_VOID, NULL, NULL)));

	//pendura expression
	if ($5) tree_insert_node($$, $5);
}

selection_command: TK_PR_SWITCH '(' expression ')' body { $$ = NULL; destroyAST($3); if ($5) destroyAST($5); }

for_command_sequence: simple_command { if ($1) destroyAST($1); }
for_command_sequence: simple_command ',' for_command_sequence { if ($1) destroyAST($1); }

foreach_expression_sequence: expression { destroyAST($1); }
foreach_expression_sequence: expression ',' foreach_expression_sequence { destroyAST($1); }

action_command: TK_PR_RETURN expression
{
	//TODO verificar se expression é compativel com o retorno da funcao (como?)
	ast_node_value_t* ast_node_value_expression = $2->value;
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


	st_identificador->semantic_user_type = id_name;
	st_identificador->semantic_type = SMTC_USER_TYPE_NAME;
	printf("semantic_user_type: %s\n",st_identificador->semantic_user_type);

	set_current_type_decl(strdup(id_name));
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
}
type_field: encapsulation primitive_type TK_IDENTIFICADOR '[' TK_LIT_INT ']'
{
	char* id_name = $3;
	ensure_identifier_not_declared(id_name);

	//insere identificador declarado na tabela de simbolos global
	st_value_t* st_identificador = putToSymbolsTable(id_name, comp_get_line_number(), POA_IDENT);

	st_value_t* st_entry_lit_int = $5;
	int size = st_entry_lit_int->value.i;
	set_st_semantic_type_and_size_vector_field($2, size, st_identificador);
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
sub_expression_chain: sub_expression { $$ = $1; }
sub_expression_chain: sub_expression operator sub_expression_chain
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
}

sub_expression: unary_operator sub_expression
{
	ast_node_value_t* ast_node_value_sub_expression = $2->value;
	ast_node_value_t* ast_node_value_head = $$->value;

	if ($1) {
		$$ = $1;
		tree_insert_node($$, $2);
	} else {
		$$ = $2;
	}
	//infere tipo semantico baseado no operando
	ast_node_value_head->semantic_type = ast_node_value_sub_expression->semantic_type;
}
sub_expression: '(' expression ')' { $$ = $2; }
sub_expression: literal {	$$ = $1; }
sub_expression: TK_IDENTIFICADOR
{
	st_value_t* st_identificador = ensure_variable_declared($1);

	$$ = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, st_identificador->semantic_type, st_identificador->semantic_user_type, st_identificador));
}
sub_expression: TK_IDENTIFICADOR '[' expression ']'
{
	//checar se indice é int
	ast_node_value_t* ast_index = $3->value;
	mark_coercion(SMTC_INT, ast_index);

	st_value_t* st_identificador = ensure_vector_declared($1);

	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, st_identificador->semantic_type, st_identificador->semantic_user_type, st_identificador));
	$$ = tree_make_binary_node(new_ast_node_value(AST_VETOR_INDEXADO, st_identificador->semantic_type, st_identificador->semantic_user_type, NULL), node_identificador, $3);
}
sub_expression: function_call { $$ = $1; }



literal: TK_LIT_INT { $$ = tree_make_node(new_ast_node_value(AST_LITERAL, SMTC_INT, NULL, $1)); }
literal: TK_LIT_FLOAT { $$ = tree_make_node(new_ast_node_value(AST_LITERAL, SMTC_FLOAT, NULL, $1)); }
literal: TK_LIT_CHAR { $$ = tree_make_node(new_ast_node_value(AST_LITERAL, SMTC_CHAR, NULL, $1)); }
literal: TK_LIT_TRUE { $$ = tree_make_node(new_ast_node_value(AST_LITERAL, SMTC_BOOL, NULL, $1)); }
literal: TK_LIT_FALSE { $$ = tree_make_node(new_ast_node_value(AST_LITERAL, SMTC_BOOL, NULL, $1)); }
literal: TK_LIT_STRING { $$ = tree_make_node(new_ast_node_value(AST_LITERAL, SMTC_STRING, NULL, $1)); }

operator: TK_OC_LE { $$ = tree_make_node(new_ast_node_value(AST_LOGICO_COMP_LE, SMTC_VOID, NULL, NULL)); }
operator: TK_OC_GE { $$ = tree_make_node(new_ast_node_value(AST_LOGICO_COMP_GE, SMTC_VOID, NULL, NULL)); }
operator: TK_OC_EQ { $$ = tree_make_node(new_ast_node_value(AST_LOGICO_COMP_IGUAL, SMTC_VOID, NULL, NULL)); }
operator: TK_OC_NE { $$ = tree_make_node(new_ast_node_value(AST_LOGICO_COMP_DIF, SMTC_VOID, NULL, NULL)); }
operator: TK_OC_AND{ $$ = tree_make_node(new_ast_node_value(AST_LOGICO_E, SMTC_VOID, NULL, NULL)); }
operator: TK_OC_OR { $$ = tree_make_node(new_ast_node_value(AST_LOGICO_OU, SMTC_VOID, NULL, NULL)); }
operator: '+' { $$ = tree_make_node(new_ast_node_value(AST_ARIM_SOMA, SMTC_VOID, NULL, NULL)); }
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
