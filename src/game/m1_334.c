/* Area m1, file 334: enemy stand-up exit (two triggers, same cleanup). Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Ob334 { uint8_t unk000[0x0C]; uint32_t f0C; uint32_t f10; uint8_t unk014[0x13C - 0x14]; int32_t snd13C; } M1Ob334;
typedef struct M1St334 { uint32_t f00; uint8_t unk04[0x50 - 4]; uint32_t f50; uint8_t unk54[0x5C - 0x54]; float f5C; } M1St334;
typedef struct M1Ai334 {
    uint8_t unk000[0x4C]; uint32_t f4C; uint8_t unk050[0x6C - 0x50]; int32_t snd6C; void *fx70;
    uint8_t unk074[0x278 - 0x74]; M1St334 *s278;
} M1Ai334;
extern float m1_frameRate42C85C;
int  sub_00156040(void);                                    /* regargs: s=EBX */
void m1_AiReset1134B0(void *e);
void m1_AiSway1561D0(M1St334 *s, float a, float b);
void sub_00113AA0(void *o, void *e);
void sub_00113190(void *o, void *e, int k);
void m1_SndStop048250(int h);
void m1_ObjSnd05BE30(int h);
void sub_00033A70(void *p);
int  m1_AiGoto113040(void *o, void *e, int st);
int  m1_AiGoto113040b(void *o, void *e, int st);   /* alias of 0x113040 */

#define M1_STANDUP_EXIT(k) M1_STANDUP_EXIT_M(k, 0xFFDBEEBFu)
#define M1_STANDUP_EXIT_M(k, mask)                           \
    s = e->s278;                                             \
    m1_AiReset1134B0(e);                                     \
    o->f0C |= 0xE0;                                          \
    o->f10 &= 0xFFFFFEC8u;                                   \
    e->f4C &= ~0x100u;                                       \
    s->f00 &= ~0x17u;                                        \
    s->f50 &= (mask);                                        \
    m1_AiSway1561D0(s, -10.0f, m1_frameRate42C85C * 10.0f);  \
    if (s->f50 & 0x10000) {                                  \
        sub_00113AA0(o, e);                                  \
        e->f4C |= 0x200;                                     \
        s->f50 &= ~0x10000u;                                 \
    }                                                        \
    if (s->f50 & 0x100000) {                                 \
        s->f50 &= ~0x100000u;                                \
        sub_00113190(o, e, 1);                               \
    }                                                        \
    if (e->snd6C != -1) {                                    \
        m1_SndStop048250(e->snd6C);                          \
        e->snd6C = -1;                                       \
    }                                                        \
    m1_ObjSnd05BE30(o->snd13C);                              \
    if (e->fx70) {                                           \
        sub_00033A70(e->fx70);                               \
        e->fx70 = 0;                                         \
    }                                                        \
    m1_AiGoto113040(o, e, k)

/* 0x14B840: leave the down state: when 0x156040 reports the stand-up trigger go to state
   0xC, else when the down timer has run out go to state 0xE; both paths reset the AI, clear
   the down flags, start the sway, handle pending flags and stop the sound and effect. */
void m1_AiStandUp14B840(M1Ob334 *o, M1Ai334 *e) {
    M1St334 *s = e->s278;
    if (sub_00156040()) {
        M1_STANDUP_EXIT(0xC);
        return;
    }
    if (!(0.0f >= s->f5C))
        return;
    M1_STANDUP_EXIT(0xE);
}

typedef struct M1Ob334b { uint8_t unk000[0x0C]; uint32_t f0C; uint32_t f10; uint8_t unk014[0x30 - 0x14]; void *anim30; uint8_t unk034[0x13C - 0x34]; int32_t snd13C; } M1Ob334b;
typedef struct M1Ai334b {
    uint8_t unk000[0x4C]; uint32_t f4C; uint8_t unk050[0x58 - 0x50]; int32_t n58; uint8_t unk05C[0x6C - 0x5C];
    int32_t snd6C; void *fx70; uint8_t unk074[0x278 - 0x74]; M1St334 *s278;
} M1Ai334b;
int sub_000833E0(void *a);

/* 0x153A00: get-up step 0: when the get-up animation ends, leave the down state into state
   0xC (stand-up trigger) or 1, with the same cleanup as 0x14B840. */
