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
more_fields: one_more_field more_fields
one_more_field : ':' type_field
type_field : encapsulation primitive_type TK_IDENTIFICADOR

encapsulation : TK_PR_PROTECTED
encapsulation : TK_PR_PRIVATE
encapsulation : TK_PR_PUBLIC ;

def_global_var: any_type TK_IDENTIFICADOR '[' TK_LIT_INT ']' ';'
def_global_var: any_type TK_IDENTIFICADOR ';'

def_function: header body;
header: any_type TK_IDENTIFICADOR '(' parameters ')'
body: '{' command_sequence '}'

command_sequence: %empty
command_sequence: simple_command command_sequence

simple_command: TK_IDENTIFICADOR command_proceeding_identifier ';'
simple_command: def_local_var ';'
simple_command: input_command ';'
simple_command: output_command ';'
simple_command: action_command

command_proceeding_identifier: attribution_command
command_proceeding_identifier: func_call
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

func_call: '(' expression_sequence ')'

shift_command: TK_OC_SL TK_LIT_INT
shift_command: TK_OC_SR TK_LIT_INT

action_command: TK_PR_RETURN expression ';'
action_command: TK_PR_CONTINUE ';'
action_command: TK_PR_BREAK ';'
action_command: TK_PR_CASE TK_LIT_INT ':'

expression_sequence: %empty
expression_sequence: ',' expression_sequence
expression_sequence: expression expression_sequence

expression: TK_LIT_INT
expression: TK_LIT_FLOAT
expression: TK_LIT_CHAR
expression: TK_LIT_TRUE
expression: TK_LIT_FALSE
expression: TK_LIT_STRING
expression: TK_IDENTIFICADOR array_expression

array_expression: '[' expression ']'
array_expression: %empty

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
