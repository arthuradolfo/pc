#include "cc_ast_node.h"

ast_node_value_t* new_ast_node_value(int type, st_value_t* symbols_table_entry) {
  ast_node_value_t* node = (ast_node_value_t*) malloc(sizeof(ast_node_value_t));
  node->type = type;
  node->symbols_table_entry = symbols_table_entry;
  return node;
}
