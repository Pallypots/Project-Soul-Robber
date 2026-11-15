/* Area m3, file 9: boss phase states and aim point. Names inferred. */
#include <stdint.h>

typedef struct M3Parts9 { uint8_t unk00[0x14]; void *parts14; } M3Parts9;
typedef struct M3Hold9 { uint8_t unk00[0x30]; M3Parts9 *mdl30; uint8_t unk34[0x2C]; float pos60[4]; } M3Hold9;
typedef struct M3Boss9 {
    uint8_t unk00[0x24]; float home24[4]; uint8_t unk34[0xAC];
    int32_t phaseE0; uint8_t unkE4[0x2C]; float v110[3]; uint8_t unk11C[0x10]; int32_t st12C; uint8_t unk130[0x20]; uint32_t f150;
    uint8_t unk154[0x1C4]; int32_t lock318; int32_t cur31C; uint8_t unk320[0x88]; int32_t mode3A8[0x20]; int32_t who428[0x40];
    int32_t idx528[0x275]; uint32_t hEFC; float aimF00[4]; uint8_t unkF10[0xC8]; M3Hold9 *holdFD8;
} M3Boss9;
extern uint8_t r6e_obj420EC0[];
int  m1_PadKeyCCD60(int a, int b, int c);
void abc_SetState(M3Boss9 *b, int st);
int  abc_TimerDone(M3Boss9 *b);
void r4d_PartsClearMask(void *parts, int m);
void sub_000CB990(M3Boss9 *b, float t);
void sub_000BC5F0(void *o);
void sub_000BC6B0(void *o, int a);
void sub_000CA600(M3Boss9 *b);
int  abc_IsActive(M3Boss9 *b);

/* 0xC04A0: boss intro phase step (velocity cleared): phase 0 flags the boss, starts a 4-second timer and the arena object, then goes to state 0x25 when active or waits (state 9, phase 1); phase 1 waits for the timer, clears the parts mask and goes to 0x25; phase 4 waits for the pad key. */
void m3_BossIntroC04A0(M3Boss9 *b) {
    b->v110[2] = 0.0f; b->v110[1] = 0.0f; b->v110[0] = 0.0f;
    switch (b->phaseE0) {
    case 4:
        if (m1_PadKeyCCD60(0, 0, 1)) return;
        abc_SetState(b, 0x25);
        return;
    case 1:
        if (!abc_TimerDone(b)) return;
        b->st12C = 2;
        r4d_PartsClearMask(b->holdFD8->mdl30->parts14, 1);
        abc_SetState(b, 0x25);
        return;
    case 0:
        b->f150 |= 0x8000001;
        sub_000CB990(b, 4.0f);
        sub_000BC5F0(r6e_obj420EC0);
        sub_000BC6B0(r6e_obj420EC0, 1);
        sub_000CA600(b);
        if (abc_IsActive(b) > 0) { b->st12C = 2; abc_SetState(b, 0x25); return; }
        b->st12C = 9;
        b->phaseE0 = 1;
        return;
    }
}

void r4c_VecSub(float *dst, const float *a, const float *b);
void rbi_VecNorm(float *d, const float *s);
void rbi_VecScale(float *d, const float *s, float k);
void r4e_VecAdd4(float *d, const float *a, const float *b);
void a3c_VecCopy(float *dst, const float *src);
void sub_000CF2C0(M3Boss9 *b, float *dir);

/* 0xCBC00: set the boss aim point 25 units from the held object along a direction (towards home when the current lock slot is in mode 1 for another target, else from 0xCF2C0), 5 units lower. -1 without a target handle, else 1. */
int m3_BossAimCBC00(M3Boss9 *b) {
    float d[4]; int k;
    d[0] = 0.0f; d[1] = 0.0f; d[2] = 0.0f; d[3] = 1.0f;
    if (b->hEFC == 0) return -1;
    if (b->lock318 && (k = b->idx528[b->cur31C], b->mode3A8[k] == 1) && b->who428[k] != b->hEFC) {
        r4c_VecSub(d, b->home24, b->holdFD8->pos60);
        d[1] = 0.0f;
        rbi_VecNorm(d, d);
    } else {
        sub_000CF2C0(b, d);
    }
    rbi_VecScale(d, d, 25.0f);
    r4e_VecAdd4(d, d, b->holdFD8->pos60);
    a3c_VecCopy(b->aimF00, d);
    b->aimF00[1] -= 5.0f;
    return 1;
}

