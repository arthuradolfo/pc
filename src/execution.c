#include "execution.h"
#include <stdlib.h>
#include <stdio.h>

func_def_t* new_func_def() {
    func_def_t* func_def = malloc(sizeof(func_def_t));
    func_def->formal_params_size = 0;
    func_def->local_vars_size = 0;
    func_def->return_size = 0;
    return func_def;
}

int func_def_size(func_def_t* func_def) {
    return func_def->formal_params_size +
           func_def->local_vars_size +
           func_def->return_size;
}

void print_func_def(func_def_t *func_def) {
    printf("\nfunc_def->formal_params_size = %d\n", func_def->formal_params_size);
    printf("func_def->local_vars_size = %d\n", func_def->local_vars_size);
    printf("func_def->return_size = %d\n\n", func_def->return_size);
}
