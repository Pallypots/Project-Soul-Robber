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
