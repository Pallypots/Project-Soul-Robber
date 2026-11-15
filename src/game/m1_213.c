/* Area m1, file 213: boss projectile launch. Names inferred. */
#include <stdint.h>

typedef struct M1PjO213 { uint8_t unk00[0xC]; uint32_t iC; uint32_t i10; uint8_t unk14[0xC]; float *m20; uint8_t unk24[0x2C]; float f50, f54, f58, f5C; } M1PjO213;
typedef struct M1PjR213 { M1PjO213 *obj0; uint8_t unk04[0x3C]; float speed40; float vel44[4]; uint8_t unk54[4]; } M1PjR213;
extern M1PjR213 m1_recs3FE0C0[3];
extern int32_t m1_recs3FE0C0_18;
extern int32_t r3d_i3FE0B8;
extern uint8_t m1_pt32B808[];
void  sub_000F3FD0(M1PjO213 *o);
float rfl_ActorHeading(void *o);
float sub_001A3EE0(float a);
float sub_001A3ED0(float a);
void  r4c_VecAdd(float *dst, const float *a, const float *b);
float sub_000F7720(void *o, const void *p);

/* 0x17F390: launch the boss's three projectiles: reset each one, give it speed 22 along its heading from its current position, aim it at the target point and enable it; then flag the volley started. */
int m1_BossVolley17F390(void) {
    float *q; M1PjO213 *o; float a, v[4];
    for (q = &m1_recs3FE0C0[0].speed40; (int32_t)q < (int32_t)&m1_recs3FE0C0[3].speed40; q += 0x58 / 4) {
        o = *(M1PjO213 **)(q - 0x10);
        o->f50 = 0.0f; o->f54 = 0.0f; o->f58 = 0.0f; o->f5C = 1.0f;
        sub_000F3FD0(o);
        { float *volatile tv = o->m20 + 12; float *t = tv; t[0] = 0.0f; t[1] = 0.0f; t[2] = 0.0f; t[3] = 1.0f; }
        *q = 22.0f;
        a = rfl_ActorHeading(o);
        v[0] = sub_001A3EE0(a) * *q;
        v[2] = sub_001A3ED0(a) * *q;
        v[3] = 0.0f; v[1] = 0.0f;
        r4c_VecAdd(q + 1, o->m20 + 28, v);
        o->f54 = sub_000F7720(o, m1_pt32B808);
        o->i10 &= ~0x4Du;
        o->iC |= 0x20;
        *(uint32_t *)((uint8_t *)o->m20 + 0x90) |= 0x40;
    }
    m1_recs3FE0C0_18 = 1;
    r3d_i3FE0B8 = 1;
    return 1;
}
