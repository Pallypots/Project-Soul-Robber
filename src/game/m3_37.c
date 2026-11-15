/* Area m3, batch 37. Names inferred. */
#include <stdint.h>

typedef struct M3HpM37 { uint8_t unk00[0x9C]; int st9C; uint8_t unkA0[0x1C]; int16_t hBC; uint8_t unkBE[0x2E]; int16_t hEC; uint8_t unkEE[0x86];
                         float f174, f178, f17C, f180, f184, f188, f18C; uint8_t unk190[4]; float f194, f198, f19C; int f1A0; uint8_t unk1A4[2]; int16_t h1A6; } M3HpM37;
typedef struct M3HpO37 { uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0x40]; float f54; uint8_t unk58[8]; float f60, f64, f68; int f6C;
                         uint8_t unk70[0xB8]; uint8_t b128; } M3HpO37;
extern float a50_frameUnits, a50_framesPerSecond;
M3HpM37 *afc_DispatchByType(void *o);
int  afc_NodeActive(void *n);
void afc_SetVisible(void *m, int k);
void sub_001AD7E0(float *d, const float *s);
float sub_000F7720(void *o, const float *v);
void afc_SetBothAnims(void *e, int v);

/* 0xF9770: minion hop: state 0 waits for the node then starts anim 0x11; state 1 turns toward its drift (capped at pi), moves along its arc and drifts while moving, starting anim 0x12 when it lands on flagged ground; state 2 rises until the node frees it and then resets. */
void m3_MinionHopF9770(M3HpO37 *o) {
    float r, k, v[4];
    M3HpM37 *m = afc_DispatchByType(o);
    int still = 0;
    if (m->f17C == 0.0f && m->f180 == 0.0f) still = 1;
    else if (o->b128 & 4) {
        m->f180 = 0.0f;
        m->f17C = 0.0f;
    }
    switch (m->st9C) {
    case 2:
        o->f64 = 34.0f / a50_framesPerSecond + o->f64;
        if (afc_NodeActive(o)) {
            m->hBC = 1;
            if (m->hEC) {
                m->hEC = 0;
                afc_SetVisible(m, 0);
                o->f10 &= ~0x840u;
            }
        }
        return;
    case 1:
        if (m->h1A6) {
            k = a50_frameUnits * 0.11170108f;
            v[0] = m->f17C;
            v[2] = m->f180;
            v[3] = 0.0f;
            v[1] = 0.0f;
            sub_001AD7E0(v, v);
            r = sub_000F7720(o, v);
            if (r >= 0.0) {
                if (3.1415927f - k > r) o->f54 += k;
                else m->h1A6 = 0;
            } else {
                if (r > k - 3.1415927f) o->f54 -= k;
                else m->h1A6 = 0;
            }
        }
        o->f60 = m->f194 + m->f184;
        o->f64 = m->f198 + m->f188;
        o->f68 = m->f19C + m->f18C;
        o->f6C = m->f1A0;
        m->f188 -= m->f178;
        m->f178 = m->f174 + m->f178;
        if (!still) {
            m->f184 += m->f17C;
            m->f18C = m->f180 + m->f18C;
        }
        if (0.0f > m->f188 && (o->b128 & 0x18)) {
            afc_SetBothAnims(m, 0x12);
            m->st9C++;
        }
        return;
    case 0:
        if (afc_NodeActive(o)) {
            afc_SetBothAnims(m, 0x11);
            m->st9C++;
        }
        return;
    }
}

typedef struct M3HsM37 { uint8_t unk00[0x9C]; int st9C; uint8_t unkA0[0x78]; float dir118[3]; float w124; int16_t h128; uint8_t unk12A[2]; int kind12C;
                         uint8_t unk130[0x44]; float acc174, vel178, sx17C, sz180, x184, y188, z18C, w190; float org194[4]; } M3HsM37;
typedef struct M3HsO37 { uint8_t unk00[0x54]; float yaw54; uint8_t unk58[8]; float pos60[4]; } M3HsO37;
extern uint8_t *g_playerObj;
float sub_001A3EC0(float y, float x);
void aab_Vec1AD9F0(float *d, const float *a, const float *b);
void a3c_VecCopy(float *dst, const float *src);

