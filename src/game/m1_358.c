/* Area m1, file 358: release everything held by the player (grabs, holds, carried items). Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Tg358 { uint8_t unk00[0x0C]; uint8_t b0C; } M1Tg358;
typedef struct M1Pc358 { uint8_t unk000[0x6C]; int32_t i6C; uint8_t unk070[0xC8 - 0x70]; void *pC8; uint8_t unk0CC[0xFC - 0xCC]; M1Tg358 *pFC[20]; } M1Pc358;
typedef struct M1It358 { uint8_t unk00[4]; int32_t i04; int32_t i08; } M1It358;
typedef struct M1Ob358 { uint8_t unk00[0x34]; uint8_t *p34; } M1Ob358;
extern void *m1_hold3F615C, *m1_hold3F6158;
M1Pc358 *sub_0001D960(void *o, int k);
void     r2c_DropTarget(M1Tg358 *t, int k);
void     sub_00189510(void *h);
M1It358 *sub_000EDB10(int k);
M1It358 *sub_000EDB90(void);                         /* regargs: continues the walk */
int      sub_000ED780(void *o);
void     sub_000F3D10(void *o, void *c, int k);
void     sub_000F3DA0(void *o, int a, int b, int c);
void     sub_000F3B00(void *o, int k);

/* 0x10D3E0: release all: drop every grabbed target (in grab mode 4), free both holds,
   remove carried items of kind 5 / type 0x15 or 0x16, reset the player's mode and pose,
   clear the push vector and re-enable it and its partner. regargs: o=ESI (hangs if null). */
void m1_ReleaseAll10D3E0(M1Ob358 *o) {
    M1Pc358 *c;
    M1Tg358 **p;
    M1It358 *x;
    float *v;
    int n;
    if (!o)
        for (;;);
    c = sub_0001D960(o, 5);
    if (c->i6C == 4) {
        p = c->pFC;
        for (n = 20; n != 0; n--, p++)
            if (*p && ((*p)->b0C & 1))
                r2c_DropTarget(*p, 0);
    }
    if (m1_hold3F615C)
        sub_00189510(m1_hold3F615C);
    if (m1_hold3F6158)
        sub_00189510(m1_hold3F6158);
    m1_hold3F615C = 0;
    m1_hold3F6158 = 0;
    for (x = sub_000EDB10(0); x; ) {
        if (x->i04 == 5 && (x->i08 == 0x15 || x->i08 == 0x16) && sub_000ED780(x))
            x = sub_000EDB10(0);
        else
            x = sub_000EDB90();
    }
    sub_000F3D10(o, sub_0001D960(o, 5), 0);
    sub_000F3DA0(o, 0, -1, 0);
    v = (float *)(o->p34 + 0x70);
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 1.0f;
    sub_000F3B00(o, 1);
    sub_000F3B00(c->pC8, 1);
}

typedef struct M1Ob358b { uint8_t unk00[0x60]; float p60[4]; uint8_t unk70[4]; float f74; } M1Ob358b;
typedef struct M1Aim358 { float pos[4]; float h; float tgt[4]; float a, b; } M1Aim358;
extern uint8_t m1_stats41FEC0[];
int  sub_000CFFB0(void);                                      /* regargs */
void sub_000F5D40(void *d, const void *s);
void m1_TgtInfo0C4250(void *s, float *tgt, float *info);
int  sub_000EE2B0(M1Aim358 *aim, const float *tgt, float *out);
int  m1_AiGoto113040(void *o, void *e, int st);

/* 0x1788D0: when a target is locked, aim from 3.5 x height below the head at it and enter
   state 3 if the throw path is clear. regargs: o=ESI. Stack arg (e). */
void m1_AiThrowCheck1788D0(void *e, M1Ob358b *o) {
    M1Aim358 s;
    float info[4];
    float out[4];
    if (sub_000CFFB0() == -1)
        return;
    sub_000F5D40(s.pos, o->p60);
    s.h = o->f74 * 3.5f;
    s.pos[1] = s.pos[1] - s.h;
    m1_TgtInfo0C4250(m1_stats41FEC0, s.tgt, info);
    s.a = info[0];
    s.b = info[1];
    if (s.a != 0.0f && s.b != 0.0f && sub_000EE2B0(&s, s.tgt, out))
        m1_AiGoto113040(o, e, 3);
}

