/* Area m1, file 251: actor state helpers. Names inferred. */
#include <stdint.h>

typedef struct M1E251 { uint8_t unk00[0x18]; uint32_t flags18; uint8_t unk1C[4]; float v20, v24, v28, v2C; } M1E251;
typedef struct M1S251 { uint8_t unk00[0x20]; uint8_t flags20; uint8_t unk21[0x257]; M1E251 *ext278; } M1S251;
typedef struct M1O251 { uint8_t unk00[0x10]; uint32_t flags10; } M1O251;
typedef struct M1P251 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1P251;
extern float a50_frameSeconds;
int32_t b4c_Enter1456E0(M1O251 *o, M1S251 *s, int32_t a, int32_t b);
M1P251 *sub_00113400(M1S251 *s, int32_t k);
int32_t sub_00036750(M1O251 *o, int32_t pose);


typedef struct M1LE251 { uint8_t unk00[0x18]; uint32_t flags18; uint8_t unk1C[4]; float v20, v24, v28, v2C; uint8_t unk30[0x5C];
    float f8C, f90; } M1LE251;
typedef struct M1LS251 { uint8_t unk00[0x20]; uint8_t flags20; uint8_t unk21[0x37]; int32_t st58; uint8_t unk5C[0x21C];
    M1LE251 *ext278; } M1LS251;
typedef struct M1LO251 { uint8_t unk00[0x30]; void *mdl30; uint8_t unk34[0x2C]; uint8_t pos60[0xC8]; uint8_t flags128; } M1LO251;
extern float a50_frameUnits;
int32_t sub_000833E0(void *m);
int32_t b4c_Enter1456E0l(M1LO251 *o, M1LS251 *s, int32_t a, int32_t b);   /* 0x1456E0 */
int32_t aab_Effect494D0(int32_t snd, void *pos, int32_t z);
void sub_00186470(M1LO251 *obj, M1LS251 *act, int state);    /* regargs: obj=EBX act=EDI state=stack */
void sub_00186470b(M1LO251 *obj, M1LS251 *act, int state);   /* same function (alias stops cl merging calls) */

/* 0x00187CA0: dive: step 0 damps the horizontal speed by 5% per frame unit until it touches ground (clears flag 0x800);
   step 1 enters 6 with a 4.0/50-per-second bounce (flag 1) or 5, stops, plays sound 0x112; step 2 on clip end goes to
   state 2 (flag 1) or 1 (calls 0x186470 with obj=EBX act=EDI). */
void m1_Dive187CA0(M1LO251 *o, M1LS251 *s)
{
    M1LE251 *e = s->ext278;
    M1LE251 *e2;
    switch (s->st58) {
    case 0:
        e->v28 *= 1.0f - a50_frameUnits * 0.05f;
        e->v20 *= 1.0f - a50_frameUnits * 0.05f;
        if (o->flags128 & 0x18) {
            e->flags18 &= ~0x800u;
            s->st58++;
        }
        return;
    case 1:
        if (s->flags20 & 1) {
            b4c_Enter1456E0l(o, s, 6, 0);
            e->f8C = 4.0f;
            e->f90 = a50_frameSeconds * 50.0f;
        } else {
            b4c_Enter1456E0l(o, s, 5, 0);
        }
        e2 = s->ext278;
        e2->v28 = 0.0f;
        e2->v24 = 0.0f;
        e2->v20 = 0.0f;
        e2->v2C = 1.0f;
        aab_Effect494D0(0x112, o->pos60, 0);
        s->st58++;
    case 2:
        if (sub_000833E0(o->mdl30)) {
            if (s->flags20 & 1) {
                sub_00186470(o, s, 2);
                return;
            }
            sub_00186470b(o, s, 1);
        }
        return;
    }
}

typedef struct M1IE251 { uint8_t unk00[4]; uint32_t flags4; } M1IE251;
typedef struct M1IS251 { uint8_t unk00[0x58]; int32_t st58; uint8_t unk5C[0x18]; float t74; uint8_t unk78[0x200];
    M1IE251 *ext278; } M1IS251;
typedef struct M1IO251 { uint8_t unk00[0x30]; void *mdl30; } M1IO251;
int32_t b4c_Enter1456E0i(M1IO251 *o, M1IS251 *s, int32_t a, int32_t b);   /* 0x1456E0 */
void sub_0001D4E0(M1IO251 *o);
void sub_00117580(M1IO251 *o, int32_t mode, M1IS251 *s);   /* regargs: s=EDI */
int sub_001C7EE1(void);   /* rand */

