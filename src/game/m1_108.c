/* Area m1, file 108. Names inferred. */
#include <stdint.h>

typedef struct M1Rig108 { uint8_t unk00[0x38]; void *fx38; uint8_t unk3C[0x50 - 0x3C]; uint32_t flags50; } M1Rig108;
typedef struct M1Step108 {
    uint8_t unk000[0x20];
    uint8_t b20;               /* +0x20 */
    uint8_t unk021;
    uint8_t b22;               /* +0x22 */
    uint8_t unk023[0x4C - 0x23];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x58 - 0x50];
    int32_t state58;           /* +0x58 */
    uint8_t unk05C[0x6C - 0x5C];
    int32_t snd6C;             /* +0x6C */
    void   *fx70;              /* +0x70 */
    float   wait74;            /* +0x74 */
    uint8_t unk078[0x278 - 0x78];
    M1Rig108 *rig278;          /* +0x278 */
} M1Step108;
typedef struct M1Obj108 { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x30 - 0x14]; void *anim30; } M1Obj108;
typedef struct M1Cmd108 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Cmd108;
typedef int (*M1Check108)(void *o, void *h, const void *tbl);
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
int  sub_001456E0(void *o, void *h, int a, int b);
void sub_00156180(void *r, float a, float b, float c, float d);
M1Cmd108 *sub_00113400(void *h, int v);
void sub_0015A490(void *fx, int v);

/* 0x0014BD00: hop setup: state 2 (alt flag, forward 24 * 1.4 * frameRate) or 1 (24 *
 * frameRate) with decay 0.003, flags, a 5-degree sway at 2.4 degrees/frame; a pending
 * flag 0x400 kicks the rig effect with 3. */
void m1_Hop14BD00(M1Obj108 *o, M1Step108 *h)
{
    M1Rig108 *r = h->rig278;
    M1Cmd108 *c;
    float a;
    float t;
    if (h->b20 & 1) {
        sub_001456E0(o, h, 2, 0);
        a = m1_frameRate42C85C * 24.0f * 1.39999998f;
    } else {
        sub_001456E0(o, h, 1, 0);
        a = m1_frameRate42C85C * 24.0f;
    }
    sub_00156180(r, a, 0.0f, 0.0f, m1_frameTime42C858 * 0.00300000003f);
    o->flags10 |= 0x20;
    h->flags4C |= 0x70;
    t = m1_frameTime42C858 * 0.0418879054f;
    c = sub_00113400(h, 1);
    c->f10 = 0.0872664675f;
    c->f14 = -0.0872664675f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
    if (r->flags50 & 0x400) {
        r->flags50 &= ~0x400u;
        sub_0015A490(r->fx38, 3);
    }
}

typedef struct M1V4 { float x, y, z, w; } M1V4;
typedef struct M1Rec108 { int16_t state00; uint8_t unk02[0xC - 2]; M1V4 vel0C; M1V4 acc1C; } M1Rec108;
typedef struct M1Step108R { uint8_t unk00[0x74]; M1Rec108 *rec74; } M1Step108R;
typedef struct M1Obj108R {
    uint8_t unk00[0x54];
    float   yaw54;             /* +0x54 */
    uint8_t unk58[0x60 - 0x58];
    M1V4    pos60;             /* +0x60 */
    float   size70;            /* +0x70 */
    uint8_t unk74[0xA4 - 0x74];
    float   fA4;               /* +0xA4 */
    uint8_t unkA8[0xB0 - 0xA8];
    float   fB0, fB4;          /* +0xB0 */
    uint8_t unkB8[0xE8 - 0xB8];
    float   fE8;               /* +0xE8 */
} M1Obj108R;
void sub_001ADB60(float *d, const float *s, float k);

/* 0x0018E100: flying record step: in state 2 spin (37.7 * frameRate), move by velocity and
 * accelerate (both scaled by frameRate); then sizes from +0x70 (2.5, -2, 1, 4 times). */
void m1_FlyStep18E100(M1Obj108R *o, M1Step108R *h)
{
    M1Rec108 *e = h->rec74;
    float t[4];
    M1V4 p;
    if (e->state00 == 2) {
        o->yaw54 -= m1_frameRate42C85C * 37.6991119f;
        sub_001ADB60(t, &e->vel0C.x, m1_frameRate42C85C);
        p = o->pos60;
        p.x += t[0];
        p.y += t[1];
        p.z += t[2];
        o->pos60 = p;
        sub_001ADB60(t, &e->acc1C.x, m1_frameRate42C85C);
        p = e->vel0C;
        p.x += t[0];
        p.y += t[1];
        p.z += t[2];
        e->vel0C = p;
    }
    o->fB0 = o->size70 * 2.5f;
    o->fB4 = o->size70 * -2.0f;
    o->fA4 = o->fB4 * -0.5f;
    o->fE8 = o->size70 * 4.0f;
}

