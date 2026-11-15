/* Area m3, file 13: transform slot reset, model swap. Names inferred. */
#include <stdint.h>

typedef struct M3XSlot13 {
    int32_t i0, i4, i8; float fC, f10, f14, f18; int32_t i1C, i20; float f24, f28, f2C, f30, f34, f38, f3C, f40, f44, f48, f4C, f50;
    int32_t i54, i58; int32_t w5C[0x20]; int32_t iDC;
} M3XSlot13;

/* 0xC4B70: clear a 0xE0-byte transform slot: all float fields 0.0 and all integer fields 0. */
void m3_XSlotClearC4B70(M3XSlot13 *s) {
    s->fC = 0.0f; s->f10 = 0.0f; s->f14 = 0.0f; s->f18 = 0.0f;
    s->f30 = 0.0f; s->f2C = 0.0f; s->f28 = 0.0f; s->f24 = 0.0f;
    s->f40 = 0.0f; s->f3C = 0.0f; s->f38 = 0.0f; s->f34 = 0.0f;
    s->f50 = 0.0f; s->f4C = 0.0f; s->f48 = 0.0f; s->f44 = 0.0f;
    s->i0 = 0; s->i4 = 0; s->i8 = 0; s->i1C = 0; s->i20 = 0; s->i54 = 0; s->i58 = 0;
    s->w5C[0] = 0; s->w5C[1] = 0; s->w5C[2] = 0; s->w5C[3] = 0; s->w5C[4] = 0; s->w5C[5] = 0; s->w5C[6] = 0; s->w5C[7] = 0;
    s->w5C[8] = 0; s->w5C[9] = 0; s->w5C[10] = 0; s->w5C[11] = 0; s->w5C[12] = 0; s->w5C[13] = 0; s->w5C[14] = 0; s->w5C[15] = 0;
    s->w5C[16] = 0; s->w5C[17] = 0; s->w5C[18] = 0; s->w5C[19] = 0; s->w5C[20] = 0; s->w5C[21] = 0; s->w5C[22] = 0; s->w5C[23] = 0;
    s->w5C[24] = 0; s->w5C[25] = 0; s->w5C[26] = 0; s->w5C[27] = 0; s->w5C[28] = 0; s->w5C[29] = 0; s->w5C[30] = 0; s->w5C[31] = 0;
    s->iDC = 0;
}

typedef struct M3Mdl13 { uint8_t unk00[0x20]; void *parts20; uint8_t unk24[0x18]; void *link3C; } M3Mdl13;
typedef struct M3Sc13 { uint8_t unk00[0x3B0]; M3Mdl13 *cur3B0; } M3Sc13;
extern M3Mdl13 *r2b_g42C8D4;
extern M3Mdl13 *r2b_state42C8DC;
extern M3Sc13 *g_42C8EC;
extern void *m1_scene42C8E4;
extern uint8_t rbk_g418A80[];
extern int m3_nodeSet418B54;
extern int m3_nodeStart418B70;
void r1b_RecDetachNodes(void *n);
void r1i_UnitsAttach(void *ctx, void *o, int a, int b, int c);
void r4b_NodePBindParts(void *n, void *parts, int *order, int set);
void r4b_NodePStart(void *n, int st);
void r4b_NodePRewind(void *n);

/* 0xCA0E0: swap the active model (to the second model when alt is set, copying its link), attach it as kind 0xB, make it the scene's current model and bind/start/rewind the node player with the reversed part order 15..0. */
void m3_ModelSwapCA0E0(int alt) {
    int t[17]; M3Mdl13 *a, *s; void *ctx = m1_scene42C8E4;
    t[0] = 15; t[1] = 14; t[2] = 13; t[3] = 12; t[4] = 11; t[5] = 10; t[6] = 9; t[7] = 8;
    t[8] = 7; t[9] = 6; t[10] = 5; t[11] = 4; t[12] = 3; t[13] = 2; t[14] = 1; t[15] = 0; t[16] = -1;
    if (alt) { a = r2b_g42C8D4; s = r2b_state42C8DC; s->link3C = a->link3C; }
    else { s = r2b_g42C8D4; a = r2b_state42C8DC; }
    r1b_RecDetachNodes(a);
    r1b_RecDetachNodes(s);
    r1i_UnitsAttach(ctx, s, 0xB, 5, 0x11);
    g_42C8EC->cur3B0 = s;
    r4b_NodePBindParts(rbk_g418A80, s->parts20, t, m3_nodeSet418B54);
    r4b_NodePStart(rbk_g418A80, m3_nodeStart418B70);
    r4b_NodePRewind(rbk_g418A80);
}

typedef struct M3Sc13b { uint8_t unk00[0x384]; float camPos384[4]; } M3Sc13b;
typedef struct M3Ev13 { uint8_t unk00[0xC]; uint8_t bC; uint8_t unkD[0xDB]; float radE8; } M3Ev13;
extern M3Ev13 *m3_curEvent420DBC;
void a3c_VecCopy(float *dst, const float *src);
int sub_000D0DC0(float *a, float r, float *c, float *d);
int r2b_PoolGetB(float *a, float *b, float *c, float *d);

