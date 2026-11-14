/* Area m1, file 105: rig setups. Names inferred. */
#include <stdint.h>

typedef struct M1Rig105 {
    uint8_t unk00[4];
    float   f04;               /* +0x04 */
    float   f08;               /* +0x08 */
    float   rate0C;            /* +0x0C */
    float   f10;               /* +0x10 */
    uint8_t unk14[0x24 - 0x14];
    float   q24[4];            /* +0x24 */
    uint8_t unk34[0x38 - 0x34];
    void   *fx38;              /* +0x38 */
    uint8_t unk3C[0x40 - 0x3C];
    uint32_t flags40;          /* +0x40 */
} M1Rig105;
typedef struct M1Step105 { uint8_t unk000[0x4C]; uint32_t flags4C; uint8_t unk050[0x54 - 0x50]; int32_t i54; uint8_t unk058[0x278 - 0x58]; M1Rig105 *rig278; } M1Step105;
typedef struct M1Cmd105 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Cmd105;
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
uint32_t sub_00185420(void *o);
int  sub_001456E0(void *o, void *h, int a, int b);
void *sub_00036750(void *o, int b);
M1Cmd105 *sub_00113400(void *h, int v);
void sub_00147FD0(void *fx, int v);

/* 0x00157590: enter state 0x15 (0x185420 under 3 and +0x54 not 0x10) or 0x12, reset the rig
 * quaternion, rig +0xC = frameTime * 0.005, +4 = -15, +8 = 10 * frameRate, clear h +0x4C bits
 * 0x70, rig +0x40 clears 0x400 sets 0x80, effect 1, command 4 = (0.1, 0.1, 2, 1); flag 0x1000
 * (cleared) runs 0x147FD0(+0x38, 3). */
void m1_RigSlide157590(void *o, M1Step105 *h)
{
    M1Rig105 *r = h->rig278;
    M1Cmd105 *c;
    uint32_t f;
    sub_001456E0(o, h, (sub_00185420(o) < 3 && h->i54 != 0x10) ? 0x15 : 0x12, 0);
    r->q24[2] = 0.0f;
    r->q24[1] = 0.0f;
    r->q24[0] = 0.0f;
    r->f10 = 0.0f;
    r->rate0C = m1_frameTime42C858 * 0.005f;
    r->q24[3] = 1.0f;
    r->f04 = -15.0f;
    r->f08 = m1_frameRate42C85C * 10.0f;
    h->flags4C &= ~0x70u;
    r->flags40 = (r->flags40 & ~0x400u) | 0x80;
    sub_00036750(o, 1);
    c = sub_00113400(h, 4);
    c->f10 = 0.1f;
    c->f14 = 0.1f;
    c->f18 = 2.0f;
    c->f1C = 1.0f;
    f = r->flags40;
    if (f & 0x1000) {
        r->flags40 = f & ~0x1000u;
        sub_00147FD0(r->fx38, 3);
    }
}


typedef struct M1Part105 { uint8_t a00[0x10]; uint8_t b10[0x340 - 0x10]; } M1Part105;
extern M1Part105 m1_parts3F6170[6];
extern int32_t r2e_g3F74F0, r2e_g3F74F4, m1_g3F74F8, r3b_items3F74FC, r2e_g3F616C, r2e_state3F7500, m1_maxN3F6168;
extern float b10_f3F7504;
void sub_0001D8B0(void *p, int kind);
int sub_00137C20(void); int sub_0013D2E0(void); int sub_001421B0(void); int sub_00119F20(void);
int sub_0011E010(void); int sub_001550D0(void); int sub_00146090(void); int sub_0012D660(void);
int sub_00135480(void); int sub_00114640(void);

#define M1_MAXN(f) { int n_ = f(); if (!(m1_maxN3F6168 > n_)) m1_maxN3F6168 = n_; }
/* 0x00112490: enemy system reset: clear the globals, reinit the six parts (0x1D8B0 kinds 4
 * and 13), then run every enemy family reset and keep the largest count they return in
 * 0x3F6168. */
void m1_EnemyReset112490(void)
{
    int i;
    r2e_g3F74F0 = 0;
    r2e_g3F74F4 = 0;
    m1_g3F74F8 = 0;
    r3b_items3F74FC = 0;
    r2e_g3F616C = 0;
    for (i = 0; i < 6; i++) {
        sub_0001D8B0(m1_parts3F6170[i].a00, 4);
        sub_0001D8B0(m1_parts3F6170[i].b10, 0xD);
    }
    r2e_state3F7500 = 0;
    b10_f3F7504 = 0.0f;
    m1_maxN3F6168 = 0;
    M1_MAXN(sub_00137C20)
    M1_MAXN(sub_0013D2E0)
    M1_MAXN(sub_001421B0)
    M1_MAXN(sub_00119F20)
    M1_MAXN(sub_0011E010)
    M1_MAXN(sub_001550D0)
    M1_MAXN(sub_00146090)
    M1_MAXN(sub_0012D660)
    M1_MAXN(sub_00135480)
    M1_MAXN(sub_00114640)
}
