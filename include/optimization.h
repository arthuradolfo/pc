/*
 * Header for optimization.c
 */

#ifndef COMPILADOR_OPTIMIZATION_H
#define COMPILADOR_OPTIMIZATION_H

#define STD_WINDOW_SIZE 2

int window_size;

void optimization_module_init(int argc, char** argv);
void print_optimization_mode();
char* optimization_mode_to_string();
void run_optimization_tests();

#endif //COMPILADOR_OPTIMIZATION_H
