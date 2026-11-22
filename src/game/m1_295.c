/* Area m1, file 295: shakes. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Ow295 { uint8_t unk00[0x54]; float yaw54; } M1Ow295;
typedef struct M1Sh295 { M1Ow295 *o0; uint8_t unk04[0x20]; float off24[3]; float f30; float ampX34, ampZ38; float t3C; } M1Sh295;
float sub_001A3EE0(float a);                                  /* sin */
float sub_001A3ED0(float a);                                  /* cos */
int32_t sub_001C7EE1(void);                                   /* rand */
void sub_001AD940(float *m);
void sub_001AD8E0(float *d, const float *s, float a);          /* rotate Y */
void sub_001AD9B0(float *d, const float *m, const float *v);
void sub_000F5D40(float *d, const float *s);

/* 0x0017F990: shake step: while the timer is positive, offset by the amplitudes in a random direction turned to
   the owner's yaw; the amplitudes decay by 3% and snap to 0 below 0.05, and the shake ends when both are 0.
   Otherwise clear the offset and amplitudes. regargs: s=ESI. */
void m1_Shake17F990(M1Sh295 *s)
{
    float ang, v[4], m[16];
    if (!s) return;
    if (!(s->t3C > 0.0f)) {
        s->ampX34 = 0.0f;
        s->ampZ38 = 0.0f;
        s->off24[0] = 0.0f;
        s->off24[1] = 0.0f;
        s->off24[2] = 0.0f;
        *(volatile float *)&s->f30 = 1.0f;
        s->f30 = 0.0f;
        return;
    }
    ang = (float)(sub_001C7EE1() % 3600 - 1800) * 0.0017453294f;
    v[1] = 0.0f;
    v[3] = 1.0f;
    v[0] = sub_001A3EE0(ang) * s->ampX34;
    v[2] = sub_001A3ED0(ang) * s->ampZ38;
    sub_001AD940(m);
    sub_001AD8E0(m, m, s->o0->yaw54);
    sub_001AD9B0(v, m, v);
    sub_000F5D40(s->off24, v);
    s->ampX34 = s->ampX34 * 0.97f;
    s->ampZ38 = s->ampZ38 * 0.97f;
    if (0.05f > s->ampX34) s->ampX34 = 0.0f;
    if (0.05f > s->ampZ38) s->ampZ38 = 0.0f;
    if (_mm_comige_ss(_mm_set_ss(0.0f), _mm_load_ss(&s->ampX34)) &&
        _mm_comige_ss(_mm_set_ss(0.0f), _mm_load_ss(&s->ampZ38)))
        s->t3C = 0.0f;
    s->f30 = 0.0f;
}
