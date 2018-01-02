#include "cc_misc.h"
#include "optimization.h"
#include "tac.h"
#include "semantics.h"

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
  optimization_module_init(argc, argv);

  #ifdef OPTM_TST
    run_optimization_tests();
    exit(EXIT_SUCCESS);
  #endif

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
  current_vector_stack = new_stack();

  //inicializacao das variaveis de suporte a execução
  current_func_def_sizes = new_func_def();

  //inicializacao do graphviz (inicializacao da ast está no parser.y - programa:)
  gv_init(GRAPHVIZ_FILENAME);
}

void main_finalize (void)
{
  //TODO chamar módulo de otimização se necessário

  #ifdef DEBUG
    printf("\nFim da Análise -"); print_optimization_mode(); printf("\n\n");
  #endif

  iloc_to_stdout(((ast_node_value_t*) abstractSyntaxTree->value)->tac_stack);

  gv_close();
  clearSymbolsTable();
  clearFuncParams();
  clearAndFreeAST();
  clearPointerToFreeTable();

  clear_scope_stack_values();
  free_stack(scope_stack);

  free(get_current_type_decl());
  free(get_current_func_decl());

  free_stack(current_vector_stack);

  free(current_func_def_sizes);
}
