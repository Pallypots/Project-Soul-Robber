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


/* 0x161C90: (must be in mode 10, else hang) when the get-up animation ends leave into 0x13
   or 1 for a flagged enemy (bit 0x10000 picks), else into 0x15. */
void m1_AiGetUpC161C90(M1Ob360 *o, M1Ai360 *e) {
    M1St360 *s;
    uint32_t f, g;
    if (*(int32_t *)((uint8_t *)e + 0x58) != 10)
        for (;;);
    if (!sub_000833E0(o->anim30))
        return;
    g = *(uint32_t *)((uint8_t *)e + 0x20);
    if (g & 1) {
        if (g & 0x10000) {
            M1_STANDUP2_EXIT(0x13);
            return;
        }
        M1_STANDUP2_EXIT(1);
        return;
    }
    M1_STANDUP2_EXIT(0x15);
}

int  sub_00185420(void *o);
int  sub_000494D0(int id, const float *pos, int k);         /* start a 3D sound */

/* Same cleanup, but starts sound 0x10F at the body (if none is playing) instead of stopping it. */
#define M1_STANDUP2_EXIT_SND(k)                                  s = e->s278;                                                 m1_AiReset1134B0(e);                                         o->f0C |= 0xE0;                                              o->f10 &= 0xFFFFFECAu;                                       e->f4C &= ~0x100u;                                           f = s->f40 & 0xFFFBF579u;                                    s->f00 &= ~0x17u;                                            s->f40 = f;                                                  s->f04 = -10.0f;                                             s->f08 = m1_frameRate42C85C * 10.0f;                         if (f & 0x4000) {                                                sub_00113AA0(o, e);                                          e->f4C |= 0x200;                                             s->f40 &= ~0x4000u;                                      }                                                            if (e->snd6C == -1)                                              e->snd6C = sub_000494D0(0x10F, o->pos60, 1);             m1_ObjSnd05BE30(o->snd13C);                                  if (e->fx70) {                                                   sub_00033A70(e->fx70);                                       e->fx70 = 0;                                             }                                                            m1_AiGoto113040(o, e, k)

/* 0x15E300: when the get-up animation ends leave into 0x18 (stand-up trigger); an enemy
   without flag 0x10000 leaves into 6; otherwise react with state 9 when 0x185420 reports 3,
   else leave into 0xD. */
void m1_AiGetUpD15E300(M1Ob360 *o, M1Ai360 *e) {
    M1St360 *s;
    uint32_t f;
    if (!sub_000833E0(o->anim30))
        return;
    if (sub_00156040()) {
        M1_STANDUP2_EXIT(0x18);
        return;
    }
    if (!(*((uint8_t *)e + 0x22) & 1)) {
        M1_STANDUP2_EXIT(6);
        return;
    }
    if (sub_00185420(o) == 3) {
        sub_0015A270(o, 9);
        return;
    }
    M1_STANDUP2_EXIT_SND(0xD);
}

/* 0x164EE0: (mode 0 only) when the get-up animation ends leave into 0x18 (stand-up
   trigger); with flag 0x10000 react with state 9 (flag 1) or leave into 2, else into 1. */
void m1_AiGetUpE164EE0(M1Ob360 *o, M1Ai360 *e) {
    M1St360 *s;
    uint32_t f, g;
    if (*(int32_t *)((uint8_t *)e + 0x58) != 0)
        return;
    if (!sub_000833E0(o->anim30))
        return;
    if (sub_00156040()) {
        M1_STANDUP2_EXIT(0x18);
        return;
    }
    g = *(uint32_t *)((uint8_t *)e + 0x20);
    if (g & 0x10000) {
        if (g & 1) {
            sub_0015A270(o, 9);
            return;
        }
        M1_STANDUP2_EXIT(2);
        return;
    }
    M1_STANDUP2_EXIT(1);
}


extern float m1_frameTime42C858;
void  sub_00185540(void *o);
void  sub_000ED780(void *o);
void  sub_00036750(void *o, int k);
void  m1_AiSetState1456E0(void *o, void *e, int st, int k);

