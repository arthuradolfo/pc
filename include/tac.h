/**
 * Arquivo com funções de tratamento de TAC (three adresses code)
 */

#ifndef TAC_H
#define TAC_H

#include "syntax_tree.h"

int label_counter;
int register_counter;

/* Registradores de base */
#define RBSS 0
#define RARP 1

/* Opcodes */

//aritmetica
#define OP_NOP 0
#define OP_ADD 1
#define OP_SUB 2
#define OP_MULT 3
#define OP_DIV 4
#define OP_ADD_I 5
#define OP_SUB_I 6
#define OP_RSUB_I 7
#define OP_MULT_I 8
#define OP_DIV_I 9
#define OP_RDIV_I 10

//shifts
#define OP_LSHIFT 11
#define OP_LSHIFT_I 12
#define OP_RSHIFT 13
#define OP_RSHIFT_I 14

//logicos
#define OP_AND 15
#define OP_AND_I 16
#define OP_OR 17
#define OP_OR_I 18
#define OP_XOR 19
#define OP_XOR_I 20

//memoria - leitura
#define OP_LOAD 21
#define OP_LOAD_AI 22
#define OP_LOAD_A0 23
#define OP_CLOAD 24
#define OP_CLOAD_AI 25
#define OP_CLOAD_A0 26
#define OP_LOAD_I 27

//memoria - escrita
#define OP_STORE 28
#define OP_STORE_AI 29
#define OP_STORE_A0 30
#define OP_CSTORE 31
#define OP_CSTORE_AI 32
#define OP_CSTORE_A0 33

//copia entre registradores
#define OP_I2I 34
#define OP_C2C 35
#define OP_C2I 36
#define OP_I2C 37

//controle de fluxo
#define OP_CMP_LT 38
#define OP_CMP_LE 39
#define OP_CMP_EQ 40
#define OP_CMP_GE 41
#define OP_CMP_GT 42
#define OP_CMP_NE 43
#define OP_CBR 44

//saltos
#define OP_JUMP_I 45
#define OP_JUMP 46

typedef struct tac
{
  /**
   * Se não NULL, é o label que imediatamente precede a operacao
   */
  char* label;

  /**
   * Uma das constantes de opcode
   */
  int opcode;

  /**
   * Primeira fonte (se != NULL)
   */
  char* src_1;

  /**
   * Segunda fonte (se != NULL)
   */
  char* src_2;

  /**
   * Primeiro alvo (se != NULL)
   */
  char* dst_1;

  /**
   * Segundo alvo (se != NULL)
   */
  char* dst_2;

} tac_t;

/**
 * Inicializa um tac_t e retorna um ponteiro pra ele
 */
tac_t* new_tac(char* label, int opcode, char* src_1, char* src_2, char* dst_1, char* dst_2);

/**
 * Libera toda memoria alocada de um tac_t
 */
void destroy_tac(tac_t* tac);

//construtores práticos, alocam e liberam registradores, imediatos e labels se necessario

/**
 * Uso em tacs do tipo r1, r2 => r3 (RegisterRegisterEqualsRegister)
 * @param use_label se chamador quer usar label na operacao
 * @param label se use_label é true, usa essa label (se essa label for NULL, cria nova label)
 * @param opcode código de operacao, deve ser um que corresponda ao padrao de uso da funcao
 * @param src_1 r1
 * @param src_2 r2
 * @param dst r3
 * @return tac alocado
 */
tac_t* new_tac_ssed(bool use_label, char* label, int opcode, char* src_1, char* src_2, char* dst);
/**
 * Uso em tacs do tipo i => r (ImediateEqualsRegister)
 * @param use_label se chamador quer usar label na operacao
 * @param label se use_label é true, usa essa label (se essa label for NULL, cria nova label)
 * @param opcode código de operacao, deve ser um que corresponda ao padrao de uso da funcao
 * @param cnst i (uma string)
 * @param dst r
 * @return tac alocado
 */
tac_t* new_tac_sed(bool use_label, char* label, int opcode, char* imed, char* dst);
/**
 * Uso em tacs do tipo r1 => r2, r3 (RegisterEqualsRegisterRegister)
 * @param use_label se chamador quer usar label na operacao
 * @param label se use_label é true, usa essa label (se essa label for NULL, cria nova label)
 * @param opcode código de operacao, deve ser um que corresponda ao padrao de uso da funcao
 * @param src r1
 * @param dst_1 r2
 * @param dst_2 r3
 * @return tac alocado
 */
