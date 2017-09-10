#include "cc_misc.h"
#include "cc_dict.h"

int lineNumber;
comp_dict_t* symbolsTable;

int comp_get_line_number (void)
{
  //implemente esta função

  return lineNumber;
}

void yyerror (char const *mensagem)
{
  fprintf (stderr, "%s\n", mensagem); //altere para que apareça a linha
}

void getAndPrintSomeEntries()
{
  printf("\ngetAndPrintSomeEntries: \n");

  if (!symbolsTable) return;

  st_value_t* entradaAdolfo = dict_get(symbolsTable, "Arthur");
  st_value_t* entradaSeibel = dict_get(symbolsTable, "Seibel");
  st_value_t* entradaLeticia = dict_get(symbolsTable, "Leticia");
  st_value_t* entradaPablo = dict_get(symbolsTable, "Pablo");

  printf("Get entrada Adolfo: linha %d\n", entradaAdolfo->line);
  printf("Get entrada Seibel: linha %d\n", entradaSeibel->line);
  printf("Get entrada Leticia: linha %d\n", entradaLeticia->line);
  printf("Get entrada Pablo: linha %d\n", entradaPablo->line);
}

void printSymbolsTable() {
  printf("\nprintSymbolsTable: \n");

  if (!symbolsTable) return;

  int i, l;
  st_value_t* entrada;
  for (i = 0, l = symbolsTable->size; i < l; ++i) {
    if (symbolsTable->data[i]) {
      entrada = dict_get(symbolsTable, symbolsTable->data[i]->key);
      printf("Chave %s Valor %d\n", symbolsTable->data[i]->key, entrada->line);
    }
  }
}

void clearSymbolsTable() {
    //remover todas as entradas da tabela antes de libera-la
    printf("\nclearSymbolsTable: \n");

    if (!symbolsTable) return;

    int i, l;
    st_value_t* entrada;
    for (i = 0, l = symbolsTable->size; i < l; ++i) {
      if (symbolsTable->data[i]) {
        dict_remove(symbolsTable, symbolsTable->data[i]->key);
      }
    }
    dict_free(symbolsTable);

    printf("symbolsTable freed\n");
}

void putSomeEntries() {
  printf("\nputSomeEntries: \n");

  if (!symbolsTable) return;

  st_value_t* valueAdolfo = (st_value_t*) malloc(sizeof(st_value_t));
  valueAdolfo->line = 41;
  st_value_t* valueSeibel = (st_value_t*) malloc(sizeof(st_value_t));
  valueSeibel->line = 42;
  st_value_t* valueLeticia = (st_value_t*) malloc(sizeof(st_value_t));
  valueLeticia->line = 43;
  st_value_t* valuePablo = (st_value_t*) malloc(sizeof(st_value_t));
  valuePablo->line = 44;

  dict_put(symbolsTable, "Arthur", valueAdolfo);
  dict_put(symbolsTable, "Seibel", valueSeibel);
  dict_put(symbolsTable, "Leticia", valueLeticia);
  dict_put(symbolsTable, "Pablo", valuePablo);
}

void main_init (int argc, char **argv)
{
  //implemente esta função com rotinas de inicialização, se necessário
  printf("\nmain_init: \n");
  lineNumber = 1;

  symbolsTable = dict_new();
  dict_debug_print(symbolsTable);

  putSomeEntries();
  dict_debug_print(symbolsTable);
  getAndPrintSomeEntries();
  comp_print_table();

  printf("\nmain: \n");
}

void main_finalize (void)
{
  //implemente esta função com rotinas de finalização, se necessário
  printf("\nmain_finalize: \n");
  comp_print_table();
  getAndPrintSomeEntries();
  clearSymbolsTable();
}

void comp_print_table (void)
{
  //para cada entrada na tabela de símbolos
  //Etapa 1: chame a função cc_dict_etapa_1_print_entrada
  //implemente esta função
  printf("\ncomp_print_table:\n");

  if (!symbolsTable) return;

  int i, l;
  st_value_t* entrada;
  for (i = 0, l = symbolsTable->size; i < l; ++i) {
    if (symbolsTable->data[i]) {
      entrada = dict_get(symbolsTable, symbolsTable->data[i]->key);
      //printf("Chave %s Valor %d\n", symbolsTable->data[i]->key, entrada->line);
      cc_dict_etapa_1_print_entrada(symbolsTable->data[i]->key, entrada->line);
    }
  }
}
