/* Area m1, file 257: HUD counters. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Spr257 { float x, y; uint8_t unk08[0x14]; float f1C, f20; uint8_t unk24[0x68]; uint32_t col8C;
    uint8_t unk90[0xC]; } M1Spr257;                                     /* 0x9C */
extern M1Spr257 m1_hudSpr37DAE4[2];
extern int16_t m1_hudOfs37DA9C[2];
void *sub_00017C90(void *dl, M1Spr257 *s);
void sub_00026910(void *dl, float x, float y, int32_t d, int32_t e, int32_t f, uint32_t col, float sx, float sy, int32_t j);

/* 0x0002B950: draw number n right-aligned at x with its backing sprite: the sprite shifts left 19.2 per digit
   (less 12), and is grey unless col's RGB is 0x23576E (then dark grey). regargs to 0x26910: EDX=n ECX=digits. */
void m1_HudNumber2B950(void *dl, float x, float y, uint32_t col, int32_t n)
{
    int32_t digits, c;
    uint32_t m;
    if (n != 0) {
        digits = 0;
        for (c = n; c > 0; c = *(volatile int32_t *)&c / 10)
            digits++;
    } else {
        digits = 1;
    }
    x -= (float)digits * 19.2f - 12.0f;
    m1_hudSpr37DAE4[0].x = x;
    m1_hudSpr37DAE4[0].y = y;
    m1_hudSpr37DAE4[0].f20 = 1.0f;
    m1_hudSpr37DAE4[0].f1C = 1.0f;
    m = -(int32_t)((col & 0xFFFFFF) != 0x23576E);
    m1_hudSpr37DAE4[0].col8C = (col & 0xFF000000u) | ((*(volatile uint32_t *)&m & 0xFFBFBFC0u) + 0x808080);
    dl = sub_00017C90(dl, &m1_hudSpr37DAE4[0]);
    sub_00026910(dl, (float)m1_hudOfs37DA9C[0] + x, (float)m1_hudOfs37DA9C[1] + y, 0, n, digits, col, 0.8f, 0.8f, 0);
}

typedef struct M1Combo257 {                 /* 0x0037EEBC */
    int16_t rankBC, rankBE, cntC0, cntC2, kindC4, lastC6;
    float timerC8;                          /* 100 at start, counts down */
    int32_t queueCC[8];                     /* pending combo entries, shifted down as each finishes */
    int32_t phaseEC;
    uint8_t alphaF0;
} M1Combo257;
extern M1Combo257 m1_combo37EEBC;
extern uint32_t m1_seqFlags37EDEC;
void sub_000720A0(float *v, int32_t target);

/* 0x0002AE60: combo meter timer. Phase 0 starts the timer at 100; phase 1 counts it down (alpha follows the
   timer) and, when it runs out, records the last rank, pops the next queued entry, and resets the counters
   (the rank is kept when the combo kind is 1). */
void m1_ComboTick2AE60(void)
{
    switch (m1_combo37EEBC.phaseEC) {
    case 0:
        m1_combo37EEBC.timerC8 = 100.0f;
        m1_combo37EEBC.phaseEC = 1;
        return;
    case 1:
        sub_000720A0(&m1_combo37EEBC.timerC8, 0);
        m1_combo37EEBC.alphaF0 = (uint8_t)(int32_t)(m1_combo37EEBC.timerC8 * 0.01f * 128.0f);
        if (!_mm_comige_ss(_mm_set_ss(0.0f), _mm_load_ss(&m1_combo37EEBC.timerC8))) return;
        m1_seqFlags37EDEC &= ~1u;
        m1_combo37EEBC.lastC6 = m1_combo37EEBC.rankBE;
        m1_combo37EEBC.queueCC[0] = m1_combo37EEBC.queueCC[1];
        m1_combo37EEBC.queueCC[1] = m1_combo37EEBC.queueCC[2];
        m1_combo37EEBC.queueCC[2] = m1_combo37EEBC.queueCC[3];
        m1_combo37EEBC.queueCC[3] = m1_combo37EEBC.queueCC[4];
        m1_combo37EEBC.queueCC[4] = m1_combo37EEBC.queueCC[5];
        m1_combo37EEBC.queueCC[5] = m1_combo37EEBC.queueCC[6];
        m1_combo37EEBC.queueCC[6] = m1_combo37EEBC.queueCC[7];
        m1_combo37EEBC.queueCC[7] = 0;
        m1_combo37EEBC.phaseEC = 0;
        if (m1_combo37EEBC.kindC4 != 1) {
            m1_combo37EEBC.rankBE = 0;
            m1_combo37EEBC.rankBC = 0;
        }
        m1_combo37EEBC.alphaF0 = 0;
        m1_combo37EEBC.kindC4 = 0;
        m1_combo37EEBC.cntC2 = 0;
        m1_combo37EEBC.cntC0 = 0;
        return;
    }
}

