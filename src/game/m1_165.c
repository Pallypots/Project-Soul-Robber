/* Area m1, file 165: pad setup step (revisited). Names inferred. */
#include <stdint.h>

int sub_000D9A70(int id);
int sub_000A42F0(int slot, int a);
int sub_000A2CA0(int slot, uint32_t f);
int sub_000A2CC0(int slot, uint32_t f);
int sub_000A2D10(int slot, uint32_t f);
int sub_000A2D40(int slot, uint32_t f);

/* 0xB12D0: three-phase pad setup step. st = {flags, phase, ticks}. */
int m1_PadPhase0B12D0(int mode, int unused, int32_t *st) {
    int volatile r; volatile int k;
    if (mode == 0) { st[0] = 0; st[1] = 0; st[2] = 0; return 1; }
    if (mode == 1) { st[2] = 0; st[0] |= 1; st[1] = 10; return 1; }
    if (mode == 3) { st[0] = 0; st[1] = 0x14; }
    st[2]++;
    if (st[1] == 10) {
        if (sub_000D9A70(0x2CC) != 0) {
            r = sub_000A2D40(2, 0x20); r = sub_000A2D40(3, 0x20);
            r = sub_000A2CC0(2, 0x10000000); r = sub_000A2CC0(3, 0x10000000);
            r = sub_000A42F0(2, 0);
            k = 0;
        } else {
            r = sub_000A2D10(2, 0x20); r = sub_000A2D40(3, 0x20);
            r = sub_000A2CA0(2, 0x10000000); r = sub_000A2CC0(3, 0x10000000);
            r = sub_000A42F0(2, 2);
            k = 2;
        }
        sub_000A42F0(3, k);
    } else if (st[1] == 0x14) {
        st[0] = 0; st[1] = 0; return 0;
    }
    st[1] = 0x14;
    return 1;
}


typedef struct M1Rg165 { uint8_t unk00[4]; uint32_t f4; } M1Rg165;
typedef struct M1Ob165 { uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0x1C]; void *anim30; } M1Ob165;
typedef struct M1Ai165 {
    uint8_t unk00[0x20]; uint8_t b20; uint8_t b21; uint8_t b22; uint8_t unk23[0x29]; uint32_t flags4C;
    uint8_t unk50[8]; int32_t n58; uint8_t unk5C[0x10]; int32_t snd6C; void *fx70; float t74;
    uint8_t unk78[0xFC - 0x78]; float fFC; uint8_t unk100[0x278 - 0x100]; M1Rg165 *rig278;
} M1Ai165;
typedef int (*M1Check165)(M1Ob165 *o, M1Ai165 *e, const uint8_t *tbl);
extern M1Check165 m1_chkFn31DBBC;
extern const uint8_t m1_chkTbl279848[];
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
int  sub_000833E0(void *a);
int  sub_001C7EE1(void);
void sub_00033A70(void *p);
void m1_SndStop048250(int h);
void sub_00113090(M1Ob165 *o, M1Ai165 *e, int st);
void m1_AiGoto113040(M1Ob165 *o, M1Ai165 *e, int st);

/* 0x1450A0: fall/land step: when the timer runs out stop effects and land; after landing choose the next move. */
void m1_AiLand1450A0(M1Ob165 *o, M1Ai165 *e) {
    volatile int st;
    switch (e->n58) {
    case 0:
        if (!(0.0f >= e->t74)) return;
        sub_00033A70(e->fx70);
        e->fx70 = 0;
        m1_SndStop048250(e->snd6C);
        e->snd6C = -1;
        sub_00113090(o, e, (e->b22 & 1) + 0x16);
        o->f10 &= ~0x10u;
        e->rig278->f4 &= 0xBFFFFFEF;
        e->n58++;
        return;
    case 1:
        if (sub_000833E0(o->anim30) == 0) return;
        if (m1_chkFn31DBBC(o, e, m1_chkTbl279848)) st = 3;
        else if (!(e->b22 & 1)) st = 7;
        else if (0.52359879f > e->fFC && sub_001C7EE1() % 4 < 1) { e->rig278->f4 |= 2; st = 8; }
        else if (e->b20 & 1) { e->t74 = 0.0f; st = 5; }
        else { e->t74 = 60.0f / m1_frameTime42C858 * m1_frameRate42C85C; st = 5; }
        e->flags4C |= 0x10;
        m1_AiGoto113040(o, e, st);
        return;
    }
}

typedef struct M1Ai165b {
    uint8_t unk00[0x20]; uint32_t f20; uint8_t unk24[0x28]; uint32_t flags4C;
    uint8_t unk50[8]; int32_t n58; uint8_t unk5C[0x10]; int32_t snd6C; void *fx70; float t74;
    uint8_t unk78[0x278 - 0x78]; M1Rg165 *rig278;
} M1Ai165b;
typedef int (*M1Check165b)(M1Ob165 *o, M1Ai165b *e, const uint8_t *tbl);
extern M1Check165b m1_chkFn31D0B8;
extern const uint8_t m1_chkTbl2797C8[];

/* 0x141570: get-up step: when the timer drops stop effects and stand; then choose the next move. */
void m1_AiGetUp141570(M1Ob165 *o, M1Ai165b *e) {
    volatile int st; float t;
    switch (e->n58) {
    case 0:
        if (e->t74 >= 0.0f) return;
        sub_00033A70(e->fx70);
        e->fx70 = 0;
        sub_00113090(o, (M1Ai165 *)e, (((uint8_t *)e)[0x22] & 1) + 0x18);
        m1_SndStop048250(e->snd6C);
        e->snd6C = -1;
        o->f10 = (o->f10 & ~0x10u) | 0x20;
        e->n58++;
    case 1:
        if (sub_000833E0(o->anim30) == 0) return;
        if (m1_chkFn31D0B8(o, e, m1_chkTbl2797C8)) st = 0xA;
        else if (e->f20 & 0x10000) {
            if (e->rig278->f4 & 0x10) { t = 60.0f; goto pause; }
            if (e->f20 & 1) st = 0x12;
            else { t = 200.0f;
            pause:
                e->t74 = t / m1_frameTime42C858 * m1_frameRate42C85C;
                st = 0xC; }
        }
        else if (!(e->f20 & 1) && sub_001C7EE1() % 8 < 1) st = 0xB;
        else st = 0x28;
        e->flags4C |= 0x10;
        m1_AiGoto113040(o, (M1Ai165 *)e, st);
        return;
    }
}
