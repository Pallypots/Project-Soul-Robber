/* Area m1, file 242: actor state pickers (register-argument callers per docs/verification.md). Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1E242 { uint8_t unk00[0x180]; float t180; } M1E242;
typedef struct M1O242 { uint8_t unk00[0x60]; uint8_t pos60[0xC8]; uint8_t flags128; } M1O242;
typedef struct M1S242 { uint8_t unk00[0x104]; uint8_t v104[0x174]; M1E242 *ext278; } M1S242;
extern float a50_frameSeconds;
int  r2_RunSteps31C510(int table, M1O242 *obj, M1S242 *act);   /* regargs: table=EAX obj=EBX act=EDI */
void r3_SetStateA(M1O242 *obj, M1S242 *act, int state);        /* regargs: obj=EBX act=EDI state=stack */
void r3_SetStateA2(M1O242 *obj, M1S242 *act, int state);       /* same function (alias stops cl merging calls) */
float sub_001B2770(const void *a, const void *b);

/* 0x00132130: pick the next state: scripts 1-4 -> 15/16/17/14; count t180 down to 0; within 20 of the target -> 8;
   flag 1 at +0x128 -> 14 (calls 0x12DC90 with table=EAX obj=EBX act=EDI, 0x131310 with obj=EBX act=EDI). */
void m1_PickState132130(M1O242 *o, M1S242 *s)
{
    M1E242 *e = s->ext278;
    if (r2_RunSteps31C510(1, o, s)) {
        r3_SetStateA(o, s, 15);
        return;
    }
    if (r2_RunSteps31C510(2, o, s)) {
        r3_SetStateA(o, s, 16);
        return;
    }
    if (r2_RunSteps31C510(3, o, s)) {
        r3_SetStateA(o, s, 17);
        return;
    }
    if (r2_RunSteps31C510(4, o, s)) {
        r3_SetStateA(o, s, 14);
        return;
    }
    e->t180 -= a50_frameSeconds;
    if (_mm_comige_ss(_mm_setzero_ps(), _mm_load_ss(&e->t180)))
        e->t180 = 0.0f;
    if (sub_001B2770(o->pos60, s->v104) <= 20.0f) {
        r3_SetStateA(o, s, 8);
        return;
    }
    if (o->flags128 & 1)
        r3_SetStateA2(o, s, 14);
}

typedef struct M1RE242 { uint8_t unk00[4]; uint32_t flags4; uint8_t unk08[0x3C]; float t44; } M1RE242;
typedef struct M1RT242 { uint8_t unk00[0x60]; uint8_t pos60[0x10]; } M1RT242;
typedef struct M1RS242 { uint8_t unk00[0x74]; float t74; uint8_t unk78[0x8C]; M1RT242 *tgt104; uint8_t unk108[0x170];
    M1RE242 *ext278; } M1RS242;
int  r2_RunSteps31A380(int idx, M1O242 *a, M1RS242 *b);   /* regargs: idx=EAX a=EBX b=EDI */
void sub_00117580(M1O242 *o, int32_t mode, M1RS242 *s);    /* regargs: s=EDI */
void sub_00117580d(M1O242 *o, int32_t mode, M1RS242 *s);   /* same function (alias stops cl merging calls) */

/* 0x00118640: pick the next mode: scripts 0/1/2 -> 10/11/12; unless flag 0x1000, count t44 down (0.5 per second) and
   go to 0x12 within 10 units of the target; then mode 1 when t74 has run out (calls 0x114D10 with idx=EAX a=EBX
   b=EDI, 0x117580 with s=EDI). */
void m1_PickMode118640(M1O242 *o, M1RS242 *s)
{
    M1RE242 *e = s->ext278;
    if (r2_RunSteps31A380(0, o, s)) {
        sub_00117580(o, 10, s);
        return;
    }
    if (r2_RunSteps31A380(1, o, s)) {
        sub_00117580(o, 11, s);
        return;
    }
    if (r2_RunSteps31A380(2, o, s)) {
        sub_00117580(o, 12, s);
        return;
    }
    if (!(e->flags4 & 0x1000)) {
        e->t44 -= a50_frameSeconds * 0.5f;
        if (_mm_comige_ss(_mm_setzero_ps(), _mm_load_ss(&e->t44)))
            e->t44 = 0.0f;
        if (sub_001B2770(o->pos60, s->tgt104->pos60) <= 10.0f) {
            sub_00117580(o, 0x12, s);
            return;
        }
    }
    if (s->t74 <= 0.0f)
        sub_00117580d(o, 1, s);
}

