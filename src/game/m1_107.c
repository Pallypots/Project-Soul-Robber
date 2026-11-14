/* Area m1, file 107. Names inferred. */
#include <stdint.h>

typedef struct M1Rec107 { int16_t used00; uint8_t unk02[2]; void *tgt04; uint8_t unk08[0x3C - 8]; } M1Rec107;
typedef struct M1Tgt107 { uint8_t unk000[0x130]; int32_t i130; } M1Tgt107;
typedef struct M1Step107R {
    uint8_t unk00[0x2C];
    float   f2C;               /* +0x2C */
    uint8_t unk30[0x74 - 0x30];
    M1Rec107 *rec74;           /* +0x74 */
    void   *fn78, *fn7C, *fn80; /* +0x78 */
    const void *tbl84, *tbl88; /* +0x84 */
} M1Step107R;
typedef struct M1Obj107R {
    uint8_t unk000[0xC];
    uint32_t flags0C;          /* +0x0C */
    uint32_t flags10;          /* +0x10 */
    uint8_t unk014[0xA4 - 0x14];
    float   fA4;               /* +0xA4 */
    uint8_t unk0A8[0xB0 - 0xA8];
    float   fB0, fB4;          /* +0xB0 */
    uint8_t unk0B8[0xD0 - 0xB8];
    int32_t iD0;               /* +0xD0 */
    uint8_t unk0D4[0xE8 - 0xD4];
    float   fE8;               /* +0xE8 */
    int32_t iEC, iF0, iF4;     /* +0xEC */
    uint8_t unk0F8[0x124 - 0xF8];
    int32_t i124;              /* +0x124 */
    uint8_t unk128[0x130 - 0x128];
    int32_t i130;              /* +0x130 */
} M1Obj107R;
extern M1Rec107 m1_recs3FFDE0[];
extern const uint8_t m1_cbTbl32C594[], m1_cbTbl32C5B4[];
void sub_0018E040(void);
void sub_0018E100(void);
void sub_0018EE50(void);
int  sub_0001BC40(void *o);
void sub_00189DA0(void *o, void *h, int a);

/* 0x0018F530: setup with a target: hang if a record is already held, take a free one from
 * table 0x3FFDE0 (12 entries, 0 when full), link the target and copy its +0x130, hook the
 * step callbacks and tables, +0x2C = -4, object sizes and modes, then 0x189DA0(o, h, 1). */
int m1_Setup18F530(M1Obj107R *o, M1Step107R *h, M1Tgt107 *t)
{
    M1Rec107 *e;
    if (h->rec74 != 0)
        for (;;) ;
    for (e = m1_recs3FFDE0; (int)e < (int)(m1_recs3FFDE0 + 12); e++)
        if (e->used00 == 0)
            goto found;
    return 0;
found:
    e->used00 = 1;
    h->rec74 = e;
    e->tgt04 = t;
    o->i130 = t->i130;
    h->tbl84 = m1_cbTbl32C594;
    h->tbl88 = m1_cbTbl32C5B4;
    h->fn78 = sub_0018E040;
    h->fn7C = sub_0018E100;
    h->fn80 = sub_0018EE50;
    h->f2C = -4.0f;
    o->flags0C &= ~0xA0u;
    o->i124 = 0;
    o->iD0 = sub_0001BC40(o);
    o->fB0 = 2.5f;
    o->fB4 = -2.0f;
    o->fA4 = 1.0f;
    o->fE8 = 4.0f;
    o->iEC = 1;
    o->iF0 = 3;
    o->iF4 = 0x80000000;
    o->flags10 |= 0x205;
    sub_00189DA0(o, h, 1);
    return 1;
}

typedef struct M1Part107 { uint8_t unk00[0x70]; float v70[4]; } M1Part107;
typedef struct M1Obj107M {
    uint8_t unk00[0x20];
    float  *m20;               /* +0x20 */
    uint8_t unk24[0x34 - 0x24];
    M1Part107 *p34;            /* +0x34 */
    uint8_t unk38[0x60 - 0x38];
    float   pos60[4];          /* +0x60 */
    uint8_t unk70[0x80 - 0x70];
    float   v80[4];            /* +0x80 */
} M1Obj107M;
typedef struct M1Step107M { uint8_t unk00[0x4C]; uint32_t flags4C; uint8_t unk50[0x64 - 0x50]; float v64[4]; } M1Step107M;
void sub_001AD940(float *m);
void sub_001AD7C0(float *d, const float *a, const float *b);
void sub_001AD9B0(float *d, const float *m, const float *v);
void sub_001ADAF0(float *d, const float *a, const float *b);
void sub_001ADA40(float *d, const float *m);
void sub_000F5D40(float *d, const float *s);