/* 0x163FB0: knocked flat. A grabbed enemy (flag 0x20) only runs the grab update. Phase 0
   waits for a ground contact (body bits 0x18); phase 1 sets the knocked state, zeroes the
   speeds, plays sound 0x10E and starts a half-second timer; phase 2 waits for the timer,
   then leaves into 0 (dead), 0x18 (stand-up trigger) or 0x38. */
void m1_AiKnockedFlat163FB0(M1Ob360 *o, M1Ai360 *e) {
    M1St360 *s = e->s278;
    float *sf = (float *)s;
    uint32_t f, g;
    g = s->f40;
    if (g & 0x20) {
        sub_00185540(o);
        sub_000ED780(o);
        return;
    }
    switch (*(int32_t *)((uint8_t *)e + 0x58)) {
    case 0:
        if (*((uint8_t *)o + 0x128) & 0x18)
            *(int32_t *)((uint8_t *)e + 0x58) = 1;
        return;
    case 1:
        m1_AiSetState1456E0(o, e, 0x45, 0);
        sf[11] = 0.0f;
        sf[10] = 0.0f;
        sf[9] = 0.0f;
        sf[12] = 1.0f;
        sf[4] = 0.0f;
        sf[3] = m1_frameTime42C858 * 0.005f;
        sub_00036750(o, 6);
        sub_000494D0(0x10E, o->pos60, 0);
        *(float *)((uint8_t *)e + 0x74) = 0.5f;
        (*(int32_t *)((uint8_t *)e + 0x58))++;
        return;
    case 2:
        if (0.0f >= *(float *)((uint8_t *)e + 0x74)) {
            if (g & 0x10) {
                M1_STANDUP2_EXIT(0);
                return;
            }
            if (sub_00156040()) {
                M1_STANDUP2_EXIT(0x18);
                return;
            }
            M1_STANDUP2_EXIT(0x38);
        }
        return;
    }
}

int   sub_00145780(void *o, float r);
void  sub_00113190(void *o, void *e, int k);

/* 0x15B300: getting up from a fall. When the animation ends leave into 0x18 (stand-up trigger);
   a flagged enemy reacts with state 9 (0x185420 reports 3) or leaves into 0xD with sound
   0x10F; otherwise into 2 (or 4 one time in 4). Every frame, within 14 units of the landing
   spot, notify 0x113190. */
void m1_AiFallGetUp15B300(M1Ob360 *o, M1Ai360 *e) {
    M1St360 *s;
    uint32_t f;
    if (sub_000833E0(o->anim30)) {
        if (sub_00156040()) {
            M1_STANDUP2_EXIT(0x18);
        } else if (*((uint8_t *)e + 0x20) & 1) {
            if (sub_00185420(o) == 3) {
                sub_0015A270(o, 9);
            } else {
                M1_STANDUP2_EXIT_SND(0xD);
            }
        } else if (sub_001C7EE1() & 3) {
            M1_STANDUP2_EXIT(2);
        } else {
            M1_STANDUP2_EXIT(4);
        }
    }
    if (sub_00145780(o, 14.0f))
        sub_00113190(o, e, 1);
}

/* 0x163290: getting up after a knock-down. A grabbed enemy only runs the grab update. When
   the animation ends leave into 0 (dead), 0x18 (stand-up trigger), state 9 or 2 (flag
   0x10000, picked by flag 1), else 6. */
void m1_AiKnockGetUp163290(M1Ob360 *o, M1Ai360 *e) {
    M1St360 *s = e->s278;
    uint32_t f, g;
    if (*(uint8_t *)&s->f40 & 0x20) {
        sub_00185540(o);
        sub_000ED780(o);
        return;
    }
    if (!sub_000833E0(o->anim30))
        return;
    if (*(uint8_t *)&s->f40 & 0x10) {
        M1_STANDUP2_EXIT(0);
        return;
    }
    if (sub_00156040()) {
        M1_STANDUP2_EXIT(0x18);
        return;
    }
    g = *(uint32_t *)((uint8_t *)e + 0x20);
    if (g & 0x10000) {
        if (g & 1) {
            sub_0015A270(o, 9);
            return;
        }
        M1_STANDUP2_EXIT(2);
        return;
    }
    M1_STANDUP2_EXIT(6);
}

