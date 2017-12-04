/**
 * Arquivo com funções de tratamento de TAC (three adresses code)
 */

#include "cc_list.h"
#include "tac.h"
#include <math.h>

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
               strlen("loadA0 ") +
               strlen(tac->src_1) +
               strlen(", ") +
               strlen(tac->src_2) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%sloadA0 %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
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
                strlen("cloadA0 ") +
                strlen(tac->src_1) +
                strlen(", ") +
                strlen(tac->src_2) +
                strlen(" => ") +
                strlen(tac->dst_1) +
                1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%scloadA0 %s, %s => %s", label, tac->src_1, tac->src_2, tac->dst_1);
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
               strlen("storeA0 ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               strlen(", ") +
               strlen(tac->dst_2) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%sstoreA0 %s => %s, %s", label, tac->src_1, tac->dst_1, tac->dst_2);
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
               strlen("cstoreA0 ") +
               strlen(tac->src_1) +
               strlen(" => ") +
               strlen(tac->dst_1) +
               strlen(", ") +
               strlen(tac->dst_2) +
               1 /*para o \0*/) * sizeof(char);

      code = malloc(code_size_in_bytes);
      sprintf(code, "%scstoreA0 %s => %s, %s", label, tac->src_1, tac->dst_1, tac->dst_2);
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
      sprintf(code, "%smp_LT %s, %s -> %s", label, tac->src_1, tac->src_2, tac->dst_1);
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
