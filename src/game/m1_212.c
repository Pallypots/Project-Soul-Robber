/* Area m1, file 212: fuse bomb helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Fb212 { uint8_t unk00[0xC]; uint32_t iC; uint8_t unk10[0x40]; float spin50; uint8_t unk54[0xD4]; uint8_t b128; } M1Fb212;
typedef struct M1FbE212 { uint8_t unk00[0x7C]; float fall7C; } M1FbE212;
extern float m1_frameTime42C858;
int  sub_000CFFB0(void);
void m1_FusePulse1789E0(void *o, void *e);
void sub_001788D0(void *e);

/* 0x178D50: lit fuse bomb tick: mirror the lock-on state into flag 0x20, accelerate its fall, spin it (fast when held), then run the fuse pulse and the fall step. */
void m1_FuseBombTick178D50(M1Fb212 *o, M1FbE212 *e) {
    float d;
    if (sub_000CFFB0() == -1) o->iC &= ~0x20u; else o->iC |= 0x20;
    e->fall7C += m1_frameTime42C858 * 0.0199999996f * m1_frameTime42C858;
    if (o->b128 & 0x18) {
        e->fall7C = 0.0f;
        d = m1_frameTime42C858 * 0.174532935f;
    } else d = m1_frameTime42C858 * 0.0349065848f;
    o->spin50 += d;
    m1_FusePulse1789E0(o, e);
    sub_001788D0(e);
}

typedef struct M1Wa212 { uint8_t unk00[0x10]; uint32_t i10; uint8_t unk14[0x4C]; float pos60[4]; } M1Wa212;
typedef struct M1WaE212 { uint8_t unk00[0x50]; int32_t st50; } M1WaE212;
extern M1Wa212 *g_playerObj;
int   sub_0004ECE0(int k);
void  sub_00178470(void);
int   Stats_HasEFC(void);
float sub_001B2770(const float *a, const float *b);
int   a80_Get3ED238(void);
void  m1_AiGoto113040(void *a, void *e, int st);

/* 0x1786F0: idle watcher tick: react to the button flag, mirror the stats flag into bit 0, and go to state 4 when forced or once the player is over 200 away or 100+ above or below. */
void m1_WatchIdle1786F0(M1Wa212 *o, M1WaE212 *e) {
    float d, dy; M1Wa212 *pl;
    if (sub_0004ECE0(1) & 0x20) sub_00178470();
    if (Stats_HasEFC() > 0) o->i10 |= 1; else o->i10 &= ~1u;
    pl = g_playerObj;
    d = sub_001B2770(o->pos60, pl->pos60);
    dy = o->pos60[1] - pl->pos60[1];
    if (e->st50 == 4) return;
    if (a80_Get3ED238() || d > 200.0f || -100.0f > dy || dy > 100.0f) m1_AiGoto113040(o, e, 4);
}

typedef struct M1DbE212 { uint8_t unk00[0x74]; float t74; } M1DbE212;
extern float m1_frameRate42C85C;
void   sub_000ED780(void *o);
void   r1e_PartValues(int *n, int k, void *o);
float *sub_0001D0F0(void *o, int part);
void   a3c_VecCopy(float *dst, const float *src);
void   m1_MatMul1AD7C0(float *dst, const float *a, const float *b);
void   r4c_VecAdd(float *dst, const float *a, const float *b);

/* 0x185C90: debris tick: when the timer runs out remove the object; otherwise move each part (except the root) by its velocity, damp the horizontal velocity by 5% per frame and pull it down by gravity. */
void m1_DebrisTick185C90(void *o, M1DbE212 *e) {
    float v[4]; float *b; int i, n;
    if (0.0f >= e->t74) { sub_000ED780(o); return; }
    r1e_PartValues(&n, 0, o);
    for (i = 1; i < n; i++) {
        b = sub_0001D0F0(o, i);
        a3c_VecCopy(v, b + 28);
        m1_MatMul1AD7C0(b + 16, b + 16, b);
        r4c_VecAdd(b + 28, v, b + 12);
        b[31] = 1.0f;
        b[12] = (1.0f - m1_frameTime42C858 * 0.0500000007f) * b[12];
        b[13] += m1_frameRate42C85C * m1_frameRate42C85C * 294.0f;
        b[14] = (1.0f - m1_frameTime42C858 * 0.0500000007f) * b[14];
    }
}
