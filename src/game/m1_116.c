/* Area m1, file 116. Names inferred. */
#include <stdint.h>

typedef struct M1Rec116 {
    int32_t a00, a04;          /* +0x00 */
    float   f08;               /* +0x08 */
    int32_t a0C;               /* +0x0C */
    uint8_t unk10[4];
    volatile int16_t w14, w16; /* +0x14 */
    float   v18[3];            /* +0x18 */
} M1Rec116;
extern M1Rec116 m1_recs3FDAF8[9];

#define M1_CLR116(i) \
    m1_recs3FDAF8[i].a00 = 0; m1_recs3FDAF8[i].a04 = 0; m1_recs3FDAF8[i].f08 = 0.0f; \
    m1_recs3FDAF8[i].a0C = 0; m1_recs3FDAF8[i].w14 = 0; m1_recs3FDAF8[i].w16 = 0; \
    m1_recs3FDAF8[i].v18[0] = 0.0f; m1_recs3FDAF8[i].v18[1] = 0.0f; m1_recs3FDAF8[i].v18[2] = 0.0f;

/* 0x001799E0: clear the nine 0x24-byte records at 0x3FDAF8. */
void m1_RecsClear1799E0(void)
{
    M1_CLR116(0) M1_CLR116(1) M1_CLR116(2) M1_CLR116(3) M1_CLR116(4)
    M1_CLR116(5) M1_CLR116(6) M1_CLR116(7) M1_CLR116(8)
}

typedef struct M1Look116 { uint8_t unk00[0xD0]; float colD0[4]; } M1Look116;
typedef struct M1Ent116 { uint8_t unk00[0xC]; uint8_t b0C; } M1Ent116;
typedef struct M1Comp116 { uint8_t unk00[0x64]; uint8_t *tbl64; uint8_t unk68[0x80 - 0x68]; int32_t mode80; uint8_t unk84[4]; float t88; uint8_t unk8C[0xD0 - 0x8C]; float fD0, fD4; } M1Comp116;
typedef struct M1Obj116 { uint8_t unk000[0x170]; M1Look116 *look170; } M1Obj116;
extern float m1_frameRate42C85C;
extern uint8_t m1_stats41FEC0[];
M1Comp116 *sub_0001D960(void *o, int kind);
void sub_000F3B30(void *o, int v);
void sub_000F3BB0(void *o, int a, int b);
void sub_00039820(int v);
void sub_000D1CA0(void *s, const float *v);
void sub_000CF330(void *s, const float *v, float k);
void sub_00145620(void *e, const float *v);
void sub_000D9AB0(int id);
void sub_000F3B70(void *o, int v);

/* 0x001065C0: timed mode switch (hangs without an object): when the +0x88 timer runs out,
 * mode 2 sets look 4 and full colour; mode 1 sets look 0xC, full colour, places the player
 * (3, 0, -82) facing 80, launches the four parts held at +0x64 +0x9A8 upward (100) and
 * clears them, then event 3 and pose 4. The timer is then cleared. */
void m1_TimedMode1065C0(M1Obj116 *o)
{
    M1Comp116 *c;
    M1Ent116 *e;
    M1Look116 *p;
    float v[4];
    int off;
    if (o == 0)
        for (;;) ;
    c = sub_0001D960(o, 5);
    c->t88 -= m1_frameRate42C85C;
    if (!(0.0f >= c->t88))
        return;
    switch (c->mode80) {
    case 1:
        sub_000F3B30(o, 0xC);
        sub_000F3BB0(o, 0, 0);
        sub_00039820(2);
        p = o->look170;
        p->colD0[3] = 128.0f;
        p->colD0[2] = 128.0f;
        p->colD0[1] = 128.0f;
        p->colD0[0] = 128.0f;
        c->fD4 = 0.0f;
        c->fD0 = 0.0f;
        v[1] = 0.0f;
        v[2] = -82.0f;
        v[0] = 3.0f;
        v[3] = 1.0f;
        sub_000D1CA0(m1_stats41FEC0, v);
        v[0] = 0.0f;
        v[1] = 0.0f;
        v[2] = 80.0f;
        v[3] = 1.0f;
        sub_000CF330(m1_stats41FEC0, v, 8.0f);
        v[0] = 0.0f;
        v[2] = 0.0f;
        v[1] = 100.0f;
        v[3] = 1.0f;
        for (off = 0x9A8; off < 0x9B8; off += 4) {
            e = *(M1Ent116 **)(c->tbl64 + off);
            if (e) {
                if (e->b0C & 1)
                    sub_00145620(e, v);
                *(M1Ent116 **)(c->tbl64 + off) = 0;
            }
        }
        sub_000D9AB0(3);
        sub_000F3B70(o, 4);
        break;
    case 2:
        sub_000F3B30(o, 4);
        sub_000F3BB0(o, 0, 0);
        sub_00039820(2);
        p = o->look170;
        p->colD0[3] = 128.0f;
        p->colD0[2] = 128.0f;
        p->colD0[1] = 128.0f;
        p->colD0[0] = 128.0f;
        c->fD4 = 0.0f;
        c->fD0 = 0.0f;
        break;
    }
    c->t88 = 0.0f;
}

