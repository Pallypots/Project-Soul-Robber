/* Area m1, file 197: cutscene sound helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Cut197 {
    int32_t kind0; uint8_t unk04[0x2E4]; int32_t cue2E8; int32_t strm2EC; uint32_t ms2F0; uint8_t unk2F4[4]; int32_t live2F8;
    uint8_t unk2FC[0x2C]; int32_t keep328;
} M1Cut197;
extern int32_t m1_cutCues317BD4[];
extern int32_t m1_cutBusy3F11AC;
extern int32_t m1_cutFlag3F0750;
int  sub_0019A900(int s);
uint32_t m1_SndTimerSet053F70(uint32_t ms);
void sub_0019B800(int s, int ms);
void sub_000E51F0(M1Cut197 *c);
void a5b_SndBegin(void);
void sub_00049B00(int cue);

/* 0xE5C30: finish a cutscene's audio: resync the timer when the stream is in state 2 or 5, and once it ends fade it out, restart music and play the end cues; returns the stream id (hangs on a null cutscene). */
int m1_CutAudioEnd0E5C30(int unused, M1Cut197 *c) {
    if (c == 0) for (;;) ;
    switch (sub_0019A900(c->strm2EC)) {
    case 2:
    case 5:
        m1_SndTimerSet053F70(c->ms2F0);
    case 7:
        if (c->live2F8) {
            sub_0019B800(c->strm2EC, 1000);
            sub_000E51F0(c);
            if (c->keep328 == 0) a5b_SndBegin();
            c->live2F8 = 0;
            sub_00049B00(c->cue2E8 + 3);
            sub_00049B00(m1_cutCues317BD4[c->kind0]);
        }
        break;
    }
    m1_cutBusy3F11AC = 0;
    m1_cutFlag3F0750 = 0;
    return c->strm2EC;
}

typedef struct M1BsC197 { int32_t k0; int32_t a4; int32_t b8; } M1BsC197;
typedef struct M1Bs197 { uint8_t unk00[0x8C]; void *body8C; uint8_t unk90[0x18]; int16_t wA8; uint8_t unkAA[0x56]; int32_t i100; int32_t i104; int32_t i108; } M1Bs197;
extern M1Bs197 *g_acb_bossMgr;
void *a12_List_At(void *l, int i);
void  sub_000E1060(void *o, int k, int a, int b);

/* 0xF41C0: pass a hit command to the boss: commands 0x20..0x25 also go to both hands; the body gets it unless the boss is in a protected phase. */
void m1_BossHit0F41C0(M1BsC197 *c) {
    M1Bs197 *b = g_acb_bossMgr; void *body = b->body8C; int volatile k;
    if (b->i104 == 2) return;
    k = c->k0;
    if (k >= 0x20 && k <= 0x25) {
        sub_000E1060(a12_List_At(body, 0), k, c->a4, c->b8);
        sub_000E1060(a12_List_At(body, 1), c->k0, c->a4, c->b8);
    }
    if (b->i100 == 4 || b->i100 == 5) return;
    if (b->i108 == 2 || b->i108 == 3) return;
    if (b->wA8 == 0 || b->wA8 == 1) return;
    sub_000E1060(body, c->k0, c->a4, c->b8);
}

typedef struct M1Pl197 { uint8_t unk00[0xF8]; int32_t camF8; } M1Pl197;
extern float g_ac0_stickFX[2];
float sub_000BC040(const float *stick, int cam);
float r6c_AngleAdd(float a);

/* 0xCCA40: turn needed to face the stick direction (camera relative), wrapped to [-pi, pi]; 0 when the stick is centred. */
float m1_StickTurn0CCA40(M1Pl197 *p, float ang) {
    float a;
    if (g_ac0_stickFX[0] != 0.0f) goto calc;
    if (g_ac0_stickFX[1] != 0.0f) goto calc;
    return 0.0f;
calc:
    a = ang - r6c_AngleAdd(sub_000BC040(g_ac0_stickFX, p->camF8) * -1.0f);
    if (-3.14159274f > a) do a += 6.28318548f; while (-3.14159274f > a);
    if (a > 3.14159274f) do a -= 6.28318548f; while (a > 3.14159274f);
    return a;
}

typedef struct M1MnB197 { uint8_t unk00[0x60]; uint8_t pos60[0x10]; } M1MnB197;
typedef struct M1Mn197 { uint8_t unk00[0x8C]; M1MnB197 *body8C; uint8_t unk90[0x120]; int32_t i1B0; } M1Mn197;
extern M1Mn197 *m1_minion3F6120;
int   sub_000F60C0(M1MnB197 *b, int k, float *out);
void *aab_Attach36750(void *o, int k);
void  sub_00033880(void *fx, float *out);
void  sub_00034DD0(void *fx, float *a, float *b, float *dir);
void  sub_000F8270(M1Mn197 *m);
int   aab_Effect494D0(int id, void *pos, int arg);

/* 0xFE7E0: minion slam: if a target spot is found, spawn the slam effect pointing down, run the attack, play effect 0x14C and mark it busy. */
void m1_MinionSlam0FE7E0(void) {
    float v[4], hit[4], pos[8], tmp[8]; M1Mn197 *m = m1_minion3F6120; void *fx;
    if (sub_000F60C0(m->body8C, 0, hit) == -1) return;
    v[0] = 0.0f; v[2] = 0.0f; v[1] = -1.0f; v[3] = 1.0f;
    fx = aab_Attach36750(m->body8C, 0);
    sub_00033880(fx, pos);
    sub_00034DD0(fx, hit, tmp, v);
    sub_000F8270(m);
    aab_Effect494D0(0x14C, m->body8C->pos60, 1);
    m->i1B0 = 1;
}

typedef struct M1Cs197 { uint8_t unk00[4]; int32_t kind4; int32_t sub8; } M1Cs197;
typedef struct M1PwP197 { uint8_t unk00[0xEFC]; M1Cs197 *cosEFC; } M1PwP197;
extern float m1_frameTime42C858;
int   Stats_TestFlags(M1PwP197 *p, int f);
int   sub_000EDF10(M1Cs197 *c);
float b16_ParamF8(int kind, int sub, int lvl);
int   sub_00142630(M1Cs197 *c);
int   Stats_Get(M1PwP197 *p, int k);
void  m1_PowerAdd0CAE20(M1PwP197 *p, float d);

/* 0xCAEC0: drain the costume's power each frame at its rate; some costume modes drain almost instantly unless the matching stat is high enough. */
void m1_CostumeDrain0CAEC0(M1PwP197 *p) {
    M1Cs197 *c; float rate;
    if (p->cosEFC == 0 || Stats_TestFlags(p, 2)) return;
    c = p->cosEFC;
    rate = b16_ParamF8(c->kind4, c->sub8, sub_000EDF10(c));
    if (c->kind4 == 2 && (c->sub8 == 2 || c->sub8 == 0x10) && !sub_00142630(c)) {
        if (c->sub8 != 0x10 || Stats_Get(p, 4) < 2) rate = 9999.99023f;
    }
    m1_PowerAdd0CAE20(p, m1_frameTime42C858 * rate * -1.0f);
}