/* 0x1648B0: tumble. Phases: wait for the animation, set the tumble state (0x38); wait,
   set the landing state (0x39) and zero the speeds; wait, then leave into 0x18 (stand-up
   trigger), state 9 or 2 (flag 0x10000, picked by flag 1), else 6. During the first three
   phases the side speeds bleed off by 5% per frame unit. */
void m1_AiTumble1648B0(M1Ob360 *o, M1Ai360 *e) {
    M1St360 *s = e->s278;
    float *sf = (float *)s;
    int32_t *ph = (int32_t *)((uint8_t *)e + 0x58);
    uint32_t f, g;
    switch (*ph) {
    case 0:
        if (!sub_000833E0(o->anim30))
            break;
        (*ph)++;
    case 1:
        m1_AiSetState1456E0(o, e, 0x38, 0);
        (*ph)++;
        break;
    case 2:
        if (!sub_000833E0(o->anim30))
            break;
        (*ph)++;
    case 3:
        m1_AiSetState1456E0(o, e, 0x39, 0);
        sf[11] = 0.0f;
        sf[10] = 0.0f;
        sf[9] = 0.0f;
        sf[12] = 1.0f;
        sf[4] = 0.0f;
        sf[3] = m1_frameTime42C858 * 0.005f;
        s->f00 &= ~7u;
        (*ph)++;
        break;
    case 4:
        if (!sub_000833E0(o->anim30))
            break;
        (*ph)++;
    case 5:
        if (sub_00156040()) {
            M1_STANDUP2_EXIT(0x18);
            return;
        }
        g = *(uint32_t *)((uint8_t *)e + 0x20);
        if (g & 0x10000) {
            if (g & 1) {
                sub_0015A270(o, 9);
                return;
            }
            M1_STANDUP2_EXIT(2);
            return;
        }
        M1_STANDUP2_EXIT(6);
        return;
    }
    if (*ph <= 2) {
        sf[9] = (1.0f - m1_frameTime42C858 * 0.05f) * sf[9];
        sf[11] = (1.0f - m1_frameTime42C858 * 0.05f) * sf[11];
    }
}

/* 0x15EAB0: recover. When the animation ends leave into 0x18 (stand-up trigger); with flag
   0x10000 into 5 (flag 1) or 2; otherwise into 1 (or 6 one time in 8). */
void m1_AiRecover15EAB0(M1Ob360 *o, M1Ai360 *e) {
    M1St360 *s;
    uint32_t f, g;
    if (!sub_000833E0(o->anim30))
        return;
    if (sub_00156040()) {
        M1_STANDUP2_EXIT(0x18);
        return;
    }
    g = *(uint32_t *)((uint8_t *)e + 0x20);
    if (g & 0x10000) {
        if (g & 1) {
            M1_STANDUP2_EXIT(5);
            return;
        }
        M1_STANDUP2_EXIT(2);
        return;
    }
    if (sub_001C7EE1() & 7) {
        M1_STANDUP2_EXIT(1);
        return;
    }
    M1_STANDUP2_EXIT(6);
}

/* 0x161750: down and getting up. A grabbed enemy only runs the grab update. Phase 0 waits
   for the animation; phase 1 leaves into 0 (dead), 0x18 (stand-up trigger), 5 or 2 (flag
   0x10000, picked by flag 1), else 6 or 1 (picked by flag 1). */
void m1_AiDownGetUp161750(M1Ob360 *o, M1Ai360 *e) {
    M1St360 *s = e->s278;
    M1St360 *s0 = s;
    int32_t *ph = (int32_t *)((uint8_t *)e + 0x58);
    uint32_t f, g;
    if (*(uint8_t *)&s->f40 & 0x20) {
        sub_00185540(o);
        sub_000ED780(o);
        return;
    }
    switch (*ph) {
    case 0:
        if (!sub_000833E0(o->anim30))
            return;
        (*ph)++;
    case 1:
        if (*(uint8_t *)&s0->f40 & 0x10) {
            M1_STANDUP2_EXIT(0);
            return;
        }
        if (sub_00156040()) {
            M1_STANDUP2_EXIT(0x18);
            return;
        }
        g = *(uint32_t *)((uint8_t *)e + 0x20);
        if (g & 0x10000) {
            if (g & 1) {
                M1_STANDUP2_EXIT(5);
                return;
            }
            M1_STANDUP2_EXIT(2);
            return;
        }
        if (g & 1) {
            M1_STANDUP2_EXIT(6);
            return;
        }
        M1_STANDUP2_EXIT(1);
        return;
    }
}

