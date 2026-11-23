/* Area m1, file 362: register-argument revisits (written with normal parameters). Names inferred. */
#include <stdint.h>
#include "m1_enemy.h"

/* 0x186470 takes the body in ebx and the AI in edi plus one stack argument; written here as ordinary parameters. */
void sub_00186470(M1Actor *o, M1EnemyAi *e, int variant);

/* 0x188360: enter the get-up state, variant 2 when the AI's reaction bit is set, else variant 1. */
void m1_AiGetUpPick188360(M1Actor *o, M1EnemyAi *e) {
    if (e->aiFlags & 1) { int volatile v1 = 2; sub_00186470(o, e, v1); return; }
    { int volatile v2 = 1; sub_00186470(o, e, v2); }
}

#include "m1_fx.h"
/* 0x170400, 0x16FF30 and 0x1700C0 take the body in eax; 0x170570 takes a mode in eax and the body in ecx. Written as ordinary parameters. */
void sub_00170400(M1Actor *o);
void sub_0016FF30(M1Actor *o);
void m1_BoneStep1700C0(M1Actor *o);
void sub_00170570(int mode, M1Actor *o, M1PropCtl *c);
void aab_Attach36750(void *o, int k);
void sub_000ED780(void *o);

/* Twin prop sequences: show the prop, then play its open animation (mode 0 or 1), then wait for it to finish and remove it. */
#define M1_PROPSEQ362(name, mode) \
void name(M1Actor *o, M1PropCtl *c) { \
    switch (c->phase) { \
    case 0: \
        sub_00170400(o); \
        o->bodyFlags |= 0xD; \
        c->phase++; \
        return; \
    case 1: \
        sub_0016FF30(o); \
        aab_Attach36750(o, c->variant == 1 ? 2 : 0); \
        sub_00170570((mode), o, c); \
        c->phase++; \
        return; \
    case 2: \
        m1_BoneStep1700C0(o); \
        if (c->timer > 1.0f) sub_000ED780(o); \
        return; \
    } \
}

/* 0x1707F0: prop sequence, mode 0. */
M1_PROPSEQ362(m1_PropSeqA1707F0, 0)
/* 0x170880: prop sequence, mode 1. */
M1_PROPSEQ362(m1_PropSeqB170880, 1)
