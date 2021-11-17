#include "defs.h"
#include <stdio.h>

void
def_handler(c)
struct cpu *c;
{
  fprintf(stderr, "Unhandled instruction at $%X\n", c->pc);
  return;
}