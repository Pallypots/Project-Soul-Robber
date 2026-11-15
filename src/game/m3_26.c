/* Area m3, file 26: pending entity spawns and loops with signed pointer bounds. Names inferred. */
#include <stdint.h>

typedef struct M3EU26 { uint8_t unk00[4]; int32_t kind4; int32_t type8; uint32_t fC; uint8_t unk10[0x50]; float pos60[4]; uint8_t unk70[0xDC]; int32_t list14C; } M3EU26;
typedef struct M3EE26 { uint32_t f0; int32_t a4; int32_t b8; uint8_t unk0C[0x28]; float pos34[4]; uint8_t unk44[0x20]; M3EU26 *unit64; } M3EE26;
typedef struct M3ER26 { uint8_t unk00[4]; int32_t kind4, type8; } M3ER26;
extern M3EE26 m1_ents41CEC0[];
extern uint8_t *m1_rbBData41D008;
extern uint8_t *m1_rbAData41CEBC;
extern void *m1_scene42C8E4;
void sub_00022380(void *o, void *res, void *ctx);
void r1i_UnitsAttach(void *ctx, void *o, int a, int b, int c);
void sub_0001EBF0(void *o, int a);
void sub_0001D4B0(void *o, int a);
M3ER26 *a12_List_FindId(void *o, int id);
void a3c_VecCopy(float *dst, const float *src);

/* 0xC6980: spawn pending entities (sign bit set): take the first free of 3 units, pick the resource by (group 0..3, variant 0..2), attach and enable the unit as kind 13 with type group*3+variant, mark the entity live, place and reset the unit, and copy its kind to its first list record unless it is group 3. */
#pragma optimize("s", on)
void m3_SpawnEntsC6980(void) {
    void *ctx = m1_scene42C8E4; M3EE26 *p; M3EU26 *q; uint8_t *m; int i;
    for (p = m1_ents41CEC0; (int32_t)p < (int32_t)&m1_ents41CEC0[3]; p++) {
        M3EE26 *volatile vp = p; M3EE26 *e = vp;
        if ((int32_t)e->f0 >= 0) continue;
        q = (M3EU26 *)m1_rbBData41D008;
        for (i = 0; i < 3; i++, q = (M3EU26 *)((uint8_t *)q + 0x150))
            if (!(q->fC & 1)) goto got;
        q = 0;
got:
        e->unit64 = q;
        if (q == 0) continue;
        {
            volatile int va = e->a4; int b = e->b8;
            if (va < 0 || va > 3 || b >= 3) m = 0;
            else { volatile int st = 0x150; m = m1_rbAData41CEBC + (b + va * 3) * st; }
        }
        sub_00022380(q, m, ctx);
        r1i_UnitsAttach(ctx, e->unit64, e->unit64->list14C, 5, 0x11);
        e->unit64->fC |= 1;
        e->unit64->kind4 = 0xD;
        e->unit64->type8 = e->a4 * 3 + e->b8;
        e->f0 = (e->f0 & 0x7FFFFFFE) | 1;
        a3c_VecCopy(e->unit64->pos60, e->pos34);
        sub_0001EBF0(e->unit64, 0);
        sub_0001D4B0(e->unit64, 0);
        if (e->a4 != 3) {
            M3ER26 *r = a12_List_FindId(e->unit64, 0);
            r->kind4 = e->unit64->kind4;
            r->type8 = e->unit64->type8;
        }
    }
}
#pragma optimize("", on)

typedef struct M3PR26 { uint32_t f0; uint8_t unk04[0x3C]; float pos40[4]; uint8_t unk50[0x8C]; } M3PR26;
typedef struct M3PMdl26 { uint8_t unk00[0xC4]; uint8_t *bonesC4; } M3PMdl26;
typedef struct M3PHold26 { uint8_t unk00[0x20]; M3PMdl26 *mdl20; uint8_t unk24[0x3C]; float pos60[4]; } M3PHold26;
typedef struct M3PBoss26 { uint8_t unk00[0xFD8]; M3PHold26 *holdFD8; } M3PBoss26;
extern M3PR26 m1_voices420F20[];
extern float m1_frameTime42C858;
void r4c_VecSub(float *dst, const float *a, const float *b);
float m1_VecLen082D70(const float *v);
void rbi_VecNorm(float *d, const float *s);
void sub_000CA200(void *bone, float *pos, float *dir, int a, int b, int c);
void rbi_VecScale(float *d, const float *s, float k);
void r4e_VecAdd4(float *d, const float *a, const float *b);