/* 0xFA900: start a minion hop away from the player: face away (anim 0x34) when the player is ahead within 90 degrees, else face back (anim 0x38); then set the arc for its kind (3: 32 high over 1.5 s in place, 0x23: 32 units out, 5: 48 out 13.5 high, else 25 high) from its current spot. */
void m3_MinionHopStartFA900(M3HsO37 *o) {
    float a, t, h, T, v;
    M3HsM37 *m = afc_DispatchByType(o);
    a = sub_000F7720(o, (float *)(g_playerObj + 0x60));
    aab_Vec1AD9F0(m->dir118, o->pos60, (float *)(g_playerObj + 0x60));
    m->w124 = 0.0f;
    m->dir118[1] = 0.0f;
    sub_001AD7E0(m->dir118, m->dir118);
    if ((double)1.5707964f >= a && a >= -1.5707964f) {
        afc_SetBothAnims(m, 0x34);
        m->h128 = 0;
        o->yaw54 = sub_001A3EC0(m->dir118[0], m->dir118[2]);
    } else {
        afc_SetBothAnims(m, 0x38);
        m->h128 = 1;
        t = sub_001A3EC0(m->dir118[0], m->dir118[2]) + 3.1415927f;
        o->yaw54 = t;
        if (t > (double)3.1415927f) o->yaw54 = t - 6.2831855f;
    }
    a3c_VecCopy(m->org194, o->pos60);
    m->st9C = 0;
    if (m->kind12C == 3) {
        m->sx17C = 0.0f / a50_framesPerSecond * m->dir118[0];
        m->sz180 = 0.0f / a50_framesPerSecond * m->dir118[2];
        h = 32.0f;
        T = a50_framesPerSecond * 1.5f;
    } else if (m->kind12C == 0x23) {
        m->sx17C = 32.0f / a50_framesPerSecond * m->dir118[0];
        m->sz180 = 32.0f / a50_framesPerSecond * m->dir118[2];
        h = 25.0f;
        T = a50_framesPerSecond * 0.8333f;
    } else if (m->kind12C == 5) {
        m->sx17C = 48.0f / a50_framesPerSecond * m->dir118[0];
        m->sz180 = 48.0f / a50_framesPerSecond * m->dir118[2];
        h = 13.5f;
        T = a50_framesPerSecond * 0.605f;
    } else {
        m->sx17C = 0.0f;
        m->sz180 = 0.0f;
        h = 25.0f;
        T = a50_framesPerSecond * 0.8333f;
    }
    { volatile float two = 2.0f; float g = two; v = h / T * g * g; }
    m->x184 = 0.0f;
    m->z18C = 0.0f;
    m->w190 = 0.0f;
    m->acc174 = (h - v * T * 0.5f) * 8.0f / (T * T);
    m->vel178 = v;
    m->y188 = 0.0f - v;
}

typedef struct M3DgK37 { uint8_t unk00[8]; int f8; } M3DgK37;
typedef struct M3DgO37 { uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0x1C]; M3DgK37 *p30; uint8_t unk34[0x20]; float yaw54; } M3DgO37;
typedef struct M3DgP37 { uint8_t unk00[0xAA]; int16_t hAA; } M3DgP37;
typedef struct M3DgMm37 { uint8_t unk00[0x8C]; M3DgO37 *p8C; uint8_t unk90[0x14]; int16_t hA4; uint8_t unkA6[0x46]; int16_t hEC; uint8_t unkEE[0x3E];
                          int kind12C; uint8_t unk130[0x28]; float v158[4]; float f168, f16C, f170; } M3DgMm37;
int  sub_001C7EE1(void);
M3DgP37 *sub_000FE3D0(void);
int  sub_000F6B40(void *m);
int  sub_000F6510(void *o, float ang, int dist);
void m1_AngWrap0F5ED0(float *a);
void sub_001AD940(float *m);
void sub_001AD8E0(float *d, const float *m, float a);
void sub_001AD9B0(float *d, const float *m, const float *p);
void sub_000F62C0(void *m, int k);

