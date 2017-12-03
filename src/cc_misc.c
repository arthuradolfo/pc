#include "cc_misc.h"
#include "tac.h"


/**
  * @var int lineNumber Gerencia o numero de linhas do arquivo processado
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
  fprintf (stderr, "%s in line %d\n", mensagem, lineNumber);
}

void main_init (int argc, char **argv)
{
  lineNumber = 1;

  //inicializacao da estrutura de limpeza
  pointersToFreeTable = dict_new();

  //inicializacao da tabela de simbolos principal
  symbolsTable = dict_new();

  endOffsetGlobalSymbolsTable = 0;

  //inicializacao das variaveis de semantica
  funcs_params = dict_new();
  scope_stack = new_stack();
  current_type_decl = NULL;
  current_func_decl = NULL;

  //inicializacao das variaveis de tac
  label_counter = 1;
  register_counter = 1;

  //inicializacao do graphviz (inicializacao da ast está no parser.y - programa:)
  gv_init(GRAPHVIZ_FILENAME);


  //TODO remove
  tac_basic_tests();
  tac_stack_test();
}

void main_finalize (void)
{
  // comp_print_table();

  gv_close();
  clearSymbolsTable();
  clearFuncParams();
  clearAndFreeAST();
  clearPointerToFreeTable();

  clear_scope_stack_values();
  free_stack(scope_stack);

  free(get_current_type_decl());
  free(get_current_func_decl());
}