void m1_AiGetUp153A00(M1Ob334b *ob, M1Ai334b *ai) {
    M1Ob334 *o = (M1Ob334 *)ob;
    M1Ai334 *e = (M1Ai334 *)ai;
    M1St334 *s;
    if (ai->n58 != 0)
        return;
    if (!sub_000833E0(ob->anim30))
        return;
    if (sub_00156040()) {
        M1_STANDUP_EXIT(0xC);
        return;
    }
    M1_STANDUP_EXIT(1);
}

/* 0x14FF90: get-up step for state 0x14 (any other step hangs): when the animation ends,
   leave the down state into state 0xC (stand-up trigger) or 0xD, same cleanup as 0x14B840. */
void m1_AiGetUp14FF90(M1Ob334b *ob, M1Ai334b *ai) {
    M1Ob334 *o = (M1Ob334 *)ob;
    M1Ai334 *e = (M1Ai334 *)ai;
    M1St334 *s;
    if (ai->n58 != 0x14)
        for (;;);
    if (!sub_000833E0(ob->anim30))
        return;
    if (sub_00156040()) {
        M1_STANDUP_EXIT(0xC);
        return;
    }
    M1_STANDUP_EXIT(0xD);
}

int  sub_001C7EE1(void);                   /* rand */
void sub_00147580(void *obj, int32_t st, void *act);   /* regargs: st=EBX act=ESI */
void sub_00147580b(void *obj, int32_t st, void *act);  /* alias of 0x147580 */

/* 0x149650: when the get-up animation ends: stand-up trigger -> state 0xC; otherwise 7 in
   8 times hand over to 0x147580 (with k = 3), else state 5; same cleanup as 0x14B840. */
void m1_AiGetUp149650(M1Ob334b *ob, M1Ai334b *ai) {
    M1Ob334 *o = (M1Ob334 *)ob;
    M1Ai334 *e = (M1Ai334 *)ai;
    M1St334 *s;
    if (!sub_000833E0(ob->anim30))
        return;
    if (sub_00156040()) {
        M1_STANDUP_EXIT(0xC);
        return;
    }
    if (!(sub_001C7EE1() & 7)) {
        M1_STANDUP_EXIT(5);
        return;
    }
    sub_00147580(ob, 3, ai);
}

typedef struct M1Ai334c {
    uint8_t unk000[0xF8]; int32_t iF8; uint8_t unk0FC[0x104 - 0xFC]; void *p104;
    uint8_t unk108[0x278 - 0x108]; M1St334 *s278;
} M1Ai334c;
typedef struct M1Ent334 { uint8_t unk00[0x60]; float x60; float y64; float z68; } M1Ent334;
extern uint8_t *g_playerObj;
int       sub_00147270(int k, void *e);          /* regargs: k=EAX e=EDI */
M1Ent334 *sub_000C7130(void *o);
int       sub_00145940(void *o, float x, float z, float lo, float hi);
float     sub_001B2770(const void *a, const void *b);   /* distance */

/* 0x14C470: get-up choice: without the 0x400 flag hand over with k = 1; otherwise the first
   ready move of 8, 9, 0x12 (k 0x10) or 0x16 (k 5); else grab the nearest entity when it is
   closer than the player, within 80 and in the +-120 degree cone, then leave the down state
   into state 0x12 with the same cleanup as 0x14B840. */
void m1_AiGetUpPick14C470(M1Ob334b *ob, M1Ai334c *ai) {
    M1Ob334 *o = (M1Ob334 *)ob;
    M1Ai334 *e = (M1Ai334 *)ai;
    M1St334 *s;
    M1Ent334 *t;
    float dp, dt;
    if (!(ai->s278->f50 & 0x400)) {
        sub_00147580(ob, 1, ai);
        return;
    }
    if (sub_00147270(8, ai)) {
        sub_00147580(ob, 8, ai);
        return;
    }
    if (sub_00147270(9, ai)) {
        sub_00147580(ob, 9, ai);
        return;
    }
    if (sub_00147270(0x12, ai)) {
        sub_00147580(ob, 0x10, ai);
        return;
    }
    if (sub_00147270(0x16, ai)) {
        sub_00147580(ob, 5, ai);
        return;
    }
    t = sub_000C7130(ob);
    if (!t)
        return;
    dp = sub_001B2770((uint8_t *)ob + 0x60, g_playerObj + 0x60);
    dt = sub_001B2770((uint8_t *)ob + 0x60, (uint8_t *)t + 0x60);
    if (!_mm_comige_ss(_mm_set_ss(dp), _mm_set_ss(dt)))
        return;
    if (!_mm_comige_ss(_mm_set_ss(80.0f), _mm_set_ss(dt)))
        return;
    if (sub_00145940(ob, t->x60, t->z68, -2.0943952f, 2.0943952f) != 1)
        return;
    ai->p104 = t;
    ai->iF8 = 1;
    M1_STANDUP_EXIT(0x12);
}

