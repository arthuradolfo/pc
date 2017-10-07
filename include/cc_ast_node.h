#ifndef __AST_NODE_H
#define __AST_NODE_H

#include "cc_dict.h"
#include <stdlib.h>

/**
 * Tipos de valores de nodos de ast
 */
typedef struct ast_node_value {

  /**
   * Uma das constantes de cc_ast.h
   */
  int type;
  comp_dict_t* symbols_table_entry;

} ast_node_value_t;

/**
 * Construtor para ast_node_value_t
 */
ast_node_value_t* new_ast_node_value(int type, comp_dict_t* symbols_table_entry);

#endif
