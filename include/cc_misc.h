#ifndef __MISC_H
#define __MISC_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"

union Value {
	int i;
	float f;
	bool b;
	char c;
	char *s;
};

typedef struct symbolsTable_value {
    int line;
    int token_type;
    union Value value;
} st_value_t;


int getLineNumber (void);
void yyerror (char const *mensagem);
void comp_print_table();
void concatTokeType(char *key, int token_type);
void removeQuotes(char *key);
void setEntryValue(st_value_t* entryValue, char* value);
st_value_t* putToSymbolsTable(char* key, int line, int token_type);
void main_init (int argc, char **argv);
void main_finalize (void);
int comp_set_line_number (char *yytext);

#endif
