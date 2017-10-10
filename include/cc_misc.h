#ifndef __MISC_H
#define __MISC_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "cc_tree.h"
#include "cc_ast.h"

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

void set_ast_root(comp_tree_t* root);
comp_tree_t* get_ast_root();
void putToGraphviz(comp_tree_t *pai);

int getLineNumber (void);
void yyerror (char const *mensagem);
void comp_print_table();
void concatTokenType(char *key, int token_type);
void clearPointerToFreeTable();
void clearSymbolsTable();
void removeQuotes(char *key);
void remove_collisions(comp_dict_item_t * item);
void remove_collisions_pointer_to_free(comp_dict_item_t * item);
void setEntryValue(st_value_t* entryValue, char* value);
st_value_t* putToSymbolsTable(char* key, int line, int token_type);
void main_init (int argc, char **argv);
void main_finalize (void);
int comp_set_line_number (char *yytext);

#endif
