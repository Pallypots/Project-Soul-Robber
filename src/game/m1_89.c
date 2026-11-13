/* Area m1, file 89: effect spawns. Names inferred. */
#include <stdint.h>

typedef struct M1Obj89 { uint8_t unk00[0x54]; float yaw54; uint8_t unk58[0x60 - 0x58]; float pos60[4]; } M1Obj89;
void *sub_00035D80(void *o, int a, int b);
void sub_001ADAF0(float *d, const float *a, const float *b);
void sub_001AD940(float *m);
void sub_001AE010(float *d, const float *m, const float *v);
void sub_001AD8E0(float *d, const float *s, float a);
void sub_00034E00(void *fx, const float *pos, const float *at, const float *up);

/* 0x00175310: spawn effect (0x35D80(v, 3)) at the object lowered by p[1], oriented by a frame
 * built from (0, 0, -1) and the object yaw, with up (0, 1, 0). */
void m1_FxSpawn175310(M1Obj89 *o, const float *p, int v)
{
    float a[4];
    float c[4];
    float d[4];
    float m[16];
    void *fx;
    d[0] = 0.0f;
    d[2] = 0.0f;
    a[0] = 0.0f;
    a[2] = 0.0f;
    c[0] = 0.0f;
    c[1] = 0.0f;
    d[1] = 1.0f;
    d[3] = 1.0f;
    a[3] = 1.0f;
    c[2] = -1.0f;
    c[3] = 1.0f;
    a[1] = 0.0f - p[1];
    fx = sub_00035D80(o, v, 3);
    sub_001ADAF0(a, o->pos60, a);
    sub_001AD940(m);
    sub_001AE010(m, m, c);
    sub_001AD8E0(m, m, o->yaw54);
    sub_00034E00(fx, a, &m[12], d);
}

typedef struct M1Pl89 { uint8_t unk00[0x60]; float pos60[4]; } M1Pl89;
typedef struct M1Ray89 { float v[4]; float x, y; } M1Ray89;
extern M1Pl89 *g_playerObj;
extern uint8_t m1_stats41FEC0[];
void sub_000C4250(void *s, float *a, float *b);
int  sub_00194F00(M1Ray89 *r, void *a, float *out);
void sub_001AD9F0(float *out, const float *a, const float *b);
void sub_001AD7E0(float *out, const float *v);
int  sub_000D3BF0(void *s, void *a, void *b, const float *pos, const float *dir);
void sub_000F5D40(float *d, const float *s);

/* 0x0017D5C0: pick a point from the player's aim (0xC4250 and 0x194F00, -1 when none), then
 * run 0xD3BF0 with the flat direction from the point to the player; the point is also copied
 * to out (w = 1) when given. */
int m1_AimPoint17D5C0(void *a, void *b, void *c, float *out)
{
    float d[4];
    float pt[4];
    M1Ray89 ray;
    int r;
    sub_000C4250(m1_stats41FEC0, ray.v, d);
    ray.x = d[0];
    ray.y = d[1];
    if (!sub_00194F00(&ray, b, pt))
        return -1;
    sub_001AD9F0(d, g_playerObj->pos60, pt);
    d[3] = 0.0f;
    d[1] = 0.0f;
    sub_001AD7E0(d, d);
    r = sub_000D3BF0(m1_stats41FEC0, a, c, pt, d);
    if (out != 0) {
        sub_000F5D40(out, pt);
        out[3] = 1.0f;
    }
    return r;
}
