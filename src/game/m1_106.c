/* Area m1, file 106: recover variants and more. Names inferred. */
#include <stdint.h>

typedef struct M1Rig106 { uint32_t flags00; uint8_t unk04[0x50 - 4]; uint32_t flags50; } M1Rig106;
typedef struct M1Step106 {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x6C - 0x50];
    int32_t snd6C;             /* +0x6C */
    void   *fx70;              /* +0x70 */
    uint8_t unk074[0x278 - 0x74];
    M1Rig106 *rig278;          /* +0x278 */
} M1Step106;
typedef struct M1Obj106 { uint8_t unk000[0xC]; uint32_t flags0C; uint32_t flags10; uint8_t unk014[0x30 - 0x14]; void *anim30; uint8_t unk034[0x60 - 0x34]; float pos60[4]; uint8_t unk070[0x13C - 0x70]; int32_t i13C; } M1Obj106;
extern float m1_frameRate42C85C;
int  sub_000833E0(void *a);
void sub_001134B0(void *h);
void sub_00113AA0(void *o, void *h);
int  sub_000494D0(int id, const void *pos, int c);
void sub_0005BE30(int v);
void sub_00033A70(void *r);
void sub_00113040(void *o, void *h, int state);
void sub_00113190(void *o, void *h, int a);
void sub_001561D0(void *rig, float a, float b);

/* 0x00154250: recover once the clip ends: clear flags, rig setup (-10, 10 * frameRate) through
 * 0x1561D0, handle pending flags 0x10000 and 0x100000, start looping sound 0x10F, state 0x11. */
void m1_Recover154250(M1Obj106 *o, M1Step106 *h)
{
    M1Rig106 *r;
    if (!sub_000833E0(o->anim30))
        return;
    r = h->rig278;
    sub_001134B0(h);
    o->flags0C |= 0xE0;
    o->flags10 &= ~0x137u;
    h->flags4C &= ~0x100u;
    r->flags00 &= ~0x17u;
    r->flags50 &= ~0x241140u;
    sub_001561D0(r, -10.0f, m1_frameRate42C85C * 10.0f);
    if (r->flags50 & 0x10000) {
        sub_00113AA0(o, h);
        h->flags4C |= 0x200;
        r->flags50 &= ~0x10000u;
    }
    if (r->flags50 & 0x100000) {
        r->flags50 &= ~0x100000u;
        sub_00113190(o, h, 1);
    }
    if (h->snd6C == -1)
        h->snd6C = sub_000494D0(0x10F, o->pos60, 1);
    sub_0005BE30(o->i13C);
    if (h->fx70 != 0) {
        sub_00033A70(h->fx70);
        h->fx70 = 0;
    }
    sub_00113040(o, h, 0x11);
}

typedef struct M1Ent106 { uint8_t unk000[0xC]; uint32_t flags0C; uint32_t flags10; uint8_t unk014[0xB0 - 0x14]; float fB0; uint8_t unk0B4[0x14C - 0xB4]; int32_t i14C; } M1Ent106;
extern void *m1_scene42C8E4;
M1Ent106 *sub_000EDC20(int kind, int id);
void sub_0001D470(void *o, int i);
void sub_0001D4B0(void *o, int i);
void sub_0001EB80(void *e);
void sub_0001E9B0(void *s, void *e, int a, int b, int c);

/* 0x00172A30: show n lives: enable the first n parts of entity (6, 15), disable the rest up to
 * 5, hide entities 16..n+15, then raise entity n+16 (light it unless it has more than 10 in
 * +0xB0) and hide the rest up to 20. */
