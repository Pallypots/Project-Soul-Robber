/* Area m1, file 144: more script opcode helpers. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Vm144 { uint8_t unk00[4]; uint8_t *pc4; } M1Vm144;
typedef union M1Hi144 { int16_t s; uint8_t b[2]; } M1Hi144;
typedef union M1F144 { uint32_t u; float f; } M1F144;
extern uint8_t m1_stats41FEC0[];

#define M1_RDF144(d, p) do { M1Hi144 h_; h_.b[0] = (p)[2]; h_.b[1] = (p)[3]; \
    (d).u = (((uint32_t)(uint16_t)h_.s << 8 | (p)[1]) << 8) | (p)[0]; } while (0)

void sub_000D1CA0(void *s, float *v);
void sub_00087450(void);
void sub_000D9020(void);
void m1_AimAt0CF330(void *s, float *v, float r);
void m1_PlAct0CF490(void *s, int id);
void m1_PlStop0D0000(void);
void m1_PlWalkTo0D23D0(float *v, int a);

/* 0xDB090: script op, warp the player to a position in the script. */
int m1_OpWarp0DB090(M1Vm144 *c) {
    uint8_t *p = c->pc4; M1F144 x, y, z; float v[4];
    M1_RDF144(x, p); M1_RDF144(y, p + 4); M1_RDF144(z, p + 8);
    v[0] = x.f; v[1] = y.f; v[2] = z.f; v[3] = 1.0f;
    sub_000D1CA0(m1_stats41FEC0, v);
    sub_00087450();
    sub_000D9020();
    return 0x200C;
}

/* 0xDB150: script op, make the player face a position in the script. */
int m1_OpFace0DB150(M1Vm144 *c) {
    uint8_t *p = c->pc4; M1F144 x, y, z; float v[4];
    M1_RDF144(x, p); M1_RDF144(y, p + 4); M1_RDF144(z, p + 8);
    v[0] = x.f; v[1] = y.f; v[2] = z.f; v[3] = 1.0f;
    m1_AimAt0CF330(m1_stats41FEC0, v, 8.0f);
    return 0x200C;
}

/* 0xDB210: script op, player action by id (0xFE: walk to a fixed spot, 0xFF: stop). */
int m1_OpPlayerAct0DB210(M1Vm144 *c) {
    uint8_t *p = c->pc4; M1Hi144 h; int id; float v[4];
    h.s = 0; h.b[1] = p[1]; id = h.s | p[0];
    switch (id) {
    case 0xFE:
        v[0] = -0.286199987f; v[1] = -34.0330009f; v[2] = -2.92070007f; v[3] = 1.0f;
        m1_PlWalkTo0D23D0(v, 0);
        return 0x2002;
    case 0xFF:
        m1_PlStop0D0000();
        return 0x2002;
    }
    m1_PlAct0CF490(m1_stats41FEC0, id);
    return 0x2002;
}

int  sub_000CF790(void *s, int k);
void sub_000D9AB0(int id);
void sub_000D9B30(int id);

/* 0xDD990: script op, play one of a set of lines chosen by the last digit of stat 12. */
int m1_OpLineByStat0DD990(M1Vm144 *c) {
    float f = (float)sub_000CF790(m1_stats41FEC0, 0xC);
    int d = _mm_cvtt_ss2si(_mm_set_ss(f - (float)_mm_cvtt_ss2si(_mm_set_ss(f * 0.100000001f)) * 10.0f));
    uint8_t *p; M1Hi144 h; int id;
    if (d > 0) d--;
    p = c->pc4; h.s = 0; h.b[1] = p[1]; id = h.s | p[0];
    sub_000D9AB0(id + d / 3);
    return 0x2002;
}

typedef struct M1Pair144 { int32_t k; int32_t v; } M1Pair144;
typedef struct M1Grp144 { int32_t key; M1Pair144 e[64]; } M1Grp144;
extern M1Grp144 m1_lookup309BE8[];

