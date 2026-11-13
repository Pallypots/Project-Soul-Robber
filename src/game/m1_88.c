/* Area m1, file 88: rig steps. Names inferred. */
#include <stdint.h>

typedef struct M1Rig88 { uint8_t unk000[0xC]; uint32_t flags0C; uint8_t unk010[0x164 - 0x10]; float q164[4]; } M1Rig88;
typedef struct M1Step88 { uint8_t unk000[0x278]; M1Rig88 *rig278; } M1Step88;
typedef struct M1Obj88 { uint8_t unk00[0xC]; uint32_t flags0C; uint32_t flags10; } M1Obj88;
typedef struct M1Cmd88 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Cmd88;
int  sub_001456E0(void *o, void *h, int a, int b);
void sub_0001D4E0(void *o);
M1Cmd88 *sub_00113400(void *h, int v);
void sub_00134DB0(void *o, void *h);

/* 0x00135170: enter state 0x18, reset the rig quaternion (+0x164), o flags 5, rig +0xC |=
 * 0x80 (flag 1: clear o bits 0xE0, o +0x10 |= 0x100, rig +0xC |= 4), o flag 4, command 6 =
 * (1/12, 0, 0, 0), then three steps of 0x134DB0. */
void m1_RigBurst135170(M1Obj88 *o, M1Step88 *h)
{
    M1Rig88 *r = h->rig278;
    M1Rig88 *p;
    M1Cmd88 *c;
    uint32_t f;
    int n;
    if (sub_001456E0(o, h, 0x18, 0) == 1)
        sub_0001D4E0(o);
    p = h->rig278;
    p->q164[2] = 0.0f;
    p->q164[1] = 0.0f;
    p->q164[0] = 0.0f;
    p->q164[3] = 1.0f;
    o->flags10 |= 5;
    f = r->flags0C | 0x80;
    r->flags0C = f;
    if (f & 1) {
        o->flags0C &= ~0xE0u;
        o->flags10 |= 0x100;
        r->flags0C |= 4;
    }
    o->flags10 |= 4;
    c = sub_00113400(h, 6);
    c->f10 = 0.083333336f;
    c->f14 = 0.0f;
    c->f18 = 0.0f;
    c->f1C = 0.0f;
    for (n = 3; n != 0; n--)
        sub_00134DB0(o, h);
}

typedef int (*M1Check88)(void *o, void *h, const void *tbl);
extern M1Check88 r3b_disp31DBBC[];
extern const uint8_t r3b_recs279848[];
typedef struct M1Step88P {
    uint8_t unk000[0x20];
    uint8_t b20;               /* +0x20 */
    uint8_t unk021[0x4C - 0x21];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x58 - 0x50];
    int32_t phase58;           /* +0x58 */
    float   t5C;               /* +0x5C */
    uint8_t unk060[0x74 - 0x60];
    float   wait74;            /* +0x74 */
    uint8_t unk078[0x100 - 0x78];
    float   f100;              /* +0x100 */
} M1Step88P;
typedef struct M1Obj88P { uint8_t unk00[0x30]; void *anim30; } M1Obj88P;
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
int  sub_000833E0(void *a);
void sub_00142270(void *o, void *h);
void sub_00113040(void *o, void *h, int state);

/* 0x00144720: phase 0 after 15 frames runs 0x142270 and goes to phase 1; phase 1 when the clip
 * ends picks state 3 (check 0 hits), 8 (h +0x20 bit 0 and +0x100 under 45) or 5 (else, with a
 * 60-frame wait when bit 0 is clear), with h +0x4C flag 0x10. */
void m1_RigPick144720(M1Obj88P *o, M1Step88P *h)
{
    int s;
    switch (h->phase58) {
    case 0:
        if (h->t5C >= 15.0f / m1_frameTime42C858 * m1_frameRate42C85C) {
            sub_00142270(o, h);
            h->phase58++;
        }
        break;
    case 1:
        if (sub_000833E0(o->anim30)) {
            s = 3;
            if (!r3b_disp31DBBC[0](o, h, r3b_recs279848)) {
                s = 8;
                if (!(h->b20 & 1)) {
                    h->wait74 = 60.0f / m1_frameTime42C858 * m1_frameRate42C85C;
                    s = 5;
                } else if (!(45.0f > h->f100)) {
                    s = 5;
                }
            }
            h->flags4C |= 0x10;
            sub_00113040(o, h, s);
        }
        break;
    }
}
