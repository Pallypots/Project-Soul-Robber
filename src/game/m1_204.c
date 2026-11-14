/* Area m1, file 204: enemy state helpers. Names inferred. */
#include <stdint.h>

typedef struct M1JmS204 { uint32_t i0; float f4; } M1JmS204;
typedef struct M1JmE204 { uint8_t unk00[0x54]; int32_t i54; uint8_t unk58[0x1C]; M1JmS204 *st74; } M1JmE204;
typedef struct M1JmO204 { uint8_t unk00[0x30]; void *h30; uint8_t unk34[0x20]; float yaw54; uint8_t unk58[8]; float pos60[4]; } M1JmO204;
extern M1JmO204 *g_playerObj;
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
void  aab_Attach36750(void *o, int k);
void  Grade_AddExclamations(int n);
float m1_FaceAngle113200(void *o, const float *target);
int   aab_Rand(void);
int   sub_000833E0(void *h);
void  sub_001671D0(void *o, void *e, int st);

/* 0x16A5C0: surprised hop: mark the grade, face the player with a random +/-70 degree offset (unless pinned), then when the hop anim ends wait 120..240 frames and go to state 4. */
void m1_EnemySurprise16A5C0(M1JmO204 *o, M1JmE204 *e) {
    M1JmS204 *s = e->st74; uint32_t f; M1JmO204 *pl; float a;
    switch (e->i54) {
    case 0:
        aab_Attach36750(o, 1);
        Grade_AddExclamations(-1);
        f = s->i0 | 4;
        s->i0 = f;
        if (f & 0x20) s->i0 = f | 0x40;
        else {
            pl = g_playerObj;
            a = m1_FaceAngle113200(pl, o->pos60);
            o->yaw54 = ((float)(aab_Rand() % 15) * 10.0f - 70.0f) * 0.0174532924f + pl->yaw54 + a;
        }
        e->i54++;
    case 1:
        if (!sub_000833E0(o->h30)) return;
        f = s->i0 & ~4u;
        s->i0 = f;
        if (!(f & 0x20)) s->f4 = ((float)(aab_Rand() % 120) + 120.0f) / m1_frameTime42C858 * m1_frameRate42C85C;
        sub_001671D0(o, e, 4);
        break;
    }
}

float sub_001AD9D0(const float *a, const float *b);
void  rbi_VecNorm(float *dst, const float *src);
void  r4e_VecCross3(float *dst, const float *a, const float *b);
void  a3c_VecCopy(float *dst, const float *src);
void  r4e_MatIdentity(float *m);

/* 0x82C80: build a look-at rotation matrix from a forward and an up vector (z = forward, x = up x z, y = z x x, all normalised); identity when forward is zero. */
void m1_LookAt082C80(float *out, const float *fwd, const float *up) {
    float x[4], y[4], z[4];
    if (sub_001AD9D0(fwd, fwd) > 0.0f) {
        rbi_VecNorm(z, fwd);
        r4e_VecCross3(x, up, z);
        rbi_VecNorm(x, x);
        r4e_VecCross3(y, z, x);
        rbi_VecNorm(y, y);
        a3c_VecCopy(out, x);
        a3c_VecCopy(out + 4, y);
        a3c_VecCopy(out + 8, z);
        out[11] = 0.0f; out[7] = 0.0f; out[3] = 0.0f;
        out[14] = 0.0f; out[13] = 0.0f; out[12] = 0.0f;
        out[15] = 1.0f;
        return;
    }
    r4e_MatIdentity(out);
}

typedef struct M1Rig204 { uint8_t unk00[0xC0]; uint32_t nC0; uint8_t *bonesC4; } M1Rig204;
typedef struct M1RgO204 { uint8_t unk00[0x120]; struct { uint8_t unk00[0x20]; M1Rig204 *rig20; } *p120; } M1RgO204;
extern float m1_frameTime42C858;
void m1_MatMul1AD7C0(float *dst, const float *a, const float *b);
void r4c_VecAdd(float *dst, const float *a, const float *b);

/* 0x94B00: animate a rig's bones (all but the root): re-apply each bone's own 3x3 rotation to its world matrix, offset its position and advance its spin by 0.1 per frame. */
void m1_RigSpin094B00(M1RgO204 *o) {
    float m[16]; M1Rig204 *r = o->p120->rig20; uint32_t i; float *b;
    for (i = 1; i < r->nC0; i++) {
        b = (float *)(r->bonesC4 + i * 0x108);
        a3c_VecCopy(m, b);
        a3c_VecCopy(m + 4, b + 4);
        a3c_VecCopy(m + 8, b + 8);
        m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
        m1_MatMul1AD7C0(b + 16, b + 16, m);
        r4c_VecAdd(b + 28, b + 28, b + 12);
        b[31] = 1.0f;
        b[13] += m1_frameTime42C858 * 0.1f;
    }
}

typedef struct M1FdM204 { uint8_t unk00[0xE0]; int32_t iE0, iE4, iE8, iEC; } M1FdM204;
typedef struct M1FdP204 { uint8_t unk00[0x20]; M1FdM204 *m20; } M1FdP204;
typedef struct M1FdB204 { uint8_t unk00[0x20]; M1FdM204 *m20; uint8_t unk24[0x18]; M1FdP204 *p3C; } M1FdB204;
typedef struct M1FdO204 { uint8_t unk00[0x40]; int32_t st40; uint8_t unk44[0xBC]; float a100, step104, end108; uint8_t unk10C[0x14]; M1FdB204 *b120; } M1FdO204;
void sub_000A41D0(void *o, int k);
void m1_AnimScale0EE6D0(void *o, float s);

/* 0x93780: fade a pickup in: set its blend mode (and its child's) on entry, then step the alpha toward its end value and scale the light by it; despawn in state 2. */
void m1_PickupFade093780(M1FdO204 *o) {
    M1FdB204 *b = o->b120; M1FdM204 *m;
    switch (o->st40) {
    case 0:
        m = b->m20;
        m->iE0 = 0x44; m->iE4 = 0; m->iE8 = 0x5000D; m->iEC = 0;
        if (b->p3C != 0) {
            m = b->p3C->m20;
            m->iE0 = 0x44; m->iE4 = 0; m->iE8 = 0x5000D; m->iEC = 0;
        }
        o->st40++;
    case 1:
        o->a100 -= o->step104;
        if (0.0f > o->a100) *(int32_t *)&o->a100 = *(int32_t *)&o->end108;
        if (o->a100 > 1.0f) *(int32_t *)&o->a100 = *(int32_t *)&o->end108;
        if (o->a100 == o->end108) o->st40++;
        m1_AnimScale0EE6D0(b, o->a100);
        return;
    case 2:
        sub_000A41D0(o, -1);
        return;
    }
}
