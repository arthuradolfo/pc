/**
 * Arquivo com funções de tratamento de TAC (three adresses code)
 */

#ifndef TAC_H
#define TAC_H

int label_counter;
int register_counter;

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

/**
 * Retorna uma copia do tac fornecido por parametro
 */
tac_t* copy_tac(tac_t* copied);

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

/**************** TAC STACK ****************/

/**
 * Imprime na tela uma pilha de tacs (do fundo para o topo)
 */
void print_tac_stack(stack_t** stack);

/**
 * Retorna uma pilha que é a concatenacao das duas pilhas fornecidas por parametro
 */
stack_t* cat_stacks(stack_t** stack_1, stack_t** stack_2);

/**
 * Destroi os tacs de um pilha (em data->value)
 */
void clear_tac_stack(stack_t** stack);

void tac_stack_test();

#endif
