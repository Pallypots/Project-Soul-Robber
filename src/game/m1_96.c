/* Area m1, file 96: launches and scene cleanup. Names inferred. */
#include <stdint.h>

typedef struct M1Obj96 {
    uint8_t unk00[0xC];
    uint32_t flags0C;          /* +0x0C */
    uint32_t flags10;          /* +0x10 */
    uint8_t unk14[0x20 - 0x14];
    float  *node20;            /* +0x20 */
    uint8_t unk24[0x70 - 0x24];
    float   size70;            /* +0x70 */
    uint8_t unk74[0xB0 - 0x74];
    float   fB0;               /* +0xB0 */
    float   fB4;               /* +0xB4 */
    uint8_t unkB8[0xE8 - 0xB8];
    float   fE8;               /* +0xE8 */
    uint8_t unkEC[0xF0 - 0xEC];
    int32_t iF0;               /* +0xF0 */
} M1Obj96;
typedef struct M1Shot96 { uint8_t unk00[0x28]; float f28; uint8_t unk2C[0x4C - 0x2C]; float dir4C[4]; uint8_t unk5C[0x70 - 0x5C]; float f70; } M1Shot96;
extern float m1_fps42C964;
float sub_001B27C0(const float *a, const float *b);
void  sub_001AD940(float *m);
void  sub_001AD8E0(float *d, const float *s, float a);
void  sub_001ADB60(float *d, const float *s, float k);

/* 0x0018AC10: launch: turn the node to the shot direction (angle from (0, 0, -1)), scale the
 * direction by fps, o flags (+0xC clear 0x20 set 0x40, +0x10 |= 5), mode 2, and size the
 * shot from +0x70: f28 = -4x, B4 = -30x, E8 = 12x, B0 = 10x. */
void m1_Launch18AC10(M1Obj96 *o, M1Shot96 *s)
{
    float v[4];
    float *d = s->dir4C;
    float a;
    float k;
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = -1.0f;
    v[3] = 0.0f;
    a = sub_001B27C0(v, d);
    sub_001AD940(o->node20);
    sub_001AD8E0(o->node20, o->node20, a);
    sub_001ADB60(d, d, m1_fps42C964);
    o->flags0C = (o->flags0C & ~0x20u) | 0x40;
    o->flags10 |= 5;
    o->iF0 = 2;
    s->f70 = 0.0f;
    k = o->size70;
    s->f28 = k * -4.0f;
    o->fB4 = k * -30.0f;
    o->fE8 = k * 12.0f;
    o->fB0 = k * 10.0f;
}

typedef struct M1Slot96 { uint8_t unk00[0xD8]; void *obj; void *res; uint8_t unk[0x54 - 8]; } M1Slot96;
extern uint8_t *m1_scr3F6130;
void sub_00033B30(void *o);
void sub_00033A70(void *r);
int  sub_000ED780(void *o);
void *sub_000E0770(void);
void sub_000E3BA0(void *p);
void sub_0001EB80(void *o);
void *sub_0001D960(void *o, int kind);
void sub_0001D910(void *o, void *c);

/* 0x00104B70: scene cleanup for an active object: 0x33B30, free the three slot resources
 * (+0xDC, stride 0x54) and the twelve at +0x2E4, release the three slot objects (+0xD8),
 * 0xE3BA0(0xE0770()), o flags (+0x10 |= 0xD, +0xC clear 3), 0x1EB80, re-register components
 * 5 and 13; returns 1 (0 when inactive). */
int m1_SceneFree104B70(uint8_t *o)
{
    uint8_t *g = m1_scr3F6130;
    void **p;
    int n;
    int off;
    void *a;
    void *b;
    if (!(o[0xC] & 1))
        return 0;
    sub_00033B30(o);
    for (p = (void **)(g + 0xDC), n = 3; n != 0; n--, p = (void **)((uint8_t *)p + 0x54)) {
        if (*p != 0) {
            sub_00033A70(*p);
            *p = 0;
        }
    }
    for (p = (void **)(g + 0x2E4), n = 12; n != 0; n--, p++) {
        if (*p != 0) {
            sub_00033A70(*p);
            *p = 0;
        }
    }
    for (off = 0; off < 0xFC; off += 0x54)
        sub_000ED780(*(void **)(m1_scr3F6130 + off + 0xD8));
    sub_000E3BA0(sub_000E0770());
    *(uint32_t *)(o + 0x10) |= 0xD;
    *(uint32_t *)(o + 0xC) &= ~3u;
    sub_0001EB80(o);
    a = sub_0001D960(o, 5);
    b = sub_0001D960(o, 0xD);
    sub_0001D910(o, a);
    sub_0001D910(o, b);
    return 1;
}
