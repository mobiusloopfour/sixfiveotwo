#ifndef __DEFS_H_
#define __DEFS_H_

/* null check */
#include <stdio.h>
#include <stdlib.h>
#define NULLCHK(x) \
    if (!x) \
    { fprintf(stderr, "Attempted null dereference: %s - line %d", __FILE__, __LINE__); \
    exit(EXIT_FAILURE); }

#define WEAK_NULLCHK(x) \
    if (!x) \
    { fprintf(stderr, "[Warning]: Attempted null dereference: %s - line %d", __FILE__, __LINE__); return 1; }


/* processor state and registers */
#define R(x) unsigned char x
#define L(x) unsigned short x
#define F(x) unsigned short x : 1
struct status {
  F(cf);    F(zf);
  F(id);    F(dm);
  F(bc);    F(of);
  F(nf);    F(_); /* unused */
};
struct cpu {
  L(pc);    /*x16*/
  R(sp);    R(acc);   
  R(irx);   R(iry); 
  struct status stat;  
};
#undef R
#undef L
#undef F

#define EXEC(x, y) (*f_ptr[x])(y)

#define LDA_IMM 0xA9
#define LDA_ZPG 0xA5
#define LDA_ZPX 0xB5
#define LDA_ABS 0xAD
#define LDA_ABX 0xBD
#define LDA_ABY 0xB9
#define LDA_IDX 0xA1
#define LDA_IDY 0xB1

extern int (*f_ptr[0xff])(struct cpu*);

/* memop.c */
extern unsigned short   fetchw(struct cpu *const c);
extern unsigned char    fetchb(struct cpu *const c);

/* bogus.c */

extern char buffer[65535];
extern unsigned long long cyc;

#endif /* __DEFS_H_ */