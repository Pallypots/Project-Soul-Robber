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
