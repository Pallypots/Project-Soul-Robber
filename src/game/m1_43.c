/* Area m1, file 43: entry pose sync. Names inferred. */
#include <stdint.h>

typedef struct M1PoseObj {
    uint8_t unk00[0x50];
    float   rot50[4];          /* +0x50 */
    float   pos60[4];          /* +0x60 */
} M1PoseObj;
typedef struct M1EntP {
    uint8_t    unk000[0x70];
    float      pos070[4];      /* +0x070 */
    float      rot080[4];      /* +0x080 */
    uint8_t    unk090[0x120 - 0x90];
    M1PoseObj *obj120;         /* +0x120 */
} M1EntP;
void sub_000F5D40(void *dst, const void *src);

/* 0x000A3D40: copies e's position and rotation to its object (w = 1 on both sides). */
void m1_SyncPoseA3D40(M1EntP *e)
{
    sub_000F5D40(e->obj120->pos60, e->pos070);
    e->pos070[3] = 1.0f;
    e->obj120->pos60[3] = 1.0f;
    sub_000F5D40(e->obj120->rot50, e->rot080);
    e->rot080[3] = 1.0f;
    e->obj120->rot50[3] = 1.0f;
}

/* 0x000A35B0: wraps the angle at a into [-pi, pi] in 2*pi steps. */
void m1_WrapAngleA35B0(float *a)
{
    float x;
    if (a == 0)
        return;
    if (*a > 3.1415927f) {
        x = *a;
        do
            x = x - 6.2831855f;
        while (x > 3.1415927f);
        *a = x;
    }
    if (-3.1415927f > *a) {
        x = *a;
        do
            x = x + 6.2831855f;
        while (-3.1415927f > x);
        *a = x;
    }
}

typedef struct M1SpinW {
    uint32_t flags00;          /* +0x00 */
    float    rate04;           /* +0x04 */
    float    f08;              /* +0x08 */
} M1SpinW;
typedef struct M1SpinA { uint8_t unk00[0x74]; M1SpinW *spin74; } M1SpinA;
typedef struct M1SpinO {
    uint8_t  unk00[0xC];
    uint32_t flags0C;          /* +0x0C */
    uint32_t flags10;          /* +0x10 */
    uint8_t  unk14[0x50 - 0x14];
    float    rot50[4];         /* +0x50 */
    uint8_t  unk60[0x80 - 0x60];
    float    v80[4];           /* +0x80 */
} M1SpinO;
extern float m1_frameRate42C85C;          /* 0x0042C85C */
extern void *g_playerObj;                 /* 0x00420E98 */
void sub_001ADBA0(float *d, const float *a, float s);

#define M1_SPIN_CORE(o, a) \
    w = (a)->spin74; \
    w->rate04 = m1_frameRate42C85C * 3.1415927f; \
    w->flags00 |= 0xC; \
    (o)->flags10 &= ~0x20u; \
    (o)->rot50[1] += 3.1415927f; \
    if ((o)->rot50[1] > 3.1415927f) \
        (o)->rot50[1] -= 6.2831855f; \
    sub_001ADBA0((o)->v80, (o)->v80, -2.0f); \
    (o)->v80[1] = 0.0f; \
    w->f08 = 0.0f

/* 0x0018D190: half-turn spin: sets the spin rate, turns o by pi, scales its +0x80
 * vector by -2 (y cleared), then copies Jack's rotation. */
void m1_SpinTurn18D190(M1SpinO *o, M1SpinA *a)
{
    M1SpinW *w;
    M1_SPIN_CORE(o, a);
    sub_000F5D40(o->rot50, (uint8_t *)g_playerObj + 0x50);
}

/* 0x0018D090: as 0x18D190 starting from a unit +0x80 vector (0,0,0,1), and clears
 * flag 0x80 instead of copying Jack's rotation. */
void m1_SpinStart18D090(M1SpinO *o, M1SpinA *a)
{
    M1SpinW *w;
    o->v80[0] = 0.0f;
    o->v80[1] = 0.0f;
    o->v80[2] = 0.0f;
    o->v80[3] = 1.0f;
    M1_SPIN_CORE(o, a);
    o->flags0C &= ~0x80u;
}

typedef struct M1Rec3C {
    int16_t w00;               /* +0x00 */
    int16_t w02;               /* +0x02, -1 */
    int32_t f04, f08;          /* +0x04 */
    float   v0C[4];            /* +0x0C: 0, 0, -70, 1 */
    float   v1C[4];            /* +0x1C: 0, 0, 0, 1 */
    float   v2C[4];            /* +0x2C: 0, 0, 0, 1 */
} M1Rec3C;
extern M1Rec3C m1_recs3FFDE0[12];   /* 0x003FFDE0 */

