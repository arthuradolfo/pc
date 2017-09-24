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
programa: def_global_var programa;
programa: def_funcs programa;

def_type : TK_PR_CLASS TK_IDENTIFICADOR '[' type_fields ']' ';' ;
type_fields : %empty
type_fields : type_field more_fields
more_fields: %empty
more_fields: one_more_field more_fields
one_more_field : ':' type_field
type_field : encapsulation primitive_type TK_IDENTIFICADOR

encapsulation : TK_PR_PROTECTED
encapsulation : TK_PR_PRIVATE
encapsulation : TK_PR_PUBLIC ;

def_global_var: TK_PR_STATIC type_var TK_IDENTIFICADOR '[' TK_LIT_INT ']' ';';
def_global_var: TK_PR_STATIC type_var TK_IDENTIFICADOR ';';
def_global_var: type_var TK_IDENTIFICADOR '[' TK_LIT_INT ']' ';';
def_global_var: type_var TK_IDENTIFICADOR ';';

def_funcs: header body;
header: TK_PR_STATIC type_var TK_IDENTIFICADOR '(' parameters ')'
header: type_var TK_IDENTIFICADOR '(' parameters ')'
body: '{' command_sequence '}'

command_sequence: %empty
command_sequence: simple_command command_sequence

simple_command: def_local_var ';'
simple_command: atribuition_command ';'
simple_command: input_command ';'
simple_command: output_command ';'
simple_command: func_call ';'
simple_command: shift_command ';'
simple_command: action_command

def_local_var: TK_PR_STATIC TK_PR_CONST type_var_user TK_IDENTIFICADOR
def_local_var: TK_PR_STATIC TK_PR_CONST type_var_local TK_IDENTIFICADOR
def_local_var: TK_PR_STATIC TK_PR_CONST type_var_local TK_IDENTIFICADOR innitialize
def_local_var: TK_PR_CONST type_var_user TK_IDENTIFICADOR ';'
def_local_var: TK_PR_CONST type_var_local TK_IDENTIFICADOR
def_local_var: TK_PR_CONST type_var_local TK_IDENTIFICADOR innitialize
def_local_var: TK_PR_STATIC type_var_user TK_IDENTIFICADOR
def_local_var: TK_PR_STATIC type_var_local TK_IDENTIFICADOR
def_local_var: TK_PR_STATIC type_var_local TK_IDENTIFICADOR innitialize
def_local_var: type_var_user TK_IDENTIFICADOR
def_local_var: type_var_local TK_IDENTIFICADOR
def_local_var: type_var_local TK_IDENTIFICADOR innitialize

atribuition_command: TK_IDENTIFICADOR '=' expression
atribuition_command: TK_IDENTIFICADOR '[' expression ']' '=' expression
atribuition_command: TK_IDENTIFICADOR '$' TK_IDENTIFICADOR '=' expression

input_command: TK_PR_INPUT expression

output_command: TK_PR_OUTPUT expression expression_sequence

func_call: TK_IDENTIFICADOR '(' expression_sequence ')'

shift_command: TK_IDENTIFICADOR TK_OC_SL TK_LIT_INT
shift_command: TK_IDENTIFICADOR TK_OC_SR TK_LIT_INT

action_command: TK_PR_RETURN expression ';'
action_command: TK_PR_CONTINUE ';'
action_command: TK_PR_BREAK ';'
action_command: TK_PR_CASE TK_LIT_INT ':'

expression_sequence: %empty
expression_sequence: ',' expression_sequence
expression_sequence: expression expression_sequence

innitialize: TK_OC_LE expression

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
parameters: TK_PR_CONST type_var TK_IDENTIFICADOR parameters
parameters: type_var TK_IDENTIFICADOR parameters
parameters: ',' parameters

type_var_local: TK_PR_INT
type_var_local: TK_PR_FLOAT
type_var_local: TK_PR_BOOL
type_var_local: TK_PR_CHAR
type_var_local: TK_PR_STRING

type_var: primitive_type
type_var: type_var_user

primitive_type: TK_PR_INT
primitive_type: TK_PR_FLOAT
primitive_type: TK_PR_BOOL
primitive_type: TK_PR_CHAR
primitive_type: TK_PR_STRING

type_var_user: TK_IDENTIFICADOR
%%
