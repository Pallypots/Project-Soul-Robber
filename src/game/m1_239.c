/* Area m1, file 239: player effect timers (register inputs per docs/verification.md). Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Fx239 { uint8_t unk00[0x80]; int32_t n80; uint8_t unk84[4]; float t88; uint8_t unk8C[0x3C];
    float fC8, fCC; } M1Fx239;
extern float a50_frameSeconds;
extern uint8_t ae0_obj3E1270[];
M1Fx239 *sub_0001D960(void *o, int32_t slot);
void sub_000F3B30(void *o, int32_t k);
void sub_000F3BB0(void *o, int32_t a, int32_t b);
void sub_000F3B70(void *o, int32_t k);
int32_t sub_000E3380(void);
void sub_00019000(void *obj, int32_t k);
void sub_000BCA50(int32_t z);

/* 0x000F0660: count down effect slot 5's timer; when it runs out finish the effect: mode 2 -> pose 4, mode 1 ->
   pose 12, refresh the slot, wake 0x3E1270 unless area mode 4/5, then 0xF3B70 4; always zero the timer (hangs on a
   null player; regargs: o=ESI). */
void m1_FxTimer0F0660(void *o)
{
    M1Fx239 *e;
    int k;
    if (!o)
        for (;;) ;
    e = sub_0001D960(o, 5);
    e->t88 -= a50_frameSeconds;
    if (!_mm_comige_ss(_mm_setzero_ps(), _mm_load_ss(&e->t88)))
        return;
    switch (e->n80) {
    case 1:
        sub_000F3B30(o, 0xC);
        sub_000F3BB0(o, 0, 0);
        e->fCC = 0.0f;
        e->fC8 = 0.0f;
        sub_0001D960(o, 5);
        k = sub_000E3380();
        if (k != 4 && k != 5) {
            sub_00019000(ae0_obj3E1270, 1);
            sub_000BCA50(0);
        }
        sub_000F3B70(o, 4);
        break;
    case 2:
        sub_000F3B30(o, 4);
        sub_000F3BB0(o, 0, 0);
        e->fCC = 0.0f;
        e->fC8 = 0.0f;
        e->t88 = 0.0f;
        return;
    }
    e->t88 = 0.0f;
}

typedef struct M1CE239 { uint8_t unk00[0x7C]; float t7C; } M1CE239;
typedef struct M1CS239 { uint8_t unk00[0x20]; uint32_t flags20; uint8_t unk24[0x34]; int32_t st58; uint8_t unk5C[0x21C];
    M1CE239 *ext278; } M1CS239;
typedef struct M1CO239 { uint8_t unk00[0x30]; void *mdl30; } M1CO239;
int32_t sub_000833E0(void *m);
int  r2_PlayerOutOfReach(M1CS239 *obj, M1CO239 *self);   /* regargs: obj=EAX self=ESI */
void sub_0011F2B0(M1CO239 *obj, int k, M1CS239 *a);       /* regargs: obj=EDI k=EBX */

/* 0x00127C80: on clip end pick the next state: from step 30 -> 0x11 out of reach, 10 within 30 units, else 7/1 by
   flag 1; from step 10 -> 0x11 out of reach, else 5/0x12 by flag 1; other steps hang (calls 0x120820 with obj=EAX
   self=ESI, 0x11F2B0 with obj=EDI k=EBX). */
void m1_Next127C80(M1CO239 *o, M1CS239 *s)
{
    M1CE239 *e = s->ext278;
    switch (s->st58) {
    case 30:
        if (!sub_000833E0(o->mdl30))
            return;
        if (r2_PlayerOutOfReach(s, o))
            goto far;
        if (e->t7C <= 30.0f) {
            sub_0011F2B0(o, 10, s);
            return;
        }
        if (s->flags20 & 1) {
            sub_0011F2B0(o, 7, s);
            return;
        }
        sub_0011F2B0(o, 1, s);
        return;
    case 10:
        if (!sub_000833E0(o->mdl30))
            return;
        if (r2_PlayerOutOfReach(s, o)) {
far:
            sub_0011F2B0(o, 0x11, s);
            return;
        }
        sub_0011F2B0(o, (s->flags20 & 1) ? 5 : 0x12, s);
        return;
    }
    for (;;) ;
}

