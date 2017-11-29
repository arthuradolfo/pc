#include "syntax_tree.h"
#include "cc_ast.h"
#include "main.h"
#include "semantics.h"
#include <stdlib.h>

void set_ast_root(comp_tree_t* root)
{
  abstractSyntaxTree = root;
}

comp_tree_t* get_ast_root()
{
  return abstractSyntaxTree;
}

ast_node_value_t* new_ast_node_value(int syntactic_type, int semantic_type, char* semantic_user_type, st_value_t* symbols_table_entry) {

  ast_node_value_t* node = (ast_node_value_t*) malloc(sizeof(ast_node_value_t));
  node->syntactic_type = syntactic_type;
  node->semantic_type = semantic_type;
  node->semantic_user_type = semantic_user_type;
  node->symbols_table_entry = symbols_table_entry;
  node->coercion = SMTC_NO_COERCION;

  node->inputable = false;
  node->outputable = false;

  node->symbols_table = NULL;
  return node;
}

/**
 * Libera values dos nodos da AST recursivamente
 * e depois libera a arvore
 */
void clearAndFreeAST()
{
  if (abstractSyntaxTree) {
    if (abstractSyntaxTree->value != NULL)
      free(abstractSyntaxTree->value);
    freeValuesOfChilds(abstractSyntaxTree);
    tree_free(abstractSyntaxTree);
  }
}

/**
 * Libera values dos nodos da AST recursivamente
 * e depois libera a arvore
 */
void destroyAST(comp_tree_t* ast)
{
  if (ast) {
    if (ast->value != NULL)
      free(ast->value);
    freeValuesOfChilds(ast);
    tree_free(ast);
  }
}

int getASTtype(comp_tree_t* node)
{
  ast_node_value_t* value = (ast_node_value_t*) node->value;

  if (value != NULL)
    return value->syntactic_type;
  else
    return -1;
}

/**
 * Retorna o lexema de um nodo que é um lexema válido somente
 * se o tipo for um AST_IDENTIFICADOR (o lexema do
 * identificador), AST_LITERAL (o lexema do literal) ou
 * AST_FUNCAO (o lexema do identificador da função).
 * Se nao for nenhum desses, retorna NULL
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

void freeValuesOfChilds(comp_tree_t* pai)
{
  if (pai == NULL) return;

  //percorre filhos do nodo
  comp_tree_t* filho = pai->first;
  for (int i = 0; i < pai->childnodes; ++i) {
    if (filho != NULL) {

      ast_node_value_t* filho_ast = filho->value;

      if (filho_ast != NULL) {

        if (filho_ast->semantic_user_type != NULL)
          free(filho_ast->semantic_user_type);

        if (filho_ast->symbols_table != NULL)
          clearGeneralST(filho_ast->symbols_table);

        free(filho->value);
      }

      //recursao sobre o filho
      freeValuesOfChilds(filho);
    } else return;

    filho = filho->next;
  }
}