/* 0xCA9C0: suck in pickups: every live record with flag 0x800 within range of the boss's held object is pulled along the direction to it (0xCA200 at the boss's bone +0x7F0) and moved by one frame step. */
void m3_PullPickupsCA9C0(M3PBoss26 *b, int x, float range, int y, int z) {
    M3PMdl26 *m = b->holdFD8->mdl20; float d[4], l; M3PR26 *p;
    d[0] = 0.0f; d[1] = 0.0f; d[2] = 0.0f; d[3] = 1.0f;
    for (p = m1_voices420F20; (int32_t)p->pos40 < (int32_t)m1_voices420F20[56].pos40; p++) {
        { volatile uint32_t f = p->f0; if (!(f & 1) || !(f & 0x800)) continue; }
        r4c_VecSub(d, b->holdFD8->pos60, p->pos40);
        l = m1_VecLen082D70(d);
        rbi_VecNorm(d, d);
        if (range > l) {
            sub_000CA200(m->bonesC4 + 0x7F0, p->pos40, d, y, x, z);
            rbi_VecScale(d, d, m1_frameTime42C858);
            r4e_VecAdd4(p->pos40, p->pos40, d);
        }
    }
}

typedef struct M3Save26 { int32_t i0, i4; int32_t w8[8]; int32_t i28, i2C; int32_t blk30[0x50]; float f170; int32_t pos174[4]; int32_t i184; } M3Save26;
typedef struct M3SvPl26 { uint8_t unk00[0x60]; int32_t pos60[4]; } M3SvPl26;
extern M3SvPl26 *g_playerObj;
extern int32_t m3_stat420C24, m3_stat420C28, m3_stat420C60, m3_stat420C64;
extern float m3_gauge41FFC8, m3_gauge41FFBC;
extern int32_t m3_pending420000;
extern int32_t m1_costume420C2C[8];
extern int32_t m3_saveBlk420C68[0x50];
extern int m1_plMode420078;
void sub_000BCB90(void);
void sub_000BCBC0(int v);
void sub_000BCBE0(void);
void sub_000BCC90(void);

/* 0xCFB50: restore the player state from a save block: stats, gauges, pending form change, player position, costume words and the 0x50-word block; a pending change resets the form and re-runs the form setup. */
void m3_LoadStateCFB50(M3Save26 *s) {
    int32_t *d, *p; int32_t v;
    m3_stat420C24 = s->i0;
    m3_stat420C28 = s->i4;
    m3_stat420C60 = s->i28;
    m3_stat420C64 = s->i2C;
    m3_gauge41FFC8 = s->f170;
    m3_gauge41FFBC = s->f170;
    m3_pending420000 = s->i184;
    g_playerObj->pos60[0] = s->pos174[0];
    g_playerObj->pos60[1] = s->pos174[1];
    g_playerObj->pos60[2] = s->pos174[2];
    g_playerObj->pos60[3] = s->pos174[3];
    m1_costume420C2C[0] = s->w8[0]; m1_costume420C2C[1] = s->w8[1]; m1_costume420C2C[2] = s->w8[2]; m1_costume420C2C[3] = s->w8[3];
    m1_costume420C2C[4] = s->w8[4]; m1_costume420C2C[5] = s->w8[5]; m1_costume420C2C[6] = s->w8[6]; m1_costume420C2C[7] = s->w8[7];
    for (d = m3_saveBlk420C68, p = s->blk30; (int32_t)d < (int32_t)&m3_saveBlk420C68[0x50]; d++, p++) *d = *p;
    v = m3_pending420000;
    if (v == 0) return;
    m1_plMode420078 = 0;
    m3_pending420000 = 0;
    sub_000BCB90();
    sub_000BCBC0(v);
    sub_000BCBE0();
    sub_000BCC90();
}

/* 0xCFA60: save the player state into a save block (inverse of 0xCFB50): stats, gauge, pending form change, position, costume words and the 0x50-word block. */
#pragma optimize("s", on)
void m3_SaveStateCFA60(M3Save26 *s) {
    s->i0 = m3_stat420C24;
    s->i4 = m3_stat420C28;
    s->i28 = m3_stat420C60;
    s->i2C = m3_stat420C64;
    s->f170 = m3_gauge41FFC8;
    s->i184 = m3_pending420000;
    s->pos174[0] = g_playerObj->pos60[0];
    s->pos174[1] = g_playerObj->pos60[1];
    s->pos174[2] = g_playerObj->pos60[2];
    s->pos174[3] = g_playerObj->pos60[3];
    s->w8[0] = m1_costume420C2C[0]; s->w8[1] = m1_costume420C2C[1]; s->w8[2] = m1_costume420C2C[2]; s->w8[3] = m1_costume420C2C[3];
    s->w8[4] = m1_costume420C2C[4]; s->w8[5] = m1_costume420C2C[5]; s->w8[6] = m1_costume420C2C[6]; s->w8[7] = m1_costume420C2C[7];
    {
        int32_t *d = s->blk30; int n = 0x50;
        int diff = (int)((uint8_t *)&m1_costume420C2C[3] - (uint8_t *)s);
        do { *d = *(int32_t *)((uint8_t *)d + diff); d++; } while (--n);
    }
}
#pragma optimize("", on)

