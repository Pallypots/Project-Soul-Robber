/* Area m1, file 67: rig blends and timed waits. Names inferred. */
#include <stdint.h>

typedef struct M1RigH {
    uint8_t unk00[0xC];
    float   f0C, f10;          /* +0x0C */
    uint8_t unk14[0x24 - 0x14];
    float   q24[4];            /* +0x24 */
    uint8_t unk34[0x44 - 0x34];
    int32_t f44;               /* +0x44 */
    uint8_t unk48[0x54 - 0x48];
    float   f54;               /* +0x54 */
} M1RigH;
typedef struct M1StepH {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x58 - 0x50];
    int32_t state58;           /* +0x58 */
    uint8_t unk05C[0x278 - 0x5C];
    M1RigH *rig278;            /* +0x278 */
} M1StepH;
extern float m1_frameTime42C858, m1_frameRate42C85C;
int  sub_001456E0(void *o, void *s, int a, int b);
void sub_000414A0(int v);

/* 0x00158430: 0x1456E0(0x13), rig quaternion +0x24 = (0, 0, 0, 1), rig +0x10 = 0, rig +0x0C =
 * frame time * 0.005, clear h +0x4C bits 0x70, 0x414A0(1), rig +0x44 = 0, rig +0x54 += 40
 * clamped to 0..200, state 10. */
void m1_RigBlend158430(void *o, M1StepH *h)
{
    M1RigH *r = h->rig278;
    M1RigH *p;
    float v;
    sub_001456E0(o, h, 0x13, 0);
    r->q24[2] = 0.0f;
    r->q24[1] = 0.0f;
    r->q24[0] = 0.0f;
    r->q24[3] = 1.0f;
    r->f10 = 0.0f;
    r->f0C = m1_frameTime42C858 * 0.005f;
    h->flags4C &= ~0x70u;
    sub_000414A0(1);
    r->f44 = 0;
    p = h->rig278;
    v = p->f54 + 40.0f;
    p->f54 = v;
    if (0.0f > v)
        p->f54 = 0.0f;
    else if (v > 200.0f)
        p->f54 = 200.0f;
    h->state58 = 10;
}

typedef struct M1Cfg74 { uint8_t flags00; } M1Cfg74;
typedef struct M1StepT2 {
    uint8_t unk00[0x54];
    int32_t state54;           /* +0x54 */
    uint8_t unk58[4];
    float   t5C;               /* +0x5C */
    uint8_t unk60[0x74 - 0x60];
    M1Cfg74 *cfg74;            /* +0x74 */
} M1StepT2;
typedef struct M1ObjT2 { uint8_t unk00[0x30]; int32_t anim30; } M1ObjT2;
extern float m1_wait3F8C18;
int  sub_00036750(void *o, int v);
int  sub_000833E0(int a);
void sub_001671D0(void *o, void *h, int next);

/* 0x0016B030: state 0 (with cfg flag 2 also 0x36750(0)) moves straight to state 1; state 1
 * waits for the animation, then a 240-frame timer and state 2; state 2, once the timer has
 * run out, sets the shared wait 0x3F8C18 to 480 frames (cfg flag 2) and goes on (0x1671D0(2)). */
void m1_Wait16B030(M1ObjT2 *o, M1StepT2 *h)
{
    M1Cfg74 *c = h->cfg74;
    switch (h->state54) {
    case 0:
        if (c->flags00 & 2)
            sub_00036750(o, 0);
        h->state54++;
        /* fall through */
    case 1:
        if (sub_000833E0(o->anim30) != 0) {
            h->t5C = 240.0f / m1_frameTime42C858 * m1_frameRate42C85C;
            h->state54++;
        }
        break;
    case 2:
        if (0.0f > h->t5C) {
            if (c->flags00 & 2)
                m1_wait3F8C18 = 480.0f / m1_frameTime42C858 * m1_frameRate42C85C;
            sub_001671D0(o, h, 2);
        }
        break;
    }
}

typedef struct M1Drop0DC { float pos00[4]; uint8_t unk10[0xDC - 0x10]; } M1Drop0DC;
typedef struct M1DropSt { uint8_t unk00[0xC]; int32_t state0C; int32_t n10; int32_t id14; } M1DropSt;
typedef struct M1DropObj { uint8_t unk00[0x60]; float pos60[4]; } M1DropObj;
extern M1Drop0DC m1_drops420F60[];
void sub_000F5D40(float *dst, const float *src);
int  sub_000A9020(int size, const float *pos);

