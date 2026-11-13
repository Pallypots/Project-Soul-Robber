/* Area m1, file 58: vector helpers and timed triggers. Names inferred. */
#include <stdint.h>

float sub_001A3F50(float x);

/* 0x00094680: out = the x/z direction of v, normalised, with y = w = 0. */
float *m1_FlatDir094680(float *out, const float *v)
{
    float len = sub_001A3F50(v[0] * v[0] + v[2] * v[2]);
    float inv = 1.0f / len;
    out[0] = inv * v[0];
    out[1] = 0.0f;
    out[2] = inv * v[2];
    out[3] = 0.0f;
    return out;
}

typedef struct M1Yaw { uint8_t unk00[0xFC]; float yawFC; } M1Yaw;
void sub_00082A30(float *out, const float *rot, const float *v);
void sub_001AD7E0(float *out, const float *v);

/* 0x000CF2C0: forward vector of o: (0, 0, -1, 1) rotated by (0, yaw +0xFC, 0, 1)
 * (0x82A30), then normalised (0x1AD7E0). */
void m1_Forward0CF2C0(const M1Yaw *o, float *out)
{
    float r[4];
    r[0] = 0.0f;
    r[2] = 0.0f;
    out[1] = 0.0f;
    out[0] = 0.0f;
    out[2] = -1.0f;
    out[3] = 1.0f;
    r[3] = 1.0f;
    r[1] = o->yawFC;
    sub_00082A30(out, r, out);
    sub_001AD7E0(out, out);
}

typedef struct M1TrigObj { uint8_t unk00[8]; int32_t kind08; } M1TrigObj;
typedef struct M1TrigSt { uint8_t unk00[0xBC]; int16_t fired; } M1TrigSt;
typedef struct M1Timer68 { uint8_t unk00[0x68]; float t68; } M1Timer68;
M1TrigSt *sub_000F5F80(M1TrigObj *o);
int  sub_000F5D00(M1TrigObj *o);

/* 0x000F95B0: marks o's trigger state fired (+0xBC = 1) once the timer passes the limit
 * (1.6 / 2.5 / 3.0 for kinds 3 / 4 / 5, else lim) or 0xF5D00(o) reports done. */
void m1_TrigTimed0F95B0(M1TrigObj *o, float lim, M1Timer68 *t)
{
    M1TrigSt *s = sub_000F5F80(o);
    if (o->kind08 == 3)
        lim = 1.6f;
    else if (o->kind08 == 4)
        lim = 2.5f;
    else if (o->kind08 == 5)
        lim = 3.0f;
    if (t->t68 > lim || sub_000F5D00(o) != 0)
        s->fired = 1;
}

typedef struct M1Fade14 { float a00, b04, c08, d0C; int32_t on10; } M1Fade14;
M1Fade14 *sub_00053AB0(int size, int a, int tag);

/* 0x000904F0: allocates a 0x14-byte record (0x53AB0, tag 0x52) holding (a, b, c, d) with
 * b and d clamped to 0..1, and marks it on. */
M1Fade14 *m1_FadeNew0904F0(float a, float b, float c, float d)
{
    M1Fade14 *f = sub_00053AB0(0x14, 0, 0x52);
    if (b > 1.0f)
        b = 1.0f;
    else if (0.0f > b)
        b = 0.0f;
    if (d > 1.0f)
        d = 1.0f;
    else if (0.0f > d)
        d = 0.0f;
    f->b04 = b;
    f->a00 = a;
    f->c08 = c;
    f->d0C = d;
    f->on10 = 1;
    return f;
}

typedef struct M1PosObj { uint8_t unk00[0x60]; float pos60[4]; } M1PosObj;
typedef struct M1Aim90 {
    uint8_t unk000[0x90];
    float   v90[4];            /* +0x90 */
    uint8_t unk0A0[0x120 - 0xA0];
    M1PosObj *target120;       /* +0x120 */
} M1Aim90;
void sub_000F5D40(float *dst, const float *src);
void sub_001AD9F0(float *out, const float *a, const float *b);
void sub_001ADBA0(float *out, const float *dir, int mode);

/* 0x000A30F0: aims +0x90 along the unit direction from the target (+0x120) to p
 * (w = 1) via 0x1ADBA0(mode), then clears +0x9C. */
void m1_AimAt0A30F0(M1Aim90 *o, const float *p, int mode)
{
    float v[4];
    sub_000F5D40(v, p);
    sub_001AD9F0(v, v, o->target120->pos60);
    sub_001AD7E0(v, v);
    v[3] = 1.0f;
    sub_001ADBA0(o->v90, v, mode);
    o->v90[3] = 0.0f;
}
