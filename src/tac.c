/**
 * Arquivo com funções de tratamento de TAC (three adresses code)
 */

#include "cc_list.h"
#include "tac.h"
#include <math.h>
#include <cc_ast.h>
#include <semantics.h>

tac_t* new_tac(char* label, int opcode, char* src_1, char* src_2, char* dst_1, char* dst_2)
{
  tac_t* tac = (tac_t*) malloc(sizeof(tac_t));

  tac->label = label ? strdup(label) : NULL;
  tac->opcode = opcode;
  tac->src_1 = src_1 ? strdup(src_1) : NULL;
  tac->src_2 = src_2 ? strdup(src_2) : NULL;
  tac->dst_1 = dst_1 ? strdup(dst_1) : NULL;
  tac->dst_2 = dst_2 ? strdup(dst_2) : NULL;

  return tac;
}

void destroy_tac(tac_t* tac)
{
  if (tac->label) free(tac->label);
  if (tac->src_1) free(tac->src_1);
  if (tac->src_2) free(tac->src_2);
  if (tac->dst_1) free(tac->dst_1);
  if (tac->dst_2) free(tac->dst_2);
  free(tac);
}

tac_t* copy_tac(tac_t* copied)
{
  return new_tac(copied->label, copied->opcode, copied->src_1, copied->src_2, copied->dst_1, copied->dst_2);
}

void create_and_destroy_tac_test()
{
  char* reg_1 = new_register();
  char* reg_2 = new_register();
  char* reg_3 = new_register();
  tac_t* tac = new_tac(NULL, OP_ADD, reg_1, reg_2, reg_3, NULL);
  destroy_tac(tac);
  free(reg_1);
  free(reg_2);
  free(reg_3);
}

//construtores praticos

void new_tac_ssed_test()
{
  char* code;
  tac_t* tac;

  //teste sem nada
  tac= new_tac_ssed(false, NULL, OP_ADD, NULL, NULL, NULL);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  //teste com label
  tac = new_tac_ssed(true, NULL, OP_ADD, NULL, NULL, NULL);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  tac = new_tac_ssed(true, "l42", OP_ADD, NULL, NULL, NULL);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  //teste com registradores (com e sem label)
  char* reg_1 = new_register();
  char* reg_2 = new_register();
  char* reg_3 = new_register();
  tac = new_tac_ssed(false, NULL, OP_ADD, reg_1, reg_2, reg_3);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  //teste com imediato
  char* imed = new_imediate(42);
  tac = new_tac_ssed(false, NULL, OP_ADD_I, reg_1, imed, reg_3);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  free(reg_1); free(reg_2); free(reg_3); free(imed);
}
void new_tac_sed_test()
{
  char* code;
  tac_t* tac;

  //teste sem nada
  tac = new_tac_sed(false, NULL, OP_I2I, NULL, NULL);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  //teste com label
  tac = new_tac_sed(true, NULL, OP_I2I, NULL, NULL);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  tac = new_tac_sed(true, "l42", OP_I2I, NULL, NULL);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  //teste com registradores
  char* reg_1 = new_register();
  char* reg_2 = new_register();
  tac = new_tac_sed(false, NULL, OP_I2I, reg_1, reg_2);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  //teste com imediato
  char* imed = new_imediate(42);
  tac = new_tac_sed(false, NULL, OP_LOAD_I, imed, reg_2);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  free(imed); free(reg_1); free(reg_2);
}
void new_tac_sedd_test()
{
  char* code;
  tac_t* tac;

  //teste sem nada
  tac = new_tac_sedd(false, NULL, OP_STORE_A0, NULL, NULL, NULL);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  //teste com label
  tac = new_tac_sedd(true, NULL, OP_STORE_A0, NULL, NULL, NULL);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  tac = new_tac_sedd(true, "l42", OP_STORE_A0, NULL, NULL, NULL);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  //teste com registradores
  char* reg_1 = new_register();
  char* reg_2 = new_register();
  char* reg_3 = new_register();
  tac = new_tac_sedd(false, NULL, OP_STORE_A0, reg_1, reg_2, reg_3);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  //teste com imediato
  char* imed = new_imediate(42);
  tac = new_tac_sedd(false, NULL, OP_STORE_AI, reg_1, reg_2, imed);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);


  free(reg_1); free(reg_2); free(reg_3); free(imed);
}

void new_tac_jump_test()
{
  char* code;
  tac_t* tac;

  //teste sem nada
  tac = new_tac_jump(false, NULL, NULL);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  //teste com label
  tac = new_tac_jump(true, NULL, NULL);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  tac = new_tac_jump(true, "l42", NULL);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  //teste com registrador
  char* reg = new_register();
  tac = new_tac_jump_i(true, "l42", reg);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  free(reg);
}
void new_tac_jump_i_test()
{
  char* code;
  tac_t* tac;

  //teste sem nada
  tac = new_tac_jump_i(false, NULL, NULL);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  //teste com label
  tac = new_tac_jump_i(true, NULL, NULL);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  tac = new_tac_jump_i(true, "l42", NULL);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  //teste com label
  tac = new_tac_jump_i(true, "l42", "l43");
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);
}
void new_tac_cbr_test()
{
  char* code;
  tac_t* tac;

  //teste sem nada
  tac = new_tac_cbr(false, NULL, NULL, NULL, NULL);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  //teste com label
  tac = new_tac_cbr(true, NULL, NULL, NULL, NULL);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  tac = new_tac_cbr(true, "l42", NULL, NULL, NULL);
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  //teste com registradores
  char* reg = new_register();
  tac = new_tac_cbr(false, NULL, reg, "l42", "l43");
  code = tac_to_string(tac); printf("%s\n", code); free(code);
  destroy_tac(tac);

  free(reg);
}
void custom_constructors_tests()
{
  printf("\nnew_tac_ssed_test: \n");
  new_tac_ssed_test();
  printf("\nnew_tac_sed_test: \n");
  new_tac_sed_test();
  printf("\nnew_tac_sedd_test: \n");
  new_tac_sedd_test();
  printf("\nnew_tac_jump_i_test:\n");
  new_tac_jump_i_test();
  printf("\nnew_tac_jump_test:\n");
  new_tac_jump_test();
  printf("\nnew_tac_cbr_test:\n");
  new_tac_cbr_test();
  printf("\nFim de custom_constructors_tests().\n\n");
}

tac_t* new_tac_ssed(bool use_label, char* label, int opcode, char* src_1, char* src_2, char* dst) {
  char* lbl;
  if (use_label) {
    lbl = label ? label : new_label();
  } else {
    lbl = NULL;
  }

  //se parametros sao NULL, chamador da funcao quer que crie novos registradores
  char* s1 = src_1 ? src_1 : new_register();
  char* s2 = src_2 ? src_2 : new_register();
  char* s3 = dst   ?   dst : new_register();

  tac_t* tac = new_tac(lbl, opcode, s1, s2, s3, NULL);

  //depois de construtor coletar dados, pode liberar memoria alocada
  if (!src_1) free(s1);
  if (!src_2) free(s2);
  if (!dst)   free(s3);
  if (use_label && (label == NULL)) free(lbl);

  return tac;
}
tac_t* new_tac_sed(bool use_label, char* label, int opcode, char* src, char* dst) {
  char* lbl;
  if (use_label) {
    lbl = label ? label : new_label();
  } else {
    lbl = NULL;
  }

  //se parametros sao NULL, chamador da funcao quer que crie novos registradores
  char* s = src ? src : new_register();
  char* d = dst  ? dst  : new_register();

  tac_t* tac = new_tac(lbl, opcode, s, NULL, d, NULL);

  //depois de construtor coletar dados, pode liberar memoria alocada
  if (!src) free(s);
  if (!dst)   free(d);
  if (use_label && (label == NULL)) free(lbl);

  return tac;
}
tac_t* new_tac_sedd(bool use_label, char* label, int opcode, char* src, char* dst_1, char* dst_2) {
  char* lbl;
  if (use_label) {
    lbl = label ? label : new_label();
  } else {
    lbl = NULL;
  }

  //se parametros sao NULL, chamador da funcao quer que crie novos registradores
  char* s = src ? src : new_register();
  char* d1 = dst_1 ? dst_1 : new_register();
  char* d2 = dst_2 ? dst_2 : new_register();

  tac_t* tac = new_tac(lbl, opcode, s, NULL, d1, d2);

  //depois de construtor coletar dados, pode liberar memoria alocada
  if (!src)   free(s);
  if (!dst_1) free(d1);
  if (!dst_2) free(d2);
  if (use_label && (label == NULL)) free(lbl);

  return tac;
}
tac_t* new_tac_jump_i(bool use_label, char* label, char* dst_label) {
  char* lbl;
  if (use_label) {
    lbl = label ? label : new_label();
  } else {
    lbl = NULL;
  }

  //se dst_label é NULL, chamador da funcao quer que crie novo label
  char* d_label = dst_label ? dst_label : new_label();

  tac_t* tac = new_tac(lbl, OP_JUMP_I, NULL, NULL, d_label, NULL);

  //depois de construtor coletar dados, pode liberar memoria alocada
  if (!dst_label) free(d_label);
  if (use_label && (label == NULL)) free(lbl);

  return tac;
}
tac_t* new_tac_jump(bool use_label, char* label, char* dst_reg) {
  char* lbl;
  if (use_label) {
    lbl = label ? label : new_label();
  } else {
    lbl = NULL;
  }

  //se dst_reg é NULL, chamador da funcao quer que crie novo registrador
  char* d_reg = dst_reg ? dst_reg : new_register();

  tac_t* tac = new_tac(lbl, OP_JUMP_I, NULL, NULL, d_reg, NULL);

  //depois de construtor coletar dados, pode liberar memoria alocada
  if (!dst_reg) free(d_reg);
  if (use_label && (label == NULL)) free(lbl);

  return tac;
}

