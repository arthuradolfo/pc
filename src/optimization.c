/*
 * Módulo de otimização de janela
 * Modos: //TODO definir e explicar
 *
 * Compilação para TESTES EXEMPLO: (onde X é o modo de otimização)
 * pc/build$ cd .. && rm -R build && mkdir build && cd build && cmake .. -DOX=1 -DOPTM_TST=1 && make
 * Execução: (onde Y é o tamanho da janela de otimização)
 * pc/build$ ./main Y
 *
 * Compilação normal usando otimização: (onde X é o modo de otimização)
 * pc/build$ cd .. && rm -R build && mkdir build && cd build && cmake .. -DOX=1 && make
 * Execução: (onde Y é o tamanho da janela de otimização)
 * pc/build$ ./main [path do .poa] Y
 *
 * OBS1: se não for especificado um modo de otimização, será usado O0 (sem otimização)
 * OBS2: se não for especificado um tamanho de janela, será usado 2 (tamanho padrão)
 */

#include <stdio.h>
#include <stdlib.h>
#include "optimization.h"

window_t* new_window(tac_t* top, tac_t* bottom) {
  window_t* win = malloc(sizeof(window_t));
  win->top = top;
  win->bottom = bottom;
  return win;
}

optimizer_t* new_optimizer(stack_t* tac_stack) {
  optimizer_t* opt = malloc(sizeof(optimizer_t));
  opt->tac_stack = tac_stack;

  //achar top
  tac_t* top; tac_t* bottom;
  stack_item_t* item = tac_stack->data;
  if (item) {
    top = item->value;
    if (!top) {
      printf("Impossible top: No tac_stack->data->value\n");
      exit(EXIT_FAILURE);
    }
  }
  else {
    printf("Impossible top: No tac_stack->data\n");
    exit(EXIT_FAILURE);
  }

  //achar bottom
  int i = 0;
  item = tac_stack->data;
  while (i < window_size && item) {
    item = item->next;
    i++;
  }
  if (item) {
    bottom = item->value;
    if (!bottom) {
      printf("Impossible bottom: No item->value\n");
      exit(EXIT_FAILURE);
    }
  }
  else {
    printf("Impossible bottom: No item\n");
    exit(EXIT_FAILURE);
  }

  opt->win = new_window(top, bottom);
  return opt;
}

void clear_and_free_optimizer(optimizer_t* opt) {
  clear_tac_stack(&opt->tac_stack);
  free_stack(opt->tac_stack);
  free(opt->win);
  free(opt);
}

void optimization_module_init(int argc, char** argv) {
  int expected_min_argc = 3;
  int expected_argv_index = 2;

  #ifdef OPTM_TST
    expected_min_argc = 2;
    expected_argv_index = 1;
  #endif

  if (argc >= expected_min_argc) {
    window_size = atoi(argv[expected_argv_index]);
    if (window_size <= 0) { //janela pode ser de tamanho 1 ou maior
      window_size = STD_WINDOW_SIZE;
    }
  } else {
    window_size = STD_WINDOW_SIZE;
  }
}

void print_optimization_mode() {
  printf("%s", optimization_mode_to_string());
}

char* optimization_mode_to_string() {
  #ifdef O0
    return "O0";
  #endif
  #ifdef O1
    return "O1";
  #endif
  #ifdef O2
    return "O2";
  #endif
}

void run_optimization_tests() {
  printf("******** Optimization Tests %s [window size = %d] ********\n\n", optimization_mode_to_string(), window_size);
  //TODO chamar métodos de teste
  example_feature_test();
}

/*
 * void template_feature_test() {
 *    print código input
 *    otimizar (chamar metodo da feature)
 *    print código output
 * }
 */

void example_feature_test() {
  //print código input
  printf("~~~~~~~~~~~~ Input ILOC ~~~~~~~~~~~~\n");
  stack_t* tac_stack = new_stack();
  tac_t* add = new_tac_ssed(true, NULL, OP_ADD, NULL, NULL, NULL);
  tac_t* sub = new_tac_ssed(true, NULL, OP_SUB, NULL, NULL, NULL);
  tac_t* mul = new_tac_ssed(true, NULL, OP_MULT, NULL, NULL, NULL);
  tac_t* div = new_tac_ssed(true, NULL, OP_DIV, NULL, NULL, NULL);
  stack_push(add, tac_stack);
  stack_push(sub, tac_stack);
  stack_push(mul, tac_stack);
  stack_push(div, tac_stack);
  iloc_to_stdout(tac_stack);

  //otimizar (chamar metodo da feature)
  printf("\nOptimizing...\n\n");
  optimizer_t* opt = new_optimizer(tac_stack);

  //print código output
  printf("~~~~~~~~~~~~ Output ILOC ~~~~~~~~~~~~\n");
  iloc_to_stdout(opt->tac_stack);

  clear_and_free_optimizer(opt);
}