/* 0x00166E20: move with offsets: rotation-only copy of the object matrix, the part +0x70
 * offset rotated by it (none while flag 2), plus position, pending +0x80 push (then cleared)
 * and the step +0x64 velocity; written back as the new position and matrix. */
void m1_MoveApply166E20(M1Obj107M *o, M1Step107M *h)
{
    struct { float v[4]; float m[16]; } l;
    sub_001AD940(l.m);
    sub_001AD7C0(l.m, l.m, o->m20);
    l.m[12] = 0.0f;
    l.m[13] = 0.0f;
    l.m[14] = 0.0f;
    l.m[15] = 1.0f;
    if (!(h->flags4C & 2)) {
        sub_001AD9B0(l.v, l.m, o->p34->v70);
    } else {
        l.v[0] = 0.0f;
        l.v[1] = 0.0f;
        l.v[2] = 0.0f;
        l.v[3] = 1.0f;
    }
    sub_001ADAF0(l.v, o->pos60, l.v);
    sub_001ADAF0(l.v, l.v, o->v80);
    o->v80[0] = 0.0f;
    o->v80[1] = 0.0f;
    o->v80[2] = 0.0f;
    o->v80[3] = 1.0f;
    sub_001ADAF0(l.v, l.v, h->v64);
    l.v[3] = 1.0f;
    sub_000F5D40(o->pos60, l.v);
    sub_001ADA40(o->m20, l.m);
    sub_000F5D40(o->m20 + 12, l.v);
}

typedef struct M1Anim107 { uint8_t unk00[0xD8]; float speedD8; } M1Anim107;
typedef struct M1Mot107 { uint8_t unk00[8]; int32_t kind08; uint8_t unk0C[0x14 - 0xC]; M1Anim107 *anim14; } M1Mot107;
typedef struct M1Cam107 { uint8_t unk00[0x30]; M1Mot107 *mot30; uint8_t unk34[0x54 - 0x34]; float yaw54; } M1Cam107;
typedef struct M1Scr107 { uint8_t unk000[0x8C]; M1Cam107 *cam8C; uint8_t unk090[0x1CC - 0x90]; int32_t dir1CC; } M1Scr107;
extern M1Scr107 *m1_scr3F6130;
extern struct M1Pl107 { uint8_t unk00[0x60]; float pos60[4]; } *g_playerObj;
extern float m1_frameTime42C858;
float sub_000F7720(void *o, const void *pt);
void sub_000F5ED0(float *a);

/* 0x001050B0: turn toward the player: only while the motion (kind 1/2) runs at 15..50 times
 * the frame rate; turn by at most lim in direction +0x1CC (1 when already past), wrap the
 * angle, and return 1 once facing within 20 degrees. */
int m1_TurnToPlayer1050B0(float lim)
{
    M1Scr107 *g = m1_scr3F6130;
    M1Cam107 *c = g->cam8C;
    float a = sub_000F7720(c, g_playerObj->pos60);
    int ret = 0;
    M1Mot107 *m = m1_scr3F6130->cam8C->mot30;
    float t, v, step;
    if (m->kind08 != 1 && m->kind08 != 2)
        return 0;
    t = 1.0f / m1_frameTime42C858;
    v = m->anim14->speedD8;
    if (!(v >= t * 15.0f) || !(t * 50.0f >= v))
        return 0;
    step = lim;
    if (lim > a && a > 0.0f - lim)
        step = a;
    if (g->dir1CC == 0) {
        if (0.0f >= a)
            return 1;
        c->yaw54 += step;
    } else if (g->dir1CC == 1) {
        if (a > 0.0f)
            return 1;
        c->yaw54 -= step;
    }
    sub_000F5ED0(&c->yaw54);
    if (0.34906587f > a && a > -0.34906587f)
        ret = 1;
    return ret;
}

