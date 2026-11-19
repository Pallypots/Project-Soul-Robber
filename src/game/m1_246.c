/* Area m1, file 246: enemy follow-up pickers (register-argument callers per docs/verification.md). Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1E246 { uint8_t unk00[4]; uint32_t flags4; uint8_t unk08[0x18]; void *p20; uint8_t unk24[4]; int32_t n28; } M1E246;
typedef struct M1S246 { uint8_t unk00[0x4C]; uint32_t flags4C; uint8_t unk50[8]; int32_t st58; float t5C; uint8_t unk60[0x14];
    float t74; uint8_t unk78[0x88]; float f100; uint8_t unk104[0x174]; M1E246 *ext278; } M1S246;
typedef struct M1O246 { uint8_t unk00[8]; int32_t kind8; uint8_t unk0C[0x24]; void *mdl30; } M1O246;
typedef struct M1V246 { float v[4]; } M1V246;
typedef int (*M1Fn246)(M1O246 *o, M1S246 *s, const M1V246 *v);
extern M1Fn246 r2_fn31B0C4[];
extern M1V246 r2_vec279598[];
extern float a50_frameUnits, a50_frameSeconds;
int32_t sub_000833E0(void *m);
int  r2_GetHitKind(M1S246 *obj, int *out);              /* regargs: obj=ECX out=EDX */
int  r2_CallTbl31B0C4(int a, M1S246 *b, M1O246 *arg);   /* regargs: a=EAX b=EDX, arg on stack */
void *r2_SelectKind(int kind);                          /* regargs: kind=EAX */
void sub_00142270(M1O246 *o, M1S246 *s);
void sub_0001D720(void *p);
void sub_00113040(M1O246 *o, M1S246 *s, int32_t mode);

/* 0x0011C4F0: step 0 after 15 frames runs 0x142270 and 0x1D720 then advances; step 1 on clip end picks mode 3 (check
   passes), the hit kind, 15 (handler 1), 8 (flag 8, a selectable kind and within 45 degrees: sets flag 4, n28 = 11)
   or 5 with a zero timer, then 0x113040. */
void m1_Next11C4F0(M1O246 *o, M1S246 *s)
{
    M1E246 *e = s->ext278;
    int m, k;
    switch (s->st58) {
    case 0:
        if (s->t5C >= 15.0f / a50_frameUnits * a50_frameSeconds) {
            sub_00142270(o, s);
            sub_0001D720(s->ext278->p20);
            s->st58++;
        }
        return;
    case 1:
        if (!sub_000833E0(o->mdl30))
            return;
        if (r2_fn31B0C4[0](o, s, &r2_vec279598[0])) {
            m = 3;
        } else if (r2_GetHitKind(s, &k)) {
            m = k;
        } else if (r2_CallTbl31B0C4(1, s, o)) {
            m = 15;
        } else if ((e->flags4 & 8) && r2_SelectKind(o->kind8) && s->f100 < 45.0f) {
            e->flags4 |= 4;
            m = 8;
            e->n28 = 11;
        } else {
            s->t74 = 0.0f;
            m = 5;
        }
        s->flags4C |= 0x10;
        sub_00113040(o, s, *(volatile int *)&m);
        return;
    }
}

typedef struct M1BE246 { uint8_t unk00[4]; uint32_t flags4; uint8_t unk08[0x18]; float v20[4]; float v30[4]; float v40[4];
    float v50[3], v5C, v60, v64; } M1BE246;
typedef struct M1BS246 { uint8_t unk00[0x5C]; float t5C; uint8_t unk60[0x218]; M1BE246 *ext278; } M1BS246;
typedef struct M1BO246 { uint8_t unk00[0x10]; uint8_t flags10; uint8_t unk11[0x4F]; uint8_t pos60[0xC8]; uint8_t flags128; } M1BO246;
float sub_001B2770(const void *a, const void *b);
void m1_LockMark0C56B0(M1BO246 *o);
int32_t b4c_Enter1456E0(M1BO246 *o, M1BS246 *s, int32_t a, int32_t b);
void sub_000F5D40(void *dst, const void *src);
int32_t aab_Effect494D0(int32_t snd, void *pos, int32_t z);
void m1_PlShot0C62A0(M1BO246 *o);
void sub_00025D50(int32_t a, int32_t b);
int  r2_PlayerOutOfReachB(M1BS246 *obj, M1BO246 *self);   /* 0x120820 regargs: obj=EAX self=ESI */
void sub_0011F2B0b(M1BO246 *obj, int k, M1BS246 *a);        /* 0x11F2B0 regargs: obj=EDI k=EBX */

