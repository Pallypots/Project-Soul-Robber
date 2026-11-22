/* Area m1, file 343: enemy follow-up picker after a turn. Names inferred. */
#include <stdint.h>

typedef struct M1V343 { float v[4]; } M1V343;
typedef struct M1St343 { uint8_t unk00[4]; uint32_t f04; uint8_t unk08[0x14 - 8]; float f14; } M1St343;
typedef struct M1Ai343 {
    uint8_t unk000[0x4C]; uint32_t f4C; uint8_t unk050[0x58 - 0x50]; int32_t n58; uint8_t unk05C[0x68 - 0x5C];
    float f68; uint8_t unk06C[0x74 - 0x6C]; float f74; uint8_t unk078[0xFC - 0x78]; float fFC; float f100;
    uint8_t unk104[0x270 - 0x104]; float f270; float f274; M1St343 *s278;
} M1Ai343;
typedef struct M1Ob343 { uint8_t unk00[8]; int32_t i08; uint8_t unk0C[0x30 - 0x0C]; void *anim30; } M1Ob343;
typedef struct M1Tm343 { uint8_t unk00[0x10]; float f10; float f14; } M1Tm343;
typedef int (*M1Fn343)(M1Ob343 *o, M1Ai343 *e, const M1V343 *v);
extern M1Fn343 r2_fn31B0C4f[];
extern M1V343  r2_vec279598[];
extern float m1_frameTime42C858, m1_frameRate42C85C;
extern float m1_g3F7504;
int      sub_000833E0(void *a);
M1Tm343 *sub_001133E0(void *e, int k);
void     sub_00113370(void *e, M1Tm343 *t);
void     sub_00113480(void *e, int k);
int      m1_AiGoto113040(void *o, void *e, int st);
int      r2_GetHitKindF(M1Ai343 *e, int *out);             /* 0x11B0D0 regargs: obj=ECX out=EDX */
void    *r2_SelectKind(int kind);                           /* 0x11B140 kind=EAX */
int      r2_CallTbl31B0C4h(int a, M1Ai343 *e, M1Ob343 *o);  /* 0x11B020 regargs: a=EAX e=EDX, o on stack */
float    sub_001A3F30(float x);                             /* fabs */
int      sub_001C7EE1(void);                                /* rand */

/* 0x11C950: step 0 turns towards the target (a timed turn while the angle is 5..60
   degrees) and after 38 units ends it; step 1, when the animation ends, picks the next
   state: 3 (table check), the hit kind, 0xC (flag 0x100), then for a close target in front
   (+0x14 at least 30, +0x100 within 60, angle under 30 degrees) 0xB (no kind, half the time),
   0xA (health at least half) or 0xD; otherwise 0xF (table check) or 5 with the timer
   cleared. */
void m1_AiTurnPick11C950(M1Ob343 *o, M1Ai343 *e) {
    M1St343 *s = e->s278;
    M1Tm343 *t;
    int k, k2;
    switch (e->n58) {
    case 0:
        t = sub_001133E0(e, 3);
        if (e->fFC >= 0.0872664675f && 1.04719758f >= e->fFC)
            t->f10 = m1_frameTime42C858 * 0.0130899698f;
        else
            t->f10 = 0.0f;
        t->f14 = 0.0f;
        if (!(e->f68 >= 38.0f / m1_frameTime42C858 * m1_frameRate42C85C))
            return;
        sub_00113370(e, t);
        e->n58++;
        return;
    case 1:
        if (!sub_000833E0(o->anim30))
            return;
        if (r2_fn31B0C4f[0](o, e, &r2_vec279598[0])) {
            k = 3;
        } else if (r2_GetHitKindF(e, &k2)) {
            k = k2;
        } else if (e->f4C & 0x100) {
            k = 0xC;
        } else if (!(s->f04 & 8)) {
            goto plain;
        } else if (e->s278->f14 >= 30.0f && 60.0f >= e->f100 && 0.523598790f > sub_001A3F30(e->fFC)) {
            if (!r2_SelectKind(o->i08) && sub_001C7EE1() % 2 < 1)
                k = 0xB;
            else if (e->f274 >= e->f270 * 0.5f)
                k = 0xA;
            else
                k = 0xD;
        } else if (r2_CallTbl31B0C4h(1, e, o)) {
            k = 0xF;
        } else {
        plain:
            e->f74 = 0.0f;
            k = 5;
        }
        if (e->f4C & 0x100)
            m1_g3F7504 = 240.0f / m1_frameTime42C858 * m1_frameRate42C85C;
        e->f4C = (e->f4C & ~0x100u) | 0x10;
        sub_00113480(e, 2);
        m1_AiGoto113040(o, e, k);
        return;
    }
}

/* 0x11CB80: three-step version: step 0 turns right (10..60 degrees) for 34 units, step 1
   turns left (-180..-10 degrees) for 60 units and ends the turn, step 2 picks the next state
   as 0x11C950 does, but the close-target test needs +0x14 at least 40 and the shared
   cooldown at 0x3F7504 run out. */
void m1_AiTurnPick11CB80(M1Ob343 *o, M1Ai343 *e) {
    M1St343 *s;
    M1Tm343 *t;
    int k, k2;
    switch (e->n58) {
    case 0:
        t = sub_001133E0(e, 3);
        if (e->fFC >= 0.174532935f && 1.04719758f >= e->fFC)
            t->f10 = m1_frameTime42C858 * 0.0174532924f;
        else
            t->f10 = 0.0f;
        t->f14 = 0.0f;
        if (!(e->f68 >= 34.0f / m1_frameTime42C858 * m1_frameRate42C85C))
            return;
        e->n58++;
        return;
    case 1:
        t = sub_001133E0(e, 3);
        if (e->fFC >= -3.14159274f && -0.174532935f >= e->fFC)
            t->f14 = m1_frameTime42C858 * -0.0261799395f;
        else
            t->f14 = 0.0f;
        t->f10 = 0.0f;
        if (!(e->f68 >= 60.0f / m1_frameTime42C858 * m1_frameRate42C85C))
            return;
        sub_00113370(e, t);
        e->n58++;
        return;
    case 2:
        if (!sub_000833E0(o->anim30))
            return;
        if (r2_fn31B0C4f[0](o, e, &r2_vec279598[0])) {
            k = 3;
        } else if (r2_GetHitKindF(e, &k2)) {
            k = k2;
        } else if (e->f4C & 0x100) {
            k = 0xC;
        } else if ((s = e->s278)->f14 >= 40.0f && 60.0f >= e->f100 && 0.523598790f > sub_001A3F30(e->fFC)
                   && 0.0f >= m1_g3F7504) {
            if (!r2_SelectKind(o->i08) && sub_001C7EE1() % 2 < 1)
                k = 0xB;
            else if (e->f274 >= e->f270 * 0.5f)
                k = 0xA;
            else
                k = 0xD;
        } else if (r2_CallTbl31B0C4h(1, e, o)) {
            k = 0xF;
        } else {
            e->f74 = 0.0f;
            k = 5;
        }
        if (e->f4C & 0x100)
            m1_g3F7504 = 240.0f / m1_frameTime42C858 * m1_frameRate42C85C;
        e->f4C = (e->f4C & ~0x100u) | 0x10;
        sub_00113480(e, 2);
        m1_AiGoto113040(o, e, k);
        return;
    }
}
