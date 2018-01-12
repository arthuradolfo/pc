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

window_t* new_window(stack_item_t* top, stack_item_t* bottom) {
  window_t* win = malloc(sizeof(window_t));
  win->top = top;
  win->bottom = bottom;
  return win;
}

optimizer_t* new_optimizer(stack_t* tac_stack) {
  optimizer_t* opt = malloc(sizeof(optimizer_t));
  opt->tac_stack = tac_stack;

  //achar top
  stack_item_t* top; stack_item_t* bottom;
  stack_item_t* item = tac_stack->data;
  if (item) {
    while(item->next) {
      item = item->next;
    }
    top = item;
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
  while(item->next) {
    item = item->next;
  }
  while (i < window_size-1 && item) {
    item = item->prev;
    i++;
  }
  if (item) {
    bottom = item;
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
  int expected_min_argc = 5;
  int expected_argv_index = 2;

  if (argc >= expected_min_argc) {
    window_size = atoi(argv[expected_argv_index]);
    if (window_size <= 0) { //janela pode ser de tamanho 1 ou maior
      window_size = STD_WINDOW_SIZE;
    }
  } else {
    window_size = STD_WINDOW_SIZE;
  }
}

void eliminate_redundant_instruction(optimizer_t* opt) {
  window_t *win_aux = opt->win;
  stack_item_t *item_aux = win_aux->top;
  char* register_1 = NULL;
  char* register_2 = NULL;
  int delete = 0;
  int count = 0;
  while(count < window_size) {
    if(((tac_t*) item_aux->value)->opcode == OP_LOAD && delete == 0) {
      register_1 = ((tac_t*) item_aux->value)->src_1;
      register_2 = ((tac_t*) item_aux->value)->dst_1;
      delete = 1;
    }
    else {
      if(register_2 && ((tac_t*) item_aux->value)->dst_1) {
        if(strcmp(((tac_t*) item_aux->value)->dst_1, register_2) == 0) {
          delete = 0;
        }
      }
    }
    if(((tac_t*) item_aux->value)->opcode == OP_STORE && delete == 1) {
      if(strcmp(((tac_t*) item_aux->value)->src_1, register_2) == 0 && strcmp(((tac_t*) item_aux->value)->dst_1, register_1) == 0) {
        free(((tac_t*) item_aux->value)->src_1);
        free(((tac_t*) item_aux->value)->src_2);
        free(((tac_t*) item_aux->value)->dst_1);
        ((tac_t*) item_aux->value)->src_1 = NULL;
        ((tac_t*) item_aux->value)->src_2 = NULL;
        ((tac_t*) item_aux->value)->dst_1 = NULL;
        ((tac_t*) item_aux->value)->dst_2 = NULL;
        ((tac_t*) item_aux->value)->opcode = OP_NOP;
      }
    }
    item_aux = item_aux->prev;
    count++;
  }
}

void optimize_flux_control(optimizer_t* opt) {
  window_t *win_aux = opt->win;
  stack_item_t *item_aux = win_aux->top;
  stack_item_t *jump_aux;
  char* label = NULL;
  char* label_2 = NULL;
  int delete = 0;
  int count = 0;
  int free_label = 0;
  int free_label_2 = 0;
  while(count < window_size) {
    if(((tac_t*) item_aux->value)->opcode == OP_JUMP_I && delete == 0) {
      jump_aux = item_aux;
      label = ((tac_t*) item_aux->value)->dst_1;
      delete = 1;
    }
    if(((tac_t*) item_aux->value)->opcode == OP_CBR && delete == 0) {
      jump_aux = item_aux;
      label = ((tac_t*) item_aux->value)->dst_1;
      label_2 = ((tac_t*) item_aux->value)->dst_2;
      delete = 2;
    }
    if(label && ((tac_t*) item_aux->value)->label) {
      if(strcmp(((tac_t*) item_aux->value)->label, label) == 0 && delete == 1) {
        if(((tac_t*) item_aux->value)->opcode == OP_JUMP_I || ((tac_t*) item_aux->value)->opcode == OP_JUMP) {
            free_label = 1;
            ((tac_t*) jump_aux->value)->dst_1 = strdup(((tac_t*) item_aux->value)->dst_1);
            free(((tac_t*) item_aux->value)->src_1);
            free(((tac_t*) item_aux->value)->src_2);
            free(((tac_t*) item_aux->value)->dst_1);
            free(((tac_t*) item_aux->value)->dst_2);
            ((tac_t*) item_aux->value)->src_1 = NULL;
            ((tac_t*) item_aux->value)->src_2 = NULL;
            ((tac_t*) item_aux->value)->dst_1 = NULL;
            ((tac_t*) item_aux->value)->dst_2 = NULL;
            ((tac_t*) item_aux->value)->opcode = OP_NOP;
        }
      }
      else if(strcmp(((tac_t*) item_aux->value)->label, label) == 0 && delete == 2) {
        if(((tac_t*) item_aux->value)->opcode == OP_JUMP_I || ((tac_t*) item_aux->value)->opcode == OP_JUMP) {
            free_label = 1;
            ((tac_t*) jump_aux->value)->dst_1 = strdup(((tac_t*) item_aux->value)->dst_1);
            free(((tac_t*) item_aux->value)->src_1);
            free(((tac_t*) item_aux->value)->src_2);
            free(((tac_t*) item_aux->value)->dst_1);
            free(((tac_t*) item_aux->value)->dst_2);
            ((tac_t*) item_aux->value)->src_1 = NULL;
            ((tac_t*) item_aux->value)->src_2 = NULL;
            ((tac_t*) item_aux->value)->dst_1 = NULL;
            ((tac_t*) item_aux->value)->dst_2 = NULL;
            ((tac_t*) item_aux->value)->opcode = OP_NOP;
        }
      }
    }
    if(label_2 != NULL) {
      if(strcmp(((tac_t*) item_aux->value)->label, label_2) == 0 && delete == 2) {
        if(((tac_t*) item_aux->value)->opcode == OP_JUMP_I || ((tac_t*) item_aux->value)->opcode == OP_JUMP) {
            free_label_2 = 1;
            ((tac_t*) jump_aux->value)->dst_2 = strdup(((tac_t*) item_aux->value)->dst_1);
            free(((tac_t*) item_aux->value)->src_1);
            free(((tac_t*) item_aux->value)->src_2);
            free(((tac_t*) item_aux->value)->dst_1);
            free(((tac_t*) item_aux->value)->dst_2);
            ((tac_t*) item_aux->value)->src_1 = NULL;
            ((tac_t*) item_aux->value)->src_2 = NULL;
            ((tac_t*) item_aux->value)->dst_1 = NULL;
            ((tac_t*) item_aux->value)->dst_2 = NULL;
            ((tac_t*) item_aux->value)->opcode = OP_NOP;
        }
      }
    }
    if(count == window_size-1) {
      if(free_label) free(label);
      if(free_label_2) free(label_2);
    }
    item_aux = item_aux->prev;
    count++;
  }
}

void simplify_algebric_operations(optimizer_t* opt) {
  window_t *win_aux = opt->win;
  stack_item_t *item_aux = win_aux->top;
  int delete = 0;
  int count = 0;
  while(count < window_size) {
    if(((tac_t*) item_aux->value)->opcode == OP_ADD_I) {
      if(strcmp(((tac_t*) item_aux->value)->dst_1, "rarp") != 0 && strcmp(((tac_t*) item_aux->value)->dst_1, "rsp") != 0 && strcmp(((tac_t*) item_aux->value)->dst_1, "rbss") != 0) {
        if(strcmp(((tac_t*) item_aux->value)->src_2, "0") == 0) {
          free(((tac_t*) item_aux->value)->src_1);
          free(((tac_t*) item_aux->value)->src_2);
          free(((tac_t*) item_aux->value)->dst_1);
          free(((tac_t*) item_aux->value)->dst_2);
          ((tac_t*) item_aux->value)->src_1 = NULL;
          ((tac_t*) item_aux->value)->src_2 = NULL;
          ((tac_t*) item_aux->value)->dst_1 = NULL;
          ((tac_t*) item_aux->value)->dst_2 = NULL;
          ((tac_t*) item_aux->value)->opcode = OP_NOP;
        }
      }
    }
    if(((tac_t*) item_aux->value)->opcode == OP_MULT_I) {
      if(strcmp(((tac_t*) item_aux->value)->dst_1, "rarp") != 0 && strcmp(((tac_t*) item_aux->value)->dst_1, "rsp") != 0 && strcmp(((tac_t*) item_aux->value)->dst_1, "rbss") != 0) {
        if(strcmp(((tac_t*) item_aux->value)->src_2, "1") == 0) {
          free(((tac_t*) item_aux->value)->src_1);
          free(((tac_t*) item_aux->value)->src_2);
          free(((tac_t*) item_aux->value)->dst_1);
          free(((tac_t*) item_aux->value)->dst_2);
          ((tac_t*) item_aux->value)->src_1 = NULL;
          ((tac_t*) item_aux->value)->src_2 = NULL;
          ((tac_t*) item_aux->value)->dst_1 = NULL;
          ((tac_t*) item_aux->value)->dst_2 = NULL;
          ((tac_t*) item_aux->value)->opcode = OP_NOP;
        }
        else if(strcmp(((tac_t*) item_aux->value)->src_2, "2") == 0) {
          free(((tac_t*) item_aux->value)->src_2);
          ((tac_t*) item_aux->value)->src_2 = strdup(((tac_t*) item_aux->value)->src_1);
          ((tac_t*) item_aux->value)->opcode = OP_ADD;
        }
      }
    }
    if(((tac_t*) item_aux->value)->opcode == OP_ADD) {
      if(strcmp(((tac_t*) item_aux->value)->dst_1, "rarp") != 0 && strcmp(((tac_t*) item_aux->value)->dst_1, "rsp") != 0 && strcmp(((tac_t*) item_aux->value)->dst_1, "rbss") != 0) {
        if(((tac_t*) (stack_item_t*)(item_aux->next)->value)->opcode == OP_LOAD_I) {
          if(strcmp(((tac_t*) (stack_item_t*)(item_aux->next)->value)->src_1, "0") == 0) {
            free(((tac_t*) item_aux->value)->src_1);
            free(((tac_t*) item_aux->value)->src_2);
            free(((tac_t*) item_aux->value)->dst_1);
            free(((tac_t*) item_aux->value)->dst_2);
            ((tac_t*) item_aux->value)->src_1 = NULL;
            ((tac_t*) item_aux->value)->src_2 = NULL;
            ((tac_t*) item_aux->value)->dst_1 = NULL;
            ((tac_t*) item_aux->value)->dst_2 = NULL;
            ((tac_t*) item_aux->value)->opcode = OP_NOP;
          }
        }
      }
    }
    if(((tac_t*) item_aux->value)->opcode == OP_MULT) {
      if(strcmp(((tac_t*) item_aux->value)->dst_1, "rarp") != 0 && strcmp(((tac_t*) item_aux->value)->dst_1, "rsp") != 0 && strcmp(((tac_t*) item_aux->value)->dst_1, "rbss") != 0) {
        if(((tac_t*) (stack_item_t*)(item_aux->next)->value)->opcode == OP_LOAD_I) {
          printf("oi");
          if(strcmp(((tac_t*) (stack_item_t*)(item_aux->next)->value)->src_1, "1") == 0) {
            free(((tac_t*) item_aux->value)->src_1);
            free(((tac_t*) item_aux->value)->src_2);
            free(((tac_t*) item_aux->value)->dst_1);
            free(((tac_t*) item_aux->value)->dst_2);
            ((tac_t*) item_aux->value)->src_1 = NULL;
            ((tac_t*) item_aux->value)->src_2 = NULL;
            ((tac_t*) item_aux->value)->dst_1 = NULL;
            ((tac_t*) item_aux->value)->dst_2 = NULL;
            ((tac_t*) item_aux->value)->opcode = OP_NOP;
          }
          else if(strcmp(((tac_t*) (stack_item_t*)(item_aux->next)->value)->src_1, "2") == 0) {
            free(((tac_t*) item_aux->value)->src_2);
            ((tac_t*) item_aux->value)->src_2 = strdup(((tac_t*) item_aux->value)->src_1);
            ((tac_t*) item_aux->value)->opcode = OP_ADD;
          }
        }
      }
    }
    item_aux = item_aux->prev;
    count++;
  }
}

void propagate_copy(optimizer_t* opt) {
  window_t *win_aux = opt->win;
  stack_item_t *item_aux = win_aux->top;
  stack_item_t *load_aux;
  int count = 0;
  int change = 0;
  int primeiro = 0;
  char* register_a;
  char* register_b;
  while(count < window_size) {
    primeiro = 0;
    if(((tac_t*) item_aux->value)->opcode == OP_LOAD && change == 0) {
      register_b =  ((tac_t*) item_aux->value)->src_1;
      register_a =  ((tac_t*) item_aux->value)->dst_1;
      load_aux = item_aux;
      change = 1;
      primeiro = 1;
    }
    else if(((tac_t*) item_aux->value)->opcode == OP_LOAD && change == 1) {
      if(strcmp(((tac_t*) item_aux->value)->dst_1, register_b) == 0) {
        change = 0;
      }
    }
    if(((tac_t*) item_aux->value)->opcode == OP_LOAD_I && change == 1) {
      if(strcmp(((tac_t*) item_aux->value)->dst_1, register_b) == 0) {
        change = 0;
      }
    }
    if(((tac_t*) item_aux->value)->opcode == OP_LOAD_AI && change == 1) {
      if(strcmp(((tac_t*) item_aux->value)->dst_1, register_b) == 0) {
        change = 0;
      }
    }
    if(((tac_t*) item_aux->value)->opcode == OP_LOAD_A0 && change == 1) {
      if(strcmp(((tac_t*) item_aux->value)->dst_1, register_b) == 0) {
        change = 0;
      }
    }
    if(change == 1 && primeiro == 0) {
      if(((tac_t*) item_aux->value)->src_1) {
        if(strcmp(((tac_t*) item_aux->value)->src_1, register_a) == 0) {
          strcpy(((tac_t*) item_aux->value)->src_1, register_b);
        }
      }
      if(((tac_t*) item_aux->value)->src_2) {
        if(strcmp(((tac_t*) item_aux->value)->src_2, register_a) == 0) {
          strcpy(((tac_t*) item_aux->value)->src_2, register_b);
        }
      }
    }
    item_aux = item_aux->prev;
    count++;
  }
  if(change == 1 && primeiro == 0) {
    free(((tac_t*) load_aux->value)->src_1);
    free(((tac_t*) load_aux->value)->src_2);
    free(((tac_t*) load_aux->value)->dst_1);
    free(((tac_t*) load_aux->value)->dst_2);
    ((tac_t*) load_aux->value)->src_1 = NULL;
    ((tac_t*) load_aux->value)->src_2 = NULL;
    ((tac_t*) load_aux->value)->dst_1 = NULL;
    ((tac_t*) load_aux->value)->dst_2 = NULL;
    ((tac_t*) load_aux->value)->opcode = OP_NOP;
  }
}

void avaliate_constant(optimizer_t* opt) {
  window_t *win_aux = opt->win;
  stack_item_t *item_aux = win_aux->top;
  int delete = 0;
  int count = 0;
}

void run_optimization_tests(char* mode) {
  printf("******** Optimization Tests %s [window size = %d] ********\n\n", mode, window_size);
  //TODO chamar métodos de teste
  int size = window_size;
  window_size = 2;
  printf("\n[window_size = %d]\n", window_size);
  eliminate_redundant_instructions_feature_test();
  window_size = 4;
  printf("\n[window_size = %d]\n", window_size);
  optimize_flux_control_feature_test();
  window_size = 3;
  printf("\n[window_size = %d]\n", window_size);
  simplify_algebric_operations_feature_test();
  window_size = 3;
  printf("\n[window_size = %d]\n", window_size);
  propagate_copy_feature_test();
  window_size = size;
  printf("\n[window_size = %d]\n", window_size);
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
  char *register_r = new_register();
  char *register_r1 = new_register();
  char *register_a = new_register();
  char *register_b = new_register();
  char *imediate0 = new_imediate(0);
  char *imediate1 = new_imediate(1);
  char *imediate2 = new_imediate(2);
  tac_t* jump = new_tac_jump_i(true, NULL, "lR");
  tac_t* load = new_tac_sed(true, NULL, OP_LOAD, register_r, register_r1);
  tac_t* store = new_tac_sed(true, NULL, OP_STORE, register_r1, register_r);
  tac_t* load_1 = new_tac_sed(true, NULL, OP_LOAD, register_r, register_r1);
  tac_t* jump_1 = new_tac_jump_i(true, "lR", "lR2");
  tac_t* cbr = new_tac_cbr(true, NULL, NULL, "lR3", "lR4");
  tac_t* load_2 = new_tac_sed(true, NULL, OP_LOAD, register_r, register_r1);
  tac_t* store_1 = new_tac_sed(true, NULL, OP_STORE, register_r1, register_r);
  tac_t* jump_2 = new_tac_jump_i(true, "lR3", "lR5");
  tac_t* jump_3 = new_tac_jump_i(true, "lR4", "lR6");
  tac_t* add = new_tac_ssed(true, NULL, OP_ADD_I, register_r, imediate0, register_r1);
  tac_t* mult = new_tac_ssed(true, NULL, OP_MULT_I, register_r, imediate1, register_r1);
  tac_t* mult_1 = new_tac_ssed(true, NULL, OP_MULT_I, register_r, imediate2, register_r1);
  tac_t* load_3 = new_tac_sed(true, NULL, OP_LOAD, register_b, register_a);
  tac_t* add_1 = new_tac_ssed(true, NULL, OP_ADD_I, register_a, imediate2, register_r1);
  stack_push(jump, tac_stack);
  stack_push(load, tac_stack);
  stack_push(store, tac_stack);
  stack_push(load_1, tac_stack);
  stack_push(jump_1, tac_stack);
  stack_push(cbr, tac_stack);
  stack_push(load_2, tac_stack);
  stack_push(store_1, tac_stack);
  stack_push(jump_2, tac_stack);
  stack_push(jump_3, tac_stack);
  stack_push(add, tac_stack);
  stack_push(mult, tac_stack);
  stack_push(mult_1, tac_stack);
  stack_push(load_3, tac_stack);
  stack_push(add_1, tac_stack);
  iloc_to_stdout(tac_stack);

  //otimizar (chamar metodo da feature)
  printf("\nOptimizing...\n\n");
  optimizer_t* opt = new_optimizer(tac_stack);
  window_t* win = opt->win;
  while(win->bottom) {
    eliminate_redundant_instruction(opt);
    optimize_flux_control(opt);
    simplify_algebric_operations(opt);
    propagate_copy(opt);
    win->top = ((stack_item_t*)win->top)->prev;
    win->bottom = ((stack_item_t*)win->bottom)->prev;
  }
  //print código output
  printf("~~~~~~~~~~~~ Output ILOC ~~~~~~~~~~~~\n");
  iloc_to_stdout(opt->tac_stack);

  clear_and_free_optimizer(opt);
  free(register_r); free(register_r1);  free(imediate0); free(imediate1); free(imediate2);
  free(register_a); free(register_b);
}

void eliminate_redundant_instructions_feature_test() {
  //print código input
  printf("~~~~~~~~~~~~ Input ILOC ~~~~~~~~~~~~\n");
  stack_t* tac_stack = new_stack();
  char *register_r = new_register();
  char *register_r1 = new_register();
  char *register_a = new_register();
  char *register_b = new_register();
  char *imediate0 = new_imediate(0);
  char *imediate1 = new_imediate(1);
  char *imediate2 = new_imediate(2);
  tac_t* load = new_tac_sed(true, NULL, OP_LOAD, register_r, register_r1);
  tac_t* store = new_tac_sed(true, NULL, OP_STORE, register_r1, register_r);
  stack_push(load, tac_stack);
  stack_push(store, tac_stack);
  iloc_to_stdout(tac_stack);

  //otimizar (chamar metodo da feature)
  printf("\nOptimizing (eliminate_redundant_instruction)...\n\n");
  optimizer_t* opt = new_optimizer(tac_stack);
  window_t* win = opt->win;
  while(win->bottom) {
    eliminate_redundant_instruction(opt);
    win->top = ((stack_item_t*)win->top)->prev;
    win->bottom = ((stack_item_t*)win->bottom)->prev;
  }
  //print código output
  printf("~~~~~~~~~~~~ Output ILOC ~~~~~~~~~~~~\n");
  iloc_to_stdout(opt->tac_stack);

  clear_and_free_optimizer(opt);
  free(register_r); free(register_r1);  free(imediate0); free(imediate1); free(imediate2);
  free(register_a); free(register_b);
}

void optimize_flux_control_feature_test() {
  //print código input
  printf("~~~~~~~~~~~~ Input ILOC ~~~~~~~~~~~~\n");
  stack_t* tac_stack = new_stack();
  char *register_r = new_register();
  char *register_r1 = new_register();
  char *register_a = new_register();
  char *register_b = new_register();
  char *imediate0 = new_imediate(0);
  char *imediate1 = new_imediate(1);
  char *imediate2 = new_imediate(2);
  tac_t* jump = new_tac_jump_i(true, NULL, "lR");
  tac_t* jump_1 = new_tac_jump_i(true, "lR", "lR2");
  tac_t* cbr = new_tac_cbr(true, NULL, NULL, "lR3", "lR4");
  tac_t* jump_2 = new_tac_jump_i(true, "lR3", "lR5");
  tac_t* jump_3 = new_tac_jump_i(true, "lR4", "lR6");
  stack_push(jump, tac_stack);
  stack_push(jump_1, tac_stack);
  stack_push(cbr, tac_stack);
  stack_push(jump_2, tac_stack);
  stack_push(jump_3, tac_stack);
  iloc_to_stdout(tac_stack);

  //otimizar (chamar metodo da feature)
  printf("\nOptimizing (optimize_flux_control)...\n\n");
  optimizer_t* opt = new_optimizer(tac_stack);
  window_t* win = opt->win;
  while(win->bottom) {
    optimize_flux_control(opt);
    win->top = ((stack_item_t*)win->top)->prev;
    win->bottom = ((stack_item_t*)win->bottom)->prev;
  }
  //print código output
  printf("~~~~~~~~~~~~ Output ILOC ~~~~~~~~~~~~\n");
  iloc_to_stdout(opt->tac_stack);

  clear_and_free_optimizer(opt);
  free(register_r); free(register_r1);  free(imediate0); free(imediate1); free(imediate2);
  free(register_a); free(register_b);
}

void simplify_algebric_operations_feature_test() {
  //print código input
  printf("~~~~~~~~~~~~ Input ILOC ~~~~~~~~~~~~\n");
  stack_t* tac_stack = new_stack();
  char *register_r = new_register();
  char *register_r1 = new_register();
  char *register_a = new_register();
  char *register_b = new_register();
  char *imediate0 = new_imediate(0);
  char *imediate1 = new_imediate(1);
  char *imediate2 = new_imediate(2);
  tac_t* add = new_tac_ssed(true, NULL, OP_ADD_I, register_r, imediate0, register_r1);
  tac_t* mult = new_tac_ssed(true, NULL, OP_MULT_I, register_r, imediate1, register_r1);
  tac_t* mult_1 = new_tac_ssed(true, NULL, OP_MULT_I, register_r, imediate2, register_r1);
  stack_push(add, tac_stack);
  stack_push(mult, tac_stack);
  stack_push(mult_1, tac_stack);
  iloc_to_stdout(tac_stack);

  //otimizar (chamar metodo da feature)
  printf("\nOptimizing (simplify_algebric_operations)...\n\n");
  optimizer_t* opt = new_optimizer(tac_stack);
  window_t* win = opt->win;
  while(win->bottom) {
    simplify_algebric_operations(opt);
    win->top = ((stack_item_t*)win->top)->prev;
    win->bottom = ((stack_item_t*)win->bottom)->prev;
  }
  //print código output
  printf("~~~~~~~~~~~~ Output ILOC ~~~~~~~~~~~~\n");
  iloc_to_stdout(opt->tac_stack);

  clear_and_free_optimizer(opt);
  free(register_r); free(register_r1);  free(imediate0); free(imediate1); free(imediate2);
  free(register_a); free(register_b);
}

void propagate_copy_feature_test() {
  //print código input
  printf("~~~~~~~~~~~~ Input ILOC ~~~~~~~~~~~~\n");
  stack_t* tac_stack = new_stack();
  char *register_r = new_register();
  char *register_r1 = new_register();
  char *register_a = new_register();
  char *register_b = new_register();
  char *imediate0 = new_imediate(0);
  char *imediate1 = new_imediate(1);
  char *imediate2 = new_imediate(2);
  tac_t* load_3 = new_tac_sed(true, NULL, OP_LOAD, register_b, register_a);
  tac_t* add_1 = new_tac_ssed(true, NULL, OP_ADD_I, register_a, imediate2, register_r1);
  tac_t* mult_1 = new_tac_ssed(true, NULL, OP_MULT_I, register_a, imediate2, register_r1);
  stack_push(load_3, tac_stack);
  stack_push(add_1, tac_stack);
  stack_push(mult_1, tac_stack);
  iloc_to_stdout(tac_stack);

  //otimizar (chamar metodo da feature)
  printf("\nOptimizing (propagate_copy)...\n\n");
  optimizer_t* opt = new_optimizer(tac_stack);
  window_t* win = opt->win;
  while(win->bottom) {
    propagate_copy(opt);
    win->top = ((stack_item_t*)win->top)->prev;
    win->bottom = ((stack_item_t*)win->bottom)->prev;
  }
  //print código output
  printf("~~~~~~~~~~~~ Output ILOC ~~~~~~~~~~~~\n");
  iloc_to_stdout(opt->tac_stack);

  clear_and_free_optimizer(opt);
  free(register_r); free(register_r1);  free(imediate0); free(imediate1); free(imediate2);
  free(register_a); free(register_b);
}