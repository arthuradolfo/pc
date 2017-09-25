/*
  Arthur Adolfo 			- 	00262515
  Gabriel de Souza Seibel 	- 	00262513
*/
%{
#include "parser.h" //arquivo automaticamente gerado pelo bison
#include "main.h"
#include "cc_misc.h" //arquivo com funcoes de auto incremento
%}

%union
{
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

%%
/* Regras (e ações) da gramática */

programa: %empty;
programa: def_type programa;
programa: optional_static def_global_var_or_def_function programa
def_global_var_or_def_function: def_global_var
def_global_var_or_def_function: def_function

def_type : TK_PR_CLASS TK_IDENTIFICADOR '[' type_fields ']' ';' ;
type_fields : type_field more_fields
more_fields: %empty
more_fields: ':' type_field more_fields
type_field : encapsulation primitive_type TK_IDENTIFICADOR optional_vector_modifier

encapsulation : TK_PR_PROTECTED
encapsulation : TK_PR_PRIVATE
encapsulation : TK_PR_PUBLIC

def_global_var: any_type TK_IDENTIFICADOR optional_vector_modifier ';'

optional_vector_modifier: '[' TK_LIT_INT ']'
optional_vector_modifier: %empty

def_function: header body;
header: any_type TK_IDENTIFICADOR '(' parameters ')'
body: '{' command_sequence '}'

command_sequence: %empty
command_sequence: command_in_block command_sequence

command_in_block: simple_command ';'
command_in_block: action_command

simple_command: TK_IDENTIFICADOR command_proceeding_identifier
simple_command: def_local_var
simple_command: input_command
simple_command: output_command
simple_command: body
simple_command: flux_command

command_proceeding_identifier: attribution_command
command_proceeding_identifier: func_modifier
command_proceeding_identifier: shift_command

def_local_var: optional_static optional_const def_local_var_tail
def_local_var_tail: TK_IDENTIFICADOR TK_IDENTIFICADOR
def_local_var_tail: primitive_type TK_IDENTIFICADOR optional_init

optional_static: %empty
optional_static: TK_PR_STATIC
optional_const: %empty
optional_const: TK_PR_CONST
optional_init: %empty
optional_init: TK_OC_LE expression

attribution_command: '=' expression
attribution_command: '[' expression ']' '=' expression
attribution_command: '$' TK_IDENTIFICADOR '=' expression

input_command: TK_PR_INPUT expression

output_command: TK_PR_OUTPUT expression expression_sequence

func_modifier: '(' expression_sequence ')'

shift_command: TK_OC_SL TK_LIT_INT
shift_command: TK_OC_SR TK_LIT_INT

flux_command: condition_command
flux_command: iteration_command
flux_command: selection_command

condition_command: TK_PR_IF '(' expression ')' TK_PR_THEN body optional_else
optional_else: %empty
optional_else: TK_PR_ELSE body

iteration_command: TK_PR_FOREACH '(' TK_IDENTIFICADOR ':' foreach_expression_sequence ')' body
iteration_command: TK_PR_FOR '(' for_command_sequence ':' expression ':' for_command_sequence ')' body
iteration_command: TK_PR_WHILE '(' expression ')' TK_PR_DO body
iteration_command: TK_PR_DO body TK_PR_WHILE '(' expression ')'

selection_command: TK_PR_SWITCH '(' expression ')' body

for_command_sequence: simple_command optional_extra_for_commands
optional_extra_for_commands: %empty
optional_extra_for_commands: ',' simple_command optional_extra_for_commands

foreach_expression_sequence: expression optional_extra_foreach_expressions
optional_extra_foreach_expressions: %empty
optional_extra_foreach_expressions: ',' expression optional_extra_foreach_expressions

action_command: TK_PR_RETURN expression ';'
action_command: TK_PR_CONTINUE ';'
action_command: TK_PR_BREAK ';'
action_command: TK_PR_CASE TK_LIT_INT ':'

expression_sequence: %empty
expression_sequence: ',' expression_sequence
expression_sequence: expression expression_sequence

expression: literal
expression: '(' expression ')'
expression: TK_IDENTIFICADOR func_or_array_modifier
expression: expression arit_log_operator expression

literal: TK_LIT_INT
literal: TK_LIT_FLOAT
literal: TK_LIT_CHAR
literal: TK_LIT_TRUE
literal: TK_LIT_FALSE
literal: TK_LIT_STRING

func_or_array_modifier: optional_array_modifier
func_or_array_modifier: optional_func_modifier

optional_func_modifier: func_modifier
optional_func_modifier: %empty
optional_array_modifier: '[' expression ']'
optional_array_modifier: %empty

arit_log_operator: log_operator
arit_log_operator: arit_operator
log_operator: TK_OC_LE
log_operator: TK_OC_GE
log_operator: TK_OC_EQ
log_operator: TK_OC_NE
log_operator: TK_OC_AND
log_operator: TK_OC_OR
arit_operator: '+'
arit_operator: '-'
arit_operator: '/'
arit_operator: '*'

parameters: %empty
parameters: TK_PR_CONST any_type TK_IDENTIFICADOR parameters
parameters: any_type TK_IDENTIFICADOR parameters
parameters: ',' parameters

any_type: primitive_type
any_type: TK_IDENTIFICADOR

primitive_type: TK_PR_INT
primitive_type: TK_PR_FLOAT
primitive_type: TK_PR_BOOL
primitive_type: TK_PR_CHAR
primitive_type: TK_PR_STRING

%%