typedef struct M1Mdl108 { uint8_t unk00[0x40]; float m40[16]; struct M1Mdl108 *parent80; uint8_t unk84[0x90 - 0x84]; uint32_t flags90; } M1Mdl108;
typedef struct M1Step108F {
    uint8_t unk00[0x58];
    int32_t state58;           /* +0x58 */
    uint8_t unk5C[0x74 - 0x5C];
    float   t74;               /* +0x74 */
    uint8_t unk78[4];
    float   wait7C;            /* +0x7C */
} M1Step108F;
typedef struct M1Obj108F { uint8_t unk000[0xC]; uint32_t flags0C; uint8_t unk010[0x128 - 0x10]; uint8_t b128; } M1Obj108F;
extern void *m1_scene42C8E4;
M1Mdl108 *sub_0001D0F0(void *o, int a);
void sub_001AD940(float *m);
void sub_001AD8B0(float *d, const float *s, float a);
void sub_001AD7C0(float *d, const float *a, const float *b);
void sub_0001EB80(void *o);
void sub_0001E9B0(void *s, void *o, int a, int b, int c);
int  sub_00036750(void *o, int v);
void sub_000EE6D0(void *o, float t);
int  sub_000ED780(void *o);

/* 0x0017BD70: falling prop: phase 0 waits for +0x7C, then shows it; phase 1 tips the model
 * over by 30 degrees/second until it touches (o +0x128 bits 0x18), then settles it (pose 1,
 * timer 1); phase 2 fades it out and removes it when the timer runs out. */
void m1_PropFall17BD70(M1Obj108F *o, M1Step108F *h)
{
    float m[16];
    M1Mdl108 *d;
    switch (h->state58) {
    case 0:
        if (h->wait7C >= 0.0f) {
            o->flags0C |= 0x80;
            h->state58++;
        }
    case 1:
        d = sub_0001D0F0(o, 0);
        if (!(o->b128 & 0x18)) {
            sub_001AD940(m);
            sub_001AD8B0(m, m, 0.0f - m1_frameTime42C858 * 0.52359879f);
            sub_001AD7C0((float *)d, m, (float *)d);
            sub_001AD7C0(d->m40, d->parent80->m40, (float *)d);
            return;
        }
        d->flags90 &= ~0x40u;
        sub_0001EB80(o);
        sub_0001E9B0(m1_scene42C8E4, o, 0xE, 5, 0x11);
        sub_00036750(o, 1);
        h->t74 = 1.0f;
        h->state58++;
        return;
    case 2:
        sub_000EE6D0(o, h->t74);
        if (0.0f >= h->t74)
            sub_000ED780(o);
    }
}

typedef struct M1Ctl108 {
    uint8_t unk000[0x94];
    void   *mdl94;             /* +0x94 */
    uint8_t unk098[4];
    int32_t n9C;               /* +0x9C */
    uint8_t unk0A0[0xB0 - 0xA0];
    int16_t armB0;             /* +0xB0 */
    uint8_t unk0B2[0x134 - 0xB2];
    int32_t snd134;            /* +0x134 */
    uint8_t unk138[0x1C4 - 0x138];
    struct M1Ent108 { uint8_t unk00[0x60]; float pos60[4]; } *ent1C4;  /* +0x1C4 */
    uint8_t unk1C8[0x1D0 - 0x1C8];
    int16_t w1D0;              /* +0x1D0 */
} M1Ctl108;
typedef struct M1Step108C { uint8_t unk00[0x68]; float t68; } M1Step108C;
extern M1Ctl108 *m1_ctl3F6128;
extern void *g_playerObj;
float sub_000F7C40(void *o, void *tgt, float k);
void sub_0001D610(void *m);
void sub_0001D700(void *m);
struct M1Ent108 *sub_000ED630(int a, int b, const float *pos, int c, int i);
void sub_00048250(int h);
int  sub_000494D0(int id, const void *pos, int c);
void sub_000F3D10(void *o, void *c, int mode);
int  sub_000F5D00(void *o);

/* 0x00100AD0: boss intro step: turn toward the player, start the model at 3% of the clip,
 * at 90% (when armed) spawn the kind (5, 9) entity with sound 0x151 (else switch to 0x24),
 * and switch to 0x22 when 0xF5D00 says so or +0x1D0 is set. */
