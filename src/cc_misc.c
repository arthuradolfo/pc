#include "cc_misc.h"
#include "cc_dict.h"
#include "cc_ast.h"

#define GRAPHVIZ_FILENAME "graphvizAST.dot"

/**
  * @var int lineNumber Gerencia o numero de linahs do arquivo processado
  */
int lineNumber;

/**
  * @var comp_dict_t symbolsTable Gerencia a tabela de simbolos
  */
comp_dict_t* symbolsTable;

comp_dict_t* pointersToFreeTable;

comp_tree_t* abstractSyntaxTree;

/**
  * Da free em ponteiros das entradas da tabela de simbolos que estao no ponteiro next (quando a colisao de entradas)
  * @param comp_dict_item_t* item
  */
void remove_collisions(comp_dict_item_t * item)
{
  comp_dict_item_t* ptaux;
  st_value_t* entrada;
  while (item != NULL) {
    ptaux = item;
    entrada = dict_get(symbolsTable, ptaux->key);
    if(entrada->token_type == POA_IDENT || entrada->token_type == POA_LIT_STRING) {
      free(entrada->value.s);
    }
    free(ptaux->value);
    item = item->next;
    dict_remove(symbolsTable, ptaux->key);
  }
}

void remove_collisions_pointer_to_free(comp_dict_item_t * item)
{
  comp_dict_item_t* ptaux;
  st_value_t* entrada;
  while (item != NULL) {
    ptaux = item;
    item = item->next;
    dict_remove(pointersToFreeTable, ptaux->key);
  }
}

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


/**
 * Converte o token para o tipo especificado e insere no campo value da entrada da tabela de simbolos
 * @param st_value_t* entryValue
 * @param char* value
 */
void setEntryValue(st_value_t* entryValue, char* value) {
  switch(entryValue->token_type) {
    case POA_LIT_INT:
      entryValue->value.i = atoi(value);
      free(value);
      break;

    case POA_LIT_FLOAT:
      entryValue->value.f = atof(value);
      free(value);
      break;

    case POA_LIT_CHAR:
      entryValue->value.c = *value;
      free(value);
      break;

    case POA_LIT_STRING:
      entryValue->value.s = value;
      break;

    case POA_LIT_BOOL:
      if(strcmp(value, "true") == 0) {
        entryValue->value.b = false;
      }
      else {
        entryValue->value.b = true;
      }
      free(value);
      break;

    case POA_IDENT:
      entryValue->value.s = value;
      break;

    default:
      break;
  }
}

/**
 * Remove aspas simples e duplas dos tokens tipo TK_LIT_STRING e TK_LIT_CHAR
 * @param char* key
 */
void removeQuotes(char *key) {
  int i = 0, string = 0;
  while(i < strlen(key)) {
    if(key[i] == '"' || key[i] == '\'') {
      string = 1;
      if(key[i+1] == '"') {
        key[i] = '\0';
      }
      else {
        key[i] = key[i+1];
      }
      key[strlen(key)-1] = '\0';
    }
    else if(string == 1) {
      key[i] = key[i+1];
    }
    i++;
  }
}

/**
  * Concatena tipo do token ao key
  * @param char* key
  * @param int token_type
  */
void concatTokenType(char *key, int token_type) {
  char *token_str = (char *) malloc(sizeof(char)*2);
  sprintf(token_str, "%d", token_type);
  strcat(key, token_str);
  free(token_str);
}

/**
 * Coloca o token na tabela de simbolos
 * @param char* key
 * @param int line
 * @int token_type
 * @return st_value_t* entryValue
 */
