/* Area m1, file 146: targeting helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Tgt146 { float v[4]; float a, b; } M1Tgt146;
extern uint8_t m1_stats41FEC0[];
extern uint8_t *g_playerObj;
void m1_TgtInfo0C4250(void *s, M1Tgt146 *t, float *ab);
int  sub_000EE2B0(void *t, M1Tgt146 *in, float *out);
void sub_001AD9F0(float *d, const float *a, const void *b);
void sub_001AD7E0(float *d, const float *s);
int  sub_000D3BF0(void *s, void *o, int k, float *pos, float *dir);
void sub_000F5D40(float *d, const void *s);

/* 0xF61D0: lock onto a target; returns the lock slot (or -1) and its position. */
int m1_LockOn0F61D0(void *o, void *t, int k, float *out) {
    M1Tgt146 y; float ab[2], z[4], v[4]; int r;
    if (o == 0) return -1;
    if (t == 0) return -1;
    m1_TgtInfo0C4250(m1_stats41FEC0, &y, ab);
    y.a = ab[0]; y.b = ab[1];
    if (sub_000EE2B0(t, &y, z) == 0) return -1;
    sub_001AD9F0(v, (float *)(g_playerObj + 0x60), t);
    v[3] = 0.0f; v[1] = 0.0f;
    sub_001AD7E0(v, v);
    r = sub_000D3BF0(m1_stats41FEC0, o, k, z, v);
    if (out != 0) { sub_000F5D40(out, z); out[3] = 1.0f; }
    return r;
}

typedef struct M1Fx146 { uint32_t flags00; int32_t kind04; uint8_t unk08[0xE0 - 8]; } M1Fx146;
typedef struct M1Ent146 { uint8_t unk00[4]; int32_t kind04; uint8_t unk08[0x58]; float pos60[4]; } M1Ent146;
typedef struct M1Mdl146 { uint8_t unk00[0x60]; float pos60[4]; } M1Mdl146;
typedef struct M1Act146 { uint8_t unk00[0xFD8]; M1Mdl146 *mdlFD8; } M1Act146;
void sub_001ADBA0(float *d, const float *s, float k);
void m1_FxInit0C4B70(M1Fx146 *f);
void m1_FxShotA0C5D20(M1Act146 *o, M1Ent146 *e, M1Fx146 *f, float *pos, float *dir);
void m1_FxShotB0C5E70(M1Act146 *o, M1Ent146 *e, M1Fx146 *f, float *pos, float *dir);
void m1_LockMark0C56B0(M1Ent146 *e);

/* 0xC61B0: fire a lock-on shot effect from the actor toward an entity. */
void m1_LockShot0C61B0(M1Act146 *o, M1Ent146 *e) {
    struct { float a[4]; M1Fx146 f; } l;
    l.a[0] = 0.0f; l.a[1] = 0.0f; l.a[2] = 0.0f; l.a[3] = 1.0f;
    if (e == 0) return;
    sub_001AD9F0(l.a, e->pos60, o->mdlFD8->pos60);
    l.a[1] = 0.0f; l.a[3] = 1.0f;
    sub_001AD7E0(l.a, l.a);
    sub_001ADBA0(l.a, l.a, 3.0f);
    m1_FxInit0C4B70(&l.f);
    l.f.kind04 = 0x2A;
    if (e->kind04 != 0xC) m1_FxShotA0C5D20(o, e, &l.f, e->pos60, l.a);
    else m1_FxShotB0C5E70(o, e, &l.f, e->pos60, l.a);
    m1_LockMark0C56B0(e);
}

typedef struct M1Txt146 { float x; float y; uint8_t rest[0x90]; } M1Txt146;
extern int32_t m1_mode381AB8;
extern int32_t m1_lang381884;
extern int32_t m1_busy381850;
extern int32_t m1_font413174;
extern M1Txt146 m1_txtA3819C0;
extern M1Txt146 m1_txtB381924;
void sub_0019BEB0(int f);
void sub_000150B0(M1Txt146 *t, int k);
int  sub_00017AE0(int pkt, M1Txt146 *t);
void sub_00014E80(M1Txt146 *t);
void sub_00079340(void);

/* 0x324B0: draw the two title-screen captions into the packet when the title is up. */
int m1_TitleText0324B0(int pkt) {
    int save, r;
    if (m1_mode381AB8 != 100 || m1_lang381884 != 1) return pkt;
    if (m1_busy381850 == 0) {
    save = m1_font413174;
    sub_0019BEB0(0x8000);
    m1_txtA3819C0.x = -216.0f; m1_txtA3819C0.y = 156.0f;
    sub_000150B0(&m1_txtA3819C0, 1);
    r = sub_00017AE0(pkt, &m1_txtA3819C0);
    sub_00014E80(&m1_txtA3819C0);
    m1_txtB381924.x = -70.0f; m1_txtB381924.y = 192.0f;
    sub_000150B0(&m1_txtB381924, 0);
    r = sub_00017AE0(r, &m1_txtB381924);
    sub_00014E80(&m1_txtB381924);
    m1_font413174 = save;
    sub_00079340();
    return r;
    }
    sub_00079340();
    return pkt;
}

typedef struct M1Pk146 { uint8_t *base; uint32_t *cur; int32_t n; } M1Pk146;
extern int32_t m1_scrIdx42CAC0;
extern M1Pk146 m1_scrBuf42CAC4[2];
extern uint32_t m1_vsync42C918;
extern int32_t m1_interl42CAF0;
extern int32_t m1_pktMax3E05E4;
extern uint8_t m1_fbA3DE700[], m1_fbB3DE610[], m1_fbC3DE5B0[];
void sub_000AD090();
int  sub_000586E0(int k);
void sub_00102FA0();

/* 0x4EB50: start a frame: pick the field buffer, open the packet with an end tag, track the largest packet. */
void m1_FrameBegin04EB50(void) {
    int d;
    sub_000AD090(0, 0);
    m1_interl42CAF0 = sub_000586E0(0) == 0;
    sub_00102FA0((m1_vsync42C918 & 1ull) ? m1_fbA3DE700 : m1_fbB3DE610, 0x800, 0x800, m1_interl42CAF0);
    sub_000AD090(m1_fbC3DE5B0, m1_vsync42C918);
    m1_scrBuf42CAC4[m1_scrIdx42CAC0].cur[0] = 0x70000000;
    m1_scrBuf42CAC4[m1_scrIdx42CAC0].cur[1] = 0;
    m1_scrBuf42CAC4[m1_scrIdx42CAC0].cur[2] = 0;
    m1_scrBuf42CAC4[m1_scrIdx42CAC0].cur[3] = 0;
    d = (int)((uint8_t *)m1_scrBuf42CAC4[m1_scrIdx42CAC0].cur - m1_scrBuf42CAC4[m1_scrIdx42CAC0].base);
    if (d > m1_pktMax3E05E4) m1_pktMax3E05E4 = d;
    sub_00102FA0(0);
    sub_00102FA0(&m1_scrBuf42CAC4[m1_scrIdx42CAC0]);
}
