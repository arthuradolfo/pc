/*
 * Header for optimization.c
 */

#ifndef COMPILADOR_OPTIMIZATION_H
#define COMPILADOR_OPTIMIZATION_H

#include "tac.h"

#define STD_WINDOW_SIZE 2
#define WINDOW_STEP 1

int window_size;

typedef struct {
    stack_item_t* top;
    stack_item_t* bottom;
} window_t;

typedef struct {
    window_t* win;
    stack_t* tac_stack;
} optimizer_t;

window_t* new_window(stack_item_t* top, stack_item_t* bottom);
optimizer_t* new_optimizer(stack_t* tac_stack);
void clear_and_free_optimizer(optimizer_t* opt);

void optimization_module_init(int argc, char** argv);
void print_optimization_mode();
char* optimization_mode_to_string();
void run_optimization_tests();

void example_feature_test();

#endif //COMPILADOR_OPTIMIZATION_H
