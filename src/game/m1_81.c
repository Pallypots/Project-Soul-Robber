/* Area m1, file 81: rig steps. Names inferred. */
#include <stdint.h>

typedef struct M1Cmd81 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Cmd81;
typedef struct M1Obj81 { uint8_t unk00[0x30]; void *anim30; } M1Obj81;
extern float m1_frameTime42C858;
int  sub_00145780(void *o, float frame);
M1Cmd81 *sub_00113400(void *h, int v);
void sub_00113480(void *h, int v);
int  sub_000833E0(void *a);
void sub_00117580(void *o, int v);

/* 0x00118070: at clip frame 12 start a +-10 degree sway (frameTime * 45/7), at frame 26 stop
 * it (0x113480); when the clip is done 0x117580(o, 1). */
void m1_SwayClip118070(M1Obj81 *o, void *h)
{
    if (sub_00145780(o, 12.0f)) {
        float t = m1_frameTime42C858 * 6.4285712f;
        M1Cmd81 *c = sub_00113400(h, 1);
        c->f10 = 0.17453294f;
        c->f14 = -0.17453294f;
        if (t != -1.0f)
            c->f18 = t;
        c->f1C = 0.0f;
    } else if (sub_00145780(o, 26.0f)) {
        sub_00113480(h, 1);
    }
    if (sub_000833E0(o->anim30))
        sub_00117580(o, 1);
}

typedef struct M1Rig81 { uint8_t unk00[0x50]; uint32_t flags50; } M1Rig81;
typedef struct M1Step81 {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x278 - 0x50];
    M1Rig81 *rig278;           /* +0x278 */
} M1Step81;
extern float m1_frameRate42C85C;
int  sub_001456E0(void *o, void *h, int a, int b);
void sub_00156180(void *rig, int a, int b, int c, float t);
void sub_001561D0(void *rig, float a, float b);
void *sub_00036750(void *o, int b);

/* 0x0014B1C0: enter state 0x15, rig spin (0x156180, frameTime * 0.003) and tilt (-15,
 * frameRate * 10), clear h +0x4C bits 0x70 and rig +0x50 bit 0x200, effect 1, command 5 =
 * (0.1, 0.1, 1/30, 1). */
void m1_RigSpin14B1C0(void *o, M1Step81 *h)
{
    M1Rig81 *r = h->rig278;
    M1Cmd81 *c;
    sub_001456E0(o, h, 0x15, 0);
    sub_00156180(r, 0, 0, 0, m1_frameTime42C858 * 0.003f);
    sub_001561D0(r, -15.0f, m1_frameRate42C85C * 10.0f);
    h->flags4C &= ~0x70u;
    r->flags50 &= ~0x200u;
    sub_00036750(o, 1);
    c = sub_00113400(h, 5);
    c->f10 = 0.1f;
    c->f14 = 0.1f;
    c->f18 = 0.033333335f;
    c->f1C = 1.0f;
}

typedef struct M1Obj81H {
    uint8_t unk00[0x54];
    float   yaw54;             /* +0x54 */
    uint8_t unk58[0x60 - 0x58];
    float   pos60[4];          /* +0x60 */
    uint8_t unk70[0x80 - 0x70];
    float   vel80[4];          /* +0x80 */
} M1Obj81H;
typedef struct M1Tgt81 { uint8_t unk00[0x60]; float pos60[4]; } M1Tgt81;
float sub_00113290(void *o, const float *pos);
void sub_001AD9F0(float *out, const float *a, const float *b);
void sub_001AD7E0(float *out, const float *v);
void sub_001ADBA0(float *d, const float *s, float k);
void sub_000F5D40(float *d, const float *s);

/* 0x0018D680: home in: turn the yaw toward the target (0x113290, wrapped to -pi..pi) and set
 * the velocity +0x80 to the direction to 15 below the target, scaled to speed. */
void m1_HomeIn18D680(M1Obj81H *o, M1Tgt81 *t, float speed)
{
    float *p = t->pos60;
    float v[4];
    o->yaw54 = o->yaw54 + sub_00113290(o, p);
    if (o->yaw54 > 3.1415927f)
        o->yaw54 -= 6.2831855f;
    if (-3.1415927f > o->yaw54)
        o->yaw54 += 6.2831855f;
    sub_001AD9F0(v, p, o->pos60);
    v[1] = v[1] - 15.0f;
    sub_001AD7E0(v, v);
    sub_001ADBA0(v, v, speed);
    sub_000F5D40(o->vel80, v);
}

