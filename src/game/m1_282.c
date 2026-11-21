/* Area m1, file 282: camera shake. Names inferred. */
#include <stdint.h>

typedef struct M1Sk282 { uint8_t unk00[0x80]; int32_t mode80; uint8_t unk84[4]; float t88; uint8_t unk8C[0x2C];
    float offB8, offBC, offC0, wC4; float ampXC8, ampZCC; } M1Sk282;
M1Sk282 *sub_0001D960(void *o, int32_t kind);
float sub_001A3ED0(float a);                                  /* cos */
float sub_001A3EE0(float a);                                  /* sin */
int32_t sub_001C7EE1(void);                                   /* rand */

/* 0x000EF520: shake offset for o's kind-5 link: while shaking (mode 2 with time left) pick a random direction
   and offset by the current amplitudes, which then decay by 2% per step; otherwise zero the offset and the
   amplitudes. regargs: o=EAX. */
void m1_ShakeOffsetEF520(void *o)
{
    M1Sk282 *k = sub_0001D960(o, 5);
    float ang, c;
    if (k->mode80 == 2 && k->t88 > 0.0f) {
        ang = (float)(sub_001C7EE1() % 3600 - 1800) * 0.0017453294f;
        c = sub_001A3ED0(ang);
        k->offB8 = sub_001A3EE0(ang) * k->ampXC8;
        k->offBC = 0.0f;
        k->wC4 = 1.0f;
        k->offC0 = c * k->ampZCC;
        k->ampXC8 = k->ampXC8 * 0.98f;
        k->ampZCC = k->ampZCC * 0.98f;
        return;
    }
    k->ampZCC = 0.0f;
    k->ampXC8 = 0.0f;
    k->offB8 = 0.0f;
    k->offBC = 0.0f;
    k->offC0 = 0.0f;
    k->wC4 = 1.0f;
}

typedef struct M1Rn282 { uint8_t unk00[0x20]; float *m20; uint8_t unk24[0x30]; float yaw54, roll58; uint8_t unk5C[0x44];
    float a0A0[4]; uint8_t unkB0[0x28]; float d0D8[1]; float yDC; } M1Rn282;
typedef struct M1Ra282 { uint8_t unk00[0x50]; int32_t mode50; } M1Ra282;
void sub_001AD940(float *m);
void sub_001AD8E0(float *d, const float *s, float a);          /* rotate Y */
void sub_001AD910(float *d, const float *s, float a);          /* rotate Z */
void sub_001ADA40(float *d, const float *s);                  /* copy matrix */
void sub_001AE010(float *d, const float *s, const float *v);   /* translate */
void sub_001ADB40(float *d, const float *s);                  /* copy 3-vector */

/* 0x00179FE0: build n's rotation (yaw then roll) into its matrix; in mode 1 also compute the turned offset
   (0, -20, 5) as n's anchor, otherwise the anchor is the origin. Both anchor points take it, and the second
   one is lowered to -7.5. */
void m1_RigAnchor179FE0(M1Rn282 *n, M1Ra282 *a)
{
    float m[16], v[4];
    sub_001AD940(m);
    sub_001AD8E0(m, m, n->yaw54);
    sub_001AD910(m, m, n->roll58);
    sub_001ADA40(n->m20, m);
    sub_001AD940(m);
    if (a->mode50 == 1) {
        v[1] = -20.0f;
        v[0] = 0.0f;
        v[2] = 5.0f;
        v[3] = 0.0f;
        sub_001AE010(m, m, v);
        sub_001AD8E0(m, m, n->yaw54);
        sub_001AD910(m, m, n->roll58);
        m[13] = 0.0f;
        m[15] = 1.0f;
    }
    sub_001ADB40(n->a0A0, &m[12]);
    sub_001ADB40(n->d0D8, &m[12]);
    n->yDC = -7.5f;
}