typedef struct M3Hero9 { uint8_t unk00[0x60]; float pos60[4]; uint8_t unk70[0xC0]; int32_t list130; } M3Hero9;
typedef struct M3Scr9 { uint8_t unk00[0x8C]; M3Hero9 *hero8C; uint8_t unk90[0x20C]; int32_t on29C; int32_t live2A0[12]; uint8_t unk2D0[0]; } M3Scr9;
typedef struct M3ScrB9 { uint8_t unk00[0x2D0]; float r2D0; float c2D4[4]; int32_t h2E4[12]; } M3ScrB9;
extern uint8_t *m1_scr3F6130;
int  rbj_ListPlayMotion(M3Hero9 *h, int list, int a, int b);
void sub_00033880(int h, float *m);
void rbj_ObjSetMotionDir(int h, float *pos, float *rot, float *up);

/* 0x1029B0: start the ring effect around the hero: radius 20 at the hero's position, then twelve motion handles spread every 30 degrees (starting at 90, wrapped to -pi..pi), each placed at the hero with its rotation. */
void m3_RingStart1029B0(void) {
    uint8_t *s = m1_scr3F6130; M3Hero9 *h = ((M3Scr9 *)s)->hero8C;
    float up[4], rot[4], m[16]; int i; int *p; float a;
    up[0] = 0.0f; up[2] = 0.0f;
    ((M3Scr9 *)s)->on29C = 1;
    ((M3ScrB9 *)s)->r2D0 = 20.0f;
    up[1] = 1.0f; up[3] = 1.0f;
    a3c_VecCopy(((M3ScrB9 *)s)->c2D4, h->pos60);
    p = ((M3ScrB9 *)s)->h2E4;
    for (i = 0; i < 12; i++, p++) {
        a = (float)i * 0.5235988f + 1.5707964f;
        p[-0x11] = 1;
        if (a > 3.1415927f) a -= 6.2831855f;
        rot[0] = 0.0f; rot[2] = 0.0f; rot[3] = 1.0f; rot[1] = a;
        *p = rbj_ListPlayMotion(h, h->list130, 2, 1);
        sub_00033880(*p, m);
        rbj_ObjSetMotionDir(*p, h->pos60, rot, up);
    }
}

typedef struct M3Strm9 { int32_t kind0; uint8_t unk04[0x2E4]; int32_t h2E8; uint8_t unk2EC[4]; int32_t last2F0; int32_t loops2F4; int32_t hold2F8; } M3Strm9;
extern int g_acb_3F0A78;
extern int m1_cutBusy3F11AC;
extern int m1_cutFlag3F0750;
int  r2d_StageStreamPos(M3Strm9 *s);
unsigned r1c_LookupB(int h);
unsigned r1c_LookupA(int h);
void r2b_TrackMarkBefore(M3Strm9 *s, int track, int pos, int a);
void sub_000E3BA0(M3Strm9 *s);

/* 0xE3C90: detect a stream loop: when not held and the last position is past the current one plus half the loop span, count the loop and either stop a kind-6 stream or re-mark tracks 1, 2, 5, 6 and 7 at the loop point; clears the cutscene flags. Records the position; 1 on a loop, else 0. Hangs on null. */
int m3_StreamLoopE3C90(M3Strm9 *s) {
    int cur, t, n;
    if (s == 0) for (;;) ;
    cur = r2d_StageStreamPos(s);
    if (s->hold2F8 == 0) {
        t = r2d_StageStreamPos(s);
        if (s->last2F0 > t + (int)((r1c_LookupB(s->h2E8) + r1c_LookupA(s->h2E8)) >> 1)) {
            s->loops2F4++;
            if (s->kind0 != 6) {
                n = r1c_LookupA(s->h2E8);
                r2b_TrackMarkBefore(s, 1, n, 0);
                r2b_TrackMarkBefore(s, 2, n, 0);
                r2b_TrackMarkBefore(s, 5, n, 0);
                r2b_TrackMarkBefore(s, 6, n, 0);
                r2b_TrackMarkBefore(s, 7, n, 0);
            } else {
                sub_000E3BA0(s);
                g_acb_3F0A78 = 0;
            }
            m1_cutBusy3F11AC = 0;
            m1_cutFlag3F0750 = 0;
            s->last2F0 = cur;
            return 1;
        }
    }
    s->last2F0 = cur;
    return 0;
}

