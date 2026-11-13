/* Area m1, file 91: sway variants. Names inferred. */
#include <stdint.h>

typedef struct M1Rig91 {
    uint8_t unk00[0xC];
    float   rate0C;            /* +0x0C */
    float   f10;               /* +0x10 */
    uint8_t unk14[0x24 - 0x14];
    float   q24[4];            /* +0x24 */
    uint8_t unk34[0x40 - 0x34];
    uint32_t flags40;          /* +0x40 */
} M1Rig91;
typedef struct M1Step91 { uint8_t unk000[0x4C]; uint32_t flags4C; uint8_t unk050[0x278 - 0x50]; M1Rig91 *rig278; } M1Step91;
typedef struct M1Obj91 { uint8_t unk00[0x10]; uint32_t flags10; } M1Obj91;
typedef struct M1Cmd91 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Cmd91;
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
int  sub_001456E0(void *o, void *h, int a, int b);
M1Cmd91 *sub_00113400(void *h, int v);

/* 0x00156C10: enter state 3, rig quaternion z = 30 * frameRate, rig +0xC = frameTime * 0.005,
 * o flag 0x20, h +0x4C |= 0x70, rig flag 0x200, +-30 degree sway at 2 degrees/frame. */
void m1_Sway156C10(M1Obj91 *o, M1Step91 *h)
{
    M1Rig91 *r = h->rig278;
    M1Cmd91 *c;
    float t;
    sub_001456E0(o, h, 3, 0);
    r->q24[1] = 0.0f;
    r->q24[0] = 0.0f;
    r->f10 = 0.0f;
    r->rate0C = m1_frameTime42C858 * 0.005f;
    r->q24[2] = 0.0f - m1_frameRate42C85C * -30.0f;
    r->q24[3] = 1.0f;
    o->flags10 |= 0x20;
    h->flags4C |= 0x70;
    r->flags40 |= 0x200;
    t = m1_frameTime42C858 * 0.034906585f;
    c = sub_00113400(h, 1);
    c->f10 = 0.52359879f;
    c->f14 = -0.52359879f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
}


typedef struct M1Rig91C { uint32_t unk00; uint32_t flags04; } M1Rig91C;
typedef struct M1Step91C {
    int32_t kind00;            /* +0x00 */
    uint8_t unk004[0x6C - 4];
    int32_t snd6C;             /* +0x6C */
    uint8_t unk070[0x74 - 0x70];
    float   wait74;            /* +0x74 */
    uint8_t unk078[0x278 - 0x78];
    M1Rig91C *rig278;          /* +0x278 */
} M1Step91C;
typedef struct M1Obj91C { uint8_t unk00[0xC]; uint8_t b0C; uint8_t unk0D[0x60 - 0xD]; float pos60[4]; } M1Obj91C;
M1Obj91C *sub_000EDC20(int a, int b);
M1Step91C *sub_0001D960(void *o, int kind);
void sub_00048250(int snd);
int  sub_00049700(int id, int r, int g, int b, const void *pos, int a, float size, int c);

/* 0x00184040: signal the active kind 4/4 object: mode 0 swaps its sound for 0x326 and adds
 * 5 to its wait, mode 1 starts sound 0x325, mode 2 sets rig flag 4. Spins on a missing or
 * wrong component 6 or rig. */
void m1_Signal184040(int mode)
{
    M1Obj91C *t = sub_000EDC20(4, 4);
    M1Step91C *h;
    M1Rig91C *r;
    if (t == 0 || !(t->b0C & 1))
        return;
    h = sub_0001D960(t, 6);
    if (h == 0)
        for (;;) ;
    if (h->kind00 != 6)
        for (;;) ;
    r = h->rig278;
    if (r == 0)
        for (;;) ;
    switch (mode) {
    case 0:
        sub_00048250(h->snd6C);
        h->snd6C = sub_00049700(0x326, 0x80, 0x80, 0x80, t->pos60, 0, 500.0f, 0);
        h->wait74 += 5.0f;
        break;
    case 1:
        h->snd6C = sub_00049700(0x325, 0x80, 0x80, 0x80, t->pos60, 0, 500.0f, 0);
        break;
    case 2:
        r->flags04 |= 4;
        break;
    }
}

typedef int (*M1Check91)(void *o, void *h, const void *tbl);
extern M1Check91 m1_checkFn31B0C8;
extern const uint8_t m1_checkTbl2795A8[];
typedef struct M1Step91D {
    uint8_t unk000[0x58];
    int32_t phase58;           /* +0x58 */
    uint8_t unk05C[0x68 - 0x5C];
    float   t68;               /* +0x68 */
    uint8_t unk06C[0x74 - 0x6C];
    float   wait74;            /* +0x74 */
    uint8_t unk078[0x278 - 0x78];
    M1Rig91C *rig278;          /* +0x278 */
} M1Step91D;
typedef struct M1Obj91D { uint8_t unk00[0x30]; void *anim30; } M1Obj91D;
int  sub_000833E0(void *a);
void sub_00113040(void *o, void *h, int state);

/* 0x0011D8A0: phase 0 after 38 frames clears rig flag 1 and goes to phase 1; phase 1 on clip
 * end: rig flag 0x10 -> state 5 with no wait, flag 0x40 -> state 4, check 0x31B0C8 -> state
 * 0xF, else state 5 with a 30-frame wait. */
void m1_RigNext11D8A0(M1Obj91D *o, M1Step91D *h)
{
    uint32_t f;
    float w;
    switch (h->phase58) {
    case 0:
        if (h->t68 >= 38.0f / m1_frameTime42C858 * m1_frameRate42C85C) {
            h->rig278->flags04 &= ~1u;
            h->phase58++;
        }
        break;
    case 1:
        if (sub_000833E0(o->anim30)) {
            f = h->rig278->flags04;
            w = 0.0f;
            if (!(f & 0x10)) {
                if (f & 0x40) {
                    sub_00113040(o, h, 4);
                    return;
                }
                if (m1_checkFn31B0C8(o, h, m1_checkTbl2795A8)) {
                    sub_00113040(o, h, 0xF);
                    return;
                }
                w = 30.0f / m1_frameTime42C858 * m1_frameRate42C85C;
            }
            h->wait74 = w;
            sub_00113040(o, h, 5);
        }
        break;
    }
}
