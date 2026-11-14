/* Area m1, file 121: small helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Hp121 { uint8_t unk000[0xD98]; float tD98; uint8_t unkD9C[0xE04 - 0xD9C]; int32_t hpE04; } M1Hp121;
extern uint8_t m1_stats41FEC0[];
int  sub_000D9A70(int id);
int  sub_00171CD0(void *s);

/* 0x000D2C40: health drain: reset the +0xD98 timer while event 0xF8 is set; once it reaches
 * 8, lose 1 health (capped at ten times the 0x171CD0 maximum, floored at 0) and restart. */
void m1_HpDrain0D2C40(M1Hp121 *o)
{
    int32_t *p;
    int v, n;
    if (sub_000D9A70(0xF8))
        o->tD98 = 0.0f;
    if (!(o->tD98 >= 8.0f))
        return;
    v = o->hpE04;
    p = &o->hpE04;
    n = sub_00171CD0(m1_stats41FEC0) * 10;
    v--;
    if (v >= n)
        v = n;
    if (v <= 0)
        v = 0;
    if (p)
        *p = v;
    o->tD98 = 0.0f;
}

typedef struct M1Curve121 { uint8_t unk00[4]; int32_t kind04; float *keys08; float *cur0C; } M1Curve121;
extern int32_t m1_curveTbl2E020C[];

/* 0x0007EF30: curve key lookup: from the cached key (+0x0C, else the first) walk forward
 * while the next key's time is not negative and not past t, or backward while t is before
 * the key, by the kind's key stride; caches and returns the key (0 without a curve or keys). */
float *m1_CurveFind07EF30(M1Curve121 *c, float t)
{
    float *base;
    float *cur;
    float *res;
    int st;
    if (c == 0)
        return 0;
    base = c->keys08;
    if (base == 0)
        return 0;
    cur = c->cur0C;
    if (cur == 0)
        cur = base;
    st = m1_curveTbl2E020C[c->kind04 * 5];
    if (t >= *cur) {
        res = cur;
        if (!(0.0f > *cur)) {
            while (!(*cur > t)) {
                res = cur;
                if (!(0.0f <= cur[st]))
                    break;
                cur += st;
            }
        }
    } else {
        if (cur != base) {
            while (!(t > *cur)) {
                cur -= st;
                if (cur == c->keys08)
                    break;
            }
        }
        res = cur;
    }
    c->cur0C = res;
    return res;
}

extern int32_t m1_q3F43E0, m1_q3F43E4, m1_q3F43E8, m1_q3F43EC;
extern int32_t m1_qState3F43F0;
extern float m1_qF3F43F4;
extern float m1_qT3F4408;

/* 0x000E9100: queued request step: state 0 arms it (+0x3F43F4 = 10, state 1); state 1 counts
 * the timer down by 0.01 and, once it runs out, shifts the queue (0x3F43E4..EC into
 * 0x3F43E0..E8, last cleared) and goes back to state 0. */
void m1_QueueStep0E9100(void)
{
    float t;
    switch (m1_qState3F43F0) {
    case 0:
        m1_qF3F43F4 = 10.0f;
        m1_qState3F43F0 = 1;
        return;
    case 1:
        t = m1_qT3F4408 - 0.00999999978f;
        m1_qT3F4408 = t;
        if (!(0.0f >= t))
            return;
        m1_q3F43E0 = m1_q3F43E4;
        m1_qT3F4408 = 0.0f;
        m1_q3F43E4 = m1_q3F43E8;
        m1_q3F43E8 = m1_q3F43EC;
        m1_q3F43EC = 0;
        m1_qState3F43F0 = 0;
        return;
    }
}

typedef struct M1Mdl121 { uint8_t unk00[8]; int32_t n08; } M1Mdl121;
typedef struct M1Scene121 { uint8_t unk000[0x1E8]; void *root1E8; } M1Scene121;
extern M1Scene121 *m1_scene42C8E4;
extern void *m1_pool3F59D0;
extern M1Mdl121 *m1_pool3F59D8;
extern int32_t m1_pool3F59DC;
extern void *m1_pool3F59E0;
extern int32_t m1_pool3F59F0;
M1Mdl121 *sub_0001F930(int kind, void *res);
void sub_0001CFF0(void *root, void *m, int a);
void *sub_00053AB0(int size, int a, int tag);
void __stosd(unsigned long *d, unsigned long v, unsigned int n);
void __stosb(unsigned char *d, unsigned char v, unsigned int n);
#pragma intrinsic(__stosd, __stosb)