typedef struct M1Part116 { uint8_t unk000[0x20]; float *m20; uint8_t unk024[0x14C - 0x24]; int32_t i14C; } M1Part116;
typedef struct M1Fly116 { int32_t mode00; uint8_t unk04[4]; float t08; int32_t phase0C; float vx10, vy14, vz18; } M1Fly116;
typedef struct M1Rig116 { uint32_t unk00; uint32_t flags04; } M1Rig116;
typedef struct M1Step116 { uint8_t unk000[0x278]; M1Rig116 *rig278; } M1Step116;
extern float m1_frameTime42C858;
extern void *m1_scene42C8E4;
M1Part116 *sub_0001D2B0(void *o, int part);
void sub_0001D610(void *p);
void sub_00113370(void *h, void *s);
void sub_0001EB80(void *e);
void sub_0001E9B0(void *s, void *e, int a, int b, int c);
void sub_001ADA40(float *d, const float *m);
void sub_001ADBA0(float *d, const float *s, float k);
void sub_001AD7E0(float *out, const float *v);
float sub_001AD9D0(const float *a, const float *b);

/* 0x00114AE0: knock a part off: phase 0 detaches part 2 (rig flag 0x40) and launches it
 * backward on the flat plane at 30 * frameRate and up at -100 * frameRate; phase 1 moves it,
 * damps the horizontal speed by 0.02 * frameTime and adds gravity until 3 s have passed;
 * phase 2 finishes the step. Mode 1 becomes 2 while it runs. */
void m1_PartOff114AE0(void *o, M1Step116 *h, M1Fly116 *s)
{
    float d[4];
    float ax[4];
    float az[4];
    M1Part116 *p;
    ax[0] = 1.0f;
    ax[1] = 0.0f;
    ax[2] = 0.0f;
    ax[3] = 0.0f;
    az[0] = 0.0f;
    az[1] = 0.0f;
    az[2] = 1.0f;
    az[3] = 0.0f;
    p = sub_0001D2B0(o, 2);
    switch (s->phase0C) {
    case 0:
        sub_0001EB80(p);
        sub_0001E9B0(m1_scene42C8E4, p, p->i14C, 5, 0x11);
        sub_001ADA40(p->m20, p->m20 + 16);
        h->rig278->flags04 |= 0x40;
        sub_001ADBA0(d, p->m20 + 8, -1.0f);
        d[1] = 0.0f;
        sub_001AD7E0(d, d);
        sub_001ADBA0(d, d, m1_frameRate42C85C * 30.0f);
        s->vx10 = sub_001AD9D0(ax, d);
        s->vz18 = sub_001AD9D0(az, d);
        s->vy14 = m1_frameRate42C85C * -100.0f;
        s->phase0C++;
        break;
    case 1:
        p->m20[12] = s->vx10 + p->m20[12];
        p->m20[13] = s->vy14 + p->m20[13];
        p->m20[14] += s->vz18;
        s->vx10 = (1.0f - m1_frameTime42C858 * 0.0199999996f) * s->vx10;
        s->vy14 = m1_frameRate42C85C * m1_frameRate42C85C * 294.0f + s->vy14;
        s->vz18 = (1.0f - m1_frameTime42C858 * 0.0199999996f) * s->vz18;
        if (s->t08 >= 3.0f)
            s->phase0C++;
        break;
    case 2:
        sub_0001D610(p);
        if (s->mode00)
            s->mode00 = 1;
        sub_00113370(h, s);
        return;
    }
    if (s->mode00)
        s->mode00 = 2;
}

