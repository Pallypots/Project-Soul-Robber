/* Area m3, batch 29. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M3Modes29 { uint8_t unk00[0x5C]; int pick5C; int32_t bits60[11]; } M3Modes29;
extern M3Modes29 r2_modes3EDB60;
extern int m1_talk3EDBB0;
int a5b_GetVideoMode(void);
int sub_001C7EE1(void);

#pragma optimize("s", on)
/* 0xD85F0: pick a random unused id in a range set by video mode and the talk flag (bitset of 10 bits per word; resets when the last word is full), store id*2+35 and return it; gives up after 1000 tries. */
int m3_PickIdD85F0(void) {
    float hi, lo;
    int n, i, a, b, mn, mx, v, tries;
    int32_t *w = r2_modes3EDB60.bits60;
    if (!a5b_GetVideoMode()) {
        hi = 109.0f;
        lo = 99.0f;
        if (m1_talk3EDBB0) lo = 0.0f;
        n = 10;
    } else {
        lo = 0.0f;
        hi = 10.0f;
        if (m1_talk3EDBB0) hi = 99.0f;
        n = 9;
    }
    for (i = 0; i < 11; i++) {
        if (i == n) {
            if (w[i] != 0x1FF) break;
            w[0] = 0; w[1] = 0; w[2] = 0; w[3] = 0; w[4] = 0; w[5] = 0; w[6] = 0;
            w[8] = 0; w[9] = 0; w[10] = 0; w[7] = 4;
        } else if (w[i] != 0x3FF) break;
    }
    tries = 0;
    a = _mm_cvtt_ss2si(_mm_set_ss(hi));
    b = _mm_cvtt_ss2si(_mm_set_ss(lo));
    do {
        mx = a; mn = b;
        if (mn > mx) { v = mn; mn = mx; mx = v; }
        v = sub_001C7EE1() % (mx - mn) + mn;
        if (!(w[(unsigned)v / 10] & (1 << ((unsigned)v % 10)))) {
            w[(unsigned)v / 10] |= 1 << ((unsigned)v % 10);
            r2_modes3EDB60.pick5C = v * 2 + 0x23;
            return r2_modes3EDB60.pick5C;
        }
    } while (++tries < 1000);
    return r2_modes3EDB60.pick5C;
}
#pragma optimize("", on)

typedef struct M3Mn29 { uint8_t unk00[0x9C]; int st9C; float tA0; uint8_t unkA4[0x178 - 0xA4]; float f178; uint8_t unk17C[0xC]; float f188;
                        uint8_t unk18C[0xC]; float f198; uint8_t unk19C[0xC]; void *p1A8; } M3Mn29;
typedef struct M3Ob29 { uint8_t unk00[0x64]; float f64; } M3Ob29;
extern M3Mn29 *afc_minion;
extern float a50_framesPerSecond, a50_frameSeconds;
void sub_000F3D10(void *o, void *c, int mode);
float sub_00194D60(void *p);
void sub_00194D30(void *p, int k);
void sub_0001D7A0(void *o);
void aab_Hide1D700(void *o);

/* 0xFF2C0: minion leap step: state 0 rises then falls (gravity 1.1/s, fall cap 38/s) and hides after 1 s; state 1 waits for its sound to end and then stops it; any other state hands off to mode 0x24. */
void m3_MinionLeapFF2C0(M3Ob29 *o, void *c) {
    M3Mn29 *m = afc_minion;
    float lim;
    switch (m->st9C) {
    case 0:
        o->f64 = m->f198 + m->f188;
        m->f188 = m->f178 + m->f188;
        m->f178 = 1.1f / a50_framesPerSecond + m->f178;
        lim = 0.0f - 38.0f / a50_framesPerSecond;
        if (m->f188 >= lim) m->f188 = lim;
        if (m->tA0 > 1.0f) {
            aab_Hide1D700(o);
            o->f64 = -85.0f;
            sub_00194D30(m->p1A8, 8);
            m->st9C++;
            return;
        }
        m->tA0 += a50_frameSeconds;
        return;
    case 1:
        if (sub_00194D60(m->p1A8) > 0.0f) return;
        sub_00194D30(m->p1A8, 0);
        sub_0001D7A0(m->p1A8);
        sub_000F3D10(o, c, 0x24);
        return;
    default:
        sub_000F3D10(o, c, 0x24);
    }
}

typedef struct M3Tier29 { int upto; int count; } M3Tier29;
int sub_000A8330(void *src, float *out, int a);
int sub_000A8990(int id, int kind, int a, const float *pos, float *v0, float *v1);
void a3c_VecCopy(float *dst, const float *src);

/* 0xA9140: burst of pickup effects: count is given, or taken from a tier table by amount (8:1, 15:3, 20:3, 40:4, 79:5, 999:4); each spawns effect 0x47..0x4A at pos lowered by 12. */
void m3_PickupBurstA9140(int amount, int count, const float *pos, void *src) {
    float p[4], v0[4], v1[4];
    M3Tier29 tier[6] = { {8, 1}, {15, 3}, {20, 3}, {40, 4}, {79, 5}, {999, 4} };
    int n = 0, i, r;
    v0[0] = 0.0f; v0[1] = 0.0f; v0[2] = 0.0f; v0[3] = 1.0f;
    p[0] = 0.0f; p[1] = 0.0f; p[2] = 0.0f; p[3] = 1.0f;
    v1[0] = 0.0f; v1[1] = 0.0f; v1[2] = 0.0f; v1[3] = 1.0f;
    if (count) n = count;
    else {
        if (!amount) return;
        for (i = 0; i < 6; i++) {
            if (amount <= tier[i].upto) { n = tier[i].count; break; }
        }
    }
    if (n <= 0) return;
    do {
        r = sub_001C7EE1() % 4;
        sub_000A8330(src, v0, r);
        a3c_VecCopy(p, pos);
        p[1] -= 12.0f;
        sub_000A8990(r + 0x47, 0xC, 0, p, v0, v1);
    } while (--n);
}

