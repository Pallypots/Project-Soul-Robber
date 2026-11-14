/* Area m1, file 117. Names inferred. */
#include <stdint.h>

typedef struct M1Roll117 { float f00, f04; uint32_t flags08; float spd0C; } M1Roll117;
typedef struct M1Step117R { uint8_t unk00[0x58]; int32_t state58; uint8_t unk5C[0x74 - 0x5C]; float t74; } M1Step117R;
typedef struct M1Obj117R {
    uint8_t unk00[0x10];
    uint32_t flags10;          /* +0x10 */
    uint8_t unk14[0x54 - 0x14];
    float   yaw54;             /* +0x54 */
    float   f58;               /* +0x58 */
    uint8_t unk5C[0x60 - 0x5C];
    float   pos60[4];          /* +0x60 */
    uint8_t unk70[0x80 - 0x70];
    float   f80, f84;          /* +0x80 */
} M1Obj117R;
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
void m1_FxSpawn175310(void *o, const float *p, int v);
int  sub_000494D0(int id, const void *pos, int c);
int  sub_001C7EE1(void);

/* 0x00176150: roll attack: phase 0 copies +0x00 to +0x04, spawns effect 1 with sound 0x20F
 * and waits 90 frames; phase 1 unwinds +0x04 over that time while spinning 18.85 rad per
 * 90 frames, with effects at 60 and 34 frames left and sound 0x20D at the end; phase 2 jitters
 * the speed randomly and returns 1 (stop) once 10 frames past the wait. */
int m1_Roll176150(M1Obj117R *o, M1Step117R *h, M1Roll117 *s)
{
    float r;
    switch (h->state58) {
    case 0:
        s->f04 = s->f00;
        s->flags08 = 0;
        m1_FxSpawn175310(o, &s->f00, 1);
        sub_000494D0(0x20F, o->pos60, 0);
        h->state58++;
        h->t74 = 90.0f / m1_frameTime42C858 * m1_frameRate42C85C;
        return 0;
    case 1:
        o->f84 = 0.0f - s->f00 / (90.0f / m1_frameTime42C858);
        s->f04 -= s->f00 / (90.0f / m1_frameTime42C858);
        o->yaw54 += 18.849556f / (90.0f / m1_frameTime42C858);
        if (m1_frameRate42C85C * 60.0f > h->t74 && !(s->flags08 & 1)) {
            s->flags08 |= 1;
            m1_FxSpawn175310(o, &s->f00, 1);
        }
        if (m1_frameRate42C85C * 34.0f > h->t74 && !(s->flags08 & 4)) {
            s->flags08 |= 4;
            m1_FxSpawn175310(o, &s->f00, 2);
        }
        if (m1_frameRate42C85C > h->t74) {
            sub_000494D0(0x20D, o->pos60, 0);
            s->spd0C = 0.0f;
            h->state58++;
        }
        return 0;
    case 2:
        if (-10.0f / m1_frameTime42C858 * m1_frameRate42C85C > h->t74) {
            o->f80 = 0.0f - s->spd0C;
            o->flags10 &= ~1u;
            o->f58 = 0.0f;
            return 1;
        }
        r = (float)(sub_001C7EE1() % 5) * 0.100000001f;
        if (0.0f > s->spd0C) {
            s->spd0C = m1_frameTime42C858 * r + s->spd0C;
            o->f80 = m1_frameTime42C858 * r;
        } else {
            s->spd0C -= m1_frameTime42C858 * r;
            o->f80 = 0.0f - m1_frameTime42C858 * r;
        }
        return 0;
    }
    return 0;
}

typedef struct M1Own117 { uint8_t unk00[8]; int32_t kind08; } M1Own117;
typedef struct M1Cam117 {
    uint8_t unk00[0x10];
    M1Own117 *own10;           /* +0x10 */
    int32_t aim14;             /* +0x14 */
    int32_t mode18;            /* +0x18 */
    int32_t look1C;            /* +0x1C */
    float   yaw20;             /* +0x20 */
    float   pitch24;           /* +0x24 */
    int32_t tilt28;            /* +0x28 */
    float   tiltAng2C;         /* +0x2C */
} M1Cam117;
typedef struct M1Node117 { uint8_t unk00[0x40]; float m40[16]; } M1Node117;
void *sub_0001D960(void *o, int kind);
int  sub_001726C0(void *n, float *yaw, float *pitch);
void sub_001AD940(float *m);
void sub_001AD8E0(float *d, const float *s, float a);
void sub_001AD8B0(float *d, const float *s, float a);
void sub_001AD7C0(float *d, const float *a, const float *b);

/* 0x001741A0: head tracking: aim the node toward the target from 0x1726C0, turning the yaw
 * +0x20 by at most 0.5 degree per frame (half for owner kinds 7 and 0x17), giving up past
 * 50 degrees (look 3 when locked) and easing back to centre when there is no target or it is
 * within 15 degrees; pitch +0x24 follows up to 16 degrees; kind 1 adds a tilt up to pi; the
 * node matrix is then rotated by yaw and pitch. */
