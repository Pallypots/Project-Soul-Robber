/* Area m1, file 360: second enemy type's stand-up exits (shared cleanup). Names inferred. */
#include <stdint.h>

typedef struct M1St360 { uint32_t f00; float f04; float f08; uint8_t unk0C[0x38 - 0x0C]; void *p38; uint8_t unk3C[4]; uint32_t f40; uint8_t unk44[0x50 - 0x44]; float f50; } M1St360;
typedef struct M1Ai360 {
    uint8_t unk000[0x4C]; uint32_t f4C; uint8_t unk050[0x6C - 0x50]; int32_t snd6C; void *fx70;
    uint8_t unk074[0x278 - 0x74]; M1St360 *s278;
} M1Ai360;
typedef struct M1Ob360 { uint8_t unk000[0x0C]; uint32_t f0C; uint32_t f10; uint8_t unk014[0x30 - 0x14]; void *anim30; uint8_t unk034[0x60 - 0x34]; float pos60[3]; uint8_t unk06C[0x13C - 0x6C]; int32_t snd13C; } M1Ob360;
extern float m1_frameRate42C85C;
int  sub_000833E0(void *a);
int  sub_00156040(void);                                    /* regargs: s=EBX */
void m1_AiReset1134B0(void *e);
void sub_00113AA0(void *o, void *e);
void m1_SndStop048250(int h);
void m1_ObjSnd05BE30(int h);
void sub_00033A70(void *p);
int  m1_AiGoto113040(void *o, void *e, int st);
void sub_00147FD0(void *p, int k);
int  sub_001C7EE1(void);                                    /* rand */

#define M1_STANDUP2_EXIT(k)                                  \
    s = e->s278;                                             \
    m1_AiReset1134B0(e);                                     \
    o->f0C |= 0xE0;                                          \
    o->f10 &= 0xFFFFFECAu;                                   \
    e->f4C &= ~0x100u;                                       \
    f = s->f40 & 0xFFFBF579u;                                \
    s->f00 &= ~0x17u;                                        \
    s->f40 = f;                                              \
    s->f04 = -10.0f;                                         \
    s->f08 = m1_frameRate42C85C * 10.0f;                     \
    if (f & 0x4000) {                                        \
        sub_00113AA0(o, e);                                  \
        e->f4C |= 0x200;                                     \
        s->f40 &= ~0x4000u;                                  \
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

/* 0x15CF20: when the get-up animation ends leave into state 0x18 (stand-up trigger), or
   cue the helper and leave into 4 (one time in 8) or 2. */
void m1_AiGetUp15CF20(M1Ob360 *o, M1Ai360 *e) {
    M1St360 *s = e->s278;
    uint32_t f;
    if (!sub_000833E0(o->anim30))
        return;
    if (sub_00156040()) {
        M1_STANDUP2_EXIT(0x18);
        return;
    }
    s->f40 |= 0x1000;
    sub_00147FD0(s->p38, 2);
    if (sub_001C7EE1() & 7) {
        M1_STANDUP2_EXIT(2);
        return;
    }
    M1_STANDUP2_EXIT(4);
}

typedef struct M1Hit360 { int32_t kind00; uint8_t unk04[8]; float dmg0C; uint8_t unk10[0x20]; } M1Hit360;   /* 0x30 bytes */
typedef struct M1St360b { uint8_t unk000[0x38]; void *p38; uint8_t unk3C[4]; uint32_t f40; int32_t i44; uint8_t unk48[0x1B8 - 0x48]; M1Hit360 hit1B8; } M1St360b;
typedef struct M1Ai360b { uint8_t unk000[0x274]; float f274; M1St360b *s278; } M1Ai360b;
int  sub_001550E0(void);                                    /* regargs */
int  sub_00146030(int kind);
void sub_0015A270(void *o, int k);                          /* regargs: e=ESI */

/* 0x15A550: take a hit (second enemy type): dead or flagged enemies ignore it; store the
   hit and subtract the damage (death flags the body); react with the state 0x1550E0 picks
   (0x25 only counts a damaging hit), then tell the helper whether it died and pass on a
   pending cue. Returns 1 for kind-1 hits, else -1. */
int m1_TakeHit15A550(M1Ob360 *o, M1Ai360b *e, M1Hit360 *hit) {
    M1St360b *s;
    volatile int f;
    float v;
    int k, r;
    if (o->f10 & 8)
        return 0;
    s = e->s278;
    if (*(uint8_t *)&s->f40 & 0x10)
        return 0;
    s->hit1B8 = *hit;
    v = e->f274 - s->hit1B8.dmg0C;
    e->f274 = v;
    if (0.0f >= v) {
        e->f274 = 0.0f;
        o->f10 |= 8;
        s->f40 |= 0x10;
    }
    k = sub_001550E0();
    r = sub_00146030(s->hit1B8.kind00) == 1 ? 1 : -1;
    if (k == 0x25) {
        if (s->hit1B8.dmg0C > 0.0f)
            s->i44++;
    } else {
        sub_0015A270(o, k);
    }
    if (s->p38) {
        f = 0;
        if (s->f40 & 0x10)
            f = 1;
        sub_00147FD0(s->p38, f);
        if (s->f40 & 0x1000) {
            s->f40 &= ~0x1000u;
            sub_00147FD0(s->p38, 3);
        }
    }
    return r;
}


/* 0x15D1F0: when the get-up animation ends leave into state 0x18 (stand-up trigger); a
   flagged enemy reacts with state 9 instead; otherwise leave into 4 (one time in 8) or 2. */
void m1_AiGetUpB15D1F0(M1Ob360 *o, M1Ai360 *e) {
    M1St360 *s;
    uint32_t f;
    if (!sub_000833E0(o->anim30))
        return;
    if (sub_00156040()) {
        M1_STANDUP2_EXIT(0x18);
        return;
    }
    if (*((uint8_t *)e + 0x20) & 1) {
        sub_0015A270(o, 9);
        return;
    }
    if (sub_001C7EE1() & 7) {
        M1_STANDUP2_EXIT(2);
        return;
    }
    M1_STANDUP2_EXIT(4);
}

