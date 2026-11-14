/* Area m1, file 156: link-beam slots. Names inferred. */
#include <stdint.h>

typedef struct M1Lk156 {
    uint32_t flags0; int32_t a4; int32_t a8; float fC; float v10[4]; int32_t i20[4]; float f30;
    float v34[4]; float v44[4]; float v54[4]; int32_t i64;
} M1Lk156;
extern M1Lk156 m1_ents41CEC0[3];
void sub_000F5D40(float *d, const void *s);
void sub_00082A30(float *out, const float *a, const float *b);
void m1_LinkAdd0C6B50(void *o, int slot);

static int m1_LkFree156(void) {
    int i;
    for (i = 0; i < 3; i++)
        if (!(m1_ents41CEC0[i].flags0 & 1)) return i;
    return -1;
}

/* 0xC8850: claim a link-beam slot between two points and register it with the owner. */
int m1_LinkNew0C8850(void *owner, int a, int b, const float *p0, const float *p1) {
    float up[4]; M1Lk156 *s; int i;
    up[1] = -0.800000012f; up[2] = -0.5f; up[0] = 0.0f; up[3] = 1.0f;
    i = m1_LkFree156();
    if (i < 0) return -1;
    s = &m1_ents41CEC0[i];
    s->i20[0] = 0; s->i20[1] = 0; s->i20[2] = 0; s->i20[3] = 0; s->i64 = 0;
    s->a4 = a;
    s->v10[0] = 0.0f; s->v10[1] = 1.0f; s->v10[2] = 0.5f; s->v10[3] = 0.0f;
    s->f30 = 0.0f;
    s->v34[2] = 0.0f; s->v34[1] = 0.0f;
    s->v44[2] = 0.0f; s->v44[1] = 0.0f;
    s->v54[2] = 0.0f; s->v54[1] = 0.0f;
    s->v54[3] = 1.0f; s->v44[3] = 1.0f; s->v34[3] = 1.0f;
    s->flags0 = 0x80000000;
    s->a8 = b;
    s->fC = 0.0f;
    s->v34[0] = 0.0f; s->v44[0] = 0.0f; s->v54[0] = 0.0f;
    sub_000F5D40(s->v34, p0);
    sub_000F5D40(s->v44, p1);
    sub_00082A30(s->v54, s->v44, up);
    m1_LinkAdd0C6B50(owner, i);
    return i;
}

typedef struct M1Mtx156 { uint8_t unk00[0x40]; float m40[4][4]; uint8_t unk80[0x10]; uint32_t f90; } M1Mtx156;
typedef struct M1Cam156 {
    uint8_t unk00[0x8C]; void *o8C; uint8_t unk90[0x28]; M1Mtx156 *mB8; M1Mtx156 *mBC; float mC0[4][4];
    int32_t i100; uint8_t unk104[0x14]; float ang118;
} M1Cam156;
typedef struct M1Ob156 { uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0x4C]; float pos60[4]; } M1Ob156;
extern M1Cam156 *m1_cam3F610C;
extern void *m1_camH3F6110;
extern float m1_frameTime42C858;
void sub_001AD940(float (*m)[4]);
void sub_001AD8B0(float (*d)[4], float (*s)[4], float a);
void m1_MatMul1AD7C0(float (*d)[4], float (*a)[4], float (*b)[4]);
void sub_001ADA40(void *d, float (*m)[4]);
void sub_000F3D10(void *a, void *b, int k);
void sub_000494D0(int id, void *pos, int k);

/* 0xF4A10: tip the camera rig up over a quarter second; when done, restore it and hand control back. */
void m1_CamTipUp0F4A10(M1Ob156 *o) {
    M1Cam156 *c = m1_cam3F610C; float *a = &c->ang118; float m[4][4]; void *p, *q;
    *a = 1.57079637f / (25.0f / m1_frameTime42C858) + *a;
    if (0.0f > *a) {
        sub_001AD940(m);
        sub_001AD8B0(m, m, *a);
        m1_MatMul1AD7C0(c->mBC->m40, c->mB8->m40, c->mC0);
        m1_MatMul1AD7C0(c->mBC->m40, c->mBC->m40, m);
        return;
    }
    sub_001ADA40(c->mBC, c->mC0);
    c->mBC->f90 &= ~0x40u;
    o->f10 &= ~0x40u;
    c->i100 = 1;
    *a = 0.0f;
    p = m1_cam3F610C->o8C;
    if (p == 0) for (;;) ;
    q = m1_camH3F6110;
    if (q == 0) for (;;) ;
    sub_000F3D10(p, q, 0);
    sub_000494D0(0x1DB, o->pos60, 1);
}
