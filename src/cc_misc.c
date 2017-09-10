#include "cc_misc.h"
#include "cc_dict.h"

int lineNumber;
comp_dict_t* symbolsTable;

void remove_collisions(comp_dict_item_t * item)
{
  comp_dict_item_t* ptaux;
  while (item != NULL) {
    ptaux = item;
    free(ptaux->value);
    item = item->next;
    dict_remove(symbolsTable, ptaux->key);
  }
}

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

int comp_get_line_number (void)
{
  //implemente esta função

  return lineNumber;
}

void yyerror (char const *mensagem)
{
  fprintf (stderr, "%s\n", mensagem); //altere para que apareça a linha
}

void putToSymbolsTable(char* key, int line)
{
  if (!symbolsTable) return;

  st_value_t* entryValue = (st_value_t *) malloc(sizeof(st_value_t));
  entryValue->line = line;
  st_value_t* getEntry = dict_get(symbolsTable, key);
  if(getEntry) {
    free(entryValue);
    getEntry->line = line;
  }
  else {
    dict_put(symbolsTable, key, entryValue);
  }
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

void printSymbolsTable()
{
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

void clearSymbolsTable()
{
    //remover todas as entradas da tabela antes de libera-la
    //printf("\nclearSymbolsTable: \n");

    if (!symbolsTable) return;

    int i, l;
    for (i = 0, l = symbolsTable->size; i < l; i++) {
      if (symbolsTable->data[i]) {
        if(symbolsTable->data[i]->next) {
          remove_collisions(symbolsTable->data[i]->next);
        }
        free(symbolsTable->data[i]->value);
        dict_remove(symbolsTable, symbolsTable->data[i]->key);
      }
    }
    dict_free(symbolsTable);

    //printf("symbolsTable freed\n");
}

void putSomeEntries()
{
  //printf("\nputSomeEntries: \n");

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
  lineNumber = 1;
  symbolsTable = dict_new();

  //putToSymbolsTable("Bolo", 87);
}

void main_finalize (void)
{
  //implemente esta função com rotinas de finalização, se necessário

  //comp_print_table();
  clearSymbolsTable();
}

void comp_print_table (void)
{
  //para cada entrada na tabela de símbolos
  //Etapa 1: chame a função cc_dict_etapa_1_print_entrada
  //implemente esta função

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