/* 0x00118730: idle fidget: with flag 0x1000 hand over to mode 1; otherwise loop: enter clip 0 and wait 0-3 units, then
   play one of four random fidgets (0x16/0x19/0x1A/0x1D) and restart when it ends (calls 0x117580 with s=EDI). */
void m1_Fidget118730(M1IO251 *o, M1IS251 *s)
{
    int ids[4];
    ids[0] = 0x16;
    ids[1] = 0x19;
    ids[2] = 0x1A;
    ids[3] = 0x1D;
    if (s->ext278->flags4 & 0x1000) {
        sub_00117580(o, 1, s);
        return;
    }
    switch (s->st58) {
    case 0:
        if (b4c_Enter1456E0i(o, s, 0, 0) == 1)
            sub_0001D4E0(o);
        s->t74 = (float)sub_001C7EE1() * (1.0f / 32767.0f) * 3.0f;
        s->st58++;
        return;
    case 1:
        if (s->t74 <= 0.0f)
            s->st58 = 10;
        return;
    case 10:
        if (b4c_Enter1456E0i(o, s, ids[sub_001C7EE1() & 3], 0) == 1)
            sub_0001D4E0(o);
        s->st58++;
        return;
    case 11:
        if (sub_000833E0(o->mdl30))
            s->st58 = 0;
        return;
    }
}

typedef struct M1HE251 { uint8_t unk00[4]; uint32_t flags4; } M1HE251;
typedef struct M1HS251 { uint8_t unk00[0x22]; uint8_t b22; uint8_t unk23[0x29]; uint32_t flags4C; uint8_t unk50[8];
    int32_t st58; uint8_t unk5C[0xC]; float t68; uint8_t unk6C[0x20C]; M1HE251 *ext278; } M1HS251;
typedef struct M1HO251 { uint8_t unk00[0x10]; uint32_t flags10; } M1HO251;
typedef struct M1HP251 { uint8_t unk00[0x10]; float f10, f14; int32_t n18; void *cb1C; } M1HP251;
extern float a50_frameSeconds;
M1HP251 *sub_00113400h(M1HS251 *s, int32_t k);   /* 0x113400 */
void sub_00119FF0(void);
int  r2_GetHitKind(M1HS251 *obj, int *out);   /* regargs: obj=ECX out=EDX */
void sub_00113040(M1HO251 *o, M1HS251 *s, int32_t mode);
void sub_00113040b(M1HO251 *o, M1HS251 *s, int32_t mode);   /* same function (aliases stop cl merging calls) */
void sub_00113040c(M1HO251 *o, M1HS251 *s, int32_t mode);
void sub_00113040d(M1HO251 *o, M1HS251 *s, int32_t mode);

/* 0x0011D750: knock-back recovery: step 0 after 35 frames picks mode 4 (pending flag 0x20000000), the hit kind, or 12/7
   by s flag 1; step 1 after 10 frames starts a 0.25 tumble with callback 0x119FF0; step 2 after 35 frames clears o flags
   6 and goes to mode 12 (calls 0x11B0D0 with obj=ECX out=EDX). */
void m1_Recover11D750(M1HO251 *o, M1HS251 *s)
{
    M1HE251 *e;
    M1HP251 *p;
    int k;
    switch (s->st58) {
    case 0:
        if (s->t68 >= 35.0f / a50_frameUnits * a50_frameSeconds) {
            e = s->ext278;
            if (e->flags4 & 0x20000000) {
                e->flags4 &= ~0x20000000u;
                sub_00113040(o, s, 4);
                return;
            }
            if (r2_GetHitKind(s, &k)) {
                sub_00113040b(o, s, k);
                return;
            }
            sub_00113040c(o, s, (-(s->b22 & 1) & 5) + 7);
        }
        return;
    case 1:
        if (s->t68 >= 10.0f / a50_frameUnits * a50_frameSeconds) {
            p = sub_00113400h(s, 1);
            if (p) {
                p->f10 = 0.25f;
                p->f14 = 0.25f;
                p->n18 = 0;
                p->cb1C = (void *)sub_00119FF0;
            }
            s->st58++;
        }
        return;
    case 2:
        if (s->t68 >= 35.0f / a50_frameUnits * a50_frameSeconds) {
            o->flags10 &= ~6u;
            s->flags4C |= 0x10;
            sub_00113040d(o, s, 12);
        }
        return;
    }
}

