/* Area m1, file 115. Names inferred. */
#include <stdint.h>

typedef struct M1Pl115 { uint8_t unk00[0x60]; float pos60[4]; } M1Pl115;
typedef struct M1Rig115 {
    uint8_t unk00[0x3C];
    void   *path3C;            /* +0x3C */
    uint8_t unk40[0x50 - 0x40];
    uint32_t flags50;          /* +0x50 */
    uint8_t unk54[0x5C - 0x54];
    float   t5C;               /* +0x5C */
    float   air60;             /* +0x60 */
    uint8_t unk64[0x70 - 0x64];
    float   t70;               /* +0x70 */
    uint8_t unk74[0x78 - 0x74];
    float   v78[4];            /* +0x78 */
} M1Rig115;
typedef struct M1Step115 {
    uint8_t unk000[0x50];
    int32_t state50;           /* +0x50 */
    uint8_t unk054[0xF8 - 0x54];
    int32_t mode0F8;           /* +0xF8 */
    uint8_t unk0FC[0x104 - 0xFC];
    M1Pl115 *tgt104;           /* +0x104 */
    uint8_t unk108[0x278 - 0x108];
    M1Rig115 *rig278;          /* +0x278 */
} M1Step115;
typedef struct M1Obj115 { uint8_t unk000[0x20]; float *m20; uint8_t unk024[0x60 - 0x24]; float pos60[4]; uint8_t unk070[0x128 - 0x70]; uint8_t b128; } M1Obj115;
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
void sub_001AD7E0(float *out, const float *v);
void sub_001ADA60(float *out, const float *a, const float *b);
void sub_00145F70(void *node, const void *src);
void sub_00166200(void *p, const void *pos, int a);
void sub_00166750(void *p);
void sub_00166260(void *p, float *out, int a);
int  sub_001662C0(void *p, int f);
void sub_001560B0(void *o, void *h, void *r);
int  sub_00036750(void *o, int v);

/* 0x001465C0: path walker step: re-orthonormalise the matrix in state 0x2E (else upright it),
 * feed the target (mode 1: its position, mode 2: the target slot) and the object position to
 * the path, read the heading into +0x78, track flag 0x800 from the path, run 0x1560B0, count
 * air time (max 10), count down +0x5C in state 0xD, and when +0x70 runs out (flag 0x200000)
 * restart it at 1 with pose 7. */
void m1_PathStep1465C0(M1Obj115 *o, M1Step115 *h)
{
    M1Rig115 *r = h->rig278;
    float v;
    if (h->state50 == 0x2E) {
        sub_001AD7E0(o->m20, o->m20);
        sub_001AD7E0(o->m20 + 4, o->m20 + 4);
        sub_001ADA60(o->m20 + 8, o->m20, o->m20 + 4);
        sub_001ADA60(o->m20, o->m20 + 4, o->m20 + 8);
    } else {
        sub_00145F70(o->m20, o->m20);
    }
    if (h->mode0F8 == 1)
        sub_00166200(r->path3C, h->tgt104->pos60, 0);
    else if (h->mode0F8 == 2)
        sub_00166200(r->path3C, &h->tgt104, 0);
    sub_00166200(r->path3C, o->pos60, 2);
    sub_00166750(r->path3C);
    sub_00166260(r->path3C, r->v78, 1);
    if (sub_001662C0(r->path3C, 0x10000) == 1)
        r->flags50 |= 0x800;
    else
        r->flags50 &= ~0x800u;
    sub_001560B0(o, h, r);
    if (o->b128 & 6) {
        v = m1_frameRate42C85C + r->air60;
        r->air60 = v;
        if (v > 10.0f)
            r->air60 = 10.0f;
    } else {
        r->air60 = 0.0f;
    }
    if (h->state50 == 0xD) {
        v = r->t5C - m1_frameTime42C858;
        r->t5C = v;
        if (0.0f > v)
            r->t5C = 0.0f;
    }
    if (r->flags50 & 0x200000) {
        v = r->t70 - m1_frameRate42C85C;
        r->t70 = v;
        if (0.0f >= v) {
            r->t70 = 1.0f;
            sub_00036750(o, 7);
        }
    }
}