/* 0xCAB90: probe around the camera point: radius 6 (or the current event's larger radius when it has flag 0x40); 1 when 0xD0DC0 finds a hit within it, else the result of the line probe from the camera point up to radius + 2 above it. */
int m3_CamProbeCAB90(void) {
    float r, a[4], b[4], c[4], d[4];
    a[0] = 0.0f; a[1] = 0.0f; a[2] = 0.0f; a[3] = 1.0f;
    b[0] = 0.0f; b[1] = 0.0f; b[2] = 0.0f; b[3] = 1.0f;
    c[0] = 0.0f; c[1] = 0.0f; c[2] = 0.0f; c[3] = 1.0f;
    d[0] = 0.0f; d[1] = 0.0f; d[2] = 0.0f; d[3] = 1.0f;
    a3c_VecCopy(a, ((M3Sc13b *)g_42C8EC)->camPos384);
    a3c_VecCopy(b, a);
    r = 6.0f;
    if (m3_curEvent420DBC && (m3_curEvent420DBC->bC & 0x40) && !(6.0f > m3_curEvent420DBC->radE8)) r = m3_curEvent420DBC->radE8;
    b[1] = r + b[1] + 2.0f;
    if (sub_000D0DC0(a, r, c, d) > 0) return 1;
    return r2b_PoolGetB(a, b, c, d);
}

typedef struct M3Boss13 { uint8_t unk00[0xD8]; int32_t iD8; uint8_t unkDC[4]; int32_t phaseE0; uint8_t unkE4[4]; float tE8; uint8_t unkEC[0x24]; float v110[3]; uint8_t unk11C[0x10]; int32_t st12C; uint8_t unk130[0x20]; uint32_t f150; } M3Boss13;
void sub_000CFF90(M3Boss13 *b, int a, float t);
int  abc_TimerDone(M3Boss13 *b);
void sub_000CA600(M3Boss13 *b);
void abc_SetState(M3Boss13 *b, int st);
void sub_000CEE40(int a, int b);
void sub_000AA2E0(int a);

/* 0xBE8E0: boss rise phase (velocity cleared, 2-second timer): phase 0 flags the boss, picks its state from +0xD8 and starts the rise; phase 1 waits 18 time units; phase 2 waits for the timer, restarts it at 20 and goes to state 0x1D (flag 0x10000) or back to state 1. */
void m3_BossRiseBE8E0(M3Boss13 *b) {
    sub_000CFF90(b, 1, 2.0f);
    b->v110[2] = 0.0f; b->v110[1] = 0.0f; b->v110[0] = 0.0f;
    switch (b->phaseE0) {
    case 2:
        if (!abc_TimerDone(b)) return;
        sub_000CA600(b);
        sub_000CFF90(b, 1, 20.0f);
        if (b->f150 & 0x10000) { abc_SetState(b, 0x1D); return; }
        b->f150 &= ~0x6000u;
        b->st12C = 0;
        abc_SetState(b, 1);
        return;
    case 1:
        if (!(b->tE8 > 18.0f)) return;
        { volatile int z; sub_000CEE40(0, 0); z = 0; }
        break;
    case 0:
        b->f150 |= 0x28006001;
        b->st12C = b->iD8 + 0x4A;
        sub_000AA2E0(8);
        sub_000CEE40(1, 1);
        break;
    default:
        return;
    }
    b->phaseE0++;
    b->tE8 = 0.0f;
}

extern int m3_swapReady420088;
extern int m3_swapBitA42008C;
extern int m3_forceKind420090;
extern int r2b_g420080;
extern int m3_swapBusy420094;
extern int m3_menuLock41FFAC;
extern int m1_gameMode41FF94;
extern uint32_t aab_flags420010;
extern uint32_t m3_padSwapA41CD20;
extern uint32_t m3_padSwapB41CD24;
extern int m1_plMode420078;
extern int m1_g42007C;
extern uint8_t g_stats[];
int  sub_0019BE60(int id);
int  r2b_TestBit(int bit);
uint32_t m1_PadHit04ECE0(int pad);
void r2d_PlayerResetD8(void *s);
void sub_000D3780(void *s);

/* 0xD41D0: character swap check: refresh the two swap story bits (0xF5, 0xF4); while a swap is pending run it; otherwise, when nothing blocks (menus, game modes 2 and 4, busy flags, prompt 0x4101) and a swap button is hit, reset the player and pick the target form (button A: form 2 when unlocked unless already 2; button B: form 1 unless already 1; else form 0) and flag the swap. */
void m3_SwapCheckD41D0(void) {
    uint32_t m;
    m3_swapReady420088 = 1;
    m3_swapBitA42008C = r2b_TestBit(0xF5);
    m3_forceKind420090 = r2b_TestBit(0xF4);
    m3_swapBusy420094 = 0;
    if (r2b_g420080 < 0) {
        if (m3_menuLock41FFAC != 0) return;
        if (m1_gameMode41FF94 == 2 || m1_gameMode41FF94 == 4) return;
        if (aab_flags420010 & 0x40282006) return;
        if (sub_0019BE60(0x4101)) return;
        m = m1_PadHit04ECE0(0);
        if (!(m & (m3_padSwapB41CD24 | m3_padSwapA41CD20))) return;
        r2d_PlayerResetD8(g_stats);
        if (m & m3_padSwapA41CD20) {
            if (m1_plMode420078 == 2) {
zero:
                m1_g42007C = 0;
            } else {
                if (m3_forceKind420090 == 0) return;
                m1_g42007C = 2;
            }
        } else {
            if (m1_plMode420078 == 1) goto zero;
            if (m3_swapBitA42008C == 0) return;
            m1_g42007C = 1;
        }
        r2b_g420080 = 0;
        aab_flags420010 |= 0x80000000;
        return;
    }
    sub_000D3780(g_stats);
}