/* 0xF7850: maybe start a side dodge (kinds 1-3 and 14): roll against 80% (player in attack poses), 20% (player airborne) or 45%, require the player ahead within 50 degrees, probe 20 units to each side, then dodge 90 degrees to a free side (random if both free) at speed 20 (state 0xD); returns 1 when started. */
int m3_MinionDodgeF7850(M3DgMm37 *m) {
    float v[4], mt[16], a;
    int r = sub_001C7EE1() % 100;
    M3DgO37 *o;
    int lf, rt, k;
    if (!m) return 0;
    k = m->kind12C;
    o = m->p8C;
    if (k <= 0) return 0;
    if (k > 3 && k != 0xE) return 0;
    if (o->p30->f8 == 0x16 || o->p30->f8 == 0x18 || o->p30->f8 == 0x19) {
        if (r > 0x50) return 0;
    } else if (sub_000FE3D0()->hAA) {
        if (r > 0x14) return 0;
    } else if (r > 0x2D) return 0;
    if (!sub_000F6B40(m)) return 0;
    a = sub_000F7720(m->p8C, (float *)(g_playerObj + 0x60));
    if (a >= (double)0.87266463f) return 0;
    if (-0.87266463f >= a) return 0;
    v[0] = 0.0f; v[1] = 0.0f; v[2] = -20.0f; v[3] = 0.0f;
    a = -o->yaw54;
    lf = 0;
    rt = 0;
    m1_AngWrap0F5ED0(&a);
    if (sub_000F6510(m->p8C, a, 0x41A00000)) lf = 1;
    a = -o->yaw54 - 3.1415927f;
    m1_AngWrap0F5ED0(&a);
    if (sub_000F6510(m->p8C, a, 0x41A00000)) rt = 1;
    if (lf && rt) return 0;
    sub_001AD940(mt);
    if (lf) a = 1.5707964f;
    else if (rt || (sub_001C7EE1() & 1)) a = -1.5707964f;
    else a = 1.5707964f;
    a = a + o->yaw54;
    m1_AngWrap0F5ED0(&a);
    sub_001AD8E0(mt, mt, a);
    sub_001AD9B0(v, mt, v);
    sub_001AD7E0(m->v158, v);
    m->f168 = 20.0f / (40.0f / a50_framesPerSecond);
    m->f16C = 10.0f;
    m->f170 = 20.0f;
    sub_000F62C0(m, 0xD);
    m->hEC = 1;
    m->hA4 = 1;
    m->p8C->f10 |= 0x44;
    m->p8C->f10 &= ~0x220u;
    m->p8C->f10 |= 0x840;
    return 1;
}

typedef struct M3SoSt37 { uint8_t unk00[4]; uint32_t f4; uint8_t unk08[0x28]; float v30[4]; float v40[4]; float x50, y54, z58, w5C, f60, f64;
                          float f68, f6C; uint8_t unk70[4]; float f74, f78; uint8_t unk7C[0xC]; float ang88; } M3SoSt37;
typedef struct M3SoO37 { uint8_t unk00[0x4C]; uint32_t f4C; uint8_t unk50[0x24]; float f74; uint8_t unk78[0x200]; M3SoSt37 *st278; } M3SoO37;
typedef struct M3SoA37 { uint8_t unk00[0x10]; uint32_t f10; } M3SoA37;
typedef struct M3SoC37 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M3SoC37;
extern float a50_frameSeconds;
int  m1_AiSetState1456E0(void *a, void *e, int s, int t);
M3SoC37 *sub_00113400(void *o, int v);
float sub_001A3ED0(float a);

/* 0x121650: start an AI spin-out (state 1): flag it, set command 1's limits (+-20 degrees), pick a start quadrant at random and advance the spin angle, write the sway (difference of sines) into the AI input block, and set the spin rate (one turn per 5 s, hangs if it exceeds a turn). */
void m3_AiSpinOut121650(M3SoA37 *a, M3SoO37 *o) {
    float s1, c1;
    M3SoSt37 *st = o->st278;
    M3SoC37 *c;
    float t, x, y, s2, c2, w, k2, v;
    volatile float two = 2.0f;
    m1_AiSetState1456E0(a, o, 1, 0);
    a->f10 |= 0x20;
    o->f4C |= 0x70;
    st->f4 |= 0x4000;
    o->f74 = 0.5f;
    t = a50_frameUnits * 0.0087266462f;
    c = sub_00113400(o, 1);
    c->f10 = 0.34906587f;
    c->f14 = -0.34906587f;
    if (t != -1.0f) c->f18 = t;
    c->f1C = 0.0f;
    x = (sub_001C7EE1() & 1) ? 0.0f : 4.0f;
    st->ang88 = x;
    x *= 0.78539819f;
    st->ang88 = x;
    y = x * two;
    if (y > 6.2831855f) y -= 6.2831855f;
    s1 = sub_001A3ED0(x);
    c1 = sub_001A3ED0(y);
    st->ang88 = a50_frameUnits * 0.010471975f + st->ang88;
    if (st->ang88 > 6.2831855f) st->ang88 -= 6.2831855f;
    x = st->ang88;
    y = x * two;
    if (y > 6.2831855f) y -= 6.2831855f;
    s2 = sub_001A3ED0(x);
    c2 = sub_001A3ED0(y);
    st = o->st278;
    k2 = a50_frameUnits * 0.033333335f;
    w = (c2 - c1) * 15.0f;
    a3c_VecCopy(st->v40, st->v30);
    st->z58 = -w;
    st->x50 = (s2 - s1) * 30.0f;
    st->y54 = 0.0f;
    st->w5C = 1.0f;
    st->f60 = (k2 == 1.0f) ? 1.0f : 0.0f;
    st->f64 = k2;
    o->st278->f6C = a50_frameSeconds * 10.0f;
    o->st278->f68 = -15.0f;
    o->st278->f4 |= 1;
    st = o->st278;
    v = 6.2831855f / (a50_framesPerSecond * 5.0f);
    if (!(6.2831855f >= v)) for (;;) ;
    st->f4 |= 2;
    st->f74 = 7.5f;
    st->f78 = v;
}

