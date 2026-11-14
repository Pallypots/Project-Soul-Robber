/* Area m1, file 171: proximity triggers (range revisit). Names inferred. */
#include <stdint.h>

typedef struct M1Tg171 { uint8_t unk00[4]; int32_t kind4; uint8_t unk08[0x1C]; float v24[4]; } M1Tg171;
typedef struct M1Ac171 { uint8_t unk00[0x5B0]; float v5B0[4]; uint8_t unk5C0[0xEF8 - 0x5C0]; int32_t xEF8; } M1Ac171;
void  sub_001AD9F0(float *d, const float *a, const float *b);
float m1_VecLen082D70(const float *v);
void  m1_ActReact0CA540(M1Ac171 *o, int a, int b);

/* 0xC46B0: when a kind 0x25/0x26 object gets within 20 units of the actor, trigger reaction 2. */
void m1_ActNear0C46B0(M1Ac171 *o, M1Tg171 *t) {
    float v[4]; volatile int k;
    v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 1.0f;
    k = t->kind4;
    if (k != 0x25 && k != 0x26) return;
    if (o->xEF8 != 0) return;
    sub_001AD9F0(v, o->v5B0, t->v24);
    if (20.0f > m1_VecLen082D70(v)) m1_ActReact0CA540(o, 0, 2);
}

extern uint8_t m1_stickX42CA5E;
extern uint8_t m1_stickY42CA5F;

/* 0xCCC90: which diagonal quadrant the left stick is in (0..3), or -1 when centred on an axis. */
int m1_StickQuad0CCC90(void) {
    volatile int x = m1_stickX42CA5E - 0x7F, y = m1_stickY42CA5F - 0x7F;
    if (x == 0 || y == 0) return -1;
    if (x > 0) {
        if (y < 0) return 0;
        if (y > 0) return 1;
    }
    if (x < 0) {
        if (y > 0) return 2;
        if (y < 0) return 3;
    }
    return -1;
}

typedef struct M1Lk171 { uint32_t flags0; uint8_t unk04[0x60]; int32_t owner64; } M1Lk171;
extern M1Lk171 m1_ents41CEC0[3];

#define M1_LKFIRE171(i) do { f = m1_ents41CEC0[i].flags0;     if ((f & 1) && (f & 0x10000000) && m1_ents41CEC0[i].owner64 == who)         m1_ents41CEC0[i].flags0 = (f & 0xEFFFFFFF) | 0x20000000; } while (0)

/* 0xC6CD0: mark every armed link beam (3 slots) owned by `who` as firing. */
void m1_LinkFire0C6CD0(int who) {
    volatile uint32_t f;
    M1_LKFIRE171(0); M1_LKFIRE171(1); M1_LKFIRE171(2);
}

