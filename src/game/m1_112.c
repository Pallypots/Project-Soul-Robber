/* Area m1, file 112. Names inferred. */
#include <stdint.h>

typedef struct M1Pl112 { uint8_t unk00[0x60]; float pos60[4]; } M1Pl112;
extern M1Pl112 *g_playerObj;
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
void sub_00113040(void *o, void *h, int state);

typedef struct M1Rig112T { uint32_t flags00; } M1Rig112T;
typedef struct M1Step112T {
    uint8_t unk000[0x58];
    int32_t mode58;            /* +0x58 */
    uint8_t unk05C[0x74 - 0x5C];
    float   wait74;            /* +0x74 */
    uint8_t unk078[0x278 - 0x78];
    M1Rig112T *rig278;         /* +0x278 */
} M1Step112T;
typedef struct M1Obj112T { uint8_t unk00[0x54]; float yaw54; uint8_t unk58[0x60 - 0x58]; float pos60[4]; } M1Obj112T;
float sub_001B2770(const float *a, const float *b);
float sub_00113290(void *o, const float *pos);

/* 0x00177B80: watch the player: per mode +0x58 (0: reach 80, turn 0.4 degrees/frame; 1:
 * reach 160, turn 0.8), once the wait is over attack (state 1) when the player is in reach
 * and within 15 degrees; otherwise turn toward the player (rig flag 0x800) when more than
 * 5 degrees off. */
void m1_Watch177B80(M1Obj112T *o, M1Step112T *h)
{
    M1Rig112T *r = h->rig278;
    float tbl[2][3];
    float d = sub_001B2770(o->pos60, g_playerObj->pos60);
    float a = sub_00113290(o, g_playerObj->pos60);
    tbl[0][0] = 80.0f;
    tbl[0][1] = 100.0f;
    tbl[1][2] = m1_frameTime42C858 * 0.0139626348f;
    tbl[0][2] = m1_frameTime42C858 * 0.00698131742f;
    tbl[1][0] = 160.0f;
    tbl[1][1] = 160.0f;
    if (0.0f > h->wait74 && tbl[h->mode58][0] > d && 0.261799395f > a && a > -0.261799395f) {
        sub_00113040(o, h, 1);
        return;
    }
    if (a > 0.0872664675f)
        o->yaw54 = tbl[h->mode58][2] + o->yaw54;
    else if (-0.0872664675f > a)
        o->yaw54 -= tbl[h->mode58][2];
    else
        return;
    r->flags00 |= 0x800;
}

typedef struct M1Shot112 { uint8_t unk00[0x10]; int32_t n10; } M1Shot112;
extern uint8_t m1_stats41FEC0[];
int  sub_00113670(void *o, void *h, int n, float *tgt);
void sub_001AD9F0(float *out, const float *a, const float *b);
int  sub_000D3BF0(void *stats, void *o, int n, const float *tgt, const float *dir);
int  sub_000494D0(int id, const void *pos, int c);
void *sub_00035D80(void *o, int a, int b);
void sub_00034E00(void *fx, const float *pos, const float *dir, const float *up);

/* 0x0017A180: double shot: shot +0x10 toward the player (on a hit, sound 0x190 and effect
 * (1, 3) with up = (0, 1, 0)), then shot +0x10 + 1 the same way without effects. */
void m1_DoubleShot17A180(M1Pl112 *o, void *h, M1Shot112 *s)
{
    struct { float d[4]; float up[4]; float tgt[4]; } l;
    int n;
    n = sub_00113670(o, h, s->n10, l.tgt);
    sub_001AD9F0(l.d, g_playerObj->pos60, o->pos60);
    l.d[3] = 1.0f;
    if (n >= 0 && sub_000D3BF0(m1_stats41FEC0, o, s->n10, l.tgt, l.d) == 1) {
        l.up[0] = 0.0f;
        l.up[1] = 1.0f;
        l.up[2] = 0.0f;
        l.up[3] = 1.0f;
        sub_000494D0(0x190, o->pos60, 0);
        sub_00034E00(sub_00035D80(o, 1, 3), l.tgt, l.d, l.up);
    }
    n = sub_00113670(o, h, s->n10 + 1, l.tgt);
    sub_001AD9F0(l.d, g_playerObj->pos60, o->pos60);
    l.d[3] = 1.0f;
    if (n >= 0)
        sub_000D3BF0(m1_stats41FEC0, o, s->n10 + 1, l.tgt, l.d);
}

typedef struct M1Comp112 { uint8_t unk00[0xE4]; int32_t sndE4; } M1Comp112;
typedef struct M1Step112D {
    uint8_t unk000[0x150];
    int32_t mode150;           /* +0x150 */
    uint8_t unk154[0x15C - 0x154];
    float   v15C[4];           /* +0x15C */
    uint8_t unk16C[0x188 - 0x16C];
    int32_t band188;           /* +0x188 */
} M1Step112D;
M1Comp112 *sub_0001D960(void *o, int kind);
void sub_000F3DA0(void *o, int a, int b, int c);
void sub_000F3F00(void *o, float k);

/* 0x00110600: zero the +0x15C velocity, hang without an object, sort the flat distance to the
 * player into bands 0..3 (50, 90, 130), start looping sound 0x1AA once, set mode 1 on the
 * object and slow it to 0.75 in modes 1/2. */
