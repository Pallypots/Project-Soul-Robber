/* Area m1, file 190: AI turning helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Tn190 { uint8_t unk00[0x54]; float yaw54; } M1Tn190;
typedef struct M1TnE190 { uint8_t unk00[0x4C]; int32_t i4C; int32_t i50; float f54; uint8_t unk58[0x68]; int32_t iC0; } M1TnE190;
typedef void (*M1TnCb190)(M1Tn190 *o, M1TnE190 *e);
extern uint8_t *g_playerObj;
extern float m1_frameTime42C858;
extern M1TnCb190 m1_tnDone32B1B4;
float sub_00113290(M1Tn190 *o, const void *target);

/* 0x173F10: turn toward the player at a fixed rate (side picked by 0x113290), and when the turn is no longer locked restart the move state through the done callback. */
void m1_AiTurnToPlayer173F10(M1Tn190 *o, M1TnE190 *e) {
    float d;
    if (sub_00113290(o, g_playerObj + 0x60) > 0.0f) d = m1_frameTime42C858 * 0.0122173047f;
    else d = 0.0f - m1_frameTime42C858 * 0.0122173047f;
    o->yaw54 += d;
    if (e->iC0 == 0) {
        e->i4C = 1; e->i50 = 0; e->f54 = 0.0f;
        m1_tnDone32B1B4(o, e);
    }
}

typedef struct M1Key190 { uint8_t unk00[8]; int32_t kind8; } M1Key190;
typedef struct M1KeyE190 { uint8_t unk00[0x4C]; int32_t i4C; int32_t i50; float f54; uint8_t unk58[4]; uint32_t i5C; } M1KeyE190;
typedef void (*M1KeyCb190)(M1Key190 *o, M1KeyE190 *e);
extern int32_t m1_fxBones3FD7BC;
extern M1KeyCb190 m1_keyReset32B1C0;
M1Key190  *r2c_FindKey(int kind, int from);
M1KeyE190 *rbi_Comp1D960(M1Key190 *o, int comp);

/* 0x174540: reset the move state of every kind-6 key object, except kinds 7, 0x17, 0x10..0x14 and kind 1 with flag 0x1000 (hangs if one has no component 8). */
void m1_KeysReset174540(void) {
    M1Key190 *o; M1KeyE190 *e; int volatile k;
    if (m1_fxBones3FD7BC == 0) return;
    for (o = r2c_FindKey(6, -1); o != 0; o = r2c_FindKey(-1, -1)) {
        e = rbi_Comp1D960(o, 8);
        if (e == 0) for (;;) ;
        k = o->kind8;
        if (k == 0x17 || k == 7) continue;
        if (k == 1 && (e->i5C & 0x1000)) continue;
        if (k >= 0x10 && k <= 0x14) continue;
        e->i4C = 4; e->i50 = 0; e->f54 = 0.0f;
        m1_keyReset32B1C0(o, e);
    }
}

typedef struct M1En190 { uint8_t unk00[0x10]; uint32_t i10; uint8_t unk14[0x4C]; uint8_t pos60[0xC8]; uint8_t b128; } M1En190;
typedef struct M1EnE190 { uint8_t unk00[0x70]; float f70; } M1EnE190;
typedef struct M1EnN190 { uint8_t unk00[4]; int32_t kind4; } M1EnN190;
int  Stats_HasEFC(void);
M1EnN190 *m1_FindFirstEDB10(int kind);
M1EnN190 *r2c_FindNext(void);
void rbj_SetState(M1En190 *o, M1EnE190 *e, int st);
void aab_Effect494D0(int id, void *pos, int arg);
void aab_Attach36750(void *o, int k);

/* 0x18AF00: enemy upkeep: mirror the stats flag into bit 0, clear the recover timer once every kind-1 object is kind 5, re-enter state 1 when it has run out, and play effect 0xD7 when flagged. */
void m1_EnemyUpkeep18AF00(M1En190 *o, M1EnE190 *e) {
    M1EnN190 *n;
    if (Stats_HasEFC() > 0) o->i10 |= 1; else o->i10 &= ~1u;
    for (n = m1_FindFirstEDB10(1); n != 0; n = r2c_FindNext())
        if (n->kind4 != 5) goto check;
    e->f70 = 0.0f;
check:
    if (0.0f >= e->f70 && (o->b128 & 0x18)) rbj_SetState(o, e, 1);
    if (o->b128 & 8) {
        aab_Effect494D0(0xD7, o->pos60, 0);
        aab_Attach36750(o, 3);
    }
}

