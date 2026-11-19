/* Area m1, file 253: effect spawn helpers. Names inferred. */
#include <stdint.h>

typedef struct M1E253 { uint8_t unk00[0x1C]; float f1C; } M1E253;
typedef struct M1A253 { uint8_t unk00[0x74]; M1E253 *e74; } M1A253;
typedef struct M1O253 { uint8_t unk00[0xC]; uint32_t flagsC, flags10; uint8_t unk14[0x3C]; float v50[3], w5C; float pos60[4];
    float v70[4]; uint8_t unk80[0xA8]; uint8_t flags128; } M1O253;
typedef struct M1Sc253 { uint8_t unk00[0x130]; int32_t res130; } M1Sc253;
M1Sc253 *sub_000FC4B0(void);
void *sub_00035DD0(M1O253 *o, int32_t res, int32_t a, int32_t b);
void sub_00033880(void *h, float *out);
void sub_001AD940(float *m);
void sub_000F5D40(void *dst, const void *src);
void sub_00034DD0(void *h, const float *pos, const float *m, const float *col);
void sub_00034DD0b(void *h, const float *pos, const float *m, const float *col);   /* same function (alias stops cl merging calls) */
int32_t aab_Effect494D0(int32_t snd, void *pos, int32_t z);
void aab_Hide1D700(M1O253 *o);

/* 0x00195A30: pop effect: set o's draw flags, reset its rotation and scale, spawn the green burst at o (2 units lower
   when on the ground), play sound 0x15E and hide o. */
void m1_Pop195A30(M1O253 *o, M1A253 *a)
{
    M1E253 *e = a->e74;
    float col[4], buf[8], m[16], p[4];
    void *h;
    o->flags10 = (o->flags10 & ~0x200u) | 0xC45;
    o->flagsC &= ~0x80u;
    e->f1C = 1.0f;
    o->v50[0] = 0.0f;
    o->v50[1] = 0.0f;
    o->v50[2] = 0.0f;
    o->w5C = 1.0f;
    o->v70[3] = 1.0f;
    o->v70[2] = 1.0f;
    o->v70[1] = 1.0f;
    o->v70[0] = 1.0f;
    col[0] = 0.0f;
    col[1] = 1.0f;
    col[2] = 0.0f;
    col[3] = 1.0f;
    h = sub_00035DD0(o, sub_000FC4B0()->res130, 1, 1);
    sub_00033880(h, buf);
    sub_001AD940(m);
    if (o->flags128 & 8) {
        sub_000F5D40(p, o->pos60);
        p[1] -= 2.0f;
        sub_00034DD0(h, p, m, col);
    } else {
        sub_00034DD0b(h, o->pos60, m, col);
    }
    aab_Effect494D0(0x15E, o->pos60, 1);
    aab_Hide1D700(o);
}

typedef struct M1VO253 { uint8_t unk00[0x2F8]; int32_t n2F8, n2FC; uint8_t unk300[0x1C]; int32_t h31C; } M1VO253;
extern int32_t g_acb_3F0A78, r2d_g3F0A80;
int32_t sub_0019A900(int32_t h);
int32_t sub_000E07F0(M1VO253 *o);
void sub_000E5C30(M1VO253 *o);
void a5b_SndBegin(void);
void sub_0019B800(int32_t h, int32_t z);

/* 0x000E6840: voice update: while the voice system is up, restart the queued line (when r2d is set) or check the
   current one: returns 0 while it is still busy (states 1/3/4/6, or line states 1/3-6), plays the follow-up for line
   states 2/7, else 1. */
int m1_Voice0E6840(M1VO253 *o)
{
    if (!g_acb_3F0A78)
        return 1;
    if (!r2d_g3F0A80) {
        if (!o->n2F8)
            return 1;
        switch (sub_0019A900(o->h31C)) {
        case 1: case 3: case 4: case 6:
            return 0;
        }
        switch (sub_000E07F0(o)) {
        case -1: case 0:
            return 1;
        case 1: case 3: case 4: case 5: case 6:
            return 0;
        case 2: case 7:
            sub_000E5C30(o);
            return 1;
        }
        return 1;
    }
    a5b_SndBegin();
    if (o->n2FC >= 0)
        sub_0019B800(o->n2FC, 0);
    return 1;
}

typedef struct M1HE253 { uint8_t unk00[0x14]; float f14; uint8_t unk18[8]; float v20[4]; } M1HE253;
typedef struct M1HA253 { uint8_t unk00[0x74]; M1HE253 *e74; } M1HA253;
typedef struct M1HO253 { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x4C]; uint8_t pos60[0x70]; int32_t nD0; } M1HO253;
extern float a50_framesPerSecond;
extern M1HO253 *g_playerObj;
float afc_VecLengthXZ(const float *v);
M1HO253 *sub_000E23F0(int32_t a, int32_t b);
void sub_000F5EA0(float *out, const void *a, const void *b);
void sub_000F5EA0b(float *out, const void *a, const void *b);   /* same function (alias stops cl merging calls) */
void sub_001ADB60(float *dst, const float *src, float k);

/* 0x00197510: home in: speed is twice the current horizontal speed but at least 75 units per second; aim from the
   tracked target (or o) toward the player at that speed, clear +0x14 and set o's flags 0x41 and mode 2. */
void m1_Home197510(M1HO253 *o, M1HA253 *a)
{
    M1HE253 *e = a->e74;
    float lim = 75.0f / a50_framesPerSecond;
    float v;
    M1HO253 *t;
    v = afc_VecLengthXZ(e->v20);
    v = v + v;
    if (lim > v)
        v = lim;
    t = sub_000E23F0(3, 0);
    if (t)
        sub_000F5EA0(e->v20, t->pos60, g_playerObj->pos60);
    else
        sub_000F5EA0b(e->v20, o->pos60, g_playerObj->pos60);
    sub_001ADB60(e->v20, e->v20, v);
    e->f14 = 0.0f;
    o->nD0 = 2;
    o->flags10 |= 0x41;
}