typedef struct M1Rig115G { uint8_t unk00[8]; float t08; uint8_t unk0C[0x16 - 0xC]; int16_t landed16; uint8_t unk18[0x20 - 0x18]; float wait20; } M1Rig115G;
typedef struct M1Step115G { uint8_t unk000[0x278]; M1Rig115G *rig278; } M1Step115G;
typedef struct M1Obj115G { uint8_t unk000[0x30]; struct { uint8_t unk00[8]; int32_t i08; } *anim30; uint8_t unk034[0x54 - 0x34]; float yaw54; uint8_t unk058[0x60 - 0x58]; float pos60[4]; uint8_t unk070[0x130 - 0x70]; int32_t i130; } M1Obj115G;
extern const float m1_off32B3A4[4];
void sub_001AD940(float *m);
void sub_001AD8E0(float *d, const float *s, float a);
void sub_001AD9B0(float *d, const float *m, const float *v);
void sub_001ADAF0(float *d, const float *a, const float *b);
int  sub_000F61D0(void *o, const float *pos, int a, float *out);
void *sub_00035DD0(void *o, int a, int b, int c);
void sub_00033880(void *fx, float *m);
void sub_00034DD0(void *fx, const float *pos, const float *dir, const float *up);
int  sub_000F5D00(void *o);
void sub_000832D0(void *a, int v);
void sub_00113040(void *o, void *h, int state);

/* 0x00179590: slam until landing: find the ground under the yaw-rotated offset 0x32B3A4 from
 * the object; until landed, when the 0.5 s cooldown allows, put the dust effect there, and
 * mark it landed on a solid hit; on 0xF5D00 leave (state 3 once landed, else reset the clip);
 * leave to state 4 after 6 frames, counting +0x08. */
void m1_SlamStep179590(M1Obj115G *o, M1Step115G *h)
{
    struct { float up[4]; float pt[4]; float k20; float hit[4]; float off[4]; float m[16]; float m2[16]; } l;
    M1Rig115G *r = h->rig278;
    void *fx;
    int n;
    sub_001AD940(l.m);
    sub_001AD8E0(l.m, l.m, o->yaw54);
    sub_001AD9B0(l.off, l.m, m1_off32B3A4);
    sub_001ADAF0(l.pt, o->pos60, l.off);
    l.k20 = 27.0f;
    if (r->landed16 == 0) {
        n = sub_000F61D0(o, l.pt, 0, l.hit);
        if (n != -1) {
            if (0.0f >= r->wait20) {
                l.up[0] = 0.0f;
                l.up[1] = 1.0f;
                l.up[2] = 0.0f;
                l.up[3] = 1.0f;
                fx = sub_00035DD0(o, o->i130, 0, 1);
                sub_00033880(fx, l.m2);
                sub_00034DD0(fx, l.hit, &l.m2[8], l.up);
                r->wait20 = 0.5f;
            }
            if (n == 1)
                r->landed16 = (int16_t)n;
        }
    }
    if (sub_000F5D00(o)) {
        if (r->landed16 != 0) {
            sub_00113040(o, h, 3);
            return;
        }
        o->anim30->i08 = -1;
        sub_000832D0(o->anim30, 6);
    }
    if (r->t08 > 6.0f) {
        sub_00113040(o, h, 4);
        return;
    }
    r->t08 += m1_frameRate42C85C;
}

typedef struct M1Tgt115 { uint8_t unk00[0xC]; uint8_t b0C; uint8_t unk0D[0x60 - 0xD]; float pos60[4]; } M1Tgt115;
typedef struct M1Rec115C { uint32_t flags00; float f04; uint8_t unk08[0x40 - 8]; M1Tgt115 *tgt40; uint8_t unk44[0x5C - 0x44]; void *fx5C; } M1Rec115C;
typedef struct M1Step115C { uint8_t unk00[0x54]; int32_t state54; uint8_t unk58[0x5C - 0x58]; float t5C; uint8_t unk60[0x74 - 0x60]; M1Rec115C *rec74; } M1Step115C;
typedef struct M1Obj115C { uint8_t unk000[0x60]; float pos60[4]; uint8_t unk070[0x128 - 0x70]; uint8_t b128; } M1Obj115C;
float sub_001B2770(const float *a, const float *b);
void sub_00033AC0(void *fx);
void sub_00033AB0(void *fx);
void sub_001671D0(void *o, void *h, int next);
int  sub_001C7EE1(void);

