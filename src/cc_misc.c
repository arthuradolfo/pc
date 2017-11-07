#include "cc_misc.h"
#include "cc_dict.h"

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

void set_ast_root(comp_tree_t* root)
{
  abstractSyntaxTree = root;
}

comp_tree_t* get_ast_root()
{
  return abstractSyntaxTree;
}

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
        entryValue->value.b = true;
      }
      else {
        entryValue->value.b = false;
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
  if (!symbolsTable) return NULL;


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
 */
int getASTtype(comp_tree_t* node)
{
  ast_node_value_t* value = (ast_node_value_t*) node->value;

  if (value != NULL)
    return value->syntactic_type;
  else
    return NULL;
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
  ast_node_value_t* value = (ast_node_value_t*) node->value;
  char *string_aux = malloc(sizeof(char)*200);
  if (value == NULL) return NULL;

  switch (value->syntactic_type) {
    case AST_FUNCAO:
      free(string_aux);
      return value->symbols_table_entry->value.s;
    case AST_LITERAL:
      switch(value->symbols_table_entry->token_type) {
        case POA_LIT_INT:
          sprintf(string_aux, "%d", value->symbols_table_entry->value.i);
          return string_aux;

        case POA_LIT_FLOAT:
          sprintf(string_aux, "%f", value->symbols_table_entry->value.f);
          return string_aux;

        case POA_LIT_CHAR:
          sprintf(string_aux, "%c", value->symbols_table_entry->value.c);
          return string_aux;

        case POA_LIT_STRING:
          sprintf(string_aux, "%s", value->symbols_table_entry->value.s);
          return string_aux;

        case POA_LIT_BOOL:
          if(value->symbols_table_entry->value.b) {
            sprintf(string_aux, "%s", "true");
            return string_aux;
          }
          else {
            sprintf(string_aux, "%s", "false");
            return string_aux;
          }

      }
    case AST_IDENTIFICADOR:
      free(string_aux);
      return value->symbols_table_entry->value.s;

    default:
      free(string_aux);
      return NULL;
  }
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
  char *string;
	for (int i = 0; i < pai->childnodes; ++i) {
		if (filho != NULL) {
      string = getASTlexem(filho);
			//declara filho no arquivo
			gv_declare(getASTtype(filho), filho, string);
      if(getASTtype(filho) == AST_LITERAL) free(string);
      //free(lexem);
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

/**
 * Libera values dos nodos da AST recursivamente
 * e depois libera a arvore
 */
void destroyAST(comp_tree_t* ast)
{
  if (ast->value != NULL)
    free(ast->value);
  freeValue(ast);
  tree_free(ast);
}

void main_init (int argc, char **argv)
{
  //implemente esta função com rotinas de inicialização, se necessário
  lineNumber = 1;
  pointersToFreeTable = dict_new();
  symbolsTable = dict_new();

	//abstractSyntaxTree = tree_new();
	//gv_init(GRAPHVIZ_FILENAME);
	//generateExampleTree();
}

void main_finalize (void)
{
  //implemente esta função com rotinas de finalização, se necessário


  //comp_print_table();

  //printf("Building .dot ...\n");
  //gv_declare(AST_PROGRAMA, abstractSyntaxTree, NULL);
  //putToGraphviz(abstractSyntaxTree);
	//gv_close();
  clearSymbolsTable();
  //printf("Clearing AST ...\n");
	clearAndFreeAST();
  //printf("Clearing pointersToFreeTable ...\n");
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



/* -------------------------------------------------------------------------- */
/* ---------------------------------  AST ----------------------------------  */
/* -------------------------------------------------------------------------- */

ast_node_value_t* new_ast_node_value(int syntactic_type, int semantic_type, char* semantic_user_type, st_value_t* symbols_table_entry) {
  ast_node_value_t* node = (ast_node_value_t*) malloc(sizeof(ast_node_value_t));
  node->syntactic_type = syntactic_type;
  node->semantic_type = semantic_type;
  node->semantic_user_type = semantic_user_type;
  node->symbols_table_entry = symbols_table_entry;
  return node;
}



/* -------------------------------------------------------------------------- */
/* ------------------------------- semantics -------------------------------  */
/* -------------------------------------------------------------------------- */

void print_semantic_type(int semantic_type)
{
  switch (semantic_type)
  {
    case SMTC_VOID: printf("void "); break;
    case SMTC_INT: printf("int "); break;
    case SMTC_FLOAT: printf("float "); break;
    case SMTC_CHAR: printf("char "); break;
    case SMTC_STRING: printf("string "); break;
    case SMTC_BOOL: printf("bool "); break;
  }
}

void print_semantic_type_ln(int semantic_type)
{
  switch (semantic_type)
  {
    case SMTC_VOID: printf("void\n"); break;
    case SMTC_INT: printf("int\n"); break;
    case SMTC_FLOAT: printf("float\n"); break;
    case SMTC_CHAR: printf("char\n"); break;
    case SMTC_STRING: printf("string\n"); break;
    case SMTC_BOOL: printf("bool\n"); break;
  }
}

int check_coercion_needed(int first_type, int second_type)
{
  if (first_type == second_type) return SMTC_SUCCESS;

  if ((first_type == SMTC_FLOAT && second_type == SMTC_INT) || (first_type == SMTC_INT && second_type == SMTC_FLOAT))
  {
    return SMTC_FLOAT;
  }
  if ((first_type == SMTC_BOOL && second_type == SMTC_INT) || (first_type == SMTC_INT && second_type == SMTC_BOOL))
  {
    return SMTC_INT;
  }
  if ((first_type == SMTC_FLOAT && second_type == SMTC_BOOL) || (first_type == SMTC_BOOL && second_type == SMTC_FLOAT))
  {
    return SMTC_FLOAT;
  }

  //tipos incompatives

  if (first_type == SMTC_CHAR || second_type == SMTC_CHAR)
  {
    printf("[ERRO SEMANTICO] [Linha %d] Coercao impossivel do tipo char : ", lineNumber);
    print_semantic_type(first_type); printf("e ");
    print_semantic_type_ln(second_type);
    exit(SMTC_ERROR_CHAR_TO_X);
  }
  if (first_type == SMTC_STRING || second_type == SMTC_STRING)
  {
    printf("[ERRO SEMANTICO] [Linha %d] Coercao impossivel do tipo string : ", lineNumber);
    print_semantic_type(first_type); printf("e ");
    print_semantic_type_ln(second_type);
    exit(SMTC_ERROR_STRING_TO_X);
  }
}

int get_type_size(int semantic_type)
{
  switch (semantic_type)
  {
    default:
    case SMTC_VOID: return SMTC_VOID_SIZE;
    case SMTC_INT: return SMTC_INT_SIZE;
    case SMTC_FLOAT: return SMTC_FLOAT_SIZE;
    case SMTC_CHAR: return SMTC_CHAR_SIZE;
    case SMTC_BOOL: return SMTC_BOOL_SIZE;
  }
}

void set_st_semantic_type_and_size_primitive(int semantic_type, st_value_t* symbols_table_entry)
{
	//associa tipo semantico na tabela de simbolos
	symbols_table_entry->semantic_type = semantic_type;
	//associa tamanho na tabela de simbolos
	symbols_table_entry->size = get_type_size(semantic_type);
}

void set_st_semantic_type_and_size_vector(int semantic_type, int length, st_value_t* symbols_table_entry)
{
  //associa tipo semantico na tabela de simbolos
	symbols_table_entry->semantic_type = get_semantic_type_vector_from_element(semantic_type);
	//associa tamanho na tabela de simbolos
	symbols_table_entry->size = get_type_size(semantic_type) * length;
}

int get_semantic_type_of_indexed_vector(int vector_semantic_type)
{
  switch (vector_semantic_type)
  {
    default:
    case SMTC_INT_VECTOR: return SMTC_INT;
    case SMTC_FLOAT_VECTOR: return SMTC_FLOAT;
    case SMTC_CHAR_VECTOR: return SMTC_CHAR;
    case SMTC_STRING_VECTOR: return SMTC_STRING;
    case SMTC_BOOL_VECTOR: return SMTC_BOOL;
    case SMTC_USER_TYPE_VECTOR: return SMTC_USER_TYPE_VAR;
  }
}

int get_semantic_type_vector_from_element(int vector_semantic_type)
{
  switch (vector_semantic_type)
  {
    default:
    case SMTC_INT: return SMTC_INT_VECTOR;
    case SMTC_FLOAT: return SMTC_FLOAT_VECTOR;
    case SMTC_CHAR: return SMTC_CHAR_VECTOR;
    case SMTC_STRING: return SMTC_STRING_VECTOR;
    case SMTC_BOOL: return SMTC_BOOL_VECTOR;
    case SMTC_USER_TYPE_VAR: return SMTC_USER_TYPE_VECTOR;
  }
}

void set_st_semantic_type_and_size_user_type(st_value_t* type_entry, st_value_t* variable_entry)
{
  variable_entry->semantic_type = SMTC_USER_TYPE_VAR;
  variable_entry->semantic_user_type = type_entry->value.s;
  variable_entry->size = type_entry->size;
}

void set_st_semantic_type_and_size_vector_user_type(st_value_t* type_entry, st_value_t* variable_entry, int length)
{
  variable_entry->semantic_type = SMTC_USER_TYPE_VECTOR;
  variable_entry->semantic_user_type = type_entry->value.s;
  variable_entry->size = type_entry->size * length;
}

void verify_shiftable(st_value_t* symbols_table_entry)
{
  if (symbols_table_entry->semantic_type != SMTC_INT) {
    printf("[ERRO SEMANTICO] [Linha %d] Tipo de identificador incorreto : ", lineNumber);
    print_semantic_type(symbols_table_entry->semantic_type);
    printf("deveria ser "); print_semantic_type_ln(SMTC_INT);
    exit(SMTC_ERROR_WRONG_TYPE);
  }
}

void verify_index(ast_node_value_t* ast_index)
{
  if (ast_index->semantic_type == SMTC_INT) return;
  if (ast_index->semantic_type == SMTC_BOOL)
  {
    mark_coercion(SMTC_INT, ast_index);
    return;
  }

  printf("[ERRO SEMANTICO] [Linha %d] Tipo incompativel para indice de vetor : ", lineNumber);
  print_semantic_type(ast_index->semantic_type);
  printf(". Use int ou bool\n");
  exit(SMTC_ERROR_STRING_TO_X);
}

void mark_coercion(int semantic_type, ast_node_value_t* ast_to_coerce)
{
  //TODO indicar que ast deve sofrer coercao
}