void m1_IntroStep100AD0(void *o, M1Step108C *h)
{
    M1Ctl108 *g = m1_ctl3F6128;
    struct M1Ent108 *e;
    sub_000F7C40(o, g_playerObj, m1_frameTime42C858 * 0.0785398185f);
    if (g->n9C == 0 && h->t68 > 0.0333000012f) {
        sub_0001D610(g->mdl94);
        g->n9C++;
    }
    if (g->armB0 != 0 && h->t68 > 0.899999976f) {
        sub_0001D700(g->mdl94);
        e = sub_000ED630(5, 9, 0, 0, 0);
        g->ent1C4 = e;
        if (e) {
            if (g->snd134 != -1) {
                sub_00048250(g->snd134);
                g->snd134 = -1;
            }
            g->snd134 = sub_000494D0(0x151, g->ent1C4->pos60, 1);
            g->armB0 = 0;
        } else {
            sub_000F3D10(o, h, 0x24);
        }
    }
    if (sub_000F5D00(o) != 0 || g->w1D0 != 0)
        sub_000F3D10(o, h, 0x22);
}

typedef struct M1Node108 { uint8_t unk00[0x20]; uint8_t *mtx20; uint8_t unk24[0x54 - 0x24]; float yaw54; } M1Node108;
typedef struct M1Rec108B { M1Node108 *node00; uint8_t unk04[0x24 - 4]; float off24[4]; uint8_t unk34[0x58 - 0x34]; } M1Rec108B;
extern M1Rec108B m1_recs3FE0C0[3];
extern uint8_t m1_pt32B808[];
void *sub_000A42A0(int id);
float sub_000F7720(void *o, const void *pt);
void sub_001AD8E0(float *d, const float *s, float a);
void sub_001ADAF0(float *d, const float *a, const float *b);
void sub_001ADA40(float *d, const float *m);
void sub_000F5D40(float *d, const float *s);

/* 0x0017F860: turret turn: turn the base node toward point 0x32B808 by at most 0.4 degrees per
 * frame, rebuild its matrix, and attach the two follower nodes at parts 2..4 of model 0x15
 * plus their offsets. */
void m1_TurretTurn17F860(void)
{
    float lim = m1_frameTime42C858 * 0.00698131742f;
    M1Node108 *e = m1_recs3FE0C0[0].node00;
    float *m;
    float *n;
    void *a = sub_000A42A0(0x15);
    float s = sub_000F7720(e, m1_pt32B808);
    if (s > lim)
        s = lim;
    else if (0.0f - lim > s)
        s = 0.0f - lim;
    m = (float *)(e->mtx20 + 0x40);
    e->yaw54 += s;
    sub_001AD940(m);
    sub_001AD8E0(m, m, e->yaw54);
    sub_000F5D40(m + 12, (float *)((uint8_t *)sub_0001D0F0(a, 2) + 0x70));
    sub_001ADAF0(m + 12, m + 12, m1_recs3FE0C0[0].off24);
    n = (float *)(m1_recs3FE0C0[1].node00->mtx20 + 0x40);
    sub_001ADA40(n, (float *)(e->mtx20 + 0x40));
    sub_000F5D40(n + 12, (float *)((uint8_t *)sub_0001D0F0(a, 3) + 0x70));
    sub_001ADAF0(n + 12, n + 12, m1_recs3FE0C0[1].off24);
    n = (float *)(m1_recs3FE0C0[2].node00->mtx20 + 0x40);
    sub_001ADA40(n, (float *)(e->mtx20 + 0x40));
    sub_000F5D40(n + 12, (float *)((uint8_t *)sub_0001D0F0(a, 4) + 0x70));
    sub_001ADAF0(n + 12, n + 12, m1_recs3FE0C0[2].off24);
}

typedef struct M1Rig108S {
    uint32_t unk00;
    float   f04, f08, f0C, f10;  /* +0x04 */
    uint8_t unk14[0x24 - 0x14];
    float   f24, f28, f2C, f30;  /* +0x24 */
    uint8_t unk34[0x40 - 0x34];
    uint32_t flags40;          /* +0x40 */
    uint8_t unk44[0x54 - 0x44];
    float   f54;               /* +0x54 */
} M1Rig108S;
typedef struct M1Step108S {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x278 - 0x50];
    M1Rig108S *rig278;         /* +0x278 */
} M1Step108S;

/* 0x00157130: spin-back setup: state 0x15, rig motion (spin -3, -15, 10 * frameRate, decay
 * 0.005), +0x54 += 100 clamped to 0..200, flags, and a +-10 degree sway at 2 degrees/frame. */