void m1_LivesShow172A30(int n)
{
    M1Ent106 *p = sub_000EDC20(6, 0xF);
    M1Ent106 *e;
    int i;
    if (p) {
        for (i = 0; i < n; i++)
            sub_0001D470(p, i);
        for (; i < 5; i++)
            sub_0001D4B0(p, i);
    }
    n += 0x10;
    for (i = 0x10; i < n; i++) {
        e = sub_000EDC20(6, i);
        if (e) {
            sub_0001EB80(e);
            e->flags10 |= 1;
            e->flags0C &= ~0x20u;
        }
    }
    e = sub_000EDC20(6, i);
    if (e) {
        sub_0001E9B0(m1_scene42C8E4, e, e->i14C, 5, 0x11);
        e->flags10 &= ~1u;
        e->flags0C |= 0x20;
        if (e->fB0 > 10.0f)
            e->flags0C &= ~0x20u;
    }
    for (i++; i <= 0x14; i++) {
        e = sub_000EDC20(6, i);
        if (e) {
            sub_0001EB80(e);
            e->flags10 |= 1;
            e->flags0C &= ~0x20u;
        }
    }
}

typedef struct M1Pl106 { uint8_t unk00[0x60]; float pos60[4]; } M1Pl106;
typedef struct M1Shot106 { uint8_t unk00[0x10]; int32_t n10; uint32_t s14; uint32_t s18; int32_t n1C; } M1Shot106;
extern M1Pl106 *g_playerObj;
extern uint8_t m1_stats41FEC0[];
int  sub_00113670(void *o, void *h, int n, float *tgt);
void sub_001AD9F0(float *out, const float *a, const float *b);
int  sub_000D3BF0(void *stats, void *o, int n, const float *tgt, const float *dir);
void sub_00113370(void *h, void *s);
void *sub_00035D80(void *o, int a, int b);
void sub_00034E00(void *fx, const float *pos, const float *dir, const float *up);

/* 0x00139890: shot with effect: as 0x1556D0 (unflattened direction), and on a hit play sound
 * and effect: the low halves of +0x14/+0x18 for hits below +0x1C (all of them when +0x1C is
 * 0, then whole), the high halves after; the effect gets up = (0, -1, 0). */
void m1_ShootFx139890(M1Pl106 *o, M1Step106 *h, M1Shot106 *s)
{
    float d[4];
    float tgt[4];
    float up[4];
    int idx, fx, snd;
    if (sub_00113670(o, h, s->n10, tgt) < 0)
        return;
    sub_001AD9F0(d, g_playerObj->pos60, o->pos60);
    d[3] = 1.0f;
    idx = sub_000D3BF0(m1_stats41FEC0, o, s->n10, tgt, d);
    if (idx != -1) {
        h->flags4C |= 0x100;
        if (s->n1C == 0) {
            fx = s->s14;
            snd = s->s18;
        } else if (idx < s->n1C) {
            fx = s->s14 & 0xFFFF;
            snd = s->s18 & 0xFFFF;
        } else {
            fx = *(uint16_t *)((char *)s + 0x16);
            snd = *(uint16_t *)((char *)s + 0x1A);
        }
        sub_000494D0(snd, tgt, 0);
        up[0] = 0.0f;
        up[1] = -1.0f;
        up[2] = 0.0f;
        up[3] = 1.0f;
        sub_00034E00(sub_00035D80(o, fx, 3), tgt, d, up);
    }
    sub_00113370(h, s);
}

typedef struct M1Tgt106 { uint8_t unk000[0x60]; float pos60[4]; uint8_t unk070[0x130 - 0x70]; int32_t i130; } M1Tgt106;
typedef struct M1Rig106G { uint32_t unk00; M1Tgt106 *tgt04; uint8_t unk08[0x20 - 8]; float wait20; } M1Rig106G;
typedef struct M1Step106G { uint8_t unk000[0x278]; M1Rig106G *rig278; } M1Step106G;
typedef struct M1Comp106 { uint8_t unk00[0x50]; int32_t mode50; } M1Comp106;
void *sub_00182750(int kind);
M1Comp106 *sub_0001D960(void *o, int kind);
int  sub_000F6A80(void);
int  sub_000F40B0(void);
void sub_000F5D40(float *d, const float *s);
int  sub_000F61D0(void *o, const float *pos, int a, float *out);
void *sub_00035DD0(void *o, int a, int b, int c);
void sub_00033880(void *fx, float *m);
void sub_00034DD0(void *fx, const float *pos, const float *dir, const float *up);

