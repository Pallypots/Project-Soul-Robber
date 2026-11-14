/* Area m1, file 109. Names inferred. */
#include <stdint.h>

typedef struct M1Cmd109 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Cmd109;
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
extern void *g_playerObj;
int  sub_001456E0(void *o, void *h, int a, int b);
void sub_0001D4E0(void *o);
M1Cmd109 *sub_00113400(void *h, int v);
int  sub_00036750(void *o, int v);

typedef struct M1Rig109A { uint8_t unk000[0xC]; uint32_t flags0C; uint8_t unk010[0x164 - 0x10]; float q164[4]; uint8_t unk174[0x184 - 0x174]; float spin184; } M1Rig109A;
typedef struct M1Step109A {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0xF8 - 0x50];
    int32_t mode0F8;           /* +0xF8 */
    uint8_t unk0FC[0x104 - 0xFC];
    void   *tgt104;            /* +0x104 */
    uint8_t unk108[0x278 - 0x108];
    M1Rig109A *rig278;         /* +0x278 */
} M1Step109A;
typedef struct M1Obj109 { uint8_t unk00[0x10]; uint32_t flags10; } M1Obj109;

/* 0x0012F710: aim setup: state 0x25, reset the rig quaternion, aim at the player (+0x104,
 * mode 1), rig flag 2, a 5-degree sway at 22.5 degrees/frame, and spin command 6 at +0x184
 * when positive. */
void m1_Aim12F710(M1Obj109 *o, M1Step109A *h)
{
    M1Rig109A *r = h->rig278;
    M1Rig109A *p;
    M1Cmd109 *c;
    float t;
    if (sub_001456E0(o, h, 0x25, 0) == 1)
        sub_0001D4E0(o);
    p = h->rig278;
    p->q164[2] = 0.0f;
    p->q164[1] = 0.0f;
    p->q164[0] = 0.0f;
    p->q164[3] = 1.0f;
    h->flags4C |= 0x70;
    h->tgt104 = g_playerObj;
    h->mode0F8 = 1;
    r->flags0C |= 2;
    t = m1_frameTime42C858 * 0.392699093f;
    c = sub_00113400(h, 1);
    c->f10 = 0.0872664675f;
    c->f14 = -0.0872664675f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
    if (r->spin184 > 0.0f) {
        o->flags10 |= 4;
        t = r->spin184;
        c = sub_00113400(h, 6);
        if (t != -1.0f)
            c->f10 = t;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        c->f1C = 0.0f;
    }
}

typedef struct M1Rig109B { uint8_t unk00[0x18]; uint32_t flags18; uint8_t unk1C[4]; float q20[4]; uint8_t unk30[0x8C - 0x30]; float f8C; float f90; } M1Rig109B;
typedef struct M1Step109B {
    uint8_t unk000[0x74];
    float   wait74;            /* +0x74 */
    uint8_t unk078[0x278 - 0x78];
    M1Rig109B *rig278;         /* +0x278 */
} M1Step109B;

/* 0x00186F00: rig sway: state 0x21, reset the quaternion, rig +0x8C and wait = 2, +0x90 =
 * 30 * frameRate, pose 3, a 5-degree sway at 5 degrees/frame, plus command 2 = (3, 0, 1, 1)
 * when rig flag 0x2000 is set. */
void m1_RigSway186F00(void *o, M1Step109B *h)
{
    M1Rig109B *r = h->rig278;
    M1Rig109B *p;
    M1Cmd109 *c;
    float t;
    volatile float u;
    sub_001456E0(o, h, 0x21, 0);
    p = h->rig278;
    p->q20[2] = 0.0f;
    p->q20[1] = 0.0f;
    p->q20[0] = 0.0f;
    p->q20[3] = 1.0f;
    r->f8C = 2.0f;
    r->f90 = m1_frameRate42C85C * 30.0f;
    h->wait74 = 2.0f;
    sub_00036750(o, 3);
    t = m1_frameTime42C858 * 0.0872664675f;
    c = sub_00113400(h, 1);
    c->f10 = 0.0872664675f;
    c->f14 = -0.0872664675f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
    if (r->flags18 & 0x2000) {
        u = 1.0f;
        c = sub_00113400(h, 2);
        c->f10 = 3.0f;
        c->f14 = 0.0f;
        c->f18 = 1.0f;
        if (u != -1.0f)
            c->f1C = u;
    }
}

