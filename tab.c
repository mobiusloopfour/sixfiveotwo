#include "defs.h"

/* lda */
#include "lda.c"

int (*f_ptr[0xff])(struct cpu *);

init() {
  auto i;
  f_ptr[LDA_IMM] = &lda_imm;
  return 0;
}