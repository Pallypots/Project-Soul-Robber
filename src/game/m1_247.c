/* Area m1, file 247: actor state helpers (register-argument callers per docs/verification.md). Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1N247 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; float v20[4]; } M1N247;
typedef struct M1O247 { uint8_t unk00[0x20]; M1N247 *n20; uint8_t unk24[0xC]; void *mdl30; uint8_t unk34[0x2C];
    uint8_t pos60[0x10]; } M1O247;
typedef struct M1E247 { uint8_t unk00[0x1D8]; float t1D8; } M1E247;
typedef struct M1S247 { uint8_t unk00[0x20]; uint8_t flags20; uint8_t unk21[0x37]; int32_t st58; uint8_t unk5C[0x21C];
    M1E247 *ext278; } M1S247;
extern float a50_frameUnits, a50_frameSeconds;
extern M1O247 *g_playerObj;
int32_t sub_000833E0(void *m);
int32_t b4c_Enter1456E0(M1O247 *o, M1S247 *s, int32_t a, int32_t b);
void aab_Vec1AD9F0(float *out, const void *a, const void *b);
void sub_001AD7E0(float *out, const float *in);
void sub_001ADBA0(float *out, const float *in, float k);
void sub_001ADA60(M1N247 *n, const float *a, const float *b);
int  r2_PlayerOutOfReach(M1S247 *obj, M1O247 *self);   /* regargs: obj=EAX self=ESI */
void sub_0011F2B0(M1O247 *obj, int k, M1S247 *a);       /* regargs: obj=EDI k=EBX */

/* 0x0012A250: count the +0x1D8 timer down; step 0 on clip end -> state 1 if the timer is out, else advance; step 1
   enters 0x41 (flag 1, skipping a step) or 0x37 and turns the node to face away from the player; step 2 enters 0x38 on
   clip end; step 3 when the timer runs out -> 0x11 (out of reach) or 0x28 (calls 0x120820 with obj=EAX self=ESI,
   0x11F2B0 with obj=EDI k=EBX). */
void m1_Turn12A250(M1O247 *o, M1S247 *s)
{
    M1E247 *e = s->ext278;
    M1N247 *n;
    float v[4];
    e->t1D8 -= a50_frameSeconds;
    switch (s->st58) {
    case 0:
        if (!sub_000833E0(o->mdl30))
            return;
        if (e->t1D8 <= 0.0f) {
            sub_0011F2B0(o, 1, s);
            return;
        }
        s->st58++;
        return;
    case 1:
        if (s->flags20 & 1) {
            b4c_Enter1456E0(o, s, 0x41, 0);
            s->st58 += 2;
        } else {
            b4c_Enter1456E0(o, s, 0x37, 0);
            s->st58++;
        }
        aab_Vec1AD9F0(v, o->pos60, g_playerObj->pos60);
        v[1] = 0.0f;
        sub_001AD7E0(v, v);
        sub_001ADBA0(o->n20->v20, v, -1.0f);
        o->n20->f1C = 0.0f;
        o->n20->f18 = 0.0f;
        o->n20->f10 = 0.0f;
        o->n20->f14 = 1.0f;
        n = o->n20;
        sub_001ADA60(n, &n->f10, n->v20);
        return;
    case 2:
        if (sub_000833E0(o->mdl30)) {
            b4c_Enter1456E0(o, s, 0x38, 0);
            s->st58++;
        }
    case 3:
        if (e->t1D8 <= 0.0f) {
            int k = 0x11;
            if (!r2_PlayerOutOfReach(s, o))
                k = 0x28;
            sub_0011F2B0(o, k, s);
        }
        return;
    }
}

typedef struct M1PE247 { uint8_t unk00[4]; uint32_t flags4; uint8_t unk08[0x428]; uint32_t f430; uint8_t unk434[0xBC];
    uint32_t f4F0; uint8_t unk4F4[0xBC]; uint32_t f5B0; uint8_t unk5B4[0xBC]; uint32_t f670; } M1PE247;
typedef struct M1PS247 { uint8_t unk00[0x4C]; uint32_t flags4C; uint8_t unk50[8]; int32_t st58; uint8_t unk5C[0x18];
    float t74; uint8_t unk78[0x200]; M1PE247 *ext278; } M1PS247;
typedef struct M1PO247 { uint8_t unk00[0x20]; uint8_t *n20; uint8_t unk24[0x3C]; float x60, y64, z68; uint8_t unk6C[0x34];
    float dA0, dA4, dA8; } M1PO247;
