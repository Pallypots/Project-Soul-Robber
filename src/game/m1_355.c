/* Area m1, file 355: flying enemy perch / dive-check state. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Pt355 { float v[4]; int32_t i10; } M1Pt355;   /* 0x14 bytes */
typedef struct M1St355 { uint32_t f00; int32_t i04; int32_t i08; float vC[4]; int32_t i1C; float f20, f24, f28, f2C; } M1St355;
typedef struct M1Ai355 { uint8_t unk00[0x4C]; uint32_t f4C; uint8_t unk50[4]; int32_t n54; uint8_t unk58[4]; float f5C; uint8_t unk60[0x74 - 0x60]; M1St355 *s74; } M1Ai355;
typedef struct M1Ob355 { uint8_t unk00[0x54]; float yaw54; uint8_t unk58[0x60 - 0x58]; float p60[4]; } M1Ob355;
extern M1Ob355 *g_playerObj;
extern M1Pt355 *r3d_vecs31F3E0[];
extern float m1_frameTime42C858, m1_frameRate42C85C;
float sub_001B2730(const void *a, const void *b);     /* flat distance */
void  r3_SetState16C820(M1Ai355 *e, int st);          /* regargs: e=EAX */
float sub_00113290(void *o, const void *p);           /* signed angle to p */
void  sub_000F5D40(void *d, const void *s);

/* 0x16C860: perch. Step 0 arms it (flags, a 10/s hover, 120-unit wait); step 1 turns
   towards the player while waiting (one degree a frame when more than 20 degrees off);
   when the wait ends it dives (state 4) at a player close below, or otherwise flies off
   (state 3) towards the first marked point of its route. */
void m1_FlyerPerch16C860(M1Ob355 *o, M1Ai355 *e) {
    M1Ob355 *pl = g_playerObj;
    M1St355 *s = e->s74;
    M1St355 *t;
    M1Pt355 *r, *p;
    int i;
    float a;
    switch (e->n54) {
    case 0:
        e->f4C |= 1;
        s->f00 |= 0x80;
        t = e->s74;
        t->f28 = 10.0f;
        t->f24 = 0.0f;
        t->f2C = 0.0f;
        t->f20 = 0.0f;
        t->f00 |= 0x1000;
        e->f5C = 120.0f / m1_frameTime42C858 * m1_frameRate42C85C;
        e->n54++;
    case 1:
        if (0.0f >= e->f5C) {
            if (40.0f > sub_001B2730(o->p60, pl->p60) && 20.0f > o->p60[1] - pl->p60[1]) {
                r3_SetState16C820(e, 4);
                return;
            }
            r3_SetState16C820(e, 3);
            r = r3d_vecs31F3E0[s->i04];
            i = 0;
            for (p = r; (uint8_t)p->i10 != 1 && p->i10 >= 0; p++)
                i++;
            p = &r[i];
            sub_000F5D40(s->vC, p->v);
            s->i08 = i;
            s->i1C = p->i10;
            s->f00 |= 0x10;
            return;
        }
        a = sub_00113290(o, pl->p60);
        if (!(a >= 0.349065870f) && !(-0.349065870f >= a))
            return;
        if (a > 0.0f)
            o->yaw54 = o->yaw54 + 0.0174532924f;
        else
            o->yaw54 = o->yaw54 - 0.0174532924f;
        return;
    }
}

typedef struct M1St355b { uint32_t f00; int32_t i04; int32_t i08; float vC[4]; int32_t i1C; uint8_t unk20[0x3C - 0x20]; float f3C; } M1St355b;
void sub_001671D0(void *o, void *e, int k);
void sub_001671D0b(void *o, void *e, int k);   /* alias of 0x1671D0 */

/* 0x16CA10: patrol hover. Step 0 clears the perch flags and the wait; step 1, while the
   state block's top bit is set, keeps turning towards the player (half a degree a frame
   when more than 30 degrees off); otherwise it dives (state 4) at a player close below, or
   steers along its route (holding the heading when free) and heads for the first marked
   route point. */
