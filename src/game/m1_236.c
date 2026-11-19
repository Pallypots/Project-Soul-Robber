/* Area m1, file 236: actor state helpers (register-argument callers per docs/verification.md). Names inferred. */
#include <stdint.h>

typedef struct M1E236 { uint8_t unk00[0x20]; float v20, v24, v28, v2C; } M1E236;
typedef struct M1O236 { uint8_t unk00[0x30]; void *mdl30; uint8_t unk34[0xF4]; uint8_t flags128; } M1O236;
typedef struct M1S236 { uint8_t unk00[0x58]; int32_t st58; uint8_t unk5C[0x278 - 0x5C]; M1E236 *ext278; } M1S236;
extern float a50_frameUnits;
int32_t sub_000833E0(void *m);
void sub_00186470(void *obj, void *act, int state);   /* regargs: obj=EBX act=EDI state=stack */

/* 0x00187810: three-step landing: wait for the clip, wait for ground flags 0x18, then state 1 with a reset
   velocity; while in steps 0-1 damp x/z velocity by 5% per frame unit (calls 0x186470 with obj=EBX act=EDI). */
void m1_Land187810(M1O236 *o, M1S236 *s)
{
    M1E236 *e = s->ext278;
    switch (s->st58) {
    case 0:
        if (sub_000833E0(o->mdl30))
            s->st58++;
        break;
    case 1:
        if (o->flags128 & 0x18)
            s->st58 = 2;
        break;
    case 2: {
        M1E236 *e2;
        sub_00186470(o, s, 1);
        e2 = s->ext278;
        e2->v28 = 0.0f;
        e2->v24 = 0.0f;
        e2->v20 = 0.0f;
        e2->v2C = 1.0f;
        break;
    }
    }
    if (s->st58 <= 1) {
        e->v28 *= 1.0f - a50_frameUnits * 0.05f;
        e->v20 *= 1.0f - a50_frameUnits * 0.05f;
    }
}

typedef struct M1HE236 { uint8_t unk00[4]; uint32_t flags4; } M1HE236;
typedef struct M1HS236 { uint8_t unk00[0x20]; uint32_t flags20; uint8_t unk24[0x28]; uint32_t flags4C; uint8_t unk50[0x24];
    float t74; uint8_t unk78[0x278 - 0x78]; M1HE236 *ext278; } M1HS236;
typedef struct M1HV236 { float v[4]; } M1HV236;
typedef int (*M1HFn236)(M1O236 *o, M1HS236 *s, const M1HV236 *v);
extern M1HFn236 m1_chkFn31DBBC[];
extern M1HV236 m1_chkTbl279848[];
extern float a50_frameSeconds;
int  r3b_Dispatch143740(int idx, M1HS236 *b, M1O236 *a);   /* regargs: idx=EAX b=EDX a=stack */
void sub_00113040(M1O236 *o, M1HS236 *s, int32_t mode);

/* 0x001452D0: when the clip ends pick the follow-up mode (3 if check 0 passes, 4 while guarded, 8 after a
   successful dispatch, 7, or 5 with a 60-frame timer) and hand over to 0x113040 (calls 0x143740 with idx=EAX b=EDX). */
void m1_NextMode1452D0(M1O236 *o, M1HS236 *s)
{
    int m;
    uint32_t f;
    if (!sub_000833E0(o->mdl30))
        return;
    if (m1_chkFn31DBBC[0](o, s, &m1_chkTbl279848[0])) {
        m = 3;
    } else {
        m = 4;
        if (!(s->ext278->flags4 & 4) || (s->flags20 & 1)) {
            f = s->flags20;
            if (f & 0x10000) {
                if (r3b_Dispatch143740((f & 1) ? 3 : 2, s, o)) {
                    s->ext278->flags4 |= 2;
                    m = 8;
                    goto done;
                }
            } else if (f & 1) {
                m = 7;
                goto done;
            }
            s->t74 = 60.0f / a50_frameUnits * a50_frameSeconds;
            m = 5;
        }
    }
done:
    s->flags4C |= 0x18;
    sub_00113040(o, s, *(volatile int *)&m);
}

