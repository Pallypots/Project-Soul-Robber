/* Area m1, file 346: two enemy hit handlers. Names inferred. */
#include <stdint.h>

typedef struct M1Hit346 { int32_t kind00; uint8_t unk04[8]; float dmg0C; uint8_t unk10[0x10]; float v20[4]; } M1Hit346;
typedef struct M1St346a { uint8_t unk00[0x26]; int16_t w26; uint8_t unk28[0x34 - 0x28]; float v34[3]; float f40; } M1St346a;
typedef struct M1Ai346 {
    uint8_t unk000[0x50]; int32_t n50; uint8_t unk054[0x74 - 0x54]; float f74; uint8_t unk078[0x274 - 0x78];
    float f274; void *s278;
} M1Ai346;
typedef struct M1Ob346 { uint8_t unk00[0x30]; void *anim30; } M1Ob346;
typedef struct M1St346b { uint32_t f00; float f04; } M1St346b;
extern float m1_frameTime42C858, m1_frameRate42C85C;
void sub_000832D0(void *a, int k);
void sub_001ADB60(float *d, const float *s, float k);   /* d = s * k */
int  sub_0017CEC0(void);                                /* regargs */
void sub_00175220(void *o);
void sub_001131E0(void *e, float dmg);
void sub_000C75E0(void *o);
int  m1_AiGoto113040(void *o, void *e, int st);

/* 0x17D280: hit handler (ignored in state 1): stop the animation, then by hit kind flag a
   stagger (state 7), bounce off (state 3, returns 1), knock back along the hit (state 4),
   be grabbed (state 5 when 0x17CEC0 allows, else knock back into state 6), or in state 6
   only go to 8. Returns 1 only for the bounce. */
int m1_HitReact17D280(M1Ob346 *o, M1Ai346 *e, M1Hit346 *hit) {
    M1St346a *s = (M1St346a *)e->s278;
    if (e->n50 == 1)
        return 0;
    sub_000832D0(o->anim30, 0);
    switch (hit->kind00) {
    case 1: case 2: case 3: case 5: case 10: case 29: case 32: case 34: case 35:
        s->w26 = 1;
        m1_AiGoto113040(o, e, 7);
        return 0;
    case 14: case 40:
        m1_AiGoto113040(o, e, 3);
        return 1;
    case 26: case 27: case 28:
        sub_001ADB60(s->v34, hit->v20, m1_frameTime42C858);
        s->f40 = 0.0f;
        m1_AiGoto113040(o, e, 4);
        return 0;
    case 42:
        if (sub_0017CEC0()) {
            m1_AiGoto113040(o, e, 5);
            return 0;
        }
        sub_001ADB60(s->v34, hit->v20, m1_frameTime42C858);
        s->f40 = 0.0f;
        m1_AiGoto113040(o, e, 6);
        return 0;
    case 12:
        if (e->n50 == 6)
            m1_AiGoto113040(o, e, 8);
        return 0;
    }
    return 0;
}

/* 0x1756A0: hit handler: ignored while invulnerable (+4 timer running or flag 2). Most
   hit kinds start the 20/s flinch (returns 1); kind 36 deals no damage. Applies the damage
   (cancelling the +0x74 timer in state 6 unless kind 0x20) and enters state 7 when health
   runs out (kind 0x20 first releases the grab). */
int m1_HitReact1756A0(M1Ob346 *o, M1Ai346 *e, M1Hit346 *hit) {
    M1St346b *s = (M1St346b *)e->s278;
    int r = 0;
    float dmg;
    if (s->f04 > 0.0f || (s->f00 & 2))
        return 0;
    dmg = hit->dmg0C;
    switch (hit->kind00) {
    case 1: case 2: case 3: case 5: case 6: case 7: case 8: case 9: case 10: case 11:
    case 29: case 30: case 31: case 32: case 34: case 35:
        r = 1;
        sub_00175220(o);
        s->f00 |= 0x200;
        s->f04 = m1_frameRate42C85C * 20.0f;
        break;
    case 36:
        dmg = 0.0f;
        break;
    }
    if (hit->kind00 != 0x20 && e->n50 == 6)
        e->f74 = -1.0f;
    sub_001131E0(e, dmg);
    if (0.0f >= e->f274) {
        if (hit->kind00 == 0x20)
            sub_000C75E0(o);
        m1_AiGoto113040(o, e, 7);
    }
    return r;
}

typedef struct M1St346c { uint32_t f00; uint8_t unk04[4]; float f08; } M1St346c;

/* 0x176810: twin of 0x1756A0 for another enemy: invulnerable while the +8 timer runs or
   flag 0x20 is set; the flinch sets flag 0x100 and a 20-unit timer; the +0x74 timer is
   cancelled in state 7, and running out of health enters state 8. */