/* 0x0012B860: grab attempt: near (< 60), early (< 3) and with no blocking flags just mark the lock-on; otherwise enter
   state 0x49, reset the hold vectors, play sounds 0xE5/0x77, fire the shot and rumble; then (unless flag 0x20) go to
   0x11 when out of reach or 0x2C, hanging if flag 0x20 / o flag 8 is set (calls 0x120820 with obj=EAX self=ESI,
   0x11F2B0 with obj=EDI k=EBX). */
void m1_Grab12B860(M1BO246 *o, M1BS246 *s)
{
    M1BE246 *e = s->ext278;
    M1BE246 *e2;
    float d = sub_001B2770(o->pos60, e->v20);
    if (!(o->flags128 & 0x1E) && !_mm_comige_ss(_mm_load_ss(&s->t5C), _mm_set_ss(3.0f))
        && !_mm_comige_ss(_mm_load_ss(&d), _mm_set_ss(60.0f)) && !(e->flags4 & 0x20000000)) {
        m1_LockMark0C56B0(o);
        return;
    }
    b4c_Enter1456E0(o, s, 0x49, 0);
    e2 = s->ext278;
    sub_000F5D40(e2->v40, e2->v30);
    e2->v50[2] = 0.0f;
    e2->v50[1] = 0.0f;
    e2->v50[0] = 0.0f;
    e2->v5C = 1.0f;
    e2->v60 = 1.0f;
    e2->v64 = 1.0f;
    aab_Effect494D0(0xE5, o->pos60, 0);
    aab_Effect494D0(0x77, o->pos60, 0);
    m1_PlShot0C62A0(o);
    sub_00025D50(1, 1);
    if (e->flags4 & 0x20)
        return;
    if (r2_PlayerOutOfReachB(s, o)) {
        sub_0011F2B0b(o, 0x11, s);
        return;
    }
    if ((e->flags4 & 0x20) || (o->flags10 & 8))
        for (;;) ;
    sub_0011F2B0b(o, 0x2C, s);
}

typedef struct M1CT246 { uint8_t unk00[4]; int32_t kind4; uint8_t unk08[4]; uint8_t flagsC; } M1CT246;
typedef struct M1CE246 { uint8_t unk00[0x90]; float f90; } M1CE246;
typedef struct M1CS246 { uint8_t unk00[0x4C]; uint32_t flags4C; uint8_t unk50[0xC]; float t5C; uint8_t unk60[0x98];
    int32_t nF8; uint8_t unkFC[8]; M1CT246 *tgt104; uint8_t unk108[0x170]; M1CE246 *ext278; } M1CS246;
typedef struct M1CO246 { uint8_t unk00[0x30]; void *mdl30; uint8_t unk34[0x2C]; uint8_t pos60[0x10]; } M1CO246;
extern M1CO246 *g_playerObjC;
extern float b10_f3F7504;
int32_t sub_00145730(float t, int32_t n);
void sub_00113480c(M1CS246 *s, int32_t k);
int sub_001C7EE1(void);   /* rand */
int  r2_PlayerOutOfReachC(M1CS246 *obj, M1CO246 *self);   /* 0x120820 regargs: obj=EAX self=ESI */
void sub_0011F2B0c(M1CO246 *obj, int k, M1CS246 *a);        /* 0x11F2B0 regargs: obj=EDI k=EBX */

/* 0x00123C10: (0x113480 1 every 30 frames) on clip end pick state 0x11 (out of reach), 3/4 at random with the global
   speed 6 when flag 0x100, 0x15 (locked on an active kind-13 target), 6 with a random 1-2 speed within 30 of the
   player, else 1 (speed 1) (calls 0x120820 with obj=EAX self=ESI, 0x11F2B0 with obj=EDI k=EBX). */