extern uint8_t m1_stats41FEC0[];
int   sub_000CF4F0(void *stats);                             /* current stage/difficulty index */
typedef struct M1Ai360c { uint8_t unk000[0x20]; uint32_t f20; uint8_t unk024[0x270 - 0x24]; float hpMax270; float hp274; } M1Ai360c;

/* 0x15C7A0: recovering on the ground. Until the animation ends the enemy heals 0.05% of its
   maximum per frame (capped at full). Then: 0x18 (stand-up trigger); on stage 8, 0xF at half
   health or less, else 0x11 (coin flip) or state 9/7 by flag 1; flagged enemies react with
   state 9 (0x185420 reports 3) or leave into 0xD with sound 0x10F; otherwise 2 (or 4 one time
   in 8). */
void m1_AiRecoverHeal15C7A0(M1Ob360 *o, M1Ai360 *e) {
    M1Ai360c *h = (M1Ai360c *)e;
    M1St360 *s;
    uint32_t f;
    int d;
    float v;
    if (!sub_000833E0(o->anim30)) {
        v = h->hpMax270 * 0.0005f + h->hp274;
        h->hp274 = v;
        if (v > h->hpMax270)
            h->hp274 = h->hpMax270;
        return;
    }
    d = sub_000CF4F0(m1_stats41FEC0);
    if (sub_00156040()) {
        M1_STANDUP2_EXIT(0x18);
        return;
    }
    if (d == 8) {
        if (0.5f >= h->hp274 / h->hpMax270) {
            M1_STANDUP2_EXIT(0xF);
            return;
        }
        if (sub_001C7EE1() & 1) {
            M1_STANDUP2_EXIT(0x11);
            return;
        }
        if (h->f20 & 1) {
            sub_0015A270(o, 9);
            return;
        }
        sub_0015A270(o, 7);
        return;
    }
    if (h->f20 & 1) {
        if (sub_00185420(o) == 3) {
            sub_0015A270(o, 9);
            return;
        }
        M1_STANDUP2_EXIT_SND(0xD);
        return;
    }
    if (sub_001C7EE1() & 7) {
        M1_STANDUP2_EXIT(2);
        return;
    }
    M1_STANDUP2_EXIT(4);
}

typedef struct M1St360d { uint8_t unk00[0x40]; uint32_t f40; uint32_t hits44; float f48; } M1St360d;

/* 0x161100: down after a combo. Like 0x161750, but on getting up an enemy hit 10+ times (or
   5+ times, one time in 8) arms an angry dash (flag 4, speed 288 or 216) and leaves into
   0x1A. */
void m1_AiComboDown161100(M1Ob360 *o, M1Ai360 *e) {
    M1St360 *s = e->s278;
    M1St360d *c = (M1St360d *)s;
    int32_t *ph = (int32_t *)((uint8_t *)e + 0x58);
    uint32_t f, g;
    float v;
    if (*(uint8_t *)&s->f40 & 0x20) {
        sub_00185540(o);
        sub_000ED780(o);
        return;
    }
    switch (*ph) {
    case 0:
        if (!sub_000833E0(o->anim30))
            return;
        (*ph)++;
    case 1:
        if (c->hits44 >= 10) {
            v = 288.0f;
            goto arm;
        }
        if (c->hits44 >= 5 && !(sub_001C7EE1() & 7)) {
            v = 216.0f;
arm:
            c->f40 |= 4;
            c->f48 = v;
        }
        if (*(uint8_t *)&c->f40 & 0x10) {
            M1_STANDUP2_EXIT(0);
            return;
        }
        if (sub_00156040()) {
            M1_STANDUP2_EXIT(0x18);
            return;
        }
        if (*(uint8_t *)&c->f40 & 4) {
            M1_STANDUP2_EXIT(0x1A);
            return;
        }
        g = *(uint32_t *)((uint8_t *)e + 0x20);
        if (g & 0x10000) {
            if (g & 1) {
                M1_STANDUP2_EXIT(5);
                return;
            }
            M1_STANDUP2_EXIT(2);
            return;
        }
        if (g & 1) {
            M1_STANDUP2_EXIT(6);
            return;
        }
        M1_STANDUP2_EXIT(1);
        return;
    }
}