tac_t* new_tac_nop(bool use_label, char *label) {
  char* lbl;
  if (use_label) {
    lbl = label ? label : new_label();
  } else {
    lbl = NULL;
  }
  return new_tac(lbl, OP_NOP, NULL, NULL, NULL, NULL);
}

tac_t* new_tac_cbr  (bool use_label, char* label, char* src, char* lbl_true, char* lbl_false) {
  char* lbl;
  if (use_label) {
    lbl = label ? label : new_label();
  } else {
    lbl = NULL;
  }

  //se parametros sao NULL, chamador da funcao quer que crie novos registradores
  char* s = src ? src : new_register();
  char* d1 = lbl_true ? lbl_true : new_label();
  char* d2 = lbl_false ? lbl_false : new_label();

  tac_t* tac = new_tac(lbl, OP_CBR, s, NULL, d1, d2);

  //depois de construtor coletar dados, pode liberar memoria alocada
  if (!src)   free(s);
  if (!lbl_true) free(d1);
  if (!lbl_false) free(d2);
  if (use_label && (label == NULL)) free(lbl);

  return tac;
}

//registradores, labels e imediatos

char* base_register_name(int base_register)
{
  if (base_register == RBSS) return strdup("rbss");
  else if (base_register == RARP) return strdup("rarp");
}

void base_register_test()
{
  char* reg = base_register_name(RBSS);
  printf("register_name(RBSS) = %s\n", reg);
  free(reg);

  reg = base_register_name(RARP);
  printf("register_name(RARP) = %s\n", reg);
  free(reg);
}

