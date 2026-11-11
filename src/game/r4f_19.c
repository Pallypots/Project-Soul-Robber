/* Area r4f: particle emitter helpers at 0x001B3160-0x001B8383 (r4f_19). Names inferred. */
#include "r4f.h"

/* 0x001B3160: move every particle of a type-A emitter (0x108-byte particles) to the
   emitter position and copy the emitter pair at +0xE0. Stack arg (e). */
void r4f_EmitASetPos(R4fEmitter *e)
{
    R4fPartA *p;
    int i;
    if (!e->parts0C4)
        return;
    p = (R4fPartA *)e->parts0C4;
    for (i = 0; i < e->n0C0; i++, p++) {
        sub_000F5D40(p->posDC, e->posCC);
        p->f100 = e->fE0;
        p->f104 = e->fE4;
    }
}

/* 0x001B3210: set the pair at +0xE0 of a type-A emitter and of all its particles.
   Stack args (e a b). */
void r4f_EmitASetPair(R4fEmitter *e, int a, int b)
{
    int i;
    e->fE0 = a;
    e->fE4 = b;
    for (i = 0; i < e->n0C0; i++) {
        ((R4fPartA *)e->parts0C4)[i].f100 = a;
        ((R4fPartA *)e->parts0C4)[i].f104 = b;
    }
}

/* 0x001B8320: like r4f_EmitASetPos for type-B emitters (0x110-byte particles).
   Stack arg (e). */
void r4f_EmitBSetPos(R4fEmitter *e)
{
    R4fPartB *p;
    int i;
    if (!e->parts0C4)
        return;
    p = (R4fPartB *)e->parts0C4;
    for (i = 0; i < e->n0C0; i++, p++) {
        sub_000F5D40(p->posD8, e->posCC);
        p->fE8 = e->fE0;
        p->fEC = e->fE4;
    }
}


/* 0x001BB990: set the pair at +0xD8 of a type-C emitter and, unless its particles keep
   their own (flag 0x100), of all its particles. Stack args (e a b). */
void r4f_EmitCSetPair(R4fEmitterC *e, int a, int b)
{
    int i;
    e->fD8 = a;
    e->fDC = b;
    if (e->flags90 & 0x100)
        return;
    for (i = 0; i < e->n0C0; i++) {
        e->parts0C4[i].fF8 = a;
        e->parts0C4[i].fFC = b;
    }
}

/* 0x001B6D70: reset a type-D emitter through 0x001B6270 and clear the two per-particle
   fields at +0xB0 and +0x118. Stack arg (e). */
void r4f_EmitDReset(R4fEmitterD *e)
{
    uint32_t i;
    sub_001B6270(e);
    for (i = 0; i < e->n0B0; i++) {
        e->parts0B4[i].fB0 = 0;
        e->parts0B4[i].f118 = 0;
    }
}