typedef struct M1FE251 { uint8_t unk00[0x2C]; float f2C, f30, f34, f38; } M1FE251;
typedef struct M1FS251 { uint8_t unk00[0x58]; int32_t st58; uint8_t unk5C[8]; int32_t n64; uint8_t unk68[0x210];
    M1FE251 *ext278; } M1FS251;
typedef struct M1FO251 { uint8_t unk00[0x30]; void *mdl30; uint8_t unk34[0xF4]; uint8_t flags128; } M1FO251;
int32_t b4c_Enter1456E0f(M1FO251 *o, M1FS251 *s, int32_t a, int32_t b);   /* 0x1456E0 */
void sub_0001D4E0f(M1FO251 *o);                                            /* 0x1D4E0 */
void sub_00117580f(M1FO251 *o, int32_t mode, M1FS251 *s);                  /* 0x117580 regargs: s=EDI */

/* 0x00119790: fall: (clip end) enter 0x35/0x39 for falls 0x34/0x38, wait for ground, enter 0x36/0x3A for 0x35/0x39 and
   stop, (clip end) mode 0x23; other fall kinds hang; while in steps 0-2 damp x/z speed by 5% per frame unit (calls
   0x117580 with s=EDI). */
void m1_Fall119790(M1FO251 *o, M1FS251 *s)
{
    M1FE251 *e = s->ext278;
    M1FE251 *e2;
    int m;
    switch (s->st58) {
    case 0:
        if (!sub_000833E0(o->mdl30))
            break;
        s->st58++;
    case 1:
        if (s->n64 == 0x34)
            m = 0x35;
        else if (s->n64 == 0x38)
            m = 0x39;
        else
            for (;;) ;
        if (b4c_Enter1456E0f(o, s, m, 0) == 1)
            sub_0001D4E0f(o);
        s->st58++;
    case 2:
        if (o->flags128 & 0x18)
            s->st58++;
        break;
    case 3:
        if (s->n64 == 0x35)
            m = 0x36;
        else if (s->n64 == 0x39)
            m = 0x3A;
        else
            for (;;) ;
        if (b4c_Enter1456E0f(o, s, m, 0) == 1)
            sub_0001D4E0f(o);
        e2 = s->ext278;
        e2->f34 = 0.0f;
        e2->f30 = 0.0f;
        e2->f2C = 0.0f;
        e2->f38 = 1.0f;
        s->st58++;
        break;
    case 4:
        if (!sub_000833E0(o->mdl30))
            break;
        s->st58++;
    case 5:
        sub_00117580f(o, 0x23, s);
        return;
    }
    if (s->st58 <= 2) {
        e->f2C *= 1.0f - a50_frameUnits * 0.05f;
        e->f34 *= 1.0f - a50_frameUnits * 0.05f;
    }
}

typedef void (*M1TCb251)(void *o, void *s, int32_t arg);
typedef struct M1TP251 { int32_t f0; uint8_t unk04[4]; float t8; int32_t stC; float f10, f14; int32_t n18; M1TCb251 cb1C; } M1TP251;
void sub_000EE760(void *o, float k);
void sub_001130F0(void *o, void *s, int32_t arg);
void sub_00113370(void *s, M1TP251 *p);

/* 0x00139330: fade transition: step 0 marks state 2 and waits for the start time; step 1 fades out over 0.7 x the
   length, then runs 0x1130F0 and the optional callback; step 2 fades back in and on finishing marks state 1 and ends the
   transition (0x113370). */
void m1_Fade139330(void *o, void *s, M1TP251 *p)
{
    float d, k;
    switch (p->stC) {
    case 0:
        if (p->f0)
            p->f0 = 2;
        if (p->t8 >= p->f10)
            p->stC = 1;
        return;
    case 1:
        d = p->t8 - p->f10;
        k = 1.0f - d / (p->f14 * 0.7f);
        if (0.0f > k)
            k = 0.0f;
        sub_000EE760(o, k);
        if (d > p->f14) {
            sub_001130F0(o, s, p->n18);
            if (p->cb1C)
                p->cb1C(o, s, p->n18);
            p->stC++;
        }
        return;
    case 2:
        d = p->t8 - p->f10 - p->f14;
        k = d / (p->f14 * 0.7f);
        if (k > 1.0f)
            k = 1.0f;
        sub_000EE760(o, k);
        if (d > p->f14) {
            if (p->f0)
                p->f0 = 1;
            sub_00113370(s, p);
        }
        return;
    }
}
