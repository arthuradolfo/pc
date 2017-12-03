/**
 * Arquivo com funções de tratamento de TAC (three adresses code)
 */

#include "cc_list.h"
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

tac_t* copy_tac(tac_t* copied)
{
  return new_tac(copied->opcode, copied->src_1, copied->src_2, copied->dst_1, copied->dst_2);
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
  size_t number_of_digits = (size_t) floor(log(label_counter) + 1);

  char* label_name = (char*) malloc((sizeof(char) * (1/*para o 'L'*/ + number_of_digits + 1/*para o '\0'*/)));
  sprintf(label_name, "L%d", label_counter);

  label_counter++;

  return label_name;
}

char* new_register()
{
  size_t number_of_digits = (size_t) floor(log(register_counter)+1);

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
  size_t number_of_digits;
  if (constant == 0)
    number_of_digits = 1;
  else {
    number_of_digits = (size_t) floor(log(abs(constant))+1);

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

char* tac_to_string(tac_t *tac)
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


    //memoria - leitura
    case OP_LOAD:
      code_size_in_bytes =
              (strlen("load ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "load %s => %s", tac->src_1, tac->dst_1);

      break;

    case OP_LOAD_AI:
      code_size_in_bytes =
              (strlen("loadAI ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "loadAI %s, %s => %s", tac->src_1, tac->src_2, tac->dst_1);

      break;

    case OP_LOAD_A0:
      code_size_in_bytes =
              (strlen("loadA0 ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "loadA0 %s, %s => %s", tac->src_1, tac->src_2, tac->dst_1);

      break;

    case OP_CLOAD:
      code_size_in_bytes =
              (strlen("cload ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "cload %s => %s", tac->src_1, tac->dst_1);

      break;

    case OP_CLOAD_AI:
      code_size_in_bytes =
              (strlen("cloadAI ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "cloadAI %s, %s => %s", tac->src_1, tac->src_2, tac->dst_1);

      break;

     case OP_CLOAD_A0:
       code_size_in_bytes =
               (strlen("cloadA0 ") +
                strlen(tac->src_1) +
                strlen(", ") +
                strlen(tac->src_2) +
                strlen(" => ") +
                strlen(tac->dst_1) +
                1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "cloadA0 %s, %s => %s", tac->src_1, tac->src_2, tac->dst_1);

      break;

    case OP_LOAD_I:
      code_size_in_bytes =
              (strlen("loadI ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "loadI %s => %s", tac->src_1, tac->dst_1);

      break;


     //memoria - escrita
     case OP_STORE:
       code_size_in_bytes =
               (strlen("store ") +
                strlen(tac->src_1) +
                strlen(" => ") +
                strlen(tac->dst_1) +
                1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "store %s => %s", tac->src_1, tac->dst_1);

      break;

    case OP_STORE_AI:
      code_size_in_bytes =
              (strlen("storeAI ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               strlen(", ") +
               strlen(tac->dst_2) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "storeAI %s => %s, %s", tac->src_1, tac->dst_1, tac->dst_2);

      break;

    case OP_STORE_A0:
      code_size_in_bytes =
              (strlen("storeA0 ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               strlen(", ") +
               strlen(tac->dst_2) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "storeA0 %s => %s, %s", tac->src_1, tac->dst_1, tac->dst_2);

      break;

    case OP_CSTORE:
      code_size_in_bytes =
              (strlen("cstore ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "cstore %s => %s", tac->src_1, tac->dst_1);

      break;

    case OP_CSTORE_AI:
      code_size_in_bytes =
              (strlen("cstoreAI ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               strlen(", ") +
               strlen(tac->dst_2) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "cstoreAI %s => %s, %s", tac->src_1, tac->dst_1, tac->dst_2);

      break;

    case OP_CSTORE_A0:
      code_size_in_bytes =
              (strlen("cstoreA0 ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               strlen(", ") +
               strlen(tac->dst_2) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "cstoreA0 %s => %s, %s", tac->src_1, tac->dst_1, tac->dst_2);

      break;


     //copia entre registradores
     case OP_I2I:
       code_size_in_bytes =
               (strlen("i2i ") +
                strlen(tac->src_1) +
                strlen(" => ") +
                strlen(tac->dst_1) +
                1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "i2i %s => %s", tac->src_1, tac->dst_1);

      break;

    case OP_C2C:
      code_size_in_bytes =
              (strlen("c2c ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "c2c %s => %s", tac->src_1, tac->dst_1);

      break;

    case OP_C2I:
      code_size_in_bytes =
              (strlen("c2i ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "c2i %s => %s", tac->src_1, tac->dst_1);

      break;

    case OP_I2C:
      code_size_in_bytes =
              (strlen("i2c ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "i2c %s => %s", tac->src_1, tac->dst_1);

      break;


    //controle de fluxo
     case OP_CMP_LT:
       code_size_in_bytes =
               (strlen("cmp_LT ") +
                strlen(tac->src_1) +
                strlen(", ") +
                strlen(tac->src_2) +
                strlen(" -> ") +
                strlen(tac->dst_1) +
                1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "cmp_LT %s, %s -> %s", tac->src_1, tac->src_2, tac->dst_1);

      break;

    case OP_CMP_LE:
      code_size_in_bytes =
              (strlen("cmp_LE ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" -> ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "cmp_LE %s, %s -> %s", tac->src_1, tac->src_2, tac->dst_1);

      break;

    case OP_CMP_EQ:
      code_size_in_bytes =
              (strlen("cmp_EQ ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" -> ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "cmp_EQ %s, %s -> %s", tac->src_1, tac->src_2, tac->dst_1);

      break;

    case OP_CMP_GE:
      code_size_in_bytes =
              (strlen("cmp_GE ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" -> ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "cmp_GE %s, %s -> %s", tac->src_1, tac->src_2, tac->dst_1);

      break;

    case OP_CMP_GT:
      code_size_in_bytes =
              (strlen("cmp_GT ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" -> ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "cmp_GT %s, %s -> %s", tac->src_1, tac->src_2, tac->dst_1);

      break;

    case OP_CMP_NE:
      code_size_in_bytes =
              (strlen("cmp_NE ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" -> ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "cmp_NE %s, %s -> %s", tac->src_1, tac->src_2, tac->dst_1);

      break;

    case OP_CBR:
      code_size_in_bytes =
              (strlen("cbr ") +
               strlen(tac->src_1) +
               strlen(" -> ") +
               strlen(tac->dst_1) +
               strlen(", ") +
               strlen(tac->dst_2) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "cbr %s -> %s, %s", tac->src_1, tac->dst_1, tac->dst_2);

      break;


     //saltos
     case OP_JUMP_I:
       code_size_in_bytes =
               (strlen("jumpI") +
                strlen(" -> ") +
                strlen(tac->dst_1) +
                1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "jumpI -> %s", tac->dst_1);

      break;

    case OP_JUMP:
      code_size_in_bytes =
              (strlen("jump") +
               strlen(" -> ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "jump -> %s", tac->dst_1);

      break;


    default:
      printf("Opcode de tac_t deve ser uma das constantes OP_* de tac.h\n");
      exit(EXIT_FAILURE);
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

void tac_to_string_loads_test()
{
  int i;
  int opcode = 0;
  tac_t *tac;
  char *code;

  for (i = 0; i < 2; ++i) {
    if (i == 0) opcode = OP_LOAD;
    else if (i == 1) opcode = OP_CLOAD;

    char *reg_1 = new_register();
    char *reg_2 = new_register();

    tac = new_tac(opcode, reg_1, NULL, reg_2, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(reg_2);
    destroy_tac(tac);
    free(code);
  }
  for (i = 0; i < 2; ++i) {
    if (i == 0) opcode = OP_LOAD_AI;
    else if (i == 1) opcode = OP_CLOAD_AI;

    char *reg_1 = new_register();
    char *imed = new_imediate(42);
    char *reg_2 = new_register();

    tac = new_tac(opcode, reg_1, imed, reg_2, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(imed);
    free(reg_2);
    destroy_tac(tac);
    free(code);
  }
  for (i = 0; i < 2; ++i) {
    if (i == 0) opcode = OP_LOAD_A0;
    else if (i == 1) opcode = OP_CLOAD_A0;

    char *reg_1 = new_register();
    char *reg_2 = new_register();
    char *reg_3 = new_register();

    tac = new_tac(opcode, reg_1, reg_2, reg_3, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(reg_2);
    free(reg_3);
    destroy_tac(tac);
    free(code);
  }

  {
    opcode = OP_LOAD_I;

    char *reg_1 = new_register();
    char *reg_2 = new_register();

    tac = new_tac(opcode, reg_1, NULL, reg_2, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(reg_2);
    destroy_tac(tac);
    free(code);
  }
}

void tac_to_string_stores_test()
{
  int i;
  int opcode = 0;
  tac_t *tac;
  char *code;

  for (i = 0; i < 2; ++i) {
    if (i == 0) opcode = OP_STORE;
    else if (i == 1) opcode = OP_CSTORE;

    char *reg_1 = new_register();
    char *reg_2 = new_register();

    tac = new_tac(opcode, reg_1, NULL, reg_2, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(reg_2);
    destroy_tac(tac);
    free(code);
  }
  for (i = 0; i < 2; ++i) {
    if (i == 0) opcode = OP_STORE_AI;
    else if (i == 1) opcode = OP_CSTORE_AI;

    char *reg_1 = new_register();
    char *imed = new_imediate(42);
    char *reg_2 = new_register();

    tac = new_tac(opcode, reg_1, NULL, reg_2, imed);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(imed);
    free(reg_2);
    destroy_tac(tac);
    free(code);
  }
  for (i = 0; i < 2; ++i) {
    if (i == 0) opcode = OP_STORE_A0;
    else if (i == 1) opcode = OP_CSTORE_A0;

    char *reg_1 = new_register();
    char *reg_2 = new_register();
    char *reg_3 = new_register();

    tac = new_tac(opcode, reg_1, NULL, reg_2, reg_3);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(reg_2);
    free(reg_3);
    destroy_tac(tac);
    free(code);
  }
}

void tac_to_string_reg_copy_test()
{
  int opcode = 0;
  tac_t *tac;
  char *code;

  for (opcode = OP_I2I; opcode <= OP_I2C; ++opcode) {
    char *reg_1 = new_register();
    char *reg_2 = new_register();

    tac = new_tac(opcode, reg_1, NULL, reg_2, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(reg_2);
    destroy_tac(tac);
    free(code);
  }
}

void tac_to_string_flux_control_test()
{
  int opcode = 0;
  tac_t* tac;
  char* code;

  for (opcode = OP_CMP_LT; opcode <= OP_CMP_NE; opcode++) {
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
  {
    opcode = OP_CBR;
    char* reg_1 = new_register();
    char* label_1 = new_label();
    char* label_2 = new_label();

    tac = new_tac(opcode, reg_1, NULL, label_1, label_2);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(label_1);
    free(label_2);
    destroy_tac(tac);
    free(code);
  }
}

void tac_to_string_jumps_test()
{
  int opcode = 0;
  tac_t* tac;
  char* code;

  {
    opcode = OP_JUMP_I;
    char* label = new_label();

    tac = new_tac(opcode, NULL, NULL, label, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(label);
    destroy_tac(tac);
    free(code);
  }
  {
    opcode = OP_JUMP;
    char* reg = new_register();

    tac = new_tac(opcode, NULL, NULL, reg, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg);
    destroy_tac(tac);
    free(code);
  }
}

void tac_to_string_test()
{
  printf("\n____  Arits  ____\n");
  tac_to_string_arit_test();
  printf("\n____  Shifts  ____\n");
  tac_to_string_shifts_test();
  printf("\n____  Loads  ____\n");
  tac_to_string_loads_test();
  printf("\n____  Stores  ____\n");
  tac_to_string_stores_test();
  printf("\n____  RegCopies  ____\n");
  tac_to_string_reg_copy_test();
  printf("\n____  FluxCtrl  ____\n");
  tac_to_string_flux_control_test();
  printf("\n____  Jumps  ____\n");
  tac_to_string_jumps_test();
}

void tac_basic_tests()
{
  registers_labels_test();
  imediates_test();
  create_and_destroy_tac_test();
  tac_to_string_test();
}


/**************** TAC STACK ****************/

void clear_tac_stack(stack_t** stack)
{
  stack_item_t* item;
  item = (*stack)->data;

  do {
    if (item && item->value) {
      destroy_tac(item->value);
      item = item->next;
    }
  } while (item);
}

void reverse_stack(stack_t** stack)
{
  stack_t* reversed = new_stack();
  stack_item_t* item = (*stack)->data;

  while (item) {
    stack_push(item->value, reversed);
    item = item->next;
  }

  free_stack(*stack);
  *stack = reversed;
}

void print_tac_stack(stack_t** stack)
{
  tac_t* tac;
  stack_item_t* item = (*stack)->data;

  printf("TOPO\n");
  while (item) {
    tac = item->value;
    if (tac) {
      char *code = tac_to_string(tac);
      printf("%s\n", code);
      free(code);
    }
    item = item->next;
  }
  printf("FUNDO\n");
}

stack_t* cat_stacks(stack_t** stack_1, stack_t** stack_2)
{
  stack_t* stack_3 = new_stack();
  stack_item_t* item;

  //pegar todos os elementos da stack 2
  item = (*stack_2)->data;
  do {
    if (item && item->value) {
      stack_push(copy_tac(item->value), stack_3);
      item = item->next;
    }
  } while (item != NULL);

  //pegar todos os elementos da stack 1
  item = (*stack_1)->data;
  do {
    if (item && item->value) {
      stack_push(copy_tac(item->value), stack_3);
      item = item->next;
    }
  } while (item != NULL);

  reverse_stack(&stack_3);

  return stack_3;
}

void tac_stack_test_2()
{
  int opcode;
  tac_t* tac;
  char* code;
  stack_t* stack_1 = new_stack();
  stack_t* stack_2 = new_stack();

  printf("____ inserções ____\n");

  //preencher stack 1
  for (opcode = OP_ADD; opcode <= OP_DIV; opcode++) {
    char* reg_1 = new_register();
    char* reg_2 = new_register();
    char* reg_3 = new_register();

    tac = new_tac(opcode, reg_1, reg_2, reg_3, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);
    stack_push(tac, stack_1);

    free(reg_1);
    free(reg_2);
    free(reg_3);
    free(code);
  }

  stack_t* stack_3 = cat_stacks(&stack_1, &stack_2);

  printf("\n\n____ stack_1 ____\n");
  print_tac_stack(&stack_1);

  printf("\n\n____ stack_2 ____\n");
  print_tac_stack(&stack_2);

  printf("\n\n____ stack_3 ____\n");
  print_tac_stack(&stack_3);

  clear_tac_stack(&stack_1);
  clear_tac_stack(&stack_2);
  clear_tac_stack(&stack_3);
  free_stack(stack_1);
  free_stack(stack_2);
  free_stack(stack_3);

  printf("\nFim do teste 2!\n\n");
}

void tac_stack_test()
{
  stack_t* stack_1 = new_stack();
  stack_t* stack_2 = new_stack();

  int opcode = 0;
  tac_t* tac;
  char* code;

  printf("____ inserções ____\n");

  //preencher stack 1
  for (opcode = OP_ADD; opcode <= OP_DIV; opcode++) {
    char* reg_1 = new_register();
    char* reg_2 = new_register();
    char* reg_3 = new_register();

    tac = new_tac(opcode, reg_1, reg_2, reg_3, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);
    stack_push(tac, stack_1);

    free(reg_1);
    free(reg_2);
    free(reg_3);
    free(code);
  }

  //preencher stack 2
  for (opcode = OP_ADD_I; opcode <= OP_RDIV_I; opcode++) {
    char* reg_1 = new_register();
    char* imed = new_imediate(42);
    char* reg_2 = new_register();

    tac = new_tac(opcode, reg_1, imed, reg_2, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);
    stack_push(tac, stack_2);

    free(reg_1);
    free(imed);
    free(reg_2);
    free(code);
  }

  stack_t* stack_3 = cat_stacks(&stack_1, &stack_2);

  printf("\n\n____ stack_1 ____\n");
  print_tac_stack(&stack_1);

  printf("\n\n____ stack_2 ____\n");
  print_tac_stack(&stack_2);

  printf("\n\n____ stack_3 ____\n");
  print_tac_stack(&stack_3);

  printf("\nFim do teste 1!\n\n");
  clear_tac_stack(&stack_1);
  clear_tac_stack(&stack_2);
  clear_tac_stack(&stack_3);
  free_stack(stack_1);
  free_stack(stack_2);
  free_stack(stack_3);

  tac_stack_test_2();
}