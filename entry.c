#include "defs.h"
#include <stdint.h>
#include <stdio.h>

extern reset(struct cpu*);

printc(c) const struct cpu *const c;
{
  if (!c)
    return 1;
  printf("REGS       : ==\n");
  printf("INSTRUCTION: $%X\t\n", c->pc);
  printf("STACK      : $%X\t\n", c->sp);
  printf("ACCUMULATOR: $%X\t\n", c->acc);
  printf("X REGISTER : $%X\t\n", c->irx);
  printf("Y REGISTER : $%X\n\n", c->iry);
  printf("FLAGS      : ==\n");
  printf("CARRY      : $%X\t", c->stat.cf);
  printf("ZERO       : $%X\t\n", c->stat.zf);
  printf("I/D        : $%X\t", c->stat.id);
  printf("DECIMAL    : $%X\t\n", c->stat.dm);
  printf("BREAK CMD  : $%X\t", c->stat.bc);
  printf("OVERFLOW   : $%X\t\n", c->stat.of);
  printf("NEGATIVE   : $%X\t", c->stat.nf);
  printf("___________: $0\t\n");
  return 0;
}

extern init();

loop(c) struct cpu *c;
{
  auto next;
  NULLCHK(c);

  while (cyc > 0) {
    if (cyc == UINT64_MAX) {
      /* rather crude */
      fprintf(stderr, "Cycles overflow\n");
      return 1;
    } else if (!next) {
      fprintf(stderr, "Attempt to execute zero'ed memory (core dumped)\n");
      printc(c);
      return 1;
    }
    next = fetchb(c);
    EXEC(next, c);
  }

  return 0;
}

main() 
{
  struct cpu *cpu;

  /* ISA */
  init();

  /* CPU */
  cpu = (struct cpu*)malloc(sizeof(struct cpu));
  NULLCHK(cpu);

  reset(cpu);

  loop(cpu);
#if 1 /* debugging */
  printc(cpu);
#endif
  /* defer */
  free(cpu);
  return 0;
}