tac_t* new_tac_sedd(bool use_label, char* label, int opcode, char* src, char* dst_1, char* dst_2);
/**
 * Uso em tacs do tipo cmp_x r1, r2 -> r3
 * @param use_label se chamador quer usar label na operacao
 * @param label se use_label é true, usa essa label (se essa label for NULL, cria nova label)
 * @param opcode código de operacao, deve ser um que corresponda ao padrao de uso da funcao
 * @param src_1 r1
 * @param src_2 r3
 * @param dst r3
 * @return
 */
tac_t* new_tac_jump_i(bool use_label, char* label, char* dst_label);
tac_t* new_tac_jump(bool use_label, char* label, char* dst_reg);
tac_t* new_tac_cbr  (bool use_label, char* label, char* src, char* lbl_true, char* lbl_false);

/**
 * Retorna uma copia do tac fornecido por parametro
 */
tac_t* copy_tac(tac_t* copied);

/**
 * Retorna o nome do registrador passado por parametro
 * @param base_register deve ser RBSS ou RARP
 */
char* base_register_name(int base_register);

/**
 * Retorna um nome de rótulo novo
 */
char* new_label();

/**
 * Retorna um nome de registrador novo
 */
char* new_register();

/**
 * Retorna uma string representando uma constante
 */
char* new_imediate(int constant);

/**
 * Transforma um tac_t em string (o codigo em si)
 */
char* tac_to_string(tac_t *tac);

//testes

void create_and_destroy_tac_test();

void imediates_test();

void registers_labels_test();

void tac_to_string_test();

void tac_basic_tests();

void new_tac_ssed_test();
void new_tac_sed_test();
void new_tac_sedd_test();
void new_tac_jump_test();
void new_tac_jump_i_test();
void new_tac_cbr_test();
void custom_constructors_tests();

/**************** TAC STACK ****************/

/**
 * Imprime na tela uma pilha de tacs (do fundo para o topo)
 */
void print_tac_stack(stack_t** stack);

/**
 * Imprime na tela uma pilha de tacs (do fundo para o topo) sem os identificadores de fundo e topo
 */
void print_tac_stack_clean(stack_t** stack);

/**
 * Retorna uma pilha que é a concatenacao das duas pilhas fornecidas por parametro
 */
stack_t* cat_stacks(stack_t** stack_1, stack_t** stack_2);

/**
 * Destroi os tacs de um pilha (em data->value)
 */
void clear_tac_stack(stack_t** stack);

void tac_stack_test();
void tac_stack_test_2();
void tac_stack_test_3();
void reversed_stack_test();

/**
 * Retorna uma pilha que é a mesma que a fornecida, porem invertida
 */
stack_t* reversed_tac_stack(stack_t* stack);

/**
 * Pusha todos os tacs de uma pilha para outra
 * @param dst a pilha que recebe os push
 * @param pushed a pilha cujos tacs sao pushados para a outra
 */
void stack_push_all_tacs(stack_t* dst, stack_t* pushed);

char* new_hole();

/**
 * Remenda os buracos com o label fornecido
 * @param buracos ponteiro para uma pilha de ponteiros para ponteiros de char (stack_t** de char**)
 * @param label o que deve ser usado para tapar os buracos
 */
void remenda(stack_t** buracos, char* label);

void remenda_test();

bool has_holes_to_patch(ast_node_value_t* ast_node);
int opcode_from_operator(ast_node_value_t* operator);
bool is_relop(int opcode);
bool is_logic(int opcode);
bool is_arit(int opcode);
bool is_or(int opcode);
bool is_and(int opcode);

void generate_code_load_var(ast_node_value_t *variable);
void generate_code_load_literal_int(ast_node_value_t *literal);
void generate_code_load_literal_bool(ast_node_value_t *literal);
void generate_code_expression(ast_node_value_t* expression, ast_node_value_t* operand_1, ast_node_value_t* operator, ast_node_value_t* operand_2);
void generate_code_if(ast_node_value_t* cabeca, ast_node_value_t* condicao, ast_node_value_t* codigo);
void generate_code_if_else(ast_node_value_t* cabeca, ast_node_value_t* condicao, ast_node_value_t* codigo_true, ast_node_value_t* codigo_false);
void generate_code_attribution_var(ast_node_value_t* var, ast_node_value_t* expression);
void generate_code_unary_op(ast_node_value_t *cabeca, ast_node_value_t *unary_op, ast_node_value_t *expressao);
void generate_code_while(ast_node_value_t *cabeca, ast_node_value_t *condicao, ast_node_value_t *codigo);
void generate_code_do_while(ast_node_value_t *cabeca, ast_node_value_t *condicao, ast_node_value_t *codigo);

/**
 * Imprime uma pilha de tacs (invertida) na saida padrao
 */
void iloc_to_stdout(stack_t* tac_stack);

#endif
