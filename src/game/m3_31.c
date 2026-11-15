/* Area m3, batch 31. Names inferred. */
#include <stdint.h>

typedef struct M3Key31 { float t; float v; float vec[4]; } M3Key31;
typedef struct M3Trk31 { int unk0; int n4; M3Key31 *keys8; } M3Trk31;
void sub_001ADBA0(float *d, const float *a, float s);
void sub_001ADAF0(float *d, const float *a, const float *b);

/* 0xEEBC0: sample a key track at time t: find the bracketing keys and lerp the scalar and vector; out = {t, v, vec.xyz, 1}, or zeros with w 1 when t is outside the track (hangs on a null track or output). */
void m3_TrackSampleEEBC0(float t, M3Trk31 *k, float *out) {
    float tmp[4], f, g;
    M3Key31 *a, *b;
    int i, n;
    if (!k || !out) for (;;) ;
    n = k->n4 - 1;
    i = 0;
    if (n >= 4) {
        M3Key31 *p = k->keys8 + 1;
        do {
            if (t >= p[-1].t && p[0].t >= t) { a = &p[-1]; b = &p[0]; goto found; }
            if (t >= p[0].t && p[1].t >= t) { a = &p[0]; b = &p[1]; i += 1; goto found; }
            if (t >= p[1].t && p[2].t >= t) { a = &p[1]; b = &p[2]; i += 2; goto found; }
            if (t >= p[2].t && p[3].t >= t) { a = &p[2]; b = &p[3]; i += 3; goto found; }
            i += 4;
            p += 4;
        } while (i < n - 3);
    }
    for (; i < n; i++) {
        a = &k->keys8[i];
        b = &k->keys8[i + 1];
        if (t >= a->t && b->t >= t) break;
    }
found:
    if (i >= n) {
        out[0] = 0.0f; out[1] = 0.0f; out[2] = 0.0f; out[3] = 0.0f; out[4] = 0.0f;
        out[5] = 1.0f;
        return;
    }
    f = (t - a->t) / (b->t - a->t);
    out[0] = t;
    g = 1.0f - f;
    out[1] = a->v * g + b->v * f;
    sub_001ADBA0(out + 2, a->vec, g);
    sub_001ADBA0(tmp, b->vec, f);
    sub_001ADAF0(out + 2, out + 2, tmp);
    out[5] = 1.0f;
}

#include <xmmintrin.h>
typedef struct M3UNd31 { struct M3UNd31 *next; uint8_t unk04[8]; void (*fnC)(void); } M3UNd31;
typedef struct M3UHd31 { int unk0; M3UNd31 *head4; } M3UHd31;
typedef struct M3UOb31 { uint8_t unk00[4]; int f4; int f8; uint32_t fC; uint8_t unk10[0x50]; float pos60[4]; } M3UOb31;
typedef struct M3UEn31 { struct M3UEn31 *next; uint8_t unk04[8]; M3UOb31 *oC; } M3UEn31;
typedef struct M3UCp31 { uint8_t unk00[0x10]; int f10; uint8_t unk14[0x10]; int (*cull24)(void *o); void (*upd28)(void *o); } M3UCp31;
typedef struct M3UBs31 { uint8_t unk00[0x274]; float f274; } M3UBs31;
extern M3UHd31 aec_3F5DB0, r2d_q3F60D0;
extern M3UEn31 *aec_list3F5DC4, *r2_head3F60E0, *m1_filtNext3F60E4;
extern int r2_list3F5DC0;
extern int a9b_g413164;
extern uint32_t aa0_flags420010;
extern int g_stats;
extern uint8_t *g_playerObj;
void b16_SlotSysClear2(void);
void *sub_0001D960(void *o, int kind);
float sub_001B2730(const float *a, const float *b);
int  sub_000EE5F0(void *o);
void sub_000253D0(int a, int b);
void a80_ModeSetFlag4(void);
void PlayerObj_SetFlags(void *s, int f, int v);
void a80_Set3ED238(void);
M3UEn31 *a4c_ListFind(void *l, int k, void *o);
void sub_0003D8C0(void *e);
void sub_0003D860(void *e);
void sub_0001EB80(void *o);
void sub_000362B0(void *o);
void sub_0001D190(void *o);
void aab_Hide1B3F0(void *o);
void sub_00102FA0(void);

