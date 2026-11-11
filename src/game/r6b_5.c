/* Area r6b: actor-slot queries and small helpers in 0x00092620-0x000B4D30 (r6b_5). Names inferred. */
#include "r6b.h"

/* 0x00092620: when +0x40 is clear, set flag 0x200 and reset the state at +0x3C to -1. */
void r6b_EntResetState(R6bEnt40 *e)
{
    if (!e->i40) {
        e->flags |= 0x200;
        sub_000A41D0(e, -1);
    }
}

/* 0x00094BF0: set value +0x124 of slot i, then its state to 1. */
void r6b_SlotSetAndStart(int i, int v)
{
    sub_000A4480(i, v);
    sub_000A43C0(i, 1);
}

/* 0x000952A0: bit 7 of slot 0's flags at +0x11C (as 0/1); hangs when there is no slot. */
int r6b_Slot0Flag7(void)
{
    R6bEnt *e = sub_000A4290(0);
    if (!e)
        for (;;) ;
    return (e->flags11C & 0x80) != 0;
}

/* 0x000952D0: bit 8 of slot 0's flags at +0x11C; hangs when there is no slot. */
uint32_t r6b_Slot0Flag8(void)
{
    R6bEnt *e = sub_000A4290(0);
    if (!e)
        for (;;) ;
    return (e->flags11C >> 8) & 1;
}

/* 0x00095300: field +0x110 of slot 0; hangs when there is no slot. */
int r6b_Slot0Value110(void)
{
    R6bEnt *e = sub_000A4290(0);
    if (!e)
        for (;;) ;
    return e->i110;
}

/* 0x00095320: bit 19 of slot 0's flags at +0x11C; hangs when there is no slot. */
uint32_t r6b_Slot0Flag19(void)
{
    R6bEnt *e = sub_000A4290(0);
    if (!e)
        for (;;) ;
    return (e->flags11C >> 19) & 1;
}

/* 0x0009FAD0: classify id 1..45: 1, -1 or 0. */
int r6b_ClassifyId(int id)
{
    switch (id) {
    case 1: case 2: case 3: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12:
    case 32: case 34: case 35:
        return 1;
    case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
    case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 33: case 36:
    case 39: case 40: case 41: case 42: case 43: case 45:
        return -1;
    default:
        return 0;
    }
}

/* 0x000AD090: returns 0. Callers push any number of arguments (declared
   unprototyped, like sub_000AD090 in shared_decls.h). */
int r6b_ReturnZero()
{
    return 0;
}

/* 0x000B4D30: forwards to 0x000BCBC0. */
void r6b_FwdBCBC0(void *p)
{
    sub_000BCBC0(p);
}
