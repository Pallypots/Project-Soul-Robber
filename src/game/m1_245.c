/* Area m1, file 245: assorted state helpers (register inputs per docs/verification.md). Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Fx245 { uint8_t unk00[0xC]; int32_t state0C; uint8_t unk10[0x14]; float t24; uint8_t unk28[0x28];
    void *ent50; } M1Fx245;
extern float a50_frameUnits, a50_frameSeconds;
int32_t sub_00172950(void *e);
void sub_0001D470(void *e, int32_t n);
void sub_0001D4B0(void *e, int32_t n);
int sub_001C7EE1(void);   /* rand */

/* 0x000CE750: four-light chaser: odd steps light flag (step-1)/2 of four (0-3, or 4-7 when 0x172950 > 0) and wait
   8-11 units, even steps count the wait down; after step 8 it wraps to 1 (regargs: f=EDI). */
void m1_Chaser0CE750(M1Fx245 *f)
{
    void *e = f->ent50;
    int ids[4];
    int i, st;
    ids[0] = 0;
    ids[1] = 1;
    ids[2] = 2;
    ids[3] = 3;
    if (sub_00172950(e) > 0) {
        ids[0] = 4;
        ids[1] = 5;
        ids[2] = 6;
        ids[3] = 7;
    }
    switch (f->state0C) {
    case 0:
        f->state0C = 1;
        return;
    case 1: case 3: case 5: case 7:
        for (i = 0; i < 4; i++) {
            if (i == (f->state0C - 1) / 2)
                sub_0001D470(e, ids[i]);
            else
                sub_0001D4B0(e, ids[i]);
        }
        f->t24 = 8.0f;
        f->t24 = (float)(sub_001C7EE1() % 4) + f->t24;
        f->state0C++;
        return;
    case 2: case 4: case 6: case 8:
        f->t24 -= a50_frameUnits;
        if (_mm_comige_ss(_mm_setzero_ps(), _mm_load_ss(&f->t24))) {
            st = f->state0C + 1;
            f->t24 = 0.0f;
            f->state0C = st;
            if (st >= 9)
                f->state0C = 1;
        }
        return;
    }
}

typedef struct M1CE245 { uint8_t unk00[0x7C]; float f7C; uint8_t unk80[0x10]; float f90; uint8_t unk94[4]; int32_t n98; } M1CE245;
typedef struct M1CS245 { uint8_t unk00[0x74]; float t74; uint8_t unk78[0x200]; M1CE245 *ext278; } M1CS245;
typedef struct M1CO245 { uint8_t unk00[0x30]; void *mdl30; } M1CO245;
int32_t sub_000833E0(void *m);
int  r2_PlayerOutOfReach(M1CS245 *obj, M1CO245 *self);   /* regargs: obj=EAX self=ESI */
void sub_0011F2B0(M1CO245 *obj, int k, M1CS245 *a);       /* regargs: obj=EDI k=EBX */

/* 0x00123550: on clip end: out of reach -> 0x11; else follow the queued state: 5 (random 1-2.5 speed and 2-3 unit
   timer), 12, or 13 (raise +0x7C by 50, clamped 0-200); anything else hangs (calls 0x120820 with obj=EAX self=ESI,
   0x11F2B0 with obj=EDI k=EBX). */
void m1_Queued123550(M1CO245 *o, M1CS245 *s)
{
    M1CE245 *e = s->ext278;
    int r;
    if (!sub_000833E0(o->mdl30))
        return;
    if (r2_PlayerOutOfReach(s, o)) {
        sub_0011F2B0(o, 0x11, s);
        return;
    }
    r = e->n98;
    if (r == 5) {
        sub_0011F2B0(o, r, s);
        r = sub_001C7EE1();
        e->f90 = (float)r * (1.0f / 32767.0f) * 1.5f + 1.0f;
        r = sub_001C7EE1();
        s->t74 = (float)r * (1.0f / 32767.0f) + 2.0f;
        return;
    }
    if (r == 12) {
        sub_0011F2B0(o, r, s);
        return;
    }
    if (r == 13) {
        M1CE245 *e2 = s->ext278;
        float v = e2->f7C + 50.0f;
        e2->f7C = v;
        float c = 0.0f;
        if (0.0f > v)
            goto st;
        c = 200.0f;
        if (v > 200.0f) {
st:
            e2->f7C = c;
        }
        sub_0011F2B0(o, 13, s);
        return;
    }
    for (;;) ;
}


typedef struct M1JE245 { uint8_t unk00[4]; uint32_t flags4; uint8_t unk08[0x78]; float f80, f84; } M1JE245;
typedef struct M1JS245 { uint8_t unk00[0x20]; uint8_t flags20; uint8_t unk21[0x37]; int32_t st58; uint8_t unk5C[0x21C];
    M1JE245 *ext278; } M1JS245;
