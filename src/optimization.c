/*
 * Módulo de otimização
 * Modos: //TODO definir e explicar
 *
 * Compilação para TESTES EXEMPLO: (onde X é o modo de otimização)
 * pc/build$ cd .. && rm -R build && mkdir build && cd build && cmake .. -DOX=1 -DOPTM_TST=1 && make
 *
 * Compilação normal usando otimização: (onde X é o modo de otimização)
 * pc/build$ cd .. && rm -R build && mkdir build && cd build && cmake .. -DOX=1 && make
 */

#include <stdio.h>
#include "optimization.h"

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
  printf("******** Optimization Tests %s ********\n\n", optimization_mode_to_string());
  //TODO chamar métodos de teste
}

/*
 * void template_feature_test() {
 *    print código input
 *    otimizar (chamar metodo da feature)
 *    print código output
 * }
 */