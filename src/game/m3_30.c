/* Area m3, batch 30. Names inferred. */
#include <stdint.h>

typedef struct M3Snd30 { uint8_t unk00[0x60]; float x60; uint8_t unk64[4]; float z68; } M3Snd30;
typedef struct M3Mn30 { uint8_t unk00[0x9C]; int st9C; float tA0; uint8_t unkA4[0x1A8 - 0xA4]; M3Snd30 *p1A8; uint8_t unk1AC[0x10]; int16_t h1BC; } M3Mn30;
typedef struct M3Ob30 { uint8_t unk00[0x60]; float x60; uint8_t unk64[4]; float z68; } M3Ob30;
extern M3Mn30 *afc_minion;
extern float a50_frameSeconds;
void sub_000F3D10(void *o, void *c, int mode);
float sub_00194D60(void *p);
void sub_00194D30(void *p, int k);
void sub_00194D00(void *p, int k);
void sub_00194CD0(void *p, int k);
int  aab_Effect494D0(int id, const void *pos, int c);

/* 0xFF440: minion landing step: state 0 waits 2 s, snaps to its sound's spot and plays it; state 1 waits for the sound to pass 1.7 then rewinds it; state 2 plays effect 0x16F once after 0.5 s and hands off to mode 0x25 after 1 s. */
void m3_MinionLandFF440(M3Ob30 *o, void *c) {
    M3Mn30 *m = afc_minion;
    switch (m->st9C) {
    case 0:
        if (m->tA0 > 2.0f) {
            sub_00194D30(m->p1A8, 9);
            if (m->p1A8) {
                o->x60 = m->p1A8->x60;
                o->z68 = m->p1A8->z68;
            }
            sub_00194D00(m->p1A8, 1);
            sub_00194CD0(m->p1A8, 0);
            m->st9C++;
            return;
        }
        m->tA0 += a50_frameSeconds;
        return;
    case 1:
        if (!(sub_00194D60(m->p1A8) >= 1.7f)) return;
        sub_00194CD0(m->p1A8, 1);
        m->st9C++;
        m->tA0 = 0.0f;
        return;
    case 2:
        if (!m->h1BC && m->tA0 > 0.5f) {
            aab_Effect494D0(0x16F, &o->x60, 1);
            m->h1BC = 1;
        }
        if (m->tA0 > 1.0f) {
            sub_000F3D10(o, c, 0x25);
            return;
        }
        m->tA0 += a50_frameSeconds;
        return;
    default:
        sub_000F3D10(o, c, 0x25);
    }
}

typedef struct M3Scr30 { uint8_t unk00[4]; uint8_t *pc4; } M3Scr30;
typedef struct M3Ent30 { uint8_t unk00[0x60]; float pos60[4]; } M3Ent30;
extern uint8_t *g_playerObj;
M3Ent30 *sub_000DE170(int a, int b);
float sub_001B2770(const float *a, const float *b);
float sub_001B2730(const float *a, const float *b);
int  sub_00172990(void *e);
float sub_000DE1A0(void *e);
float rfl_PlayerAngleTo(const float *v);
void a3c_VecCopy(float *dst, const float *src);

/* 0xDAB70: script wait: hold (0x2004) while the player is within 50 units of entity (b0,b1), between -10 and 20 units above it, within 10 units of its edge (radius + 6) and within 60 degrees of facing; otherwise jump by the 16-bit offset and continue (0x1000). */
int m3_ScrNearDAB70(M3Scr30 *s) {
    float d, h, e2[4], p2[4], e1[4], p1[4];
    M3Ent30 *e = sub_000DE170(s->pc4[0], s->pc4[1]);
    if (!e) goto skip;
    a3c_VecCopy(p1, (float *)(g_playerObj + 0x60));
    a3c_VecCopy(p2, (float *)(g_playerObj + 0x60));
    a3c_VecCopy(e1, e->pos60);
    a3c_VecCopy(e2, e->pos60);
    d = sub_001B2770(e1, p1);
    if (d >= 50.0) goto skip;
    p2[2] = 0.0f; p2[0] = 0.0f; e2[2] = 0.0f; e2[0] = 0.0f;
    h = sub_001B2730(p2, e2);
    if (-10.0 > h) goto skip;
    if (h > 20.0f) goto skip;
    if (!sub_00172990(e)) goto skip;
    if (!(10.0f > d - (sub_000DE1A0(e) + 6.0f))) goto skip;
    h = rfl_PlayerAngleTo(e1);
    if (!(h > (double)-1.0471976f)) goto skip;
    if (!(1.0471976f > h)) goto skip;
    return 0x2004;
skip:
    {
        union { int16_t v; uint8_t b[2]; } u;
        u.v = 0;
        u.b[1] = s->pc4[3];
        s->pc4 += (u.v | s->pc4[2]) + 2;
    }
    return 0x1000;
}

