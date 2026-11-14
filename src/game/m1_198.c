/* Area m1, file 198: proximity checks. Names inferred. */
#include <stdint.h>

typedef struct M1Px198 { uint8_t unk00[0x60]; float pos60[4]; } M1Px198;
typedef struct M1PxS198 { uint8_t unk00[0x18]; uint8_t b18; } M1PxS198;
extern uint8_t  a80_flags3ED258;
extern M1PxS198 *a8c_g3ED254;
extern int32_t  a80_mode3ED274;
extern M1Px198 *g_playerObj;
M1Px198 *m1_FindFirstEDB10(int kind);
M1Px198 *r2c_FindNext(void);
float sub_001A3F30(float v);
float sub_001B2770(const float *a, const float *b);

/* 0x87BB0: pick the camera mode: 1 when forced or when any kind-1 object is within 50 of the player (and within 200 in height), 0xC when there are none. */
void m1_NearCheck087BB0(void) {
    uint8_t f = a80_flags3ED258; M1Px198 *n, *pl;
    if (f & 1) { a80_mode3ED274 = 1; return; }
    if (!(f & 2)) return;
    if (a8c_g3ED254->b18 != 0) { a80_mode3ED274 = 1; return; }
    n = m1_FindFirstEDB10(1);
    if (n == 0) { a80_mode3ED274 = 0xC; return; }
    pl = g_playerObj;
    do {
        if (200.0f > sub_001A3F30(pl->pos60[1] - n->pos60[1]) &&
            50.0f >= sub_001B2770(pl->pos60, n->pos60)) { a80_mode3ED274 = 1; return; }
        n = r2c_FindNext();
    } while (n != 0);
}

typedef struct M1Sp198 { uint8_t unk00[0x50]; float rot50[3]; } M1Sp198;
extern float m1_frameTime42C858;

/* 0xF6450: spin an object: add spin*frame time to each rotation axis, wrapping each into [-pi, pi]. */
void m1_SpinAdd0F6450(M1Sp198 *o, const float *spin) {
    float a;
    if (o == 0) return;
#define M1_WRAP198(i) \
    a = spin[i] * m1_frameTime42C858 + o->rot50[i]; o->rot50[i] = a; \
    if (a > 3.14159274f) o->rot50[i] = a - 6.28318548f; \
    else if (-3.14159274f > a) o->rot50[i] = a + 6.28318548f;
    M1_WRAP198(0)
    M1_WRAP198(1)
    M1_WRAP198(2)
#undef M1_WRAP198
}

void  rbj_VecSub(float *dst, const float *a, const float *b);
float sub_00082D70(const float *v);

/* 0xC4190: cylinder test: is b within horizontal reach r + ext[0] of a and inside a's height band (a.y +/- r, allowing ext[1] below)? 1 if so, else -1. */
int m1_InCylinder0C4190(float r, const float *a, const float *ext, const float *b) {
    float v[4], lo, hi, reach;
    v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 1.0f;
    reach = r + ext[0];
    lo = a[1] - r;
    hi = a[1] + r;
    rbj_VecSub(v, a, b);
    v[1] = 0.0f;
    if (sub_00082D70(v) > reach) return -1;
    if (lo > b[1]) return -1;
    if (b[1] - ext[1] > hi) return -1;
    return 1;
}

typedef struct M1AiQ198 { uint8_t unk00[0x34]; void *p34; } M1AiQ198;
typedef struct M1AiM198 { uint8_t unk00[0x50]; float x50[4]; float p60[4]; float f70; float t74; uint8_t unk78[0x28]; float pA0[3]; uint8_t unkAC[0x1CC]; M1AiQ198 *st278; } M1AiM198;
void sub_00113AA0(void *a, M1AiM198 *e);
void sub_0018E7F0(void *p, int k);
void m1_AiGoto113040(void *a, M1AiM198 *e, int st);
int  m1_XfAlloc0C7540(void *owner, float a, float b, const float *pos, const float *dir);

/* 0x13FD90: while the wait timer runs, spawn a trail transform at the offset position; when it runs out, finish the action, release its held object and go to state 0xC. */
void m1_AiWaitDone13FD90(void *a, M1AiM198 *e) {
    float v[4];
    if (0.0f >= e->t74) {
        sub_00113AA0(a, e);
        if (e->st278->p34) sub_0018E7F0(e->st278->p34, 0);
        m1_AiGoto113040(a, e, 0xC);
        return;
    }
    v[0] = e->p60[0] + e->pA0[0];
    v[1] = e->p60[1] + e->pA0[1];
    v[2] = e->p60[2] + e->pA0[2];
    v[3] = e->p60[3];
    m1_XfAlloc0C7540(e, 1.0f, e->f70 * 0.8f, v, e->x50);
}