char* new_label()
{
  size_t number_of_digits = (size_t) floor(log(label_counter) + 1);

  char* label_name = (char*) malloc((sizeof(char) * (1/*para o 'l'*/ + number_of_digits + 1/*para o '\0'*/)));
  sprintf(label_name, "l%d", label_counter);

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
  for (i = 0; i < 201; i++)
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

//codigo em string

char* tac_to_string(tac_t* tac)
{
  size_t code_size_in_bytes;
  char* code;
  size_t label_size;
  char* label;

  if (tac->label) {
    label_size = strlen(tac->label) + strlen(": ");
    label = malloc(label_size + 1/*para o '\0*/);
    sprintf(label, "%s: ", tac->label);
  } else {
    label_size = 0;
    label = "";
  }

  switch (tac->opcode) {

    case OP_NOP:
      code_size_in_bytes =
              (label_size +
              strlen("nop") +
              1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%snop", label);
      break;

    //aritmetica
    case OP_ADD:
      code_size_in_bytes =
          (label_size +
          strlen("add ") +
          strlen(tac->src_1) +
          strlen(", ") +
          strlen(tac->src_2) +
          strlen(" => ") +
          strlen(tac->dst_1) +
          1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%sadd %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_SUB:
      code_size_in_bytes =
          (label_size +
          strlen("sub ") +
          strlen(tac->src_1) +
          strlen(", ") +
          strlen(tac->src_2) +
          strlen(" => ") +
          strlen(tac->dst_1) +
          1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%ssub %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_MULT:
      code_size_in_bytes =
          (label_size +
          strlen("mult ") +
          strlen(tac->src_1) +
          strlen(", ") +
          strlen(tac->src_2) +
          strlen(" => ") +
          strlen(tac->dst_1) +
          1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%smult %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_DIV:
      code_size_in_bytes =
          (label_size +
          strlen("div ") +
          strlen(tac->src_1) +
          strlen(", ") +
          strlen(tac->src_2) +
          strlen(" => ") +
          strlen(tac->dst_1) +
          1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%sdiv %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_ADD_I:
      code_size_in_bytes =
          (label_size +
          strlen("addI ") +
          strlen(tac->src_1) +
          strlen(", ") +
          strlen(tac->src_2) +
          strlen(" => ") +
          strlen(tac->dst_1) +
          1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%saddI %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_SUB_I:
      code_size_in_bytes =
          (label_size +
          strlen("subI ") +
          strlen(tac->src_1) +
          strlen(", ") +
          strlen(tac->src_2) +
          strlen(" => ") +
          strlen(tac->dst_1) +
          1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%ssubI %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_RSUB_I:
      code_size_in_bytes =
          (label_size +
          strlen("rsubI ") +
          strlen(tac->src_1) +
          strlen(", ") +
          strlen(tac->src_2) +
          strlen(" => ") +
          strlen(tac->dst_1) +
          1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%srsubI %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_MULT_I:
      code_size_in_bytes =
          (label_size +
          strlen("multI ") +
          strlen(tac->src_1) +
          strlen(", ") +
          strlen(tac->src_2) +
          strlen(" => ") +
          strlen(tac->dst_1) +
          1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%smultI %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_DIV_I:
      code_size_in_bytes =
          (label_size +
          strlen("divI ") +
          strlen(tac->src_1) +
          strlen(", ") +
          strlen(tac->src_2) +
          strlen(" => ") +
          strlen(tac->dst_1) +
          1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%sdivI %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_RDIV_I:
      code_size_in_bytes =
          (label_size +
          strlen("rdivI ") +
          strlen(tac->src_1) +
          strlen(", ") +
          strlen(tac->src_2) +
          strlen(" => ") +
          strlen(tac->dst_1) +
          1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%srdivI %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

     //shifts
     case OP_LSHIFT:
       code_size_in_bytes =
               (label_size +
                strlen("lshift ") +
                strlen(tac->src_1) +
                strlen(", ") +
                strlen(tac->src_2) +
                strlen(" => ") +
                strlen(tac->dst_1) +
                1 /*para o \0*/) * sizeof(char);

        code = malloc(code_size_in_bytes);
        sprintf(code, "%slshift %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
        break;

      case OP_LSHIFT_I:
        code_size_in_bytes =
                (label_size +
                 strlen("lshiftI ") +
                 strlen(tac->src_1) +
                 strlen(", ") +
                 strlen(tac->src_2) +
                 strlen(" => ") +
                 strlen(tac->dst_1) +
                 1 /*para o \0*/) * sizeof(char);

        code = malloc(code_size_in_bytes);
        sprintf(code, "%slshiftI %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
        break;

     case OP_RSHIFT:
       code_size_in_bytes =
               (label_size +
                strlen("rshift ") +
                strlen(tac->src_1) +
                strlen(", ") +
                strlen(tac->src_2) +
                strlen(" => ") +
                strlen(tac->dst_1) +
                1 /*para o \0*/) * sizeof(char);

        code = malloc(code_size_in_bytes);
        sprintf(code, "%srshift %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
        break;

      case OP_RSHIFT_I:
        code_size_in_bytes =
                (label_size +
                 strlen("rshiftI ") +
                 strlen(tac->src_1) +
                 strlen(", ") +
                 strlen(tac->src_2) +
                 strlen(" => ") +
                 strlen(tac->dst_1) +
                 1 /*para o \0*/) * sizeof(char);

        code = malloc(code_size_in_bytes);
        sprintf(code, "%srshiftI %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
        break;


    //logicos
    case OP_AND:
      code_size_in_bytes =
              (label_size +
               strlen("and ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%sand %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_AND_I:
      code_size_in_bytes =
              (label_size +
               strlen("andI ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%sandI %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_OR:
      code_size_in_bytes =
              (label_size +
               strlen("or ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%sor %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_OR_I:
      code_size_in_bytes =
              (label_size +
               strlen("orI ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%sorI %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_XOR:
      code_size_in_bytes =
              (label_size +
               strlen("xor ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%sxor %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_XOR_I:
      code_size_in_bytes =
              (label_size +
               strlen("xorI ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%sxorI %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    //memoria - leitura
    case OP_LOAD:
      code_size_in_bytes =
              (label_size +
               strlen("load ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%sload %s => %s", label, tac->src_1, tac->dst_1);
      break;

    case OP_LOAD_AI:
      code_size_in_bytes =
              (label_size +
               strlen("loadAI ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%sloadAI %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_LOAD_A0:
      code_size_in_bytes =
              (label_size +
               strlen("loadAO ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%sloadAO %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_CLOAD:
      code_size_in_bytes =
              (label_size +
               strlen("cload ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%scload %s => %s", label, tac->src_1, tac->dst_1);
      break;

    case OP_CLOAD_AI:
      code_size_in_bytes =
              (label_size +
               strlen("cloadAI ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%scloadAI %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

     case OP_CLOAD_A0:
       code_size_in_bytes =
               (label_size +
                strlen("cloadAO ") +
                strlen(tac->src_1) +
                strlen(", ") +
                strlen(tac->src_2) +
                strlen(" => ") +
                strlen(tac->dst_1) +
                1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%scloadAO %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_LOAD_I:
      code_size_in_bytes =
              (label_size +
               strlen("loadI ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%sloadI %s => %s", label, tac->src_1, tac->dst_1);
      break;


     //memoria - escrita
     case OP_STORE:
       code_size_in_bytes =
               (label_size +
                strlen("store ") +
                strlen(tac->src_1) +
                strlen(" => ") +
                strlen(tac->dst_1) +
                1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%sstore %s => %s", label, tac->src_1, tac->dst_1);
      break;

    case OP_STORE_AI:
      code_size_in_bytes =
              (label_size +
               strlen("storeAI ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               strlen(", ") +
               strlen(tac->dst_2) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%sstoreAI %s => %s, %s", label, tac->src_1, tac->dst_1, tac->dst_2);
      break;

    case OP_STORE_A0:
      code_size_in_bytes =
              (label_size +
               strlen("storeAO ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               strlen(", ") +
               strlen(tac->dst_2) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%sstoreAO %s => %s, %s", label, tac->src_1, tac->dst_1, tac->dst_2);
      break;

    case OP_CSTORE:
      code_size_in_bytes =
              (label_size +
               strlen("cstore ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%scstore %s => %s", label, tac->src_1, tac->dst_1);
      break;

    case OP_CSTORE_AI:
      code_size_in_bytes =
              (label_size +
               strlen("cstoreAI ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               strlen(", ") +
               strlen(tac->dst_2) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%scstoreAI %s => %s, %s", label, tac->src_1, tac->dst_1, tac->dst_2);
      break;

    case OP_CSTORE_A0:
      code_size_in_bytes =
              (label_size +
               strlen("cstoreAO ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               strlen(", ") +
               strlen(tac->dst_2) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%scstoreAO %s => %s, %s", label, tac->src_1, tac->dst_1, tac->dst_2);
      break;


     //copia entre registradores
     case OP_I2I:
       code_size_in_bytes =
               (label_size +
                strlen("i2i ") +
                strlen(tac->src_1) +
                strlen(" => ") +
                strlen(tac->dst_1) +
                1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%si2i %s => %s", label, tac->src_1, tac->dst_1);
      break;

    case OP_C2C:
      code_size_in_bytes =
              (label_size +
               strlen("c2c ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%sc2c %s => %s", label, tac->src_1, tac->dst_1);
      break;

    case OP_C2I:
      code_size_in_bytes =
              (label_size +
               strlen("c2i ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%sc2i %s => %s", label, tac->src_1, tac->dst_1);
      break;

    case OP_I2C:
      code_size_in_bytes =
              (label_size +
               strlen("i2c ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%si2c %s => %s", label, tac->src_1, tac->dst_1);
      break;


    //controle de fluxo
     case OP_CMP_LT:
       code_size_in_bytes =
               (label_size +
                strlen("cmp_LT ") +
                strlen(tac->src_1) +
                strlen(", ") +
                strlen(tac->src_2) +
                strlen(" -> ") +
                strlen(tac->dst_1) +
                1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%scmp_LT %s, %s -> %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_CMP_LE:
      code_size_in_bytes =
              (label_size +
               strlen("cmp_LE ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" -> ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%scmp_LE %s, %s -> %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_CMP_EQ:
      code_size_in_bytes =
              (label_size +
               strlen("cmp_EQ ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" -> ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%scmp_EQ %s, %s -> %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_CMP_GE:
      code_size_in_bytes =
              (label_size +
               strlen("cmp_GE ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" -> ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%scmp_GE %s, %s -> %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_CMP_GT:
      code_size_in_bytes =
              (label_size +
               strlen("cmp_GT ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" -> ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%scmp_GT %s, %s -> %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_CMP_NE:
      code_size_in_bytes =
              (label_size +
               strlen("cmp_NE ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" -> ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%scmp_NE %s, %s -> %s", label, tac->src_1, tac->src_2, tac->dst_1);
      break;

    case OP_CBR:
      code_size_in_bytes =
              (label_size +
               strlen("cbr ") +
               strlen(tac->src_1) +
               strlen(" -> ") +
               strlen(tac->dst_1) +
               strlen(", ") +
               strlen(tac->dst_2) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%scbr %s -> %s, %s", label, tac->src_1, tac->dst_1, tac->dst_2);
      break;


     //saltos
     case OP_JUMP_I:
       code_size_in_bytes =
               (label_size +
                strlen("jumpI") +
                strlen(" -> ") +
                strlen(tac->dst_1) +
                1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%sjumpI -> %s", label, tac->dst_1);
      break;

    case OP_JUMP:
      code_size_in_bytes =
              (label_size +
               strlen("jump") +
               strlen(" -> ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%sjump -> %s", label, tac->dst_1);
      break;


    default:
      printf("Opcode de tac_t deve ser uma das constantes OP_* de tac.h\n");
      exit(EXIT_FAILURE);
      return NULL;
  }
  if (tac->label) free(label);
  return code;
}

void tac_to_string_nop_test(bool use_label)
{
  int opcode = 0;
  tac_t* tac;
  char* code;
  char* label = use_label ? new_label() : NULL;

  tac = new_tac(label, opcode, NULL, NULL, NULL, NULL);
  code = tac_to_string(tac);
  printf("%s\n", code);

  destroy_tac(tac);
  free(code);
  if (use_label)  free(label);
}

void tac_to_string_arit_test(bool use_label)
{
  int opcode = 0;
  tac_t* tac;
  char* code;

  //aritmetica
  for (opcode = OP_ADD; opcode <= OP_DIV; opcode++) {

    char* label = use_label ? new_label() : NULL;
    char* reg_1 = new_register();
    char* reg_2 = new_register();
    char* reg_3 = new_register();

    tac = new_tac(label, opcode, reg_1, reg_2, reg_3, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(reg_2);
    free(reg_3);
    destroy_tac(tac);
    free(code);
    if (use_label) free(label);
  }
  for (opcode = OP_ADD_I; opcode <= OP_RDIV_I; opcode++) {

    char* label = use_label ? new_label() : NULL;
    char* reg_1 = new_register();
    char* imed = new_imediate(42);
    char* reg_2 = new_register();

    tac = new_tac(label, opcode, reg_1, imed, reg_2, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(imed);
    free(reg_2);
    destroy_tac(tac);
    free(code);
    if (use_label) free(label);
  }
}

void tac_to_string_shifts_test(bool use_label)
{
  int i;
  int opcode = 0;
  tac_t* tac;
  char* code;

  for (i = 0; i < 2; ++i) {
    if      (i == 0) opcode = OP_LSHIFT;
    else if (i == 1) opcode = OP_RSHIFT;

    char* label = use_label ? new_label() : NULL;
    char* reg_1 = new_register();
    char* reg_2 = new_register();
    char* reg_3 = new_register();

    tac = new_tac(label, opcode, reg_1, reg_2, reg_3, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(reg_2);
    free(reg_3);
    destroy_tac(tac);
    free(code);
    if (use_label) free(label);
  }
  for (i = 0; i < 2; ++i) {
    if      (i == 0) opcode = OP_LSHIFT_I;
    else if (i == 1) opcode = OP_RSHIFT_I;

    char* label = use_label ? new_label() : NULL;
    char* reg_1 = new_register();
    char* imed = new_imediate(42);
    char* reg_2 = new_register();

    tac = new_tac(label, opcode, reg_1, imed, reg_2, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(imed);
    free(reg_2);
    destroy_tac(tac);
    free(code);
    if (use_label) free(label);
  }
}

void tac_to_string_logics_test(bool use_label)
{
  int i;
  int opcode = 0;
  tac_t* tac;
  char* code;

  for (i = 0; i < 3; i++) {

    if (i == 0) opcode = OP_AND;
    else if (i == 1) opcode = OP_OR;
    else if (i == 2) opcode = OP_XOR;

    char* label = use_label ? new_label() : NULL;
    char* reg_1 = new_register();
    char* reg_2 = new_register();
    char* reg_3 = new_register();

    tac = new_tac(label, opcode, reg_1, reg_2, reg_3, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(reg_2);
    free(reg_3);
    destroy_tac(tac);
    free(code);
    if (use_label) free(label);
  }
  for (i = 0; i < 3; i++) {

    if (i == 0) opcode = OP_AND_I;
    else if (i == 1) opcode = OP_OR_I;
    else if (i == 2) opcode = OP_XOR_I;

    char* label = use_label ? new_label() : NULL;
    char* reg_1 = new_register();
    char* imed = new_imediate(42);
    char* reg_3 = new_register();

    tac = new_tac(label, opcode, reg_1, imed, reg_3, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(imed);
    free(reg_3);
    destroy_tac(tac);
    free(code);
    if (use_label) free(label);
  }
}

void tac_to_string_loads_test(bool use_label)
{
  int i;
  int opcode = 0;
  tac_t *tac;
  char *code;

  for (i = 0; i < 2; ++i) {
    if (i == 0) opcode = OP_LOAD;
    else if (i == 1) opcode = OP_CLOAD;

    char* label = use_label ? new_label() : NULL;
    char *reg_1 = new_register();
    char *reg_2 = new_register();

    tac = new_tac(label, opcode, reg_1, NULL, reg_2, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(reg_2);
    destroy_tac(tac);
    free(code);
    if (use_label) free(label);
  }
  for (i = 0; i < 2; ++i) {
    if (i == 0) opcode = OP_LOAD_AI;
    else if (i == 1) opcode = OP_CLOAD_AI;

    char* label = use_label ? new_label() : NULL;
    char *reg_1 = new_register();
    char *imed = new_imediate(42);
    char *reg_2 = new_register();

    tac = new_tac(label, opcode, reg_1, imed, reg_2, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(imed);
    free(reg_2);
    destroy_tac(tac);
    free(code);
    if (use_label) free(label);
  }
  for (i = 0; i < 2; ++i) {
    if (i == 0) opcode = OP_LOAD_A0;
    else if (i == 1) opcode = OP_CLOAD_A0;

    char* label = use_label ? new_label() : NULL;
    char *reg_1 = new_register();
    char *reg_2 = new_register();
    char *reg_3 = new_register();

    tac = new_tac(label, opcode, reg_1, reg_2, reg_3, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(reg_2);
    free(reg_3);
    destroy_tac(tac);
    free(code);
    if (use_label) free(label);
  }

  {
    opcode = OP_LOAD_I;

    char* label = use_label ? new_label() : NULL;
    char *reg_1 = new_register();
    char *reg_2 = new_register();

    tac = new_tac(label, opcode, reg_1, NULL, reg_2, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(reg_2);
    destroy_tac(tac);
    free(code);
    if (use_label) free(label);
  }
}

void tac_to_string_stores_test(bool use_label)
{
  int i;
  int opcode = 0;
  tac_t *tac;
  char *code;

  for (i = 0; i < 2; ++i) {
    if (i == 0) opcode = OP_STORE;
    else if (i == 1) opcode = OP_CSTORE;

    char* label = use_label ? new_label() : NULL;
    char *reg_1 = new_register();
    char *reg_2 = new_register();

    tac = new_tac(label, opcode, reg_1, NULL, reg_2, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(reg_2);
    destroy_tac(tac);
    free(code);
    if (use_label) free(label);
  }
  for (i = 0; i < 2; ++i) {
    if (i == 0) opcode = OP_STORE_AI;
    else if (i == 1) opcode = OP_CSTORE_AI;

    char* label = use_label ? new_label() : NULL;
    char *reg_1 = new_register();
    char *imed = new_imediate(42);
    char *reg_2 = new_register();

    tac = new_tac(label, opcode, reg_1, NULL, reg_2, imed);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(imed);
    free(reg_2);
    destroy_tac(tac);
    free(code);
    if (use_label) free(label);
  }
  for (i = 0; i < 2; ++i) {
    if (i == 0) opcode = OP_STORE_A0;
    else if (i == 1) opcode = OP_CSTORE_A0;

    char* label = use_label ? new_label() : NULL;
    char *reg_1 = new_register();
    char *reg_2 = new_register();
    char *reg_3 = new_register();

    tac = new_tac(label, opcode, reg_1, NULL, reg_2, reg_3);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(reg_2);
    free(reg_3);
    destroy_tac(tac);
    free(code);
    if (use_label) free(label);
  }
}

void tac_to_string_reg_copy_test(bool use_label)
{
  int opcode = 0;
  tac_t *tac;
  char *code;

  for (opcode = OP_I2I; opcode <= OP_I2C; ++opcode) {

    char* label = use_label ? new_label() : NULL;
    char *reg_1 = new_register();
    char *reg_2 = new_register();

    tac = new_tac(label, opcode, reg_1, NULL, reg_2, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(reg_2);
    destroy_tac(tac);
    free(code);
    if (use_label) free(label);
  }
}

void tac_to_string_flux_control_test(bool use_label)
{
  int opcode = 0;
  tac_t* tac;
  char* code;

  for (opcode = OP_CMP_LT; opcode <= OP_CMP_NE; opcode++) {

    char* label = use_label ? new_label() : NULL;
    char* reg_1 = new_register();
    char* reg_2 = new_register();
    char* reg_3 = new_register();

    tac = new_tac(label, opcode, reg_1, reg_2, reg_3, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(reg_2);
    free(reg_3);
    destroy_tac(tac);
    free(code);
    if (use_label) free(label);
  }
  {
    opcode = OP_CBR;

    char* label = use_label ? new_label() : NULL;
    char* reg_1 = new_register();
    char* label_1 = new_label();
    char* label_2 = new_label();

    tac = new_tac(label, opcode, reg_1, NULL, label_1, label_2);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg_1);
    free(label_1);
    free(label_2);
    destroy_tac(tac);
    free(code);
    if (use_label) free(label);
  }
}

void tac_to_string_jumps_test(bool use_label)
{
  int opcode = 0;
  tac_t* tac;
  char* code;

  {
    opcode = OP_JUMP_I;

    char* label_1 = use_label ? new_label() : NULL;
    char* label_2 = new_label();

    tac = new_tac(label_1, opcode, NULL, NULL, label_2, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(label_2);
    destroy_tac(tac);
    free(code);
    if (use_label) free(label_1);
  }
  {
    opcode = OP_JUMP;

    char* label = use_label ? new_label() : NULL;
    char* reg = new_register();

    tac = new_tac(label, opcode, NULL, NULL, reg, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);

    free(reg);
    destroy_tac(tac);
    free(code);
    if (use_label) free(label);
  }
}

void tac_to_string_test()
{
  int i;
  bool use_label;
  for (i = 0; i < 2; ++i) {

    if (i == 0) use_label = true;
    if (i == 1) use_label = false;

    printf("\n____  Nop  ____\n");
    tac_to_string_nop_test(use_label);
    printf("\n____  Arits  ____\n");
    tac_to_string_arit_test(use_label);
    printf("\n____  Shifts  ____\n");
    tac_to_string_shifts_test(use_label);
    printf("\n____  Logics  ____\n");
    tac_to_string_logics_test(use_label);
    printf("\n____  Loads  ____\n");
    tac_to_string_loads_test(use_label);
    printf("\n____  Stores  ____\n");
    tac_to_string_stores_test(use_label);
    printf("\n____  RegCopies  ____\n");
    tac_to_string_reg_copy_test(use_label);
    printf("\n____  FluxCtrl  ____\n");
    tac_to_string_flux_control_test(use_label);
    printf("\n____  Jumps  ____\n");
    tac_to_string_jumps_test(use_label);
  }
}

void tac_basic_tests()
{
  base_register_test();
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

void print_tac_stack(stack_t** stack)
{
  tac_t* tac;
  stack_item_t* item = (*stack)->data;

  printf("\nTOPO\n");
  while (item) {
    tac = item->value;
    if (tac) {
      char *code = tac_to_string(tac);
      printf("%s\n", code);
      free(code);
    }
    item = item->next;
  }
  printf("FUNDO\n\n");
}

void print_tac_stack_clean(stack_t** stack)
{
  tac_t* tac;
  stack_item_t* item = (*stack)->data;

  while (item) {
    tac = item->value;
    if (tac) {
      char *code = tac_to_string(tac);
      printf("%s\n", code);
      free(code);
    }
    item = item->next;
  }
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

    tac = new_tac(NULL, opcode, reg_1, reg_2, reg_3, NULL);
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

    tac = new_tac(NULL, opcode, reg_1, reg_2, reg_3, NULL);
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

    tac = new_tac(NULL, opcode, reg_1, imed, reg_2, NULL);
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

void tac_stack_test_3()
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

    tac = new_tac(NULL, opcode, reg_1, reg_2, reg_3, NULL);
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

    tac = new_tac(NULL, opcode, reg_1, imed, reg_2, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);
    stack_push(tac, stack_2);

    free(reg_1);
    free(imed);
    free(reg_2);
    free(code);
  }

  stack_t* stack_3 = new_stack();
  stack_push_all_tacs(stack_3, stack_1);
  stack_push(new_tac_jump_i(true, "l_middle", "l_end"), stack_3);
  stack_push_all_tacs(stack_3, stack_2);

  printf("\n\n____ stack_1 ____\n");
  print_tac_stack(&stack_1);

  printf("\n\n____ stack_2 ____\n");
  print_tac_stack(&stack_2);

  printf("\n\n____ stack_3 ____\n");
  reverse_stack(&stack_3);
  print_tac_stack(&stack_3);

  printf("\nFim do teste 3!\n\n");
  clear_tac_stack(&stack_1);
  clear_tac_stack(&stack_2);
  clear_tac_stack(&stack_3);
  free_stack(stack_1);
  free_stack(stack_2);
  free_stack(stack_3);
}

stack_t* reversed_tac_stack(stack_t* stack)
{
  stack_t* reversed = new_stack();
  stack_item_t* item = stack->data;

  while (item) {
    stack_push(copy_tac(item->value), reversed);
    item = item->next;
  }

  return reversed;
}

void reversed_stack_test()
{
  stack_t* stack = new_stack();

  tac_t* tac;
  char* code;
  int opcode;
  printf("\ninsercoes:\n");
  for (opcode = OP_ADD_I; opcode <= OP_RDIV_I; opcode++) {
    char* reg_1 = new_register();
    char* imed = new_imediate(42);
    char* reg_2 = new_register();

    tac = new_tac(NULL, opcode, reg_1, imed, reg_2, NULL);
    code = tac_to_string(tac);
    printf("%s\n", code);
    stack_push(tac, stack);

    free(reg_1);
    free(imed);
    free(reg_2);
    free(code);
  }

  stack_t* reversed = reversed_tac_stack(stack);

  printf("\n\n____ stack ____\n");
  print_tac_stack(&stack);

  printf("\n\n____ reversed ____\n");
  print_tac_stack(&reversed);

  clear_tac_stack(&stack);
  clear_tac_stack(&reversed);
  free_stack(stack);
  free_stack(reversed);
}

void stack_push_all_tacs(stack_t* dst, stack_t* pushed)
{
  stack_t* reversed = reversed_tac_stack(pushed);
  stack_item_t* item = reversed->data;

  while (item) {
    stack_push(copy_tac(item->value), dst);
    item = item->next;
  }
  clear_tac_stack(&reversed);
  free_stack(reversed);
}

void stack_push_all_tacs_not(stack_t* dst, stack_t* pushed, stack_t* t_holes, stack_t* f_holes)
{
  stack_t* reversed = reversed_tac_stack(pushed);
  stack_item_t* item = reversed->data;
  int count = 0;
  while (item) {
    stack_push(copy_tac(item->value), dst);
    if(((tac_t*)dst->data->value)->opcode == OP_CBR) {
      if(strcmp((((tac_t*)dst->data->value)->dst_1), "BURACO") == 0) stack_push(&(((tac_t*)dst->data->value)->dst_1), f_holes);
      if(strcmp((((tac_t*)dst->data->value)->dst_2), "BURACO") == 0) stack_push(&(((tac_t*)dst->data->value)->dst_2), t_holes);
    }
    item = item->next;
  }
  clear_tac_stack(&reversed);
  free_stack(reversed);
}

void stack_push_all_tacs_and(stack_t* dst, stack_t* pushed, stack_t* t_holes, stack_t* f_holes, bool op1, int syntatic_type)
{
  stack_t* reversed = reversed_tac_stack(pushed);
  stack_item_t* item = reversed->data;
  int count = 0;
  while (item) {
    stack_push(copy_tac(item->value), dst);
    if(((tac_t*)dst->data->value)->opcode == OP_CBR) {
      if(syntatic_type == AST_LOGICO_COMP_NEGACAO) {
        if(strcmp((((tac_t*)dst->data->value)->dst_1), "BURACO") == 0) stack_push(&(((tac_t*)dst->data->value)->dst_1), f_holes);
        if(strcmp((((tac_t*)dst->data->value)->dst_2), "BURACO") == 0) stack_push(&(((tac_t*)dst->data->value)->dst_2), t_holes);
      }
      else {
        if(strcmp((((tac_t*)dst->data->value)->dst_1), "BURACO") == 0) stack_push(&(((tac_t*)dst->data->value)->dst_1), t_holes);
        if(strcmp((((tac_t*)dst->data->value)->dst_2), "BURACO") == 0) stack_push(&(((tac_t*)dst->data->value)->dst_2), f_holes);
      }
    }
    item = item->next;
  }
  clear_tac_stack(&reversed);
  free_stack(reversed);
}

void stack_push_all_tacs_or(stack_t* dst, stack_t* pushed, stack_t* t_holes, stack_t* f_holes, bool op1, int syntatic_type)
{
  stack_t* reversed = reversed_tac_stack(pushed);
  stack_item_t* item = reversed->data;
  int count = 0;
  while (item) {
    stack_push(copy_tac(item->value), dst);
    if(((tac_t*)dst->data->value)->opcode == OP_CBR) {
      if(syntatic_type == AST_LOGICO_COMP_NEGACAO) {
        if(strcmp((((tac_t*)dst->data->value)->dst_1), "BURACO") == 0) stack_push(&(((tac_t*)dst->data->value)->dst_1), f_holes);
        if(strcmp((((tac_t*)dst->data->value)->dst_2), "BURACO") == 0) stack_push(&(((tac_t*)dst->data->value)->dst_2), t_holes);
      }
      else {
        if(strcmp((((tac_t*)dst->data->value)->dst_1), "BURACO") == 0) stack_push(&(((tac_t*)dst->data->value)->dst_1), t_holes);
        if(strcmp((((tac_t*)dst->data->value)->dst_2), "BURACO") == 0) stack_push(&(((tac_t*)dst->data->value)->dst_2), f_holes);
      }
    }
    item = item->next;
  }
  clear_tac_stack(&reversed);
  free_stack(reversed);
}

char* new_hole()
{
  return "BURACO";
}

void remenda(stack_t** holes, char* label)
{
  char** buraco;
  stack_item_t* item = (*holes)->data;
  while (item) {
    buraco = item->value;
    if (buraco) {
      free(*buraco);
      *buraco = strdup(label);
    }
    item = item->next;
  }
}

void remenda_test()
{
  int i;
  //representa o campo t_buracos de um ast_node
  stack_t* stack = new_stack();
  //representa alguns campos de tacs a serem remendados
  char* holes[5] = { new_hole(), new_hole(), new_hole(), new_hole(), new_hole() };

  printf("\nBuracos:\n");
  for (i = 0; i < 5 ; ++i) {
    printf("%d - %s\n", i, holes[i]);
  }

  //coloca numa lista de buracos
  for (i = 0; i < 5 ; ++i) {
    stack_push(&(holes[i]), stack);
  }
  //remenda lista
  remenda(&stack, "Remendo");
  printf("\nBuracos remendados:\n");
  for (i = 0; i < 5 ; ++i) {
    printf("%d - %s\n", i, holes[i]);
  }

  for (i = 0; i < 5 ; ++i) {
    free(holes[i]);
  }
  free_stack(stack);
}

void print_stack_holes(stack_t *stack) {
  stack_item_t *item = stack->data;
  while(item) {
    printf("%s\n", *((char**)item->value));
    item = item->next;
  }
}

//geracao de codigo de facto

int opcode_from_operator(ast_node_value_t* operator) {
  switch (operator->syntactic_type) {
    case AST_LOGICO_COMP_LE: return OP_CMP_LE;
    case AST_LOGICO_COMP_GE: return OP_CMP_GE;
    case AST_LOGICO_COMP_L: return OP_CMP_LT;
    case AST_LOGICO_COMP_G: return OP_CMP_GT;
    case AST_LOGICO_COMP_IGUAL: return OP_CMP_EQ;
    case AST_LOGICO_COMP_DIF: return OP_CMP_NE;
    case AST_LOGICO_E: return OP_AND;
    case AST_LOGICO_OU: return OP_OR;
    case AST_ARIM_SOMA: return OP_ADD;
    case AST_ARIM_SUBTRACAO: return OP_SUB;
    case AST_ARIM_DIVISAO: return OP_DIV;
    case AST_ARIM_MULTIPLICACAO:return OP_MULT;

    default:
      printf("Operador não encontrado!\n");
      exit(EXIT_FAILURE);
  }
}
bool is_relop(int opcode) {
  switch (opcode) {
    case OP_CMP_LE: return true;
    case OP_CMP_GE: return true;
    case OP_CMP_EQ: return true;
    case OP_CMP_NE: return true;
    case OP_CMP_LT: return true;
    case OP_CMP_GT: return true;
    default: return false;
  }
}
bool is_logic(int opcode) {
  switch (opcode) {
    case OP_AND: return true;
    case OP_OR: return true;
    default: return false;
  }
}
bool is_arit(int opcode) {
  switch (opcode) {
    case OP_ADD: return true;
    case OP_SUB: return true;
    case OP_DIV: return true;
    case OP_MULT: return true;
    default: return false;
  }
}
bool is_and(int opcode) {
  return (opcode == OP_AND);
}
bool is_or(int opcode) {
  return (opcode == OP_OR);
}
bool has_holes_to_patch(ast_node_value_t* ast_node) {
  return (!ast_node->t_holes->empty) || (!ast_node->f_holes->empty);
}

void generate_code_load_var(ast_node_value_t *variable) {
  variable->result_reg = new_register();
  st_value_t* st_entry = variable->symbols_table_entry;
  char* imediate = new_imediate(st_entry->offset_address);
  char* base_register = base_register_name(st_entry->address_base);

  tac_t* loadai = new_tac_ssed(false, NULL, OP_LOAD_AI, base_register, imediate, variable->result_reg);
  stack_push(loadai, variable->tac_stack);

  free(imediate); free(base_register);
}

void generate_code_load_literal_int(ast_node_value_t *literal) {
  literal->result_reg = new_register();
  st_value_t* st_entry = literal->symbols_table_entry;
  char* imediate = new_imediate(st_entry->value.i);

  tac_t* loadi = new_tac_sed(false, NULL, OP_LOAD_I, imediate, literal->result_reg);
  stack_push(loadi, literal->tac_stack);

  free(imediate);
}

void generate_code_load_literal_bool(ast_node_value_t *literal) {
  literal->result_reg = new_register();
  st_value_t* st_entry = literal->symbols_table_entry;
  char* imediate = new_imediate(st_entry->value.b);

  //TODO oportunidade de melhora: deixar só um jump e um buraco na t ou f holes dependendo de value.b
  //TODO para isso é preciso que o and e o or tratem jumpi alem de cbr...

  //carga
  tac_t* loadi = new_tac_sed(false, NULL, OP_LOAD_I, imediate, literal->result_reg);
  stack_push(loadi, literal->tac_stack);
  //buracos para remendo
  tac_t* cbr = new_tac(NULL, OP_CBR, literal->result_reg, NULL, new_hole(), new_hole());
  stack_push(cbr, literal->tac_stack);
  //guarda referencias para buracos a serem remendados
  char** x_address = &cbr->dst_1;
  char** y_address = &cbr->dst_2;
  stack_push(x_address, literal->t_holes);
  stack_push(y_address, literal->f_holes);

  free(imediate);
}

void generate_code_unary_op(ast_node_value_t *cabeca, ast_node_value_t *unary_op, ast_node_value_t *expressao) {
  cabeca->result_reg = new_register();
  if(unary_op->syntactic_type == AST_ARIM_INVERSAO) {
    char* imediate = new_imediate(0);

    stack_push_all_tacs(cabeca->tac_stack, expressao->tac_stack);
    tac_t* sub = new_tac_ssed(false, NULL, OP_RSUB_I, expressao->result_reg, imediate, cabeca->result_reg);
    stack_push(sub, cabeca->tac_stack);

    free(imediate);
  }
    //TODO simplificar esses branches de if abaixo e "implementar de fato"
  else if(unary_op->syntactic_type == AST_LOGICO_COMP_NEGACAO) {
    stack_push_all_tacs_not(cabeca->tac_stack, expressao->tac_stack, cabeca->t_holes, cabeca->f_holes);
  }
  else {
    stack_push_all_tacs(cabeca->tac_stack, expressao->tac_stack);
  }
}

void generate_code_expression(ast_node_value_t* expression, ast_node_value_t* operand_1, ast_node_value_t* operator, ast_node_value_t* operand_2) {
  expression->result_reg = new_register();
  int opcode = opcode_from_operator(operator);

  if (is_relop(opcode)) {

    char* x = new_hole();
    char* y = new_hole();

    //concatenacao de codigo
    stack_push_all_tacs(expression->tac_stack, operand_1->tac_stack);
    stack_push_all_tacs(expression->tac_stack, operand_2->tac_stack);
    tac_t* comparison = new_tac(NULL, opcode, operand_1->result_reg, operand_2->result_reg, expression->result_reg, NULL);
    stack_push(comparison, expression->tac_stack);
    tac_t* cbr = new_tac(NULL, OP_CBR, expression->result_reg, NULL, x, y);
    stack_push(cbr, expression->tac_stack);
    //guarda referencias para buracos a serem remendados
    char** x_address = &cbr->dst_1;
    char** y_address = &cbr->dst_2;
    stack_push(x_address, expression->t_holes);
    stack_push(y_address, expression->f_holes);
  }
  else if (is_logic(opcode)) {
    if(is_and(opcode)) {
      char* label_check_B2 = new_label();

      //TODO colocar um cbrs com result regs de operandos se eles nao forem bools

      remenda(&(operand_1->t_holes), label_check_B2);

      //guarda referencias para buracos a serem remendados
      stack_push_all_tacs_and(expression->tac_stack, operand_1->tac_stack, expression->t_holes, expression->f_holes, true, operand_1->syntactic_type);
      stack_push(new_tac_nop(true, label_check_B2), expression->tac_stack);
      stack_push_all_tacs_and(expression->tac_stack, operand_2->tac_stack, expression->t_holes, expression->f_holes, false, operand_2->syntactic_type);

      free(label_check_B2);
    }
    else {
      char* label_check_B2 = new_label();

      remenda(&(operand_1->f_holes), label_check_B2);

      //guarda referencias para buracos a serem remendados
      stack_push_all_tacs_or(expression->tac_stack, operand_1->tac_stack, expression->t_holes, expression->f_holes, true, operand_1->syntactic_type);
      stack_push(new_tac_nop(true, label_check_B2), expression->tac_stack);
      stack_push_all_tacs_or(expression->tac_stack, operand_2->tac_stack, expression->t_holes, expression->f_holes, false, operand_2->syntactic_type);

      free(label_check_B2);
    }
  }
  else if (is_arit(opcode)) {
    //a ideia é que concatenemos os codigos dos operandos e depois é possivel que concatenemos os codigos
    //de obtencao de valor numerico de bool_ops. os bool_ops tem buracos a serem remendados, entao primeiro
    //geramos o codigo dessa obtencao de valores, com os labels remendados, mas guardamos em um cache para ser
    //pushado em expression->tac_stack só depois da concatenacao do codigo dos operandos, ficando na ordem correta
    stack_t* cache_stack_1;
    if (has_holes_to_patch(operand_1)) {
      cache_stack_1 = new_stack();
    } else {
      cache_stack_1 = NULL;
    }
    stack_t* cache_stack_2;
    if (has_holes_to_patch(operand_2)) {
      cache_stack_2 = new_stack();
    } else {
      cache_stack_2 = NULL;
    }

    //se os operandos forem operadores logicos ou relacionais, há buracos a serem remendados neles, e precisamos
    //obter um valor numerico (1 ou 0) da expressao em algum registrador para poder realizar a arit op
    //fazer analise para ambos os operandos (for de duas iteracoes apenas)
    int i;
    for (i = 0; i < 2; ++i) {
      ast_node_value_t* operand = (i == 0)? operand_1 : operand_2;
      stack_t* cache_stack = (i == 0)? cache_stack_1 : cache_stack_2;
      if (has_holes_to_patch(operand)) {

        //criamos duas labels. a (true/false) refere ao codigo que se carrega (1/0) no result reg do operando
        char *label_true = new_label();
        char *label_false = new_label();
        //criamos uma label que é o fim dessa atribuicao de 1 ou 0, para continuar o codigo depois disso
        char *label_continue = new_label();

        //colocamos a label true e a atribuicao do 1 (true)
        char* imed_true = new_imediate(1);
        tac_t* loadi_true = new_tac_sed(true, label_true, OP_LOAD_I, imed_true, operand->result_reg);
        stack_push(loadi_true, cache_stack);
        //colocamos um jump para a label de continue, para pular a atribuicao do 0 (false)
        tac_t* skip_false = new_tac_jump(false, NULL, label_continue);
        stack_push(skip_false, cache_stack);

        //colocamos a label false e a atribuicao do 0 (false)
        char* imed_false = new_imediate(0);
        tac_t* loadi_false = new_tac_sed(true, label_false, OP_LOAD_I, imed_false, operand->result_reg);
        stack_push(loadi_false, cache_stack);

        //colocamos a label de continue
        tac_t* nop_continue_label = new_tac_nop(true, label_continue);
        stack_push(nop_continue_label, cache_stack);

        //finalmente, remendamos os buracos do operando com as labels que criamos
        remenda(&(operand->t_holes), label_true);
        remenda(&(operand->f_holes), label_false);

        free(label_true); free(label_false); free(label_continue); free(imed_true); free(imed_false);
      }
    }
    //concatenacao do codigo final

    //codigo do operando 1 e obtencao de seu valor se ele for booleano
    stack_push_all_tacs(expression->tac_stack, operand_1->tac_stack);
    if (cache_stack_1) {
      stack_push_all_tacs(expression->tac_stack, cache_stack_1);
      clear_tac_stack(&cache_stack_1);
      free_stack(cache_stack_1);
    }
    //codigo do operando 2 e obtencao de seu valor se ele for booleano
    stack_push_all_tacs(expression->tac_stack, operand_2->tac_stack);
    if (cache_stack_2) {
      stack_push_all_tacs(expression->tac_stack, cache_stack_2);
      clear_tac_stack(&cache_stack_2);
      free_stack(cache_stack_2);
    }
    //operacao aritmetica
    tac_t* arit_op = new_tac(NULL, opcode, operand_1->result_reg, operand_2->result_reg, expression->result_reg, NULL);
    stack_push(arit_op, expression->tac_stack);
  }
}

void generate_code_if(ast_node_value_t *cabeca, ast_node_value_t *condicao, ast_node_value_t *codigo) {
  char* label_true = new_label();
  char* label_end = new_label();

  //stack_print(condicao->t_holes);
  //print_stack_holes(condicao->t_holes);
  //print_stack_holes(condicao->f_holes);
  remenda(&(condicao->t_holes), label_true);
  remenda(&(condicao->f_holes), label_end);
  //print_stack_holes(condicao->t_holes);
  //print_stack_holes(condicao->f_holes);

  //printf("CONDICAO:\n");
  //print_tac_stack(&condicao->tac_stack);
  stack_push_all_tacs(cabeca->tac_stack, condicao->tac_stack);
  stack_push(new_tac_nop(true, label_true), cabeca->tac_stack);
  stack_push_all_tacs(cabeca->tac_stack, codigo->tac_stack);
  stack_push(new_tac_nop(true, label_end), cabeca->tac_stack);

  free(label_true);
  free(label_end);
}

void generate_code_while(ast_node_value_t *cabeca, ast_node_value_t *condicao, ast_node_value_t *codigo) {
  char* label_begin = new_label();
  char* label_true = new_label();
  char* label_end = new_label();

  //stack_print(condicao->t_holes);
  //print_stack_holes(condicao->t_holes);
  //print_stack_holes(condicao->f_holes);
  remenda(&(condicao->t_holes), label_true);
  remenda(&(condicao->f_holes), label_end);
  //print_stack_holes(condicao->t_holes);
  //print_stack_holes(condicao->f_holes);

  //printf("CONDICAO:\n");
  //print_tac_stack(&condicao->tac_stack);
  stack_push(new_tac_nop(true, label_begin), cabeca->tac_stack);
  stack_push_all_tacs(cabeca->tac_stack, condicao->tac_stack);
  stack_push(new_tac_nop(true, label_true), cabeca->tac_stack);
  stack_push_all_tacs(cabeca->tac_stack, codigo->tac_stack);
  stack_push(new_tac_jump(false, NULL, label_begin), cabeca->tac_stack);
  stack_push(new_tac_nop(true, label_end), cabeca->tac_stack);

  free(label_begin);
  free(label_true);
  free(label_end);
}

void generate_code_do_while(ast_node_value_t *cabeca, ast_node_value_t *condicao, ast_node_value_t *codigo) {
  char* label_true = new_label();
  char* label_end = new_label();

  //stack_print(condicao->t_holes);
  //print_stack_holes(condicao->t_holes);
  //print_stack_holes(condicao->f_holes);
  remenda(&(condicao->t_holes), label_true);
  remenda(&(condicao->f_holes), label_end);
  //print_stack_holes(condicao->t_holes);
  //print_stack_holes(condicao->f_holes);

  //printf("CONDICAO:\n");
  //print_tac_stack(&condicao->tac_stack);
  stack_push(new_tac_nop(true, label_true), cabeca->tac_stack);
  stack_push_all_tacs(cabeca->tac_stack, codigo->tac_stack);
  stack_push_all_tacs(cabeca->tac_stack, condicao->tac_stack);
  stack_push(new_tac_nop(true, label_end), cabeca->tac_stack);

  free(label_true);
  free(label_end);
}

void generate_code_if_else(ast_node_value_t *cabeca, ast_node_value_t *condicao, ast_node_value_t *codigo_true, ast_node_value_t *codigo_false) {
  char* label_true = new_label();
  char* label_false = new_label();
  char* label_end = new_label();

  remenda(&(condicao->t_holes), label_true);
  remenda(&(condicao->f_holes), label_false);

  stack_push_all_tacs(cabeca->tac_stack, condicao->tac_stack);
  stack_push(new_tac_nop(true, label_true), cabeca->tac_stack);
  stack_push_all_tacs(cabeca->tac_stack, codigo_true->tac_stack);
  stack_push(new_tac_jump(false, NULL, label_end), cabeca->tac_stack);
  stack_push(new_tac_nop(true, label_false), cabeca->tac_stack);
  stack_push_all_tacs(cabeca->tac_stack, codigo_false->tac_stack);
  stack_push(new_tac_nop(true, label_end), cabeca->tac_stack);

  free(label_true);
  free(label_false);
  free(label_end);
}

void generate_code_attribution_var(ast_node_value_t* var, ast_node_value_t* expression) {

  //a ideia é que concatenemos os codigos dos operandos e depois é possivel que concatenemos os codigos
  //de obtencao de valor numerico de bool_ops. os bool_ops tem buracos a serem remendados, entao primeiro
  //geramos o codigo dessa obtencao de valores, com os labels remendados, mas guardamos em um cache para ser
  //pushado em var->tac_stack só depois da concatenacao do codigo dos operandos, ficando na ordem correta
  stack_t* cache_stack;
  if (has_holes_to_patch(expression)) {
    cache_stack = new_stack();
  } else {
    cache_stack = NULL;
  }

  //se os operandos forem operadores logicos ou relacionais, há buracos a serem remendados neles, e precisamos
  //obter um valor numerico (1 ou 0) da expressao em algum registrador para poder realizar a atribuicao
  if (has_holes_to_patch(expression)) {

    //criamos duas labels. a (true/false) refere ao codigo que se carrega (1/0) no result reg do operando
    char *label_true = new_label();
    char *label_false = new_label();
    //criamos uma label que é o fim dessa atribuicao de 1 ou 0, para continuar o codigo depois disso
    char *label_continue = new_label();

    //colocamos a label true e a atribuicao do 1 (true)
    char* imed_true = new_imediate(1);
    tac_t* loadi_true = new_tac_sed(true, label_true, OP_LOAD_I, imed_true, expression->result_reg);
    stack_push(loadi_true, cache_stack);
    //colocamos um jump para a label de continue, para pular a atribuicao do 0 (false)
    tac_t* skip_false = new_tac_jump(false, NULL, label_continue);
    stack_push(skip_false, cache_stack);

    //colocamos a label false e a atribuicao do 0 (false)
    char* imed_false = new_imediate(0);
    tac_t* loadi_false = new_tac_sed(true, label_false, OP_LOAD_I, imed_false, expression->result_reg);
    stack_push(loadi_false, cache_stack);

    //colocamos a label de continue
    tac_t* nop_continue_label = new_tac_nop(true, label_continue);
    stack_push(nop_continue_label, cache_stack);

    //finalmente, remendamos os buracos do operando com as labels que criamos
    remenda(&(expression->t_holes), label_true);
    remenda(&(expression->f_holes), label_false);

    free(label_true); free(label_false); free(label_continue); free(imed_true); free(imed_false);
  }
  //concatenacao do codigo final

  //codigo do operando 1 e obtencao de seu valor se ele for booleano
  stack_push_all_tacs(var->tac_stack, expression->tac_stack);
  if (cache_stack) {
    stack_push_all_tacs(var->tac_stack, cache_stack);
    clear_tac_stack(&cache_stack);
    free_stack(cache_stack);
  }

  st_value_t* var_st_entry = var->symbols_table_entry;
  char* imediate = new_imediate(var_st_entry->offset_address);
  char* base_register = base_register_name(var_st_entry->address_base);
  tac_t* store_ai = new_tac(NULL, OP_STORE_AI, expression->result_reg, NULL, base_register, imediate);
  stack_push(store_ai, var->tac_stack);

  free(imediate); free(base_register);
}

void generate_code_for(ast_node_value_t* head, ast_node_value_t* first_cmds, ast_node_value_t* condition, ast_node_value_t* scnd_cmds, ast_node_value_t* body) {
  char* label_condition = new_label();
  char* label_body = new_label();
  char* label_break = new_label();

  //controle de iterar ou sair do for
  remenda(&condition->t_holes, label_body);
  remenda(&condition->f_holes, label_break);

  //código de inicializacao
  stack_push_all_tacs(head->tac_stack, first_cmds->tac_stack);
  //código da condicao, com label para reiteracao
  tac_t* nop_label_condition = new_tac_nop(true, label_condition);
  stack_push(nop_label_condition, head->tac_stack);
  stack_push_all_tacs(head->tac_stack, condition->tac_stack);
  //codigo do corpo, com label para onde condition = true pula
  tac_t* nop_label_body= new_tac_nop(true, label_body);
  stack_push(nop_label_body, head->tac_stack);
  stack_push_all_tacs(head->tac_stack, body->tac_stack);
  //codigo dos comandos finais do laço
  stack_push_all_tacs(head->tac_stack, scnd_cmds->tac_stack);
  //salto para recomeço do loop
  tac_t* jump_condition = new_tac_jump(false, NULL, label_condition);
  stack_push(jump_condition, head->tac_stack);
  //label de final de loop, para salto de break/saida do for
  tac_t* nop_label_break = new_tac_nop(true, label_break);
  stack_push(nop_label_break, head->tac_stack);

  //libera alocacoes nao mais necessarias
  free(label_body); free(label_break); free(label_condition);
}

void generate_code_foreach(ast_node_value_t* head, st_value_t* identifier, comp_tree_t* params, ast_node_value_t* body) {
  ast_node_value_t *param_node;

  char* imediate = new_imediate(identifier->offset_address);
  char* base_register = base_register_name(identifier->address_base);
  char* reg_identifier = new_register();

  while(params) {
    param_node = params->value;
    stack_push_all_tacs(head->tac_stack, param_node->tac_stack);
    tac_t* store_ai = new_tac(NULL, OP_STORE_AI, param_node->result_reg, NULL, base_register, imediate);
    stack_push(store_ai, head->tac_stack);
    stack_push_all_tacs(head->tac_stack, body->tac_stack);
    params = params->first;
  }

  free(imediate); free(base_register); free(reg_identifier);
}

void generate_code_function_label(ast_node_value_t* function) {
  //gerar label da funcao
  char* function_name = function->symbols_table_entry->value.s;
  char* function_label = malloc((strlen(function_name) + 2)*sizeof(char));
  sprintf(function_label, "l%s", function_name);

  //colocar label antes do código da função
  tac_t* nop_func_label = new_tac_nop(true, function_label);
  stack_push(nop_func_label, function->tac_stack);

  free(function_label);
}

void iloc_to_stdout(stack_t *tac_stack) {
  stack_t* inv_stack = reversed_tac_stack(tac_stack);

  stack_item_t* item = inv_stack->data;
  while (item) {
    if (item->value) {
      char* code = tac_to_string(item->value);
      fprintf(stdout, "%s\n", code);
      free(code);
    }
    item = item->next;
  }

  clear_tac_stack(&inv_stack);
  free_stack(inv_stack);
}

int calculate_factor(int dimension, int* sizes) {
  if (dimension == 0) {
    return 1;
  }
  else {
    return sizes[dimension-1]* calculate_factor(dimension-1, sizes);
  }
}

int* stack_to_vector(stack_t* stack) {
  int size = 0;
  stack_item_t* item = stack->data;
  while (item) {
    size++;
    item = item->next;
  }

  int* vector = (int*) malloc(sizeof(int)*size);
  int count = 0;
  item = stack->data;
  while (item) {
    vector[count] = *((int*) item->value);
    count++;
    item = item->next;
  }

  return vector;
}

void generate_code_atrib_vector(ast_node_value_t* head, stack_t* indices /*lista de ast_nodes dos indices de acesso*/,
                                st_value_t* st_vector, ast_node_value_t* expression) {

  char* reg_acumulador = new_register();
  char* reg_aux = new_register();

  //concatenar codigo da expression
  stack_push_all_tacs(head->tac_stack, expression->tac_stack);

  //concatenar codigo dos indices
  stack_item_t* index = indices->data;
  while (index) {
    ast_node_value_t* ast_access_index = index->value;
    stack_push_all_tacs(head->tac_stack, ast_access_index->tac_stack);
    index = index->next;
  }

  //loadi 0 => acumulador
  char* imed_0 = new_imediate(0);
  tac_t* loadi_ac = new_tac_sed(false, NULL, OP_LOAD_I, imed_0, reg_acumulador);
  stack_push(loadi_ac, head->tac_stack);
  //load 0 => reg_aux
  tac_t* loadi_aux = new_tac_sed(false, NULL, OP_LOAD_I, imed_0, reg_aux);
  stack_push(loadi_aux, head->tac_stack);

  int dimension = 0;
  stack_item_t* item = indices->data;

  //ai pro fim da pilha
  while (item->next) {
    item = item->next;
  }

  //percorre pilha do fim pro inicio
  while (item) {
    ast_node_value_t* ast_access_index = item->value;

    int* sizes = stack_to_vector(st_vector->vector_sizes);
    int fator = calculate_factor(dimension, sizes);
    //multi item->result_reg, fator => reg_aux
    char* imed_fator = new_imediate(fator);
    tac_t* mult = new_tac_ssed(false, NULL, OP_MULT_I, ast_access_index->result_reg, imed_fator, reg_aux);
    stack_push(mult, head->tac_stack);
    //add reg_acumulador, reg_aux => acumulador
    tac_t* add = new_tac_ssed(false, NULL, OP_ADD, reg_acumulador, reg_aux, reg_acumulador);
    stack_push(add, head->tac_stack);

    free(sizes);
    free(imed_fator);
    item = item->prev;
    dimension++;
  }
  //mult acumulador, get_primitive_size(st_vector->semantic_type) => acumulador
  char* imed_prim_size = new_imediate(get_type_size(st_vector->semantic_type));
  tac_t* multi = new_tac_ssed(false, NULL, OP_MULT_I, reg_acumulador, imed_prim_size, reg_acumulador);
  stack_push(multi, head->tac_stack);

  //add acumulador, st_vector->offset => acumulador
  char* imed_offset_adr = new_imediate(st_vector->offset_address);
  tac_t* add_offset = new_tac_ssed(false, NULL, OP_ADD_I, reg_acumulador, imed_offset_adr, reg_acumulador);
  stack_push(add_offset, head->tac_stack);

  //store expression->result_reg => st_vector->adress_base, acumulador
  char* base_reg = base_register_name(st_vector->address_base);
  tac_t* store = new_tac_sedd(false, NULL, OP_STORE_A0, expression->result_reg, base_reg, reg_acumulador);
  stack_push(store, head->tac_stack);

  free(imed_0); free(reg_acumulador); free(reg_aux);
  free(imed_prim_size); free(base_reg);
}

void generate_code_exp_vector(ast_node_value_t* head, stack_t* indices /*lista de ast_nodes dos indices de acesso*/, st_value_t* st_vector) {

  head->result_reg = new_register();
  char* reg_acumulador = new_register();
  char* reg_aux = new_register();

  //concatenar codigo dos indices
  stack_item_t* index = indices->data;
  while (index) {
    ast_node_value_t* ast_access_index = index->value;
    stack_push_all_tacs(head->tac_stack, ast_access_index->tac_stack);
    index = index->next;
  }

  //loadi 0 => acumulador
  char* imed_0 = new_imediate(0);
  tac_t* loadi_ac = new_tac_sed(false, NULL, OP_LOAD_I, imed_0, reg_acumulador);
  stack_push(loadi_ac, head->tac_stack);
  //load 0 => reg_aux
  tac_t* loadi_aux = new_tac_sed(false, NULL, OP_LOAD_I, imed_0, reg_aux);
  stack_push(loadi_aux, head->tac_stack);

  int dimension = 0;
  stack_item_t* item = indices->data;

  //ai pro fim da pilha
  while (item->next) {
    item = item->next;
  }

  //percorre pilha do fim pro inicio
  while (item) {
    ast_node_value_t* ast_access_index = item->value;

    int* sizes = stack_to_vector(st_vector->vector_sizes);
    int fator = calculate_factor(dimension, sizes);
    //multi item->result_reg, fator => reg_aux
    char* imed_fator = new_imediate(fator);
    tac_t* mult = new_tac_ssed(false, NULL, OP_MULT_I, ast_access_index->result_reg, imed_fator, reg_aux);
    stack_push(mult, head->tac_stack);
    //add reg_acumulador, reg_aux => acumulador
    tac_t* add = new_tac_ssed(false, NULL, OP_ADD, reg_acumulador, reg_aux, reg_acumulador);
    stack_push(add, head->tac_stack);

    free(sizes);
    free(imed_fator);
    item = item->prev;
    dimension++;
  }
  //mult acumulador, get_primitive_size(st_vector->semantic_type) => acumulador
  char* imed_prim_size = new_imediate(get_type_size(st_vector->semantic_type));
  tac_t* mult = new_tac_ssed(false, NULL, OP_MULT_I, reg_acumulador, imed_prim_size, reg_acumulador);
  stack_push(mult, head->tac_stack);

  //add acumulador, st_vector->offset => acumulador
  char* imed_offset_adr = new_imediate(st_vector->offset_address);
  tac_t* add_offset = new_tac_ssed(false, NULL, OP_ADD_I, reg_acumulador, imed_offset_adr, reg_acumulador);
  stack_push(add_offset, head->tac_stack);

  //load st_vector->adress_base, acumulador => head->result_reg
  char* base_reg = base_register_name(st_vector->address_base);
  tac_t* load = new_tac_ssed(false, NULL, OP_LOAD_A0, base_reg, reg_acumulador, head->result_reg);
  stack_push(load, head->tac_stack);

  free(reg_acumulador); free(reg_aux); free(base_reg);
  free(imed_0); free(imed_prim_size); free(imed_offset_adr);
}