/* 0x001821B0: in modes 4/5 (component 6), when nothing blocks and the game is not in state 2:
 * find a ground point under the target (0xF61D0, gravity 9.82 passed along) and, once the
 * +0x20 wait is used up, spawn its effect there with sound 0x1E8 and wait 0.5 again. */
void m1_GroundFx1821B0(M1Pl106 *o, M1Step106G *h)
{
    struct { float up[4]; float hit[4]; float pos[4]; float g; float m[16]; } l;
    M1Rig106G *r = h->rig278;
    int mode = sub_0001D960(sub_00182750(6), 6)->mode50;
    void *fx;
    if (mode != 4 && mode != 5)
        return;
    if (sub_000F6A80())
        return;
    if (sub_000F40B0() == 2)
        return;
    l.g = 9.81999969f;
    sub_000F5D40(l.pos, r->tgt04->pos60);
    if (sub_000F61D0(r->tgt04, l.pos, 0, l.hit) == -1)
        return;
    if (0.0f >= r->wait20) {
        l.up[0] = 0.0f;
        l.up[1] = 1.0f;
        l.up[2] = 0.0f;
        l.up[3] = 1.0f;
        fx = sub_00035DD0(r->tgt04, r->tgt04->i130, 0, 1);
        sub_00033880(fx, l.m);
        sub_00034DD0(fx, l.hit, &l.m[8], l.up);
        sub_000494D0(0x1E8, o->pos60, 1);
        r->wait20 = 0.5f;
    }
}

typedef int (*M1Check106)(void *o, void *h, const void *tbl);
typedef struct M1Rig106T { uint8_t unk00[0x1C]; float fade1C; } M1Rig106T;
typedef struct M1Step106T {
    uint8_t unk000[0x74];
    float   wait74;            /* +0x74 */
    uint8_t unk078[0xFC - 0x78];
    float   angFC;             /* +0xFC */
    float   dist100;           /* +0x100 */
    uint8_t unk104[0x278 - 0x104];
    M1Rig106T *rig278;         /* +0x278 */
} M1Step106T;
typedef struct M1Obj106T { uint8_t unk000[0x128]; uint8_t b128; } M1Obj106T;
extern M1Check106 m1_chkFn31D0B8, m1_chkFn31D0C4, m1_chkFn31D0C8;
extern const uint8_t m1_chkTbl2797C8[], m1_chkTbl2797F8[], m1_chkTbl279808[];
extern float m1_frameTime42C858;
void sub_00113C60(float *v, float a, float b);
float sub_001A3F30(float x);
void sub_00113480(void *h, int v);

/* 0x00141E80: idle decision: fade +0x1C, then by the check tables and the target distance
 * (+0x100) and |angle| (+0xFC): state 0x2A (far, 100+), 0x14 (close and facing, or check 3),
 * or 0x2B with a 60-frame wait unless on the ground and nearer than 55. */
void m1_IdlePick141E80(M1Obj106T *o, M1Step106T *h)
{
    float a;
    float d;
    int st;
    sub_00113C60(&h->rig278->fade1C, m1_frameTime42C858 * 0.00200000009f, 1.0f);
    a = sub_001A3F30(h->angFC);
    d = h->dist100;
    if (m1_chkFn31D0B8(o, h, m1_chkTbl2797C8))
        st = 0x2A;
    else if (m1_chkFn31D0C4(o, h, m1_chkTbl2797F8))
        st = 0x14;
    else if (d >= 100.0f)
        st = 0x2A;
    else if ((25.0f > d && 0.69813174f > a) || m1_chkFn31D0C8(o, h, m1_chkTbl279808))
        st = 0x14;
    else {
        if (!(o->b128 & 7) && d < 55.0f)
            return;
        h->wait74 = 60.0f / m1_frameTime42C858 * m1_frameRate42C85C;
        st = 0x2B;
    }
    sub_00113480(h, 3);
    sub_00113040(o, h, st);
}

