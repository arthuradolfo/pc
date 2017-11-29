#ifndef __MISC_H
#define __MISC_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"

int getLineNumber (void);
void yyerror (char const *mensagem);
void comp_print_table();
void main_init (int argc, char **argv);
void main_finalize (void);
int comp_get_line_number (void);
int comp_set_line_number (char *yytext);

#endif