typedef struct M3SpPl26 { uint8_t unk00[0x60]; float pos60[4]; } M3SpPl26;
extern float m3_sparkTbl2E4E90[13];
extern int32_t m3_sparkFx2E4EC0[];
extern int m1_level413178;
float r4_Distance(const float *a, const float *b);
void m1_FxAdd0C4DF0(int a, int kind, float s, int fx, float r1, int b, float r2, float *pos, float *dir, float *up);

/* 0xADCB0: menu step that sprinkles three sparkle effects (table positions and sizes, effect by difficulty) while the player is within 50 of the second spot: 0 clears, 1 sets bit 0 and 10, 3 or a setting of 20 clears and returns 0. */
int m3_MenuSparkADCB0(int k, int *s) {
    float a[4], c[4], b[4], *p; int fx;
    a[0] = 0.0f; a[1] = 0.0f; a[2] = 0.0f; a[3] = 1.0f;
    c[0] = 0.0f; c[1] = 0.0f; c[2] = 0.0f; c[3] = 1.0f;
    b[0] = 0.0f; b[1] = 0.0f; b[2] = 0.0f; b[3] = 1.0f;
    if (k == 0) { s[0] = 0; s[1] = 0; return 1; }
    if (k == 1) { s[0] |= 1; s[2] = 0; s[1] = 10; return 1; }
    if (k != 3) {
        if (s[1] == 10) goto work;
        if (s[1] != 0x14) return 1;
    }
    s[0] = 0; s[1] = 0;
    return 0;
work:
    fx = m3_sparkFx2E4EC0[m1_level413178];
    a[0] = m3_sparkTbl2E4E90[4]; a[1] = m3_sparkTbl2E4E90[5]; a[2] = m3_sparkTbl2E4E90[6];
    if (50.0f >= r4_Distance(((M3SpPl26 *)g_playerObj)->pos60, a)) {
        for (p = &m3_sparkTbl2E4E90[1]; (int32_t)p < (int32_t)&m3_sparkTbl2E4E90[13]; p += 4) {
            float *volatile vp = p; float *q = vp; float sc = q[2];
            a[0] = q[-1]; a[1] = q[0]; a[2] = q[1];
            m1_FxAdd0C4DF0(0, 0, 1.0f, fx, sc, 0, sc, a, c, b);
        }
    }
    return 1;
}

extern float m3_sparkB2E4BE8[24];
extern int32_t m3_sparkBFx2E4C48[];

/* 0xACA60: like 0xADCB0 with two clusters of three sparkles, each shown while the player is within 50 of the cluster's second spot. */
int m3_MenuSpark2ACA60(int k, int *s) {
    float a[4], c[4], b[4], *p; int fx;
    a[0] = 0.0f; a[1] = 0.0f; a[2] = 0.0f; a[3] = 1.0f;
    c[0] = 0.0f; c[1] = 0.0f; c[2] = 0.0f; c[3] = 1.0f;
    b[0] = 0.0f; b[1] = 0.0f; b[2] = 0.0f; b[3] = 1.0f;
    if (k == 0) { s[0] = 0; s[1] = 0; return 1; }
    if (k == 1) { s[0] |= 1; s[2] = 0; s[1] = 10; return 1; }
    if (k != 3) {
        if (s[1] == 10) goto work;
        if (s[1] != 0x14) return 1;
    }
    s[0] = 0; s[1] = 0;
    return 0;
work:
    fx = m3_sparkBFx2E4C48[m1_level413178];
    a[0] = m3_sparkB2E4BE8[4]; a[1] = m3_sparkB2E4BE8[5]; a[2] = m3_sparkB2E4BE8[6];
    if (50.0f >= r4_Distance(((M3SpPl26 *)g_playerObj)->pos60, a)) {
        for (p = &m3_sparkB2E4BE8[1]; (int32_t)p < (int32_t)&m3_sparkB2E4BE8[13]; p += 4) {
            float *volatile vp = p; float *q = vp; float sc = q[2];
            a[0] = q[-1]; a[1] = q[0]; a[2] = q[1];
            m1_FxAdd0C4DF0(0, 0, 1.0f, fx, sc, 0, sc, a, c, b);
        }
    }
    a[0] = m3_sparkB2E4BE8[16]; a[1] = m3_sparkB2E4BE8[17]; a[2] = m3_sparkB2E4BE8[18];
    if (50.0f >= r4_Distance(((M3SpPl26 *)g_playerObj)->pos60, a)) {
        for (p = &m3_sparkB2E4BE8[13]; (int32_t)p < (int32_t)&m3_sparkB2E4BE8[25]; p += 4) {
            float *volatile vp = p; float *q = vp; float sc = q[2];
            a[0] = q[-1]; a[1] = q[0]; a[2] = q[1];
            m1_FxAdd0C4DF0(0, 0, 1.0f, fx, sc, 0, sc, a, c, b);
        }
    }
    return 1;
}
