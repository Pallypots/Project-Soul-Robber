/* Area m1, file 195: visibility helpers. Names inferred. */
#include <stdint.h>
#include <math.h>
#pragma intrinsic(fabs)

void a3c_VecCopy(float *dst, const float *src);
void rbj_VecTransform(float *dst, const float *m, const float *v);

/* 0x82E50: box cull: transform the eight corners by m; returns 0 as soon as one lands inside the clip cube (|x|,|y|,|z| <= |w|), 1 when all are outside. */
int m1_BoxCulled082E50(const float *corners, const float *m) {
    float aw, o[4], v[4]; double a; int i;
    for (i = 0; i < 8; i++, corners += 4) {
        a3c_VecCopy(v, corners);
        v[3] = 1.0f;
        rbj_VecTransform(o, m, v);
        a = fabs(o[3]);
        aw = (float)a;
        if (o[0] > a) continue;
        if (0.0f - aw > o[0] || o[1] > aw || 0.0f - aw > o[1] || o[2] > aw || 0.0f - aw > o[2]) continue;
        return 0;
    }
    return 1;
}

typedef struct M1Shot195 { uint32_t flags0; int32_t kind4; int32_t id8; uint8_t unk0C[0xD4]; } M1Shot195;
extern uint8_t abc_player[];
extern int32_t m1_costume420C2C;
void m1_FxInit0C4B70(M1Shot195 *r);
int  m1_FxShotA0C5D20(void *pl, void *who, M1Shot195 *r, float *a, float *b);
void sub_000A95E0(void *who, float *v, int id);

/* 0xC62A0: fire the player's costume shot at who: effect 0xE/0x13/0x1A by costume; on a hit, play the hit reaction. */
void m1_PlShot0C62A0(void *who) {
    float v[4]; int32_t t[3]; M1Shot195 r; int k;
    v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 1.0f;
    t[0] = 0xE; t[1] = 0x13; t[2] = 0x1A;
    m1_FxInit0C4B70(&r);
    k = t[m1_costume420C2C];
    r.kind4 = 0xC; r.id8 = k;
    if (m1_FxShotA0C5D20(abc_player, who, &r, v, v) > 0) sub_000A95E0(who, v, k);
}

typedef struct M1Lt195 { uint8_t unk00[0x794]; float rad794, rad798, x79C, y7A0, r7A4, g7A8, b7AC, a7B0; } M1Lt195;
typedef struct M1LtS195 { uint8_t unk00[0xC]; int16_t xC, yE; uint8_t r10, g11, b12, unk13; int32_t rad14; } M1LtS195;

/* 0xEAC10: load a light's parameters from its packed record: radius (scaled), position and colour, alpha 1. */
void m1_LightLoad0EAC10(M1Lt195 *l, M1LtS195 *s) {
    if (l == 0 || s == 0) return;
    l->rad794 = (float)s->rad14 * 0.001f;
    l->rad798 = (float)s->rad14 * 0.001f;
    l->x79C = (float)s->xC;
    l->y7A0 = (float)s->yE;
    l->r7A4 = (float)s->r10;
    l->g7A8 = (float)s->g11;
    l->b7AC = (float)s->b12;
    l->a7B0 = 1.0f;
}

typedef struct M1MnP195 { uint8_t unk00[0x30]; void *h30; } M1MnP195;
typedef struct M1Mn195 { uint8_t unk00[0x8C]; M1MnP195 *p8C; M1MnP195 *p90; int32_t unk94[2]; int32_t i9C; uint8_t unkA0[0xD8]; float f178; uint8_t unk17C[0xC]; float f188; uint8_t unk18C[0xC]; int32_t i198; } M1Mn195;
typedef struct M1MnO195 { uint8_t unk00[0x64]; int32_t i64; } M1MnO195;
extern M1Mn195 *m1_minion3F6120;
extern float m1_fps42C964;
void aab_SetAnim832D0(void *h, int anim);

