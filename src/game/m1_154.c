/* Area m1, file 154: grab-enemy setup and release. Names inferred. */
#include <stdint.h>

typedef struct M1Ob154 { uint8_t unk00[0xC]; uint32_t fC; uint32_t f10; uint8_t unk14[0x1C]; void *anim30; uint8_t unk34[0x3C]; float v70[4]; uint8_t unk80[0x13C - 0x80]; int32_t x13C; } M1Ob154;
typedef struct M1Gr154 { M1Ob154 *p0; int32_t p4; } M1Gr154;
typedef struct M1Rg154 { uint32_t f0; float f4; float f8; uint8_t unk0C[0x34]; uint32_t f40; } M1Rg154;
typedef struct M1Ai154 {
    uint8_t unk00[0x4C]; uint32_t flags4C; uint8_t unk50[8]; int32_t n58; uint8_t unk5C[0x10]; int32_t snd6C; void *fx70;
    uint8_t unk74[0x278 - 0x74]; void *rig278; void *fn27C; void *fn280; void *fn284; void *fn288;
    const void *t28C; const void *t290; const void *t294; void *fn298; void *fn29C;
} M1Ai154;
extern M1Gr154 m1_grabs3FE3A4[1];
extern const uint8_t m1_aiTblA32BCA8[], m1_aiTblB32BCB8[], m1_aiTblC32BCC8[];
void m1_GrabUpd184120(void); void m1_GrabHit184260(void); void m1_GrabDraw184160(void); void m1_GrabKill184240(void);
void m1_StubAD090(void); void m1_Stub102FA0(void);
void m1_AiReset1134B0(M1Ai154 *e);
void m1_AiGoto113040(M1Ob154 *o, M1Ai154 *e, int st);

/* 0x184390: set up the grab enemy (one slot), its callbacks and tables, then start state 3. */
int m1_GrabInit184390(M1Ob154 *o, M1Ai154 *e, int bad) {
    int i; M1Gr154 *g;
    for (i = 0; i < 1; i++)
        if (m1_grabs3FE3A4[i].p0 == 0) break;
    if (i >= 1) return 0;
    g = &m1_grabs3FE3A4[i];
    *(volatile M1Ob154 **)&g->p0 = 0;
    g->p4 = 0;
    g->p0 = o;
    e->rig278 = g;
    e->t28C = m1_aiTblA32BCA8; e->t290 = m1_aiTblB32BCB8; e->t294 = m1_aiTblC32BCC8;
    e->fn27C = (void *)m1_GrabUpd184120; e->fn29C = (void *)m1_StubAD090;
    e->fn280 = (void *)m1_GrabHit184260; e->fn284 = (void *)m1_Stub102FA0;
    e->fn288 = (void *)m1_GrabDraw184160; e->fn298 = (void *)m1_GrabKill184240;
    o->f10 |= 5; o->fC &= ~0xE0u;
    o->v70[2] = 1.0f; o->v70[1] = 1.0f; o->v70[0] = 1.0f; o->v70[3] = 1.0f;
    if (bad) for (;;) ;
    m1_AiReset1134B0(e);
    m1_AiGoto113040(o, e, 3);
    return 1;
}

extern float m1_frameRate42C85C;
int  sub_000833E0(void *a);
void sub_00113AA0(M1Ob154 *o, M1Ai154 *e);
void m1_SndStop048250(int h);
void m1_ObjSnd05BE30(int h);
void sub_00033A70(void *p);

/* 0x162640: finish the grab: restore the object's flags, drop any carried thing, go to state 0x1A. */
void m1_GrabEnd162640(M1Ob154 *o, M1Ai154 *e) {
    M1Rg154 *r; uint32_t f;
    if (e->n58 != 0x14) for (;;) ;
    if (sub_000833E0(o->anim30) == 0) return;
    r = (M1Rg154 *)e->rig278;
    m1_AiReset1134B0(e);
    o->fC |= 0xE0;
    o->f10 &= 0xFFFFFECA;
    e->flags4C &= ~0x100u;
    f = r->f40 & 0xFFFBF579;
    r->f40 = f;
    r->f0 &= 0xFFFFFFE8;
    r->f4 = -10.0f;
    r->f8 = m1_frameRate42C85C * 10.0f;
    if (f & 0x4000) {
        sub_00113AA0(o, e);
        e->flags4C |= 0x200;
        r->f40 &= ~0x4000u;
    }
    if (e->snd6C != -1) { m1_SndStop048250(e->snd6C); e->snd6C = -1; }
    m1_ObjSnd05BE30(o->x13C);
    if (e->fx70 != 0) { sub_00033A70(e->fx70); e->fx70 = 0; }
    m1_AiGoto113040(o, e, 0x1A);
}