typedef struct M1St334d { uint8_t unk00[0x38]; void *p38; uint8_t unk3C[0x68 - 0x3C]; float f68; float f6C; } M1St334d;

/* 0x1499C0: when the get-up animation ends: stand-up trigger -> state 0xC; otherwise, below
   150 on +0x68, raise +0x6C by 200 (300 without +0x38) clamped to 0..200, then state 1;
   same cleanup as 0x14B840. */
void m1_AiGetUp1499C0(M1Ob334b *ob, M1Ai334b *ai) {
    M1Ob334 *o = (M1Ob334 *)ob;
    M1Ai334 *e = (M1Ai334 *)ai;
    M1St334 *s = ai->s278;
    M1St334d *d;
    float v;
    if (!sub_000833E0(ob->anim30))
        return;
    if (sub_00156040()) {
        M1_STANDUP_EXIT(0xC);
        return;
    }
    if (150.0f > ((M1St334d *)s)->f68) {
        d = (M1St334d *)ai->s278;
        if (((M1St334d *)s)->p38)
            v = d->f6C + 200.0f;
        else
            v = d->f6C + 300.0f;
        d->f6C = v;
        if (0.0f > v)
            d->f6C = 0.0f;
        else if (v > 200.0f)
            d->f6C = 200.0f;
    }
    M1_STANDUP_EXIT(1);
}

typedef struct M1Ai334x { uint8_t unk00[0x20]; uint32_t f20; } M1Ai334x;

/* 0x14B280: when the get-up animation ends: stand-up trigger -> state 0xC; otherwise by the
   player distance: with +0x38 set hand over with k = 4 within 30 (else k = 2); without it
   leave into state 9 within 40 (else k = 2). Same cleanup as 0x14B840. */
void m1_AiGetUp14B280(M1Ob334b *ob, M1Ai334b *ai) {
    M1Ob334 *o = (M1Ob334 *)ob;
    M1Ai334 *e = (M1Ai334 *)ai;
    M1St334 *s = ai->s278;
    float d;
    if (!sub_000833E0(ob->anim30))
        return;
    if (sub_00156040()) {
        M1_STANDUP_EXIT(0xC);
        return;
    }
    d = sub_001B2770(g_playerObj + 0x60, (uint8_t *)ob + 0x60);
    if (((M1St334d *)s)->p38) {
        if (30.0f >= d) {
            sub_00147580(ob, 4, ai);
            return;
        }
    } else if (40.0f >= d) {
        M1_STANDUP_EXIT(9);
        return;
    }
    sub_00147580(ob, 2, ai);
}

/* 0x14BA50: when the get-up animation ends: stand-up trigger -> state 0xC; with the guard bit
   hand over with k = 4 (+0x38 set) or 2; otherwise raise +0x6C by 200 (+0x38 set) or 100,
   clamped to 0..200, then state 1. Same cleanup as 0x14B840. */
void m1_AiGetUp14BA50(M1Ob334b *ob, M1Ai334b *ai) {
    M1Ob334 *o = (M1Ob334 *)ob;
    M1Ai334 *e = (M1Ai334 *)ai;
    M1St334 *s = ai->s278;
    M1St334d *d;
    float v;
    if (!sub_000833E0(ob->anim30))
        return;
    if (sub_00156040()) {
        M1_STANDUP_EXIT(0xC);
        return;
    }
    if (((M1Ai334x *)ai)->f20 & 1) {
        if (((M1St334d *)s)->p38)
            sub_00147580(ob, 4, ai);
        else
            sub_00147580b(ob, 2, ai);   /* alias keeps the two calls apart */
        return;
    }
    d = (M1St334d *)ai->s278;
    if (((M1St334d *)s)->p38)
        v = d->f6C + 200.0f;
    else
        v = d->f6C + 100.0f;
    d->f6C = v;
    if (0.0f > v)
        d->f6C = 0.0f;
    else if (v > 200.0f)
        d->f6C = 200.0f;
    M1_STANDUP_EXIT(1);
}

