/* Memory operations
 *
 *     Copyright (C) 2021 MobiusLoopFour
 *
 *	This file is part of sixfiveotwo.
 *	sixfiveotwo is free software; you can redistribute it and/or modify it under
 *	the terms of the GNU General Public License as published by the Free
 *	Software Foundation; either version 3, or (at your option) any later
 *	version.
 *	Sixfiveotwo is distributed in the hope that it will be useful, but
 *	WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *	or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *	for more details.
 *	You should have received a copy of the GNU General Public License
 *	along with sixfiveotwo; see the file COPYING.  If not see
 *	<http://www.gnu.org/licenses/>.  
 *
 */

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