void m1_HeadTrack1741A0(M1Node117 *n, M1Cam117 *s)
{
    float m[16];
    float pitch;
    float ang;
    float lim, lim4, d, v;
    int r;
    M1Own117 *own = s->own10;
    sub_0001D960(own, 8);
    if (s->aim14) {
        r = sub_001726C0(n, &ang, &pitch);
        if (r == 0)
            s->look1C = 0;
        else
            s->look1C = 2;
    } else {
        r = 0;
        s->look1C = 0;
    }
    lim = m1_frameTime42C858 * 0.00872664619f;
    if (own->kind08 == 7 || own->kind08 == 0x17)
        lim *= 0.5f;
    if (r && (s->mode18 == 2 || !(ang > -0.261799395f) || !(0.261799395f > ang))) {
        d = ang - s->yaw20;
        s->look1C = 2;
        if (d > lim)
            d = lim;
        else if (0.0f - lim > d)
            d = 0.0f - lim;
        s->yaw20 += d;
        if ((s->yaw20 > 0.87266463f || -0.87266463f > s->yaw20) && s->aim14 == 2)
            s->look1C = 3;
    } else {
        lim4 = lim * 4.0f;
        s->look1C = 0;
        if (s->yaw20 > lim4)
            v = s->yaw20 - lim4;
        else if (0.0f - lim4 > s->yaw20)
            v = s->yaw20 + lim4;
        else
            v = 0.0f;
        s->yaw20 = v;
    }
    if (r) {
        d = pitch - s->pitch24;
        if (d > lim)
            d = lim;
        else if (0.0f - lim > d)
            d = 0.0f - lim;
        v = d + s->pitch24;
        s->pitch24 = v;
        if (v > 0.279252678f)
            s->pitch24 = 0.279252678f;
        else if (0.0f > v)
            s->pitch24 = 0.0f;
    } else if (s->pitch24 > lim) {
        s->pitch24 -= lim;
    } else {
        s->pitch24 = 0.0f;
    }
    if (own->kind08 == 1) {
        v = s->tiltAng2C;
        if (s->tilt28 == 0) {
            v -= m1_frameRate42C85C * 10.4719753f;
            s->tiltAng2C = v;
            if (0.0f > v)
                s->tiltAng2C = 0.0f;
        } else {
            v += m1_frameRate42C85C * 10.4719753f;
            s->tiltAng2C = v;
            if (v > 3.14159274f)
                s->tiltAng2C = 3.14159274f;
        }
        ang = s->yaw20 + s->tiltAng2C;
        if (ang > 3.14159274f)
            ang -= 6.28318548f;
    } else {
        ang = s->yaw20;
    }
    sub_001AD940(m);
    sub_001AD8E0(m, m, ang);
    sub_001AD8B0(m, m, 0.0f - s->pitch24);
    sub_001AD7C0(n->m40, n->m40, m);
}

typedef struct M1Part117 { uint8_t unk000[0x20]; float *m20; uint8_t unk024[0x14C - 0x24]; int32_t i14C; } M1Part117;
typedef struct M1Fly117 { int32_t mode00; uint8_t unk04[4]; float t08; int32_t phase0C; float vx10, vy14, vz18; } M1Fly117;
typedef struct M1Rig117 { uint8_t unk00[0xC]; uint32_t flags0C; } M1Rig117;
typedef struct M1Step117 { uint8_t unk000[0x278]; M1Rig117 *rig278; } M1Step117;
extern void *m1_scene42C8E4;
M1Part117 *sub_0001D2B0(void *o, int part);
void sub_0001D610(void *p);
void sub_00113370(void *h, void *s);
void sub_0001EB80(void *e);
void sub_0001E9B0(void *s, void *e, int a, int b, int c);
void sub_001ADA40(float *d, const float *m);
void sub_001ADBA0(float *d, const float *s, float k);
void sub_001AD7E0(float *out, const float *v);
float sub_001AD9D0(const float *a, const float *b);

/* 0x0012DA60: knock a part off (as 0x114AE0, with rig flag +0x0C 0x100 on detach). */
void m1_PartOff12DA60(void *o, M1Step117 *h, M1Fly117 *s)
{
    float d[4];
    float ax[4];
    float az[4];
    M1Part117 *p;
    ax[0] = 1.0f;
    ax[1] = 0.0f;
    ax[2] = 0.0f;
    ax[3] = 0.0f;
    az[0] = 0.0f;
    az[1] = 0.0f;
    az[2] = 1.0f;
    az[3] = 0.0f;
    p = sub_0001D2B0(o, 2);
    switch (s->phase0C) {
    case 0:
        sub_0001EB80(p);
        sub_0001E9B0(m1_scene42C8E4, p, p->i14C, 5, 0x11);
        sub_001ADA40(p->m20, p->m20 + 16);
        h->rig278->flags0C |= 0x100;
        sub_001ADBA0(d, p->m20 + 8, -1.0f);
        d[1] = 0.0f;
        sub_001AD7E0(d, d);
        sub_001ADBA0(d, d, m1_frameRate42C85C * 30.0f);
        s->vx10 = sub_001AD9D0(ax, d);
        s->vz18 = sub_001AD9D0(az, d);
        s->vy14 = m1_frameRate42C85C * -100.0f;
        s->phase0C++;
        break;
    case 1:
        p->m20[12] = s->vx10 + p->m20[12];
        p->m20[13] = s->vy14 + p->m20[13];
        p->m20[14] += s->vz18;
        s->vx10 = (1.0f - m1_frameTime42C858 * 0.0199999996f) * s->vx10;
        s->vy14 = m1_frameRate42C85C * m1_frameRate42C85C * 294.0f + s->vy14;
        s->vz18 = (1.0f - m1_frameTime42C858 * 0.0199999996f) * s->vz18;
        if (s->t08 >= 3.0f)
            s->phase0C++;
        break;
    case 2:
        sub_0001D610(p);
        if (s->mode00)
            s->mode00 = 1;
        sub_00113370(h, s);
        return;
    }
    if (s->mode00)
        s->mode00 = 2;
}
