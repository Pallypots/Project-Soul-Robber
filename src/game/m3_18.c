/* Area m3, file 18: AI attack states. Names inferred. */
#include <stdint.h>

typedef struct M3Pl18 { uint8_t unk00[0x60]; float pos60[4]; } M3Pl18;
typedef struct M3A18 { uint8_t unk00[0x60]; float pos60[4]; uint8_t unk70[0xB8]; uint8_t b128; } M3A18;
typedef struct M3E18 { uint8_t unk00[0x68]; float t68; uint8_t unk6C[0xF0]; float v15C[4]; uint8_t unk16C[0x1C]; int32_t step188; } M3E18;
extern M3Pl18 *g_playerObj;
extern float b10_frameDelta;
float rbj_Distance(const float *a, const float *b);
void m1_LockMark0C56B0(M3A18 *a);
void m1_PlShot0C62A0(M3A18 *a);
void *sub_0001D960(void *o, int kind);
void sub_000F3D10(void *a, void *c, int st);

/* 0x10EDF0: AI pounce state: step 0 locks on within 60 units (not grounded-blocked) or fires and stops (step 1); step 1 waits for the time threshold and then leaps (12 forward, -4 on the last axis per frame unit; step 2); step 2 lands into state 10 when airborne time is up and grounded. */
void m3_AiPounce10EDF0(M3A18 *a, M3E18 *o) {
    switch (o->step188) {
    case 2:
        if (o->v15C[2] > 0.0f && (a->b128 & 0x18))
            sub_000F3D10(a, sub_0001D960(a, 5), 10);
        return;
    case 1:
        if (!(o->t68 >= 0.02f)) return;
        o->v15C[0] = b10_frameDelta * 12.0f;
        o->v15C[3] = b10_frameDelta * -4.0f;
        o->step188 = 2;
        o->t68 = 0.0f;
        return;
    case 0:
        if (!(a->b128 & 6) && !(rbj_Distance(a->pos60, g_playerObj->pos60) >= 60.0f)) {
            m1_LockMark0C56B0(a);
            return;
        }
        m1_PlShot0C62A0(a);
        o->v15C[0] = b10_frameDelta * 0.0f;
        o->v15C[1] = b10_frameDelta * 0.0f;
        o->v15C[2] = b10_frameDelta * 0.0f;
        o->v15C[3] = b10_frameDelta * 0.0f;
        o->step188 = 1;
        o->t68 = 0.0f;
        return;
    }
}

typedef struct M3Bar18 { uint8_t unk00[0xFAC]; float hpFAC; uint8_t unkFB0[0x10]; float colFC0, colFC4, colFC8; } M3Bar18;
float sub_00171B40(M3Bar18 *b);

/* 0xC9E30: colour the boss health bar from its health against the maximum from 0x171B40: above half it shifts red down and blue up, below half it fades green out; each channel clamped to 0..255. */
void m3_BossBarC9E30(M3Bar18 *b) {
    float t = sub_00171B40(b), a = b->hpFAC, h, x, g;
    if (0.0f > a) a = 0.0f;
    h = t * 0.5f;
    if (a > h) {
        x = (h - (t - a)) / h;
        if (x > 1.0f) x = 1.0f;
        b->colFC0 = 255.0f - x * 128.0f;
        g = 242.0f - x * 116.0f;
        b->colFC8 = x * 128.0f;
    } else {
        x = (h - a) / h;
        if (x > 1.0f) x = 1.0f;
        b->colFC0 = 255.0f - x * 10.0f;
        g = 242.0f - x * 222.0f;
        b->colFC8 = x * 28.0f;
    }
    b->colFC4 = g;
    if (b->colFC0 > 255.0f) b->colFC0 = 255.0f;
    if (0.0f > b->colFC0) b->colFC0 = 0.0f;
    if (b->colFC4 > 255.0f) b->colFC4 = 255.0f;
    if (0.0f > b->colFC4) b->colFC4 = 0.0f;
    if (b->colFC8 > 255.0f) b->colFC8 = 255.0f;
    if (0.0f > b->colFC8) b->colFC8 = 0.0f;
}

typedef struct M3Dg18 { uint8_t unk00[0xFC]; float yawFC; uint8_t unk100[0x50]; uint32_t f150; } M3Dg18;
void r6c_RotateVec(float *d, const float *rot, const float *v);
void rbi_VecNorm(float *d, const float *s);
float rbi_VecDot(const float *a, const float *b);
void sub_000CF2C0(M3Dg18 *b, float *dir);
void abc_SetState(M3Dg18 *b, int st);

/* 0xCFC80: pick the boss dodge state from the hit direction d (flattened): facing it (dot >= cos limit) state 0x18, away (dot <= the other limit) 0x17, else turn 90 degrees, probe a side direction and go left (0x1A) or right (0x19) by its sign; then flag 0x2000. */
void m3_BossDodgeCFC80(M3Dg18 *b, int unused, float *d) {
    float f[4], r[4], k, save, x; int s = 0;
    r[0] = 0.0f; r[2] = 0.0f;
    f[1] = 0.0f; f[0] = 0.0f;
    f[2] = -1.0f;
    r[3] = 1.0f; f[3] = 1.0f;
    r[1] = b->yawFC;
    r6c_RotateVec(f, r, f);
    rbi_VecNorm(f, f);
    d[1] = 0.0f;
    rbi_VecNorm(d, d);
    k = rbi_VecDot(f, d);
    if (!(k < 0.7071f)) s = 1;
    else if (-0.7071f >= k) s = 0;
    else if (0.7071f > k && k > -0.7071f) {
        save = b->yawFC;
        x = save + 1.5707964f;
        b->yawFC = x;
        if (x > 3.1415927f) b->yawFC = x - 6.2831855f;
        sub_000CF2C0(b, f);
        b->yawFC = save;
        s = (rbi_VecDot(f, d) >= 0.0f) ? 3 : 2;
    }
    abc_SetState(b, s + 0x17);
    b->f150 |= 0x2000;
}

