#ifndef EXECUTION_H
#define EXECUTION_H

/*
    Ordem dos campos em um registro de ativação:

    [rarp] ======== Campos de tamanho fixo (4*4=16) ========
      Estado da máquina (rsp anterior) [size 4]
      Endereço de retorno (relacionado a rpc) [size 4]
      Vínculo estático (0 sempre) [size 4]
      Vínculo dinâmico (rarp anterior) [size 4]

    [rarp+16] ===== Campos de tamanho variável ===
      [DEFINIDO NA DECLARACAO] Parâmetros formais (argumentos)
      Variáveis locais
      [DEFINIDO NA DECLARACAO] Valor retornado
*/

typedef struct {
  int formal_params_size;
  int local_vars_size;
  int return_size;
} func_def_t;

/**
 * Variável global usada no parser.y para construir func_def_t s e colocar na árvore de símbolos
 */
func_def_t* current_func_def_sizes;

func_def_t* new_func_def();
int func_def_size(func_def_t* func_def);
void print_func_def(func_def_t* func_def);

//TODO move to tac.h
//void generate_code_start_exec(ast_node_value_t* program);
//void generate_code_func_def(ast_node_value_t* func_def);
//void generate_code_func_call(ast_node_value_t* func_call);


#endif
