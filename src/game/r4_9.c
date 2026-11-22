/* Area r4: fog command emitter with range upload (r4_9). Names inferred. */
#include "r4.h"
#include <xmmintrin.h>

void r4f_SetFogRange(void *f); /* 0x001A7100 */
extern R4Fog *r4_g40F1B8;

/* 0x001B1E80: compute the fog factors, emit the fog command words plus the range block,
   remember the fog block and upload its range; returns the next command slot. */
uint32_t *r4_FogEmitFull(R4Fog *f, uint32_t *cmd)
{
    float k = 0.0f - (f->f04 - f->f00) / (f->f0C - f->f08);
    uint32_t *p;
    f->cmd34 = cmd;
    f->f30 = k;
    f->f20 = 0.0f - f->f0C * k;
    cmd[0] = 0x30000002;
    cmd[2] = 0x1000101;
    cmd[3] = 0x6C02000E;
    p = cmd + 4;
    cmd[1] = (uint32_t)(uintptr_t)&f->f14; /* XBOX32: GPU push-buffer word holds a 32-bit address */
    p[0] = 0x10000002;
    p[3] = 0x50000002;
    p[1] = 0;
    p[2] = 0;
    p[6] = 0xE;
    p[7] = 0;
    p[4] = 0x8001;
    p[5] = 0x10000000;
    p += 8;
    p[2] = 0x3D;
    p[3] = 0;
    p[0] = ((uint32_t *)f)[4];
    p[1] = ((uint32_t *)f)[5];
    r4_g40F1B8 = f;
    r4f_SetFogRange(f);
    return p + 4;
}

void  sub_000F5D40(void *d, const void *s);       /* vector copy */
float sub_001AD9D0(const float *a, const float *b); /* dot product */
float sub_001A3F20(float x);                        /* acos (Hypothesis) */
void  sub_001ADA60(float *d, const float *a, const float *b); /* cross product */

/* 0x001B27C0: signed angle (radians) between directions a and b in the ground plane:
   flatten both (y = 0), normalise, acos of the clamped dot, negative when the cross y is below 0. */
float r4_GroundAngle(const float *a, const float *b)
{
    float d;
    float vb[4];
    float c[4];
    float va[4];
    sub_000F5D40(va, a);
    va[1] = 0.0f;
    sub_001AD7E0(va, va);
    sub_000F5D40(vb, b);
    vb[1] = 0.0f;
    sub_001AD7E0(vb, vb);
    d = sub_001AD9D0(va, vb);
    if (d > 1.0f)
        d = 1.0f;
    else if (-1.0f > d)
        d = -1.0f;
    d = sub_001A3F20(d);
    sub_001ADA60(c, va, vb);
    if (0.0f > c[1])
        d = 0.0f - d;
    return d;
}

void sub_001A6CF0(void *o);
void sub_001A6CC0(void *m);
void sub_001A6EE0(float *v);
extern void *r4_g40F334;
uint32_t *r4_FogEmitFullB(R4Fog *f, uint32_t *cmd); /* alias of 0x001B1E80 (keeps the call) */

/* 0x001B7360: emit the camera state of o into the command buffer: header words, the 14
   vectors at +0x1F0, the 4x4 block at +0x1B0, then the fog block at +0x290; clears the
   current colour. Returns the next command slot. Stack args (cmd o). */
uint32_t *r4_CamEmit(uint32_t *cmd, uint8_t *o)
{
    float v[4];
    uint32_t *p = cmd + 4;
    const uint32_t *s;
    int i;
    cmd[0] = 0x10000000;
    cmd[1] = 0;
    cmd[2] = 0;
    cmd[3] = 0x11000000;
    p[0] = 0x1000000E;
    p[1] = 0;
    p[2] = 0x1000101;
    p[3] = 0x6C0E0000;
    p += 4;
    s = (const uint32_t *)(o + 0x1F0);
    for (i = 14; i != 0; i--) {
        p[3] = s[3];
        p[2] = s[2];
        p[1] = s[1];
        p[0] = s[0];
        p += 4;
        s += 4;
    }
    sub_001A6CF0(o);
    sub_001A6CC0(o + 0xB0);
    p[0] = 0x10000004;
    p[1] = 0;
    p[2] = 0x1000101;
    p[3] = 0x6C04000A;
    p += 4;
    s = (const uint32_t *)(o + 0x1B0);
    p[3] = s[3];   p[2] = s[2];   p[1] = s[1];   p[0] = s[0];
    p[7] = s[7];   p[6] = s[6];   p[5] = s[5];   p[4] = s[4];
    p[11] = s[11]; p[10] = s[10]; p[9] = s[9];   p[8] = s[8];
    p[15] = s[15]; p[14] = s[14]; p[13] = s[13]; p[12] = s[12];
    p += 16;
    r4_g40F334 = o;
    p = r4_FogEmitFullB((R4Fog *)(o + 0x290), p);
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 0.0f;
    sub_001A6EE0(v);
    return p;
}

void r4_MatCopyRotation(float *d, const float *s);   /* 0x001B1F70 */
void sub_001ADBA0(float *d, const float *s, float k); /* d = s * k */
extern uint32_t r4_g378088[4];

/* 0x001B50F0: emit the matrix m (full and rotation-only), then pull the point p (in camera
   space) back towards the eye so it lies at least r from it (or 0.001 inside), project it,
   set the depth bias from the depth change and emit the point and the closing words.
   Returns the next command slot. Stack args (m cmd p r). */
uint32_t *r4_BillboardEmit(const float *m, uint32_t *cmd, const float *p, float r)
{
    float b[4];
    float a[4];
    float c[4];
    float d, x;
    uint32_t *volatile q = cmd + 4;   /* volatile keeps the step-by-step pointer advances */
    uint8_t *cam;
    cmd[0] = 0x10000000;
    cmd[1] = 0;
    cmd[2] = 0;
    cmd[3] = 0x11000000;
    q[0] = 0x10000008;
    q[1] = 0;
    q[2] = 0x1000101;
    q[3] = 0x6C08001B;
    q += 4;
    sub_001ADA40(q, m);
    q += 16;
    r4_MatCopyRotation((float *)q, m);
    q += 16;
    sub_001AD9B0(a, (uint8_t *)r4_g40F334 + 0xB0, p);
    sub_001AD7E0(b, a);
    d = sub_001AD9D0(a, b);
    if (r > d)
        x = d - 0.001f;
    else
        x = r;
    sub_001ADBA0(b, a, (d - x) / d);
    cam = (uint8_t *)r4_g40F334;
    sub_001AD9B0(a, cam + 0xF0, a);
    cam = (uint8_t *)r4_g40F334;
    sub_001AD9B0(b, cam + 0xF0, b);
    b[3] = b[2] - a[2];
    c[0] = 0.0f;
    c[1] = 0.0f;
    c[2] = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(b[3]), _mm_set_ss(-0.025f)));
    c[3] = 0.0f;
    sub_001A6EE0(c);
    q[0] = 0x10000001;
    q[1] = 0;
    q[2] = 0x1000101;
    q[3] = 0x6C010009;
    q += 4;
    sub_000F5D40(q, b);
    q[5] = 0;
    q[4] = 0x10000000;
    q[6] = 0x14000000;
    q[7] = 0x11000000;
    q += 4;
    q[5] = 0;
    q[4] = 0x10000001;
    q[6] = 0x1000101;
    q[7] = 0x30000000;
    q += 4;
    q += 4;
    q[3] = r4_g378088[3];
    q[2] = r4_g378088[2];
    q[1] = r4_g378088[1];
    q[0] = r4_g378088[0];
    return q + 4;
}