/* 0xED7E0: per-frame object pass: run pre hooks, update every listed object; far objects (over 1000) may trigger the stage-exit event (stage 5 obj 2/11 or stage 11 obj 2/13) and are culled and unlinked when their hit component allows; then post hooks. */
void m3_ObjPassED7E0(void) {
    M3UNd31 *n;
    M3UEn31 *cur, *e;
    M3UOb31 *o;
    M3UCp31 *c;
    b16_SlotSysClear2();
    for (n = aec_3F5DB0.head4; n; n = n->next) n->fnC();
    for (cur = aec_list3F5DC4; cur; cur = r2_head3F60E0) {
        o = cur->oC;
        r2_head3F60E0 = cur->next;
        c = (M3UCp31 *)sub_0001D960(o, 0xD);
        if (!c) for (;;) ;
        c->upd28(o);
        if (c->f10 < 0) continue;
        if (!(sub_001B2730(o->pos60, (float *)(g_playerObj + 0x60)) > 1000.0f)) continue;
        if (a9b_g413164 == 5) {
            if (o->f4 != 2 || o->f8 != 0xB) goto cull;
            if (aa0_flags420010 & 0x80000) goto cull;
        } else {
            if (a9b_g413164 != 0xB || o->f4 != 2 || o->f8 != 0xD) goto cull;
            if (aa0_flags420010 & 0x80000) goto cull;
        }
        sub_000253D0(2, _mm_cvtt_ss2si(_mm_load_ss(&((M3UBs31 *)sub_0001D960(o, sub_000EE5F0(o)))->f274)));
        a80_ModeSetFlag4();
        PlayerObj_SetFlags(&g_stats, 0x10, 0);
        a80_Set3ED238();
cull:
        if (!o || !(o->fC & 1)) continue;
        c = (M3UCp31 *)sub_0001D960(o, 0xD);
        if (!c || !c->cull24(o)) continue;
        e = a4c_ListFind(&r2_list3F5DC0, 0, o);
        if (e) {
            if (r2_head3F60E0 == e) r2_head3F60E0 = e->next;
            if (m1_filtNext3F60E4 == e) m1_filtNext3F60E4 = e->next;
            sub_0003D8C0(e);
            sub_0003D860(e);
        }
        o->fC &= ~1u;
        sub_0001EB80(o);
        sub_000362B0(o);
        sub_0001D190(o);
        aab_Hide1B3F0(o);
    }
    for (n = r2d_q3F60D0.head4; n; n = n->next) n->fnC();
    sub_00102FA0();
}

typedef struct M3HSet31 { int id; int n; int *hits; } M3HSet31;
typedef struct M3HMdl31 { uint8_t unk00[0xD8]; void *skelD8; } M3HMdl31;
typedef struct M3HRoot31 { uint8_t unk00[0x14]; M3HMdl31 *mdl14; } M3HRoot31;
typedef struct M3HObj31 { uint8_t unk00[0x20]; void *part20; uint8_t unk24[0xC]; uint8_t *root30; } M3HObj31;
typedef struct M3HTgt31 { uint8_t unk00[4]; int kind4; uint8_t unk08[0x58]; float pos60[4]; uint8_t unk70[0x30]; float offA0[4]; float rB0; float hB4; } M3HTgt31;
typedef struct M3HCyl31 { float c[4]; float r; float h; } M3HCyl31;
typedef struct M3HSph31 { float c[4]; float r; } M3HSph31;
void m1_TgtInfo0C4250(void *s, float *c, float *rh);
void *sub_0001D0F0(void *o, int part);
void sub_000EE3B0(void *part, float *t, M3HSph31 *s);
int  sub_000EE2B0(M3HSph31 *s, M3HCyl31 *shape, int k);
void sub_000EEBC0(void *skel, int *hit, float *out);

/* 0x113870: test hit set `id` of an object against a target's cylinder (the player via its stats, or a type-13 body); returns the index of the first hit sphere, else -1. */
int m3_HitSetIdx113870(void *a, M3HObj31 *o, M3HTgt31 *t, int id, int k) {
    float rh[2];
    M3HSph31 sp;
    int j;
    M3HCyl31 cy;
    float tm[6];
    M3HSet31 *e;
    int i;
    void *q;
    if (!a || !o || !t || !o->root30) return -1;
    switch (t->kind4) {
    case 1:
        m1_TgtInfo0C4250(&g_stats, cy.c, rh);
        cy.r = rh[0];
        cy.h = rh[1];
        break;
    case 0xD:
        sub_001ADAF0(cy.c, t->pos60, t->offA0);
        cy.r = t->rB0;
        cy.h = t->hB4;
        break;
    default:
        return -1;
    }
    if (cy.r == 0.0f) return -1;
    if (cy.h == 0.0f) return -1;
    e = (M3HSet31 *)o->root30;
    if (e->id < 0) return -1;
    for (i = 0; id != e[i].id; i++) {
        if (e[i + 1].id < 0) return -1;
    }
    e = &e[i];
    if (!e) return -1;
    for (j = 0; j < e->n; j++) {
        int *h = (int *)((uint8_t *)e->hits + j * 12);
        q = sub_0001D0F0(o, *h);
        if (!q) q = o->part20;
        sub_000EEBC0(((M3HRoot31 *)o->root30)->mdl14->skelD8, h, tm);
        sub_000EE3B0(q, tm, &sp);
        if (sp.r != 0.0f && sub_000EE2B0(&sp, &cy, k) == 1) return j;
    }
    return -1;
}