/* 0x161F40: landing from a throw (phase 0x28) or a slam (phase 0x1E); any other phase hangs.
   Throw: when the animation ends leave into 0x18 (stand-up trigger), 5 or 2 (flag 0x10000,
   picked by flag 1), else 1. Slam: 0x11 when within 30 units, else 0x13 or 0x12 (flag
   0x10000, picked by flag 1), else 6. */
void m1_AiLand161F40(M1Ob360 *o, M1Ai360 *e) {
    M1St360 *s = e->s278;
    M1St360 *s0 = s;
    uint32_t f, g;
    switch (*(int32_t *)((uint8_t *)e + 0x58)) {
    default:
        for (;;);
    case 0x28:
        if (!sub_000833E0(o->anim30))
            return;
        if (sub_00156040()) {
            M1_STANDUP2_EXIT(0x18);
            return;
        }
        g = *(uint32_t *)((uint8_t *)e + 0x20);
        if (g & 0x10000) {
            if (g & 1) {
                M1_STANDUP2_EXIT(5);
                return;
            }
            M1_STANDUP2_EXIT(2);
            return;
        }
        M1_STANDUP2_EXIT(1);
        return;
    case 0x1E:
        if (!sub_000833E0(o->anim30))
            return;
        if (30.0f >= *(float *)((uint8_t *)s0 + 0x54)) {
            M1_STANDUP2_EXIT(0x11);
            return;
        }
        g = *(uint32_t *)((uint8_t *)e + 0x20);
        if (g & 0x10000) {
            if (g & 1) {
                M1_STANDUP2_EXIT(0x13);
                return;
            }
            M1_STANDUP2_EXIT(0x12);
            return;
        }
        M1_STANDUP2_EXIT(6);
        return;
    }
}

float sub_001B2730(const void *a, const void *b);            /* distance */


/* 0x162740: launched upward. A grabbed enemy only runs the grab update. Phases: wait, switch
   the flight animation (0x34 -> 0x35, 0x37 -> 0x38, else hang) and mark airborne; wait for a
   ground contact (clears body flag 0x10); wait, switch the landing animation (0x35 -> 0x36,
   0x38 -> 0x39) and zero the speeds; wait, then leave into 0 (dead), 0x18 (stand-up
   trigger), state 9 or 2 (flag 0x10000, picked by flag 1), else 6. In the first four
   phases the side speeds bleed off and gravity (147) pulls the body down. */
void m1_AiLaunched162740(M1Ob360 *o, M1Ai360 *e) {
    M1St360 *s = e->s278;
    M1St360 *s0 = s;
    float *sf = (float *)s;
    int32_t *ph = (int32_t *)((uint8_t *)e + 0x58);
    int32_t an;
    uint32_t f, g;
    float fr;
    if (*(uint8_t *)&s->f40 & 0x20) {
        sub_00185540(o);
        sub_000ED780(o);
        return;
    }
    switch (*ph) {
    case 0:
        if (!sub_000833E0(o->anim30))
            break;
        (*ph)++;
    case 1:
        an = *(int32_t *)((uint8_t *)e + 0x64);
        if (an == 0x34)
            m1_AiSetState1456E0(o, e, 0x35, 0);
        else if (an == 0x37)
            m1_AiSetState1456E0(o, e, 0x38, 0);
        else
            for (;;);
        s->f00 |= 8;
        (*ph)++;
        break;
    case 2:
        if (*((uint8_t *)o + 0x128) & 0x18) {
            o->f10 &= ~0x10u;
            (*ph)++;
        }
        break;
    case 3:
        if (!sub_000833E0(o->anim30))
            break;
        (*ph)++;
    case 4:
        an = *(int32_t *)((uint8_t *)e + 0x64);
        if (an == 0x35)
            m1_AiSetState1456E0(o, e, 0x36, 0);
        else if (an == 0x38)
            m1_AiSetState1456E0(o, e, 0x39, 0);
        else
            for (;;);
        sf[11] = 0.0f;
        sf[10] = 0.0f;
        sf[9] = 0.0f;
        sf[12] = 1.0f;
        sf[4] = 0.0f;
        sf[3] = m1_frameTime42C858 * 0.005f;
        s->f00 &= ~7u;
        (*ph)++;
        break;
    case 5:
        if (!sub_000833E0(o->anim30))
            break;
        (*ph)++;
    case 6:
        if (*(uint8_t *)&s0->f40 & 0x10) {
            M1_STANDUP2_EXIT(0);
            return;
        }
        if (sub_00156040()) {
            M1_STANDUP2_EXIT(0x18);
            return;
        }
        g = *(uint32_t *)((uint8_t *)e + 0x20);
        if (g & 0x10000) {
            if (g & 1) {
                sub_0015A270(o, 9);
                return;
            }
            M1_STANDUP2_EXIT(2);
            return;
        }
        M1_STANDUP2_EXIT(6);
        return;
    }
    if (*ph <= 3) {
        sf[9] = (1.0f - m1_frameTime42C858 * 0.05f) * sf[9];
        sf[11] = (1.0f - m1_frameTime42C858 * 0.05f) * sf[11];
        fr = m1_frameRate42C85C;
        sf[10] = fr * fr * 147.0f + sf[10];
    }
}

