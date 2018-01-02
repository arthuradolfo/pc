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
}

/*
 * void template_feature_test() {
 *    print código input
 *    otimizar (chamar metodo da feature)
 *    print código output
 * }
 */