void sub_000ED780(void *o);
int  r2_PlayerOutOfReachJ(M1JS245 *obj, M1CO245 *self);   /* 0x120820 regargs: obj=EAX self=ESI */
void sub_0011F2B0j(M1CO245 *obj, int k, M1JS245 *a);        /* 0x11F2B0 regargs: obj=EDI k=EBX */

/* 0x00127710: destroy when flag 0x400; otherwise after the first clip end: big hits (>= 8) or 1-in-4 medium hits
   (>= 4) set flag 0x80 and a recoil value, then pick state 0x2F (flag 0x20), 0x11 (out of reach), 15 (flag 0x80) or
   7/1 by s flag 1 (calls 0x120820 with obj=EAX self=ESI, 0x11F2B0 with obj=EDI k=EBX). */
void m1_HitPick127710(M1CO245 *o, M1JS245 *s)
{
    M1JE245 *e = s->ext278;
    float v;
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
        break;
    default:
        return;
    }
    if (e->f84 >= 8.0f) {
        v = 288.0f;
        goto set;
    }
    if (e->f84 >= 4.0f && !(sub_001C7EE1() & 3)) {
        v = 216.0f;
set:
        e->flags4 |= 0x80;
        e->f80 = v;
    }
    if (e->flags4 & 0x20) {
        sub_0011F2B0j(o, 0x2F, s);
        return;
    }
    if (r2_PlayerOutOfReachJ(s, o)) {
        sub_0011F2B0j(o, 0x11, s);
        return;
    }
    if (e->flags4 & 0x80) {
        sub_0011F2B0j(o, 15, s);
        return;
    }
    sub_0011F2B0j(o, (s->flags20 & 1) ? 7 : 1, s);
}


typedef struct M1KE245 { uint8_t unk00[0x14]; float v14[3]; float f20; uint8_t unk24[0xC]; float v30[4]; uint8_t unk40[8];
    float hp48; } M1KE245;
typedef struct M1KA245 { uint8_t unk00[0x60]; int32_t st60; uint8_t unk64[0x10]; M1KE245 *e74; } M1KA245;
typedef struct M1KM245 { int32_t kind; uint8_t unk04[8]; float dmgC; uint8_t unk10[0x10]; float v20[4]; } M1KM245;
void r4c_FxKill(void *o);   /* regargs: o=EDI */
void sub_00189DA0(void *o, M1KA245 *a, int32_t st);
void sub_001ADB60(float *dst, const float *src, float k);
void sub_000F5D40(void *dst, const void *src);

/* 0x00191EA0: effect message handler: hits (1/2/3/32/34/35) only land in step 3 (32/35 otherwise kill it), 5 hits
   in step 3 or switches to step 4, 10/12 kill, 14/40 -> step 5, 26-28 copy the message vector and -> step 6, 42 blends
   toward it and -> step 7; a landed hit drains +0x48 and kills at 0; returns 1 for landed hits and 14/40 (calls
   0x190A00 with o=EDI). */
int m1_FxMsg191EA0(void *o, M1KA245 *a, M1KM245 *m)
{
    int k = m->kind;
    M1KE245 *e = a->e74;
    switch (k) {
    case 1: case 2: case 3: case 32: case 34: case 35:
        if (a->st60 == 3)
            goto hit;
        if (k == 0x23 || k == 0x20)
            goto kill;
        return 0;
    case 5: {
        int st = a->st60;
        if (st == 4)
            return 0;
        if (st == 3)
            goto hit;
        sub_00189DA0(o, a, 4);
        return 0;
    }
    case 10: case 12:
kill:
        r4c_FxKill(o);
        return 0;
    case 14: case 40:
        sub_00189DA0(o, a, 5);
        return 1;
    case 26: case 27: case 28:
        sub_000F5D40(e->v30, m->v20);
        sub_00189DA0(o, a, 6);
        return 0;
    case 42:
        if (a->st60 == 3)
            return 0;
        sub_001ADB60(e->v14, m->v20, a50_frameUnits);
        e->f20 = 0.0f;
        sub_00189DA0(o, a, 7);
        return 0;
    default:
        return 0;
    }
hit:
    e->hp48 -= m->dmgC;
    if (e->hp48 <= 0.0f)
        r4c_FxKill(o);
    return 1;
}