/* 0x00168950: chase: phase 0 clears flags (lock 0x40000000 when the target is within 40),
 * waits 0.5 and starts effect pose 4; phase 1 after the wait sets flag 4, speed 7 and a random
 * 0.5..3.4 s wait; phase 2 locks on within 40 (restarting the effect), drops a lost target
 * (state 5), toggles flag 0x200 on the ground, and attacks (state 3) within 15 once the wait
 * is over. */
void m1_Chase168950(M1Obj115C *o, M1Step115C *h)
{
    M1Rec115C *s = h->rec74;
    float d = 3.40282347e+38f;
    uint32_t f;
    if (s->tgt40)
        d = sub_001B2770(o->pos60, s->tgt40->pos60);
    switch (h->state54) {
    case 0:
        f = s->flags00 & ~0x40080000u;
        s->flags00 = f;
        if (s->tgt40 && 40.0f > d)
            s->flags00 = f | 0x40000000;
        h->t5C = 0.5f;
        s->fx5C = (void *)sub_00036750(o, 4);
        sub_00033AB0(s->fx5C);
        h->state54++;
    case 1:
        if (0.0f > h->t5C) {
            s->flags00 |= 4;
            s->f04 = 7.0f;
            h->t5C = (float)(sub_001C7EE1() % 30 + 5) * 0.100000001f;
            h->state54++;
        }
        return;
    case 2:
        if (s->tgt40 && !(s->flags00 & 0x40000000) && 40.0f > d) {
            s->flags00 |= 0x40000000;
            if (s->fx5C)
                sub_00033AC0(s->fx5C);
            s->fx5C = (void *)sub_00036750(o, 4);
            sub_00033AB0(s->fx5C);
        }
        if (!(s->tgt40->b0C & 1)) {
            s->tgt40 = 0;
            sub_001671D0(o, h, 5);
            return;
        }
        if (o->b128 & 6)
            s->flags00 ^= 0x200;
        if (0.0f > h->t5C && 15.0f > d && !(s->flags00 & 0x20)) {
            s->flags00 |= 0x4020000;
            sub_001671D0(o, h, 3);
        }
    }
}

typedef struct M1Rig115S { uint32_t flags00; } M1Rig115S;
typedef struct M1Step115S {
    uint8_t unk000[0x50];
    int32_t stop50;            /* +0x50 */
    uint8_t unk054[0x6C - 0x54];
    int32_t snd6C;             /* +0x6C */
    uint8_t unk070[0x278 - 0x70];
    M1Rig115S *rig278;         /* +0x278 */
} M1Step115S;
typedef struct M1Obj115S {
    uint8_t unk00[0x20];
    float  *m20;               /* +0x20 */
    uint8_t unk24[0x50 - 0x24];
    float   rx50, ry54, rz58;  /* +0x50 */
    uint8_t unk5C[0x60 - 0x5C];
    float   pos60[4];          /* +0x60 */
    uint8_t unk70[0x80 - 0x70];
    float   vel80[4];          /* +0x80 */
} M1Obj115S;
int  sub_00049700(int id, int r, int g, int b, const void *pos, int a, float size, int c);
void sub_00048250(int h);
void sub_001AD8B0(float *d, const float *s, float a);
void sub_001AD910(float *d, const float *s, float a);
void sub_001ADA40(float *d, const float *m);

/* 0x001754E0: spinning object (as 0x177840), but while rig flag 0x200 is set the pitch +0x50
 * eases back toward 0 by 1 degree * frameTime and the flag clears once it is within that. */
