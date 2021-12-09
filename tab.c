#include "defs.h"
#include <stdio.h>

/* lda */
void 
def_handler (c) struct cpu *c;
{
  fprintf (stderr, "Unhandled instruction at $%X\n", c->pc);
  return;
}

#define LO(x) (x & 0xff)
#define HI(x) ((x << 8) & 0xff)

extern printc (struct cpu *c);

void 
jsr (c) struct cpu *c;
{

  buffer[c->sp] = LO (c->pc);
  buffer[--c->sp] = HI (c->pc);

  c->pc = fetchw (c);

  cyc -= 6;
  return;
}

#undef LO
#undef HI

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

void
nop (struct cpu *c)
{ cyc -= 2; }

void (*f_ptr[0xff]) (struct cpu *);

init ()
{
  auto i;
  static init = 1;

  if (init)
    {
      for (i = 0; i <= 0xff; ++i)
        {
          f_ptr[i] = &def_handler;
        }
    }
  init ^= init;

  f_ptr[LDA_IMM] = &lda_imm;
  f_ptr[LDA_ZPG] = &lda_zpg;
  f_ptr[LDA_ZPX] = &lda_zpx;
  f_ptr[JSR] = &jsr;
	f_ptr[NOP] = &nop;
  return 0;
}