/* 0xFF240: send the minion after o: both halves play anim 0x25, remember o's id and start a half-turn per second (hangs if the minion is missing). */
void m1_MinionChase0FF240(M1MnO195 *o) {
    M1Mn195 *m = m1_minion3F6120;
    if (m == 0) for (;;) ;
    if (m->p8C == 0) for (;;) ;
    aab_SetAnim832D0(m->p8C->h30, 0x25);
    aab_SetAnim832D0(m1_minion3F6120->p90->h30, 0x25);
    m->i198 = o->i64;
    m->f178 = 0.0f - 180.0f / m1_fps42C964;
    m->f188 = 0.0f;
    m->i9C = 0;
}

typedef struct M1Hp195 { uint8_t unk00[0x8C]; M1MnP195 *p8C; M1MnP195 *p90; int32_t unk94[2]; int32_t i9C; float fA0; uint8_t unkA4[0x15C]; float f200; int16_t w204; } M1Hp195;
typedef struct M1HpO195 { uint8_t unk00[0x60]; float pos60[4]; } M1HpO195;
extern M1Hp195 *m1_helper3F6114;
extern uint8_t *g_playerObj;
float sub_001B2770(const float *a, const void *b);

/* 0xFBF90: send the helper toward o: both halves play anim 0x23; travel distance is the gap to the player minus 20 (at least 20). */
void m1_HelperGo0FBF90(M1HpO195 *o) {
    M1Hp195 *h = m1_helper3F6114; float d, v;
    if (h == 0) for (;;) ;
    if (h->p8C == 0) for (;;) ;
    aab_SetAnim832D0(h->p8C->h30, 0x23);
    aab_SetAnim832D0(m1_helper3F6114->p90->h30, 0x23);
    d = sub_001B2770(o->pos60, g_playerObj + 0x60);
    if (40.0f >= d) v = 20.0f;
    else v = d - 20.0f;
    h->f200 = v;
    h->w204 = 1;
    h->i9C = 0;
    h->fA0 = 0.0f;
}

typedef struct M1Cs195 { uint8_t unk00[8]; int32_t kind8; uint8_t unk0C[0x54]; uint8_t pos60[0x10]; } M1Cs195;
int  aab_Effect494D0(int id, void *pos, int arg);
void aab_Attach36750(void *o, int k);

/* 0xF6F60: costume change flash: play effect 0x3B2 and attach in the costume's mode (alt or normal); unknown kinds pass the object pointer through, as the original does. */
void m1_CostumeFlash0F6F60(M1Cs195 *o, int alt) {
    int a, b;
    if (o == 0) for (;;) ;
    if (o->kind8 == 3) { a = o->kind8; b = 4; }
    else if (o->kind8 == 4) { a = 2; b = 3; }
    else if (o->kind8 == 5) { a = 3; b = 4; }
    else { a = (int)(intptr_t)o; b = (int)(intptr_t)o; }
    aab_Effect494D0(0x3B2, o->pos60, 0);
    if (alt) { int volatile v1 = a; aab_Attach36750(o, v1); }
    else { int volatile v2 = b; aab_Attach36750(o, v2); }
}

typedef struct M1Fl195 { uint32_t flags0; uint8_t unk04[0x3C]; int32_t st40; uint8_t unk44[0x2C]; float pos70[4]; uint8_t unk80[0x30]; float goalB0[4]; uint8_t unkC0[0x40]; int32_t i100; } M1Fl195;
void  sub_000A30F0(M1Fl195 *o, float *goal, int k);
void  rbj_VecSub(float *dst, const float *a, const float *b);
float sub_00082D70(const float *v);
void  sub_000A41D0(void *o, int k);

/* 0x92650: flying pickup: home toward its goal and snap onto it when within 1 unit (state 0xA); in state 0xA despawn. */
void m1_FlyPickup092650(M1Fl195 *o) {
    float v[4];
    v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 1.0f;
    if (o->st40 != 0) {
        if (o->st40 == 0xA) {
            sub_000A41D0(o, -1);
            o->flags0 &= ~0x10u;
        }
        return;
    }
    sub_000A30F0(o, o->goalB0, o->i100);
    rbj_VecSub(v, o->goalB0, o->pos70);
    if (1.0f > sub_00082D70(v)) {
        a3c_VecCopy(o->pos70, o->goalB0);
        o->st40 = 0xA;
    }
}
