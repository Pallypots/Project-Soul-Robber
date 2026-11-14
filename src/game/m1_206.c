/* Area m1, file 206: costume pickup effects. Names inferred. */
#include <stdint.h>

typedef struct M1Pk206 { uint8_t unk00[4]; int32_t kind4; uint8_t unk08[0x2C]; float pos34[4]; } M1Pk206;
typedef struct M1Fx206 { uint8_t unk00[0x14]; float s14, s18; uint8_t unk1C[0xC4]; } M1Fx206;
extern M1Fx206 g_ac0_41E2A0[32];
extern uint8_t abc_player[];
float b16_TabFloat7C(void *p, int kind);
int   b16_TabInt84(void *p);
void  a3c_VecCopy(float *dst, const float *src);
int   m1_FxStart0C4C90(int id, float a, float s, int k, const float *v1, const float *v2, const float *v3);

/* 0xC5A10: costume pickup flash: effect 0x1E+kind at the pickup, lowered by its size (table x10), sized with a thirtieth of that as its second size; kind 2 also passes the player's level. */
void m1_PickupFlash0C5A10(M1Pk206 *o) {
    float v[4], w[4], s; int kind = o->kind4, k = 0, i;
    v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 1.0f;
    w[0] = 0.0f; w[1] = 0.0f; w[2] = 0.0f; w[3] = 1.0f;
    s = b16_TabFloat7C(abc_player, kind) * 10.0f;
    a3c_VecCopy(v, o->pos34);
    v[1] = v[1] - s;
    v[3] = 1.0f;
    if (kind == 2) k = b16_TabInt84(abc_player);
    i = m1_FxStart0C4C90(kind + 0x1E, 50.0f, 0.5f, k, v, w, w);
    if (i >= 0) {
        g_ac0_41E2A0[i].s18 = s * 0.0333333351f;
        g_ac0_41E2A0[i].s14 = s;
    }
}

typedef struct M1Jp206 { uint8_t unk00[0x8C]; void *body8C; uint8_t unk90[0x140]; float dir1D0[4]; float g1E0; uint8_t unk1E4[0x30]; float vel214[4]; } M1Jp206;
extern M1Jp206 *b10_scr;
extern float m1_frameTime42C858;
float rfl_ActorHeading(void *body);
float sub_001A3EE0(float a);
float sub_001A3ED0(float a);
void  sub_001ADB60(float *dst, const float *src, float s);

/* 0x102560: set up the helper's jump arc: horizontal direction from its heading (x77 for the launch speed, 77/flight-time for the step), then upward speed 2*128/T and the gravity that lands it after T = 70 frames. */
void m1_HelperJumpArc102560(void) {
    M1Jp206 *h = b10_scr; float a, t, up;
    a = rfl_ActorHeading(h->body8C);
    h->dir1D0[0] = sub_001A3EE0(a);
    h->dir1D0[2] = sub_001A3ED0(a);
    h->dir1D0[3] = 0.0f;
    h->dir1D0[1] = 0.0f;
    sub_001ADB60(h->vel214, h->dir1D0, 77.0f);
    sub_001ADB60(h->dir1D0, h->dir1D0, 77.0f / (70.0f / m1_frameTime42C858));
    t = 70.0f / m1_frameTime42C858;
    { float volatile k = 2.0f; up = 128.0f / t * k; }
    h->g1E0 = (64.0f - t * up * 0.5f) * 8.0f / (t * t);
    h->dir1D0[1] = 0.0f - up;
}