typedef struct M1WE245 { uint8_t unk00[4]; uint8_t flags4; } M1WE245;
typedef struct M1WS245 { uint8_t unk00[0x20]; uint8_t flags20; uint8_t unk21[0x2B]; uint32_t flags4C; uint8_t unk50[8];
    int32_t st58; uint8_t unk5C[0x18]; float t74; uint8_t unk78[0x200]; M1WE245 *ext278; } M1WS245;
typedef int (*M1WFn245)(M1CO245 *o, M1WS245 *s, const void *t);
extern M1WFn245 m1_chkFn31DBBC[];
extern const uint8_t m1_chkTbl279848[];
void sub_00113040w(M1CO245 *o, M1WS245 *s, int32_t mode);
void sub_00113090(M1CO245 *o, M1WS245 *s, int32_t mode);
void sub_00113090b(M1CO245 *o, M1WS245 *s, int32_t mode);   /* same function (alias stops cl merging calls) */

/* 0x001451E0: steps 0/1 wait for t74 then play 0x3E (step 1) or 0x39 and move to step 2; step 2 on clip end picks
   mode 3 (check passes), 4 (guarded and not flag 1), 7 (flag 1) or 5 with a 60-frame timer, then 0x113040. */
void m1_HitWait1451E0(M1CO245 *o, M1WS245 *s)
{
    int st = s->st58;
    int m;
    if (st < 0)
        return;
    if (st > 1) {
        if (st == 2 && sub_000833E0(o->mdl30)) {
            if (m1_chkFn31DBBC[0](o, s, m1_chkTbl279848)) {
                m = 3;
            } else {
                m = 4;
                if (!(s->ext278->flags4 & 4) || (s->flags20 & 1)) {
                    if (s->flags20 & 1) {
                        m = 7;
                    } else {
                        s->t74 = 60.0f / a50_frameUnits * a50_frameSeconds;
                        m = 5;
                    }
                }
            }
            s->flags4C |= 0x18;
            sub_00113040w(o, s, *(volatile int *)&m);
        }
        return;
    }
    if (s->t74 <= 0.0f) {
        if (st == 1) {
            sub_00113090(o, s, 0x3E);
            s->st58 = 2;
            return;
        }
        sub_00113090b(o, s, 0x39);
        s->st58 = 2;
    }
}

typedef struct M1XS245 { uint8_t unk00[0x58]; int32_t st58; uint8_t unk5C[0x18]; float t74; } M1XS245;
typedef struct M1XO245 { uint8_t unk00[0x30]; void *mdl30; uint8_t unk34[0x2C]; uint8_t pos60[0x10]; } M1XO245;
extern M1XO245 *g_playerObjX;
int32_t sub_00087500(void);
float sub_001B2770(const void *a, const void *b);
void sub_00113040x(M1XO245 *o, M1XS245 *s, int32_t mode);
void sub_00113090x(M1XO245 *o, M1XS245 *s, int32_t mode);

/* 0x001390E0: go to mode 9 when a zone fires, the timer t74 has run out, or the player is within 15; then a
   three-clip sequence playing 0x16, 0 and 0 (wrapping to step 0). */
void m1_Seq1390E0(M1XO245 *o, M1XS245 *s)
{
    if (sub_00087500() || _mm_comige_ss(_mm_setzero_ps(), _mm_load_ss(&s->t74))
        || sub_001B2770(o->pos60, g_playerObjX->pos60) <= 15.0f)
        sub_00113040x(o, s, 9);
    switch (s->st58) {
    case 0:
        if (sub_000833E0(o->mdl30)) {
            sub_00113090x(o, s, 0x16);
            s->st58++;
        }
        return;
    case 1:
        if (sub_000833E0(o->mdl30)) {
            sub_00113090x(o, s, 0);
            s->st58++;
        }
        return;
    case 2:
        if (sub_000833E0(o->mdl30)) {
            sub_00113090x(o, s, 0);
            s->st58 = 0;
        }
        return;
    }
}


typedef struct M1YE245 { uint8_t unk00[0x18]; float f18; } M1YE245;
typedef struct M1YS245 { uint8_t unk00[0xFC]; float fFC, f100; uint8_t unk104[0x174]; M1YE245 *ext278; } M1YS245;
typedef int (*M1YFn245)(M1CO245 *o, M1YS245 *s, const void *t);
extern M1YFn245 b3b_checkFns31D0B8y[];
extern M1YFn245 m1_chkFn31D0CC, m1_chkFn31D0C0;
extern const uint8_t b3b_tbl2797C8[], m1_chkTbl279818[], m1_tbl2797E8[];
float sub_001A3F30(float v);
void b10_SubClampF(float *v, float d, float lim);
void sub_00113480y(M1YS245 *s, int32_t k);
void sub_00113040y(M1CO245 *o, M1YS245 *s, int32_t mode);

