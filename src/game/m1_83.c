/* Area m1, file 83: rig steps. Names inferred. */
#include <stdint.h>

typedef struct M1Cmd83 { int32_t i00; uint8_t unk04[0x10 - 4]; float f10, f14, f18, f1C; } M1Cmd83;
typedef struct M1Step83 {
    uint8_t unk000[0x20];
    uint8_t b20;               /* +0x20 */
    uint8_t unk021[0x4C - 0x21];
    uint32_t flags4C;          /* +0x4C */
} M1Step83;
typedef struct M1Obj83 { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x60 - 0x14]; float pos60[4]; } M1Obj83;
extern float m1_fps42C964;
void *sub_00036750(void *o, int b);
int  sub_000494D0(int id, const void *pos, int c);
M1Cmd83 *sub_00113400(void *h, int v);

/* 0x00159D60: stun: o flags 0xD, clear h +0x4C bits 0x1000070, effect 4, sound 0x130, command
 * 7 = (fps unless -1, 0, 0, 0) and with h +0x20 bit 0 command 5 = (0.5, 2, 0, 0); a running
 * command is set to state 2. */
void m1_Stun159D60(M1Obj83 *o, M1Step83 *h)
{
    float t;
    M1Cmd83 *c;
    o->flags10 |= 0xD;
    h->flags4C &= ~0x1000070u;
    sub_00036750(o, 4);
    sub_000494D0(0x130, o->pos60, 0);
    t = m1_fps42C964;
    c = sub_00113400(h, 7);
    if (t != -1.0f)
        c->f10 = t;
    c->f14 = 0.0f;
    c->f18 = 0.0f;
    c->f1C = 0.0f;
    if (c->i00 != 0)
        c->i00 = 2;
    if (h->b20 & 1) {
        c = sub_00113400(h, 5);
        c->f10 = 0.5f;
        c->f14 = 2.0f;
        c->f18 = 0.0f;
        c->f1C = 0.0f;
        if (c->i00 != 0)
            c->i00 = 2;
    }
}


typedef struct M1Sub83 {
    uint8_t unk00[0xC];
    uint32_t flags0C;          /* +0x0C */
    float   spin10;            /* +0x10 */
    uint8_t unk14[0x24 - 0x14];
    float   vel24[4];          /* +0x24 */
    float   pos34[4];          /* +0x34 */
} M1Sub83;
typedef struct M1Step83S { uint8_t unk00[0x74]; M1Sub83 *sub74; } M1Step83S;
typedef struct M1Pos83 { uint8_t unk00[0x60]; float pos60[4]; } M1Pos83;
extern M1Pos83 *g_playerObj;
extern float m1_frameRate42C85C;
void  sub_001ADBA0(float *d, const float *s, float k);
void  sub_001AD7E0(float *out, const float *v);
float sub_001AD9D0(const float *a, const float *b);
void  sub_000F5D40(float *d, const float *s);

/* 0x0018BA50: bounce: velocity = position * -2 flattened (y = 0); if it is slower than
 * 80 * frameRate raise it to that speed; spin *= -2 clamped to -pi..pi; o flags 5, sub flag 2,
 * position = player position. */
void m1_Bounce18BA50(M1Obj83 *o, M1Step83S *h)
{
    M1Sub83 *s = h->sub74;
    float *v = s->vel24;
    float n[4];
    float len;
    float k;
    sub_001ADBA0(v, s->pos34, -2.0f);
    s->vel24[1] = 0.0f;
    sub_001AD7E0(n, v);
    len = sub_001AD9D0(n, v);
    k = m1_frameRate42C85C * 80.0f;
    if (k > len)
        sub_001ADBA0(v, n, k);
    s->spin10 = s->spin10 * -2.0f;
    if (s->spin10 > 3.1415927f)
        s->spin10 = 3.1415927f;
    else if (-3.1415927f > s->spin10)
        s->spin10 = -3.1415927f;
    o->flags10 |= 5;
    s->flags0C |= 2;
    sub_000F5D40(s->pos34, g_playerObj->pos60);
}