typedef struct M1Rig116S { uint32_t flags00; float yaw04; uint8_t unk08[4]; float spin0C; } M1Rig116S;
typedef struct M1Step116S {
    uint8_t unk000[0x50];
    int32_t stop50;            /* +0x50 */
    uint8_t unk054[0x64 - 0x54];
    int32_t state64;           /* +0x64 */
    uint8_t unk068[0x6C - 0x68];
    int32_t snd6C;             /* +0x6C */
    uint8_t unk070[0x278 - 0x70];
    M1Rig116S *rig278;         /* +0x278 */
} M1Step116S;
typedef struct M1Obj116S {
    uint8_t unk00[0x20];
    float  *m20;               /* +0x20 */
    uint8_t unk24[0x50 - 0x24];
    float   rx50, ry54, rz58;  /* +0x50 */
    uint8_t unk5C[0x60 - 0x5C];
    float   pos60[4];          /* +0x60 */
    uint8_t unk70[0x80 - 0x70];
    float   vel80[4];          /* +0x80 */
} M1Obj116S;
int  sub_00049700(int id, int r, int g, int b, const void *pos, int a, float size, int c);
void sub_00048250(int h);
void sub_00113090(void *o, void *h, int next);
int  sub_00175290(void *o);
void sub_001AD940(float *m);
void sub_001AD8B0(float *d, const float *s, float a);
void sub_001AD910(float *d, const float *s, float a);
void sub_001AD8E0(float *d, const float *s, float a);
void sub_001AD9B0(float *d, const float *m, const float *v);
void sub_001AE010(float *d, const float *m, const float *v);
void *sub_0001D0F0(void *o, int part);

/* 0x001765C0: spinning top: turn by the rig spin +0x0C (unless flag 0x800), run the looping
 * sound 0x20B while spinning, settle (clip 3) once it stops, clear flag 0x100 via 0x175290,
 * wrap the yaw, build the matrix from pitch, roll and rig yaw +0x04, turn the +0x80 velocity,
 * and (outside state 8) orient part 2 about the point (0, -2, 0). */
void m1_SpinTop1765C0(M1Obj116S *o, M1Step116S *h)
{
    M1Rig116S *r = h->rig278;
    float v[4];
    float m[16];
    if (!(r->flags00 & 0x800))
        o->ry54 = r->spin0C + o->ry54;
    if (r->spin0C != 0.0f && h->snd6C < 0) {
        h->snd6C = sub_00049700(0x20B, 0x80, 0x80, 0x80, o->pos60, 1, 100.0f, 1);
    } else if (h->snd6C >= 0 && (r->spin0C == 0.0f || h->stop50 != 0)) {
        sub_00048250(h->snd6C);
        h->snd6C = -1;
    }
    if (r->spin0C == 0.0f && h->stop50 == 0 && h->state64 != 3)
        sub_00113090(o, h, 3);
    r->spin0C = 0.0f;
    if ((r->flags00 & 0x100) && sub_00175290(o))
        r->flags00 &= ~0x100u;
    if (-3.14159274f > o->ry54)
        o->ry54 += 6.28318548f;
    if (o->ry54 > 3.14159274f)
        o->ry54 -= 6.28318548f;
    v[0] = 0.0f;
    v[2] = 0.0f;
    v[1] = -2.0f;
    v[3] = 1.0f;
    sub_001AD940(m);
    sub_001AD8B0(m, m, o->rx50);
    sub_001AD910(m, m, o->rz58);
    sub_001AD8E0(m, m, r->yaw04);
    sub_001ADA40(o->m20, m);
    sub_001AD940(m);
    sub_001AD8E0(m, m, r->yaw04);
    sub_001AD9B0(o->vel80, m, o->vel80);
    if (h->stop50 != 8) {
        sub_001AD940(m);
        sub_001AE010(m, m, v);
        sub_001AD8B0(m, m, o->rx50);
        sub_001AD8E0(m, m, 0.0f - r->yaw04);
        sub_001AD8E0(m, m, o->ry54);
        sub_001ADA40((float *)sub_0001D0F0(o, 2), m);
    }
}

