/* Area m1, file 243: enemy random-choice pickers (register-argument callers per docs/verification.md). Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1O243 { uint8_t unk00[0x60]; uint8_t pos60[0x10]; } M1O243;
typedef struct M1S243 { uint8_t unk00[0x58]; int32_t st58; uint8_t unk5C[0x18]; float t74; uint8_t unk78[0x1F8];
    float max270, hp274; } M1S243;
int  r2_RunSteps31A380(int idx, M1O243 *a, M1S243 *b);   /* regargs: idx=EAX a=EBX b=EDI */
void sub_00117580(M1O243 *o, int32_t mode, M1S243 *s);    /* regargs: s=EDI */
void sub_00117580d(M1O243 *o, int32_t mode, M1S243 *s);   /* same function (aliases stop cl merging calls) */
void sub_00117580h(M1O243 *o, int32_t mode, M1S243 *s);
void sub_00117580i(M1O243 *o, int32_t mode, M1S243 *s);
int sub_001C7EE1(void);   /* rand */

/* 0x00117D50: pick the next mode: scripts 0/2/4 -> 10/12/17; step 0 rolls 0-99: below 40 (30 when under half health)
   -> mode 2, below 55 (45) -> mode 8, else advance; step 1 when t74 runs out -> mode 8 or 1 at random (calls 0x114D10
   with idx=EAX a=EBX b=EDI, 0x117580 with s=EDI). */
void m1_Roll117D50(M1O243 *o, M1S243 *s)
{
    int r;
    if (r2_RunSteps31A380(0, o, s)) {
        sub_00117580(o, 10, s);
        return;
    }
    if (r2_RunSteps31A380(2, o, s)) {
        sub_00117580(o, 12, s);
        return;
    }
    if (r2_RunSteps31A380(4, o, s)) {
        sub_00117580(o, 0x11, s);
        return;
    }
    switch (s->st58) {
    case 0:
        r = sub_001C7EE1() % 100;
        if (s->hp274 >= s->max270 * 0.5f) {
            if (r < 40)
                goto two;
            if (r >= 55)
                goto next;
        } else {
            if (r < 30) {
two:
                sub_00117580d(o, 2, s);
                return;
            }
            if (r >= 45)
                goto next;
        }
        sub_00117580h(o, 8, s);
        return;
next:
        s->st58++;
        return;
    case 1:
        if (s->t74 <= 0.0f) {
            if (sub_001C7EE1() & 1) {
                sub_00117580i(o, 8, s);
                return;
            }
            sub_00117580(o, 1, s);
        }
        return;
    }
}

int  r2_RunSteps31C510(int table, M1O243 *obj, M1S243 *act);   /* regargs: table=EAX obj=EBX act=EDI */
void r3_SetStateA(M1O243 *obj, M1S243 *act, int state);        /* regargs: obj=EBX act=EDI state=stack */
void r3_SetStateA2(M1O243 *obj, M1S243 *act, int state);       /* same function (aliases stop cl merging calls) */
void r3_SetStateA3(M1O243 *obj, M1S243 *act, int state);

/* 0x00132420: pick the next state: scripts 1/3 -> 15/17; step 0 rolls 0-99: above half health below 40 -> 0x15,
   below 60 -> 6, else advance; under half health below 50 -> 0x15, below 60 -> 6, below 65 -> 12, else advance;
   step 1 when t74 runs out -> 12 or 5 at random (calls 0x12DC90 with table=EAX obj=EBX act=EDI, 0x131310 with obj=EBX
   act=EDI). */
void m1_Roll132420(M1O243 *o, M1S243 *s)
{
    int r;
    if (r2_RunSteps31C510(1, o, s)) {
        r3_SetStateA(o, s, 15);
        return;
    }
    if (r2_RunSteps31C510(3, o, s)) {
        r3_SetStateA(o, s, 0x11);
        return;
    }
    switch (s->st58) {
    case 0:
        r = sub_001C7EE1() % 100;
        if (s->hp274 >= s->max270 * 0.5f) {
            if (r < 40)
                goto s21;
            if (r < 55)
                goto s6;
            if (r >= 60)
                goto next;
s6:
            r3_SetStateA2(o, s, 6);
            return;
        }
        if (r < 50) {
s21:
            r3_SetStateA3(o, s, 0x15);
            return;
        }
        if (r < 60)
            goto s6;
        if (r >= 65)
            goto next;
        r3_SetStateA(o, s, 12);
        return;
next:
        s->st58++;
        return;
    case 1:
        if (s->t74 <= 0.0f) {
            if (sub_001C7EE1() & 1) {
                r3_SetStateA2(o, s, 12);
                return;
            }
            r3_SetStateA(o, s, 5);
        }
        return;
    }
}

typedef struct M1TE243 { uint8_t unk00[0xC]; uint32_t flagsC; uint8_t unk10[0x16C]; float t17C; } M1TE243;
typedef struct M1TS243 { uint8_t unk00[0x74]; float t74; uint8_t unk78[0x200]; M1TE243 *ext278; } M1TS243;
int  r2_RunSteps31C510b(int table, M1O243 *obj, M1TS243 *act);   /* 0x12DC90 regargs: table=EAX obj=EBX act=EDI */
void r3_SetStateA4(M1O243 *obj, M1TS243 *act, int state);        /* 0x131310 regargs: obj=EBX act=EDI */
void r3_SetStateA5(M1O243 *obj, M1TS243 *act, int state);        /* same function (aliases stop cl merging calls) */

