/* Area m1, file 85: approach and timer steps. Names inferred. */
#include <stdint.h>

typedef struct M1Pos85 { uint8_t unk00[0x60]; float pos60[4]; } M1Pos85;
typedef struct M1Obj85 { uint8_t unk00[0x54]; float yaw54; uint8_t unk58[0x60 - 0x58]; float pos60[4]; } M1Obj85;
typedef struct M1Step85 { uint8_t unk00[0x58]; int32_t phase58; } M1Step85;
extern M1Pos85 *g_playerObj;
extern float m1_frameTime42C858;
float sub_001B2770(const float *a, const float *b);
float sub_00113290(void *o, const float *pos);
void  sub_00113040(void *o, void *h, int state);

/* 0x00175CE0: approach: state 5 once the player is within 60 (phase 0) or 120 (phase 1);
 * otherwise turn 2 degrees per frame toward the player when more than 20 degrees off. */
void m1_Approach175CE0(M1Obj85 *o, M1Step85 *h)
{
    float *p = g_playerObj->pos60;
    float dist = sub_001B2770(o->pos60, p);
    float ang = sub_00113290(o, p);
    float lim[2];
    lim[0] = 60.0f;
    lim[1] = 120.0f;
    if (lim[h->phase58] > dist) {
        sub_00113040(o, h, 5);
        return;
    }
    if (ang > 0.34906587f)
        o->yaw54 = m1_frameTime42C858 * 0.034906585f + o->yaw54;
    else if (-0.34906587f > ang)
        o->yaw54 = o->yaw54 - m1_frameTime42C858 * 0.034906585f;
}

typedef struct M1Rig85 { uint8_t unk00[8]; float t08; int32_t step0C; } M1Rig85;
typedef struct M1Step85T { uint8_t unk000[0x278]; M1Rig85 *rig278; } M1Step85T;
typedef struct M1Obj85T { uint8_t unk00[0x9C]; float size9C; } M1Obj85T;
extern float m1_frameRate42C85C;
extern float m1_fps42C964;
int  sub_000F5D00(void *o);
void sub_000EE760(void *o, float a);
int  sub_000ED780(void *o);

/* 0x00179910: step 0 waits for 0xF5D00, step 1 waits 0.55 s, step 2 shrinks +0x9C by
 * 112 / (fps * 0.85) per frame (0xEE760(1)) and at 16 stops there and releases (0xED780). */
void m1_Shrink179910(M1Obj85T *o, M1Step85T *h)
{
    M1Rig85 *r = h->rig278;
    switch (r->step0C) {
    case 0:
        if (sub_000F5D00(o)) {
            r->step0C++;
            r->t08 = 0.0f;
        }
        break;
    case 1:
        if (r->t08 > 0.55000001f)
            r->step0C = 2;
        else
            r->t08 += m1_frameRate42C85C;
        break;
    case 2:
        sub_000EE760(o, 1.0f);
        o->size9C -= 112.0f / (m1_fps42C964 * 0.85000002f);
        if (16.0f > o->size9C) {
            o->size9C = 16.0f;
            sub_000ED780(o);
        }
        break;
    }
}

typedef struct M1Rig85R { uint8_t unk00[0x24]; int16_t w24; uint8_t unk26[0x2C - 0x26]; float f2C; float f30; } M1Rig85R;
typedef struct M1Step85R { uint8_t unk000[0x50]; int32_t state50; uint8_t unk054[0x278 - 0x54]; M1Rig85R *rig278; } M1Step85R;
typedef struct M1Obj85R {
    uint8_t unk00[0xC];
    uint32_t flags0C;          /* +0x0C */
    uint32_t flags10;          /* +0x10 */
    uint8_t unk14[0x30 - 0x14];
    void   *anim30;            /* +0x30 */
    uint8_t unk34[0x50 - 0x34];
    float   q50[4];            /* +0x50 */
    float   pos60[4];          /* +0x60 */
    float   s70[3];            /* +0x70 */
} M1Obj85R;
void sub_000F3FD0(void *o);
void sub_0001D700(void *o);
void sub_000832D0(void *a, int v);
void *sub_00036750(void *o, int b);
void sub_00034D70(void *fx, float t);
int  sub_000494D0(int id, const void *pos, int c);

