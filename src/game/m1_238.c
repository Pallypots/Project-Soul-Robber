/* Area m1, file 238: actor message handlers. Names inferred. */
#include <stdint.h>

typedef struct M1E238 { uint8_t unk00[0x18]; float f18; uint8_t unk1C[0x20]; float t3C, t40; } M1E238;
typedef struct M1S238 { uint8_t unk00[0x274]; float hp274; M1E238 *ext278; } M1S238;
typedef struct M1Msg238 { int32_t kind; uint8_t unk04[8]; float dmgC; } M1Msg238;
void sub_000C75E0(void *o);
int32_t sub_00036750(void *o, int32_t pose);
void sub_00113040(void *o, M1S238 *s, int32_t mode);

/* 0x00180CE0: damage handler: kinds 1/2/3/5/29/32 always hit (32 also calls 0xC75E0), 34/35 hit only when their
   0.5 s / 1.5 s cooldown has run out; a hit sets pose 2, subtracts the damage and goes to mode 5 at 0 hp; returns 1
   on a hit. */
int m1_Damage180CE0(void *o, M1S238 *s, M1Msg238 *m)
{
    M1E238 *e = s->ext278;
    int k = m->kind;
    switch (k) {
    case 1: case 2: case 3: case 5: case 29: case 32:
        if (*(volatile int *)&k == 0x20)
            sub_000C75E0(o);
        break;
    case 34:
        if (*(volatile int *)&k != 0x22)
            return 0;
        if (e->t3C > 0.0f)
            return 0;
        e->t3C = 0.5f;
        break;
    case 35:
        if (*(volatile int *)&k != 0x23)
            return 0;
        if (e->t40 > 0.0f)
            return 0;
        e->t40 = 1.5f;
        break;
    default:
        return 0;
    }
    e->f18 = 0.58f;
    sub_00036750(o, 2);
    s->hp274 -= m->dmgC;
    if (s->hp274 <= 0.0f) {
        s->hp274 = 0.0f;
        sub_00113040(o, s, 5);
    }
    return 1;
}

typedef struct M1Sub238 { uint8_t unk00[0x50]; int32_t st50; } M1Sub238;
typedef struct M1E238b { void *o0; uint8_t unk04[4]; M1Sub238 *s8; uint8_t unk0C[0xC]; float t18, t1C; } M1E238b;
typedef struct M1S238b { uint8_t unk00[0x274]; float hp274; M1E238b *ext278; } M1S238b;
void sub_00113040b(void *o, M1Sub238 *s, int32_t mode);

/* 0x00182060: damage handler variant: ignored while the sub-actor is in step 2; kinds 1/2/3/5/29 hit, 32 hits after
   0xC75E0, 34/35 hit only after their 0.4 s / 1.3 s cooldown; a hit sets pose 1, subtracts the damage and at 0 hp
   sends the sub-actor to mode 2; returns 1 on a hit. */
int m1_Damage182060(void *o, M1S238b *s, M1Msg238 *m)
{
    M1E238b *e = s->ext278;
    int k;
    if (e->s8->st50 == 2)
        return 0;
    k = m->kind;
    switch (k) {
    case 32:
        sub_000C75E0(o);
    case 1: case 2: case 3: case 5: case 29:
        break;
    case 34:
        if (*(volatile int *)&k != 0x22)
            return 0;
        if (e->t18 > 0.0f)
            return 0;
        e->t18 = 0.4f;
        break;
    case 35:
        if (*(volatile int *)&k != 0x23)
            return 0;
        if (e->t1C > 0.0f)
            return 0;
        e->t1C = 1.3f;
        break;
    default:
        return 0;
    }
    sub_00036750(o, 1);
    s->hp274 -= m->dmgC;
    if (s->hp274 <= 0.0f) {
        sub_00113040b(e->o0, e->s8, 2);
        s->hp274 = 0.0f;
    }
    return 1;
}

typedef struct M1Tg238 { uint8_t unk00[0xC]; uint32_t flagsC; uint8_t unk10[0x10]; void *n20; } M1Tg238;
typedef struct M1Ts238 { uint16_t w0; uint8_t unk02[2]; M1Tg238 *t4; } M1Ts238;
typedef struct M1Ta238 { uint8_t unk00[0x74]; M1Ts238 *st74; } M1Ta238;
typedef struct M1To238 { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0xC]; uint8_t *n20; uint8_t unk24[0x2C];
    float r50, r54, r58, r5C; uint8_t pos60[0x10]; } M1To238;
typedef struct M1Ctx238 { uint8_t unk00[0x44]; void *res44; } M1Ctx238;
extern float m1_vec32C5D4[];
extern M1Ctx238 *a80_ctx42C8E4;
void *sub_0001D0F0(M1Tg238 *t, int32_t slot);
void sub_001B2080(void *n);
void sub_001B2080b(void *n);   /* same function (alias stops cl hoisting the call out of both branches) */
void sub_001B2020(void *parent, void *n);
void *sub_000847F0(void *res, int32_t k);
void sub_000F5D40(void *dst, const void *src);

/* 0x0018E270: attach o's node to the target's slot 0x10 (snap to the attach point, flag 0x40, state 1) or detach it
   back into the world (keep its world position, yaw 90 degrees, state 2); hangs if the slot is missing
   (regargs: a=EAX o=ESI). */
void m1_Attach18E270(M1Ta238 *a, M1To238 *o, int attach)
{
    M1Ts238 *st = a->st74;
    M1Tg238 *t = st->t4;
    void *n;
    if (!t || !(t->flagsC & 1) || !t->n20)
        return;
    n = sub_0001D0F0(t, 0x10);
    if (!n)
        for (;;) ;
    if (attach) {
        sub_001B2080(o->n20);
        sub_001B2020(n, o->n20);
        sub_000F5D40(o->pos60, m1_vec32C5D4);
        o->r50 = 0.0f;
        o->r54 = 0.0f;
        o->r58 = 0.0f;
        o->r5C = 1.0f;
        o->flags10 |= 0x40;
        st->w0 = 1;
        return;
    }
    sub_001B2080b(o->n20);
    sub_001B2020(sub_000847F0(a80_ctx42C8E4->res44, 9), o->n20);
    sub_000F5D40(o->pos60, o->n20 + 0x70);
    o->r58 = 1.57079637f;
    o->flags10 &= ~0x40u;
    st->w0 = 2;
}
