/* Internal defines
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

#ifndef __DEFS_H_
#define __DEFS_H_

/* null check */
#include <stdio.h>
#include <stdlib.h>
#define NULLCHK(x)                                                            \
  if (!x)                                                                     \
    {                                                                         \
      fprintf (stderr, "Attempted null dereference: %s - line %d", __FILE__,  \
               __LINE__);                                                     \
      exit (EXIT_FAILURE);                                                    \
    }

#define WEAK_NULLCHK(x)                                                       \
  if (!x)                                                                     \
    {                                                                         \
      fprintf (stderr, "[Warning]: Attempted null dereference: %s - line %d", \
               __FILE__, __LINE__);                                           \
      return 1;                                                               \
    }

/* processor state and registers */
#define R(x) unsigned char x
#define L(x) unsigned short x
#define F(x) unsigned short x : 1
struct status
{
  F (cf);
  F (zf);
  F (id);
  F (dm);
  F (bc);
  F (of);
  F (nf);
  F (_); /* unused */
};
struct cpu
{
  L (pc); /*x16*/
  R (sp);
  R (acc);
  R (irx);
  R (iry);
  struct status stat;
};
#undef R
#undef L
#undef F

#define EXEC(x, y) (*f_ptr[x]) (y)

#define LDA_IMM 0xA9
#define LDA_ZPG 0xA5
#define LDA_ZPX 0xB5
#define LDA_ABS 0xAD
#define LDA_ABX 0xBD
#define LDA_ABY 0xB9
#define LDA_IDX 0xA1
#define LDA_IDY 0xB1
#define JSR 0x20
#define NOP 0xEA

extern void (*f_ptr[0xff]) (struct cpu *);

/* memop.c */
extern unsigned short fetchw (struct cpu *);
extern unsigned char fetchb (struct cpu *);

extern unsigned short rofetchw (struct cpu *);
unsigned char rofetchb (unsigned short i, struct cpu *c);

/* bogus.c */

extern volatile char buffer[0xFFFF];
extern unsigned long long cyc;

#endif /* __DEFS_H_ */