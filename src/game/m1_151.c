/* Area m1, file 151: minion movement helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Anm151 { uint8_t unk00[0x30]; void *anim30; } M1Anm151;
typedef struct M1Min151 {
    uint8_t unk00[0x8C]; M1Anm151 *o8C; M1Anm151 *o90; uint8_t unk94[8]; int32_t i9C;
    uint8_t unkA0[0x158 - 0xA0]; float v158[4]; float f168; float f16C; uint8_t unk170[4]; float f174; float f178;
    float f17C; float f180; float v184[4]; float v194[4];
} M1Min151;
extern M1Min151 *m1_minion3F6120;
extern float m1_fps42C964;
void sub_000832D0(void *a, int id);
void sub_000F5D40(float *d, const void *s);
void sub_001ADB60(float *d, const float *s, float k);

/* 0xFF9F0: send the minion toward a target using its stored launch vector (scaled jump). */
void m1_MinionHop0FF9F0(uint8_t *tgt) {
    M1Min151 *p = m1_minion3F6120; float l[4], b, x; volatile float k = 2.0f;
    if (p == 0) for (;;) ;
    if (p->o8C == 0) for (;;) ;
    sub_000832D0(p->o8C->anim30, 0x28);
    sub_000832D0(m1_minion3F6120->o90->anim30, 0x28);
    p->i9C = 0;
    sub_000F5D40(p->v194, tgt + 0x60);
    l[0] = p->f168;
    b = p->f16C;
    sub_001ADB60(l, p->v158, 50.0f / m1_fps42C964);
    p->f17C = l[1];
    p->f180 = l[3];
    p->v184[3] = 0.0f; p->v184[2] = 0.0f; p->v184[1] = 0.0f; p->v184[0] = 0.0f;
    x = b / l[0] * k * k;
    p->f174 = (b - x * l[0] * 0.5f) * 8.0f / (l[0] * l[0]);
    p->f178 = x;
}