/* 0x00140800: pick the follow-up mode: 10 (check 0), 0x29 (check CC, or within 50 units and 40 degrees), 0x13 (check
   C0); otherwise drain +0x18 by 0.25 per frame unit and go to 0x12 once it is at most 20; a chosen mode calls
   0x113480 3 then 0x113040. */
void m1_Follow140800(M1CO245 *o, M1YS245 *s)
{
    float d, ang;
    float *t;
    int m;
    d = sub_001A3F30(s->fFC);
    ang = s->f100;
    sub_000833E0(o->mdl30);
    if (b3b_checkFns31D0B8y[0](o, s, b3b_tbl2797C8)) {
        m = 10;
        goto go;
    }
    if (m1_chkFn31D0CC(o, s, m1_chkTbl279818))
        goto near;
    if (m1_chkFn31D0C0(o, s, m1_tbl2797E8)) {
        m = 0x13;
        goto go;
    }
    if (_mm_comige_ss(_mm_set_ss(50.0f), _mm_load_ss(&d)) && _mm_comige_ss(_mm_set_ss(0.698131740f), _mm_load_ss(&ang))) {
near:
        m = 0x29;
        goto go;
    }
    t = &s->ext278->f18;
    b10_SubClampF(t, a50_frameUnits * 0.25f, 0.0f);
    if (!_mm_comige_ss(_mm_set_ss(20.0f), _mm_load_ss(t)))
        return;
    m = 0x12;
go:
    sub_00113480y(s, 3);
    sub_00113040y(o, s, m);
}

typedef struct M1ZS245 { uint8_t unk00[0x58]; int32_t st58; uint8_t unk5C[0x18]; float t74; uint8_t unk78[0x10];
    float v88[4]; uint8_t unk98[0x1E0]; M1YE245 *ext278; } M1ZS245;
typedef struct M1ZO245 { uint8_t unk00[0x30]; void *mdl30; uint8_t unk34[0x3C]; float v70[4]; } M1ZO245;
void sub_00113480z(M1ZS245 *s, int32_t k);
void sub_000ED780b(void *o);   /* same function (alias stops cl merging calls) */
void sub_00113040z(M1ZO245 *o, M1ZS245 *s, int32_t mode);

/* 0x0013F2C0: four-step exit: 0 destroy on clip end; 1 drain +0x18 by frame units and at 0 go to mode 10; 2 on clip
   end save o's position and set a 0.2 timer; 3 blend o back toward it (5x the time left) and destroy when done. */
void m1_Exit13F2C0(M1ZO245 *o, M1ZS245 *s)
{
    float *t;
    switch (s->st58) {
    case 0:
        if (sub_000833E0(o->mdl30))
            sub_000ED780(o);
        return;
    case 1:
        t = &s->ext278->f18;
        b10_SubClampF(t, a50_frameUnits, 0.0f);
        if (_mm_comige_ss(_mm_setzero_ps(), _mm_load_ss(t))) {
            sub_00113480z(s, 9);
            sub_00113040z(o, s, 10);
        }
        return;
    case 2:
        if (sub_000833E0(o->mdl30)) {
            sub_000F5D40(s->v88, o->v70);
            s->t74 = 0.2f;
            s->st58++;
        }
        return;
    case 3:
        if (_mm_comige_ss(_mm_setzero_ps(), _mm_load_ss(&s->t74))) {
            sub_000ED780b(o);
            return;
        }
        sub_001ADB60(o->v70, s->v88, s->t74 * 5.0f);
        return;
    }
}

typedef struct M1QE245 { uint8_t unk00[4]; uint8_t flags4; uint8_t unk05[0x13]; float f18; } M1QE245;
typedef struct M1QS245 { uint8_t unk00[0x58]; int32_t st58; uint8_t unk5C[0xC]; float t68; uint8_t unk6C[8]; float t74;
    uint8_t unk78[0x88]; float f100; uint8_t unk104[0x174]; M1QE245 *ext278; } M1QS245;
typedef int (*M1QFn245)(M1CO245 *o, M1QS245 *s, const void *t);
extern M1QFn245 b3b_checkFns31D0B8q[];
void sub_00113040q(M1CO245 *o, M1QS245 *s, int32_t mode);
void sub_00113040r(M1CO245 *o, M1QS245 *s, int32_t mode);   /* same function (aliases stop cl merging calls) */

/* 0x00141FD0: step 0 waits 52 frames, step 1 leaves via mode 10 when check 0 passes; on clip end pick mode 12 with a
   60-frame (flag 0x10) or zero timer, or 0x29/0x12 by the +0x18 meter (>= 120 when within 30 degrees, >= 160
   otherwise). */
