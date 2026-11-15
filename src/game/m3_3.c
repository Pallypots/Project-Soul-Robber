/* Area m3, file 3: object release, AI resets, story checks, effects. Names inferred. */
#include <stdint.h>

typedef struct M3Cam3 { uint8_t unk00[0x12C]; int32_t snd12C; } M3Cam3;
typedef struct M3Obj3 { uint8_t unk00[0xC]; uint32_t fC; uint32_t f10; } M3Obj3;
extern M3Cam3 *m1_cam3F610C;
int  sub_000E0770(void);
void sub_000E3BA0(int s);
int  sub_00199E70(int h);
void m1_SndStop048250(int h);
void sub_00033B30(M3Obj3 *o);
void r1b_RecDetachNodes(M3Obj3 *o);
void *sub_0001D960(void *o, int kind);
void sub_0001D910(void *o, void *c);

/* 0xF42C0: release an active object: stop the current stream, stop the camera's pending sound, detach it, mark it inactive (flags |= 0xD), and remove its kind 5 and kind 0xD components. 0 when it was not active. */
int m3_ObjReleaseF42C0(M3Obj3 *o) {
    M3Cam3 *c = m1_cam3F610C; void *a, *b;
    sub_000E3BA0(sub_000E0770());
    if (!(*(uint8_t *)&o->fC & 1)) return 0;
    if (c->snd12C != -1 && sub_00199E70(c->snd12C)) {
        m1_SndStop048250(c->snd12C);
        c->snd12C = -1;
    }
    sub_00033B30(o);
    o->f10 |= 0xD;
    o->fC &= ~1u;
    r1b_RecDetachNodes(o);
    a = sub_0001D960(o, 5);
    b = sub_0001D960(o, 0xD);
    sub_0001D910(o, a);
    sub_0001D910(o, b);
    return 1;
}

typedef struct M3Ai3 { uint8_t unk00[0xA4]; float fA4; uint8_t unkA8[0x48]; float vF0[4]; uint8_t unk100[0x10]; int32_t i110, i114; } M3Ai3;
extern float b10_frameDelta;
extern uint8_t m1_snd3E1270[];
int  sub_000E3380(void);
void sub_00019000(void *s, int a);
void sub_000BCA50(int a);

/* 0xF15B0: stop the AI (velocity = rate * 0, counters cleared, +0xA4 = 0), touch its kind 5 component, and unless the game mode is 4 or 5 play cue 1 on 0x3E1270 and call 0xBCA50(3). Hangs on a null record. */
void m3_AiStopF15B0(void *o, M3Ai3 *e) {
    if (e == 0) for (;;) ;
    e->vF0[0] = b10_frameDelta * 0.0f;
    e->vF0[1] = b10_frameDelta * 0.0f;
    e->vF0[2] = b10_frameDelta * 0.0f;
    e->vF0[3] = b10_frameDelta * 0.0f;
    e->i110 = 0; e->i114 = 0;
    e->fA4 = 0.0f;
    sub_0001D960(o, 5);
    {
        int m = sub_000E3380();
        if (m != 4 && m != 5) {
            sub_00019000(m1_snd3E1270, 1);
            sub_000BCA50(3);
        }
    }
}

typedef struct M3Ev3 { uint8_t unk00[4]; int32_t i4, i8; } M3Ev3;
extern M3Ev3 *m3_curEvent420DBC;
int  r2b_TestBit(int bit);
void r1d_CamSetFlag(int a, int b);

/* 0xAAC10: fill a 3-int setting for mode k (0: all zero, 1: bit 0 + 10, 3: 0 + 20, returns early for 0 and 1), then set camera flag 3 to 1 only when story bit 0xCA is clear and the current event is (12, 0x22), else 0. */
int m3_ModeSetupAAC10(int k, int *s) {
    if (k == 0) { s[0] = 0; s[1] = 0; s[2] = 0; return 1; }
    if (k == 1) { s[0] |= 1; s[1] = 10; s[2] = 0; return 1; }
    if (k == 3) { s[0] = 0; s[1] = 0x14; }
    if (!r2b_TestBit(0xCA) && m3_curEvent420DBC && m3_curEvent420DBC->i4 == 0xC && m3_curEvent420DBC->i8 == 0x22) {
        r1d_CamSetFlag(3, 1);
        return 1;
    }
    r1d_CamSetFlag(3, 0);
    return 1;
}

typedef struct M3Mdl3 { uint8_t unk00[0xC4]; uint8_t *bonesC4; } M3Mdl3;
typedef struct M3Hold3 { uint8_t unk00[0x20]; M3Mdl3 *mdl20; } M3Hold3;
typedef struct M3Boss3 { uint8_t unk00[0xFD8]; M3Hold3 *holdFD8; } M3Boss3;
void a3c_VecCopy(float *dst, const float *src);
void m1_FxStart0C4C90(int id, float a, float b, int c, float *pos, float *dir, float *up);

/* 0xC53B0: start effect 0x24 (3.0, 18.0) at the bone at +0x1F0 of the held model, lowered by 18 units. */
void m3_BoneFxC53B0(M3Boss3 *b) {
    float p[4], d[4];
    p[0] = 0.0f; p[1] = 0.0f; p[2] = 0.0f; p[3] = 1.0f;
    d[0] = 0.0f; d[1] = 0.0f; d[2] = 0.0f; d[3] = 1.0f;
    a3c_VecCopy(p, (float *)(b->holdFD8->mdl20->bonesC4 + 0x1F0));
    p[1] = p[1] - 18.0f;
    p[3] = 1.0f;
    m1_FxStart0C4C90(0x24, 3.0f, 18.0f, 0, p, d, d);
}