void m1_Next123C10(M1CO246 *o, M1CS246 *s)
{
    M1CE246 *e = s->ext278;
    if (sub_00145730(s->t5C, 0x1E))
        sub_00113480c(s, 1);
    if (!sub_000833E0(o->mdl30))
        return;
    if (r2_PlayerOutOfReachC(s, o)) {
        sub_0011F2B0c(o, 0x11, s);
        return;
    }
    if (s->flags4C & 0x100) {
        b10_f3F7504 = 6.0f;
        if (sub_001C7EE1() & 1) {
            sub_0011F2B0c(o, 3, s);
            return;
        }
        sub_0011F2B0c(o, 4, s);
        return;
    }
    if (s->nF8 == 1 && (s->tgt104->flagsC & 1) && s->tgt104->kind4 == 13) {
        sub_0011F2B0c(o, 0x15, s);
        return;
    }
    b10_f3F7504 = 1.0f;
    if (sub_001B2770(o->pos60, g_playerObjC->pos60) < 30.0f) {
        e->f90 = (float)sub_001C7EE1() * (1.0f / 32767.0f) + 1.0f;
        sub_0011F2B0c(o, 6, s);
        return;
    }
    sub_0011F2B0c(o, 1, s);
}

typedef struct M1DE246 { uint8_t unk00[4]; uint32_t flags4; uint8_t unk08[0x48]; float v50, v54, v58; } M1DE246;
typedef struct M1DS246 { uint8_t unk00[0x58]; int32_t st58; uint8_t unk5C[0x21C]; M1DE246 *ext278; } M1DS246;
int32_t b4c_Enter1456E0d(M1CO246 *o, M1DS246 *s, int32_t a, int32_t b);   /* 0x1456E0 */
void r2_BodySetMotion(M1DS246 *s, int32_t a, int32_t b, int32_t c, float t);   /* regargs: s=EAX */
int  r2_PlayerOutOfReachD(M1DS246 *obj, M1CO246 *self);   /* 0x120820 regargs: obj=EAX self=ESI */
void sub_0011F2B0d(M1CO246 *obj, int k, M1DS246 *a);        /* 0x11F2B0 regargs: obj=EDI k=EBX */

/* 0x0012A940: six-step knock-back: (clip end) enter 0x38, (clip end) enter 0x39 and restart the body motion clearing
   flag 8, (clip end) state 0x11 out of reach else 1; while in steps 0-2 damp the velocity by 2% per frame unit
   (calls 0x11F480 with s=EAX, 0x120820 with obj=EAX self=ESI, 0x11F2B0 with obj=EDI k=EBX). */
void m1_Knock12A940(M1CO246 *o, M1DS246 *s)
{
    M1DE246 *e = s->ext278;
    switch (s->st58) {
    case 0:
        if (!sub_000833E0(o->mdl30))
            break;
        s->st58++;
    case 1:
        b4c_Enter1456E0d(o, s, 0x38, 0);
        goto inc;
    case 2:
        if (!sub_000833E0(o->mdl30))
            break;
        s->st58++;
    case 3:
        b4c_Enter1456E0d(o, s, 0x39, 0);
        r2_BodySetMotion(s, 0, 0, 0, a50_frameUnits * 0.0333333351f);
        e->flags4 &= ~8u;
inc:
        s->st58++;
        break;
    case 4:
        if (!sub_000833E0(o->mdl30))
            break;
        s->st58++;
    case 5:
        if (r2_PlayerOutOfReachD(s, o)) {
            sub_0011F2B0d(o, 0x11, s);
            return;
        }
        sub_0011F2B0d(o, 1, s);
        return;
    }
    if (s->st58 <= 2) {
        e->v50 *= 1.0f - a50_frameUnits * 0.02f;
        e->v54 *= 1.0f - a50_frameUnits * 0.02f;
        e->v58 *= 1.0f - a50_frameUnits * 0.02f;
    }
}

typedef struct M1FS246 { uint8_t unk00[0x4C]; uint32_t flags4C; uint8_t unk50[8]; int32_t st58; uint8_t unk5C[0xC];
    float t68; uint8_t unk6C[8]; float t74; } M1FS246;
typedef struct M1FO246 { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x1C]; void *mdl30; } M1FO246;
typedef int (*M1FFn246)(M1FO246 *o, M1FS246 *s, const M1V246 *v);
extern M1FFn246 r2_fn31B0C4f[];
int32_t sub_00036750(M1FO246 *o, int32_t pose);
int  r2_GetHitKindF(M1FS246 *obj, int *out);   /* 0x11B0D0 regargs: obj=ECX out=EDX */
void sub_00113480f(M1FS246 *s, int32_t k);
void sub_00113040f(M1FO246 *o, M1FS246 *s, int32_t mode);