int m1_HitReact176810(M1Ob346 *o, M1Ai346 *e, M1Hit346 *hit) {
    M1St346c *s = (M1St346c *)e->s278;
    int r = 0;
    float dmg;
    if (s->f08 > 0.0f || (s->f00 & 0x20))
        return 0;
    dmg = hit->dmg0C;
    switch (hit->kind00) {
    case 1: case 2: case 3: case 5: case 6: case 7: case 8: case 9: case 10: case 11:
    case 30: case 31: case 32: case 34: case 35:
        sub_00175220(o);
        s->f00 |= 0x100;
        r = 1;
        s->f08 = 20.0f / m1_frameTime42C858 * m1_frameRate42C85C;
        break;
    case 36:
        dmg = 0.0f;
        break;
    }
    if (hit->kind00 != 0x20 && e->n50 == 7)
        e->f74 = -1.0f;
    sub_001131E0(e, dmg);
    if (0.0f >= e->f274) {
        if (hit->kind00 == 0x20)
            sub_000C75E0(o);
        m1_AiGoto113040(o, e, 8);
    }
    return r;
}

/* 0x1779A0: identical copy of 0x1756A0 used by another enemy type. */
int m1_HitReact1779A0(M1Ob346 *o, M1Ai346 *e, M1Hit346 *hit) {
    M1St346b *s = (M1St346b *)e->s278;
    int r = 0;
    float dmg;
    if (s->f04 > 0.0f || (s->f00 & 2))
        return 0;
    dmg = hit->dmg0C;
    switch (hit->kind00) {
    case 1: case 2: case 3: case 5: case 6: case 7: case 8: case 9: case 10: case 11:
    case 29: case 30: case 31: case 32: case 34: case 35:
        r = 1;
        sub_00175220(o);
        s->f00 |= 0x200;
        s->f04 = m1_frameRate42C85C * 20.0f;
        break;
    case 36:
        dmg = 0.0f;
        break;
    }
    if (hit->kind00 != 0x20 && e->n50 == 6)
        e->f74 = -1.0f;
    sub_001131E0(e, dmg);
    if (0.0f >= e->f274) {
        if (hit->kind00 == 0x20)
            sub_000C75E0(o);
        m1_AiGoto113040(o, e, 7);
    }
    return r;
}

typedef struct M1St346d {
    void *p00; void *p04; void *p08; void *p0C; uint8_t unk10[0x1C - 0x10];
    float f1C, f20, f24, f28; uint8_t unk2C[4]; int16_t w30;
} M1St346d;
typedef struct M1Ob346d { uint8_t unk00[0x0C]; uint32_t f0C; uint32_t f10; uint8_t unk14[0x50 - 0x14]; float v50[4]; float v60[4]; } M1Ob346d;
void sub_000F5D40(void *d, const void *s);
void *sub_00036750(void *o, int k);
void sub_0001D700(void *o);
void sub_00033A40(void *p);
void m1_SpawnKindED630(int a, int b, const float *pos, const float *vel, int k);

/* 0x1846E0: hit handler for a breakable object: kinds 34/35/10/11 only land when their
   cool-down slot is free (34 also spawns the hit flash); then the damage is taken and,
   when it breaks, the object is switched off, its effect released, the break debris
   spawned and the owner told. Returns 1 when the hit landed. */
int m1_HitBreak1846E0(M1Ob346d *o, M1Ai346 *e, M1Hit346 *hit) {
    M1St346d *s = (M1St346d *)e->s278;
    float vel[4];
    float pos[4];
    switch (hit->kind00) {
    case 1: case 2: case 3: case 5: case 7: case 9: case 32:
        break;
    case 34:
        s->f1C = 0.5f;
        if (s->p0C)
            return 0;
        s->p0C = sub_00036750(o, 2);
        break;
    case 35:
        if (s->f20 > 0.0f)
            return 0;
        s->f20 = 1.5f;
        break;
    case 10:
        if (s->f28 > 0.0f)
            return 0;
        s->f28 = 1.3f;
        break;
    case 11:
        if (s->f24 > 0.0f)
            return 0;
        s->f24 = 1.3f;
        break;
    default:
        return 0;
    }
    e->f274 = e->f274 - hit->dmg0C;
    if (0.0f >= e->f274) {
        e->f274 = 0.0f;
        sub_000F5D40(vel, o->v50);
        sub_000F5D40(pos, o->v60);
        o->f0C &= ~0xE0u;
        o->f10 |= 0x44D;
        m1_AiGoto113040(o, s->p08, 0);
        sub_0001D700(o);
        s->p04 = o;
        if (s->p0C) {
            sub_00033A40(s->p0C);
            s->p0C = 0;
        }
        m1_SpawnKindED630(4, 0x26, pos, vel, s->w30);
        m1_AiGoto113040(s->p00, s->p08, 2);
    }
    return 1;
}
