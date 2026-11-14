/* Area m1, file 192: effect state helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Sp192 { uint8_t unk00[0x84]; float spin84; } M1Sp192;
typedef struct M1SpE192 { uint8_t unk00[0x58]; int32_t i58; float t5C; } M1SpE192;
extern float m1_frameRate42C85C;
void sub_0013A380(M1Sp192 *o, int a, int *out);
void aab_Attach36750(void *o, int k);
void sub_000ED780(void *o);

/* 0x178160: spin-out state: query the target once, after 1 unit detach (mode 2); then spin 10 per tick and finish after 3 units. */
void m1_FxSpinOut178160(M1Sp192 *o, M1SpE192 *e) {
    int t = -1;
    switch (e->i58) {
    case 0:
        sub_0013A380(o, 1, &t);
        if (e->t5C > 1.0f) { aab_Attach36750(o, 2); e->i58++; }
        break;
    case 1:
        o->spin84 += m1_frameRate42C85C * 10.0f;
        if (e->t5C > 3.0f) sub_000ED780(o);
        break;
    }
}

typedef struct M1Sys192 { uint8_t unk00[0x128]; int32_t fx128; } M1Sys192;
typedef struct M1Sv192 { uint8_t unk00[0x60]; uint8_t pos60[0x10]; } M1Sv192;
extern uint32_t m1_level413178;
extern float    m1_spinSpd3FE384;
extern int32_t  m1_spinRev3FE388;
extern int32_t  m1_spinDir3FE378;
M1Sys192 *r4i_GetSys(void);
int  aab_Rand(void);
int  aab_Effect494D0(int id, void *pos, int arg);

/* 0x182B70: start the spinner: stop it, pick its direction by level (fixed, from the saved direction, or random) and start its loop effect once. */
void m1_SpinnerStart182B70(M1Sv192 *o) {
    M1Sys192 *s = r4i_GetSys();
    m1_spinSpd3FE384 = 0.0f;
    { uint32_t l = m1_level413178;
      if (l > 2) goto rnd;
      if (l == 0) m1_spinRev3FE388 = 0;
      else if (l == 1) m1_spinRev3FE388 = m1_spinDir3FE378 != 0;
      else if (l == 2) { rnd: m1_spinRev3FE388 = (signed char)~(signed char)aab_Rand() & 1; } }
    if (s->fx128 == -1) s->fx128 = aab_Effect494D0(0x1C9, o->pos60, 1);
}

typedef struct M1Gx192 { uint8_t unk00[8]; int32_t kind8; uint8_t unk0C[0x58]; float f64; } M1Gx192;
typedef struct M1Gp192 { uint8_t unk00[0x6C]; int32_t anim6C; uint8_t unk70[0x1C]; M1Gx192 *x8C; } M1Gp192;
extern float m1_fps42C964;
#define M1_HURT192(a) ((a) == 0xD || (a) == 0x14 || (a) == 0x17 || (a) == 0x16 || (a) == 0x18 || (a) == 0x19)

/* 0xF6330: build up the special gauge each frame unless the player is in a hurt or special animation (which ones depend on the costume kind 3/4/5). */
void m1_GaugeTick0F6330(M1Gp192 *p) {
    M1Gx192 *x; int a;
    if (p == 0) return;
    x = p->x8C;
    a = p->anim6C;
    if (x->kind8 == 3) {
        if (a == 0x1F || a == 0x23 || a == 0x24 || a == 0x25 || a == 0x26) return;
        goto k4;
    } else if (x->kind8 == 4) {
k4:     if (M1_HURT192(a)) return;
    } else if (x->kind8 == 5) {
        if (M1_HURT192(a)) return;
    } else return;
    x->f64 += 34.0f / m1_fps42C964;
}

typedef struct M1ScO192 { uint8_t unk00[0x30]; struct { uint8_t unk00[0x14]; int32_t h14; } *p30; } M1ScO192;
typedef struct M1ScOp192 { uint8_t unk00[4]; uint8_t *args4; uint8_t unk08[0x48]; float wait50; } M1ScOp192;
M1ScO192 *m1_ObjFind0DE170(int a, int b);
int  aab_Ctl1AEE50(int h, int k);
int  af0_GetVar3EDCF0(void);
void af0_SetVar3EDCF0(int v);
int  af0_GetVar3EE6AC(void);
void af0_Release3EE6A8(void);
void r3_GlobalAnim174470(int k);

/* 0xDCE40: script op "end object cutscene": stop the global anim if the object is still playing; wait while the timer runs (returns 0x3000), then release and return 0x2002. */
int m1_ScrEndCut0DCE40(M1ScOp192 *op) {
    M1ScO192 *o = m1_ObjFind0DE170(op->args4[0], op->args4[1]);
    if (o != 0 && (aab_Ctl1AEE50(o->p30->h14, 0) & 2) && af0_GetVar3EDCF0()) {
        r3_GlobalAnim174470(0);
        af0_SetVar3EDCF0(0);
    }
    if (af0_GetVar3EE6AC() != 5 && !(0.0f >= op->wait50)) return 0x3000;
    if (o != 0 && af0_GetVar3EDCF0()) r3_GlobalAnim174470(0);
    af0_Release3EE6A8();
    af0_SetVar3EDCF0(0);
    return 0x2002;
}