typedef struct M1Dat107 { uint8_t unk00[4]; int32_t busy04; uint8_t unk08[4]; float score0C; } M1Dat107;
typedef struct M1Comp107 { uint8_t unk00[0x60]; int32_t mode60; uint8_t unk64[0x74 - 0x64]; M1Dat107 *dat74; } M1Comp107;
void *sub_000EDC20(int kind, int id);
M1Comp107 *sub_0001D960(void *o, int kind);
int  sub_000ED780(void *o);

/* 0x0018B130: crowd control: over entities of kinds (5: 1, 2, 3, 0x1B), count the idle ones and
 * track the best and second-best scorer (+0xC, modes 4..7 excluded); with 6 or more remove the
 * best and wake the second, with 5 wake the best unless it is in mode 1. */
void m1_CrowdCheck18B130(void)
{
    int ids[4];
    void *e;
    M1Comp107 *c;
    M1Dat107 *d;
    void *best = 0;
    void *prev = 0;
    M1Comp107 *bestC = 0;
    M1Comp107 *prevC;
    float score;
    int n;
    int i;
    ids[0] = 1;
    ids[1] = 2;
    ids[2] = 3;
    ids[3] = 0x1B;
    n = 0;
    score = 0.0f;
    prevC = 0;
    for (i = 0; i < 4; i++) {
        for (e = sub_000EDC20(5, ids[i]); e; e = sub_000EDC20(-1, -1)) {
            c = sub_0001D960(e, 7);
            if (c == 0)
                for (;;) ;
            d = c->dat74;
            if (d->busy04 == 0) {
                n++;
                if (d->score0C > score && c->mode60 != 4 && c->mode60 != 5 && c->mode60 != 6 && c->mode60 != 7) {
                    prev = best;
                    prevC = bestC;
                    score = d->score0C;
                    best = e;
                    bestC = c;
                }
            }
        }
    }
    if (n >= 6) {
        sub_000ED780(best);
        sub_00189DA0(prev, prevC, 1);
    } else if (n >= 5 && bestC->mode60 != 1) {
        sub_00189DA0(best, bestC, 1);
    }
}

typedef int (*M1Check107)(void *o, void *h, const void *tbl);
typedef struct M1Rig107T { uint8_t unk00[0x18]; float wait18; } M1Rig107T;
typedef struct M1Step107T {
    uint8_t unk000[0xFC];
    float   angFC;             /* +0xFC */
    float   dist100;           /* +0x100 */
    uint8_t unk104[0x278 - 0x104];
    M1Rig107T *rig278;         /* +0x278 */
} M1Step107T;
typedef struct M1Obj107T { uint8_t unk000[0x128]; uint8_t b128; } M1Obj107T;
typedef struct M1Cmd107 { uint8_t unk00[0x10]; float f10, f14; } M1Cmd107;
extern M1Check107 m1_chkFn31D0B8, m1_chkFn31D0CC, m1_chkFn31D0C0;
extern const uint8_t m1_chkTbl2797C8[], m1_chkTbl279818[], m1_tbl2797E8[];
void sub_00113CB0(float *v, float a, int b);
float sub_001A3F30(float x);
M1Cmd107 *sub_001133E0(void *h, int v);
void sub_00113370(void *h, void *s);
void sub_00113040(void *o, void *h, int state);

/* 0x00140D30: walk decision: count down +0x18, then by the check tables, ground flags, the
 * distance (+0x100 < 50) and the wait: state 0xA, 0x29, 0x13, 0x12 or none; turn command 9
 * at 4 degrees/frame when the |angle| is under 150 degrees; switch when a state was picked. */
void m1_WalkPick140D30(M1Obj107T *o, M1Step107T *h)
{
    M1Rig107T *r = h->rig278;
    float *w = &r->wait18;
    M1Cmd107 *c;
    float a;
    float t;
    int st = -1;
    sub_00113CB0(w, m1_frameTime42C858 * 0.75f, 0);
    a = sub_001A3F30(h->angFC);
    if (m1_chkFn31D0B8(o, h, m1_chkTbl2797C8))
        st = 0xA;
    else if (m1_chkFn31D0CC(o, h, m1_chkTbl279818))
        st = 0x29;
    else if (m1_chkFn31D0C0(o, h, m1_tbl2797E8))
        st = 0x13;
    else if ((o->b128 & 7) || h->dist100 >= 50.0f)
        st = 0x29;
    else if (20.0f >= *w)
        st = 0x12;
    c = sub_001133E0(h, 9);
    if (2.61799383f > a) {
        t = m1_frameTime42C858 * 0.0698131695f;
        c->f14 = 0.0f - t;
    } else {
        t = 0.0f;
        c->f14 = 0.0f;
    }
    c->f10 = t;
    if (st >= 0) {
        sub_00113370(h, c);
        sub_00113040(o, h, st);
    }
}

