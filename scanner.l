/*
  Arthur Adolfo 			- 	00262515
  Gabriel de Souza Seibel 	- 	00262513
*/

LTR  [a-z_A-Z]
DGT  [0-9]
BCM	 "//"
ESP  [!#-&(-\-/:->[-^{}]
INT  {DGT}+
FLT  {INT}\.{DGT}+

%{
#include "parser.h" //arquivo automaticamente gerado pelo bison
#include "cc_misc.h" //arquivo com funcoes de auto incremento
#include "semantics.h"
#include "main.h" //arquivo com constantes da main
%}

%%
[\n|\r\n]					                comp_set_line_number(yytext);
"int"                         return TK_PR_INT;
"float"                       return TK_PR_FLOAT;
"bool"                        return TK_PR_BOOL;
"char"                        return TK_PR_CHAR;
"string"                      return TK_PR_STRING;
"if"                          return TK_PR_IF;
"then"                        return TK_PR_THEN;
"else"                        return TK_PR_ELSE;
"while"                       return TK_PR_WHILE;
"do"                          return TK_PR_DO;
"input"                       return TK_PR_INPUT;
"output"                      return TK_PR_OUTPUT;
"return"                      return TK_PR_RETURN;
"const"                       return TK_PR_CONST;
"static"                      return TK_PR_STATIC;
"foreach"                     return TK_PR_FOREACH;
"for"                         return TK_PR_FOR;
"switch"                      return TK_PR_SWITCH;
"case"                        return TK_PR_CASE;
"break"                       return TK_PR_BREAK;
"continue"                    return TK_PR_CONTINUE;
"class"                       return TK_PR_CLASS;
"private"                     return TK_PR_PRIVATE;
"public"                      return TK_PR_PUBLIC;
"protected"                   return TK_PR_PROTECTED;
"false"						            yylval.valor_lexico = putToCurrentST(yytext, comp_get_line_number(), POA_LIT_BOOL); return TK_LIT_FALSE;
"true"						            yylval.valor_lexico = putToCurrentST(yytext, comp_get_line_number(), POA_LIT_BOOL); return TK_LIT_TRUE;
{INT}          					  	  yylval.valor_lexico = putToCurrentST(yytext, comp_get_line_number(),POA_LIT_INT); return TK_LIT_INT;
{FLT}				                  yylval.valor_lexico = putToCurrentST(yytext, comp_get_line_number(), POA_LIT_FLOAT); return TK_LIT_FLOAT;
'.'						                yylval.valor_lexico = putToCurrentST(yytext, comp_get_line_number(), POA_LIT_CHAR); return TK_LIT_CHAR;
\"(\\.|[^"])*\"				        yylval.valor_lexico = putToCurrentST(yytext, comp_get_line_number(), POA_LIT_STRING); return TK_LIT_STRING;
{ESP}						              return yytext[0];
"<="						              return TK_OC_LE;
">="						              return TK_OC_GE;
"=="						              return TK_OC_EQ;
"!="						              return TK_OC_NE;
"&&"						              return TK_OC_AND;
"||"						              return TK_OC_OR;
"<<"						              return TK_OC_SL;
">>"						              return TK_OC_SR;
{LTR}({LTR}|{DGT})*           yylval.valor_lexico = strdup(yytext); return TK_IDENTIFICADOR;
{BCM}(.*)		  			          //nao faz nada
"/*"((.|\n)*)"*/"		  	      comp_set_line_number(yytext);
[ \t]+        				        //nao faz nada
.                             return TOKEN_ERRO;
%%