typedef struct M3TmRec9 { int32_t start0; uint8_t unk04[8]; int32_t kindC; int32_t len10; int32_t flag14; } M3TmRec9;
typedef struct M3Tm9 {
    uint8_t unk00[0x408]; int32_t on408; uint8_t unk40C[0xC]; int32_t act418; int32_t a41C; uint8_t unk420[0xC]; int32_t a42C;
    int32_t slot430; int32_t start434; int32_t lo438; int32_t hi43C; int32_t col440; int32_t text444; int32_t flag448;
} M3Tm9;
extern int32_t m3_timerCol318578[];
int  m1_HudText0E85D0(int kind, float t);
void sub_000E8BB0(float t);
void sub_000E8A50(int a, int b);

/* 0xEA060: start a timed window from a record: clear the eight slot flags, create its HUD text, mark slot 0 active with the start time and the window [start - len/2, start + len/2], its colour by kind, then set the HUD time (len * 0.03) and show it. */
void m3_TimerStartEA060(M3Tm9 *o, M3TmRec9 *r) {
    int32_t *z; int h;
    if (o == 0 || r == 0 || o->on408 == 0) return;
    z = &o->slot430;
    z[0] = 0; z[7] = 0; z[14] = 0; z[21] = 0; z[28] = 0; z[35] = 0; z[42] = 0; z[49] = 0;
    h = m1_HudText0E85D0(r->kindC, (float)r->len10 * 0.03f);
    o->a42C = 0; o->a41C = 0;
    o->act418 = 1;
    o->slot430 = 1;
    o->start434 = r->start0;
    o->lo438 = r->start0 - r->len10 / 2;
    o->hi43C = r->len10 / 2 + r->start0;
    o->col440 = m3_timerCol318578[r->kindC];
    o->text444 = h;
    o->flag448 = r->flag14;
    sub_000E8BB0((float)r->len10 * 0.03f);
    sub_000E8A50(1, 0);
}

typedef struct M3Glow9 { uint32_t f0; uint8_t unk04[4]; float max8; float curC; uint8_t unk10[0x14]; float lvl24; float rate28; uint8_t unk2C[0xAC]; void *mdlD8; } M3Glow9;
extern float m1_frameTime42C858;
void r2b_ModelSetColor(void *m, float *c);

/* 0xA79E0: pulse an object's glow (flag 2): with flag 0x40 the pulse speed follows the remaining fraction (4, 8 or 16 per frame unit, keeping its direction); the level bounces between 64 and 255 and is applied as a grey colour with alpha 128. */
void m3_GlowPulseA79E0(M3Glow9 *o) {
    float c[4]; float v;
    c[0] = 0.0f; c[1] = 0.0f; c[2] = 0.0f; c[3] = 128.0f;
    if (!(o->f0 & 2)) return;
    if (o->f0 & 0x40) {
        float r = o->curC / o->max8, s;
        if (r >= 0.5f) s = 4.0f;
        else if (r >= 0.25f) s = 8.0f;
        else s = 16.0f;
        if (!(o->rate28 > 0.0f)) s *= -1.0f;
        o->rate28 = s;
    }
    v = o->rate28 * m1_frameTime42C858 + o->lvl24;
    o->lvl24 = v;
    if (o->rate28 > 0.0f) {
        if (v >= 255.0f) { o->rate28 = -4.0f; o->lvl24 = 255.0f; }
    } else {
        if (64.0f >= v) { o->rate28 = 4.0f; o->lvl24 = 64.0f; }
    }
    c[2] = o->lvl24; c[1] = o->lvl24; c[0] = o->lvl24;
    r2b_ModelSetColor(o->mdlD8, c);
}