typedef struct M1HS242 { uint8_t unk00[0x270]; float max270, hp274; M1RE242 *ext278; } M1HS242;
int  r2_RunSteps31A380b(int idx, M1O242 *a, M1HS242 *b);   /* 0x114D10 regargs: idx=EAX a=EBX b=EDI */
void sub_00117580h(M1O242 *o, int32_t mode, M1HS242 *s);    /* 0x117580 regargs: s=EDI */
void sub_00117580i(M1O242 *o, int32_t mode, M1HS242 *s);    /* same function (aliases stop cl merging calls) */
int sub_001C7EE1(void);   /* rand */

/* 0x00117AE0: pick the next mode: scripts 0/2/4 -> 10/12/17; with flag 0x40000 a 20% (above half health) or 10%
   (below) chance of mode 15; otherwise mode 2 (calls 0x114D10 with idx=EAX a=EBX b=EDI, 0x117580 with s=EDI). */
void m1_PickMode117AE0(M1O242 *o, M1HS242 *s)
{
    M1RE242 *e = s->ext278;
    if (r2_RunSteps31A380b(0, o, s)) {
        sub_00117580h(o, 10, s);
        return;
    }
    if (r2_RunSteps31A380b(2, o, s)) {
        sub_00117580h(o, 12, s);
        return;
    }
    if (r2_RunSteps31A380b(4, o, s)) {
        sub_00117580h(o, 0x11, s);
        return;
    }
    if (s->hp274 >= s->max270 * 0.5f) {
        if ((e->flags4 & 0x40000) && sub_001C7EE1() % 100 < 20) {
            sub_00117580h(o, 15, s);
            return;
        }
    } else if ((e->flags4 & 0x40000) && sub_001C7EE1() % 100 < 10) {
        sub_00117580i(o, 15, s);
        return;
    }
    sub_00117580h(o, 2, s);
}

typedef struct M1QS242 { uint8_t unk00[0x104]; uint8_t v104[0x174]; M1RE242 *ext278; } M1QS242;
int  r2_RunSteps31A380c(int idx, M1O242 *a, M1QS242 *b);   /* 0x114D10 regargs: idx=EAX a=EBX b=EDI */
void sub_00117580q(M1O242 *o, int32_t mode, M1QS242 *s);    /* 0x117580 regargs: s=EDI */
void sub_00117580r(M1O242 *o, int32_t mode, M1QS242 *s);    /* same function (aliases stop cl merging calls) */

/* 0x001179C0: pick the next mode: scripts 0-3 -> 10/11/12/9; count t44 down to 0; within 15 of the target -> 4;
   flag 1 at +0x128 -> 9 (calls 0x114D10 with idx=EAX a=EBX b=EDI, 0x117580 with s=EDI). */
void m1_PickMode1179C0(M1O242 *o, M1QS242 *s)
{
    M1RE242 *e = s->ext278;
    if (r2_RunSteps31A380c(0, o, s)) {
        sub_00117580q(o, 10, s);
        return;
    }
    if (r2_RunSteps31A380c(1, o, s)) {
        sub_00117580q(o, 11, s);
        return;
    }
    if (r2_RunSteps31A380c(2, o, s)) {
        sub_00117580q(o, 12, s);
        return;
    }
    if (r2_RunSteps31A380c(3, o, s)) {
        sub_00117580q(o, 9, s);
        return;
    }
    e->t44 -= a50_frameSeconds;
    if (_mm_comige_ss(_mm_setzero_ps(), _mm_load_ss(&e->t44)))
        e->t44 = 0.0f;
    if (sub_001B2770(o->pos60, s->v104) <= 15.0f) {
        sub_00117580q(o, 4, s);
        return;
    }
    if (o->flags128 & 1)
        sub_00117580r(o, 9, s);
}

/* 0x00131D40: as 0x132130 but within 20 of the target -> state 4. */
void m1_PickState131D40(M1O242 *o, M1S242 *s)
{
    M1E242 *e = s->ext278;
    if (r2_RunSteps31C510(1, o, s)) {
        r3_SetStateA(o, s, 15);
        return;
    }
    if (r2_RunSteps31C510(2, o, s)) {
        r3_SetStateA(o, s, 16);
        return;
    }
    if (r2_RunSteps31C510(3, o, s)) {
        r3_SetStateA(o, s, 17);
        return;
    }
    if (r2_RunSteps31C510(4, o, s)) {
        r3_SetStateA(o, s, 14);
        return;
    }
    e->t180 -= a50_frameSeconds;
    if (_mm_comige_ss(_mm_setzero_ps(), _mm_load_ss(&e->t180)))
        e->t180 = 0.0f;
    if (sub_001B2770(o->pos60, s->v104) <= 20.0f) {
        r3_SetStateA(o, s, 4);
        return;
    }
    if (o->flags128 & 1)
        r3_SetStateA2(o, s, 14);
}