typedef struct M1Rt190 { uint8_t unk00[0x20]; float *mtx20; uint8_t unk24[0x2C]; float rot50[3]; } M1Rt190;
void a3c_VecCopy(float *dst, const float *src);
void r4e_MatIdentity(float *m);
void rbj_MatRotZ(float *dst, const float *src, float a);
void rbj_MatRotY(float *dst, const float *src, float a);
void rbj_MatRotX(float *dst, const float *src, float a);
void r4f_MatCopy1ADA40(float *dst, const float *src);

/* 0x145650: set an object's rotation (x, y, z): store it and rebuild the matrix as Z, Y then X rotations keeping its position. */
void m1_SetRot145650(M1Rt190 *o, float x, float y, float z) {
    float m[16];
    o->rot50[0] = x; o->rot50[1] = y; o->rot50[2] = z;
    r4e_MatIdentity(m);
    rbj_MatRotZ(m, m, z);
    rbj_MatRotY(m, m, y);
    rbj_MatRotX(m, m, x);
    a3c_VecCopy(&m[12], o->mtx20 + 12);
    r4f_MatCopy1ADA40(o->mtx20, m);
}

typedef struct M1AiW190 { uint8_t unk00[4]; uint32_t i4; } M1AiW190;
typedef struct M1AiJ190 { uint8_t unk00[0x58]; int32_t i58; uint8_t unk5C[0xC]; float f68; uint8_t unk6C[8]; float f74; uint8_t unk78[0x200]; M1AiW190 *st278; } M1AiJ190;
typedef struct M1AiB190 { uint8_t unk00[0x30]; void *h30; } M1AiB190;
extern float m1_frameRate42C85C;
int  sub_000833E0(void *h);
void m1_AiGoto113040(M1AiB190 *a, M1AiJ190 *e, int st);

/* 0x143380: recover state: after 38 frames clear the stun bit; when the get-up anim ends, set a 30-frame grace timer and go to state 5. */
void m1_AiRecover143380(M1AiB190 *a, M1AiJ190 *e) {
    switch (e->i58) {
    case 0:
        if (e->f68 >= 38.0f / m1_frameTime42C858 * m1_frameRate42C85C) {
            e->st278->i4 &= ~1u;
            e->i58++;
        }
        break;
    case 1:
        if (sub_000833E0(a->h30)) {
            e->f74 = 30.0f / m1_frameTime42C858 * m1_frameRate42C85C;
            m1_AiGoto113040(a, e, 5);
        }
        break;
    }
}

typedef struct M1AiX190 { uint8_t unk00[8]; uint32_t i8; uint8_t unk0C[0x154]; float f160, f164, f168, f16C; } M1AiX190;
typedef struct M1AiK190 { uint8_t unk00[0x278]; M1AiX190 *st278; } M1AiK190;
typedef struct M1AiC190 { uint8_t unk00[0xC]; uint32_t iC; uint32_t i10; } M1AiC190;
int  aab_Rand(void);
int  m1_AiSetState1456E0(M1AiC190 *a, M1AiK190 *e, int s, int t);
void sub_0001D4E0(M1AiC190 *a);

/* 0x1373D0: enter a random taunt (anim 0x31 or 0x32), reset the sway vector and set the taunt flags. */
void m1_AiTaunt1373D0(M1AiC190 *a, M1AiK190 *e) {
    M1AiX190 *s = e->st278, *t; int r;
    if (aab_Rand() & 1) { int volatile v1 = 0x32; r = m1_AiSetState1456E0(a, e, v1, 0); }
    else { int volatile v2 = 0x31; r = m1_AiSetState1456E0(a, e, v2, 0); }
    if (r == 1) sub_0001D4E0(a);
    t = e->st278;
    t->f168 = 0.0f; t->f164 = 0.0f; t->f160 = 0.0f; t->f16C = 1.0f;
    a->iC &= ~0xE0u;
    a->i10 |= 5;
    s->i8 |= 6;
}