st_value_t* putToSymbolsTable(char* key, int line, int token_type)
{
  if (!symbolsTable) return;


  char *value;
  char *key_aux = (char *) malloc((strlen(key)+2)*sizeof(char));
  removeQuotes(key);

  strcpy(key_aux, key);

  value = strdup(key);

  concatTokenType(key_aux, token_type);

  st_value_t* entryValue = (st_value_t *) malloc(sizeof(st_value_t));

  entryValue->line = line;
  entryValue->token_type = token_type;

  setEntryValue(entryValue, value);

  st_value_t* getEntryPointerToFree = dict_get(pointersToFreeTable, key);
  if(getEntryPointerToFree) {
    getEntryPointerToFree->line = line;
  }
  else {
    dict_put(pointersToFreeTable, key, entryValue);
  }

  st_value_t* getEntry = dict_get(symbolsTable, key_aux);
  if(getEntry) {
    free(key_aux);
    if(token_type == POA_IDENT || token_type == POA_LIT_STRING) {
      free(entryValue->value.s);
    }
    free(entryValue);
    getEntry->line = line;
    return getEntry;
  }
  else {
    dict_put(symbolsTable, key_aux, entryValue);
    free(key_aux);
    return entryValue;
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

/**
  * Libera os espacos de memoria ocupados pelos ponteiros da tabela de simbolos
  */
void clearSymbolsTable()
{
    //remover todas as entradas da tabela antes de libera-la
    st_value_t* entrada;
    if (!symbolsTable) return;

    int i, l;
    for (i = 0, l = symbolsTable->size; i < l; i++) {
      if (symbolsTable->data[i]) {
        if(symbolsTable->data[i]->next) {
          remove_collisions(symbolsTable->data[i]->next);
        }
        entrada = dict_get(symbolsTable, symbolsTable->data[i]->key);
        if(entrada->token_type == POA_IDENT || entrada->token_type == POA_LIT_STRING) {
          free(entrada->value.s);
        }
        free(symbolsTable->data[i]->value);
        dict_remove(symbolsTable, symbolsTable->data[i]->key);
      }
    }
    dict_free(symbolsTable);
}

/**
  * Libera os espacos de memoria ocupados pelos ponteiros da tabela de ponteiros a serem liberados
  */
void clearPointerToFreeTable()
{
    //remover todas as entradas da tabela antes de libera-la
    st_value_t* entrada;
    if (!pointersToFreeTable) return;

    int i, l;
    for (i = 0, l = pointersToFreeTable->size; i < l; i++) {
      if (pointersToFreeTable->data[i]) {
        if(pointersToFreeTable->data[i]->next) {
          remove_collisions_pointer_to_free(pointersToFreeTable->data[i]->next);
        }
        dict_remove(pointersToFreeTable, pointersToFreeTable->data[i]->key);
      }
    }
    dict_free(pointersToFreeTable);
}

void putSomeEntries()
{

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

/**
 * Retorna o tipo AST de um nodo
 * (sempre uma das constantes em ast.h)
 * //TODO implementar de fato
 */
int getASTtype(comp_tree_t* node)
{
	return AST_PROGRAMA;
}

/**
 * Retorna o lexema de um nodo que é um lexema válido somente
 * se o tipo for um AST_IDENTIFICADOR (o lexema do
 * identificador), AST_LITERAL (o lexema do literal) ou
 * AST_FUNCAO (o lexema do identificador da função).
 * Se nao for nenhum desses, retorna NULL
 * //TODO implementar de fato
 */
char* getASTlexem(comp_tree_t* node)
{
	return NULL;
}

void generateExampleTree()
{
	//filhos da raiz
	int* a = malloc(sizeof(int));
	*a = 42;
	comp_tree_t* nodo1 = tree_make_node(a);
	tree_insert_node(abstractSyntaxTree, nodo1);

	int* b = malloc(sizeof(int));
	*b = 42;
	comp_tree_t* nodo2 = tree_make_node(b);
	tree_insert_node(abstractSyntaxTree, nodo2);

	int* c = malloc(sizeof(int));
	*c = 42;
	comp_tree_t* nodo3 = tree_make_node(c);
	tree_insert_node(abstractSyntaxTree, nodo3);

	int* d = malloc(sizeof(int));
	*d = 42;
	comp_tree_t* nodo4 = tree_make_node(d);
	tree_insert_node(abstractSyntaxTree, nodo4);


	//filhos de nodo1
	int* e = malloc(sizeof(int));
	*e = 42;
	comp_tree_t* nodo5 = tree_make_node(e);
	tree_insert_node(nodo1, nodo5);

	int* f = malloc(sizeof(int));
	*f = 42;
	comp_tree_t* nodo6 = tree_make_node(f);
	tree_insert_node(nodo1, nodo6);

	int* g = malloc(sizeof(int));
	*g = 42;
	comp_tree_t* nodo7 = tree_make_node(g);
	tree_insert_node(nodo1, nodo7);

	int* h = malloc(sizeof(int));
	*h = 42;
	comp_tree_t* nodo8 = tree_make_node(h);
	tree_insert_node(nodo1, nodo8);


	//filhos de nodo2
	int* i = malloc(sizeof(int));
	*i = 42;
	comp_tree_t* nodo9 = tree_make_node(i);
	tree_insert_node(nodo2, nodo9);

	int* j = malloc(sizeof(int));
	*j = 42;
	comp_tree_t* nodo10 = tree_make_node(j);
	tree_insert_node(nodo2, nodo10);

	int* k = malloc(sizeof(int));
	*k = 42;
	comp_tree_t* nodo11 = tree_make_node(k);
	tree_insert_node(nodo2, nodo11);

	int* l = malloc(sizeof(int));
	*l = 42;
	comp_tree_t* nodo12 = tree_make_node(l);
	tree_insert_node(nodo2, nodo12);


	//filhos de nodo3
	int* m = malloc(sizeof(int));
	*m = 42;
	comp_tree_t* nodo13 = tree_make_node(m);
	tree_insert_node(nodo3, nodo13);

	int* n = malloc(sizeof(int));
	*n = 42;
	comp_tree_t* nodo14 = tree_make_node(n);
	tree_insert_node(nodo3, nodo14);

	int* o = malloc(sizeof(int));
	*o = 42;
	comp_tree_t* nodo15 = tree_make_node(o);
	tree_insert_node(nodo3, nodo15);

	int* p = malloc(sizeof(int));
	*p = 42;
	comp_tree_t* nodo16 = tree_make_node(p);
	tree_insert_node(nodo3, nodo16);
}

/**
 * Percorre filhos do nodo,
 * declarando, conectando e fazendo recursao em cada um
 * @param pai nodo considerado pai no nivel atual de recursao
 */
void putToGraphviz(comp_tree_t *pai)
{
	if (pai == NULL) return;

	//percorre filhos do nodo
	comp_tree_t* filho = pai->first;
	for (int i = 0; i < pai->childnodes; ++i) {
		if (filho != NULL) {
			//declara filho no arquivo
			gv_declare(getASTtype(filho), filho, getASTlexem(filho));
			//conecta pai e filho
			gv_connect(pai, filho);

			//recursao sobre o filho
			putToGraphviz(filho);
		} else return;

		filho = filho->next;
	}
}

/**
 * Percorre filhos do nodo,
 * liberando campo value e fazendo recursao em cada um
 * @param pai nodo considerado pai no nivel atual de recursao
 */
void freeValue(comp_tree_t* pai)
{
	if (pai == NULL) return;

	//percorre filhos do nodo
	comp_tree_t* filho = pai->first;
	for (int i = 0; i < pai->childnodes; ++i) {
		if (filho != NULL) {

			if (filho->value != NULL)
				free(filho->value);

			//recursao sobre o filho
			freeValue(filho);
		} else return;

		filho = filho->next;
	}
}

/**
 * Libera values dos nodos da AST recursivamente
 * e depois libera a arvore
 */
void clearAndFreeAST()
{
	if (abstractSyntaxTree->value != NULL)
		free(abstractSyntaxTree->value);
	freeValue(abstractSyntaxTree);
	tree_free(abstractSyntaxTree);
}

void main_init (int argc, char **argv)
{
  //implemente esta função com rotinas de inicialização, se necessário
  lineNumber = 1;
  pointersToFreeTable = dict_new();
  symbolsTable = dict_new();

	abstractSyntaxTree = tree_new();
	gv_init(GRAPHVIZ_FILENAME);
	gv_declare(AST_PROGRAMA, abstractSyntaxTree, NULL);
	generateExampleTree();
}

void main_finalize (void)
{
  //implemente esta função com rotinas de finalização, se necessário


  //comp_print_table();
  clearSymbolsTable();

	putToGraphviz(abstractSyntaxTree);
	gv_close();
	clearAndFreeAST();
  clearPointerToFreeTable();
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
      cc_dict_etapa_2_print_entrada(symbolsTable->data[i]->key, entrada->line, entrada->token_type);
    }
  }
}
