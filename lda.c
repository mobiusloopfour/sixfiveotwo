#include "defs.h"

#define LDA_RETURN(x) setf(c); cyc-=x; return 0;

static setf(struct cpu *const c);

lda_imm(c) struct cpu *c;
{
  NULLCHK(c);
  c->acc = fetchb(c);
  LDA_RETURN(2);
}

lda_zpg(c) struct cpu *c;
{
  NULLCHK(c);

  LDA_RETURN(3);
}

lda_zpx(c) struct cpu *c;
{
  NULLCHK(c);
  
  LDA_RETURN(4);
}

lda_abs(c) struct cpu *c;
{
  NULLCHK(c);
  
  LDA_RETURN(4);
}

lda_abx(c) struct cpu *c;
{
  NULLCHK(c);
  cyc -= 4; /* TODO: check for page crossing */

  LDA_RETURN(0);
}

lda_aby(c) struct cpu *c;
{
  NULLCHK(c);
  cyc -= 4; /* TODO: check for page crossing */
  LDA_RETURN(0);
}

lda_idx(c) struct cpu *c;
{
  NULLCHK(c);

  LDA_RETURN(6);
}

lda_idy(c) struct cpu *c;
{
  NULLCHK(c);
  cyc -= 5; /* TODO: check for page crossing */
  LDA_RETURN(0);
}

static setf(c) struct cpu *const c;
{
  NULLCHK(c);

  if (!c->acc) {
    c->stat.nf = 1;
  }
  if ((c->acc & 0b10000000) > 0) {
    c->stat.nf = 1;
  }
  return 0;
}

#undef LDA_RETURN