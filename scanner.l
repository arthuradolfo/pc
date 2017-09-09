/*
  Coloque aqui o identificador do grupo e dos seus membros
*/

LTR  [a-z_A-Z]		
DGT  [0-9]		 		
BCM	 "//"				
ESP  [!#-&(-/:->[-^{}] 
OCP  (<=)|(>=)|(==)|(!=)|(&&)|("||")|(>>)|(<<)
INT  (-?){DGT}+
FLT  {INT}.{DGT}+

%{
#include "parser.h" //arquivo automaticamente gerado pelo bison
%}

%%
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
"false"						  return TK_LIT_FALSE;
"true"						  return TK_LIT_TRUE;
{INT}					  	  return TK_LIT_INT;
{FLT}				          return TK_LIT_FLOAT;
'.'						      return TK_LIT_CHAR;
["](.+)["]				      return TK_LIT_STRING;
{LTR}({LTR}|{DGT})*           return TK_IDENTIFICADOR;
{BCM}(.*)		  			  printf("Achei um comentario\n");//nao faz nada
"/*"[^*]*|[*]*"*/"		  	  printf("Achei um comentario\n");//nao faz nada
"\n"					      return TOKEN_NEWLINE;
{ESP}						  printf("%d\n", (int) yytext[0]);
{OCP}						  printf("%s\n", yytext);
[ ]+        				  //nao faz nada com espacos
.                             return TOKEN_ERRO;
%%