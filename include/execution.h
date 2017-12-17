#ifndef EXECUTION_H
#define EXECUTION_H

/*
    Ordem dos campos em um registro de ativação:
    Parâmetros formais (argumentos)
    Variáveis locais
    ======== Campos de tamanho fixo     ========
    Estado da máquina
    Vínculo estático
    Vínculo dinâmico
    Endereço de retorno
    ======== Campos de tamanho variável ========
    Valor retornado
    Temporários (caso necessário)
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
int proto_actv_rec_size(func_def_t* func_def);
void print_func_def(func_def_t* func_def);

//TODO move to tac.h
//void generate_code_start_exec(ast_node_value_t* program);
//void generate_code_func_def(ast_node_value_t* func_def);
//void generate_code_func_call(ast_node_value_t* func_call);


#endif