/* 0x0018DFC0: resets the twelve 0x3C records at 0x3FFDE0. */
void m1_ResetRecs18DFC0(void)
{
    int i;
    for (i = 0; i < 12; i++) {
        M1Rec3C *r = &m1_recs3FFDE0[i];
        r->w00 = 0;
        r->f04 = 0;
        r->f08 = 0;
        r->w02 = -1;
        r->v0C[0] = 0.0f;
        r->v0C[1] = 0.0f;
        r->v0C[2] = 0.0f;
        r->v0C[3] = 1.0f;
        r->v0C[2] = -70.0f;
        r->v1C[0] = 0.0f;
        r->v1C[1] = 0.0f;
        r->v1C[2] = 0.0f;
        r->v1C[3] = 1.0f;
        r->v2C[0] = 0.0f;
        r->v2C[1] = 0.0f;
        r->v2C[2] = 0.0f;
        r->v2C[3] = 1.0f;
    }
}

typedef struct M1Pos60 { uint8_t unk00[0x60]; float pos60[4]; } M1Pos60;
typedef struct M1Flag74 { uint8_t unk00[0x74]; uint8_t *flags74; } M1Flag74;
int   sub_00049700(int id, int r, int g, int b, const void *pos, int a, float size, int c);
void *sub_000C46A0(float x, float y, float z, const float *pos, float *a, float *b);
void  sub_000C4D30(void *o, int kind, float s, void *src);
int   r4i_ObjDestroy(void *o);

/* 0x0018DC90: spawns effect 0x7A at o, a 10-burst when the flag bit 1 is set, then
 * destroys o. */
void m1_BurstDestroy18DC90(M1Pos60 *o, M1Flag74 *a)
{
    float v[4];
    sub_00049700(0x7A, 0x80, 0x80, 0x80, o->pos60, 1, 100.0f, 0);
    if (*a->flags74 & 2) {
        v[0] = 0.0f;
        v[1] = 0.0f;
        v[2] = 0.0f;
        v[3] = 0.0f;
        sub_000C4D30(o, 10, 1.0f, sub_000C46A0(2.5f, 0.0f, 2.5f, o->pos60, v, v));
    }
    r4i_ObjDestroy(o);
}

typedef struct M1Obj130 {
    uint8_t  unk000[0x10];
    uint32_t flags10;          /* +0x010 */
    uint8_t  unk014[0x60 - 0x14];
    float    pos60[4];         /* +0x060 */
    uint8_t  unk070[0x130 - 0x70];
    void    *model130;         /* +0x130 */
} M1Obj130;
void *sub_00035DD0(M1Obj130 *o, void *model, int a, int b);
void  sub_00034E00(void *h, const float *pos, const float *dir, const float *col);

/* 0x0018DC00: disables o (flags 0xD), creates its model instance (0x35DD0 4, 3) and
 * places it at o pointing down -z with colour (0, 1, 0, 1). */
void m1_PlaceModel18DC00(M1Obj130 *o)
{
    float col[4], dir[4];
    void *h;
    o->flags10 |= 0xD;
    dir[2] = -1.0f;
    dir[0] = 0.0f;
    dir[1] = 0.0f;
    dir[3] = 1.0f;
    col[0] = 0.0f;
    col[1] = 1.0f;
    col[2] = 0.0f;
    col[3] = 1.0f;
    h = sub_00035DD0(o, o->model130, 4, 3);
    sub_00034E00(h, o->pos60, dir, col);
}