void sub_00113A40(M1PO247 *o, M1PS247 *s);
void sub_00113AA0(M1PO247 *o, M1PS247 *s);
float sub_00145B60(void *m);
void sub_000C7540p(M1PO247 *o, float a, float b, const float *pos, const float *rot);   /* 0xC7540 */
void sub_000ED780p(M1PO247 *o);                                                       /* 0xED780 */
int  r2_PlayerOutOfReachP(M1PS247 *obj, M1PO247 *self);   /* 0x120820 regargs: obj=EAX self=ESI */
void sub_0011F2B0p(M1PO247 *obj, int k, M1PS247 *a);        /* 0x11F2B0 regargs: obj=EDI k=EBX */
void sub_0011F2B0q(M1PO247 *obj, int k, M1PS247 *a);        /* same function (alias stops cl merging calls) */

/* 0x00129BD0: step 0 starts the hover (0x113A40); step 1 draws it 10 units above o facing the node and advances when t74
   runs out (0x11 when out of reach); step 2 lands (0x113AA0, flag 0x200, clears flag 0x4000000 and the four limb
   flags 4) then 0x11 or 0x10; step 10 destroys on flag 0x400 (calls 0x120820 with obj=EAX self=ESI, 0x11F2B0 with
   obj=EDI k=EBX). */
void m1_Hover129BD0(M1PO247 *o, M1PS247 *s)
{
    M1PE247 *e = s->ext278;
    float pos[4], rot[4];
    switch (s->st58) {
    case 0:
        sub_00113A40(o, s);
        s->st58++;
    case 1:
        pos[0] = o->dA0 + o->x60;
        pos[2] = o->dA8 + o->z68;
        pos[1] = o->y64 + 10.0f;
        pos[3] = 1.0f;
        rot[0] = 0.0f;
        rot[1] = 0.0f;
        rot[2] = 0.0f;
        rot[3] = 1.0f;
        rot[1] = sub_00145B60(o->n20 + 0x20);
        sub_000C7540p(o, 1.0f, 1.0f, pos, rot);
        if (s->t74 <= 0.0f) {
            s->st58++;
            return;
        }
        if (r2_PlayerOutOfReachP(s, o))
            sub_0011F2B0q(o, 0x11, s);
        return;
    case 2:
        sub_00113AA0(o, s);
        s->flags4C |= 0x200;
        e->flags4 &= ~0x4000000u;
        e->f430 &= ~4u;
        e->f5B0 &= ~4u;
        e->f4F0 &= ~4u;
        e->f670 &= ~4u;
        if (r2_PlayerOutOfReachP(s, o)) {
            sub_0011F2B0p(o, 0x11, s);
            return;
        }
        sub_0011F2B0p(o, 0x10, s);
        return;
    case 10:
        if (e->flags4 & 0x400)
            sub_000ED780p(o);
        return;
    }
}


extern int32_t r4e_g404320, r4e_g404324, r4e_g404328, r4e_g40432C, r4e_g404330;
extern int32_t m1_mvOn404334, m1_mvSteps404338, m1_mvT40433C, m1_mvT404340, m1_mvT404344, m1_mvT404348, m1_mvT40434C;
extern int32_t a1a_g403960;
void sub_001A7F90(int32_t h);
void r4b_MovieSetVolume(int32_t v);

/* 0x001A0200: while a movie fade is active, move the volume and four other levels 1/steps of the way toward their
   targets each tick; on the last step snap to the targets, stop the fade and call 0x1A7F90; then apply the volume. */
void m1_MovieFade1A0200(void)
{
    int n;
    if (m1_mvOn404334 <= 0)
        return;
    n = m1_mvSteps404338;
    if (n > 0) {
        r4e_g404330 -= (r4e_g404330 - m1_mvT40433C) / n;
        r4e_g404320 -= (r4e_g404320 - m1_mvT404340) / n;
        r4e_g404324 -= (r4e_g404324 - m1_mvT404344) / n;
        r4e_g404328 -= (r4e_g404328 - m1_mvT404348) / n;
        r4e_g40432C -= (r4e_g40432C - m1_mvT40434C) / n;
    } else {
        m1_mvSteps404338 = 0;
        m1_mvOn404334 = 0;
        r4e_g404324 = m1_mvT404344;
        r4e_g404330 = m1_mvT40433C;
        r4e_g404320 = m1_mvT404340;
        r4e_g404328 = m1_mvT404348;
        r4e_g40432C = m1_mvT40434C;
        sub_001A7F90(a1a_g403960);
    }
    r4b_MovieSetVolume(*(volatile int32_t *)&r4e_g404330);
    m1_mvSteps404338--;
}

