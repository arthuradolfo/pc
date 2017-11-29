#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include "symbols_table.h"
#include "cc_tree.h"
#include "cc_dict.h"

#define GRAPHVIZ_FILENAME "graphvizAST.dot"

comp_tree_t* abstractSyntaxTree;

/**
 * Tipos de valores de nodos de ast
 */
typedef struct ast_node_value {

  /**
   * Uma das constantes de cc_ast.h
   */
  int syntactic_type;

  /**
   * Uma das constantes de tipo de semantic.h
   */
  int semantic_type;

  /**
   * Quando semantic_type for IKS_USER_TYPE_VAR,
   * esse campo tem o nome do tipo de usuario.
   * Senão, deve ser NULL.
   */
   char* semantic_user_type;

	 /**
	  * Diferente de SMTC_NO_COERCION quando é necessaria coercao
		*/
	 int coercion;

	 /**
	  * Marca que é parâmetro válido de um input
		*/
	 bool inputable;

	 /**
	  * Marca que é parâmetro válido de um output
		*/
	 bool outputable;

	 /**
	  * Um ponteiro para uma tabela de simbolos caso o nodo seja uma funcao, um bloco ou similar
		*/
	 comp_dict_t* symbols_table;

   struct symbolsTable_value* symbols_table_entry;

} ast_node_value_t;

/**
 * Construtor para ast_node_value_t
 */
ast_node_value_t* new_ast_node_value(int syntactic_type, int semantic_type, char* semantic_user_type, struct symbolsTable_value* symbols_table_entry);

void set_ast_root(comp_tree_t* root);

comp_tree_t* get_ast_root();

void putToGraphviz(comp_tree_t *pai);

void clearAndFreeAST();

void destroyAST(comp_tree_t* ast);

/**
 * Retorna o tipo AST de um nodo
 * (sempre uma das constantes em ast.h)
 */
int getASTtype(comp_tree_t* node);

/**
 * Percorre filhos do nodo,
 * liberando campos value e fazendo recursao em cada um
 * @param pai nodo considerado pai no nivel atual de recursao
 */
void freeValuesOfChilds(comp_tree_t* pai);

#endif
