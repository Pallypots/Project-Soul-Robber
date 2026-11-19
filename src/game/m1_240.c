/* Area m1, file 240: effect helpers (register inputs per docs/verification.md). Names inferred. */
#include <stdint.h>

typedef struct M1Sc240 { uint8_t unk00[0x60]; uint8_t pos60[0xD0]; int32_t res130; } M1Sc240;
typedef struct M1G240 { uint8_t unk00[0x8C]; M1Sc240 *sc8C; uint8_t unk90[0xA4]; int32_t snd134; } M1G240;
typedef struct M1R240 { void *o0; } M1R240;
M1G240 *sub_00100110(void);
int32_t sub_000F60C0(void *o, int32_t z, float *out);
void sub_00048250(int32_t h);
void *sub_00035DD0(void *o, int32_t res, int32_t a, int32_t b);
void sub_00033880(void *h, float *out);
void sub_00034E00(void *h, const void *pos, float *v, const float *col);
void m1_GreenFx18F8D0(void *o);   /* regargs: o=EAX */
void sub_000ED780(void *o);
void sub_000F8270(M1G240 *g);
int32_t aab_Effect494D0(int32_t snd, void *pos, int32_t z);

/* 0x0018F950: burst r's object: stop the scene sound, spawn the green burst at its anchor, run 0x18F8D0, destroy it
   and play sound 0x14C; returns 1, or 0 with no object / anchor (regargs: r=EDI; calls 0x18F8D0 with o=EAX). */
int m1_Burst18F950(M1R240 *r)
{
    float col[4];
    float at[4];
    float a[8];
    float b[8];
    M1G240 *g = sub_00100110();
    void *h;
    if (!r)
        return 0;
    if (sub_000F60C0(r->o0, 0, at) == -1)
        return 0;
    col[0] = 0.0f;
    col[1] = 1.0f;
    col[2] = 0.0f;
    col[3] = 1.0f;
    if (g->snd134 != -1) {
        sub_00048250(g->snd134);
        g->snd134 = -1;
    }
    h = sub_00035DD0(r->o0, g->sc8C->res130, 0, 3);
    sub_00033880(h, a);
    sub_00034E00(h, at, b, col);
    m1_GreenFx18F8D0(r->o0);
    sub_000ED780(r->o0);
    sub_000F8270(g);
    aab_Effect494D0(0x14C, g->sc8C->pos60, 1);
    return 1;
}

struct M1Mgr240;
typedef struct M1Nd240 { uint8_t unk00[0x8C]; int32_t kind8C; uint32_t flags90; uint8_t unk94[0x1C]; uint32_t idxB0;
    struct M1Mgr240 *ownerB4; int32_t lB8, lBC, lC0, lC4, lC8, lCC; float sD0; int32_t lD4, lD8, lDC, lE0, lE4;
    float sE8; uint8_t vEC[0x10]; uint8_t vFC[0x10]; uint8_t v10C[0x10]; int32_t l11C; uint8_t v120[0x10]; } M1Nd240;
typedef struct M1Mgr240 { uint8_t unk00[0xB0]; uint32_t nB0; M1Nd240 *nodesB4; } M1Mgr240;
extern float m1_vec367E28[], m1_vec367E38[], m1_vec40F1A0[], m1_vec367E48[];
void sub_001B25B0(M1Nd240 *n);
void sub_001B2020(M1Mgr240 *m, M1Nd240 *n);
void sub_000F5D40(void *dst, const void *src);

/* 0x001AEA00: initialise n nodes (0x130 bytes each, kind 8, flags 0x140, index, owner m, zeroed state, default
   vectors) in nodes[] and link them to m. */