typedef struct M1Ai334e { uint8_t unk000[0x74]; float f74; uint8_t unk078[0x278 - 0x78]; M1St334d *s278; } M1Ai334e;
extern float m1_frameTime42C858;


/* 0x14F400: get-up step for state 0xA (any other step hangs): when the animation ends leave
   into state 0xC (stand-up trigger), 7 (guard bit) or 0xA; same cleanup as 0x14B840. */
void m1_AiGetUp14F400(M1Ob334b *ob, M1Ai334b *ai) {
    M1Ob334 *o = (M1Ob334 *)ob;
    M1Ai334 *e = (M1Ai334 *)ai;
    M1St334 *s;
    if (ai->n58 != 0xA)
        for (;;);
    if (!sub_000833E0(ob->anim30))
        return;
    if (sub_00156040()) {
        M1_STANDUP_EXIT(0xC);
        return;
    }
    if (((M1Ai334x *)ai)->f20 & 1) {
        M1_STANDUP_EXIT_M(7, 0xFFDBFEBFu);   /* this exit keeps flag 0x1000 */
        return;
    }
    M1_STANDUP_EXIT(0xA);
}


typedef struct M1Tg334 { uint8_t unk00[4]; int32_t i04; uint8_t unk08[4]; uint8_t b0C; } M1Tg334;
typedef struct M1Ai334f { uint8_t unk000[0x74]; float f74; uint8_t unk078[0xF8 - 0x78]; int32_t iF8; uint8_t unk0FC[0x104 - 0xFC]; M1Tg334 *p104; } M1Ai334f;


typedef struct M1Ob334g { uint8_t unk000[0x128]; uint8_t b128; } M1Ob334g;
typedef struct M1Ai334g { uint8_t unk000[0x58]; int32_t n58; uint8_t unk05C[0x74 - 0x5C]; float f74; } M1Ai334g;
void sub_000ED780(void *o);
int  m1_AiSetState1456E0(void *o, void *e, int a, int b);
void sub_00156180(void *s, int a, int b, int c, float t);
void sub_00036750(void *o, int k);
void sub_000494D0(int id, void *pos, int k);

/* 0x152880: knock-down: flag 0x20 hands over to 0xED780. Step 0 waits for ground contact;
   step 1 enters pose 0x45, starts the down sway, plays sound 6 and effect 0x10E and waits
   0.5; step 2, once that timer runs out, leaves into state 0 (flag 0x10), 0xC (stand-up
   trigger) or 0x2A. Same cleanup as 0x14B840. */
void m1_AiKnockDown152880(M1Ob334b *ob, M1Ai334b *ai) {
    M1Ob334 *o = (M1Ob334 *)ob;
    M1Ai334 *e = (M1Ai334 *)ai;
    M1Ai334g *g = (M1Ai334g *)ai;
    M1St334 *s = ai->s278;
    if (s->f50 & 0x20) {
        sub_000ED780(ob);
        return;
    }
    switch (g->n58) {
    case 0:
        if (((M1Ob334g *)ob)->b128 & 0x18)
            g->n58 = 1;
        return;
    case 1:
        m1_AiSetState1456E0(ob, ai, 0x45, 0);
        sub_00156180(s, 0, 0, 0, m1_frameTime42C858 * 0.003f);
        sub_00036750(ob, 6);
        sub_000494D0(0x10E, (uint8_t *)ob + 0x60, 0);
        g->f74 = 0.5f;
        g->n58++;
        return;
    case 2:
        if (!(0.0f >= g->f74))
            return;
        if (s->f50 & 0x10) {
            M1_STANDUP_EXIT(0);
            return;
        }
        if (sub_00156040()) {
            M1_STANDUP_EXIT(0xC);
            return;
        }
        M1_STANDUP_EXIT(0x2A);
        return;
    }
}

typedef struct M1St334h { uint32_t f00; uint8_t unk04[0x24 - 4]; float f24; uint8_t unk28[4]; float f2C; } M1St334h;

/* 0x153240: three-stage get-up: each stage waits for its animation, stage 1 enters pose 0x38,
   stage 2 pose 0x39 with the down sway (clearing the low state bits), stage 3 leaves into
   state 0xC (stand-up trigger), 5 or 1 at random. While in the first stages the +0x24/+0x2C
   speeds decay by 5 percent per unit. Same cleanup as 0x14B840. */