/* 0x0011D260: step 0 after 15 frames sets pose 10; step 1 after 80 frames clears o flags 6 (immediately when flag
   0x100); step 2 on clip end picks mode 3 (check), the hit kind, 4 (flag 0x100, also setting the global to 240
   frames) or 5 with a 90-frame timer, clears 0x100, sets 0x10, then 0x113480 2 and 0x113040 (calls 0x11B0D0 with
   obj=ECX out=EDX). */
void m1_Next11D260(M1FO246 *o, M1FS246 *s)
{
    int m, k;
    switch (s->st58) {
    case 0:
        if (s->t68 >= 15.0f / a50_frameUnits * a50_frameSeconds) {
            sub_00036750(o, 10);
            s->st58++;
        }
        return;
    case 1:
        if (s->t68 >= 80.0f / a50_frameUnits * a50_frameSeconds) {
            o->flags10 &= ~6u;
            s->st58++;
            return;
        }
        if (s->flags4C & 0x100)
            o->flags10 &= ~6u;
        return;
    case 2:
        if (!sub_000833E0(o->mdl30))
            return;
        if (r2_fn31B0C4f[0](o, s, &r2_vec279598[0])) {
            m = 3;
        } else if (r2_GetHitKindF(s, &k)) {
            m = k;
        } else if (s->flags4C & 0x100) {
            m = 4;
        } else {
            s->t74 = 90.0f / a50_frameUnits * a50_frameSeconds;
            m = 5;
        }
        if (s->flags4C & 0x100)
            b10_f3F7504 = 240.0f / a50_frameUnits * a50_frameSeconds;
        s->flags4C = (s->flags4C & ~0x100u) | 0x10;
        sub_00113480f(s, 2);
        sub_00113040f(o, s, *(volatile int *)&m);
        return;
    }
}

typedef struct M1GE246 { int32_t f0; uint32_t flags4; uint8_t unk08[0xC]; float f14; uint8_t unk18[0x10]; int32_t n28; } M1GE246;
typedef struct M1GS246 { uint8_t unk00[0x22]; uint8_t b22; uint8_t unk23[0x35]; int32_t st58; uint8_t unk5C[0xC];
    float t68; uint8_t unk6C[8]; float t74; uint8_t unk78[0x84]; float fFC; uint8_t unk100[0x178]; M1GE246 *ext278; } M1GS246;
typedef struct M1GO246 { uint8_t unk00[8]; int32_t kind8; uint8_t unk0C[4]; uint32_t flags10; uint8_t unk14[0x1C]; void *mdl30; } M1GO246;
float sub_001A3F30(float v);
void b10_SubClampF(float *v, float d, float lim);
int  r2_GetHitKindG(M1GS246 *obj, int *out);   /* 0x11B0D0 regargs: obj=ECX out=EDX */
void sub_00113090g(M1GO246 *o, M1GS246 *s, int32_t mode);
void sub_00113040g(M1GO246 *o, M1GS246 *s, int32_t mode);

/* 0x0011D5E0: step 0 when t74 runs out drains +0x14 (30 when flagged negative, else 10) and plays 0x32/0x33 (+2 when
   flagged); step 1 after 34 frames clears o flag 4; step 2 on clip end picks the hit kind, 8 (flag 8, s flag 1, no
   selectable kind, within 60 degrees and 1 in 4: sets flag 4, n28 = 11) or 5 with a zero timer, clears o flag 4 and
   hands over to 0x113040 (calls 0x11B0D0 with obj=ECX out=EDX, 0x11B140 with kind=EAX). */