/* 0x162C90: knocked back. A grabbed enemy only runs the grab update. Phases (each waiting
   step falls straight into the next): wait, switch the flight animation (0x34 -> 0x35,
   0x37 -> 0x38, else hang); wait, switch the landing animation (0x35 -> 0x36, 0x38 -> 0x39)
   and zero the speeds; wait, then leave into 0 (dead), 0x18 (stand-up trigger), 0x1A
   (angry, flag 0x20000), state 9 or 2 (flag 0x10000, picked by flag 1), else 6. During the
   first three phases the side speeds bleed off by 5% per frame unit. */
void m1_AiKnockBack162C90(M1Ob360 *o, M1Ai360 *e) {
    M1St360 *s = e->s278;
    M1St360 *s0 = s;
    float *sf = (float *)s;
    int32_t *ph = (int32_t *)((uint8_t *)e + 0x58);
    int32_t an;
    uint32_t f, g;
    if (*(uint8_t *)&s->f40 & 0x20) {
        sub_00185540(o);
        sub_000ED780(o);
        return;
    }
    switch (*ph) {
    case 0:
        if (!sub_000833E0(o->anim30))
            break;
        (*ph)++;
    case 1:
        an = *(int32_t *)((uint8_t *)e + 0x64);
        if (an == 0x34)
            m1_AiSetState1456E0(o, e, 0x35, 0);
        else if (an == 0x37)
            m1_AiSetState1456E0(o, e, 0x38, 0);
        else
            for (;;);
        (*ph)++;
    case 2:
        if (!sub_000833E0(o->anim30))
            break;
        (*ph)++;
    case 3:
        an = *(int32_t *)((uint8_t *)e + 0x64);
        if (an == 0x35)
            m1_AiSetState1456E0(o, e, 0x36, 0);
        else if (an == 0x38)
            m1_AiSetState1456E0(o, e, 0x39, 0);
        else
            for (;;);
        sf[11] = 0.0f;
        sf[10] = 0.0f;
        sf[9] = 0.0f;
        sf[12] = 1.0f;
        sf[4] = 0.0f;
        sf[3] = m1_frameTime42C858 * 0.005f;
        s->f00 &= ~7u;
        (*ph)++;
        break;
    case 4:
        if (!sub_000833E0(o->anim30))
            break;
        (*ph)++;
    case 5:
        if (*(uint8_t *)&s0->f40 & 0x10) {
            M1_STANDUP2_EXIT(0);
            return;
        }
        if (sub_00156040()) {
            M1_STANDUP2_EXIT(0x18);
            return;
        }
        g = *(uint32_t *)((uint8_t *)e + 0x20);
        if (g & 0x10000) {
            if (s0->f40 & 0x20000) {
                *(float *)((uint8_t *)s0 + 0x48) = 0.0f;
                M1_STANDUP2_EXIT(0x1A);
                return;
            }
            if (g & 1) {
                sub_0015A270(o, 9);
                return;
            }
            M1_STANDUP2_EXIT(2);
            return;
        }
        M1_STANDUP2_EXIT(6);
        return;
    }
    if (*ph <= 2) {
        sf[9] = (1.0f - m1_frameTime42C858 * 0.05f) * sf[9];
        sf[11] = (1.0f - m1_frameTime42C858 * 0.05f) * sf[11];
    }
}

