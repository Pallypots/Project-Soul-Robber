/* Area m1, file 223: actor resets and an entity scan. Register inputs follow docs/verification.md. Names inferred. */
#include <stdint.h>

typedef struct M1Nd223 { uint8_t unk00[0xC]; uint32_t flagsC; } M1Nd223;
typedef struct M1Mot223 { int32_t a0; float f4, f8, fC; int32_t a10; float f14, f18, f1C, f20, f24, f28, f2C, f30;
                          uint8_t unk34[0xE8 - 0x34]; M1Nd223 *ndE8; } M1Mot223;
void sub_0001EB80(M1Nd223 *n);

/* 0x000C7340: detach the motion block's node and reset it (regargs: m=ESI). */
void m1_MotReset0C7340(M1Mot223 *m)
{
    m->ndE8->flagsC &= ~1u;
    sub_0001EB80(m->ndE8);
    m->a0 = 0;
    m->f4 = 0.0f; m->f8 = 1.0f; m->fC = 0.0f;
    m->a10 = 0;
    m->f1C = 0.0f; m->f18 = 0.0f; m->f14 = 0.0f;
    m->f2C = 0.0f; m->f28 = 0.0f; m->f24 = 0.0f;
    m->f30 = 1.0f; m->f20 = 1.0f;
    m->ndE8 = 0;
}

typedef struct M1Act223 { uint8_t unk00[0xE8]; float fE8; uint32_t flagsEC; float fF0; uint8_t unkF4[0x12C - 0xF4];
                          volatile int32_t anim12C; uint8_t unk130[0x188 - 0x130]; int32_t f188; uint8_t unk18C[0xD8C - 0x18C];
                          int32_t modeD8C; } M1Act223;
void sub_000D0560(M1Act223 *a, int anim, int c);

/* 0x000C1A90: flag the actor (+0xEC |= 0x40), reset its blend, and start anim 0x317 in mode 3 or 0x310 otherwise (regargs: a=EAX). */
void m1_ActStart0C1A90(M1Act223 *a)
{
    a->flagsEC |= 0x40;
    a->fF0 = 1.0f;
    a->f188 = 1;
    a->fE8 = 0.0f;
    if (a->modeD8C == 3) {
        a->anim12C = 0x317;
        sub_000D0560(a, a->anim12C, 3);
    } else {
        a->anim12C = 0x310;
        sub_000D0560(a, a->anim12C, 3);
    }
}

typedef struct M1Ent223 { uint32_t flags0; int32_t kind4; uint8_t unk08[0x12C - 8]; void *tgt12C[8]; uint8_t unk14C[0x260 - 0x14C]; } M1Ent223;
extern M1Ent223 m1_ents4242C0[32];
extern void *g_playerObj;

/* 0x000A47A0: over every live entity, for each of its 8 target slots holding the player, pick a code by entity kind
   (0x1B-0x1C -> 6, 0x2C-0x2F and 0x62-0x69 -> 15, 0x38 -> 1); the last match wins, -1 when none. */
int m1_PlayerTargetCode0A47A0(void)
{
    void *pl = g_playerObj;
    int r = -1;
    int i;
    for (i = 0; i < 32; i++) {
        M1Ent223 *e = &m1_ents4242C0[i];
        void **s; int n;
        if (!(e->flags0 & 1)) continue;
        s = e->tgt12C;
        for (n = 8; n != 0; n--, s++) {
            if (!*s || *s != pl) continue;
            switch (e->kind4) {
            case 0x1B: case 0x1C: r = 6; break;
            case 0x2C: case 0x2D: case 0x2E: case 0x2F:
            case 0x62: case 0x63: case 0x64: case 0x65: case 0x66: case 0x67: case 0x68: case 0x69: r = 15; break;
            case 0x38: r = 1; break;
            }
        }
    }
    return r;
}
