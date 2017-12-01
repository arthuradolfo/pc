/**
 * Arquivo com funções de tratamento de TAC (three adresses code)
 */

#include "tac.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

tac_t* new_tac(int opcode, char* src_1, char* src_2, char* dst_1, char* dst_2)
{
  tac_t* tac = (tac_t*) malloc(sizeof(tac_t));
  tac->opcode = opcode;

  if (src_1)
    tac->src_1 = strdup(src_1);
  else
    tac->src_1 = NULL;

  if (src_2)
    tac->src_2 = strdup(src_2);
  else
    tac->src_2 = NULL;

  if (dst_1)
    tac->dst_1 = strdup(dst_1);
  else
    tac->dst_1 = NULL;

  if (dst_2)
    tac->dst_2 = strdup(dst_2);
  else
    tac->dst_2 = NULL;

  return tac;
}

void destroy_tac(tac_t* tac)
{
  if (tac->src_1) free(tac->src_1);
  if (tac->src_2) free(tac->src_2);
  if (tac->dst_1) free(tac->dst_1);
  if (tac->dst_2) free(tac->dst_2);
  free(tac);
}

void create_and_destroy_tac_test()
{
  char* reg_1 = new_register();
  char* reg_2 = new_register();
  char* reg_3 = new_register();
  tac_t* tac = new_tac(OP_ADD, reg_1, reg_2, reg_3, NULL);
  destroy_tac(tac);
  free(reg_1);
  free(reg_2);
  free(reg_3);
}

char* new_label()
{
  int number_of_digits = floor(log(label_counter)+1);

  char* label_name = (char*) malloc(sizeof(char)*(1/*para o 'L'*/ + number_of_digits + 1/*para o '\0'*/));
  sprintf(label_name, "L%d", label_counter);

  label_counter++;

  return label_name;
}