typedef struct M1WS236 { uint8_t unk00[0x4C]; uint32_t flags4C; uint8_t unk50[8]; int32_t st58; uint8_t unk5C[0x18];
    float t74; } M1WS236;
typedef struct M1WV236 { float v[4]; } M1WV236;
typedef int (*M1WFn236)(M1O236 *o, M1WS236 *s, const M1WV236 *v);
extern M1WFn236 r2_fn31B0C4[];
extern M1WV236 r2_vec279598[];
int  r2_GetHitKind(M1WS236 *obj, int *out);   /* regargs: obj=ECX out=EDX */
void sub_00113040w(M1O236 *o, M1WS236 *s, int32_t mode);
void sub_00113090(M1O236 *o, M1WS236 *s, int32_t mode);
void sub_00113090b(M1O236 *o, M1WS236 *s, int32_t mode);   /* same function (alias stops cl merging calls) */

/* 0x0011D980: steps 0/1 wait for t74 to run out then play 0x3E (step 1) or 0x39 and move to step 2; step 2 waits
   for the clip and hands over to 0x113040 with mode 3 (handler 0 accepts), the hit kind, or 12 (calls 0x11B0D0 with
   obj=ECX out=EDX). */
void m1_HitWait11D980(M1O236 *o, M1WS236 *s)
{
    int st = s->st58;
    int m, k;
    if (st < 0)
        return;
    if (st > 1) {
        if (st == 2 && sub_000833E0(o->mdl30)) {
            if (r2_fn31B0C4[0](o, s, &r2_vec279598[0])) {
                m = 3;
            } else {
                m = 12;
                if (r2_GetHitKind(s, &k))
                    m = k;
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

typedef struct M1JE236 { uint8_t unk00[8]; uint32_t flags8; } M1JE236;
typedef struct M1JS236 { uint8_t unk00[0x58]; int32_t st58; uint8_t unk5C[0x278 - 0x5C]; M1JE236 *ext278; } M1JS236;
int32_t sub_00145780(M1O236 *o, float r);
void sub_00113480(M1JS236 *s, int32_t k);
int32_t b4c_Enter1456E0(M1O236 *o, M1JS236 *s, int32_t a, int32_t b);
void sub_0001D4E0(M1O236 *o);
void r3_SetStateB(M1O236 *obj, M1JS236 *act, int state);    /* regargs: obj=ESI act=EDI state=stack */
void r3_SetStateB2(M1O236 *obj, M1JS236 *act, int state);   /* same function (aliases stop cl merging calls) */
void r3_SetStateB3(M1O236 *obj, M1JS236 *act, int state);

/* 0x001372E0: four-step sequence: (player within 12 -> 0x113480 1) wait for the clip, enter 0x15, wait twice, then
   state 3 (flags 1+0x80), 5 (flag 1) or 1 (calls 0x135A70 with obj=ESI act=EDI). */
void m1_Seq1372E0(M1O236 *o, M1JS236 *s)
{
    M1JE236 *e = s->ext278;
    switch (s->st58) {
    case 0:
        if (sub_00145780(o, 12.0f))
            sub_00113480(s, 1);
        if (!sub_000833E0(o->mdl30))
            return;
        s->st58++;
    case 1:
        if (b4c_Enter1456E0(o, s, 0x15, 0) == 1)
            sub_0001D4E0(o);
        s->st58++;
        return;
    case 2:
        if (!sub_000833E0(o->mdl30))
            return;
        s->st58++;
    case 3:
        if (!sub_000833E0(o->mdl30))
            return;
        if (e->flags8 & 1) {
            if ((int8_t)e->flags8 < 0) {
                r3_SetStateB(o, s, 3);
                return;
            }
            r3_SetStateB2(o, s, 5);
            return;
        }
        r3_SetStateB3(o, s, 1);
        return;
    }
}

typedef struct M1Ac236 { uint8_t unk00[0x20]; } M1Ac236;
typedef struct M1Ec236 { uint8_t unk00[0x968]; } M1Ec236;
extern M1Ac236 *g_acb_table;
extern M1Ec236 *aec_3F0744;
void *a50_Alloc(int32_t pool, int32_t size, int32_t a, int32_t b);
void sub_00075F00(M1Ec236 *e);
void sub_0003FAB0(M1Ac236 *a, M1Ec236 *e);
void a60_FlagsClear(M1Ec236 *e, uint32_t f);
void a60_FlagsSet(M1Ec236 *e, uint32_t f);
void sub_00018620(M1Ac236 *a, int32_t kind);

/* 0x000E0260: allocate the four 0x20-byte controller records and four 0x968-byte channel records, initialise and
   link each pair, set flags 0x100 (clear 0x80) and give controllers 0-3 kinds 0x11/0x12/0x13/0. */
void m1_ChanInit0E0260(void)
{
    int i, k;
    g_acb_table = (M1Ac236 *)a50_Alloc(8, 0x80, 0, 0);
    aec_3F0744 = (M1Ec236 *)a50_Alloc(8, 0x25A0, 0, 0);
    for (i = 0; i < 4; i++) {
        sub_00075F00(&aec_3F0744[i]);
        sub_0003FAB0(&g_acb_table[i], &aec_3F0744[i]);
        a60_FlagsClear(&aec_3F0744[i], 0x80);
        a60_FlagsSet(&aec_3F0744[i], 0x100);
        switch (*(volatile int *)&i) {
        case 0: k = 0x11; break;
        case 1: k = 0x12; break;
        case 2: k = 0x13; break;
        case 3: k = 0; break;
        default: continue;
        }
        sub_00018620(&g_acb_table[i], k);
    }
}

typedef struct M1Zone236 { int32_t used0; uint8_t unk04[0x1C]; } M1Zone236;
typedef struct M1ZTab236 { uint8_t unk00[4]; int32_t n4; uint8_t unk08[8]; M1Zone236 z10[1]; } M1ZTab236;
typedef struct M1Nd236 { uint8_t unk00[0x74]; float y74; } M1Nd236;
typedef struct M1Md236 { uint8_t unk00[0xC4]; uint8_t *nodesC4; } M1Md236;
typedef struct M1Pl236 { uint8_t unk00[0x20]; M1Md236 *mdl20; uint8_t unk24[0x3C]; uint8_t pos60[0x10]; } M1Pl236;
extern M1ZTab236 *a80_g3ED248;
extern int32_t a80_g3ED238, a80_g3ED23C;
extern float r6c_target3ED224[];
extern M1Pl236 *g_playerObj;
void sub_000F5D40(void *dst, const void *src);
float sub_001B2730(const float *a, const float *b);
int  sub_000875E0(M1Zone236 *z, float *pos, float *last);   /* regargs: z=ESI pos=EDI last=EBX */

/* 0x00087960: zone trigger check: if the player (at node 0x300's height) moved since last frame, test each unused
   zone and latch a80_g3ED238 when one fires; remember the position; returns 0 (calls 0x875E0 with z=ESI pos=EDI
   last=EBX). */
int m1_ZoneCheck087960(void)
{
    float p[4];
    M1Nd236 *volatile b;
    int i;
    if (!a80_g3ED248)
        return 0;
    a80_g3ED23C = -1;
    if (a80_g3ED238)
        return 0;
    b = (M1Nd236 *)(g_playerObj->mdl20->nodesC4 + 0x300);
    sub_000F5D40(p, g_playerObj->pos60);
    p[1] = b->y74;
    if (sub_001B2730(p, r6c_target3ED224) < 0.0001f)
        return 0;
    for (i = 0; i < a80_g3ED248->n4; i++) {
        M1Zone236 *z = &a80_g3ED248->z10[i];
        if (!z->used0 && sub_000875E0(z, p, r6c_target3ED224) == 1) {
            a80_g3ED238 = 1;
            break;
        }
    }
    sub_000F5D40(r6c_target3ED224, p);
    return 0;
}