void m1_NearBand110600(M1Pl112 *o, M1Step112D *h)
{
    M1Comp112 *c;
    float dx, dz, d2;
    int band;
    h->v15C[0] = m1_frameRate42C85C * 0.0f;
    h->v15C[1] = m1_frameRate42C85C * 0.0f;
    h->v15C[2] = m1_frameRate42C85C * 0.0f;
    h->v15C[3] = m1_frameRate42C85C * 0.0f;
    if (o == 0)
        for (;;) ;
    dx = o->pos60[0] - g_playerObj->pos60[0];
    dz = o->pos60[2] - g_playerObj->pos60[2];
    d2 = dz * dz + dx * dx;
    if (2500.0f > d2)
        band = 0;
    else if (8100.0f > d2)
        band = 1;
    else if (16900.0f > d2)
        band = 2;
    else
        band = 3;
    h->band188 = band;
    c = sub_0001D960(o, 5);
    if (c->sndE4 < 0)
        c->sndE4 = sub_000494D0(0x1AA, o->pos60, 1);
    sub_000F3DA0(o, 1, 0, 0);
    if (h->mode150 == 1 || h->mode150 == 2)
        sub_000F3F00(o, 0.75f);
}

/* 0x001758B0: watch the player (as 0x177B80 with reach 60 / 180 and rig flag 0x800 cleared when
 * no turn is needed). */
void m1_Watch1758B0(M1Obj112T *o, M1Step112T *h)
{
    M1Rig112T *r = h->rig278;
    float tbl[2][3];
    float d = sub_001B2770(o->pos60, g_playerObj->pos60);
    float a = sub_00113290(o, g_playerObj->pos60);
    tbl[0][0] = 60.0f;
    tbl[0][1] = 100.0f;
    tbl[0][2] = m1_frameTime42C858 * 0.00698131742f;
    tbl[1][2] = m1_frameTime42C858 * 0.0139626348f;
    tbl[1][0] = 180.0f;
    tbl[1][1] = 160.0f;
    if (0.0f > h->wait74 && tbl[h->mode58][0] > d && 0.261799395f > a && a > -0.261799395f) {
        sub_00113040(o, h, 1);
        return;
    }
    if (a > 0.0872664675f) {
        o->yaw54 = tbl[h->mode58][2] + o->yaw54;
        r->flags00 |= 0x800;
    } else if (-0.0872664675f > a) {
        o->yaw54 -= tbl[h->mode58][2];
        r->flags00 |= 0x800;
    } else {
        r->flags00 &= ~0x800u;
    }
}

typedef struct M1Rig112S { uint32_t flags00; } M1Rig112S;
typedef struct M1Step112S {
    uint8_t unk000[0x50];
    int32_t stop50;            /* +0x50 */
    uint8_t unk054[0x6C - 0x54];
    int32_t snd6C;             /* +0x6C */
    uint8_t unk070[0x278 - 0x70];
    M1Rig112S *rig278;         /* +0x278 */
} M1Step112S;
typedef struct M1Obj112S {
    uint8_t unk00[0x20];
    float  *m20;               /* +0x20 */
    uint8_t unk24[0x50 - 0x24];
    float   rx50, ry54, rz58;  /* +0x50 */
    uint8_t unk5C[0x60 - 0x5C];
    float   pos60[4];          /* +0x60 */
    uint8_t unk70[0x80 - 0x70];
    float   vel80[4];          /* +0x80 */
} M1Obj112S;
int  sub_00049700(int id, int r, int g, int b, const void *pos, int a, float size, int c);
void sub_00048250(int h);
int  sub_00175290(void *o);
void sub_001AD940(float *m);
void sub_001AD8B0(float *d, const float *s, float a);
void sub_001AD910(float *d, const float *s, float a);
void sub_001AD8E0(float *d, const float *s, float a);
void sub_001ADA40(float *d, const float *m);
void sub_001AD9B0(float *d, const float *m, const float *v);

/* 0x00177840: spinning object: start the looping sound 0x20B when rig flag 0x800 asks for it,
 * stop it when the flag is gone or +0x50 is set (flag cleared either way), clear flag 0x200
 * once 0x175290 agrees, wrap the yaw, rebuild the matrix from the three angles and turn the
 * +0x80 velocity by the yaw. */
void m1_Spin177840(M1Obj112S *o, M1Step112S *h)
{
    M1Rig112S *r = h->rig278;
    float m[16];
    uint32_t f = r->flags00 & 0x800;
    if (f && h->snd6C < 0) {
        h->snd6C = sub_00049700(0x20B, 0x80, 0x80, 0x80, o->pos60, 1, 100.0f, 1);
        r->flags00 &= ~0x800u;
    } else if (h->snd6C >= 0 && (!f || h->stop50 != 0)) {
        sub_00048250(h->snd6C);
        h->snd6C = -1;
        r->flags00 &= ~0x800u;
    }
    if ((r->flags00 & 0x200) && sub_00175290(o))
        r->flags00 &= ~0x200u;
    if (-3.14159274f > o->ry54)
        o->ry54 += 6.28318548f;
    if (o->ry54 > 3.14159274f)
        o->ry54 -= 6.28318548f;
    sub_001AD940(m);
    sub_001AD8B0(m, m, o->rx50);
    sub_001AD910(m, m, o->rz58);
    sub_001AD8E0(m, m, o->ry54);
    sub_001ADA40(o->m20, m);
    sub_001AD940(m);
    sub_001AD8E0(m, m, o->ry54);
    sub_001AD9B0(o->vel80, m, o->vel80);
}
