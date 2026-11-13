/* Area m1, file 86: player checks and partner timers. Names inferred. */
#include <stdint.h>

typedef struct M1Pl86 { uint8_t unk00[0x20]; float *node20; uint8_t unk24[0x60 - 0x24]; float pos60[4]; } M1Pl86;
typedef struct M1Obj86 { uint8_t unk00[8]; int32_t kind08; uint8_t unk0C[0x60 - 0xC]; float pos60[4]; } M1Obj86;
extern M1Pl86 *g_playerObj;
extern uint8_t m1_stats41FEC0[];
int   sub_000CF560(void *s, int v);
float sub_001B2770(const float *a, const float *b);
void  sub_001ADBA0(float *d, const float *s, float k);
void  sub_001AD9F0(float *out, const float *a, const float *b);
void  sub_001AD7E0(float *out, const float *v);
float sub_001AD9D0(const float *a, const float *b);
float sub_001A3EE0(float a);

/* 0x001357F0: behind check (as 0x12DDE0) with a 25 range: when 0xCF560 holds and the object
 * is within 25 of the player, returns 1 when it lies within 0x1A3EE0(45) of the player's
 * back direction (flat). */
int m1_BehindPlayer1357F0(M1Obj86 *o)
{
    M1Pl86 *p = g_playerObj;
    float d;
    float b[4];
    float a[4];
    if (!sub_000CF560(m1_stats41FEC0, 0))
        return 0;
    if (sub_001B2770(o->pos60, p->pos60) >= 25.0f)
        return 0;
    sub_001ADBA0(a, p->node20 + 8, -1.0f);
    sub_001AD9F0(b, o->pos60, p->pos60);
    a[1] = 0.0f;
    b[1] = 0.0f;
    sub_001AD7E0(a, a);
    sub_001AD7E0(b, b);
    d = sub_001AD9D0(a, b);
    if (sub_001A3EE0(45.0f) > d)
        return 0;
    return 1;
}

typedef struct M1Rig86 { uint32_t unk00; uint32_t flags04; uint8_t unk08[0x2C - 8]; float t2C; float t30; } M1Rig86;
typedef struct M1Step86 {
    uint8_t unk000[0xF8];
    int32_t mode0F8;           /* +0xF8 */
    float   fFC;               /* +0xFC */
    float   f100;              /* +0x100 */
    void   *tgt104;            /* +0x104 */
    uint8_t unk108[0x278 - 0x108];
    M1Rig86 *rig278;           /* +0x278 */
} M1Step86;
extern float m1_frameRate42C85C;
float sub_001135C0(void *o, void *h);
float sub_00113570(void *o, void *h);
void *sub_000EDBE0(int a, int kind);

/* 0x0011B210: target the player (mode 1), refresh +0xFC/+0x100 (0x1135C0, 0x113570); with
 * rig flag 0x80 count +0x30 down to set flag 0x40; while the partner (kind 3 <-> 4) exists
 * count +0x2C down under flag 8 to set flag 0x10, otherwise clear 0x10, set 8, reset +0x2C. */
void m1_PartnerTimers11B210(M1Obj86 *o, M1Step86 *h)
{
    M1Rig86 *r = h->rig278;
    uint32_t f;
    int k;
    h->mode0F8 = 1;
    h->tgt104 = g_playerObj;
    h->fFC = sub_001135C0(o, h);
    h->f100 = sub_00113570(o, h);
    f = r->flags04;
    if (f & 0x80) {
        r->t30 -= m1_frameRate42C85C;
        if (0.0f >= r->t30)
            r->flags04 = f | 0x40;
    }
    switch (o->kind08) {
    case 3:
        k = 4;
        break;
    case 4:
        k = 3;
        break;
    default:
        goto none;
    }
    if (sub_000EDBE0(2, k) != 0) {
        f = r->flags04;
        if (f & 8) {
            r->t2C -= m1_frameRate42C85C;
            if (0.0f >= r->t2C)
                r->flags04 = f | 0x10;
        }
        return;
    }
none:
    r->flags04 = (r->flags04 & ~0x10u) | 8;
    r->t2C = 0.0f;
}