typedef struct M1BatW { uint8_t unk00[0x14]; void *owner14; } M1BatW;
typedef struct M1BatOwner { uint8_t unk000[0x130]; void *model130; } M1BatOwner;
typedef struct M1BatObj {
    uint8_t  unk000[0xC];
    uint32_t flags0C;          /* +0x0C */
    uint32_t flags10;          /* +0x10 */
    uint8_t  unk014[0xB0 - 0x14];
    float    fB0, fB4;         /* +0xB0 */
    uint8_t  unk0B8[0xD0 - 0xB8];
    int32_t  fD0;              /* +0xD0 */
    uint8_t  unk0D4[0xE8 - 0xD4];
    float    fE8;              /* +0xE8 */
    int32_t  fEC, fF0;         /* +0xEC */
    uint32_t fF4;              /* +0xF4 */
    uint8_t  unk0F8[0x130 - 0xF8];
    void    *model130;         /* +0x130 */
} M1BatObj;
typedef void (*M1BatFn)(void);
typedef struct M1BatAct {
    uint8_t  unk00[0x28];
    float    f28, f2C;         /* +0x28 */
    uint8_t  unk30[0x74 - 0x30];
    M1BatW  *w74;              /* +0x74 */
    M1BatFn  fn78, fn7C, fn80; /* +0x78 */
    void    *p84, *p88;        /* +0x84 */
} M1BatAct;
extern uint8_t m1_batParamA32C56C[], m1_batParamB32C580[];
M1BatW *sub_0018D3C0(void);
void sub_0018D740(void);
void sub_0018D8A0(void);
void sub_0018D770(void);
int  sub_0001BC40(M1BatObj *o);
void sub_00189DA0(void *o, void *a, int k);

/* 0x0018DED0: sets up a follower actor: allocates its work block (0 if none), links
 * the owner and its model, installs callbacks and parameters, configures o and
 * starts it (0x189DA0 mode 0). Returns 1. */
int m1_SetupFollower18DED0(M1BatObj *o, M1BatAct *a, M1BatOwner *own)
{
    M1BatW *w = sub_0018D3C0();
    if (w == 0)
        return 0;
    a->w74 = w;
    w->owner14 = own;
    o->model130 = own->model130;
    a->p84 = m1_batParamA32C56C;
    a->p88 = m1_batParamB32C580;
    a->fn78 = sub_0018D740;
    a->fn7C = sub_0018D8A0;
    a->fn80 = sub_0018D770;
    o->flags0C = (o->flags0C & ~0xA0u) | 0x100;
    o->fD0 = sub_0001BC40(o);
    o->fB0 = 2.5f;
    o->fB4 = 2.5f;
    o->fE8 = 2.0f;
    o->fEC = 1;
    o->fF0 = 3;
    o->fF4 = 0x80000000;
    a->f28 = 0.0f;
    a->f2C = -7.0f;
    o->flags10 |= 0x200;
    sub_00189DA0(o, a, 0);
    return 1;
}

typedef struct M1HeightRec {
    int32_t kind00;            /* +0x00, -1 ends the table */
    float   a04;               /* +0x04 */
    float   b08;               /* +0x08 */
} M1HeightRec;
extern M1HeightRec m1_heights2E2780[];   /* 0x002E2780 */
typedef struct M1KindObj { uint8_t unk00[8]; int32_t kind08; uint8_t unk0C[0x60 - 0xC]; float pos60[4]; } M1KindObj;

/* 0x000A1F50: out = o's position raised by ten times its kind's first height. */
void m1_RaisedPosA1F50(M1KindObj *o, float *out)
{
    float h = 0.0f;
    int i;
    for (i = 0; m1_heights2E2780[i].kind00 != -1; i++) {
        if (m1_heights2E2780[i].kind00 == o->kind08) {
            h = m1_heights2E2780[i].a04 * 10.0f;
            break;
        }
    }
    sub_000F5D40(out, o->pos60);
    out[1] += h;
}

/* 0x000A1FD0: as 0xA1F50 with the second height. */
void m1_RaisedPosA1FD0(M1KindObj *o, float *out)
{
    float h = 0.0f;
    int i;
    for (i = 0; m1_heights2E2780[i].kind00 != -1; i++) {
        if (m1_heights2E2780[i].kind00 == o->kind08) {
            h = m1_heights2E2780[i].b08 * 10.0f;
            break;
        }
    }
    sub_000F5D40(out, o->pos60);
    out[1] += h;
}

/* 0x000A3CC0: as 0xA3D40, but the object's rotation x is cleared after the copy. */
void m1_SyncPoseA3CC0(M1EntP *e)
{
    sub_000F5D40(e->obj120->pos60, e->pos070);
    e->pos070[3] = 1.0f;
    e->obj120->pos60[3] = 1.0f;
    sub_000F5D40(e->obj120->rot50, e->rot080);
    e->obj120->rot50[0] = 0.0f;
    e->rot080[3] = 1.0f;
    e->obj120->rot50[3] = 1.0f;
}

typedef struct M1Act150B { uint8_t unk000[0x150]; uint32_t flags150; } M1Act150B;
void sub_000CF330(M1Act150B *o, const float *v, float k);
void abc_SetState(void *o, int state);