typedef struct M1CE239b { uint8_t unk00[4]; uint32_t flags4; uint8_t unk08[0x74]; float t7C; } M1CE239b;
typedef struct M1CS239b { uint8_t unk00[0x20]; uint32_t flags20; uint8_t unk24[0x34]; int32_t st58; uint8_t unk5C[0x218];
    float hp274; M1CE239b *ext278; } M1CS239b;
int  r2_PlayerOutOfReachB(M1CS239b *obj, M1CO239 *self);   /* 0x120820 regargs: obj=EAX self=ESI */
void sub_0011F2B0b(M1CO239 *obj, int k, M1CS239b *a);       /* 0x11F2B0 regargs: obj=EDI k=EBX */

/* 0x00127FA0: on clip end pick the next state: from step 40 -> 0x11 when weak (hp <= 1, no flag 0x10000000) or out
   of reach, else 1; from step 30 -> 0x11 out of reach, 10 within 30 units, else 7/1 by flag 1; other steps hang. */
void m1_Next127FA0(M1CO239 *o, M1CS239b *s)
{
    M1CE239b *e = s->ext278;
    switch (s->st58) {
    case 40:
        if (!sub_000833E0(o->mdl30))
            return;
        if (!(e->flags4 & 0x10000000) && s->hp274 <= 1.0f)
            goto far;
        if (r2_PlayerOutOfReachB(s, o)) {
            sub_0011F2B0b(o, 0x11, s);
            return;
        }
        goto one;
    case 30:
        if (!sub_000833E0(o->mdl30))
            return;
        if (r2_PlayerOutOfReachB(s, o)) {
far:
            sub_0011F2B0b(o, 0x11, s);
            return;
        }
        if (e->t7C <= 30.0f) {
            sub_0011F2B0b(o, 10, s);
            return;
        }
        if (s->flags20 & 1) {
            sub_0011F2B0b(o, 7, s);
            return;
        }
one:
        sub_0011F2B0b(o, 1, s);
        return;
    }
    for (;;) ;
}

typedef struct M1KO239 { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x1C]; void *mdl30; } M1KO239;
typedef struct M1KS239 { uint8_t unk00[0x20]; uint32_t flags20; uint8_t unk24[0x28]; uint32_t flags4C; uint8_t unk50[8];
    int32_t st58; uint8_t unk5C[0xC]; float t68; } M1KS239;
typedef int (*M1KFn239)(M1KO239 *o, M1KS239 *s, const void *t);
extern M1KFn239 m1_chkFn31CE04, m1_chkFn31CDFC;
extern const uint8_t m1_chkT279748[], m1_chkT279728[];
extern float a50_frameUnits;
int  r3b_Dispatch139B10(int k, M1KS239 *act, M1KO239 *obj);   /* regargs: k=EAX act=EDX obj=stack */
void sub_00113040k(M1KO239 *o, M1KS239 *s, int32_t mode);

/* 0x0013CE50: after 60 frames clear o flag 4 and advance; on the next clip end pick the follow-up mode (flag 1:
   0x13 if check passes, else 7/0 from dispatch 3; otherwise 0x11 if check passes, else 18/13 from dispatch 1) and
   hand over to 0x113040 (calls 0x139B10 with k=EAX act=EDX). */
void m1_Next13CE50(M1KO239 *o, M1KS239 *s)
{
    int m;
    switch (s->st58) {
    case 0:
        if (s->t68 >= 60.0f / a50_frameUnits * a50_frameSeconds) {
            o->flags10 &= ~4u;
            s->st58++;
        }
        return;
    case 1:
        if (!sub_000833E0(o->mdl30))
            return;
        s->flags4C |= 8;
        o->flags10 &= ~4u;
        if (s->flags20 & 1) {
            if (m1_chkFn31CE04(o, s, m1_chkT279748))
                m = 0x13;
            else
                m = -(r3b_Dispatch139B10(3, s, o) != 0) & 7;
        } else {
            if (m1_chkFn31CDFC(o, s, m1_chkT279728))
                m = 0x11;
            else
                m = (-(r3b_Dispatch139B10(1, s, o) != 0) & 5) + 0xD;
        }
        s->flags4C |= 8;
        sub_00113040k(o, s, *(volatile int *)&m);
        return;
    }
}