/* 0x00131A70: pick the next state: script 0 or an expired t17C -> clear flag 0x200 and state 2; scripts 1/3 ->
   15/17; once t74 runs out: flag 0x800 -> 13, 1 in 4 -> 12, else wait 3 more (50%) or 1 in 4 -> 18, else wait 5
   (calls 0x12DC90 with table=EAX obj=EBX act=EDI, 0x131310 with obj=EBX act=EDI). */
void m1_Roll131A70(M1O243 *o, M1TS243 *s)
{
    M1TE243 *e = s->ext278;
    if (r2_RunSteps31C510b(0, o, s)) {
        e->flagsC &= ~0x200u;
        r3_SetStateA4(o, s, 2);
        return;
    }
    if (r2_RunSteps31C510b(1, o, s)) {
        r3_SetStateA4(o, s, 15);
        return;
    }
    if (r2_RunSteps31C510b(3, o, s)) {
        r3_SetStateA4(o, s, 0x11);
        return;
    }
    if (e->t17C <= 0.0f) {
        e->flagsC &= ~0x200u;
        r3_SetStateA5(o, s, 2);
        return;
    }
    if (!_mm_comige_ss(_mm_setzero_ps(), _mm_load_ss(&s->t74)))
        return;
    if (e->flagsC & 0x800) {
        r3_SetStateA4(o, s, 13);
        return;
    }
    if (!(sub_001C7EE1() & 3)) {
        r3_SetStateA5(o, s, 12);
        return;
    }
    if (sub_001C7EE1() & 1) {
        s->t74 = 3.0f;
        return;
    }
    if (!(sub_001C7EE1() & 3)) {
        r3_SetStateA4(o, s, 0x12);
        return;
    }
    s->t74 = 5.0f;
}

/* 0x00132300: as 0x132420 with other odds: above half health below 30 -> 0x15, below 75 -> 6, below 80 -> 12, else
   advance; under half below 50 -> 0x15, below 90 -> 6, below 95 -> 12, else advance. */
void m1_Roll132300(M1O243 *o, M1S243 *s)
{
    int r;
    if (r2_RunSteps31C510(1, o, s)) {
        r3_SetStateA(o, s, 15);
        return;
    }
    if (r2_RunSteps31C510(3, o, s)) {
        r3_SetStateA(o, s, 0x11);
        return;
    }
    switch (s->st58) {
    case 0:
        r = sub_001C7EE1() % 100;
        if (s->hp274 >= s->max270 * 0.5f) {
            if (r < 30)
                goto s21;
            if (r < 60)
                goto s6;
            if (r < 75)
                goto s6;
            if (r >= 80)
                goto next;
            goto s12;
        }
        if (r < 50) {
s21:
            r3_SetStateA3(o, s, 0x15);
            return;
        }
        if (r < 80)
            goto s6;
        if (r >= 90)
            goto t95;
s6:
        r3_SetStateA2(o, s, 6);
        return;
t95:
        if (r >= 95)
            goto next;
s12:
        r3_SetStateA(o, s, 12);
        return;
next:
        s->st58++;
        return;
    case 1:
        if (s->t74 <= 0.0f) {
            if (sub_001C7EE1() & 1) {
                r3_SetStateA2(o, s, 12);
                return;
            }
            r3_SetStateA(o, s, 5);
        }
        return;
    }
}

typedef struct M1UE243 { uint8_t unk00[8]; uint32_t flags8; uint8_t unk0C[0x16C]; float t178; } M1UE243;
typedef struct M1US243 { uint8_t unk00[0x74]; float t74; uint8_t unk78[0x200]; M1UE243 *ext278; } M1US243;
int  r3_CheckConds135730(int table, M1O243 *obj, M1US243 *act);   /* regargs: table=EAX obj=EBX act=EDI */
void r3_SetStateB(M1O243 *obj, M1US243 *act, int state);          /* regargs: obj=ESI act=EDI state=stack */
void r3_SetStateB2(M1O243 *obj, M1US243 *act, int state);         /* same function (aliases stop cl merging calls) */
void r3_SetStateB3(M1O243 *obj, M1US243 *act, int state);

/* 0x00136140: pick the next state: table 0 or an expired t178 -> clear flag 0x80 and state 4; tables 1/2 -> 10/11;
   once t74 runs out: 50% -> 8 (another 50% and flag 0x200) or 7; else wait 3 (50%), 1 in 4 -> 12, else wait 5
   (calls 0x135730 with table=EAX obj=EBX act=EDI, 0x135A70 with obj=ESI act=EDI). */
void m1_Roll136140(M1O243 *o, M1US243 *s)
{
    M1UE243 *e = s->ext278;
    if (r3_CheckConds135730(0, o, s)) {
        e->flags8 &= ~0x80u;
        r3_SetStateB(o, s, 4);
        return;
    }
    if (r3_CheckConds135730(1, o, s)) {
        r3_SetStateB(o, s, 10);
        return;
    }
    if (r3_CheckConds135730(2, o, s)) {
        r3_SetStateB(o, s, 11);
        return;
    }
    if (e->t178 <= 0.0f) {
        e->flags8 &= ~0x80u;
        r3_SetStateB2(o, s, 4);
        return;
    }
    if (!_mm_comige_ss(_mm_setzero_ps(), _mm_load_ss(&s->t74)))
        return;
    if (sub_001C7EE1() & 1) {
        if ((sub_001C7EE1() & 1) && (e->flags8 & 0x200)) {
            r3_SetStateB(o, s, 8);
            return;
        }
        r3_SetStateB2(o, s, 7);
        return;
    }
    if (sub_001C7EE1() & 1) {
        s->t74 = 3.0f;
        return;
    }
    if (!(sub_001C7EE1() & 3)) {
        r3_SetStateB3(o, s, 12);
        return;
    }
    s->t74 = 5.0f;
}