/* 0x000CFF10: if src is given, pushes o towards src's position (0xCF330, 8.0);
 * then state 0x1E and flag 0x2000. */
void m1_PushStateCFF10(M1Act150B *o, M1Pos60 *src)
{
    float v[4];
    if (src != 0) {
        v[3] = 1.0f;
        v[0] = src->pos60[0];
        v[1] = src->pos60[1];
        v[2] = src->pos60[2];
        sub_000CF330(o, v, 8.0f);
    }
    abc_SetState(o, 0x1E);
    o->flags150 |= 0x2000;
}

typedef struct M1Stage314 {
    int32_t f000;              /* +0x000 */
    uint8_t unk004[0x308 - 4];
    int32_t f308, f30C;        /* +0x308 */
    uint8_t unk310[4];
    int32_t f314;              /* +0x314 */
} M1Stage314;
typedef struct M1Cam124 {
    uint8_t  unk000[0x8C];
    uint8_t *node08C;          /* +0x08C */
    uint8_t  unk090[0xAC - 0x90];
    float    fAC;              /* +0x0AC */
    uint8_t  unk0B0[0x124 - 0xB0];
    int32_t  snd124;           /* +0x124, -1 = none */
} M1Cam124;
extern M1Cam124 *m1_cam3F610C;    /* 0x003F610C */
M1Stage314 *sub_000E0770S(void);  /* 0x000E0770 */
void sub_000E0A80(M1Stage314 *s, int k, int a, int b, int c);
void sub_000E51F0(M1Stage314 *s);
int  sub_000494D0(int id, const void *pos, int c);

/* 0x000F4590: restarts the stage step (0xE0A80 kind 4), clears its counters, runs
 * 0xE51F0, sets the camera value 10.5 and starts sound 0x1E3 once. */
void m1_StageRestartF4590(void)
{
    M1Cam124 *c = m1_cam3F610C;
    M1Stage314 *s = sub_000E0770S();
    sub_000E0A80(s, 4, s->f000, s->f314, -1);
    s->f308 = 0;
    s->f30C = 0;
    sub_000E51F0(s);
    c->fAC = 10.5f;
    if (c->snd124 == -1)
        c->snd124 = sub_000494D0(0x1E3, c->node08C + 0x60, 1);
}

typedef struct M1EntE0 {
    uint32_t flags00;          /* +0x00 bit 0 in use, bits 1-2 kind */
    uint8_t  unk04[0x24 - 4];
    float    pos24[4];         /* +0x24 */
    uint8_t  unk34[0xE0 - 0x34];
} M1EntE0;
extern M1EntE0 m1_entsE41E2A0[32];   /* 0x0041E2A0 */
int m1_WithinRadiusA8090(void *t, const float *pos);   /* 0x000A8090, file 46 */

/* 0x000A8C90: 1 if any in-use entry of kind 1..3 is accepted by 0xA8090 for t
 * (tested at the entry's position), else -1. */
int m1_AnyNearA8C90(void *t)
{
    float v[4];
    int i;
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 1.0f;
    for (i = 0; i < 32; i++) {
        if ((m1_entsE41E2A0[i].flags00 & 1) && (m1_entsE41E2A0[i].flags00 & 6)) {
            sub_000F5D40(v, m1_entsE41E2A0[i].pos24);
            if (m1_WithinRadiusA8090(t, v) > 0)
                return 1;
        }
    }
    return -1;
}

typedef struct M1Rad14 M1Rad14;

typedef struct M1Skel3 { uint8_t unk00[0xC4]; uint8_t *bonesC4; } M1Skel3;
typedef struct M1Node3 { uint8_t unk00[0x20]; M1Skel3 *skel20; } M1Node3;
typedef struct M1JackN { uint8_t unk000[0xFD8]; M1Node3 *node0FD8; } M1JackN;

/* 0x000A8BF0: 1 if either of Jack's two hand bones (+0x370, +0x1F0 in his bone
 * block) is within t's radius, else the second test's result. */
int m1_HandsNearA8BF0(M1JackN *p, M1Rad14 *t)
{
    M1Skel3 *k = p->node0FD8->skel20;
    float v[4];
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 1.0f;
    sub_000F5D40(v, k->bonesC4 + 0x370);
    if (m1_WithinRadiusA8090(t, v) > 0)
        return 1;
    sub_000F5D40(v, k->bonesC4 + 0x1F0);
    return m1_WithinRadiusA8090(t, v);
}