char* new_register()
{
  int number_of_digits = floor(log(register_counter)+1);

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

char* new_imediate(int constant)
{
  int number_of_digits;
  if (constant == 0)
    number_of_digits = 1;
  else {
    number_of_digits = floor(log(abs(constant))+1);

    if (constant < 0)
      number_of_digits++; //para o "-"
  }


  char* imediate = (char*) malloc(sizeof(char)*(number_of_digits + 1/*para o '\0'*/));
  sprintf(imediate, "%d", constant);

  return imediate;
}

void imediates_test()
{
  int i;
  for (i = -101; i <= 101; i++) {
    char* imediate = new_imediate(i);
    printf("imediate(%d): %s\n", i, imediate);
    free(imediate);
  }
}

char* tac_to_string(tac_t* tac)
{
  size_t code_size_in_bytes;
  char* code;


  switch (tac->opcode) {
    //aritmetica
    case OP_ADD:
      code_size_in_bytes =
          (strlen("add ") +
          strlen(tac->src_1) +
          strlen(", ") +
          strlen(tac->src_2) +
          strlen(" => ") +
          strlen(tac->dst_1) +
          1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "add %s, %s => %s", tac->src_1, tac->src_2, tac->dst_1);

      break;

    case OP_SUB:
      code_size_in_bytes =
          (strlen("sub ") +
          strlen(tac->src_1) +
          strlen(", ") +
          strlen(tac->src_2) +
          strlen(" => ") +
          strlen(tac->dst_1) +
          1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "sub %s, %s => %s", tac->src_1, tac->src_2, tac->dst_1);

      break;

    case OP_MULT:
      code_size_in_bytes =
          (strlen("mult ") +
          strlen(tac->src_1) +
          strlen(", ") +
          strlen(tac->src_2) +
          strlen(" => ") +
          strlen(tac->dst_1) +
          1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "mult %s, %s => %s", tac->src_1, tac->src_2, tac->dst_1);

      break;

    case OP_DIV:
      code_size_in_bytes =
          (strlen("div ") +
          strlen(tac->src_1) +
          strlen(", ") +
          strlen(tac->src_2) +
          strlen(" => ") +
          strlen(tac->dst_1) +
          1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "div %s, %s => %s", tac->src_1, tac->src_2, tac->dst_1);

      break;

    case OP_ADD_I:
      code_size_in_bytes =
          (strlen("addI ") +
          strlen(tac->src_1) +
          strlen(", ") +
          strlen(tac->src_2) +
          strlen(" => ") +
          strlen(tac->dst_1) +
          1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "addI %s, %s => %s", tac->src_1, tac->src_2, tac->dst_1);

      break;

    case OP_SUB_I:
      code_size_in_bytes =
          (strlen("subI ") +
          strlen(tac->src_1) +
          strlen(", ") +
          strlen(tac->src_2) +
          strlen(" => ") +
          strlen(tac->dst_1) +
          1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "subI %s, %s => %s", tac->src_1, tac->src_2, tac->dst_1);

      break;

    case OP_RSUB_I:
      code_size_in_bytes =
          (strlen("rsubI ") +
          strlen(tac->src_1) +
          strlen(", ") +
          strlen(tac->src_2) +
          strlen(" => ") +
          strlen(tac->dst_1) +
          1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "rsubI %s, %s => %s", tac->src_1, tac->src_2, tac->dst_1);

      break;

    case OP_MULT_I:
      code_size_in_bytes =
          (strlen("multI ") +
          strlen(tac->src_1) +
          strlen(", ") +
          strlen(tac->src_2) +
          strlen(" => ") +
          strlen(tac->dst_1) +
          1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "multI %s, %s => %s", tac->src_1, tac->src_2, tac->dst_1);

      break;

    case OP_DIV_I:
      code_size_in_bytes =
          (strlen("divI ") +
          strlen(tac->src_1) +
          strlen(", ") +
          strlen(tac->src_2) +
          strlen(" => ") +
          strlen(tac->dst_1) +
          1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "divI %s, %s => %s", tac->src_1, tac->src_2, tac->dst_1);

      break;

    case OP_RDIV_I:
      code_size_in_bytes =
          (strlen("rdivI ") +
          strlen(tac->src_1) +
          strlen(", ") +
          strlen(tac->src_2) +
          strlen(" => ") +
          strlen(tac->dst_1) +
          1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "rdivI %s, %s => %s", tac->src_1, tac->src_2, tac->dst_1);

      break;


     //shifts
     case OP_LSHIFT:
       code_size_in_bytes =
               (strlen("lshift ") +
                strlen(tac->src_1) +
                strlen(", ") +
                strlen(tac->src_2) +
                strlen(" => ") +
                strlen(tac->dst_1) +
                1 /*para o \0*/) * sizeof(char);

        code = malloc(code_size_in_bytes);
        sprintf(code, "lshift %s, %s => %s", tac->src_1, tac->src_2, tac->dst_1);

        break;

      case OP_LSHIFT_I:
        code_size_in_bytes =
                (strlen("lshiftI ") +
                 strlen(tac->src_1) +
                 strlen(", ") +
                 strlen(tac->src_2) +
                 strlen(" => ") +
                 strlen(tac->dst_1) +
                 1 /*para o \0*/) * sizeof(char);

        code = malloc(code_size_in_bytes);
        sprintf(code, "lshiftI %s, %s => %s", tac->src_1, tac->src_2, tac->dst_1);

        break;

     case OP_RSHIFT:
       code_size_in_bytes =
               (strlen("rshift ") +
                strlen(tac->src_1) +
                strlen(", ") +
                strlen(tac->src_2) +
                strlen(" => ") +
                strlen(tac->dst_1) +
                1 /*para o \0*/) * sizeof(char);

        code = malloc(code_size_in_bytes);
        sprintf(code, "rshift %s, %s => %s", tac->src_1, tac->src_2, tac->dst_1);

        break;

      case OP_RSHIFT_I:
        code_size_in_bytes =
                (strlen("rshiftI ") +
                 strlen(tac->src_1) +
                 strlen(", ") +
                 strlen(tac->src_2) +
                 strlen(" => ") +
                 strlen(tac->dst_1) +
                 1 /*para o \0*/) * sizeof(char);

        code = malloc(code_size_in_bytes);
        sprintf(code, "rshiftI %s, %s => %s", tac->src_1, tac->src_2, tac->dst_1);

        break;


    // //memoria - leitura
    // case OP_LOAD:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    // case OP_LOAD_AI:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    // case OP_LOAD_A0:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    // case OP_CLOAD:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    // case OP_CLOAD_AI:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    // case OP_CLOAD_A0:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    // case OP_LOAD_I:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    //
    // //memoria - escrita
    // case OP_STORE:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    // case OP_STORE_AI:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    // case OP_STORE_A0:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    // case OP_CSTORE:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    // case OP_CSTORE_AI:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    // case OP_CSTORE_A0:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    //
    // //copia entre registradores
    // case OP_I2I:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    // case OP_C2C:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    // case OP_C2I:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    // case OP_I2C:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    //
    // //controle de fluxo
    // case OP_CMP_LT:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    // case OP_CMP_LE:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    // case OP_CMP_EQ:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    // case OP_CMP_GE:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    // case OP_CMP_GT:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    // case OP_CMP_NE:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    // case OP_CBR:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    //
    // //saltos
    // case OP_JUMP_I:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;
    //
    // case OP_JUMP:
    //   code_size_in_bytes =
    //   code = malloc(code_size_in_bytes);
    //
    //   break;

    default:
      printf("Opcode de tac_t deve ser uma das constantes OP_* de tac.h\n");
      return NULL;
  }
  return code;
}

void tac_to_string_arit_test()
{
  int opcode = 0;
  tac_t* tac;
  char* code;

  //aritmetica
  for (opcode = OP_ADD; opcode <= OP_DIV; opcode++) {
    char* reg_1 = new_register();
    char* reg_2 = new_register();
    char* reg_3 = new_register();

    tac = new_tac(opcode, reg_1, reg_2, reg_3, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(reg_2);
    free(reg_3);
    destroy_tac(tac);
    free(code);
  }
  for (opcode = OP_ADD_I; opcode <= OP_RDIV_I; opcode++) {
    char* reg_1 = new_register();
    char* imed = new_imediate(42);
    char* reg_2 = new_register();

    tac = new_tac(opcode, reg_1, imed, reg_2, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(imed);
    free(reg_2);
    destroy_tac(tac);
    free(code);
  }
}

void tac_to_string_shifts_test()
{
  int i;
  int opcode = 0;
  tac_t* tac;
  char* code;

  //shifts
  for (i = 0; i < 2; ++i) {
    if      (i == 0) opcode = OP_LSHIFT;
    else if (i == 1) opcode = OP_RSHIFT;

    char* reg_1 = new_register();
    char* reg_2 = new_register();
    char* reg_3 = new_register();

    tac = new_tac(opcode, reg_1, reg_2, reg_3, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(reg_2);
    free(reg_3);
    destroy_tac(tac);
    free(code);
  }
  for (i = 0; i < 2; ++i) {
    if      (i == 0) opcode = OP_LSHIFT_I;
    else if (i == 1) opcode = OP_RSHIFT_I;

    char* reg_1 = new_register();
    char* imed = new_imediate(42);
    char* reg_2 = new_register();

    tac = new_tac(opcode, reg_1, imed, reg_2, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(imed);
    free(reg_2);
    destroy_tac(tac);
    free(code);
  }
}

void tac_to_string_test()
{
  tac_to_string_arit_test();
  tac_to_string_shifts_test();
}