/* 0xDE100: two-level id lookup; -1 when not found. */
int m1_Lookup0DE100(int a, int b) {
    int i = 0, j, key = m1_lookup309BE8[0].key; M1Pair144 *p = m1_lookup309BE8[0].e, *q;
    while (key > -1) {
        if (key == a) {
            for (j = 0, q = p; q->k > -1; q++, j++)
                if (q->k == b) return m1_lookup309BE8[i].e[j].v;
        }
        key = *(int32_t *)((uint8_t *)p + 0x200);
        p = (M1Pair144 *)((uint8_t *)p + 0x204);
        i++;
    }
    return -1;
}

typedef struct M1Bits144 { uint16_t id; uint16_t bits[6]; } M1Bits144;
extern M1Bits144 m1_flagSets300FC8[];


typedef struct M1Cmb144 {
    uint8_t unk00[0x41C]; int32_t t41C; float pts420; int32_t lvA424; int32_t lvB428;
} M1Cmb144;
typedef struct M1Hit144 { int32_t base0; int16_t off4; uint8_t unk06[6]; int32_t t0C; int32_t a10; int32_t a14; int32_t n18; } M1Hit144;
extern float m1_cmbA3185B8[9];
extern float m1_cmbB3185DC[6];
extern float m1_cmbC3185F4[5];
void sub_000E63A0(int k);
void sub_000E0B70(M1Cmb144 *c, int k, int v, int z);
void sub_000E4950(M1Cmb144 *c, float f, int n, int a, int b);

/* 0xEA7D0: add a hit to the combo meter and pop the score text. */
void m1_ComboHit0EA7D0(M1Cmb144 *c, M1Hit144 *h) {
    unsigned k;
    if (c == 0 || h == 0) return;
    if (h->t0C <= c->t41C) { c->t41C = 0; c->lvB428++; return; }
    sub_000E63A0(5);
    sub_000E0B70(c, 6, h->off4 + h->base0, 0);
    c->pts420 += m1_cmbA3185B8[c->lvB428];
    c->pts420 += m1_cmbB3185DC[c->lvA424];
    k = _mm_cvtt_ss2si(_mm_set_ss(c->pts420 * 0.00999999978f));
    if (k > 4) k = 4;
    sub_000E4950(c, (float)h->n18 * 0.00100000005f, _mm_cvtt_ss2si(_mm_set_ss(m1_cmbC3185F4[k])), h->a10, h->a14);
}

typedef struct M1Rig144 { uint8_t unk00[4]; uint32_t f4; uint8_t unk08[0xC]; uint8_t t14[4]; } M1Rig144;
typedef struct M1Ai144 { uint8_t unk00[0x4C]; uint32_t flags4C; uint8_t unk50[8]; int32_t i58; uint8_t unk5C[0x278 - 0x5C]; M1Rig144 *rig278; } M1Ai144;
typedef struct M1Q144 { uint8_t unk00[0x10]; int32_t a10; int32_t a14; int32_t a18; } M1Q144;
int  sub_001C7EE1(void);
M1Q144 *m1_Quest113430(M1Ai144 *e, int k);
void sub_00113090(void *a, M1Ai144 *e, int st);
void sub_00113CB0(void *t, float v, int z);

/* 0x11A590: start an idle wait of a random length (wake-up or patrol variant). */
void m1_AiIdleWait11A590(void *ctx, M1Ai144 *e) {
    M1Rig144 *r = e->rig278; M1Q144 *q; int st, w; float t;
    if (r->f4 & 4) {
        r->f4 &= ~4u;
        st = 0x15;
        e->i58 = 1;
        t = (float)(sub_001C7EE1() % 4001) * 0.00999999978f + 70.0f;
    } else {
        st = 0x18;
        q = m1_Quest113430(e, 2);
        q->a10 = 7; q->a14 = 3; q->a18 = 0xC4;
        t = (float)(sub_001C7EE1() % 4001) * 0.00999999978f + 60.0f;
    }
    w = _mm_cvtt_ss2si(_mm_set_ss(t));
    e->flags4C &= ~0x10u;
    sub_00113090(ctx, e, st);
    sub_00113CB0(r->t14, (float)w, 0);
}
