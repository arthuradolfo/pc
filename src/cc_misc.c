#include "cc_misc.h"
#include "cc_dict.h"
#include "symbols_table.h"
#include "syntax_tree.h"
#include "semantics.h"


/**
  * @var int lineNumber Gerencia o numero de linahs do arquivo processado
  */
int lineNumber;

/**
  * Confere os \n no token e soma no lineNumber
  * @param char* yytext
  */
int comp_set_line_number (char *yytext)
{
  int i = 0;
  while(i < strlen(yytext)) {
    if(yytext[i] == '\n') {
      lineNumber++;
    }
    i++;
  }
}

/**
  * Getter da variavel lineNumber
  * @return int lineNumber
  */
int comp_get_line_number (void)
{
  return lineNumber;
}

void yyerror (char const *mensagem)
{
  fprintf (stderr, "%s in line %d\n", mensagem, lineNumber); //altere para que apareça a linha
}

void main_init (int argc, char **argv)
{
  //implemente esta função com rotinas de inicialização, se necessário
  lineNumber = 1;
  pointersToFreeTable = dict_new();
  symbolsTable = dict_new();
  funcs_params = dict_new();
  scope_stack = new_stack();

  current_type_decl = NULL;
  current_func_decl = NULL;

  //abstractSyntaxTree = tree_new();
  gv_init(GRAPHVIZ_FILENAME);
}

void main_finalize (void)
{
  // st_stack_item_t *item;
  // st_stack_item_t *item1;
  //implemente esta função com rotinas de finalização, se necessário

  // printf("Print table:\n");
  // comp_print_table();

  gv_close();
  clearSymbolsTable();
  clearFuncParams();
  clearAndFreeAST();
  clearPointerToFreeTable();

  clear_scope_stack_values(scope_stack);
  free_stack(scope_stack);

  free(get_current_type_decl());
  free(get_current_func_decl());
}