typedef struct M1Step109D {
    uint8_t unk00[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk50[0x58 - 0x50];
    int32_t state58;           /* +0x58 */
    uint8_t unk5C[0x74 - 0x5C];
    float   wait74;            /* +0x74 */
} M1Step109D;
typedef struct M1Obj109D { uint8_t unk00[0x30]; void *anim30; } M1Obj109D;
int  sub_00194EB0(void);
int  sub_000833E0(void *a);
int  sub_00145780(void *o, float frame);
void sub_001151A0(void *h, int v);
void sub_00113480(void *h, int v);
void sub_00117580(void *o, int v);

/* 0x001184C0: guard sequence: latch flag 0x100 from 0x194EB0; wait for the clip, enter state
 * 0x23 with wait 2 and a 2-degree lean, hold (0x1151A0 at frame 1) until the wait runs out or
 * flag 0x100, enter state 0x24 and settle, then finish with 0x117580 when the clip ends. */
void m1_Guard1184C0(M1Obj109D *o, M1Step109D *h)
{
    M1Cmd109 *c;
    float t;
    if (sub_00194EB0())
        h->flags4C |= 0x100;
    switch (h->state58) {
    case 0:
        if (!sub_000833E0(o->anim30))
            return;
        h->state58++;
    case 1:
        if (sub_001456E0(o, h, 0x23, 0) == 1)
            sub_0001D4E0(o);
        h->wait74 = 2.0f;
        t = m1_frameTime42C858 * 0.0349065848f;
        c = sub_00113400(h, 1);
        c->f10 = 0.0349065848f;
        c->f14 = -0.0349065848f;
        if (t != -1.0f)
            c->f18 = t;
        c->f1C = 0.0f;
        h->state58++;
        return;
    case 2:
        if (sub_00145780(o, 1.0f))
            sub_001151A0(h, 1);
        if (0.0f >= h->wait74 || (h->flags4C & 0x100))
            h->state58++;
        return;
    case 3:
        if (sub_001456E0(o, h, 0x24, 0) == 1)
            sub_0001D4E0(o);
        sub_00113480(h, 1);
        h->state58++;
        return;
    case 4:
        if (sub_000833E0(o->anim30))
            sub_00117580(o, 1);
    }
}

typedef struct M1PairK { void *obj00; void *act04; } M1PairK;
typedef struct M1Act109 { uint8_t unk000[0x130]; int32_t i130; } M1Act109;
extern M1PairK m1_pair3FDE68;
extern float m1_v3FDEA4[4];
extern float m1_f3FDEB4;
extern float m1_f3FDED4;
extern uint8_t m1_stats41FEC0[];
int  sub_000F40B0(void);
int  sub_000F6A80(void);
void sub_000C4250(void *s, float *a, float *b);
void sub_000F5D40(float *d, const float *s);
int  m1_AimPoint17D5C0(void *a, void *b, void *c, float *out);
void *sub_00035DD0(void *o, int a, int b, int c);
void sub_00033880(void *fx, float *m);
void sub_00034DD0(void *fx, const float *pos, const float *dir, const float *up);

/* 0x0017D970: aimed shot of the scene actor: unless the game is in state 2 or blocked, find
 * the aim point along the segment at 0x3FDEA4..0x3FDEB4 (0x17D5C0); once the 0x3FDED4 cooldown
 * is used up, fire effect 3 there (height capped at -0.5) and restart the cooldown at 0.5.
 * Returns 1 when fired. */
int m1_ActorShot17D970(void)
{
    struct {
        float pt[4];
        float up[4];
        float v[4];
        float x, y;
        float seg[2][4];
        float m[16];
    } l;
    M1Act109 *s = (M1Act109 *)m1_pair3FDE68.obj00;
    void *fx;
    if (sub_000F40B0() == 2)
        return 0;
    if (sub_000F6A80())
        return 0;
    sub_000C4250(m1_stats41FEC0, l.v, l.pt);
    l.x = l.pt[0];
    l.y = l.pt[1];
    sub_000F5D40(l.seg[0], m1_v3FDEA4);
    sub_000F5D40(l.seg[1], &m1_f3FDEB4);
    if (m1_AimPoint17D5C0(s, l.seg, 0, l.pt) == -1)
        return 0;
    if (!(0.0f >= m1_f3FDED4))
        return 0;
    l.up[0] = 0.0f;
    l.up[1] = 1.0f;
    l.up[2] = 0.0f;
    l.up[3] = 1.0f;
    if (l.pt[1] > -0.5f)
        l.pt[1] = -0.5f;
    fx = sub_00035DD0(s, s->i130, 3, 1);
    sub_00033880(fx, l.m);
    sub_00034DD0(fx, l.pt, &l.m[8], l.up);
    m1_f3FDED4 = 0.5f;
    return 1;
}

typedef struct M1Rig109F { uint32_t flags00; uint8_t unk04[0x50 - 4]; uint8_t b50; } M1Rig109F;
typedef struct M1Step109F {
    uint8_t unk000[0x20];
    uint8_t b20;               /* +0x20 */
    uint8_t unk021[0x4C - 0x21];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x278 - 0x50];
    M1Rig109F *rig278;         /* +0x278 */
} M1Step109F;
typedef struct M1Obj109F { uint8_t unk00[0xC]; uint32_t flags0C; uint32_t flags10; uint8_t unk14[0x60 - 0x14]; float pos60[4]; } M1Obj109F;
typedef struct M1Cmd109F { int32_t kind00; uint8_t unk04[0x10 - 4]; float f10, f14, f18, f1C; } M1Cmd109F;
extern float m1_fps42C964;
void sub_00156180(void *r, float a, float b, float c, float d);
void sub_00189DA0(void *o, void *h, int a);
int  sub_000494D0(int id, const void *pos, int c);

