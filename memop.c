#include "defs.h"

unsigned char
fetchb (struct cpu *const c)
{
  const unsigned char x = buffer[c->pc];
  c->pc += 1;
  return x;
}

unsigned short
fetchw (struct cpu *const c)
{
  auto index;
  unsigned short x, x1, x2;

  x1 = buffer[c->pc];
  x2 = buffer[c->pc + 1];
  x = (x1 | x2 << 8);
  return x;
}

unsigned char
rofetchb (unsigned short i, struct cpu *c)
{
  return buffer[i];
}

unsigned short
rofetchw (struct cpu *const c)
{
  return buffer[(c->pc) | ((c->pc + 1) << 8)];
}

reset (struct cpu *const c)
{
  NULLCHK (c);
  c->pc = 0xfffc;
  c->sp = 0xff; /* look up */
  c->irx = c->iry = c->acc = 0;

  c->stat.bc = c->stat.cf = c->stat.dm = c->stat.id = c->stat.nf = c->stat.of
      = c->stat.zf = 0;

  return 0;
}