int   sub_00145940(void *o, float x, float z, float lo, float hi);


typedef struct M1Spin360b { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Spin360b;
extern float m1_gF3F7504;
void  sub_00113480(void *e, int k);
void  sub_00147710(void *e, int k, float a, float b, float c, int d);   /* regargs: e=ECX k=EAX */
M1Spin360b *m1_Quest113400(void *e, int k);

/* 0x160650: counter attack. Phase 0 waits for the animation and goes to phase 10; phase 1
   resets the state; phase 2 goes to phase 10 while 0x185420 reports under 3. Phase 10 sets
   the counter state (0x22), zeroes the speeds and sets two spin channels; phase 11 lands
   (within 14 units sets flag 1) and moves to phase 20 when the animation ends; phase 20
   sets state 5; phase 21 waits for the animation (notifying 0x113190 near the landing
   spot), then leaves into 0x18 (stand-up trigger), 0x22 with sound 0x10F (target is a
   type-0xD body with flag 1), else 5 or 2 (flag 1). */
void m1_AiCounter160650(M1Ob360 *o, M1Ai360 *e) {
    M1St360 *s = e->s278;
    float *sf = (float *)s;
    int32_t *ph = (int32_t *)((uint8_t *)e + 0x58);
    M1Spin360b *p;
    uint8_t *t;
    uint32_t f;
    switch (*ph) {
    case 0:
        if (sub_000833E0(o->anim30))
            *ph = 10;
        return;
    case 1:
        m1_AiSetState1456E0(o, e, 0, 0);
        (*ph)++;
        return;
    case 2:
        if (sub_00185420(o) < 3)
            *ph = 10;
        return;
    case 10:
        m1_AiSetState1456E0(o, e, 0x22, 0);
        sf[3] = m1_frameTime42C858 * 0.005f;
        sf[11] = 0.0f;
        sf[10] = 0.0f;
        sf[9] = 0.0f;
        sf[12] = 1.0f;
        sf[4] = 0.0f;
        sub_00147710(e, 1, 0.08726647f, -0.08726647f, m1_frameTime42C858 * 0.15707964f, 0);
        p = m1_Quest113400(e, 5);
        p->f10 = 9.0f;
        p->f14 = 1.0f;
        p->f18 = 0.0f;
        p->f1C = 0.0f;
        (*ph)++;
        return;
    case 11:
        if (sub_00145780(o, 14.0f))
            sub_00113480(e, 1);
        if (sub_000833E0(o->anim30)) {
            m1_gF3F7504 = 3.0f;
            *ph = 20;
        }
        return;
    case 20:
        m1_AiSetState1456E0(o, e, 5, 0);
        (*ph)++;
        return;
    case 21:
        if (sub_00145780(o, 14.0f))
            sub_00113190(o, e, 1);
        if (!sub_000833E0(o->anim30))
            return;
        if (sub_00156040()) {
            M1_STANDUP2_EXIT(0x18);
            return;
        }
        t = *(uint8_t **)((uint8_t *)e + 0x104);
        if (*(int32_t *)((uint8_t *)e + 0xF8) == 1 && (t[0xC] & 1) && *(int32_t *)(t + 4) == 0xD) {
            M1_STANDUP2_EXIT_SND(0x22);
            return;
        }
        if (*((uint8_t *)e + 0x20) & 1) {
            M1_STANDUP2_EXIT(5);
            return;
        }
        M1_STANDUP2_EXIT(2);
        return;
    }
}

extern uint8_t *g_playerObj;
void  sub_000F5D40(void *dst, const void *src);              /* copy vec3 */
void  sub_001AD9F0(float *d, const float *a, const float *b); /* d = a - b */
void  sub_001AD7E0(float *d, const float *a);                /* normalise */
void  sub_001ADBA0(void *d, const float *a, float k);        /* d = a * k */
void  sub_001ADAF0(float *d, const float *a, const float *b); /* d = a + b */
void  sub_001ADA60(void *m, void *up, void *fwd);            /* rebuild basis */
void  sub_001459D0(void *o, float x, float z, float turn);