typedef struct M1Pl116 { uint8_t unk00[0x60]; float pos60[4]; } M1Pl116;
typedef struct M1Shot116 { int32_t id00; uint8_t unk04[8]; } M1Shot116;
typedef struct M1Step116A { uint8_t unk00[0x30]; M1Shot116 *shots30; } M1Step116A;
typedef struct M1Obj116A { uint8_t unk000[0x30]; void *anim30; uint8_t unk034[0x54 - 0x34]; float yaw54; uint8_t unk058[0x60 - 0x58]; float pos60[4]; uint8_t unk070[0x130 - 0x70]; int32_t i130; } M1Obj116A;
typedef struct M1Mode116 { uint8_t unk000[0x324]; int32_t mode324; } M1Mode116;
extern M1Pl116 *g_playerObj;
extern int32_t m1_actState3FE398;
extern float m1_actT3FE394;
extern float m1_actWait3FE39C;
M1Mode116 *sub_000E0770(void);
void sub_00113040(void *o, void *h, int state);
void sub_000832D0(void *a, int v);
void sub_0001D700(void *o);
float sub_000F7B80(void *o, const float *pt, float a);
void sub_000F5ED0(float *a);
int  sub_000F6A80(void);
int  sub_00113870(void *o, void *h, void *tgt, int i, float *out);
int  sub_000D3BF0(void *stats, void *o, int n, const float *tgt, const float *dir);
void *sub_00035DD0(void *o, int a, int b, int c);
void sub_00033880(void *fx, float *m);
void sub_00034E00(void *fx, const float *pos, const float *dir, const float *up);
int  sub_000494D0(int id, const void *pos, int c);
int  sub_000F5D00(void *o);

/* 0x001833F0: scene actor attack (only in scene mode 1, else idle): phase 0 starts the clip,
 * faces the player and turns 30 degrees; phase 1, unless blocked, tries each shot of the step
 * list until one finds the player, and on a hit (cooldown 0x3FE39C over) plays effect 3 with
 * sound 0x1E8 and a 0.5 s cooldown; it goes idle when 0xF5D00 says so. */
void m1_ActorAttack1833F0(M1Obj116A *o, M1Step116A *h)
{
    struct { float d[4]; float up[4]; float tgt[4]; float m[16]; } l;
    void *fx;
    int i;
    if (sub_000E0770()->mode324 != 1) {
        sub_00113040(o, h, 0);
        sub_000832D0(o->anim30, 0);
        sub_0001D700(o);
        return;
    }
    switch (m1_actState3FE398) {
    case 0:
        sub_000832D0(o->anim30, 2);
        sub_0001D610(o);
        sub_000F7B80(o, g_playerObj->pos60, 3.14159274f);
        o->yaw54 += 0.52359879f;
        sub_000F5ED0(&o->yaw54);
        m1_actState3FE398++;
        m1_actT3FE394 = 0.0f;
        break;
    case 1:
        if (!sub_000F6A80()) {
            for (i = 0; h->shots30[i].id00 >= 0; i++) {
                if (sub_00113870(o, h, g_playerObj, i, l.tgt) >= 0) {
                    l.d[0] = g_playerObj->pos60[0] - o->pos60[0];
                    l.d[1] = g_playerObj->pos60[1] - o->pos60[1];
                    l.d[2] = g_playerObj->pos60[2] - o->pos60[2];
                    l.d[3] = g_playerObj->pos60[3];
                    if (sub_000D3BF0(m1_stats41FEC0, o, 0, l.tgt, l.d) != -1 && 0.0f >= m1_actWait3FE39C) {
                        l.up[0] = 0.0f;
                        l.up[1] = 1.0f;
                        l.up[2] = 0.0f;
                        l.up[3] = 1.0f;
                        fx = sub_00035DD0(o, o->i130, 0, 3);
                        sub_00033880(fx, l.m);
                        sub_00034E00(fx, l.tgt, &l.m[8], l.up);
                        sub_000494D0(0x1E8, o->pos60, 1);
                        m1_actWait3FE39C = 0.5f;
                    }
                    break;
                }
            }
        }
        if (sub_000F5D00(o)) {
            sub_00113040(o, h, 0);
            sub_000832D0(o->anim30, 0);
            sub_0001D700(o);
        }
        break;
    }
}
