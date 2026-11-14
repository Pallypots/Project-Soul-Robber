/* Area m1, file 201: costume effect helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Bn201 { uint8_t unk00[0xC4]; uint8_t *bonesC4; } M1Bn201;
typedef struct M1Tg201 { uint8_t unk00[0x20]; M1Bn201 *p20; } M1Tg201;
typedef struct M1Pc201 { uint8_t unk00[0xFD8]; M1Tg201 *tgtFD8; } M1Pc201;
typedef struct M1Fx201 { uint8_t unk00[0x14]; float s14, s18; uint8_t unk1C[0xC4]; } M1Fx201;
extern M1Fx201 g_ac0_41E2A0[32];
float b16_TabFloat74(M1Pc201 *p, int k);
int   b16_TabInt74(M1Pc201 *p, int k);
void  a3c_VecCopy(float *dst, const float *src);
int   m1_FxStart0C4C90(int id, float a, float s, int k, const float *v1, const float *v2, const float *v3);

/* 0xC5930: start the costume aura (effect 0x23) at the target's bone, sized from the costume table (x10, with a tenth of that as its second size). */
void m1_CostumeAura0C5930(M1Pc201 *p) {
    float v[4], w[4], s; int i;
    v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 1.0f;
    w[0] = 0.0f; w[1] = 0.0f; w[2] = 0.0f; w[3] = 1.0f;
    s = b16_TabFloat74(p, 1) * 10.0f;
    a3c_VecCopy(v, (float *)(p->tgtFD8->p20->bonesC4 + 0x1F0));
    v[3] = 1.0f;
    i = m1_FxStart0C4C90(0x23, 20.0f, 0.5f, b16_TabInt74(p, 1), v, w, w);
    if (i >= 0) {
        g_ac0_41E2A0[i].s18 = s * 0.1f;
        g_ac0_41E2A0[i].s14 = s;
    }
}

typedef struct M1Cs201 { uint8_t unk00[4]; int32_t kind4; int32_t sub8; uint8_t unk0C[4]; uint32_t f10; uint8_t unk14[0x6C]; float v80[4]; } M1Cs201;
typedef struct M1Tg2_201 { uint8_t unk00[0x60]; float pos60[4]; } M1Tg2_201;
typedef struct M1Pd201 { uint8_t unk00[0xEFC]; M1Cs201 *cosEFC; uint8_t unkF00[0xD8]; M1Tg2_201 *tgtFD8; } M1Pd201;
extern float m1_frameTime42C858;
void  r2d_ObjCompValue(M1Cs201 *c, void *out);
void  rbj_VecSub(float *dst, const float *a, const float *b);
int   sub_000EDF10(M1Cs201 *c);
float b16_ParamF4(int kind, int sub, int lvl);
float sub_00171AF0(M1Pd201 *p);
void  sub_001ADBA0(float *dst, const float *src, float s);
void  r4c_VecAdd(float *dst, const float *a, const float *b);

/* 0xC9D20: drift the costume anchor toward the target horizontally, at a rate set by how far the power exceeds the costume's need. */
void m1_CostumeDrift0C9D20(M1Pd201 *p) {
    uint8_t *k = 0; float v[4], need; M1Cs201 *c;
    v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 1.0f;
    c = p->cosEFC;
    if (c == 0 || (c->f10 & 0x400)) return;
    r2d_ObjCompValue(c, &k);
    rbj_VecSub(v, p->tgtFD8->pos60, (float *)(k + 0x70));
    v[1] = 0.0f;
    need = b16_ParamF4(c->kind4, c->sub8, sub_000EDF10(c));
    sub_001ADBA0(v, v, (sub_00171AF0(p) - need) * 9.99999975e-05f * m1_frameTime42C858);
    r4c_VecAdd(c->v80, c->v80, v);
}

typedef struct M1HbB201 { uint8_t unk00[0x60]; uint8_t pos60[0xD0]; int32_t i130; } M1HbB201;
typedef struct M1Hb201 { uint8_t unk00[0x6C]; int32_t mode6C; uint8_t unk70[0x1C]; M1HbB201 *body8C; uint8_t unk90[0x44]; float coolD4; } M1Hb201;
extern M1Hb201 *afc_helper;
int   sub_000F6A80(void);
int   sub_000F60C0(M1HbB201 *b, int k, float *out);
void *sub_00035DD0(M1HbB201 *b, int a, int c, int d);
void  sub_00033880(void *fx, float *out);
void  sub_00034DD0(void *fx, float *a, float *b, float *dir);
int   aab_Effect494D0(int id, void *pos, int arg);

/* 0xFC580: helper stomp: in modes 2..8, when a spot is found and the cooldown is over, spawn the stomp effect pointing up, play effect 0x14C and restart a 0.5 cooldown. */
void m1_HelperStomp0FC580(void) {
    float v[4], hit[4], pos[8], tmp[8]; M1Hb201 *h = afc_helper; M1HbB201 *b = h->body8C;
    int volatile m = h->mode6C; void *fx;
    if (sub_000F6A80()) return;
    if (m < 2 || m > 8) return;
    if (sub_000F60C0(b, m == 6, hit) == -1) return;
    if (!(0.0f >= h->coolD4)) return;
    v[0] = 0.0f; v[1] = 1.0f; v[2] = 0.0f; v[3] = 1.0f;
    fx = sub_00035DD0(b, b->i130, 0, 1);
    sub_00033880(fx, pos);
    sub_00034DD0(fx, hit, tmp, v);
    aab_Effect494D0(0x14C, b->pos60, 1);
    h->coolD4 = 0.5f;
}

typedef struct M1AiR201 { uint8_t unk00[4]; uint32_t i4; uint8_t unk08[0x14]; float v1C[4]; float f2C, f30, f34, f38; } M1AiR201;
typedef struct M1AiN201 { uint8_t unk00[0x5C]; float t5C; uint8_t unk60[0x218]; M1AiR201 *st278; } M1AiN201;
typedef struct M1AiO201 { uint8_t unk00[0x10]; uint32_t i10; uint8_t unk14[0x4C]; float pos60[4]; uint8_t unk70[0xB8]; uint8_t b128; } M1AiO201;
float sub_001B2770(const float *a, const float *b);
void  m1_LockMark0C56B0(void *o);
int   m1_AiSetState1456E0(void *a, void *e, int s, int t);
void  sub_0001D4E0(void *o);
void  m1_PlShot0C62A0(void *who);
void  sub_00025D50(int a, int b);
void  sub_00117580(void *o, int k);

/* 0x119690: chase-or-strike: while far (60+), early (under 3 units of time) and not ready, keep tracking; otherwise strike: anim 0x43, effect 0x77, the costume shot and the strike flags. */
void m1_AiStrike119690(M1AiO201 *o, M1AiN201 *e) {
    M1AiR201 *s = e->st278, *t; float d;
    d = sub_001B2770(o->pos60, s->v1C);
    if (!(o->b128 & 0x1E) && !(e->t5C >= 3.0f) && !(d >= 60.0f) && !((short)s->i4 < 0)) {
        m1_LockMark0C56B0(o);
        return;
    }
    if (m1_AiSetState1456E0(o, e, 0x43, 0) == 1) sub_0001D4E0(o);
    t = e->st278;
    t->f34 = 0.0f; t->f30 = 0.0f; t->f2C = 0.0f; t->f38 = 1.0f;
    aab_Effect494D0(0x77, o->pos60, 0);
    m1_PlShot0C62A0(o);
    sub_00025D50(1, 1);
    if (s->i4 & 0x10) o->i10 |= 0xD;
    sub_00117580(o, 0x1F);
}