typedef struct M1FxS247 { void *o0; int32_t n4; uint8_t unk08[8]; int16_t w10; uint8_t unk12[0x32]; } M1FxS247;
typedef struct M1FxO247 { uint8_t unk00[0xC]; uint32_t flagsC, flags10; uint8_t unk14[0xDC]; int32_t nF0, nF4;
    uint8_t unkF8[0x24]; int32_t n11C, n120, n124; } M1FxO247;
typedef struct M1FxA247 { uint8_t unk00[0x28]; float f28; uint8_t unk2C[0x48]; M1FxS247 *slot74; void *cb78, *cb7C; uint8_t unk80[4];
    void *p84, *p88; } M1FxA247;
extern M1FxS247 *a19_g401828;
extern uint8_t m1_fxT27B248[], m1_fxT27B25C[], m1_fxT27B26C[], m1_fxT27B27C[];
extern uint8_t r4c_g32C870[], r4c_g32C874[];
void r4c_FxJReset(M1FxS247 *s);   /* regargs: s=EDI */
void sub_000F5D60(M1FxO247 *o, float a, int32_t b, int32_t c, const void *t);
void sub_000F5DD0(M1FxO247 *o, float a, float b, const void *t);
void r2d_MoverSet(M1FxO247 *o, float a, const void *t1, const void *t2);
void r4c_DynStop(void);
void r4h_FxPopDrop(void);
void sub_00189DA0(M1FxO247 *o, M1FxA247 *a, int32_t st);

/* 0x00198210: attach a pooled effect slot (first free of 6, 0x44 bytes) of the given kind to o and set up its movers
   and handlers; returns 1, or 0 when the pool is full (calls 0x1976B0 with s=EDI). */
int m1_FxAttach198210(M1FxO247 *o, M1FxA247 *a, int16_t kind)
{
    M1FxS247 *p = a19_g401828;
    M1FxS247 *s;
    int i;
    for (i = 0; i < 6; i++, p++)
        if (!p->o0)
            break;
    if (i >= 6)
        return 0;
    s = &a19_g401828[i];
    if (*(volatile int *)&i >= 6)
        return 0;
    s->n4 = i + 4;
    s->o0 = o;
    s->w10 = kind;
    a->slot74 = s;
    o->flagsC = (o->flagsC & ~0x60u) | 1;
    r4c_FxJReset(s);
    o->n124 = 1;
    sub_000F5D60(o, 1.0f, 0, 0, m1_fxT27B248);
    sub_000F5DD0(o, 1.0f, 5.5f, m1_fxT27B25C);
    o->nF0 = 2;
    o->nF4 = 2;
    r2d_MoverSet(o, 1.0f, m1_fxT27B26C, m1_fxT27B27C);
    o->n11C = 1;
    o->n120 = 2;
    a->f28 = 0.0f;
    o->flags10 |= 0x445;
    a->p84 = r4c_g32C870;
    a->p88 = r4c_g32C874;
    a->cb78 = (void *)r4c_DynStop;
    a->cb7C = (void *)r4h_FxPopDrop;
    sub_00189DA0(o, a, 0);
    return 1;
}

typedef struct M1OrbS247 { void *o0; uint8_t unk04[4]; int32_t n8; uint8_t unk0C[0x10]; } M1OrbS247;
typedef struct M1OrbO247 { uint8_t unk00[0xC]; uint32_t flagsC, flags10; uint8_t unk14[0x5C]; float v70[3], w7C;
    uint8_t unk80[0x24]; float fA4; uint8_t unkA8[8]; float fB0, fB4; uint8_t unkB8[0x18]; int32_t nD0; uint8_t unkD4[0x14];
    float fE8; int32_t nEC; uint8_t unkF0[0x34]; int32_t n124; } M1OrbO247;
typedef struct M1OrbA247 { uint8_t unk00[0x24]; int32_t n24; uint8_t unk28[0x4C]; M1OrbS247 *slot74; void *cb78, *cb7C,
    *cb80, *p84, *p88; } M1OrbA247;