void m1_Next11D5E0(M1GO246 *o, M1GS246 *s)
{
    M1GE246 *e = s->ext278;
    int m, k;
    switch (s->st58) {
    case 0:
        if (s->t74 <= 0.0f) {
            k = (s->b22 & 1) + 0x32;
            if (e->flags4 & 0x80000000) {
                k += 2;
                b10_SubClampF(&e->f14, 30.0f, 0.0f);
            } else {
                b10_SubClampF(&e->f14, 10.0f, 0.0f);
            }
            sub_00113090g(o, s, k);
            s->st58++;
        }
        return;
    case 1:
        if (s->t68 >= 34.0f / a50_frameUnits * a50_frameSeconds) {
            o->flags10 &= ~4u;
            s->st58++;
        }
        return;
    case 2:
        if (!sub_000833E0(o->mdl30))
            return;
        if (r2_GetHitKindG(s, &k)) {
            m = k;
        } else if ((e->flags4 & 8) && (s->b22 & 1) && !r2_SelectKind(o->kind8) && sub_001A3F30(s->fFC) < 1.04719758f
                   && sub_001C7EE1() % 4 < 1) {
            e->flags4 |= 4;
            m = 8;
            s->ext278->n28 = 11;
        } else {
            s->t74 = 0.0f;
            m = 5;
        }
        o->flags10 &= ~4u;
        sub_00113040g(o, s, *(volatile int *)&m);
        return;
    }
}

typedef struct M1HP246 { uint8_t unk00[0x10]; float f10, f14; } M1HP246;
typedef struct M1HE246 { uint8_t unk00[4]; uint32_t flags4; } M1HE246;
typedef struct M1HS246 { uint8_t unk00[0x4C]; uint32_t flags4C; uint8_t unk50[8]; int32_t st58; uint8_t unk5C[0xC];
    float t68; uint8_t unk6C[8]; float t74; uint8_t unk78[0x84]; float fFC; uint8_t unk100[0x178]; M1HE246 *ext278; } M1HS246;
M1HP246 *sub_00113400(M1HS246 *s, int32_t k);
void sub_00113370(M1HS246 *s, M1HP246 *p);
int  r2_CallTbl31B0C4h(int a, M1HS246 *b, M1O246 *arg);   /* 0x11B020 regargs: a=EAX b=EDX, arg on stack */
int  r2_GetHitKindH(M1HS246 *obj, int *out);              /* 0x11B0D0 regargs: obj=ECX out=EDX */
void sub_00113040h(M1O246 *o, M1HS246 *s, int32_t mode);

/* 0x0011D3D0: timed turn: step 0 waits 17 frames; step 1 at 30 frames sets flag 2; steps 1-2 turn (1.5 degrees per frame
   unit while the angle is between 10 and 90 degrees) and at 31 frames commit the turn (step 3); step 3 at 100 frames
   clears flag 2; step 4 on clip end picks mode 3 (handler 0), the hit kind or 5 (calls 0x11B020 with a=EAX b=EDX,
   0x11B0D0 with obj=ECX out=EDX). */
void m1_Turn11D3D0(M1O246 *o, M1HS246 *s)
{
    M1HP246 *p;
    int m, k;
    switch (s->st58) {
    case 0:
        if (s->t68 >= 17.0f / a50_frameUnits * a50_frameSeconds)
            s->st58 = 1;
        return;
    case 1:
        if (s->t68 >= 30.0f / a50_frameUnits * a50_frameSeconds) {
            s->ext278->flags4 |= 2;
            s->st58++;
        }
    case 2:
        p = sub_00113400(s, 3);
        if (s->fFC >= 0.174532935f && s->fFC <= 1.57079637f)
            p->f10 = a50_frameUnits * 0.0261799395f;
        else
            p->f10 = 0.0f;
        p->f14 = 0.0f;
        if (s->t68 >= 31.0f / a50_frameUnits * a50_frameSeconds) {
            sub_00113370(s, p);
            s->st58 = 3;
        }
        return;
    case 3:
        if (s->t68 >= 100.0f / a50_frameUnits * a50_frameSeconds) {
            s->ext278->flags4 &= ~2u;
            s->st58++;
        }
        return;
    case 4:
        if (!sub_000833E0(o->mdl30))
            return;
        if (r2_CallTbl31B0C4h(0, s, o)) {
            m = 3;
        } else if (r2_GetHitKindH(s, &k)) {
            m = k;
        } else {
            s->t74 = 0.0f;
            m = 5;
        }
        s->flags4C |= 0x10;
        sub_00113040h(o, s, *(volatile int *)&m);
        return;
    }
}

typedef int (*M1HFn246)(M1O246 *o, M1HS246 *s, const M1V246 *v);
extern M1HFn246 r2_fn31B0C4h[];
void sub_00113480h(M1HS246 *s, int32_t k);

