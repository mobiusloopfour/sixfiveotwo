#include "defs.h"
#include <stdio.h>

#define LDA_RETURN(x)                                                         \
  setf (c);                                                                   \
  cyc -= x;                                                                   \
  return;

static setf (struct cpu *const c);

void 
lda_imm (c) struct cpu *c;
{
  c->acc = fetchb (c);
  LDA_RETURN (2);
}

void
lda_zpg (c) struct cpu *c;
{
  c->acc = buffer[fetchb (c)];
  LDA_RETURN (3);
}

void
lda_zpx (c) struct cpu *c;
{
  const unsigned char zpa = fetchb (c) + c->irx;
  c->acc = buffer[zpa];
  LDA_RETURN (4);
}

void
lda_abs (c) struct cpu *c;
{
  LDA_RETURN (4);
}

void
lda_abx (c) struct cpu *c;
{
  cyc -= 4; /* TODO: check for page crossing */
  LDA_RETURN (0);
}

void
lda_aby (c) struct cpu *c;
{
  cyc -= 4; /* TODO: check for page crossing */
  LDA_RETURN (0);
}

void
lda_idx (c) struct cpu *c;
{
  LDA_RETURN (6);
}

void
lda_idy (c) struct cpu *c;
{
  cyc -= 5; /* TODO: check for page crossing */
  LDA_RETURN (0);
}

static
setf (c) struct cpu *const c;
{
  NULLCHK (c);
  if (!c->acc)
    {
      c->stat.nf = 1;
    }
  if ((c->acc & 0b10000000) > 0)
    {
      c->stat.nf = 1;
    }
  return 0;
}

#undef LDA_RETURN