extern M1OrbS247 r4c_recs401838[8];
extern uint8_t m1_orbT32C878[], m1_orbT32C8A0[];
extern float m1_orbF32C8C8, m1_orbF32C8D0, m1_orbF32C8D4, m1_orbF32C8D8;
void m1_orbStepA198460(void);
void r4h_FxOrbitStepB(void);
void m1_orbStepC198780(void);
int32_t sub_0001BC40(M1OrbO247 *o);
void sub_00189DA0o(M1OrbO247 *o, M1OrbA247 *a, int32_t st);   /* 0x189DA0 */

/* 0x00198E80: attach o to the first free of 8 orbit records (0x1C bytes) with its handlers and orbit parameters,
   then start it in step 1; returns 1, or 0 when all are in use. */
int m1_OrbAttach198E80(M1OrbO247 *o, M1OrbA247 *a)
{
    M1OrbS247 *r;
    float k;
    for (r = r4c_recs401838; (intptr_t)r < (intptr_t)(r4c_recs401838 + 8); r++)
        if (!r->o0)
            goto found;
    return 0;
found:
    k = m1_orbF32C8C8;
    r->o0 = o;
    a->slot74 = r;
    a->p84 = m1_orbT32C878;
    a->p88 = m1_orbT32C8A0;
    a->cb78 = (void *)m1_orbStepA198460;
    a->cb7C = (void *)r4h_FxOrbitStepB;
    a->cb80 = (void *)m1_orbStepC198780;
    o->v70[2] = k;
    o->v70[1] = k;
    o->v70[0] = k;
    o->w7C = 1.0f;
    a->n24 = 1;
    o->n124 = 1;
    o->nD0 = sub_0001BC40(o);
    o->fB0 = m1_orbF32C8D0;
    o->fB4 = m1_orbF32C8D4;
    o->fA4 = m1_orbF32C8D8;
    o->nEC = 0;
    o->fE8 = 0.0f;
    o->flagsC = (o->flagsC & ~0x80u) | 0x100;
    o->flags10 |= 0x45;
    sub_00189DA0o(o, a, 1);
    a->slot74->n8 = 0;
    return 1;
}

typedef struct M1LkS247 { uint8_t unk00[4]; int32_t n4; } M1LkS247;
typedef struct M1LkA247 { uint8_t unk00[0x70]; float t70; M1LkS247 *slot74; } M1LkA247;
typedef struct M1LkO247 { uint8_t unk00[0x60]; uint8_t pos60[0x10]; } M1LkO247;
extern uint8_t g_stats[];
void sub_000F5D40(void *dst, const void *src);
void sub_00189DA0m(M1LkO247 *o, M1LkA247 *a, int32_t st);   /* same function (alias stops cl merging calls) */
extern float m1_lkF32C90C;
extern M1LkO247 *g_playerObjL;
int32_t PlayerObj_GetState(void *p);
void m1_TgtInfo0C4250(void *p, float *a, float *b);
int32_t sub_000EE2B0(float *a, float *b, float *c);
int32_t sub_000D3BF0(void *p, M1LkO247 *o, int32_t z, float *a, float *b);
void sub_00189DA0l(M1LkO247 *o, M1LkA247 *a, int32_t st);   /* 0x189DA0 */

/* 0x001989E0: lock-on effect: unless the player is in state 8, test whether o (raised to the lock height) is inside
   the player's view and targetable, and if so go to step 3; otherwise when the timer runs out go to step 4. */
void m1_LockOn1989E0(M1LkO247 *o, M1LkA247 *a)
{
    float pos[4], tgt[4], dir[4], hit[4], box[4], ray[4];
    if (PlayerObj_GetState(g_stats) != 8) {
        sub_000F5D40(pos, o->pos60);
        pos[1] = m1_lkF32C90C;
        m1_TgtInfo0C4250(g_stats, box, tgt);
        ray[0] = tgt[1];
        ray[2] = tgt[3];
        if (sub_000EE2B0(hit, ray, pos) == 1) {
            aab_Vec1AD9F0(dir, g_playerObjL->pos60, o->pos60);
            dir[3] = 1.0f;
            if (sub_000D3BF0(g_stats, o, 0, hit, dir) == 1) {
                sub_00189DA0l(o, a, 3);
                a->slot74->n4 = 0;
                return;
            }
        }
    }
    if (a->t70 <= 0.0f) {
        sub_00189DA0m(o, a, 4);
        a->slot74->n4 = 0;
    }
}