/* 0x0011D0A0: step 0 waits 11 frames; step 1 turns 1 degree per frame unit while the angle is between 10 and 90
   degrees and commits at 40 frames; step 2 on clip end picks mode 3 (check), the hit kind, 12 (flag 0x100, also the
   240-frame global), 15 (handler 1) or 5 with a 60-frame timer, then 0x113480 2 and 0x113040. */
void m1_Turn11D0A0(M1O246 *o, M1HS246 *s)
{
    M1HP246 *p;
    int m, k;
    switch (s->st58) {
    case 0:
        if (s->t68 >= 11.0f / a50_frameUnits * a50_frameSeconds)
            s->st58 = 1;
        return;
    case 1:
        p = sub_00113400(s, 3);
        if (s->fFC >= 0.174532935f && s->fFC <= 1.57079637f)
            p->f10 = a50_frameUnits * 0.0174532924f;
        else
            p->f10 = 0.0f;
        p->f14 = 0.0f;
        if (s->t68 >= 40.0f / a50_frameUnits * a50_frameSeconds) {
            sub_00113370(s, p);
            s->st58++;
        }
        return;
    case 2:
        if (!sub_000833E0(o->mdl30))
            return;
        if (r2_fn31B0C4h[0](o, s, &r2_vec279598[0])) {
            m = 3;
        } else if (r2_GetHitKindH(s, &k)) {
            m = k;
        } else if (s->flags4C & 0x100) {
            m = 12;
        } else if (r2_CallTbl31B0C4h(1, s, o)) {
            m = 15;
        } else {
            s->t74 = 60.0f / a50_frameUnits * a50_frameSeconds;
            m = 5;
        }
        if (s->flags4C & 0x100)
            b10_f3F7504 = 240.0f / a50_frameUnits * a50_frameSeconds;
        s->flags4C = (s->flags4C & ~0x100u) | 0x10;
        sub_00113480h(s, 2);
        sub_00113040h(o, s, *(volatile int *)&m);
        return;
    }
}

typedef struct M1IE246 { uint8_t unk00[4]; uint32_t flags4; uint8_t unk08[0x88]; float f90; } M1IE246;
typedef struct M1IS246 { uint8_t unk00[0x20]; uint8_t flags20; uint8_t unk21[0x37]; int32_t st58; uint8_t unk5C[8];
    int32_t n64; uint8_t unk68[0x210]; M1IE246 *ext278; } M1IS246;
void sub_000ED780(void *o);
int32_t b4c_Enter1456E0i(M1CO246 *o, M1IS246 *s, int32_t a, int32_t b);    /* 0x1456E0 */
void r2_BodySetMotionI(M1IS246 *s, int32_t a, int32_t b, int32_t c, float t);   /* 0x11F480 regargs: s=EAX */
int  r2_PlayerOutOfReachI(M1IS246 *obj, M1CO246 *self);   /* 0x120820 regargs: obj=EAX self=ESI */
void sub_0011F2B0i(M1CO246 *obj, int k, M1IS246 *a);        /* 0x11F2B0 regargs: obj=EDI k=EBX */

/* 0x00128E40: destroy when flag 0x400; otherwise a six-step knock-down: (clip end) enter 0x35 or 0x38, (clip end) enter
   0x36 or 0x39 and restart the body motion, (clip end) random 1-2.5 speed and state 0x2F (flag 0x20), 0x11 (out of
   reach) or 7/1 (calls 0x11F480 with s=EAX, 0x120820 with obj=EAX self=ESI, 0x11F2B0 with obj=EDI k=EBX). */
