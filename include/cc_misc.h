#ifndef __MISC_H
#define __MISC_H
#include <stdio.h>
#include <stdlib.h>

typedef struct symbolsTable_value {
    int line;
} st_value_t;


int getLineNumber (void);
void yyerror (char const *mensagem);
void comp_print_table();
void main_init (int argc, char **argv);
void main_finalize (void);

#endif