void m1_Spin1754E0(M1Obj115S *o, M1Step115S *h)
{
    M1Rig115S *r = h->rig278;
    float m[16];
    uint32_t f = r->flags00 & 0x800;
    if (f && h->snd6C < 0) {
        h->snd6C = sub_00049700(0x20B, 0x80, 0x80, 0x80, o->pos60, 1, 100.0f, 1);
    } else if (h->snd6C >= 0 && (!f || h->stop50 != 0)) {
        sub_00048250(h->snd6C);
        h->snd6C = -1;
        r->flags00 &= ~0x800u;
    }
    if (r->flags00 & 0x200) {
        if (o->rx50 > 0.0f)
            o->rx50 = m1_frameTime42C858 * -0.0174532924f + o->rx50;
        else if (0.0f > o->rx50)
            o->rx50 = m1_frameTime42C858 * 0.0174532924f + o->rx50;
        if (m1_frameTime42C858 * 0.0174532924f > o->rx50 && o->rx50 > m1_frameTime42C858 * -0.0174532924f)
            r->flags00 &= ~0x200u;
    }
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

typedef struct M1Rig115W {
    uint32_t flags00;
    uint8_t unk04[0x28 - 4];
    float   vy28;              /* +0x28 */
    uint8_t unk2C[0x3C - 0x2C];
    void   *path3C;            /* +0x3C */
    uint32_t flags40;          /* +0x40 */
    uint8_t unk44[0x4C - 0x44];
    float   air4C;             /* +0x4C */
    uint8_t unk50[0x58 - 0x50];
    float   t58;               /* +0x58 */
    uint8_t unk5C[0x60 - 0x5C];
    float   t60;               /* +0x60 */
    float   v64[4];            /* +0x64 */
} M1Rig115W;
typedef struct M1Step115W {
    uint8_t unk000[0x50];
    int32_t state50;           /* +0x50 */
    uint8_t unk054[0xF8 - 0x54];
    int32_t mode0F8;           /* +0xF8 */
    uint8_t unk0FC[0x104 - 0xFC];
    M1Pl115 *tgt104;           /* +0x104 */
    uint8_t unk108[0x278 - 0x108];
    M1Rig115W *rig278;         /* +0x278 */
} M1Step115W;

/* 0x00156500: path walker step (rig variant of 0x1465C0): re-orthonormalise in states
 * 0x3C..0x3E, feed target and position to the path, heading into +0x64, flag 0x2000 from the
 * path, gravity 294 * frameRate^2 on +0x28 while airborne (flag 4, skipped once on flag 8),
 * air time (max 10), count down +0x58, and the +0x60 timer with pose 7 (flag 0x40000). */
void m1_PathStep156500(M1Obj115 *o, M1Step115W *h)
{
    M1Rig115W *r = h->rig278;
    int st = h->state50;
    float v;
    if (st == 0x3C || st == 0x3D || st == 0x3E) {
        sub_001AD7E0(o->m20, o->m20);
        sub_001AD7E0(o->m20 + 4, o->m20 + 4);
        sub_001ADA60(o->m20 + 8, o->m20, o->m20 + 4);
        sub_001ADA60(o->m20, o->m20 + 4, o->m20 + 8);
    } else {
        sub_00145F70(o->m20, o->m20);
    }
    if (h->mode0F8 == 1)
        sub_00166200(r->path3C, h->tgt104->pos60, 0);
    else if (h->mode0F8 == 2)
        sub_00166200(r->path3C, &h->tgt104, 0);
    sub_00166200(r->path3C, o->pos60, 2);
    sub_00166750(r->path3C);
    sub_00166260(r->path3C, r->v64, 1);
    if (sub_001662C0(r->path3C, 0x10000) == 1)
        r->flags40 |= 0x2000;
    else
        r->flags40 &= ~0x2000u;
    if (r->flags00 & 4) {
        if (r->flags00 & 8) {
            r->flags00 &= ~8u;
        } else {
            v = m1_frameRate42C85C * m1_frameRate42C85C * 294.0f;
            if (!(o->b128 & 0x18))
                v += r->vy28;
            r->vy28 = v;
        }
    }
    if (o->b128 & 6) {
        v = r->air4C + m1_frameRate42C85C;
        r->air4C = v;
        if (v > 10.0f)
            r->air4C = 10.0f;
    } else {
        r->air4C = 0.0f;
    }
    v = r->t58 - m1_frameRate42C85C;
    r->t58 = v;
    if (0.0f > v)
        r->t58 = 0.0f;
    if (r->flags40 & 0x40000) {
        v = r->t60 - m1_frameRate42C85C;
        r->t60 = v;
        if (0.0f >= v) {
            r->t60 = 1.0f;
            sub_00036750(o, 7);
        }
    }
}
