/* Area m1, file 94: sway variants. Names inferred. */
#include <stdint.h>

typedef struct M1Rig94 { uint8_t unk000[8]; uint32_t flags08; uint8_t unk00C[0x160 - 0xC]; float q160[4]; } M1Rig94;
typedef struct M1Step94 { uint8_t unk000[0x4C]; uint32_t flags4C; uint8_t unk050[0x278 - 0x50]; M1Rig94 *rig278; } M1Step94;
typedef struct M1Obj94 { uint8_t unk00[0xC]; uint32_t flags0C; uint32_t flags10; } M1Obj94;
typedef struct M1Cmd94 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Cmd94;
extern float m1_frameTime42C858;
int  sub_001456E0(void *o, void *h, int a, int b);
void sub_0001D4E0(void *o);
M1Cmd94 *sub_00113400(void *h, int v);

/* 0x00136CD0: sway (rig quaternion +0x160), state 0x17, o flags 5, clear o bits 0xE0,
 * h +0x4C |= 0x70, rig +8 clears 0x200 sets 4, +-5 degrees at frameTime * pi/48. */
void m1_Sway136CD0(M1Obj94 *o, M1Step94 *h)
{
    M1Rig94 *r = h->rig278;
    M1Rig94 *p;
    M1Cmd94 *c;
    float t;
    if (sub_001456E0(o, h, 0x17, 0) == 1)
        sub_0001D4E0(o);
    p = h->rig278;
    p->q160[2] = 0.0f;
    p->q160[1] = 0.0f;
    p->q160[0] = 0.0f;
    p->q160[3] = 1.0f;
    o->flags10 |= 5;
    o->flags0C &= ~0xE0u;
    h->flags4C |= 0x70;
    r->flags08 = (r->flags08 & ~0x200u) | 4;
    t = m1_frameTime42C858 * 0.065449849f;
    c = sub_00113400(h, 1);
    c->f10 = 0.087266468f;
    c->f14 = -0.087266468f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
}