void m1_FlyerHover16CA10(M1Ob355 *o, M1Ai355 *e) {
    M1Ob355 *pl = g_playerObj;
    M1St355 *s = e->s74;
    M1St355b *t;
    M1Pt355 *r, *p;
    int i;
    float a;
    switch (e->n54) {
    case 0:
        e->f4C &= ~1u;
        s->f00 &= ~6u;
        e->f5C = 0.0f;
        s->f00 |= 0x200;
        e->n54++;
    case 1:
        if ((int32_t)s->f00 >= 0) {
            if (40.0f > sub_001B2730(o->p60, pl->p60) && 20.0f > o->p60[1] - pl->p60[1]) {
                r3_SetState16C820(e, 4);
                return;
            }
            t = (M1St355b *)e->s74;
            t->f00 &= ~0xC00u;
            sub_001671D0(o, e, 3);
            if (!(t->f00 & 0xC00)) {
                t->f00 |= 0x2000;
                t->f3C = o->yaw54;
            } else {
                t->f00 &= ~0x2000u;
            }
            r = r3d_vecs31F3E0[s->i04];
            i = 0;
            for (p = r; (uint8_t)p->i10 != 1 && p->i10 >= 0; p++)
                i++;
            p = &r[i];
            sub_000F5D40(s->vC, p->v);
            s->i08 = i;
            s->i1C = p->i10;
            s->f00 |= 0x10;
            return;
        }
        a = sub_00113290(o, pl->p60);
        if (!(a >= 0.523598790f) && !(-0.523598790f >= a))
            return;
        if (a > 0.0f)
            o->yaw54 = o->yaw54 + 0.00872664619f;
        else
            o->yaw54 = o->yaw54 - 0.00872664619f;
        return;
    }
}

typedef struct M1Ob355c { uint8_t unk00[0x30]; void *anim30; uint8_t unk34[0x54 - 0x34]; float yaw54; uint8_t unk58[0x60 - 0x58]; float p60[4]; } M1Ob355c;
int sub_000833E0(void *a);

/* 0x16CD30: turn-and-screech. Step 0 starts a 10-unit wait; step 1 turns quickly towards
   the player (10 degrees a frame when more than 20 degrees off) until the wait ends; step 2
   keeps turning slowly while the screech animation plays, then flies off along its route
   (state 3) when the player is close below, or goes back to state 1. */
void m1_FlyerScreech16CD30(M1Ob355c *o, M1Ai355 *e) {
    M1Ob355 *pl = g_playerObj;
    M1St355 *s = e->s74;
    M1Pt355 *r, *p;
    int i;
    float a;
    switch (e->n54) {
    case 0:
        e->f4C |= 1;
        e->f5C = 10.0f / m1_frameTime42C858 * m1_frameRate42C85C;
        e->n54 = 1;
    case 1:
        if (0.0f >= e->f5C) {
            e->n54++;
            return;
        }
        a = sub_00113290(o, pl->p60);
        if (!(a >= 0.349065870f) && !(-0.349065870f >= a))
            return;
        if (a > 0.0f)
            o->yaw54 = o->yaw54 + 0.174532935f;
        else
            o->yaw54 = o->yaw54 - 0.174532935f;
        return;
    case 2:
        if (sub_000833E0(o->anim30)) {
        e->f4C &= ~1u;
        if (40.0f > sub_001B2730(o->p60, pl->p60) && 20.0f > o->p60[1] - pl->p60[1]) {
            s->f00 |= 2;
            r3_SetState16C820(e, 3);
            r = r3d_vecs31F3E0[s->i04];
            i = 0;
            for (p = r; (uint8_t)p->i10 != 1 && p->i10 >= 0; p++)
                i++;
            p = &r[i];
            sub_000F5D40(s->vC, p->v);
            s->i08 = i;
            s->i1C = p->i10;
            s->f00 |= 0x10;
            return;
        }
        r3_SetState16C820(e, 1);
        return;
        }
        a = sub_00113290(o, pl->p60);
        if (!(a >= 0.349065870f) && !(-0.349065870f >= a))
            return;
        if (a > 0.0f)
            o->yaw54 = o->yaw54 + 0.0174532924f;
        else
            o->yaw54 = o->yaw54 - 0.0174532924f;
        return;
    }
}

typedef struct M1St355d { uint32_t f00; uint8_t unk04[4]; float f08; } M1St355d;
typedef struct M1Ai355d { uint8_t unk00[0x54]; int32_t n54; uint8_t unk58[4]; float f5C; float f60; uint8_t unk64[0x74 - 0x64]; M1St355d *s74; } M1Ai355d;
int  sub_00169D30(void *o);                   /* regargs: o=EDI */
void sub_00167200(void *o, void *e, int k);
void sub_00036750(void *o, int k);
int  sub_001C7EE1(void);                      /* rand */

/* 0x16A170: flyer idle: steer by the pending flags (0x40 -> 4, 0x20 or a ready swoop -> 6);
   step 0 starts the idle loop, step 1 waits for the cue and a short delay and plays the cry,
   step 2 at the end of the animation picks a random 90..270 unit roam timer and 30..60 unit
   wait and steers back to 1. */