void m1_Next141FD0(M1CO245 *o, M1QS245 *s)
{
    M1QE245 *e;
    float t;
    switch (s->st58) {
    case 0:
        if (s->t68 >= 52.0f / a50_frameUnits * a50_frameSeconds)
            s->st58 = 1;
        break;
    case 1:
        if (b3b_checkFns31D0B8q[0](o, s, b3b_tbl2797C8)) {
            sub_00113040q(o, s, 10);
            return;
        }
        break;
    }
    if (!sub_000833E0(o->mdl30))
        return;
    e = s->ext278;
    if (e->flags4 & 0x10) {
        t = 60.0f / a50_frameUnits * a50_frameSeconds;
        goto setc;
    }
    if (s->f100 <= 30.0f) {
        if (e->f18 >= 120.0f) {
m29:
            sub_00113040r(o, s, 0x29);
            return;
        }
        sub_00113040q(o, s, 0x12);
        return;
    }
    if (e->f18 >= 160.0f)
        goto m29;
    t = 0.0f;
setc:
    s->t74 = *(volatile float *)&t;
    sub_00113040q(o, s, 12);
}

typedef struct M1PE245 { uint8_t unk00[0x94]; int32_t n94; } M1PE245;
typedef struct M1PS245 { uint8_t unk00[0x278]; M1PE245 *ext278; } M1PS245;
int32_t sub_001133E0(M1PS245 *s, int32_t k);
int32_t sub_00145800(int32_t lo, int32_t hi);
int  r2_PlayerOutOfReachP(M1PS245 *obj, M1CO245 *self);   /* 0x120820 regargs: obj=EAX self=ESI */
void sub_0011F2B0p(M1CO245 *obj, int k, M1PS245 *a);        /* 0x11F2B0 regargs: obj=EDI k=EBX */

/* 0x00121E50: unless busy (0x1133E0 7): out of reach -> reset the counter and state 0x11; after 4 rounds -> reset and
   state 1; otherwise add 1-4 rounds and state 4 (calls 0x120820 with obj=EAX self=ESI, 0x11F2B0 with obj=EDI k=EBX). */
void m1_Rounds121E50(M1CO245 *o, M1PS245 *s)
{
    M1PE245 *e = s->ext278;
    if (sub_001133E0(s, 7))
        return;
    if (r2_PlayerOutOfReachP(s, o)) {
        e->n94 = 0;
        sub_0011F2B0p(o, 0x11, s);
        return;
    }
    if (e->n94 >= 4) {
        e->n94 = 0;
        sub_0011F2B0p(o, 1, s);
        return;
    }
    e->n94 += sub_00145800(1, 4);
    sub_0011F2B0p(o, 4, s);
}

typedef struct M1TT245 { uint8_t unk00[4]; int32_t kind4; uint8_t unk08[4]; uint8_t flagsC; } M1TT245;
typedef struct M1TS245 { uint8_t unk00[0x58]; int32_t st58; uint8_t unk5C[0x9C]; int32_t nF8; uint8_t unkFC[8];
    M1TT245 *tgt104; } M1TS245;
int32_t sub_001133E0t(M1TS245 *s, int32_t k);
int  r2_PlayerOutOfReachT(M1TS245 *obj, M1CO245 *self);   /* 0x120820 regargs: obj=EAX self=ESI */
void sub_0011F2B0t(M1CO245 *obj, int k, M1TS245 *a);        /* 0x11F2B0 regargs: obj=EDI k=EBX */

/* 0x001263B0: step 0 hangs; step 10 waits until not busy, step 20 waits for the clip, both then go to step 99; step 99
   picks state 0x11 (out of reach), 0x15 (in mode 1 locked on an active kind-13 target) or 1 (calls 0x120820 with
   obj=EAX self=ESI, 0x11F2B0 with obj=EDI k=EBX). */
void m1_Step1263B0(M1CO245 *o, M1TS245 *s)
{
    int k;
    switch (s->st58) {
    case 0:
        for (;;) ;
    case 10:
        if (!sub_001133E0t(s, 7))
            s->st58 = 99;
        return;
    case 20:
        if (sub_000833E0(o->mdl30))
            s->st58 = 99;
        return;
    case 99:
        if (r2_PlayerOutOfReachT(s, o)) {
            sub_0011F2B0t(o, 0x11, s);
            return;
        }
        k = 1;
        if (s->nF8 == 1 && (s->tgt104->flagsC & 1) && s->tgt104->kind4 == 13)
            k = 0x15;
        sub_0011F2B0t(o, k, s);
        return;
    }
}