typedef struct M1Obj106B { uint8_t unk00[4]; int32_t i04; int32_t i08; uint8_t unk0C[0x20 - 0xC]; float *mtx20; uint8_t unk24[0x60 - 0x24]; float pos60[4]; } M1Obj106B;
typedef struct M1Sub106B { uint8_t unk00[0xC]; uint32_t flags0C; } M1Sub106B;
typedef struct M1Step106B { uint8_t unk00[0x6C]; union { int32_t i; float f; } v6C; uint8_t unk70[4]; M1Sub106B *sub74; } M1Step106B;
void sub_001AD7E0(float *out, const float *v);
void sub_001ADA60(float *out, const float *a, const float *b);
int  sub_0018BCA0(void *h);
int  sub_00145730(int a, int b);
int  sub_00171F10(int a, int b);
void *sub_000C46A0(void);
void sub_000C4D30(void *o, int k, float s, void *fx, float a, float b, float c, const float *pos, float *v0, float *v1);
int  sub_000ED780(void *o);

/* 0x0018C1B0: re-orthonormalise the object matrix, latch flag 4 when 0x18BCA0 says so, burst
 * effect (kind 10, or 11 when 0x171F10 matches) while flag 2 holds and 0x145730 agrees, and
 * remove the object once +0x6C reaches 1. */
void m1_FxStep18C1B0(M1Obj106B *o, M1Step106B *h)
{
    M1Sub106B *s = h->sub74;
    float v[4];
    float p[4];
    void *fx;
    int k;
    sub_001AD7E0(o->mtx20, o->mtx20);
    sub_001AD7E0(o->mtx20 + 4, o->mtx20 + 4);
    sub_001ADA60(o->mtx20 + 8, o->mtx20, o->mtx20 + 4);
    sub_001ADA60(o->mtx20, o->mtx20 + 4, o->mtx20 + 8);
    if (!(s->flags0C & 0xC) && sub_0018BCA0(h))
        s->flags0C |= 4;
    if ((s->flags0C & 2) && sub_00145730(h->v6C.i, 3)) {
        v[0] = 0.0f;
        v[1] = 0.0f;
        v[2] = 0.0f;
        v[3] = 1.0f;
        k = (sub_00171F10(o->i04, o->i08) != 0) + 10;
        fx = sub_000C46A0();
        sub_000F5D40(p, o->pos60);
        sub_000C4D30(o, k, 9.0f, fx, 4.0f, 0.333333343f, 1.0f, p, v, v);
    }
    if (h->v6C.f >= 1.0f)
        sub_000ED780(o);
}

typedef struct M1Cmd106 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Cmd106;
int  sub_001456E0(void *o, void *h, int a, int b);
M1Cmd106 *sub_00113400(void *h, int v);

typedef struct M1Rig106L {
    uint32_t unk00;
    float   f04, f08, f0C, f10;  /* +0x04 */
    uint8_t unk14[0x24 - 0x14];
    float   f24, f28, f2C, f30;  /* +0x24 */
    uint8_t unk34[0x38 - 0x34];
    void   *fx38;              /* +0x38 */
    uint8_t unk3C[4];
    uint32_t flags40;          /* +0x40 */
} M1Rig106L;
typedef struct M1Step106L {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x74 - 0x50];
    float   wait74;            /* +0x74 */
    uint8_t unk078[0x278 - 0x78];
    M1Rig106L *rig278;         /* +0x278 */
} M1Step106L;
typedef struct M1Obj106L { uint8_t unk00[0x10]; uint32_t flags10; } M1Obj106L;
int  sub_00036750(void *o, int v);
void sub_00147FD0(void *fx, int v);