typedef struct M3HdB31 { uint8_t unk00[0xB4]; uint8_t *mtxB4; } M3HdB31;
typedef struct M3HdM31 { uint8_t unk00[0xC8]; M3HdB31 *bC8; } M3HdM31;
typedef struct M3HdR31 { M3HdM31 *m; uint8_t unk04[0x14C]; } M3HdR31;
typedef struct M3HdO31 { uint8_t unk00[8]; int n8; uint8_t unk0C[0x14]; M3HdR31 r20[1]; } M3HdO31;
typedef struct M3HdC31 { uint8_t unk00[0x6C]; int st6C; uint8_t unk70[0x60]; float yawD0; } M3HdC31;
void sub_001AE060(float *d, const float *m);
void sub_001AD9B0(float *d, const float *m, const float *p);
float sub_001A3EC0(float y, float x);
float sub_001A3F30(float a);
void sub_001AD940(float *m);
void sub_001AD8E0(float *d, const float *m, float a);
int  sub_000F3140(int k);
void a3c_VecCopy(float *dst, const float *src);

/* 0xEF640: same head tracking as 0x107060 for another actor kind (yaw at +0xD0), skipped while the actor is in state 0x12. */
void m3_HeadTrackEF640(M3HdO31 *o) {
    float t, v[4], m[16], a;
    uint8_t *pl = g_playerObj;
    M3HdC31 *c = (M3HdC31 *)sub_0001D960(o, 5);
    M3HdR31 *r;
    int i;
    uint8_t *b;
    if (c->st6C == 0x12) return;
    r = o->r20;
    sub_001AE060(m, (float *)((uint8_t *)o->r20[0].m + 0x40));
    sub_001AD9B0(v, m, (float *)(pl + 0x60));
    a = sub_001A3EC0(v[0] * -1.0f, v[2] * -1.0f);
    if (a >= (double)0.78539819f) a = 0.78539819f;
    else if (-0.78539819f >= a) a = -0.78539819f;
    t = a - c->yawD0;
    if (0.034906585f > sub_001A3F30(t)) c->yawD0 = a;
    else if (t > 0.0f) {
        c->yawD0 = c->yawD0 + 0.034906585f;
        if (c->yawD0 >= 0.78539819f) c->yawD0 = 0.78539819f;
    } else {
        c->yawD0 = c->yawD0 - 0.034906585f;
        if (-0.78539819f >= c->yawD0) c->yawD0 = -0.78539819f;
    }
    sub_001AD940(m);
    sub_001AD8E0(m, m, c->yawD0);
    for (i = 0; i < sub_000F3140(o->n8); i++, r++) {
        b = r->m->bC8->mtxB4 + 0x720;
        a3c_VecCopy((float *)b, m);
        a3c_VecCopy((float *)(b + 0x10), m + 4);
        a3c_VecCopy((float *)(b + 0x20), m + 8);
    }
}

typedef struct M3KSt31 { uint8_t unk00[4]; uint32_t f4; } M3KSt31;
typedef struct M3KEnt31 { uint8_t unk00[0x4C]; uint32_t f4C; uint8_t unk50[0x28]; float v78[4]; float x88; float y8C; float z90;
                          uint8_t unk94[0x278 - 0x94]; M3KSt31 *st278; } M3KEnt31;
typedef struct M3KAi31 { uint8_t unk00[0x10]; uint32_t f10; } M3KAi31;
typedef struct M3KCmd31 { int f0; uint8_t unk04[0xC]; float f10; } M3KCmd31;
extern float a50_frameSeconds, a50_frameUnits;
float sub_001A3F50(float a);
void sub_001ADA60(float *d, const float *a, const float *b);
void sub_001B2890(float *m, const float *axis, float ang);
void sub_00113090(void *a, void *o, int s);
M3KCmd31 *sub_00113400(void *o, int v);

/* 0x13A4A0: launch an AI up and back along its horizontal velocity (pitch 88.5 deg at speed 120, or 61.5 deg at 117 for the heavy flag), enter state 0x37 (0x3B if the facing sign bit is set) and set command 7's timer; returns the sign bit. */
uint32_t m3_AiLaunch13A4A0(M3KAi31 *a, M3KEnt31 *o) {
    float s, v[4], u[4], m[16], inv, ang;
    M3KSt31 *st = o->st278;
    uint32_t sg = st->f4 & 0x80000000u;
    M3KCmd31 *c;
    u[1] = 1.0f; u[0] = 0.0f; u[2] = 0.0f; u[3] = 0.0f;
    inv = 1.0f / sub_001A3F50(o->x88 * o->x88 + o->z90 * o->z90);
    v[0] = o->x88 * inv;
    v[1] = 0.0f;
    v[2] = inv * o->z90;
    v[3] = 0.0f;
    sub_001ADA60(u, v, u);
    if (st->f4 & 0x10000000) { ang = 1.0733775f; s = 117.0f; }
    else { ang = 1.5446165f; s = 120.0f; }
    sub_001B2890(m, u, ang);
    sub_001AD9B0(v, m, v);
    sub_001ADBA0(o->v78, v, s);
    sub_00113090(a, o, sg ? 0x3B : 0x37);
    a->f10 = (a->f10 & ~0x20u) | 0x10;
    o->f4C &= ~8u;
    c = sub_00113400(o, 7);
    c->f10 = (float)((st->f4 & 0x10000000) ? 4 : 1) * (5.0f / a50_frameUnits) * a50_frameSeconds;
    if (c->f0) c->f0 = 2;
    a->f10 |= 4;
    return sg;
}