typedef struct M1Pw358 { uint8_t unk000[0x998]; int32_t i998; int32_t i99C; float f9A0; int32_t i9A4; } M1Pw358;
typedef struct M1Pd358 { uint8_t unk00[0x64]; M1Pw358 *p64; } M1Pd358;
extern float m1_frameRate42C85C;
float sub_000F3C70(void *o);
int   sub_000F3CB0(void *o);
int   sub_000F3B90(void *o);
void  sub_000F3B30(void *o, int k);
void  sub_000F3BB0(void *o, int a, int b);
void  sub_00189610(void *o);
uint8_t *sub_0001D0F0(void *o, int k);
void  sub_000494D0(int id, void *pos, int k);
void  sub_00039820(int k);

/* 0x1077B0: power-up charge: the window timer runs down; while charging, three quick
   presses within 1.5 units each fire the burst (flag 0x40, a 4-unit hold, effect 0x1FD at
   the hand); while the burst holds keep the pose and rumble, and when it ends clear the
   flags. Returns 1 on the frame the burst fires. regargs: o=EDI. */
int m1_PowerCharge1077B0(void *o) {
    M1Pd358 *c;
    M1Pw358 *p;
    int r = 0;
    int b;
    c = (M1Pd358 *)sub_0001D960(o, 5);
    sub_000F3C70(o);
    b = sub_000F3CB0(o);
    c->p64->f9A0 = c->p64->f9A0 - m1_frameRate42C85C;
    if (0.0f >= c->p64->f9A0) {
        c->p64->f9A0 = 0.0f;
        c->p64->i9A4 = 0;
    }
    if (c->p64->i998) {
        if ((b & 1) && sub_000F3B90(o) == 2) {
            c->p64->f9A0 = 1.5f;
            c->p64->i9A4++;
            if (c->p64->i9A4 >= 3) {
                sub_000F3B00(o, 0x40);
                r = 1;
                c->p64->i99C = 1;
                c->p64->f9A0 = 4.0f;
                c->p64->i9A4 = 0;
                sub_00189610(o);
                sub_000494D0(0x1FD, sub_0001D0F0(o, 0x11) + 0x70, 0);
            }
        }
    } else if (!c->p64->i99C) {
        c->p64->f9A0 = 0.0f;
        c->p64->i9A4 = 0;
    }
    p = c->p64;
    if (p->i99C) {
        if (p->f9A0 > 0.0f) {
            sub_000F3B00(o, 4);
            sub_000F3BB0(o, 0, 0);
            sub_00039820(2);
            return r;
        }
        sub_000F3B30(o, 0x40);
        sub_000F3B30(o, 4);
        c->p64->i99C = 0;
    }
    return r;
}

typedef struct M1Cm358 { uint8_t unk000[0x140]; uint8_t *p140; } M1Cm358;
void sub_001ADBA0(float *d, const void *s, float k);       /* d = s * k */
void sub_001ADAF0(float *d, const void *a, const void *b); /* d = a + b */

/* 0x10F130: out = absolute value of the camera's reversed forward axis (+0x28) carried
   through the basis rows +0x58/+0x68/+0x78 plus +0x88 (w = 1). regargs: out=ESI o=EDI. */
void m1_CamAbsAxis10F130(float *out, M1Cm358 *o) {
    float l[4];
    float t[4];
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    out[3] = 1.0f;
    l[0] = 0.0f;
    l[1] = 0.0f;
    l[2] = 0.0f;
    l[3] = 1.0f;
    sub_001ADBA0(l, o->p140 + 0x28, -1.0f);
    sub_001ADBA0(out, o->p140 + 0x58, l[0]);
    sub_001ADBA0(t, o->p140 + 0x68, l[1]);
    sub_001ADAF0(out, t, out);
    sub_001ADBA0(t, o->p140 + 0x78, l[2]);
    sub_001ADAF0(out, t, out);
    sub_001ADAF0(out, out, o->p140 + 0x88);
    if (0.0f > out[0])
        out[0] = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(out[0]), _mm_set_ss(-1.0f)));
    if (0.0f > out[1])
        out[1] = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(out[1]), _mm_set_ss(-1.0f)));
    if (0.0f > out[2])
        out[2] = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(out[2]), _mm_set_ss(-1.0f)));
    out[3] = 1.0f;
}

void sub_00094E00(void *it);
void sub_00094E00b(void *it);   /* alias of 0x94E00: keeps the second call apart */

/* 0x10D500: for kind-0xC items of type 0x13, 0x15 or 0x17 (or 0x96) run the pickup
   handler. Stack args (unused it). */
void m1_ItemPickup10D500(void *unused, M1It358 *it) {
    if (it->i04 != 0xC)
        return;
    switch (it->i08) {
    case 0x13:
    case 0x15:
    case 0x17:
        sub_00094E00(it);
        return;
    case 0x96:
        sub_00094E00b(it);
        return;
    }
}