typedef struct M3TmCtx18 { uint8_t unk00[0x1BC]; int32_t v1BC[5]; } M3TmCtx18;
extern M3TmCtx18 *m1_scene42C8E4;
extern int32_t m3_timerMax317B48[];
void __stosd(unsigned long *d, unsigned long v, unsigned int n);
#pragma intrinsic(__stosd)
void sub_000E63A0(int a);
void sub_0003D120(int a, int i, void *p, void *q);
void sub_0003D1A0(int a, int i, void *p);
void sub_0003D220(int a, int i, void *p);
void sub_000E8690(int a, int n);
#define M3I(o, off) (*(int32_t *)((o) + (off)))
#define M3F(o, off) (*(float *)((o) + (off)))

/* 0xE66F0: reset a stage's timing block: clear 0x6FC bytes at +0x320, reset its HUD, mark it active, and for kinds 0..7 set the limit from the table, clear the four channel fades (-1) and reload their tracks, copy the scene's five timing values and show the counters. */
void m3_StageTimesE66F0(uint8_t *o) {
    int i; uint8_t *fp, *ch; int k;
    __stosd((unsigned long *)(o + 0x320), 0, 0x1BF);
    sub_000E63A0(0);
    M3I(o, 0x318) = 0;
    M3I(o, 0x31C) = -1;
    M3I(o, 0x320) = 0;
    M3I(o, 0x408) = 1;
    { volatile int vk = M3I(o, 0); if (vk < 0 || vk > 7) return; k = vk; }
    M3I(o, 0x40C) = 0;
    M3I(o, 0x410) = m3_timerMax317B48[k];
    ch = o + 0x7B0;
    fp = o + 0x6D8;
    for (i = 0; i < 4; i++, fp += 0x30, ch += 0x28) {
        M3F(fp, -4) = -1.0f;
        M3F(fp, 0) = -1.0f;
        sub_0003D120(0, i, ch, ch + 4);
        sub_0003D1A0(0, i, ch + 8);
        sub_0003D220(0, i, ch + 0x18);
    }
    M3F(o, 0x794) = -1.0f;
    M3F(o, 0x798) = -1.0f;
    M3I(o, 0x850) = m1_scene42C8E4->v1BC[0];
    M3I(o, 0x854) = m1_scene42C8E4->v1BC[1];
    M3I(o, 0x858) = m1_scene42C8E4->v1BC[2];
    M3I(o, 0x85C) = m1_scene42C8E4->v1BC[3];
    M3I(o, 0x860) = m1_scene42C8E4->v1BC[4];
    sub_000E8690(3, M3I(o, 0x410));
    sub_000E8690(4, M3I(o, 0x40C));
}

typedef struct M3LvRes18 { uint8_t unk00[8]; int32_t n8; } M3LvRes18;
extern int32_t m1_lvlA3F74F4;
extern M3LvRes18 *m1_lvlRes3F74F0;
extern int32_t m1_maxN3F6168;
extern uint8_t *r2e_g3F616C;
extern uint8_t *r2e_units3F63E8;
extern uint8_t *m3_bufB3F6728;
extern uint8_t *m3_bufC3F6A68;
extern uint8_t *m3_bufD3F6DA8;
extern uint8_t *m3_bufE3F70E8;
extern uint8_t *m3_bufF3F7428;
M3LvRes18 *sub_0001F210(int a, int b);
void r1b_TableVisit(M3LvRes18 *r);
void m1_TakeSlotED9A0(void (*fn)(void));
void sub_00112A80(void);
void *a5b_AllocCur(int size, int a, int tag);
void __stosb(unsigned char *d, unsigned char v, unsigned int n);
#pragma intrinsic(__stosb)

/* 0x113CE0: set up the level's unit tables once: load resource (3, 3), keep its count, visit it, register the per-frame handler 0x112A80, then allocate six byte arrays of the maximum unit count in one cleared block. */
void m3_LevelUnitsInit113CE0(void) {
    M3LvRes18 *r; uint8_t *p; int n;
    if (m1_lvlA3F74F4 != 0) return;
    r = sub_0001F210(3, 3);
    m1_lvlRes3F74F0 = r;
    m1_lvlA3F74F4 = r->n8;
    r1b_TableVisit(r);
    m1_TakeSlotED9A0(sub_00112A80);
    p = (uint8_t *)a5b_AllocCur(m1_maxN3F6168 * 6, 0, 0xC9);
    n = m1_maxN3F6168;
    {
        volatile unsigned int vs = n * 6;
        unsigned int s = vs;
        __stosd((unsigned long *)p, 0, s >> 2);
        __stosb(p + (s >> 2) * 4, 0, s & 3);
    }
    m3_bufB3F6728 = p + n;
    m3_bufD3F6DA8 = p + n * 3;
    m3_bufC3F6A68 = p + n * 2;
    r2e_g3F616C = p;
    r2e_units3F63E8 = p;
    m3_bufE3F70E8 = p + n * 4;
    m3_bufF3F7428 = p + n * 5;
}
