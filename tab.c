#include "defs.h"

/* lda */
#include "lda.c"
#include "jsr.c"
#include "def_handler.c"

void (*f_ptr[0xff])(struct cpu *);

init() {
  auto i;
  static init = 1;

  if (init) {
    for (i = 0; i <= 0xff; ++i) {
      f_ptr[i] = &def_handler;
    }
  }
  init ^= init;

  f_ptr[LDA_IMM] = &lda_imm;
  f_ptr[LDA_ZPG] = &lda_zpg;
  f_ptr[LDA_ZPX] = &lda_zpx;
  f_ptr[JSR] = &jsr;
  return 0;
}