typedef struct M1Ob154b { uint8_t unk00[0x60]; float pos60[4]; } M1Ob154b;
typedef struct M1Ai154b { uint8_t unk00[0x278]; uint8_t b278; } M1Ai154b;
extern int32_t m1_worldA41316C;
extern int32_t m1_worldB413170;
void m1_ObjDie035D80(M1Ob154b *o, int a, int b);
void sub_00049700(int id, int r, int g, int b, float *pos, int k, float size, int z);
int  sub_000C46A0(float a, float b, float c, float *pos, float *v1, float *v2);
void sub_000C4D30(M1Ob154b *o, int kind, float t, int fx);
int  m1_FxAdd0C4DF0(void *unused, int kind, float c0, int arg, float c2, float c3, float c1, void *src, const float *v1, const float *v2);
void sub_000ED780(M1Ob154b *o);

/* 0x178B00: break an object: debris sound, sparkle (homing or plain), then remove it. */
void m1_ObjBreak178B00(M1Ob154b *o, M1Ai154b *e) {
    float v[4]; int id;
    v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 0.0f;
    m1_ObjDie035D80(o, 0, 1);
    id = (m1_worldA41316C == 4 && m1_worldB413170 == 6) ? 0x24B : 0x20E;
    sub_00049700(id, 0x80, 0x80, 0x80, o->pos60, 1, 150.0f, 0);
    if (e->b278 & 1) {
        sub_000C4D30(o, 0xB, 10.0f, sub_000C46A0(12.5f, 0.0166666675f, 2.5f, o->pos60, v, v));
        sub_000ED780(o);
        return;
    }
    m1_FxAdd0C4DF0(o, 0, 10.0f, 0, 12.5f, 1.0f, 2.5f, o->pos60, v, v);
    sub_000ED780(o);
}

typedef struct M1Rg154c { uint8_t unk00[0xC]; float fC; float f10; uint8_t unk14[0x10]; float f24; float f28; float f2C; float f30; uint8_t unk34[0xC]; uint32_t f40; uint8_t unk44[0xC]; float f50; } M1Rg154c;
typedef struct M1Ob154c { uint8_t unk00[0x10]; uint32_t f10; } M1Ob154c;
typedef struct M1Ai154c { uint8_t unk00[0x4C]; uint32_t flags4C; uint8_t unk50[0x278 - 0x50]; M1Rg154c *rig278; } M1Ai154c;
typedef struct M1St154c { int32_t s0; uint8_t unk04[0xC]; float t10; float t14; float t18; float t1C; } M1St154c;
extern float m1_frameTime42C858;
void m1_AiSetState1456E0(M1Ob154c *o, M1Ai154c *e, int a, int b);
M1St154c *m1_Quest113400(M1Ai154c *e, int k);

/* 0x156B10: launch the enemy into a high jump with a spin. */
void m1_AiJump156B10(M1Ob154c *o, M1Ai154c *e) {
    M1Rg154c *r = e->rig278; M1St154c *s; float t; volatile float k = 2.0f; float kk;
    m1_AiSetState1456E0(o, e, 2, 0);
    kk = k;
    r->f28 = 0.0f; r->f24 = 0.0f; r->f10 = 0.0f;
    r->f50 = 300.0f;
    r->fC = m1_frameTime42C858 * 0.00499999989f;
    r->f2C = 0.0f - m1_frameRate42C85C * 35.0f * kk;
    r->f30 = 1.0f;
    o->f10 |= 0x20;
    e->flags4C |= 0x70;
    r->f40 |= 0x200;
    t = m1_frameTime42C858 * 0.0349065848f * kk;
    s = m1_Quest113400(e, 1);
    s->t10 = 0.174532935f;
    s->t14 = -0.174532935f;
    if (t != -1.0f) s->t18 = t;
    s->t1C = 0.0f;
}
