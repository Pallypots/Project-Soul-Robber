/* Area m1, file 127: small helpers. Names inferred. */
#include <stdint.h>

/* 0x00071FE0: cubic Bezier through four 2D points at t. */
void m1_Bezier071FE0(const float *p, float t, float *out)
{
    float u = 1.0f - t;
    float uu = u * u;
    float c0 = uu * u;
    float c1 = uu * t * 3.0f;
    float c2 = u * t * t * 3.0f;
    float t3 = t * t * t;
    float x;
    x = p[6] * t3;
    x += p[4] * c2;
    x += p[2] * c1;
    x += p[0] * c0;
    out[0] = x;
    x = p[7] * t3;
    x += p[5] * c2;
    x += p[3] * c1;
    x += p[1] * c0;
    out[1] = x;
}

typedef struct M1Node127 { uint8_t unk00[0x40]; float m40[16]; } M1Node127;
typedef struct M1CamO127 { uint8_t unk00[0x60]; float pos60[4]; } M1CamO127;
typedef struct M1Cam127 {
    uint8_t unk000[0x8C];
    M1CamO127 *obj8C;          /* +0x8C */
    uint8_t unk090[0x9C - 0x90];
    float   t9C;               /* +0x9C */
    uint8_t unk0A0[0xB8 - 0xA0];
    M1Node127 *a0B8;           /* +0xB8 */
    M1Node127 *b0BC;           /* +0xBC */
    float   mC0[16];           /* +0xC0 */
    uint8_t unk100[0x110 - 0x100];
    float   len110;            /* +0x110 */
} M1Cam127;
extern M1Cam127 *m1_cam3F610C;
extern void *m1_camH3F6110;
extern float m1_frameRate42C85C;
void sub_001AD940(float *m);
void sub_001AD8B0(float *d, const float *s, float a);
void sub_001AD7C0(float *d, const float *a, const float *b);
void sub_000F3D10(void *o, void *c, int mode);

/* 0x000F4940: camera rig step: node B = node A times the rig matrix, pitched down 90 degrees;
 * once the timer passes +0x110 switch the camera to mode 5 (hangs without the camera object
 * or controller), else count it up. */
void m1_CamRig0F4940(void)
{
    M1Cam127 *g = m1_cam3F610C;
    M1Node127 *a = g->a0B8;
    M1Node127 *b = g->b0BC;
    M1CamO127 *c;
    float m[16];
    sub_001AD940(m);
    sub_001AD8B0(m, m, -1.57079637f);
    sub_001AD7C0(b->m40, a->m40, g->mC0);
    sub_001AD7C0(b->m40, b->m40, m);
    if (g->t9C > g->len110) {
        c = m1_cam3F610C->obj8C;
        if (c == 0)
            for (;;) ;
        if (m1_camH3F6110 == 0)
            for (;;) ;
        sub_000F3D10(c, m1_camH3F6110, 5);
        return;
    }
    g->t9C += m1_frameRate42C85C;
}

typedef struct M1Snd127 {
    uint8_t flags00;           /* +0x00 */
    uint8_t unk01[3];
    int32_t on04;              /* +0x04 */
    int32_t a08, a0C;          /* +0x08 */
    uint8_t unk10[4];
    uint8_t b14;               /* +0x14 */
    uint8_t unk15[3];
    int32_t kind18;            /* +0x18 */
    float   k1C;               /* +0x1C */
    uint8_t unk20[0x38 - 0x20];
    int32_t c38[7 * 4];        /* +0x38, every fourth used */
    uint8_t sprA8[0x134 - 0xA8]; /* +0xA8 */
    uint32_t col134;           /* +0x134 */
    uint8_t unk138[0x144 - 0x138];
} M1Snd127;
extern M1Snd127 m1_snd3F1B5C[32];
void sub_000150B0(void *s, int a);
void sub_000150E0(void *s, int a);

/* 0x000E85D0: start a HUD cue of kind (0..7, hangs otherwise) with value k in the first of the
 * 32 free slots at 0x3F1B5C: mark it on, set kind and value, set up its sprite, grey colour,
 * clear the seven channel slots. Returns the slot, -1 when all are busy. */
int m1_CueStart0E85D0(unsigned int kind, float k)
{
    M1Snd127 *r;
    int i;
    if (kind >= 8)
        for (;;) ;
    for (r = m1_snd3F1B5C, i = 0; (int)r < (int)(m1_snd3F1B5C + 32); r++, i++)
        if (!(r->flags00 & 1))
            goto found;
    return -1;
found:
    r = &m1_snd3F1B5C[i];
    r->on04 = 1;
    r->a08 = 0;
    r->a0C = 0;
    r->kind18 = kind;
    r->k1C = k;
    r->b14 = 0;
    sub_000150B0(r->sprA8, kind);
    sub_000150E0(r->sprA8, 0);
    r->col134 = 0x808080;
    r->c38[0] = 0;
    r->c38[4] = 0;
    r->c38[8] = 0;
    r->c38[12] = 0;
    r->c38[16] = 0;
    r->c38[20] = 0;
    r->c38[24] = 0;
    return i;
}

typedef struct M1Node127B { uint8_t unk00[0x30]; float pos30[4]; } M1Node127B;
typedef struct M1Tgt127 { uint8_t unk00[0x20]; M1Node127B *n20; } M1Tgt127;
typedef struct M1Aim127 { uint8_t unk000[0xFC]; float yawFC; uint8_t unk100[0xFD8 - 0x100]; M1Tgt127 *tgtFD8; } M1Aim127;
void sub_00082A30(float *d, const float *q, const float *v);
void sub_001AD7E0(float *out, const float *v);
void sub_001AD9F0(float *out, const float *a, const float *b);
float sub_001AD9D0(const float *a, const float *b);

/* 0x000CF200: aim alignment: the dot product of the facing vector (yaw +0xFC applied to
 * (0, 0, -1)) and the flat direction from the target's node to pos. */
float m1_AimDot0CF200(M1Aim127 *o, const float *pos)
{
    struct { float q[4]; float f[4]; float d[4]; } l;
    l.f[0] = 0.0f;
    l.f[1] = 0.0f;
    l.f[2] = -1.0f;
    l.q[0] = 0.0f;
    l.q[2] = 0.0f;
    l.f[3] = 1.0f;
    l.q[3] = 1.0f;
    l.q[1] = o->yawFC;
    sub_00082A30(l.f, l.q, l.f);
    sub_001AD7E0(l.f, l.f);
    sub_001AD9F0(l.d, pos, o->tgtFD8->n20->pos30);
    l.d[1] = 0.0f;
    sub_001AD7E0(l.d, l.d);
    return sub_001AD9D0(l.d, l.f);
}
