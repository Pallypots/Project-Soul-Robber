/* Area m1, file 220: callers of register-argument actor helpers (policy in docs/verification.md). Names inferred. */
#include "r2c.h"

typedef struct M1Tg220 { uint8_t unk00[0x68]; float f68; uint8_t unk6C[8]; float f74; } M1Tg220;

/* 0x00117AC0: when target t has no health left (+0x74 <= 0), run actor step 0x117580 with mode 1. */
void m1_ActorIfDown117AC0(R2cActor *o, M1Tg220 *t)
{
    if (t->f74 <= 0.0f) sub_00117580(o, 1, t);
}

/* 0x001183C0: same check, mode 0x0E. */
void m1_ActorIfDownE1183C0(R2cActor *o, M1Tg220 *t)
{
    if (t->f74 <= 0.0f) sub_00117580(o, 0xE, t);
}

/* 0x00111A00: once target timer +0x68 reaches 2.0, hand actor o to 0x10FD50 (tail call). */
void m1_ActorAfter2s111A00(R2cActor *o, M1Tg220 *t)
{
    if (t->f68 >= 2.0f) sub_0010FD50(o);
}

/* Dinkumware-style string: +4 inline buffer or pointer, +0x14 length, +0x18 capacity (inline when < 16). */
typedef struct M1Str { void *al0; union { char buf[16]; char *ptr; } bx4; uint32_t size14; uint32_t res18; } M1Str;

/* 0x001A3840: set the length to n and write the terminator (thiscall: s=ECX; EDX unused). */
void __fastcall m1_StrEos1A3840(M1Str *s, int unusedEdx, uint32_t n)
{
    s->size14 = n;
    if (s->res18 < 16) s->bx4.buf[n] = 0;
    else s->bx4.ptr[n] = 0;
}