void m1_SpinBack157130(void *o, M1Step108S *h)
{
    M1Rig108S *r = h->rig278;
    M1Rig108S *p;
    M1Cmd108 *c;
    float v;
    float t;
    sub_001456E0(o, h, 0x15, 0);
    r->f0C = m1_frameTime42C858 * 0.00499999989f;
    r->f30 = 1.0f;
    r->f2C = 0.0f - m1_frameRate42C85C * 3.0f;
    r->f28 = 0.0f;
    r->f24 = 0.0f;
    r->f10 = 0.0f;
    r->f08 = m1_frameRate42C85C * 10.0f;
    r->f04 = -15.0f;
    p = h->rig278;
    v = p->f54 + 100.0f;
    p->f54 = v;
    if (0.0f > v)
        p->f54 = 0.0f;
    else if (v > 200.0f)
        p->f54 = 200.0f;
    h->flags4C &= ~0x70u;
    r->flags40 |= 0x80;
    t = m1_frameTime42C858 * 0.0349065848f;
    c = sub_00113400(h, 1);
    c->f10 = 0.174532935f;
    c->f14 = -0.174532935f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
}

typedef struct M1Rig108K { uint8_t unk00[0x68]; float f68; } M1Rig108K;
typedef struct M1Step108K {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x278 - 0x50];
    M1Rig108K *rig278;         /* +0x278 */
} M1Step108K;
typedef struct M1Obj108K { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x60 - 0x14]; float pos60[4]; } M1Obj108K;
void sub_001561D0(void *r, float a, float b);
int  sub_001C7EE1(void);

/* 0x00149510: hit-back setup: state 0x10, rig motion (5 * frameRate, decay 0.003), rise
 * (-8, 10 * frameRate), +0x68 += 120 clamped to 0..200, a +-30 degree sway (command 2) at
 * 2 degrees/frame, and a one-in-four grunt (sound 0x12A). */
void m1_HitBack149510(M1Obj108K *o, M1Step108K *h)
{
    M1Rig108K *r = h->rig278;
    M1Rig108K *p;
    M1Cmd108 *c;
    float v;
    float t;
    sub_001456E0(o, h, 0x10, 0);
    sub_00156180(r, m1_frameRate42C85C * 5.0f, 0.0f, 0.0f, m1_frameTime42C858 * 0.00300000003f);
    sub_001561D0(r, -8.0f, m1_frameRate42C85C * 10.0f);
    o->flags10 |= 0x20;
    h->flags4C &= ~0x70u;
    p = h->rig278;
    v = p->f68 + 120.0f;
    p->f68 = v;
    if (0.0f > v)
        p->f68 = 0.0f;
    else if (v > 200.0f)
        p->f68 = 200.0f;
    t = m1_frameTime42C858 * 0.0349065848f;
    c = sub_00113400(h, 2);
    c->f10 = 0.52359879f;
    c->f14 = -0.52359879f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
    if (!(sub_001C7EE1() & 3))
        sub_000494D0(0x12A, o->pos60, 0);
}

typedef struct M1Rig108A { uint8_t unk00[0xC]; uint32_t flags0C; } M1Rig108A;
typedef struct M1Step108A { uint8_t unk000[0x278]; M1Rig108A *rig278; } M1Step108A;
int  sub_00145780(void *o, float frame);
void sub_00113480(void *h, int v);
void sub_00131310(int next);
int  sub_000833E0(void *a);

/* 0x001327A0: sway at frame 12 (5 degrees at 5.6 degrees/frame), settle at frame 28, and when
 * the clip ends go to step 1 (flags 1 and 0x200), 3 (flag 1) or 5. */
void m1_SwayStep1327A0(M1Obj108 *o, M1Step108A *h)
{
    M1Rig108A *r = h->rig278;
    M1Cmd108 *c;
    uint32_t f;
    float t;
    if (sub_00145780(o, 12.0f)) {
        t = m1_frameTime42C858 * 0.0981747732f;
        c = sub_00113400(h, 1);
        c->f10 = 0.0872664675f;
        c->f14 = -0.0872664675f;
        if (t != -1.0f)
            c->f18 = t;
        c->f1C = 0.0f;
    } else if (sub_00145780(o, 28.0f)) {
        sub_00113480(h, 1);
    }
    if (!sub_000833E0(o->anim30))
        return;
    f = r->flags0C;
    if (f & 1) {
        if (f & 0x200) {
            sub_00131310(1);
            return;
        }
        sub_00131310(3);
        return;
    }
    sub_00131310(5);
}