typedef struct M3PMdl29 { uint8_t unk00[0xC4]; uint8_t *bonesC4; } M3PMdl29;
typedef struct M3PHold29 { uint8_t unk00[0x20]; M3PMdl29 *mdl20; uint8_t unk24[0x3C]; float pos60[4]; } M3PHold29;
typedef struct M3PBoss29 { uint8_t unk00[0xFD8]; M3PHold29 *holdFD8; } M3PBoss29;
typedef struct M3PEnt29 { uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0x4C]; float pos60[4]; } M3PEnt29;
typedef struct M3Fx29 { int f0; int kind4; uint8_t unk08[0xD8]; } M3Fx29;
M3PEnt29 *sub_000EDB10(int k);
M3PEnt29 *sub_000EDB90(void);
float aab_Use82D70(const float *v);
void sub_000C4B70(M3Fx29 *f);
int  m1_FxShotA0C5D20(void *pl, void *who, M3Fx29 *r, float *a, float *b);
void sub_000CA200(uint8_t *bone, float *pos, float *d, int y, int x, int z);
void aab_Vec1AD9F0(float *d, const float *a, const float *b);
void sub_001ADAF0(float *d, const float *a, const float *b);
void sub_001ADBA0(float *d, const float *a, float s);
extern float a50_frameUnits;

/* 0xCA850: pull flagged (0x20) entities toward the boss's held object when within range on the ground plane; optionally fire effect 0x2B at each pulled one. */
void m3_PullEntsCA850(M3PBoss29 *b, int x, float range, int fire, int y, int z) {
    float d[4];
    M3PMdl29 *m;
    float e[4];
    M3Fx29 fx;
    M3PEnt29 *p;
    m = b->holdFD8->mdl20;
    d[0] = 0.0f; d[1] = 0.0f; d[2] = 0.0f; d[3] = 1.0f;
    e[0] = 0.0f; e[1] = 0.0f; e[2] = 0.0f; e[3] = 1.0f;
    for (p = sub_000EDB10(0); p; p = sub_000EDB90()) {
        if (!(p->f10 & 0x20)) continue;
        aab_Vec1AD9F0(d, b->holdFD8->pos60, p->pos60);
        d[1] = 0.0f;
        if (range > aab_Use82D70(d)) {
            sub_000CA200(m->bonesC4 + 0x7F0, p->pos60, d, y, x, z);
            sub_001ADBA0(d, d, a50_frameUnits);
            sub_001ADAF0(p->pos60, p->pos60, d);
            if (fire) {
                sub_000C4B70(&fx);
                fx.kind4 = 0x2B;
                m1_FxShotA0C5D20(b, p, &fx, e, e);
            }
        }
    }
}

typedef struct M3HSet29 { int id; int n; int *hits; } M3HSet29;
typedef struct M3HComp29 { uint8_t unk00[0x20]; M3HSet29 *sets20; } M3HComp29;
typedef struct M3HMdl29 { uint8_t unk00[0xD8]; void *skelD8; } M3HMdl29;
typedef struct M3HRoot29 { uint8_t unk00[0x14]; M3HMdl29 *mdl14; } M3HRoot29;
typedef struct M3HObj29 { uint8_t unk00[0x20]; void *part20; uint8_t unk24[0xC]; M3HRoot29 *root30; } M3HObj29;
typedef struct M3HShape29 { uint8_t unk00[0x10]; float f10; float f14; } M3HShape29;
typedef struct M3HSph29 { float c[4]; float r; } M3HSph29;
M3HComp29 *sub_0001D960(void *o, int kind);
void *sub_0001D0F0(void *o, int part);
void sub_000EEBC0(void *skel, int *hit, float *out);
void sub_000EE3B0(void *part, float *t, M3HSph29 *s);
int  sub_000EE2B0(M3HSph29 *s, M3HShape29 *shape, int k);

/* 0xEE470: test a shape against hit set `id` of an object's hit component: each hit sphere (on its bone, scaled by `scale`) is tested; returns 1 on the first hit. */
int m3_HitSetTestEE470(M3HObj29 *o, int id, M3HShape29 *s, float scale, int k) {
    M3HComp29 *c;
    M3HSet29 *e;
    int i, j;
    void *q;
    M3HSph29 sp;
    float t[6];
    if (!o || !s) return 0;
    c = sub_0001D960(o, 0xD);
    if (!c) return 0;
    if (s->f10 == 0.0f) return 0;
    if (s->f14 == 0.0f) return 0;
    e = c->sets20;
    if (!e) return 0;
    if (e->id < 0) return 0;
    for (i = 0; id != e[i].id; i++) {
        if (e[i + 1].id < 0) return 0;
    }
    e = &e[i];
    if (!e) return 0;
    for (j = 0; j < e->n; j++) {
        int *h = (int *)((uint8_t *)e->hits + j * 12);
        q = sub_0001D0F0(o, *h);
        if (!q) q = o->part20;
        sub_000EEBC0(o->root30->mdl14->skelD8, h, t);
        sub_000EE3B0(q, t, &sp);
        if (sp.r != 0.0f) {
            sp.r *= scale;
            if (sub_000EE2B0(&sp, s, k) == 1) return 1;
        }
    }
    return 0;
}