typedef struct M3ScB37 { uint8_t unk00[0x8C]; void *p8C; uint8_t unk90[0x11C]; float t1AC; uint8_t unk1B0[0x10]; int f1C0; uint8_t unk1C4[0x60];
                         float tgt224[4]; int f234; } M3ScB37;
typedef struct M3ScO37 { uint8_t unk00[0x54]; float yaw54; } M3ScO37;
typedef struct M3ScX37 { uint8_t unk00[0x68]; float f68; } M3ScX37;
extern M3ScB37 *b10_scr;
extern float m3_zeroVec27907C[4];
void *sub_0001D2B0(void *o, int k);
uint8_t *sub_0001D0F0(void *o, int part);
void sub_001ADAF0(float *d, const float *a, const float *b);
int  sub_000ED630(int g, int id, float *pos, int a, int b);
void sub_001809B0(float *p, float k);
void sub_00101280(int k);
void sub_00101240(int k);
int  sub_000F6A80(void);
void sub_000F3D10(void *o, void *c, int mode);

/* 0x104870: screen actor step: when its charge passes 0.3 and the target is ahead within 95 degrees, fire effect 0x18 or 0x19 from its part 12; follow the target (41 per second), turn toward it at a capped rate with a matching turn anim (0x36-0x38), then hand off (mode 0x12) when high or switch mode by the player's height. */
void m3_ScrTurn104870(M3ScO37 *o, M3ScX37 *x) {
    float v[4], m[16];
    float d, k;
    M3ScB37 *b = b10_scr;
    float *t = &b->t1AC;
    volatile int an;
    int f;
    void *q;
    if (b->t1AC > 0.3f) {
        d = sub_000F7720(o, b->tgt224);
        if (1.6580628f > d && d > -1.6580628f) {
            *t = 0.0f;
            q = sub_0001D0F0(sub_0001D2B0(o, 0), 0xC);
            sub_001AD940(m);
            sub_001AD8E0(m, m, o->yaw54);
            a3c_VecCopy(v, m3_zeroVec27907C);
            sub_001AD9B0(v, m, v);
            sub_001ADAF0(v, v, (float *)((uint8_t *)q + 0x70));
            if (!(sub_001C7EE1() & 1) || !sub_000ED630(5, 0x18, v, 0, 2))
                sub_000ED630(5, 0x19, v, 0, 2);
        }
    } else *t += a50_frameSeconds;
    sub_001809B0(b->tgt224, 41.0f / a50_framesPerSecond);
    b->tgt224[1] = ((float *)g_playerObj)[0x19];
    k = a50_frameUnits * 0.0148353f;
    d = sub_000F7720(o, b->tgt224);
    if (d > k) d = k;
    else if (0.0f - k > d) d = 0.0f - k;
    o->yaw54 += d;
    m1_AngWrap0F5ED0(&o->yaw54);
    if (afc_NodeActive(o)) {
        an = 0x36;
        if (d > 0.0f) an = 0x37;
        else if (0.0f > d) an = 0x38;
        sub_00101280(an);
    }
    if (x->f68 > 4.5f) {
        void *mm = b10_scr->p8C;
        if (!mm) for (;;) ;
        sub_000F3D10(mm, b10_scr, 0x12);
        b10_scr->f1C0 = 0;
        return;
    }
    f = (((float *)g_playerObj)[0x19] > -30.0f) ? 0 : 1;
    if (f != b->f234) {
        sub_00101240(0x12);
        return;
    }
    if (sub_000F6A80()) sub_00101240(0x13);
}