void m1_AiGetUp153240(M1Ob334b *ob, M1Ai334b *ai) {
    M1Ob334 *o = (M1Ob334 *)ob;
    M1Ai334 *e = (M1Ai334 *)ai;
    M1St334 *s = ai->s278;
    M1St334h *h = (M1St334h *)s;
    switch (ai->n58) {
    case 0:
        if (!sub_000833E0(ob->anim30))
            break;
        ai->n58++;
    case 1:
        m1_AiSetState1456E0(ob, ai, 0x38, 0);
        ai->n58++;
        break;
    case 2:
        if (!sub_000833E0(ob->anim30))
            break;
        ai->n58++;
    case 3:
        m1_AiSetState1456E0(ob, ai, 0x39, 0);
        sub_00156180(s, 0, 0, 0, m1_frameTime42C858 * 0.003f);
        h->f00 &= ~7u;
        ai->n58++;
        break;
    case 4:
        if (!sub_000833E0(ob->anim30))
            break;
        ai->n58++;
    case 5:
        if (sub_00156040()) {
            M1_STANDUP_EXIT(0xC);
            return;
        }
        if (sub_001C7EE1() & 1) {
            M1_STANDUP_EXIT(5);
            return;
        }
        M1_STANDUP_EXIT(1);
        return;
    }
    if (ai->n58 <= 2) {
        h->f24 = (1.0f - m1_frameTime42C858 * 0.05f) * h->f24;
        h->f2C = (1.0f - m1_frameTime42C858 * 0.05f) * h->f2C;
    }
}

/* 0x151490: get-up end: flag 0x20 hands over to 0xED780; when the animation ends leave into
   state 0 (flag 0x10), 0xC (stand-up trigger), or 5 / 1 at random. Same cleanup as 0x14B840. */
void m1_AiGetUp151490(M1Ob334b *ob, M1Ai334b *ai) {
    M1Ob334 *o = (M1Ob334 *)ob;
    M1Ai334 *e = (M1Ai334 *)ai;
    M1St334 *s = ai->s278;
    if (s->f50 & 0x20) {
        sub_000ED780(ob);
        return;
    }
    if (!sub_000833E0(ob->anim30))
        return;
    if (s->f50 & 0x10) {
        M1_STANDUP_EXIT(0);
        return;
    }
    if (sub_00156040()) {
        M1_STANDUP_EXIT(0xC);
        return;
    }
    if (sub_001C7EE1() & 1) {
        M1_STANDUP_EXIT(5);
        return;
    }
    M1_STANDUP_EXIT(1);
}

/* 0x14EF30: get-up: flag 0x20 hands over to 0xED780; step 0 waits for the animation, then
   (step 1) leave into state 0 (flag 0x10), 0xC (stand-up trigger), 0xD (flag 4) or 1.
   Same cleanup as 0x14B840. */
void m1_AiGetUp14EF30(M1Ob334b *ob, M1Ai334b *ai) {
    M1Ob334 *o = (M1Ob334 *)ob;
    M1Ai334 *e = (M1Ai334 *)ai;
    M1St334 *s = ai->s278;
    if (s->f50 & 0x20) {
        sub_000ED780(ob);
        return;
    }
    switch (ai->n58) {
    case 0:
        if (!sub_000833E0(ob->anim30))
            return;
        ai->n58++;
    case 1:
        if (s->f50 & 0x10) {
            M1_STANDUP_EXIT(0);
            return;
        }
        if (sub_00156040()) {
            M1_STANDUP_EXIT(0xC);
            return;
        }
        if (s->f50 & 4) {
            M1_STANDUP_EXIT(0xD);
            return;
        }
        M1_STANDUP_EXIT(1);
        return;
    }
}

typedef struct M1St334k { uint8_t unk00[0x50]; uint32_t f50; uint8_t unk54[4]; uint32_t n58; float f5C; } M1St334k;

/* 0x14E950: like 0x14EF30, but first arm the down timer: from 10 hits always (288), from 5
   hits one time in 8 (216), setting flag 4. */
