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

// programa e declaracao de globais (SEM CONFLITOS)

programa: %empty
programa: def_type programa
programa: def_global_var programa
programa: def_function programa

def_global_var: any_type TK_IDENTIFICADOR ';'
def_global_var: any_type TK_IDENTIFICADOR '[' expression ']' ';'
def_global_var: TK_PR_STATIC any_type TK_IDENTIFICADOR ';'
def_global_var: TK_PR_STATIC any_type TK_IDENTIFICADOR '[' expression ']' ';'

any_type: TK_IDENTIFICADOR
any_type: primitive_type


// funcoes (SEM CONFLITOS)

def_function: header body;
def_function: TK_PR_STATIC header body;
header: any_type TK_IDENTIFICADOR '(' parameters ')'
body: '{' command_sequence '}'

//tem erro aqui (cuidar virgula no fim da lista)
parameters: %empty
parameters: parameter
parameters: parameter parameter_chain

parameter_chain: ',' parameter
parameter_chain: ',' parameter parameter_chain

parameter: any_type TK_IDENTIFICADOR
parameter: TK_PR_CONST any_type TK_IDENTIFICADOR

command_sequence: %empty
command_sequence: command_in_block ';' command_sequence
command_sequence: TK_PR_CASE TK_LIT_INT ':' command_sequence

command_in_block: simple_command
command_in_block: io_command
command_in_block: action_command

simple_command: attribution_command
simple_command: function_call
simple_command: shift_command
simple_command: def_local_var
simple_command: body
simple_command: flux_command

io_command: input_command
io_command: output_command

def_local_var: TK_IDENTIFICADOR TK_IDENTIFICADOR
def_local_var: primitive_type TK_IDENTIFICADOR
def_local_var: primitive_type TK_IDENTIFICADOR TK_OC_LE expression
def_local_var: TK_PR_STATIC TK_IDENTIFICADOR TK_IDENTIFICADOR
def_local_var: TK_PR_STATIC primitive_type TK_IDENTIFICADOR
def_local_var: TK_PR_STATIC primitive_type TK_IDENTIFICADOR TK_OC_LE expression
def_local_var: TK_PR_CONST TK_IDENTIFICADOR TK_IDENTIFICADOR
def_local_var: TK_PR_CONST primitive_type TK_IDENTIFICADOR
def_local_var: TK_PR_CONST primitive_type TK_IDENTIFICADOR TK_OC_LE expression
def_local_var: TK_PR_STATIC TK_PR_CONST TK_IDENTIFICADOR TK_IDENTIFICADOR
def_local_var: TK_PR_STATIC TK_PR_CONST primitive_type TK_IDENTIFICADOR
def_local_var: TK_PR_STATIC TK_PR_CONST primitive_type TK_IDENTIFICADOR TK_OC_LE expression

attribution_command: TK_IDENTIFICADOR '=' expression
attribution_command: TK_IDENTIFICADOR '[' expression ']' '=' expression
attribution_command: TK_IDENTIFICADOR '$' TK_IDENTIFICADOR '=' expression

input_command: TK_PR_INPUT expression

output_command: TK_PR_OUTPUT expression_sequence

function_call: TK_IDENTIFICADOR '(' expression_sequence ')'
function_call: TK_IDENTIFICADOR '(' ')'

shift_command: TK_IDENTIFICADOR TK_OC_SL TK_LIT_INT
shift_command: TK_IDENTIFICADOR TK_OC_SR TK_LIT_INT

flux_command: condition_command
flux_command: iteration_command
flux_command: selection_command

condition_command: TK_PR_IF '(' expression ')' TK_PR_THEN body
condition_command: TK_PR_IF '(' expression ')' TK_PR_THEN body TK_PR_ELSE body

iteration_command: TK_PR_FOREACH '(' TK_IDENTIFICADOR ':' foreach_expression_sequence ')' body
iteration_command: TK_PR_FOR '(' for_command_sequence ':' expression ':' for_command_sequence ')' body
iteration_command: TK_PR_WHILE '(' expression ')' TK_PR_DO body
iteration_command: TK_PR_DO body TK_PR_WHILE '(' expression ')'

selection_command: TK_PR_SWITCH '(' expression ')' body

for_command_sequence: simple_command
for_command_sequence: simple_command ',' for_command_sequence

foreach_expression_sequence: expression
foreach_expression_sequence: expression ',' foreach_expression_sequence

action_command: TK_PR_RETURN expression
action_command: TK_PR_CONTINUE
action_command: TK_PR_BREAK


// definicoes de tipos (SEM CONFLITOS)

def_type: TK_PR_CLASS TK_IDENTIFICADOR '[' type_fields ']' ';' ;
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


//expressions e expressions sequences (SEM CONFLITOS)

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
