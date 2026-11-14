/* Area m1, file 209: player hit reactions. Names inferred. */
#include <stdint.h>

typedef struct M1Hr209 { uint8_t unk00[0xFC]; float yawFC; uint8_t unk100[0x50]; uint32_t f150; uint8_t unk154[0xBF8]; float rD4C, rD50, rD54; } M1Hr209;
void  r6c_RotateVec(float *out, const float *ang, const float *v);
void  rbi_VecNorm(float *dst, const float *src);
float sub_001AD9D0(const float *a, const float *b);
void  abc_SetState(void *p, int st);

/* 0xCFE00: start the player's knockback: compare the facing with the hit direction to pick the front (0x1C) or back (0x1B) reaction and set its recoil values. */
void m1_PlKnock0CFE00(M1Hr209 *p, int unused, float *dir) {
    float v[4], r[4]; int volatile front;
    r[0] = 0.0f; r[2] = 0.0f; v[1] = 0.0f; v[0] = 0.0f;
    v[2] = -1.0f;
    r[3] = 1.0f; v[3] = 1.0f;
    r[1] = p->yawFC;
    r6c_RotateVec(v, r, v);
    rbi_VecNorm(v, v);
    dir[1] = 0.0f;
    rbi_VecNorm(dir, dir);
    { float d = sub_001AD9D0(v, dir); if (d >= 0.0f) front = 1; else front = 0; }
    p->rD4C = 0.0f;
    p->rD50 = -0.800000012f;
    p->rD54 = 0.8f;
    if (front) p->rD54 = -0.800000012f;
    abc_SetState(p, front + 0x1B);
    p->f150 |= 0x2000;
}
