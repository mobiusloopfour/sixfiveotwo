#include "defs.h"

unsigned char fetchb(c)
struct cpu *const c;
{
  NULLCHK(c);
  unsigned char x = buffer[c->pc];
  c->pc += 1;
  return x;
}

unsigned short fetchw(c)
struct cpu *const c;
{
  NULLCHK(c);
  unsigned short x = buffer[(c->pc) | (c->pc << 8)];
  c->pc += 2;
  return x;
}

reset(c) struct cpu *const c;
{
  NULLCHK(c);
  c->pc = 0xfffc;
  c->sp = 0xff; /* look up */
  c->irx = c->iry = c->acc = 0;

  c->stat.bc = c->stat.cf = \
    c->stat.dm = c->stat.id = \
    c->stat.nf = c->stat.of = \
    c->stat.zf = 0;

  return 0;
}