/* 0x00152740: launch up: state 0x37, rise 100 * frameRate (decay 0.003), flags; with rig flag
 * 0x10 also pose 4, sound 0x130, a one-second hold (command 8) and, with the alt flag,
 * command 4 = (20, 2). */
void m1_LaunchUp152740(M1Obj109F *o, M1Step109F *h)
{
    M1Rig109F *r = h->rig278;
    M1Cmd109F *c;
    float t;
    sub_001456E0(o, h, 0x37, 0);
    sub_00156180(r, 0.0f, m1_frameRate42C85C * 100.0f, 0.0f, m1_frameTime42C858 * 0.00300000003f);
    h->flags4C &= ~0x70u;
    o->flags0C &= ~0x20u;
    o->flags10 |= 4;
    r->flags00 |= 0xF;
    if (!(r->b50 & 0x10))
        return;
    sub_00036750(o, 4);
    sub_000494D0(0x130, o->pos60, 0);
    o->flags10 |= 5;
    h->flags4C &= ~0x1000070u;
    t = m1_fps42C964;
    c = (M1Cmd109F *)sub_00113400(h, 8);
    if (t != -1.0f)
        c->f10 = t;
    c->f14 = 0.0f;
    c->f18 = 0.0f;
    c->f1C = 0.0f;
    if (c->kind00 != 0)
        c->kind00 = 2;
    if (h->b20 & 1) {
        c = (M1Cmd109F *)sub_00113400(h, 4);
        c->f10 = 20.0f;
        c->f14 = 2.0f;
        c->f18 = 0.0f;
        c->f1C = 0.0f;
        if (c->kind00 != 0)
            c->kind00 = 2;
    }
}