typedef struct M1LkB247 { uint8_t unk00[0x60]; uint8_t pos60[0x88]; float fE8; } M1LkB247;
typedef struct M1LkC247 { uint8_t unk00[0x20]; uint32_t flags20; } M1LkC247;
extern float b10_f3F7504;
int32_t sub_000D3BF0b(void *p, M1LkB247 *o, int32_t k, float *a, float *b);   /* 0xD3BF0 */
int32_t aab_Effect494D0(int32_t snd, void *pos, int32_t z);

/* 0x0018ED40: lock onto o if it is visible from the player and targetable (mode 1, or 2 with s flag 1): play the
   lock sound (0x88, or 0x90 with flag 1) and set the global lock timer to 120 frames (0 with flag 1); returns 1, or 0
   (regargs: o=ESI s=EBX). */
int m1_LockTry18ED40(M1LkB247 *o, M1LkC247 *s)
{
    float pos[4], tgt[4], box[4], hit[4], dir[4], ray[4];
    float t;
    sub_000F5D40(pos, o->pos60);
    pos[1] = o->fE8;
    m1_TgtInfo0C4250(g_stats, box, tgt);
    ray[0] = tgt[1];
    ray[2] = tgt[3];
    if (!sub_000EE2B0(hit, ray, pos))
        return 0;
    aab_Vec1AD9F0(dir, g_playerObjL->pos60, o->pos60);
    if (sub_000D3BF0b(g_stats, o, (s->flags20 & 1) + 1, hit, dir) == -1)
        return 0;
    aab_Effect494D0((-((uint8_t)s->flags20 & 1) & 8) + 0x88, box, 0);
    t = 120.0f / a50_frameUnits * a50_frameSeconds;
    b10_f3F7504 = t;
    if (s->flags20 & 1)
        b10_f3F7504 = t * 0.0f;
    return 1;
}

typedef struct M1SpE247 { uint8_t unk00[8]; void *act8; float fC; uint8_t unk10[4]; float f14; uint8_t unk18[0x2C];
    float v44[1]; float f48; uint8_t unk4C[0x14]; uint8_t v60[0x22]; uint16_t w82; float f84; } M1SpE247;
typedef struct M1SpA247 { uint8_t unk00[0x74]; M1SpE247 *e74; } M1SpA247;
typedef struct M1SpO247 { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x4C]; float pos60[3]; float w6C;
    uint8_t unk70[0xB8]; uint8_t flags128; } M1SpO247;
extern uint8_t r4c_spin32C7B8[];
int32_t Stats_HasEFC(void);
void r6_Mat1ADB40(void *dst, const void *src);
void r4c_FxScale(M1SpO247 *o, float s);   /* regargs: o=EAX */
void r4c_Spin(M1SpO247 *o, const void *t);
void sub_001ADAF0(float *out, const float *a, const float *b);
int32_t sub_000F60C0(M1SpO247 *o, int32_t a, int32_t b);
void sub_00189DA0s(M1SpO247 *o, void *a, int32_t st);   /* 0x189DA0 */

/* 0x00195920: spinning pickup tick: show only with the EFC stat, follow o, grow its scale toward 1.5 (1.2 per 10 frame
   units), spin, drift by v44, sink +0x48 by +0x84, and after 11 units (or on ground / when its anchor vanishes) go to
   step 2; advance the age +0xC by frame seconds (calls 0x1955B0 with o=EAX). */
void m1_Pickup195920(M1SpO247 *o, M1SpA247 *a)
{
    M1SpE247 *e = a->e74;
    float v;
    if (Stats_HasEFC() > 0)
        o->flags10 |= 1;
    else
        o->flags10 &= ~1u;
    r6_Mat1ADB40(e->v60, o->pos60);
    if (e->f14 < 1.5f) {
        v = 1.2f / (10.0f / a50_frameUnits) + e->f14;
        e->f14 = v;
        if (v > 1.5f)
            e->f14 = 1.5f;
        r4c_FxScale(o, e->f14);
    }
    r4c_Spin(o, r4c_spin32C7B8);
    sub_001ADAF0(o->pos60, o->pos60, e->v44);
    o->w6C = 1.0f;
    e->f48 -= e->f84;
    if (e->fC > 11.0f || (o->flags128 & 0xA) || sub_000F60C0(o, 0, 0) != -1) {
        e->w82 = 1;
        sub_00189DA0s(o, e->act8, 2);
    }
    e->fC += a50_frameSeconds;
}
