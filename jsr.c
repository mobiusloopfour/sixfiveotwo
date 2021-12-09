#include "defs.h"

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