typedef struct M1Cam257 { float sx, sy, sz, ox, oy, a14, b18, near1C, far20; } M1Cam257;
void sub_001AD940(float *m);
void sub_001AD7C0(float *d, const float *a, const float *b);
void sub_001A6D70(float *m, const M1Cam257 *c);

/* 0x001B6FE0: build a projection matrix into out from camera c: a scale matrix (x, y by sx; w from z) times a
   matrix holding the y/z scales, the x/y offsets and the depth remap terms for near/far, then apply it. */
void m1_BuildProj1B6FE0(const M1Cam257 *c, float *out)
{
    float a, b;
    float m1[16], m2[16];
    a = (c->a14 * c->far20 - c->near1C * c->b18) / (c->far20 - c->near1C);
    b = (c->b18 - c->a14) * c->near1C * c->far20 / (c->far20 - c->near1C);
    sub_001AD940(m1);
    m1[0] = c->sx;
    m1[5] = c->sx;
    m1[10] = 0.0f;
    m1[15] = 0.0f;
    m1[14] = 1.0f;
    m1[11] = 1.0f;
    sub_001AD940(m2);
    m2[0] = c->sy;
    m2[5] = c->sz;
    m2[10] = b;
    m2[12] = c->ox;
    m2[13] = c->oy;
    m2[14] = a;
    sub_001AD7C0(out, m2, m1);
    sub_001A6D70(out, c);
}

typedef struct M1Fd257 { uint8_t unk00[0x398]; float alpha398; uint8_t unk39C[0x1C]; float t3B8; uint32_t flags3BC;
    float delay3C0, dur3C4, t3C8, dur3CC; } M1Fd257;
extern float m1_frameTime42C858;

/* 0x000D4AE0: advance o's fades. Flags 1/2 run a fade: after the delay, flag 2 eases alpha up as the 4th power
   of progress (capped at 1); when delay + duration has passed alpha snaps to 0 (flag 1) or 1 and the fade
   clears. Flag 4 runs a flash timer that zeroes alpha when it expires. regargs: o=EAX. */
void m1_FadeTickD4AE0(M1Fd257 *o)
{
    uint32_t fl = o->flags3BC;
    float v;
    if (fl & 3) {
        o->t3B8 += m1_frameTime42C858;
        if ((fl & 2) && o->t3B8 > o->delay3C0 && o->dur3C4 > 0.0f) {
            v = (o->t3B8 - o->delay3C0) / o->dur3C4;
            v = v * v * v * v;
            if (v >= 0.0f) {
                o->alpha398 = v;
                if (v > 1.0f)
                    o->alpha398 = 1.0f;
            }
        }
        if (o->t3B8 > o->dur3C4 + o->delay3C0) {
            if (fl & 1)
                o->alpha398 = 0.0f;
            else
                o->alpha398 = 1.0f;
            o->t3B8 = 0.0f;
            o->flags3BC = fl & ~3u;
            o->delay3C0 = 0.0f;
            o->dur3C4 = 0.0f;
        }
    }
    fl = o->flags3BC;
    if (fl & 4) {
        o->t3C8 += m1_frameTime42C858;
        if (o->t3C8 > o->dur3CC) {
            o->alpha398 = 0.0f;
            o->flags3BC = fl & ~4u;
            o->t3C8 = 0.0f;
            o->dur3CC = 0.0f;
        }
    }
}

typedef struct M1Cmd257 { uint8_t unk00[4]; const uint8_t *p4; } M1Cmd257;
void sub_00048AF0(int32_t id);