void m1_KnockDown128E40(M1CO246 *o, M1IS246 *s)
{
    M1IE246 *e = s->ext278;
    if (e->flags4 & 0x400) {
        sub_000ED780(o);
        return;
    }
    switch (s->st58) {
    case 0:
        if (!sub_000833E0(o->mdl30))
            return;
        s->st58++;
    case 1:
        b4c_Enter1456E0i(o, s, s->n64 == 0x34 ? 0x35 : 0x38, 0);
        s->st58++;
    case 2:
        if (!sub_000833E0(o->mdl30))
            return;
        s->st58++;
    case 3:
        b4c_Enter1456E0i(o, s, s->n64 == 0x35 ? 0x36 : 0x39, 0);
        r2_BodySetMotionI(s, 0, 0, 0, a50_frameUnits * 0.0333333351f);
        s->st58++;
        return;
    case 4:
        if (!sub_000833E0(o->mdl30))
            return;
        s->st58++;
    case 5:
        e->f90 = (float)sub_001C7EE1() * (1.0f / 32767.0f) * 1.5f + 1.0f;
        if (e->flags4 & 0x20) {
            sub_0011F2B0i(o, 0x2F, s);
            return;
        }
        if (r2_PlayerOutOfReachI(s, o)) {
            sub_0011F2B0i(o, 0x11, s);
            return;
        }
        sub_0011F2B0i(o, (s->flags20 & 1) ? 7 : 1, s);
        return;
    }
}

typedef struct M1JL246 { float a0, b4; uint8_t unk08[0xB8]; } M1JL246;
typedef struct M1JE246 { uint8_t unk00[4]; uint32_t flags4; uint8_t unk08[0x28]; float v30[4]; float v40[4]; float v50[3];
    float v5C, v60, v64; uint8_t unk68[0x3B4]; M1JL246 l41C[1]; } M1JE246;
typedef struct M1JX246 { uint8_t unk00[0x424]; float f424; uint8_t unk428[8]; uint32_t f430; } M1JX246;
typedef struct M1JS246 { uint8_t unk00[0x58]; int32_t st58; uint8_t unk5C[0x18]; float t74; uint8_t unk78[0x200];
    M1JE246 *ext278; } M1JS246;
int32_t b4c_Enter1456E0j(M1BO246 *o, M1JS246 *s, int32_t a, int32_t b);    /* 0x1456E0 */
int  r2_PlayerOutOfReachJ(M1JS246 *obj, M1BO246 *self);   /* 0x120820 regargs: obj=EAX self=ESI */
void sub_0011F2B0j(M1BO246 *obj, int k, M1JS246 *a);        /* 0x11F2B0 regargs: obj=EDI k=EBX */
void sub_000ED780j(M1BO246 *o);                              /* 0x0ED780 */

/* 0x00129F70: destroy when flag 0x400; step 0 waits for ground flags 0x18 or the timer; step 1 enters 0x45, resets the
   hold vectors, plays sound 0xE5, sets a 0.5 timer and re-arms the four limb springs; step 2 when the timer runs out
   goes to 0x2F (flag 0x20), 0x11 (out of reach) or 0x2C (calls 0x120820 with obj=EAX self=ESI, 0x11F2B0 with obj=EDI
   k=EBX). */
void m1_Grab129F70(M1BO246 *o, M1JS246 *s)
{
    M1JE246 *e = s->ext278;
    uint32_t f = e->flags4;
    M1JE246 *e2;
    M1JL246 *volatile l;
    int n;
    if (f & 0x400) {
        sub_000ED780j(o);
        return;
    }
    switch (s->st58) {
    case 0:
        if ((o->flags128 & 0x18) || s->t74 <= 0.0f)
            s->st58 = 1;
        return;
    case 1:
        b4c_Enter1456E0j(o, s, 0x45, 0);
        e2 = s->ext278;
        sub_000F5D40(e2->v40, e2->v30);
        e2->v50[2] = 0.0f;
        e2->v50[1] = 0.0f;
        e2->v50[0] = 0.0f;
        e2->v5C = 1.0f;
        e2->v60 = 1.0f;
        e2->v64 = 1.0f;
        aab_Effect494D0(0xE5, o->pos60, 0);
        s->t74 = 0.5f;
        l = e->l41C;
        n = 4;
        do {
            l->b4 = 0.0f;
            l->a0 = 0.1f;
            l++;
        } while (--n);
        ((M1JX246 *)e)->f424 = 1.0f;
        ((M1JX246 *)e)->f430 |= 1;
        s->st58++;
        return;
    case 2:
        if (s->t74 <= 0.0f) {
            if (f & 0x20) {
                sub_0011F2B0j(o, 0x2F, s);
                return;
            }
            if (r2_PlayerOutOfReachJ(s, o)) {
                sub_0011F2B0j(o, 0x11, s);
                return;
            }
            sub_0011F2B0j(o, 0x2C, s);
        }
        return;
    }
}