/* 0x0017C140: spawns a drop 5 below o sized by the count (3 for 100+, 2 for 30+, 1 for 10+,
 * else 0) via 0xA9020 and keeps its slot; afterwards keeps moving it to that point. */
void m1_Drop17C140(M1DropObj *o, void *h, M1DropSt *s)
{
    float v[4];
    int lvl;
    int id;
    if (s->n10 <= 0)
        return;
    sub_000F5D40(v, o->pos60);
    v[1] = v[1] - 5.0f;
    switch (s->state0C) {
    case 0:
        if (s->n10 >= 100)
            lvl = 3;
        else if (s->n10 >= 30)
            lvl = 2;
        else
            lvl = s->n10 >= 10;
        id = sub_000A9020(lvl, v);
        s->id14 = id;
        if (id >= 0)
            s->state0C++;
        break;
    case 1:
        sub_000F5D40(m1_drops420F60[s->id14].pos00, v);
        break;
    }
}

typedef struct M1PhaseT {
    int32_t state00;           /* +0x00 */
    uint8_t unk04[4];
    float   t08;               /* +0x08 */
    int32_t phase0C;           /* +0x0C */
    float   start10, len14;    /* +0x10 */
    float   delay18;           /* +0x18 */
    float   show1C;            /* +0x1C */
} M1PhaseT;
void sub_001130F0(void *o, void *h, int on);
void sub_00113370(void *h, void *s);

/* 0x00147090: as 0x155780 but phase 0 counts its delay +0x18 down by the frame rate and
 * moves to phase 1 once it is no longer positive (spins unless start and length are
 * positive). */
void m1_PhasedT147090(void *o, void *h, M1PhaseT *s)
{
    float t;
    switch (s->phase0C) {
    case 0:
        t = s->delay18 - m1_frameRate42C85C;
        s->delay18 = t;
        if (!(0.0f >= t))
            break;
        if (!(s->start10 > 0.0f) || !(s->len14 > 0.0f))
            for (;;) ;
        s->phase0C = 1;
        break;
    case 1:
        if (s->t08 > s->start10) {
            sub_001130F0(o, h, (int)s->show1C);
            s->phase0C++;
        }
        break;
    case 2:
        if (s->t08 - s->start10 > s->len14) {
            if (s->state00 != 0)
                s->state00 = 1;
            sub_00113370(h, s);
            return;
        }
        break;
    }
    if (s->state00 != 0)
        s->state00 = 2;
}

typedef struct M1RigH2 {
    uint8_t unk00[0xC];
    float   f0C, f10;          /* +0x0C */
    uint8_t unk14[0x24 - 0x14];
    float   q24[4];            /* +0x24 */
    uint8_t unk34[0x54 - 0x34];
    float   f54, f58;          /* +0x54 */
} M1RigH2;
typedef struct M1StepH2 { uint8_t unk000[0x4C]; uint32_t flags4C; uint8_t unk050[0x278 - 0x50]; M1RigH2 *rig278; } M1StepH2;

/* 0x00157080: 0x1456E0(0x10), rig +0x0C = frame time * 0.005, rig quaternion +0x24 =
 * (0, 0, 0 - frame rate * 0, 1), rig +0x10 = 0, clear h +0x4C bits 0x70, rig +0x54 += 50
 * clamped to 0..200, rig +0x58 = 5. */
void m1_RigBlend157080(void *o, M1StepH2 *h)
{
    M1RigH2 *r = h->rig278;
    M1RigH2 *p;
    float v;
    sub_001456E0(o, h, 0x10, 0);
    r->f0C = m1_frameTime42C858 * 0.005f;
    r->q24[1] = 0.0f;
    r->q24[0] = 0.0f;
    r->f10 = 0.0f;
    r->q24[2] = 0.0f - m1_frameRate42C85C * 0.0f;
    r->q24[3] = 1.0f;
    h->flags4C &= ~0x70u;
    p = h->rig278;
    v = p->f54 + 50.0f;
    p->f54 = v;
    if (0.0f > v)
        p->f54 = 0.0f;
    else if (v > 200.0f)
        p->f54 = 200.0f;
    r->f58 = 5.0f;
}
