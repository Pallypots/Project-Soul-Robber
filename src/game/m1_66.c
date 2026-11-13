/* Area m1, file 66: rig steps. Names inferred. */
#include <stdint.h>

typedef struct M1RigJ { uint8_t unk000[8]; uint32_t flags08; uint8_t unk00C[0x160 - 0xC]; float q160[4]; } M1RigJ;
typedef struct M1StepJ { uint8_t unk000[0x4C]; uint32_t flags4C; uint8_t unk050[0x278 - 0x50]; M1RigJ *rig278; } M1StepJ;
typedef struct M1ObjJ { uint8_t unk00[0xC]; uint32_t flags0C, flags10; } M1ObjJ;
int  sub_001456E0(void *o, void *s, int a, int b);
void sub_0001D4E0(void *o);
void sub_00137690(void *o, void *h);

/* 0x00137970: 0x1456E0(0x18) (0x1D4E0 on 1), rig quaternion +0x160 = (0, 0, 0, 1), o flags
 * |= 5, h +0x4C |= 0x70, rig flag 0x40; with rig flag 1 clears o +0xC bits 0xE0, sets o
 * flag 0x100 and rig flag 4; then 0x137690 four times. */
void m1_RigStep137970(M1ObjJ *o, M1StepJ *h)
{
    M1RigJ *r = h->rig278;
    M1RigJ *p;
    uint32_t f;
    int n;
    if (sub_001456E0(o, h, 0x18, 0) == 1)
        sub_0001D4E0(o);
    p = h->rig278;
    p->q160[2] = 0.0f;
    p->q160[1] = 0.0f;
    p->q160[0] = 0.0f;
    p->q160[3] = 1.0f;
    o->flags10 |= 5;
    h->flags4C |= 0x70;
    f = r->flags08 | 0x40;
    r->flags08 = f;
    if (f & 1) {
        o->flags0C &= ~0xE0u;
        o->flags10 |= 0x100;
        r->flags08 |= 4;
    }
    for (n = 4; n != 0; n--)
        sub_00137690(o, h);
}

typedef struct M1RigS3 { uint8_t unk00[8]; float t08; int32_t state0C; int32_t f10; } M1RigS3;
typedef struct M1StepS3 { uint8_t unk000[0x278]; M1RigS3 *rig278; } M1StepS3;
typedef struct M1ObjS3 { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x30 - 0x14]; void *anim30; } M1ObjS3;
extern float m1_frameRate42C85C;
void sub_000832D0(void *a, int v);
int  sub_000F5D00(void *o);
int  sub_000ED780(void *o);

/* 0x00179820: state 0 counts the rig timer +0x08 up from below 0, then sets o flags 0xD,
 * clip 7, clears rig +0x10 and moves on; state 1 plays clip 5 once 0xF5D00 reports done;
 * state 2 ends o (0xED780) once it is done again. */
void m1_Sequence179820(M1ObjS3 *o, M1StepS3 *h)
{
    M1RigS3 *r = h->rig278;
    switch (r->state0C) {
    case 0:
        if (r->t08 > 0.0f) {
            o->flags10 |= 0xD;
            sub_000832D0(o->anim30, 7);
            r->f10 = 0;
            r->state0C++;
        } else {
            r->t08 = m1_frameRate42C85C + r->t08;
        }
        break;
    case 1:
        if (sub_000F5D00(o) != 0) {
            sub_000832D0(o->anim30, 5);
            r->state0C++;
        }
        break;
    case 2:
        if (sub_000F5D00(o) != 0)
            sub_000ED780(o);
        break;
    }
}

typedef struct M1FadeB { int32_t state00; uint8_t unk04[0xC]; float step10; uint8_t unk14[8]; float amt1C; } M1FadeB;
void sub_000EE760(void *o, float a);
void sub_00113370(void *h, void *s);

/* 0x00147140: fade step: +0x1C += +0x10 clamped to 0..0.5, alpha 1 - amount, the step
 * drops by 0.002 down to -0.01, alpha applied (0xEE760); once the amount reaches 0 the
 * step is done (1, 0x113370), otherwise running (2). */
void m1_FadeStep147140(void *o, void *h, M1FadeB *f)
{
    float v = f->step10 + f->amt1C;
    float a;
    f->amt1C = v;
    if (v > 0.5f)
        f->amt1C = 0.5f;
    else if (0.0f > v)
        f->amt1C = 0.0f;
    a = 1.0f - f->amt1C;
    f->step10 = f->step10 - 0.002f;
    if (-0.01f > f->step10)
        f->step10 = -0.01f;
    sub_000EE760(o, a);
    if (f->amt1C <= 0.0f) {
        if (f->state00 != 0)
            f->state00 = 1;
        sub_00113370(h, f);
    } else {
        if (f->state00 != 0)
            f->state00 = 2;
    }
}

typedef struct M1RigG2 { uint8_t unk00[0x20]; float q20[4]; uint8_t unk30[0x88 - 0x30]; int32_t f88, f8C; float f90; } M1RigG2;
typedef struct M1StepG2 { uint8_t unk000[0x74]; float t74; uint8_t unk078[0x278 - 0x78]; M1RigG2 *rig278; } M1StepG2;
typedef struct M1ObjG2 { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x60 - 0x14]; float pos60[3]; } M1ObjG2;
typedef struct M1CmdG2 { uint8_t unk00[0x10]; float v10[4]; } M1CmdG2;
int      sub_00036750(void *o, int v);
int      sub_000494D0(int id, const void *pos, int c);
M1CmdG2 *sub_00113400(void *h, int v);

/* 0x00186C40: 0x1456E0(0x24), rig quaternion +0x20 = (0, 0, 0, 1), rig +0x90 = 0, rig +0x8C =
 * rig +0x88, +0x74 = 4, o flag 4, 0x36750(4), sound 0x114 at o, command 5 vector = 0. */
void m1_RigStep186C40(M1ObjG2 *o, M1StepG2 *h)
{
    M1RigG2 *r = h->rig278;
    M1RigG2 *p;
    M1CmdG2 *c;
    sub_001456E0(o, h, 0x24, 0);
    p = h->rig278;
    p->q20[2] = 0.0f;
    p->q20[1] = 0.0f;
    p->q20[0] = 0.0f;
    p->q20[3] = 1.0f;
    r->f90 = 0.0f;
    r->f8C = r->f88;
    h->t74 = 4.0f;
    o->flags10 |= 4;
    sub_00036750(o, 4);
    sub_000494D0(0x114, o->pos60, 0);
    c = sub_00113400(h, 5);
    c->v10[0] = 0.0f;
    c->v10[1] = 0.0f;
    c->v10[2] = 0.0f;
    c->v10[3] = 0.0f;
}