/* 0x00157BC0: lunge setup: state 0x15, rig motion (-10, 10 * frameRate, 0.005 * frameTime),
 * flags, wait 4, pose 7, then a +-10 degree sway at 4 degrees/frame; a pending flag 0x1000
 * kicks the rig effect with 3. */
void m1_Lunge157BC0(M1Obj106L *o, M1Step106L *h)
{
    M1Rig106L *r = h->rig278;
    M1Cmd106 *c;
    float t;
    sub_001456E0(o, h, 0x15, 0);
    r->f2C = 0.0f;
    r->f28 = 0.0f;
    r->f24 = 0.0f;
    r->f10 = 0.0f;
    r->f0C = m1_frameTime42C858 * 0.00499999989f;
    r->f30 = 1.0f;
    r->f08 = m1_frameRate42C85C * 10.0f;
    r->f04 = -10.0f;
    o->flags10 |= 0x20;
    h->flags4C |= 0x70;
    r->flags40 |= 0x80;
    h->wait74 = 4.0f;
    sub_00036750(o, 7);
    t = m1_frameTime42C858 * 0.0698131695f;
    c = sub_00113400(h, 1);
    c->f10 = 0.174532935f;
    c->f14 = -0.174532935f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
    if (r->flags40 & 0x1000) {
        r->flags40 &= ~0x1000u;
        sub_00147FD0(r->fx38, 3);
    }
}

typedef struct M1Rig106W {
    uint8_t unk00[0x18];
    uint32_t flags18;          /* +0x18 */
    uint8_t unk1C[4];
    float   q20[4];            /* +0x20 */
    uint8_t unk30[0x84 - 0x30];
    int32_t i84;               /* +0x84 */
    float   cur88;             /* +0x88 */
    float   goal8C;            /* +0x8C */
    float   step90;            /* +0x90 */
} M1Rig106W;
typedef struct M1Step106W { uint8_t unk000[0x78]; float q78[4]; uint8_t unk088[0x278 - 0x88]; M1Rig106W *rig278; } M1Step106W;
typedef struct M1Obj106W { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x20 - 0x14]; void *m20; uint8_t unk24[0xE8 - 0x24]; float fE8; } M1Obj106W;
void sub_00145C90(float *d, void *m, const float *q);
void sub_00145CD0(float *d, const float *s, float k);
int  sub_000CF6C0(void);

/* 0x001866A0: while flag 2 holds, step +0x88 toward +0x8C by +0x90 and clear +0x84; build the
 * pose quaternion (0x145C90) scaled by 0.9 * +0xE8; show the object when 0xCF6C0 finds
 * something or rig flag 0x1000 is set, hide it otherwise; always clear flag 0x200. */
void m1_RigTurn1866A0(M1Obj106W *o, M1Step106W *h)
{
    M1Rig106W *r = h->rig278;
    M1Rig106W *r2;
    if (r->flags18 & 2) {
        if (r->goal8C > r->cur88) {
            r->cur88 += r->step90;
            if (r->cur88 > r->goal8C)
                r->cur88 = r->goal8C;
        } else if (r->cur88 > r->goal8C) {
            r->cur88 -= r->step90;
            if (r->goal8C > r->cur88)
                r->cur88 = r->goal8C;
        }
        r->i84 = 0;
    }
    sub_00145C90(h->q78, o->m20, h->rig278->q20);
    sub_00145CD0(h->q78, h->q78, o->fE8 * 0.899999976f);
    r2 = h->rig278;
    if (sub_000CF6C0() == -1 && !(r2->flags18 & 0x1000))
        o->flags10 &= ~1u;
    else
        o->flags10 |= 1;
    r->flags18 &= ~0x200u;
}