typedef struct M3PlB30 { uint8_t unk00[0x20]; float fwd20[4]; } M3PlB30;
typedef struct M3PlA30 { uint8_t unk00[0x20]; M3PlB30 *b20; } M3PlA30;
typedef struct M3StC30 { uint8_t unk00[0x10]; float range10; float side14; float fwd18; float t1C; } M3StC30;
typedef struct M3StI30 { uint8_t unk00[0x30]; float v30[4]; float v40[4]; float x50, y54, z58, w5C, f60, f64; } M3StI30;
typedef struct M3StE30 { uint8_t unk00[0x278]; M3StI30 *st278; } M3StE30;
typedef struct M3StA30 { uint8_t unk00[0x60]; float pos60[4]; } M3StA30;
extern float a50_frameUnits;
void aab_Vec1AD9F0(float *d, const float *a, const float *b);
void sub_001AD7E0(float *d, const float *s);
float sub_001AD9D0(const float *a, const float *b);
float sub_001A3EE0(int a);

/* 0x12D0F0: every 0.5 s pick an input for an AI keeping its range: step in or out by side14 outside a +-5 band, and forward or back by fwd18 when the player faces it within 30 degrees; writes the move into the AI input block. */
void m3_AiStrafe12D0F0(M3StA30 *a, M3StE30 *e, M3StC30 *c) {
    float y, k, d[4], n[4], x, s;
    M3PlA30 *pl;
    M3StI30 *st;
    if (c->t1C > 0.0f) {
        c->t1C -= a50_frameSeconds;
        return;
    }
    c->t1C = 0.5f;
    pl = (M3PlA30 *)g_playerObj;
    aab_Vec1AD9F0(d, a->pos60, (float *)((uint8_t *)pl + 0x60));
    d[1] = 0.0f;
    sub_001AD7E0(n, d);
    x = sub_001AD9D0(n, d);
    if (x >= c->range10 + 5.0) x = c->side14;
    else if (c->range10 - 5.0f >= x) x = 0.0f - c->side14;
    else x = 0.0f;
    s = sub_001AD9D0(pl->b20->fwd20, n);
    if (s >= sub_001A3EE0(0x3F060A92)) y = 0.0f;
    else if (sub_001AD9D0((float *)pl->b20, n) >= 0.0f) y = 0.0f - c->fwd18;
    else y = c->fwd18;
    st = e->st278;
    k = a50_frameUnits * 0.033333335f;
    a3c_VecCopy(st->v40, st->v30);
    st->z58 = 0.0f - x;
    st->x50 = y;
    st->y54 = 0.0f;
    st->w5C = 1.0f;
    st->f60 = (k == 1.0f) ? 1.0f : 0.0f;
    st->f64 = k;
}

typedef struct M3SpA30 { uint8_t unk00[0x20]; float off20[3]; float sph2C[4]; uint8_t unk3C[0x34]; float pos70[4]; } M3SpA30;
typedef struct M3SpP30 { uint8_t unk00[0x70]; float pos70[4]; } M3SpP30;
typedef struct M3SpB30 { uint8_t unk00[0x20]; M3SpP30 *p20; uint8_t unk24[0x5C]; float push80[4]; uint8_t unk90[0x10]; float offA0[4];
                         float rB0; float hB4; } M3SpB30;
int  sub_000A2890(float *sa, float *ca, float *sb, float *cb);
float aab_Use82D70(const float *v);
void sub_001ADBA0(float *d, const float *a, float s);
void sub_001ADAF0(float *d, const float *a, const float *b);