/* 0x000EC5A0: build the effect pool once: load model (0x3F59F0, 0x3F59D0), keep its count,
 * attach it to the scene root (layer 0xF), and allocate and clear 0x30 bytes per entry. */
void m1_PoolInit0EC5A0(void)
{
    M1Mdl121 *m;
    if (m1_pool3F59DC != 0)
        return;
    m = sub_0001F930(m1_pool3F59F0, m1_pool3F59D0);
    m1_pool3F59D8 = m;
    m1_pool3F59DC = m->n08;
    sub_0001CFF0(m1_scene42C8E4->root1E8, m, 0xF);
    {
        unsigned char *d = (unsigned char *)sub_00053AB0(m1_pool3F59F0 * 0x30, 0, 0x268);
        volatile unsigned int vn = m1_pool3F59F0 * 0x30;
        unsigned int n = vn;
        m1_pool3F59E0 = d;
        __stosd((unsigned long *)d, 0, n >> 2);
        __stosb(d + (n >> 2) * 4, 0, n & 3);
    }
}

void sub_000F5D40(float *d, const float *s);
void sub_001AD9F0(float *out, const float *a, const float *b);
void sub_001ADC60(float *d, const float *a, const float *b, float k);
float sub_000BC040(const float *v);
void sub_000832D0(void *a, int v);
extern float m1_fps42C964;

typedef struct M1Lit121 { uint8_t unk000[0xFB0]; float colFB0[4]; float colFC0[4]; } M1Lit121;
extern float m1_col418B30[3];

/* 0x000CA580: reset both light colours (+0xFB0, +0xFC0) to (128, 128, 128, 1) and publish the
 * second to 0x418B30. */
void m1_LightReset0CA580(M1Lit121 *o)
{
    float v[4];
    float *c;
    v[0] = 128.0f;
    v[1] = 128.0f;
    v[2] = 128.0f;
    v[3] = 1.0f;
    sub_000F5D40(o->colFB0, v);
    c = o->colFC0;
    sub_000F5D40(c, v);
    m1_col418B30[0] = c[0];
    m1_col418B30[1] = c[1];
    m1_col418B30[2] = c[2];
}

typedef struct M1Tgt121 { uint8_t unk00[0x60]; float pos60[4]; } M1Tgt121;
typedef struct M1Aim121 {
    uint8_t unk000[0xFC];
    union { int32_t i; float f; } aimFC;   /* +0xFC */
    uint8_t unk100[0x108 - 0x100];
    int32_t aim108;            /* +0x108 */
    float   k10C;              /* +0x10C */
    uint8_t unk110[0xFD8 - 0x110];
    M1Tgt121 *tgtFD8;          /* +0xFD8 */
} M1Aim121;

/* 0x000CF330: aim at a point: keep the previous aim, take the direction from the target to
 * the point (height swapped into y), store its heading (0xBC040) and the given weight. */
void m1_AimAt0CF330(M1Aim121 *o, const float *pos, float k)
{
    float d[4];
    o->aimFC.i = o->aim108;
    d[0] = 0.0f;
    d[1] = 0.0f;
    d[2] = 0.0f;
    d[3] = 1.0f;
    sub_001AD9F0(d, o->tgtFD8->pos60, pos);
    d[1] = d[2];
    o->aimFC.f = sub_000BC040(d);
    o->k10C = k;
}

typedef struct M1Node121 { uint8_t unk00[0x20]; uint8_t *mat20; uint8_t unk24[0x3C - 0x24]; struct M1Node121 *next3C; } M1Node121;
typedef struct M1Ctx121 { uint8_t unk000[0x86C]; } M1Ctx121;
extern float m1_tint317D68[4];
extern float m1_tintK317D78;

/* 0x000E1FD0: tint a node chain: the head of slot idx (0x28-byte slots at +0x86C) gets the
 * colour blended with 0x317D68 (alpha kept), every following node the colour itself. */
void m1_TintChain0E1FD0(M1Ctx121 *c, int idx, const float *col)
{
    float t[4];
    M1Node121 *n = *(M1Node121 **)((uint8_t *)c + idx * 0x28 + 0x86C);
    sub_001ADC60(t, col, m1_tint317D68, m1_tintK317D78);
    t[3] = col[3];
    sub_000F5D40((float *)(n->mat20 + 0xD0), t);
    for (n = n->next3C; n; n = n->next3C)
        sub_000F5D40((float *)(n->mat20 + 0xD0), col);
}