/* 0x0017CC00: respawn: o flags (+0x10 clear 0x200 set 0x84D, +0xC clear 0x200), reset
 * rotation and scale, 0xF3FD0, rig +0x2C = 2, 0x1D700, rig +0x24 = 3, clip 0, rig +0x30 =
 * 1 (state 7) or 3 (state 8), effect 0 with that time, looping sound 0x1F8. */
void m1_Respawn17CC00(M1Obj85R *o, M1Step85R *h)
{
    M1Rig85R *r = h->rig278;
    o->flags10 = (o->flags10 & ~0x200u) | 0x84D;
    o->flags0C &= ~0x200u;
    o->q50[0] = 0.0f;
    o->q50[1] = 0.0f;
    o->q50[2] = 0.0f;
    o->q50[3] = 1.0f;
    o->s70[2] = 1.0f;
    o->s70[1] = 1.0f;
    o->s70[0] = 1.0f;
    sub_000F3FD0(o);
    r->f2C = 2.0f;
    sub_0001D700(o);
    r->w24 = 3;
    sub_000832D0(o->anim30, 0);
    if (h->state50 == 7)
        r->f30 = 1.0f;
    else if (h->state50 == 8)
        r->f30 = 3.0f;
    sub_00034D70(sub_00036750(o, 0), r->f30);
    sub_000494D0(0x1F8, o->pos60, 1);
}

typedef struct M1Pl85 { uint8_t unk00[0x20]; float *node20; uint8_t unk24[0x60 - 0x24]; float pos60[4]; } M1Pl85;
extern uint8_t m1_stats41FEC0[];
int   sub_000CF560(void *s, int v);
void  sub_001ADBA0(float *d, const float *s, float k);
void  sub_001AD9F0(float *out, const float *a, const float *b);
void  sub_001AD7E0(float *out, const float *v);
float sub_001AD9D0(const float *a, const float *b);
float sub_001A3EE0(float a);

/* 0x0012DDE0: behind check: when 0xCF560 holds and the object is within 40 of the player,
 * returns 1 when it lies within 0x1A3EE0(45) of the player's back direction (flat). */
int m1_BehindPlayer12DDE0(M1Obj85 *o)
{
    M1Pl85 *p = (M1Pl85 *)g_playerObj;
    float d;
    float b[4];
    float a[4];
    if (!sub_000CF560(m1_stats41FEC0, 0))
        return 0;
    if (sub_001B2770(o->pos60, p->pos60) >= 40.0f)
        return 0;
    sub_001ADBA0(a, p->node20 + 8, -1.0f);
    sub_001AD9F0(b, o->pos60, p->pos60);
    a[1] = 0.0f;
    b[1] = 0.0f;
    sub_001AD7E0(a, a);
    sub_001AD7E0(b, b);
    d = sub_001AD9D0(a, b);
    if (sub_001A3EE0(45.0f) > d)
        return 0;
    return 1;
}

typedef struct M1Ring34 { float ang00; uint8_t unk04[0x34 - 4]; } M1Ring34;
extern M1Ring34 m1_ring3FE3C4[4];
uint8_t *sub_00100110(void);
void  sub_000F5D40(float *d, const float *s);
float sub_001A3ED0(float a);
int   sub_000ED630(int a, int b, const float *pos, int c, int i);

/* 0x00184530: ring spawn: copy the player position into the camera target (+0x1EC of
 * 0x100110) and spawn four kind 4/6 objects on a 45 radius circle around the player at
 * height 15, a quarter turn apart (angles kept in table 0x3FE3C4). */
void m1_RingSpawn184530(void)
{
    float a;
    float v[4];
    uint8_t *c = sub_00100110();
    float *p = g_playerObj->pos60;
    int i;
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 1.0f;
    a = 0.0f;
    sub_000F5D40((float *)(c + 0x1EC), p);
    for (i = 0; i < 4; i++) {
        m1_ring3FE3C4[i].ang00 = a;
        v[0] = sub_001A3EE0(a) * 45.0f + p[0];
        v[2] = sub_001A3ED0(a) * 45.0f + p[2];
        v[1] = 15.0f;
        sub_000ED630(4, 6, v, 0, i);
        a = a + 1.5707964f;
    }
}
