/* Area m1, file 82: rig steps. Names inferred. */
#include <stdint.h>

typedef struct M1Rig82 { uint32_t unk00; uint32_t flags04; } M1Rig82;
typedef struct M1Step82 {
    uint8_t unk000[0x20];
    uint8_t b20;               /* +0x20 */
    uint8_t unk021;
    uint8_t b22;               /* +0x22 */
    uint8_t unk023[0x74 - 0x23];
    float   wait74;            /* +0x74 */
    uint8_t unk078[0x278 - 0x78];
    M1Rig82 *rig278;           /* +0x278 */
} M1Step82;
typedef struct M1Anim82 { uint8_t unk00[0xC4]; float lenC4; } M1Anim82;
typedef struct M1Clip82 { uint8_t unk00[0x14]; M1Anim82 *anim14; } M1Clip82;
typedef struct M1Obj82 { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x30 - 0x14]; M1Clip82 *clip30; } M1Obj82;
typedef struct M1Cmd82 { int32_t i00; uint8_t unk04[0x10 - 4]; float f10; } M1Cmd82;
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
int  sub_000833E0(void *a);
void sub_00113040(void *o, void *h, int state);





/* 0x00138D20: when the clip is done clear o flags 0x20 and 4, then state 0xA/0x10 (rig flag
 * 0x20000000), 0x1A (rig flag 0x40000000), 0xB (h +0x20 bit 0) or 0xC with a 180 wait. */
void m1_RigNext138D20(M1Obj82 *o, M1Step82 *h)
{
    M1Rig82 *r;
    uint32_t f;
    if (!sub_000833E0(o->clip30))
        return;
    o->flags10 &= ~0x20u;
    r = h->rig278;
    o->flags10 &= ~4u;
    f = r->flags04;
    if (f & 0x20000000) {
        r->flags04 = f & ~0x20000000u;
        sub_00113040(o, h, (-((h->b20 & 1) != 0) & 6) + 0xA);   /* 0x10 or 0xA */
    } else if (f & 0x40000000) {
        r->flags04 = f & ~0x40000000u;
        sub_00113040(o, h, 0x1A);
    } else if (h->b20 & 1) {
        sub_00113040(o, h, 0xB);
    } else {
        h->wait74 = 180.0f / m1_frameTime42C858 * m1_frameRate42C85C;
        sub_00113040(o, h, 0xC);
    }
}


typedef struct M1Scr82 { uint8_t unk000[0x1A8]; int16_t step1A8; } M1Scr82;
extern M1Scr82 *m1_scr3F6130;
extern uint8_t r2_center3194C8[];
typedef struct M1Turn82 { uint8_t unk00[0x54]; float yaw54; } M1Turn82;
float sub_000F7720(void *o, const void *pt);
int  sub_000F5D00(void *o);
void sub_00101240(int v);
void sub_00101280(int v);
void sub_000F5ED0(float *a);

/* 0x00103770: scripted turn: step 0 runs 0x101280(0x20) and advances; step 1 turns the object
 * toward point 0x3194C8 by at most 1 degree per frame, and when already facing it and
 * 0xF5D00 holds runs 0x101240(8). */
void m1_ScriptTurn103770(M1Turn82 *o)
{
    int16_t *step = &m1_scr3F6130->step1A8;
    float k, d, a;
    switch (*step) {
    case 0:
        sub_00101280(0x20);
        (*step)++;
        break;
    case 1:
        k = m1_frameTime42C858 * 0.017453292f;
        d = sub_000F7720(o, r2_center3194C8);
        a = d;
        if (d > k)
            a = k;
        else if (0.0f - k > d)
            a = 0.0f - k;
        else if (sub_000F5D00(o))
            sub_00101240(8);
        o->yaw54 += a;
        sub_000F5ED0(&o->yaw54);
        break;
    }
}


