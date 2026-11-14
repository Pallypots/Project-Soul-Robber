/* Area m1, file 188: save data defaults. Names inferred. */
#include <stdint.h>
#include <string.h>
#include <intrin.h>
#pragma intrinsic(strcpy, memcpy)

typedef struct { int32_t w[16]; } M1B40_188;
typedef struct { int32_t w[12]; } M1B30_188;
typedef struct { int32_t w[4]; } M1B10_188;
typedef struct { char c[0x3B]; } M1B3B_188;
typedef struct { char c[5]; } M1B5_188;
extern uint8_t *m1_save3E3934;
extern const M1B5_188 m1_saveMagic26C248;
extern const M1B40_188 m1_saveDefA2DCED8;
extern const M1B30_188 m1_saveDefB2DCF18;
extern const M1B30_188 m1_saveDefC2DCF48;
extern const M1B10_188 m1_saveDefD2DCF78;
extern const M1B3B_188 m1_saveDefE26C20C;
extern const char *m1_saveName2DCDD8;

/* 0x54FE0: reset the save block to defaults: clear it, write the magic and version fields, copy the default tables and the three default names. */
void m1_SaveDefaults054FE0(void) {
    uint8_t *b; M1B10_188 *d;
    { uint8_t *volatile bv = m1_save3E3934 + 0x122D50; b = bv; }
    __stosd((unsigned long *)b, 0, 0xF1);
    *(M1B5_188 *)b = m1_saveMagic26C248;
    *(int16_t *)(m1_save3E3934 + 0x122D54) = 0;
    *(int16_t *)(m1_save3E3934 + 0x122D56) = 0x1A;
    *(int32_t *)(m1_save3E3934 + 0x122D58) = 0;
    *(int32_t *)(m1_save3E3934 + 0x122D5C) = 0x60;
    *(M1B40_188 *)(m1_save3E3934 + 0x122D60) = m1_saveDefA2DCED8;
    *(M1B30_188 *)(m1_save3E3934 + 0x122DA0) = m1_saveDefB2DCF18;
    *(M1B30_188 *)(m1_save3E3934 + 0x122DD0) = m1_saveDefC2DCF48;
    { M1B10_188 *volatile dv = (M1B10_188 *)(m1_save3E3934 + 0x122E00); d = dv; }
    *d = m1_saveDefD2DCF78;
    *(M1B3B_188 *)(m1_save3E3934 + 0x122E10) = m1_saveDefE26C20C;
    strcpy((char *)m1_save3E3934 + 0x122E54, m1_saveName2DCDD8);
    strcpy((char *)m1_save3E3934 + 0x122E94, m1_saveName2DCDD8);
    strcpy((char *)m1_save3E3934 + 0x122ED4, m1_saveName2DCDD8);
}

typedef struct M1Fx188 { uint32_t flags0; uint8_t unk04[0xC]; void *chain10; uint32_t f14; int32_t id18; uint8_t unk1C[4]; uint8_t emit20[4]; } M1Fx188;
typedef struct M1Nd188 { struct M1Nd188 *next0; uint8_t unk04[0xC]; int32_t id10; uint8_t e14[0xC]; int32_t v20; uint8_t unk24[0x40]; int32_t v64; } M1Nd188;
typedef struct M1Own188 { int32_t unk0; M1Nd188 *first4; } M1Own188;
extern uint8_t *r1c_bank283698;
void *r1c_PoolTake(void *pool, int size);
void  m1_FxReset33710(M1Fx188 *fx);
void  a5b_PairSet(M1Fx188 *fx, void *e);
void  r1c_PoolForEach(void *pool, int size, void *fn, void *arg);
int   sub_00034270(void);
M1Fx188 *r1c_BankFind(int id);
M1Fx188 *r1d_NodeFindId(int id, M1Fx188 *after);
void  r4b_EmitSetReleaseAll(void *e);
void  r4_EmitSetFlag8(void *e);
void  r1c_NodeFreeChain(void *c);
void  sub_00033560(M1Fx188 *fx);

/* 0x35A10: start (on != 0) or stop every effect with the given id on an owner: start spawns a pooled effect per matching node; stop releases all live ones. */
void m1_FxById035A10(M1Own188 *o, int id, int on) {
    M1Nd188 *n; M1Fx188 *fx, *nx; uint8_t *p;
    if (o == 0) return;
    if (on) {
        for (n = o->first4; n != 0; n = n->next0) {
            if (n->id10 != id) continue;
            p = r1c_PoolTake(r1c_bank283698 + 0x55140, 0x6C);
            if (p == 0) continue;
            fx = (M1Fx188 *)(p + 0x10);
            m1_FxReset33710(fx);
            if (fx == 0) continue;
            *(int32_t *)(n->e14 + 0xC) = n->v64;
            a5b_PairSet(fx, n->e14);
            fx->flags0 |= 1; fx->f14 |= 2; fx->id18 = n->id10;
        }
        return;
    }
    r1c_PoolForEach(r1c_bank283698 + 0x55140, 0x6C, (void *)sub_00034270, &id);
    for (fx = r1c_BankFind(id); fx != 0; fx = nx) {
        nx = r1d_NodeFindId(id, fx);
        if (fx != 0) {
            if (fx->flags0 == 0) { r4b_EmitSetReleaseAll(fx->emit20); r4_EmitSetFlag8(fx->emit20); }
            if (fx->chain10) r1c_NodeFreeChain(fx->chain10);
            sub_00033560(fx);
        }
    }
}

typedef struct M1Rot188 {
    uint8_t unk00[0xC]; uint32_t flagsC; uint8_t unk10[0x10]; float *mtx20; uint8_t unk24[0x2C];
    float f50, ang54, f58, f5C; uint8_t unk60[0x10]; float scale70[3];
} M1Rot188;
void a3c_VecCopy(float *dst, const float *src);
void r4e_MatIdentity(float *m);
void rbj_MatRotY(float *dst, const float *src, float a);
void r4f_MatCopy1ADA40(float *dst, const float *src);
void m1_MatMul1AD7C0(float *dst, const float *a, const float *b);

/* 0x1F100: set an object's yaw: rebuild its matrix as a Y rotation keeping its position, then optionally apply its stored scale (position kept). */
void m1_SetYaw01F100(M1Rot188 *o, float ang, int scale) {
    float v[4]; float m[16];
    if (o == 0) return;
    o->f5C = 0.0f; o->f58 = 0.0f; o->f50 = 0.0f; o->ang54 = ang;
    if (!(o->flagsC & 0x100)) return;
    r4e_MatIdentity(m);
    rbj_MatRotY(m, m, ang);
    a3c_VecCopy(&m[12], o->mtx20 + 12);
    r4f_MatCopy1ADA40(o->mtx20, m);
    if (!scale) return;
    v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 1.0f;
    a3c_VecCopy(v, o->mtx20 + 12);
    r4e_MatIdentity(m);
    m[0] = o->scale70[0]; m[5] = o->scale70[1]; m[10] = o->scale70[2];
    m1_MatMul1AD7C0(o->mtx20, m, o->mtx20);
    a3c_VecCopy(o->mtx20 + 12, v);
}