typedef struct M1Rig81U { uint32_t unk00; uint32_t flags04; uint8_t unk08[0x2C - 8]; float q2C[4]; } M1Rig81U;
typedef struct M1Step81U { uint8_t unk000[0x278]; M1Rig81U *rig278; } M1Step81U;
typedef struct M1Obj81U { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x20 - 0x14]; float *node20; } M1Obj81U;
void sub_0001D4E0(void *o);
void sub_001ADA60(float *out, const float *a, const float *b);

/* 0x00116EA0: enter state 0x39, reset the rig quaternion, clear rig flag 0x80000, rebuild the
 * node frame upright (y = (0, 1, 0, 0)); rig flag 0x10 sets o flags 0xD. */
void m1_Upright116EA0(M1Obj81U *o, M1Step81U *h)
{
    M1Rig81U *r = h->rig278;
    M1Rig81U *p;
    float *n;
    float up[4];
    up[0] = 0.0f;
    up[1] = 1.0f;
    up[2] = 0.0f;
    up[3] = 0.0f;
    if (sub_001456E0(o, h, 0x39, 0) == 1)
        sub_0001D4E0(o);
    p = h->rig278;
    p->q2C[2] = 0.0f;
    p->q2C[1] = 0.0f;
    p->q2C[0] = 0.0f;
    p->q2C[3] = 1.0f;
    r->flags04 &= ~0x80000u;
    o->node20[1] = 0.0f;
    sub_001AD7E0(o->node20, o->node20);
    sub_000F5D40(o->node20 + 4, up);
    n = o->node20;
    sub_001ADA60(n + 8, n, n + 4);
    if (r->flags04 & 0x10)
        o->flags10 |= 0xD;
}

typedef struct M1Rig81V { uint32_t unk00; uint32_t flags04; uint8_t unk08[0x18 - 8]; float f18; uint8_t unk1C[0x30 - 0x1C]; float f30; } M1Rig81V;
typedef struct M1Step81V {
    uint8_t unk000[0x22];
    uint8_t b22;               /* +0x22 */
    uint8_t unk023[0x4C - 0x23];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x58 - 0x50];
    int32_t phase58;           /* +0x58 */
    uint8_t unk05C[0x278 - 0x5C];
    M1Rig81V *rig278;          /* +0x278 */
} M1Step81V;
typedef struct M1CmdCb { uint8_t unk00[0x10]; float f10, f14; int32_t i18; void (*cb1C)(void); } M1CmdCb;
void sub_00113090(void *o, void *h, int state);
M1CmdCb *sub_00113430(void *h, int v);
void sub_00119FF0(void);

/* 0x0011A3D0: hit: o flags 6, clear h +0x4C bit 0x10; without rig flag 0x40 enter state 0x15
 * (phase 1) or 4, effect 0 and command 1 = (0.3, 0.25, 1, 0x119FF0); with it enter state 6/7,
 * phase 2, o flag 1, clear h +0x4C bits 0x1000008. Then clear rig +0x18, +0x30, flags 0xC0. */
void m1_Hit11A3D0(M1Obj81U *o, M1Step81V *h)
{
    M1Rig81V *r = h->rig278;
    o->flags10 |= 6;
    h->flags4C &= ~0x10u;
    if (!(r->flags04 & 0x40)) {
        M1CmdCb *c;
        if (h->b22 & 1) {
            sub_00113090(o, h, 0x15);
            h->phase58 = 1;
        } else {
            sub_00113090(o, h, 4);
        }
        sub_00036750(o, 0);
        c = sub_00113430(h, 1);
        c->f10 = 0.3f;
        c->f14 = 0.25f;
        c->i18 = 1;
        c->cb1C = sub_00119FF0;
    } else {
        sub_00113090(o, h, (h->b22 & 1) + 6);
        h->phase58 = 2;
        o->flags10 |= 1;
        h->flags4C &= ~0x1000008u;
    }
    r->f18 = 0.0f;
    r->f30 = 0.0f;
    r->flags04 &= ~0xC0u;
}
