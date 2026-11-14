/* Area m1, file 162: enemy wind-up states (revisited). Names inferred. */
#include <stdint.h>

typedef struct M1Rg162 { uint8_t unk00[0xC]; uint16_t w0C; uint8_t unk0E[2]; float t10; uint8_t unk14[0xC]; float x20; } M1Rg162;
typedef struct M1Ob162 { uint8_t unk00[0x30]; void *anim30; } M1Ob162;
typedef struct M1Ai162 { uint8_t unk00[0x278]; M1Rg162 *rig278; } M1Ai162;
extern uint32_t m1_level413178;
extern float m1_frameRate42C85C;
extern float m1_spdA27A874[3];
extern float m1_spdB27A880[3];
int  sub_000F5D00(M1Ob162 *o);
void sub_000832D0(void *a, int id);
int  m1_CamMode0F40B0(void);
int  m1_AiGoto113040(M1Ob162 *o, M1Ai162 *e, int st);

/* 0x1811F0: wind-up: start the pose, wait half a second, then attack at the level's speed. */
void m1_AiWindUp1811F0(M1Ob162 *o, M1Ai162 *e) {
    M1Rg162 *r = e->rig278; uint32_t n; int volatile v;
    switch (r->w0C) {
    case 0:
        if (sub_000F5D00(o) == 0) return;
        sub_000832D0(o->anim30, 2);
        r->w0C++;
        r->t10 = 0.0f;
        return;
    case 1:
        if (r->t10 > 0.5f) {
            n = m1_level413178;
            if (n > 2) n = 2;
            if (m1_CamMode0F40B0() == 0) { r->x20 = m1_spdA27A874[n]; v = m1_AiGoto113040(o, e, 2); return; }
            r->x20 = m1_spdB27A880[n]; v = m1_AiGoto113040(o, e, 2);
            return;
        }
        r->t10 += m1_frameRate42C85C;
        return;
    }
}

typedef struct M1Ai162b { uint8_t unk00[0x20]; uint8_t b20; uint8_t unk21[0x2B]; uint32_t flags4C; uint8_t unk50[0x24]; float t74; } M1Ai162b;
typedef int (*M1Check162)(M1Ob162 *o, M1Ai162b *e, const uint8_t *tbl);
extern M1Check162 m1_chkFn31D0B8, m1_chkFn31D0C0;
extern const uint8_t m1_chkTbl2797C8[], m1_tbl2797E8[];
extern float m1_frameTime42C858;
int sub_000833E0(void *a);
int sub_001C7EE1(void);

/* 0x141AD0: pick the enemy's next move when its animation ends (attack, block, or idle a while). */
void m1_AiChoose141AD0(M1Ob162 *o, M1Ai162b *e) {
    int volatile v; float t;
    if (sub_000833E0(o->anim30) == 0) return;
    if (m1_chkFn31D0B8(o, e, m1_chkTbl2797C8)) { int volatile v1; v1 = m1_AiGoto113040(*(M1Ob162 *volatile *)&o, (M1Ai162 *)e, 0x2A); return; }
    if (m1_chkFn31D0C0(o, e, m1_tbl2797E8)) { v = m1_AiGoto113040(o, (M1Ai162 *)e, 0x13); return; }
    if (sub_001C7EE1() % 32 < 1) {
        e->flags4C &= ~0x10u;
        v = m1_AiGoto113040(o, (M1Ai162 *)e, 0x2A);
        return;
    }
    if (e->b20 & 1) t = (float)(sub_001C7EE1() % 91); else t = 120.0f;
    e->t74 = t / m1_frameTime42C858 * m1_frameRate42C85C;
    v = m1_AiGoto113040(o, (M1Ai162 *)e, 0x2B);
}

