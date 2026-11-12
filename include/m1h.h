/* Area m1, part h: init sequences. Names inferred. */
#ifndef M1H_H
#define M1H_H
#include "oogie.h"
typedef struct M1Lock { uint8_t raw[0x20]; } M1Lock;
void  sub_001B29F0(M1Lock *l);               /* initialise a lock-like 0x20-byte object */
extern M1Lock m1_locks42C7C0[19];            /* 0x0042C7C0 */
void  sub_00047BF0(int a);
void *sub_000E0770();
void  sub_000E3BA0(void *g);
void  sub_000E0810(void *g);
void  sub_0019A6A0(int ch);
void  sub_0019A0E0(int id);
void  sub_0019AAA0(void);
void *m1_InitLocks52840(void *arg);          /* 0x00052840 */
void  m1_SoundReset48590(void);              /* 0x00048590 */
#endif
