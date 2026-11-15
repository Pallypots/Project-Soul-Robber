/* Area m3, file 22: body collision push-out. Names inferred. */
#include <stdint.h>

typedef struct M3Body22 { uint32_t f0; uint8_t unk04[0x30]; float pos34[4]; uint8_t unk44[0x10]; float vel54[4]; } M3Body22;
void a3c_VecCopy(float *dst, const float *src);
int  r2b_PoolGetA(float *a, float r, float *c, float *d);
int  r2b_PoolGetB(float *a, float *b, float *c, float *d);
void rbi_VecNorm(float *d, const float *s);
float rbi_VecDot(const float *a, const float *b);
float m1_VecLen082D70(const float *v);
void rbi_VecScale(float *d, const float *s, float k);
void r4e_VecAdd4(float *d, const float *a, const float *b);

/* 0xC6EA0: collide a body: when its position is inside a wall (radius 2.5), push the velocity out along the wall normal if it points into the wall; then probe a vertical segment of +-2.5 around the position; on a hit snap position and velocity to the result and mark contact (0x40000000, or 0x4000000 when already in contact), else clear both flags. */
void m3_BodyCollideC6EA0(M3Body22 *o) {
    float a[4], v10[4], v20[4], v30[4], v40[4], l;
    a3c_VecCopy(a, o->pos34);
    v30[0] = 0.0f; v30[1] = 0.0f; v30[2] = 0.0f; v30[3] = 1.0f;
    v20[0] = 0.0f; v20[1] = 0.0f; v20[2] = 0.0f; v20[3] = 1.0f;
    v40[0] = 0.0f; v40[1] = 0.0f; v40[2] = 0.0f; v40[3] = 1.0f;
    v10[0] = 0.0f; v10[1] = 0.0f; v10[2] = 0.0f; v10[3] = 1.0f;
    if (r2b_PoolGetA(a, 2.5f, v30, v20) > 0) {
        a3c_VecCopy(a, v20);
        a3c_VecCopy(v10, o->vel54);
        v10[1] = 0.0f; a[1] = 0.0f;
        rbi_VecNorm(a, a);
        rbi_VecNorm(v10, v10);
        if (0.0f > rbi_VecDot(a, v10)) {
            a3c_VecCopy(v10, o->vel54);
            v10[1] = 0.0f;
            l = m1_VecLen082D70(v10);
            rbi_VecScale(a, a, l);
            r4e_VecAdd4(o->vel54, o->vel54, a);
        }
    }
    a3c_VecCopy(a, o->pos34);
    a[1] = a[1] - 2.5f;
    a3c_VecCopy(v10, o->pos34);
    v10[1] = v10[1] + 2.5f;
    if (r2b_PoolGetB(a, v10, v30, v20) > 0) {
        a3c_VecCopy(o->pos34, v30);
        a3c_VecCopy(o->vel54, v40);
        if (!(o->f0 & 0x40000000)) { o->f0 |= 0x40000000; return; }
        o->f0 |= 0x4000000;
        return;
    }
    o->f0 &= ~0x44000000u;
}
