/**
 * Arquivo com funções de tratamento de TAC (three adresses code)
 */

#include "tac.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

char* new_label()
{
  int number_of_digits = ceil(log(label_counter));

  char* label_name = (char*) malloc(sizeof(char)*(1/*para o 'L'*/ + number_of_digits + 1/*para o '\0'*/));
  sprintf(label_name, "L%d", label_counter);

  label_counter++;

  return label_name;
}

char* new_register()
{
  int number_of_digits = floor(log(label_counter)+1);

  char* register_name = (char*) malloc(sizeof(char)*(1/*para o 'r'*/ + number_of_digits + 1/*para o '\0'*/));
  sprintf(register_name, "r%d", register_counter);

  register_counter++;

  return register_name;
}

void registers_labels_test()
{
  int i = 0;
  for (i = 0; i < 2001; i++)
  {
    char* label = new_label();
    printf("%s\n", label);
    free(label);

    char* registr = new_register();
    printf("%s\n", registr);
    free(registr);
  }
}