void m1_AiGetUp14E950(M1Ob334b *ob, M1Ai334b *ai) {
    M1Ob334 *o = (M1Ob334 *)ob;
    M1Ai334 *e = (M1Ai334 *)ai;
    M1St334 *s = ai->s278;
    M1St334k *k = (M1St334k *)s;
    float t;
    if (s->f50 & 0x20) {
        sub_000ED780(ob);
        return;
    }
    switch (ai->n58) {
    case 0:
        if (!sub_000833E0(ob->anim30))
            return;
        ai->n58++;
    case 1:
        if (k->n58 >= 10) {
            t = 288.0f;
            goto arm;
        }
        if (k->n58 >= 5 && !(sub_001C7EE1() & 7)) {
            t = 216.0f;
        arm:
            k->f50 |= 4;
            k->f5C = t;
        }
        if (s->f50 & 0x10) {
            M1_STANDUP_EXIT(0);
            return;
        }
        if (sub_00156040()) {
            M1_STANDUP_EXIT(0xC);
            return;
        }
        if (s->f50 & 4) {
            M1_STANDUP_EXIT(0xD);
            return;
        }
        M1_STANDUP_EXIT(1);
        return;
    }
}

typedef struct M1St334m { uint32_t f00; uint8_t unk04[0x24 - 4]; float f24; float f28; float f2C; } M1St334m;
typedef struct M1Ai334m { uint8_t unk000[0x58]; int32_t n58; uint8_t unk05C[0x64 - 0x5C]; int32_t pose64; } M1Ai334m;
typedef struct M1Ob334m { uint8_t unk000[0x10]; uint32_t f10; uint8_t unk014[0x128 - 0x14]; uint8_t b128; } M1Ob334m;

/* 0x1504C0: fall and get-up: flag 0x20 hands over to 0xED780. Steps: wait for the animation,
   enter the falling pose (0x35 after 0x34, 0x38 after 0x37; others hang) with state bit 8;
   wait for ground contact (clearing flag 0x10); wait, enter the landing pose (0x36 / 0x39)
   with the down sway, clearing the low state bits; wait, then leave into state 0 (flag
   0x10), 0xC (stand-up trigger) or 1. While falling the +0x24/+0x2C speeds decay by 5
   percent per unit and +0x28 gains gravity. Same cleanup as 0x14B840. */
void m1_AiFallGetUp1504C0(M1Ob334b *ob, M1Ai334b *ai) {
    M1Ob334 *o = (M1Ob334 *)ob;
    M1Ai334 *e = (M1Ai334 *)ai;
    M1St334 *s = ai->s278;
    M1St334m *h = (M1St334m *)s;
    M1Ai334m *m = (M1Ai334m *)ai;
    if (s->f50 & 0x20) {
        sub_000ED780(ob);
        return;
    }
    switch (ai->n58) {
    case 0:
        if (!sub_000833E0(ob->anim30))
            break;
        ai->n58++;
    case 1:
        if (m->pose64 == 0x34)
            m1_AiSetState1456E0(ob, ai, 0x35, 0);
        else if (m->pose64 == 0x37)
            m1_AiSetState1456E0(ob, ai, 0x38, 0);
        else
            for (;;);
        h->f00 |= 8;
        ai->n58++;
        break;
    case 2:
        if (!(((M1Ob334m *)ob)->b128 & 0x18))
            break;
        ((M1Ob334m *)ob)->f10 &= ~0x10u;
        ai->n58++;
        break;
    case 3:
        if (!sub_000833E0(ob->anim30))
            break;
        ai->n58++;
    case 4:
        if (m->pose64 == 0x35)
            m1_AiSetState1456E0(ob, ai, 0x36, 0);
        else if (m->pose64 == 0x38)
            m1_AiSetState1456E0(ob, ai, 0x39, 0);
        else
            for (;;);
        sub_00156180(s, 0, 0, 0, m1_frameTime42C858 * 0.003f);
        h->f00 &= ~3u;
        ai->n58++;
        break;
    case 5:
        if (!sub_000833E0(ob->anim30))
            break;
        ai->n58++;
    case 6:
        if (s->f50 & 0x10) {
            M1_STANDUP_EXIT(0);
            return;
        }
        if (sub_00156040()) {
            M1_STANDUP_EXIT(0xC);
            return;
        }
        M1_STANDUP_EXIT(1);
        return;
    }
    if (ai->n58 <= 3) {
        h->f24 = (1.0f - m1_frameTime42C858 * 0.05f) * h->f24;
        h->f2C = (1.0f - m1_frameTime42C858 * 0.05f) * h->f2C;
        h->f28 = m1_frameRate42C85C * m1_frameRate42C85C * 147.0f + h->f28;
    }
}
