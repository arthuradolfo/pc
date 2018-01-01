/*
 * Módulo de otimização
 * Modos: //TODO explicar
 */

#include <stdio.h>
#include "optimization.h"

void print_optimization_mode() {
  #ifdef O0
    printf("O0\n");
  #endif
  #ifdef O1
    printf("O1\n");
  #endif
  #ifdef O2
    printf("O2\n");
  #endif
}