void m1_NodesInit1AEA00(M1Nd240 *nodes, M1Mgr240 *m, uint32_t n)
{
    uint32_t i;
    m->nodesB4 = nodes;
    m->nB0 = n;
    i = 0;
    if (n > *(volatile uint32_t *)&i) do {
        M1Nd240 *e = &nodes[i];
        e->kind8C = 8;
        sub_001B25B0(e);
        e->flags90 |= 0x140;
        e->idxB0 = i;
        e->lB8 = 0;
        e->lBC = 0;
        e->lC0 = 0;
        e->lC4 = 0;
        e->lC8 = 0;
        e->lCC = 0;
        e->sD0 = 0.0f;
        e->lD4 = 0;
        e->lD8 = 0;
        e->lDC = 0;
        e->lE0 = 0;
        e->lE4 = 0;
        e->sE8 = 0.0f;
        e->ownerB4 = m;
        sub_000F5D40(e->v10C, m1_vec367E28);
        sub_000F5D40(e->vEC, m1_vec367E38);
        sub_000F5D40(e->vFC, m1_vec40F1A0);
        sub_000F5D40(e->v120, m1_vec367E48);
        e->l11C = 0;
        sub_001B2020(m, e);
    } while (++i < n);
}

#include <intrin.h>
typedef struct M1Str240 { uint8_t unk00[4]; union { char buf[16]; char *ptr; } bx; uint32_t size14; uint32_t res18; } M1Str240;
void sub_001C885F(void *p);   /* operator delete */

/* 0x001A3860: string _Tidy(built, newsize): if a heap buffer is in use, move the first newsize characters back into
   the small buffer and free it; then capacity 15, size newsize, terminate (thiscall s=ECX). */
void __fastcall m1_StrTidy1A3860(M1Str240 *s, int unusedEdx, char built, uint32_t n)
{
    uint32_t z = 0;
    if (built && s->res18 >= 16) {
        char *p = s->bx.ptr;
        if (n > *(volatile uint32_t *)&z) {
            __movsd((unsigned long *)s->bx.buf, (const unsigned long *)p, n >> 2);
            __movsb((unsigned char *)s->bx.buf + (n - (n & 3)), (const unsigned char *)p + (n - (n & 3)), n & 3);
        }
        sub_001C885F(p);
    }
    s->size14 = n;
    s->res18 = 15;
    s->bx.buf[n] = 0;
}

typedef struct M1Fd240 { uint32_t flags0; int32_t n4, n8; int32_t st0C; float t10; uint8_t b14; uint8_t unk15[0xF];
    float k24; uint8_t unk28[0xC]; float s34; uint8_t unk38[0x70]; uint8_t chA8[0x10]; } M1Fd240;
extern int32_t r2c_fadeD3F4B1C;
extern uint8_t m1_ch3F4BD8[], m1_ch3F4C74[];
void a60_StepByFrame(float *t, int32_t z);
void sub_000150B0(void *ch, int32_t k);
void sub_000150E0(void *ch, int32_t k);

/* 0x000E8D90: two-step 20-unit fade: step 0 resets the channel (and, in fade modes 3-4, channels 9/10), step 1 counts
   t10 down, sets the 0-255 level and the scale, and clears everything when it runs out (regargs: e=ESI). */
void m1_Fade0E8D90(M1Fd240 *e)
{
    volatile int k;
    switch (e->st0C) {
    case 0:
        sub_000150E0(e->chA8, 0);
        k = r2c_fadeD3F4B1C;
        if ((uint32_t)k >= 3 && (uint32_t)k <= 4) {
            sub_000150B0(m1_ch3F4BD8, 9);
            sub_000150B0(m1_ch3F4C74, 10);
            sub_000150E0(m1_ch3F4BD8, 0);
            sub_000150E0(m1_ch3F4C74, 0);
        }
        e->t10 = 20.0f;
        e->st0C++;
        return;
    case 1:
        a60_StepByFrame(&e->t10, 0);
        e->b14 = (uint8_t)(int)(__int64)(e->t10 * 0.05f * 128.0f);
        e->s34 = ((20.0f - e->t10) * 0.05f + 1.0f) * e->k24;
        if (e->t10 <= 0.0f) {
            e->b14 = 0;
            e->n4 = 0;
            e->n8 = 0;
            e->st0C = 0;
            e->s34 = 1.0f;
            e->flags0 &= ~1u;
        }
        return;
    }
}