typedef struct M1Rig107K { uint8_t unk00[0x50]; uint32_t flags50; uint8_t unk54[0x68 - 0x54]; float f68; float f6C; uint8_t unk70[0x78 - 0x70]; float v78[4]; } M1Rig107K;
typedef struct M1Step107K {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0xF8 - 0x50];
    int32_t mode0F8;           /* +0xF8 */
    uint8_t unk0FC[0x104 - 0xFC];
    void   *tgt104;            /* +0x104 */
    uint8_t unk108[0x278 - 0x108];
    M1Rig107K *rig278;         /* +0x278 */
} M1Step107K;
typedef struct M1Cmd107K { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Cmd107K;
extern float m1_frameRate42C85C;
int  sub_001456E0(void *o, void *h, int a, int b);
void sub_00156180(void *r, float a, float b, float c, float d);
void sub_001561D0(void *r, float a, float b);
M1Cmd107K *sub_00113400(void *h, int v);
void sub_000F5D40(float *d, const float *s);

/* 0x00149890: knock-back setup: state 0x15, rig motion (5 * frameRate, decay 0.003), rise
 * (-8, 10 * frameRate), flag 0x40, +0x68 += 100 clamped to 0..200, +0x6C = 0, and a +-30
 * degree sway at 2 degrees/frame. */
void m1_KnockBack149890(void *o, M1Step107K *h)
{
    M1Rig107K *r = h->rig278;
    M1Rig107K *p;
    M1Cmd107K *c;
    float v;
    float t;
    sub_001456E0(o, h, 0x15, 0);
    sub_00156180(r, m1_frameRate42C85C * 5.0f, 0.0f, 0.0f, m1_frameTime42C858 * 0.00300000003f);
    sub_001561D0(r, -8.0f, m1_frameRate42C85C * 10.0f);
    r->flags50 |= 0x40;
    h->flags4C &= ~0x70u;
    p = h->rig278;
    v = p->f68 + 100.0f;
    p->f68 = v;
    if (0.0f > v)
        p->f68 = 0.0f;
    else if (v > 200.0f)
        p->f68 = 200.0f;
    r->f6C = 0.0f;
    t = m1_frameTime42C858 * 0.0349065848f;
    c = sub_00113400(h, 1);
    c->f10 = 0.52359879f;
    c->f14 = -0.52359879f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
}

/* 0x00149C40: as 0x149890 without the push, +0x68 += 30, aimed at the player (+0x104, mode 1,
 * position copied to rig +0x78), and a +-15 degree sway at 5 degrees/frame. */
void m1_KnockBack149C40(void *o, M1Step107K *h)
{
    M1Rig107K *r = h->rig278;
    M1Rig107K *p;
    M1Cmd107K *c;
    struct M1Pl107 *g;
    float v;
    float t;
    sub_001456E0(o, h, 0x15, 0);
    sub_00156180(r, 0.0f, 0.0f, 0.0f, m1_frameTime42C858 * 0.00300000003f);
    sub_001561D0(r, -8.0f, m1_frameRate42C85C * 10.0f);
    h->flags4C &= ~0x70u;
    p = h->rig278;
    v = p->f68 + 30.0f;
    p->f68 = v;
    if (0.0f > v)
        p->f68 = 0.0f;
    else if (v > 200.0f)
        p->f68 = 200.0f;
    r->flags50 |= 0x40;
    g = g_playerObj;
    h->tgt104 = g;
    h->mode0F8 = 1;
    sub_000F5D40(r->v78, g->pos60);
    t = m1_frameTime42C858 * 0.0872664675f;
    c = sub_00113400(h, 1);
    c->f10 = 0.261799395f;
    c->f14 = -0.261799395f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
}
