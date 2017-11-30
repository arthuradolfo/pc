/**
 * Arquivo com funções de tratamento de TAC (three adresses code)
 */

#ifndef TAC_H
#define TAC_H

int label_counter;
int register_counter;

/**
 * Retorna um nome de rótulo novo
 */
char* new_label();

/**
 * Retorna um nome de registrador novo
 */
char* new_register();

#endif
