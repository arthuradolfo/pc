/*
  Arthur Adolfo 			- 	00262515
  Gabriel de Souza Seibel 	- 	00262513
*/
%code requires{
#include "parser.h" //arquivo automaticamente gerado pelo bison
#include "main.h"
#include "cc_misc.h" //arquivo com funcoes de auto incremento
#include "cc_ast_node.h"
}

%union
{
	comp_tree_t *tree;
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
%type<tree> def_local_var

%%
/* Regras (e ações) da gramática */

// programa

prime_programa: programa
{
	$$ = tree_new();
	set_ast_root($$);
	if ($1)
		tree_insert_node($$, $1);
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

def_global_var: any_type TK_IDENTIFICADOR ';'
def_global_var: any_type TK_IDENTIFICADOR '[' expression ']' ';'
def_global_var: TK_PR_STATIC any_type TK_IDENTIFICADOR ';'
def_global_var: TK_PR_STATIC any_type TK_IDENTIFICADOR '[' expression ']' ';'

any_type: TK_IDENTIFICADOR
any_type: primitive_type


// funcoes

def_function: any_type TK_IDENTIFICADOR '(' parameters ')' body
{
	$$ = tree_make_node(new_ast_node_value(AST_FUNCAO, NULL));
	if ($6)
		tree_insert_node($$,$6);
}
def_function: TK_PR_STATIC any_type TK_IDENTIFICADOR '(' parameters ')' body
{
	$$ = tree_make_node(new_ast_node_value(AST_FUNCAO, NULL));
	if ($7)
		tree_insert_node($$,$7);
}
body: '{' command_sequence '}' {	$$ = $2; }

parameters: %empty
parameters: parameter
parameters: parameter parameter_chain

parameter_chain: ',' parameter
parameter_chain: ',' parameter parameter_chain

parameter: any_type TK_IDENTIFICADOR
parameter: TK_PR_CONST any_type TK_IDENTIFICADOR

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
command_in_block: io_command { $$ = NULL; }
command_in_block: action_command { $$ = $1; }

simple_command: attribution_command { $$ = $1; }
simple_command: function_call { $$ = tree_make_node(new_ast_node_value(AST_CHAMADA_DE_FUNCAO, NULL)); }
simple_command: shift_command { $$ = $1; }
simple_command: def_local_var { $$ = $1; }
simple_command: flux_command { $$ = $1; }
simple_command: '{' command_sequence '}' {	$$ = tree_make_unary_node(new_ast_node_value(AST_BLOCO, NULL), $2); }

io_command: input_command
io_command: output_command

def_local_var: TK_IDENTIFICADOR TK_IDENTIFICADOR { $$ = NULL; }
def_local_var: primitive_type TK_IDENTIFICADOR { $$ = NULL; }
def_local_var: primitive_type TK_IDENTIFICADOR TK_OC_LE expression { $$ = tree_make_node(new_ast_node_value(AST_ATRIBUICAO, NULL)); }
def_local_var: TK_PR_STATIC TK_IDENTIFICADOR TK_IDENTIFICADOR { $$ = NULL; }
def_local_var: TK_PR_STATIC primitive_type TK_IDENTIFICADOR { $$ = NULL; }
def_local_var: TK_PR_STATIC primitive_type TK_IDENTIFICADOR TK_OC_LE expression { $$ = tree_make_node(new_ast_node_value(AST_ATRIBUICAO, NULL)); }
def_local_var: TK_PR_CONST TK_IDENTIFICADOR TK_IDENTIFICADOR { $$ = NULL; }
def_local_var: TK_PR_CONST primitive_type TK_IDENTIFICADOR { $$ = NULL; }
def_local_var: TK_PR_CONST primitive_type TK_IDENTIFICADOR TK_OC_LE expression { $$ = tree_make_node(new_ast_node_value(AST_ATRIBUICAO, NULL)); }
def_local_var: TK_PR_STATIC TK_PR_CONST TK_IDENTIFICADOR TK_IDENTIFICADOR { $$ = NULL; }
def_local_var: TK_PR_STATIC TK_PR_CONST primitive_type TK_IDENTIFICADOR { $$ = NULL; }
def_local_var: TK_PR_STATIC TK_PR_CONST primitive_type TK_IDENTIFICADOR TK_OC_LE expression { $$ = tree_make_node(new_ast_node_value(AST_ATRIBUICAO, NULL)); }

attribution_command: TK_IDENTIFICADOR '=' expression { $$ = tree_make_node(new_ast_node_value(AST_ATRIBUICAO, NULL)); }
attribution_command: TK_IDENTIFICADOR '[' expression ']' '=' expression { $$ = tree_make_node(new_ast_node_value(AST_ATRIBUICAO, NULL)); }
attribution_command: TK_IDENTIFICADOR '$' TK_IDENTIFICADOR '=' expression { $$ = tree_make_node(new_ast_node_value(AST_ATRIBUICAO, NULL)); }

input_command: TK_PR_INPUT expression

output_command: TK_PR_OUTPUT expression_sequence

function_call: TK_IDENTIFICADOR '(' expression_sequence ')'
function_call: TK_IDENTIFICADOR '(' ')'

shift_command: TK_IDENTIFICADOR TK_OC_SL TK_LIT_INT { $$ = tree_make_node(new_ast_node_value(AST_SHIFT_LEFT, NULL)); }
shift_command: TK_IDENTIFICADOR TK_OC_SR TK_LIT_INT { $$ = tree_make_node(new_ast_node_value(AST_SHIFT_RIGHT, NULL)); }

flux_command: condition_command
flux_command: iteration_command
flux_command: selection_command

condition_command: TK_PR_IF '(' expression ')' TK_PR_THEN body { $$ = tree_make_node(new_ast_node_value(AST_IF_ELSE, NULL)); }
condition_command: TK_PR_IF '(' expression ')' TK_PR_THEN body TK_PR_ELSE body { $$ = tree_make_node(new_ast_node_value(AST_IF_ELSE, NULL)); }

iteration_command: TK_PR_FOREACH '(' TK_IDENTIFICADOR ':' foreach_expression_sequence ')' body { $$ = NULL; }
iteration_command: TK_PR_FOR '(' for_command_sequence ':' expression ':' for_command_sequence ')' body { $$ = NULL; }
iteration_command: TK_PR_WHILE '(' expression ')' TK_PR_DO body { $$ = tree_make_node(new_ast_node_value(AST_WHILE_DO, NULL)); }
iteration_command: TK_PR_DO body TK_PR_WHILE '(' expression ')' { $$ = tree_make_node(new_ast_node_value(AST_DO_WHILE, NULL)); }

selection_command: TK_PR_SWITCH '(' expression ')' body { $$ = NULL; }

for_command_sequence: simple_command
for_command_sequence: simple_command ',' for_command_sequence

foreach_expression_sequence: expression
foreach_expression_sequence: expression ',' foreach_expression_sequence

action_command: TK_PR_RETURN expression { $$ = tree_make_node(new_ast_node_value(AST_RETURN, NULL)); }
action_command: TK_PR_CONTINUE { $$ = NULL; }
action_command: TK_PR_BREAK { $$ = NULL; }


// definicoes de tipos

def_type: TK_PR_CLASS TK_IDENTIFICADOR '[' type_fields ']' ';'
type_fields: type_field
type_fields: type_field ':' type_fields
type_field: encapsulation primitive_type TK_IDENTIFICADOR
type_field: encapsulation primitive_type TK_IDENTIFICADOR '[' expression ']'

encapsulation: TK_PR_PROTECTED
encapsulation: TK_PR_PRIVATE
encapsulation: TK_PR_PUBLIC

primitive_type: TK_PR_INT
primitive_type: TK_PR_FLOAT
primitive_type: TK_PR_BOOL
primitive_type: TK_PR_CHAR
primitive_type: TK_PR_STRING


//expressions e expressions sequences

expression: operator sub_expression
expression: sub_expression_chain
sub_expression_chain: sub_expression
sub_expression_chain: sub_expression operator sub_expression_chain

sub_expression: '(' expression ')'
sub_expression: literal
sub_expression: TK_IDENTIFICADOR
sub_expression: TK_IDENTIFICADOR '[' expression ']'
sub_expression: function_call


literal: TK_LIT_INT
literal: TK_LIT_FLOAT
literal: TK_LIT_CHAR
literal: TK_LIT_TRUE
literal: TK_LIT_FALSE
literal: TK_LIT_STRING

operator: TK_OC_LE
operator: TK_OC_GE
operator: TK_OC_EQ
operator: TK_OC_NE
operator: TK_OC_AND
operator: TK_OC_OR
operator: '+'
operator: '-'
operator: '/'
operator: '*'

expression_sequence: expression
expression_sequence: expression ',' expression_sequence

%%