/* 0xA1060: if body a's sphere overlaps body b's cylinder (radius rB0, height hB4), push b out horizontally by the overlap; returns 1 on contact. */
int m3_PushOutA1060(M3SpA30 *a, M3SpB30 *b) {
    float c[4], dir[4], sb[4], cb[4], sa[4], len;
    M3SpP30 *p = b->p20;
    dir[0] = 0.0f; dir[1] = 0.0f; dir[2] = 0.0f; dir[3] = 1.0f;
    sa[0] = 0.0f; sa[1] = 0.0f; sa[2] = 0.0f; sa[3] = 1.0f;
    c[0] = 0.0f; c[1] = 0.0f; c[2] = 0.0f; c[3] = 1.0f;
    sb[0] = 0.0f; sb[1] = 0.0f; sb[2] = 0.0f; sb[3] = 1.0f;
    cb[0] = 0.0f; cb[1] = 0.0f; cb[2] = 0.0f; cb[3] = 1.0f;
    a3c_VecCopy(sa, a->sph2C);
    a3c_VecCopy(c, a->pos70);
    c[0] += a->off20[0];
    c[1] += a->off20[1];
    c[2] += a->off20[2];
    sb[0] = b->rB0;
    sb[1] = b->hB4;
    sub_001ADAF0(cb, b->offA0, p->pos70);
    if (sub_000A2890(sa, c, sb, cb) <= 0) return 0;
    aab_Vec1AD9F0(dir, cb, c);
    dir[1] = 0.0f;
    len = aab_Use82D70(dir);
    sub_001AD7E0(dir, dir);
    sub_001ADBA0(dir, dir, sb[0] + sa[0] - len);
    sub_001ADAF0(b->push80, b->push80, dir);
    return 1;
}

typedef struct M3HdB30 { uint8_t unk00[0xB4]; uint8_t *mtxB4; } M3HdB30;
typedef struct M3HdM30 { uint8_t unk00[0xC8]; M3HdB30 *bC8; } M3HdM30;
typedef struct M3HdR30 { M3HdM30 *m; uint8_t unk04[0x14C]; } M3HdR30;
typedef struct M3HdO30 { uint8_t unk00[8]; int n8; uint8_t unk0C[0x14]; M3HdR30 r20[1]; } M3HdO30;
typedef struct M3HdC30 { uint8_t unk00[0xD8]; float yawD8; } M3HdC30;
void sub_001AE060(float *d, const float *m);
void sub_001AD9B0(float *d, const float *m, const float *p);
float sub_001A3EC0(float y, float x);
float sub_001A3F30(float a);
void sub_001AD940(float *m);
void sub_001AD8E0(float *d, const float *m, float a);
int  sub_000F3140(int k);
void *sub_0001D960(void *o, int kind);

/* 0x107060: turn an object's head toward the player: target yaw from the player in local space, clamped to +-45 degrees, approached at 2 degrees per call, then written as a Y rotation into every model's head bone (+0x720). */
void m3_HeadTrack107060(M3HdO30 *o) {
    float t, v[4], m[16], a;
    M3HdC30 *c = (M3HdC30 *)sub_0001D960(o, 5);
    M3HdR30 *r = o->r20;
    int i;
    uint8_t *b;
    sub_001AE060(m, (float *)((uint8_t *)o->r20[0].m + 0x40));
    sub_001AD9B0(v, m, (float *)(g_playerObj + 0x60));
    a = sub_001A3EC0(v[0] * -1.0f, v[2] * -1.0f);
    if (a >= (double)0.78539819f) a = 0.78539819f;
    else if (-0.78539819f >= a) a = -0.78539819f;
    t = a - c->yawD8;
    if (0.034906585f > sub_001A3F30(t)) c->yawD8 = a;
    else if (t > 0.0f) {
        c->yawD8 = c->yawD8 + 0.034906585f;
        if (c->yawD8 >= 0.78539819f) c->yawD8 = 0.78539819f;
    } else {
        c->yawD8 = c->yawD8 - 0.034906585f;
        if (-0.78539819f >= c->yawD8) c->yawD8 = -0.78539819f;
    }
    sub_001AD940(m);
    sub_001AD8E0(m, m, c->yawD8);
    for (i = 0; i < sub_000F3140(o->n8); i++, r++) {
        b = r->m->bC8->mtxB4 + 0x720;
        a3c_VecCopy((float *)b, m);
        a3c_VecCopy((float *)(b + 0x10), m + 4);
        a3c_VecCopy((float *)(b + 0x20), m + 8);
    }
}