/* 0x000DA790: script command "show message": byte 0 is the chapter (0-29), bytes 1-2 the message number within
   it; adds the chapter's base id and shows the message. An out-of-range chapter leaves the base undefined in
   the original (it reads the argument slot). Returns 0x2003. */
int32_t m1_CmdMessageDA790(M1Cmd257 *c)
{
    int32_t base;
    union { int32_t w; int16_t s; uint8_t b[4]; } hi;
    switch (c->p4[0]) {
    case 0: base = 0; break;
    case 1: base = 0x14; break;
    case 2: case 3: base = 0x84; break;
    case 4: base = 0xBD; break;
    case 5: base = 0xE5; break;
    case 6: base = 0x10E; break;
    case 7: base = 0x144; break;
    case 8: base = 0x185; break;
    case 9: base = 0x196; break;
    case 10: base = 0x1A6; break;
    case 11: base = 0x216; break;
    case 12: base = 0x246; break;
    case 13: base = 0x266; break;
    case 14: base = 0x27C; break;
    case 15: base = 0x28D; break;
    case 16: base = 0x2D8; break;
    case 17: base = 0x2E8; break;
    case 18: base = 0x2F8; break;
    case 19: base = 0x30B; break;
    case 20: base = 0x314; break;
    case 21: base = 0x31B; break;
    case 22: base = 0x333; break;
    case 23: base = 0x343; break;
    case 24: base = 0x344; break;
    case 25: base = 0x347; break;
    case 26: base = 0x359; break;
    case 27: base = 0x35E; break;
    case 28: base = 0x37E; break;
    case 29: base = 0x383; break;
    default: base = (int32_t)(intptr_t)c; break;   /* XBOX32: original reads the uninitialised slot (arg c) */
    }
    hi.w = 0;
    hi.b[1] = c->p4[2];
    sub_00048AF0(base + (hi.s | c->p4[1]));
    return 0x2003;
}

typedef struct M1Item257 {                  /* 0x0037DAA4 */
    int32_t queue[8];                       /* pending item pickups, shifted down as each finishes */
    int32_t phase20;
    float timer24;                          /* 60 at start, counts down */
    int32_t unk28, unk2C;
    int32_t from30, cur34, to38;            /* displayed count rolls from 'from' to 'to' */
} M1Item257;
extern M1Item257 m1_item37DAA4;

/* 0x000298C0: item counter roll. Phase 0 starts a 60-frame timer; phase 1 counts it down and rolls the shown
   count from 'from' to 'to' in even steps; when the timer runs out the count lands on 'to' and the next queued
   pickup moves up. */
void m1_ItemRoll298C0(void)
{
    int32_t t;
    switch (m1_item37DAA4.phase20) {
    case 0:
        m1_item37DAA4.timer24 = 60.0f;
        m1_item37DAA4.phase20 = 1;
        return;
    case 1:
        sub_000720A0(&m1_item37DAA4.timer24, 0);
        t = (int32_t)(m1_item37DAA4.timer24 - (float)((uint32_t)(int32_t)m1_item37DAA4.timer24 & 1));
        m1_item37DAA4.cur34 = (int32_t)((60.0f - (float)t) * 0.016666668f * (float)(m1_item37DAA4.to38 - m1_item37DAA4.from30)
                                        + (float)m1_item37DAA4.from30);
        if (!_mm_comige_ss(_mm_set_ss(0.0f), _mm_load_ss(&m1_item37DAA4.timer24))) return;
        m1_item37DAA4.cur34 = m1_item37DAA4.to38;
        m1_item37DAA4.queue[0] = m1_item37DAA4.queue[1];
        m1_item37DAA4.queue[1] = m1_item37DAA4.queue[2];
        m1_item37DAA4.queue[2] = m1_item37DAA4.queue[3];
        m1_item37DAA4.queue[3] = m1_item37DAA4.queue[4];
        m1_item37DAA4.queue[4] = m1_item37DAA4.queue[5];
        m1_item37DAA4.queue[5] = m1_item37DAA4.queue[6];
        m1_item37DAA4.queue[6] = m1_item37DAA4.queue[7];
        m1_item37DAA4.queue[7] = 0;
        m1_item37DAA4.phase20 = 0;
        return;
    }
}