typedef struct M1Rg162c { uint8_t unk00[4]; uint32_t f4; uint8_t unk08[0x10]; float f18; } M1Rg162c;
typedef struct M1Ob162c { uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0x1C]; void *anim30; } M1Ob162c;
typedef struct M1Ai162c {
    uint8_t unk00[0x20]; uint32_t f20; uint8_t unk24[0x28]; uint32_t flags4C; uint8_t unk50[0x24]; float t74;
    uint8_t unk78[0x278 - 0x78]; M1Rg162c *rig278;
} M1Ai162c;

/* 0x13F3E0: after a hit animation: recover, counter (0x28/0x29) or pause before the next move. */
void m1_AiRecover13F3E0(M1Ob162c *o, M1Ai162c *e) {
    M1Rg162c *r; int volatile v;
    if (sub_000833E0(o->anim30) == 0) return;
    o->f10 &= ~6u;
    e->flags4C |= 0x10;
    r = e->rig278;
    if (r->f4 & 0x10) {
        if (!(((uint8_t *)e)[0x22] & 1)) { v = m1_AiGoto113040((M1Ob162 *)o, (M1Ai162 *)e, 0x28); return; }
    zero:
        e->t74 = 0.0f;
        v = m1_AiGoto113040((M1Ob162 *)o, (M1Ai162 *)e, 0xC);
        return;
    }
    if (!(e->f20 & 0x10000)) { int volatile v2; v2 = m1_AiGoto113040((M1Ob162 *)o, *(M1Ai162 *volatile *)&e, 0xC); return; }
    if (e->f20 & 1) { int volatile v4; v4 = m1_AiGoto113040((M1Ob162 *)*(M1Ob162c *volatile *)&o, (M1Ai162 *)e, 0x29); return; }
    if (r->f18 >= 120.0f) goto zero;
    e->t74 = 90.0f / m1_frameTime42C858 * m1_frameRate42C85C;
    v = m1_AiGoto113040((M1Ob162 *)o, (M1Ai162 *)e, 0xC);
}

/* 0x13FD20: after a hit animation: pause (0xC), a 1-in-8 taunt (0xB), or counter (0x28). */
void m1_AiHitNext13FD20(M1Ob162c *o, M1Ai162c *e) {
    volatile int st;
    if (sub_000833E0(o->anim30) == 0) return;
    if (e->f20 & 0x10000) { e->t74 = 0.0f; st = 0xC; }
    else if (!(e->f20 & 1) && sub_001C7EE1() % 8 < 1) st = 0xB;
    else st = 0x28;
    o->f10 &= ~0x20u;
    m1_AiGoto113040((M1Ob162 *)o, (M1Ai162 *)e, st);
}

typedef struct M1Rg162e { uint8_t unk00[4]; uint32_t f4; } M1Rg162e;
typedef struct M1Ai162e {
    uint8_t unk00[0x20]; uint8_t b20; uint8_t unk21[0x58 - 0x21]; int32_t n58; uint8_t unk5C[0xC]; float t68;
    uint8_t unk6C[8]; float t74; uint8_t unk78[0x278 - 0x78]; M1Rg162e *rig278;
} M1Ai162e;

/* 0x138C10: wait out the stun timer, then recover (or counter-attack when flagged). */
void m1_AiStunWait138C10(M1Ob162c *o, M1Ai162e *e) {
    volatile int st;
    switch (e->n58) {
    case 0:
        if (!(e->t68 >= 46.0f / m1_frameTime42C858 * m1_frameRate42C85C)) return;
        e->n58 = 1;
        if ((e->b20 & 1) || !(e->rig278->f4 & 0x40000000)) return;
        e->t74 = 144.0f / m1_frameTime42C858 * m1_frameRate42C85C;
        st = 0x1A;
        break;
    case 1:
        if (sub_000833E0(o->anim30) == 0) return;
        st = 0xD;
        break;
    default:
        return;
    }
    o->f10 &= ~0x20u;
    m1_AiGoto113040((M1Ob162 *)o, (M1Ai162 *)e, st);
}
