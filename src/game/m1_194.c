/* Area m1, file 194: player state helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Ps194 {
    uint8_t unk00[0xE0]; int32_t stE0; uint8_t unkE4[0x28]; float f10C; uint8_t unk110[8]; float f118; uint8_t unk11C[0x10];
    int32_t mode12C; uint8_t unk130[0x20]; uint32_t flags150;
} M1Ps194;
int PlayerObj_IsActive(M1Ps194 *p);

/* 0xC1710: landing state: on entry set the land values and test the ground; on ground go to state 8 (mode 0x304), otherwise advance; in state 8 reset when airborne again. */
void m1_PlLand0C1710(M1Ps194 *p) {
    if (p->stE0 == 0) {
        p->f10C = 10.0f;
        p->flags150 &= 0x83FFF4FE;
        p->mode12C = 3;
        p->f118 = 0.2f;
        if (PlayerObj_IsActive(p) > 0) { p->mode12C = 0x304; p->stE0 = 8; return; }
        p->stE0++;
        return;
    }
    if (p->stE0 == 8 && PlayerObj_IsActive(p) < 0) p->stE0 = 0;
}

typedef struct M1Xf194 {
    uint32_t flags0; float f4, f8, fC; int32_t i10; float a14[4]; float b24[4]; float f34; uint8_t unk38[0xB0]; int32_t iE8;
} M1Xf194;
extern M1Xf194 m1_slots41D020[20];
int  sub_000C73B0(void);
void a3c_VecCopy(float *dst, const float *src);

/* 0xC7540: allocate a transform slot and fill it: two parameters, identity-like vectors overwritten by the given position and direction; returns the slot or -1. */
int m1_XfAlloc0C7540(float a, float b, const float *pos, const float *dir) {
    int i = sub_000C73B0(); M1Xf194 *r;
    if (i < 0) return -1;
    r = &m1_slots41D020[i];
    r->fC = 0.0f; r->a14[2] = 0.0f; r->a14[1] = 0.0f; r->b24[2] = 0.0f; r->b24[1] = 0.0f;
    r->a14[0] = 0.0f; r->b24[0] = 0.0f;
    r->b24[3] = 1.0f; r->a14[3] = 1.0f;
    r->f4 = a; r->i10 = 0; r->iE8 = 0; r->flags0 = 0x80000000; r->f8 = b;
    a3c_VecCopy(r->a14, pos);
    a3c_VecCopy(r->b24, dir);
    return i;
}

typedef struct M1Fx194 { uint32_t flags0; int32_t id4; int32_t k8; float aC, s10, s14; uint8_t unk18[0xC]; float v24[4]; float v34[4]; float v44[4]; uint8_t unk54[0x8C]; } M1Fx194;
extern M1Fx194 g_ac0_41E2A0[32];
void m1_FxInit0C4B70(M1Fx194 *f);

static __inline int m1_FxFree194(void) {
    M1Fx194 *p; int i;
    for (i = 0, p = g_ac0_41E2A0; (int32_t)p < (int32_t)&g_ac0_41E2A0[32]; p++, i++)
        if (!(p->flags0 & 1)) return i;
    return -1;
}

/* 0xC4C90: start an effect in the first free slot: id, timing and scale, plus three vectors; returns the slot or -1. */
int m1_FxStart0C4C90(int id, float a, float s, int k, const float *v1, const float *v2, const float *v3) {
    int i = m1_FxFree194(); M1Fx194 *f;
    if (i < 0) return -1;
    f = &g_ac0_41E2A0[i];
    m1_FxInit0C4B70(f);
    f->flags0 |= 1;
    f->id4 = id; f->aC = a; f->s10 = s; f->s14 = s; f->k8 = k;
    a3c_VecCopy(f->v24, v1);
    a3c_VecCopy(f->v34, v2);
    a3c_VecCopy(f->v44, v3);
    return i;
}

typedef struct M1Pw194 { uint8_t unk00[0xFAC]; float powFAC; uint8_t unkFB0[0x10]; float colFC0[4]; } M1Pw194;
typedef struct M1Scn194 { uint8_t unk00[0x3B0]; void *model3B0; } M1Scn194;
extern M1Scn194 *m1_scene2_42C8EC;
extern float m1_col418B30[3];
float sub_00171B40(M1Pw194 *p);
void  m1_PowerGlow0C9E30(M1Pw194 *p);
void  r2b_ModelSetColor(void *m, const float *c);

/* 0xCAE20: add to the player's power (clamped to 0..max), refresh the glow colour and copy it to the shared colour. */
void m1_PowerAdd0CAE20(M1Pw194 *p, float d) {
    void *m;
    p->powFAC += d;
    if (p->powFAC > sub_00171B40(p)) p->powFAC = sub_00171B40(p);
    if (0.0f > p->powFAC) p->powFAC = 0.0f;
    m = m1_scene2_42C8EC->model3B0;
    m1_PowerGlow0C9E30(p);
    r2b_ModelSetColor(m, p->colFC0);
    m1_col418B30[0] = p->colFC0[0];
    m1_col418B30[1] = p->colFC0[1];
    m1_col418B30[2] = p->colFC0[2];
}

typedef struct M1StE194 { uint8_t unk00[0xEC]; int32_t iEC; float velF0[4]; uint8_t unk100[0xC]; int32_t i10C; int32_t i110, i114; } M1StE194;
extern float m1_frameRate42C85C;
void sub_000A34B0(int a, int b, int c);

/* 0xF2110: stop the player: play the stop cue once (when a target is set), zero the velocity and clear the move pair. */
void m1_PlStop0F2110(void *o, M1StE194 *e) {
    int32_t *z;
    if (e->i10C >= 0 && e->iEC == 0) { sub_000A34B0(0, 9, 0); e->iEC = 1; }
    e->velF0[0] = m1_frameRate42C85C * 0.0f;
    e->velF0[1] = m1_frameRate42C85C * 0.0f;
    e->velF0[2] = m1_frameRate42C85C * 0.0f;
    e->velF0[3] = m1_frameRate42C85C * 0.0f;
    { int32_t *volatile zv = &e->i110; z = zv; }
    z[0] = 0; z[1] = 0;
}

typedef struct M1Cp194 { uint8_t unk00[0xD4]; void *chainD4; int32_t sndD8; } M1Cp194;
typedef struct M1AtE194 { uint8_t unk00[0x70]; int32_t anim70; uint8_t unk74[0x8C]; int32_t i100; int32_t i104; } M1AtE194;
M1Cp194 *rbi_Comp1D960(void *o, int comp);
void r1c_NodeFreeChain(void *c);
void aab_Release48250(int h);
void sub_000F3D10(void *o, M1Cp194 *c, int k);

/* 0xEFBE0: end the player's attack: drop the trail chain (unless in a special anim 0x1B..0x1D/0x1F), stop its sound, and restore the stance when flagged. */
void m1_PlAttackEnd0EFBE0(void *o, M1AtE194 *e) {
    M1Cp194 *c; int volatile a = e->anim70;
    if (!(a >= 0x1B && (a <= 0x1D || a == 0x1F))) {
        c = rbi_Comp1D960(o, 5);
        if (c->chainD4) { r1c_NodeFreeChain(c->chainD4); c->chainD4 = 0; }
    }
    e->i100 = 0;
    c = rbi_Comp1D960(o, 5);
    if (c->sndD8 >= 0) { aab_Release48250(c->sndD8); c->sndD8 = -1; }
    if (e->i104) {
        if (o == 0) for (;;) ;
        sub_000F3D10(o, rbi_Comp1D960(o, 5), 0x12);
    }
}