void m1_FlyerIdle16A170(M1Ob355c *o, M1Ai355d *e) {
    M1St355d *s = e->s74;
    int k = -1;
    if (s->f00 & 0x40)
        k = 4;
    if (s->f00 & 0x20)
        k = 6;
    if (sub_00169D30(o)) {
        k = 6;
        sub_001671D0(o, e, k);
    } else if (k > 0) {
        sub_001671D0(o, e, k);
    }
    switch (e->n54) {
    case 0:
        sub_00167200(o, e, 4);
        e->n54++;
    case 1:
        if ((s->f00 & 2) && e->f60 > 45.0f / m1_frameTime42C858 * m1_frameRate42C85C) {
            sub_00036750(o, 0);
            e->n54++;
        }
    case 2:
        if (sub_000833E0(o->anim30)) {
            s->f08 = ((float)(sub_001C7EE1() % 180) + 90.0f) / m1_frameTime42C858 * m1_frameRate42C85C;
            e->f5C = ((float)(sub_001C7EE1() % 30) + 30.0f) / m1_frameTime42C858 * m1_frameRate42C85C;
            sub_001671D0(o, e, 1);
        }
        return;
    }
}

/* 0x169EA0: flyer steering pick: flag 0x40 -> 4, flag 0x20 -> 6; once the wait is over a
   ready swoop -> 6, else 3 while the roam timer runs or 2 when it has run out. */
void m1_FlyerSteer169EA0(M1Ob355c *o, M1Ai355d *e) {
    M1St355d *s = e->s74;
    if (s->f00 & 0x40) {
        sub_001671D0(o, e, 4);
        return;
    }
    if (s->f00 & 0x20) {
        sub_001671D0b(o, e, 6);   /* alias keeps this call apart */
        return;
    }
    if (!(0.0f > e->f5C))
        return;
    if (sub_00169D30(o)) {
        sub_001671D0(o, e, 6);
        return;
    }
    sub_001671D0(o, e, 0.0f > s->f08 ? 3 : 2);
}

typedef struct M1St355e { uint32_t f00; uint8_t unk04[8]; float vC[4]; uint8_t unk1C[0x30 - 0x1C]; float f30; } M1St355e;
typedef struct M1Ai355e { uint8_t unk00[0x50]; uint32_t n50; uint8_t unk54[0x74 - 0x54]; M1St355e *s74; } M1Ai355e;
void sub_001AD9F0(float *d, const void *a, const void *b);   /* d = a - b */
void sub_001AD7E0(float *d, const float *s);                 /* normalise */
void sub_001ADBA0(float *d, const float *s, float k);        /* d = s * k */
void sub_001AD940(float *m);                                 /* identity */
void sub_001AD8E0(float *d, const float *s, float a);        /* rotate about Y */
void sub_001AD9B0(float *d, const float *m, const float *v);
void sub_001ADAF0(float *d, const float *a, const float *b); /* d = a + b */

/* 0x16C560: circle the anchor: take the flat offset from the anchor at radius +0x30,
   rotate it 60 (states 7..10) or 120 degrees ahead (sign by flag 0x100), and turn towards
   that point, limited to 2 degrees per frame squared. regargs: e=EBX. */
void m1_FlyerCircle16C560(M1Ob355 *o, M1Ai355e *e) {
    M1St355e *s = e->s74;
    float v[4], w[4], t[4], m[16];
    float rate, a, lim;
    volatile uint32_t n;
    sub_001AD9F0(v, o->p60, s->vC);
    v[1] = 0.0f;
    sub_001AD7E0(v, v);
    sub_001ADBA0(v, v, s->f30);
    sub_001AD940(m);
    n = e->n50;
    if (n >= 7 && n <= 10)
        rate = 60.0f;
    else
        rate = 120.0f;
    if (!(s->f00 & 0x100))
        rate = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(rate), _mm_set_ss(-1.0f)));
    sub_001AD8E0(m, m, rate * 0.0174532924f);
    sub_001AD9B0(w, m, v);
    sub_001ADAF0(t, w, s->vC);
    a = sub_00113290(o, t);
    lim = m1_frameTime42C858 * 0.0349065848f * m1_frameTime42C858;
    if (a > lim)
        a = lim;
    else if (0.0f - lim > a)
        a = 0.0f - lim;
    o->yaw54 = o->yaw54 + a;
}
