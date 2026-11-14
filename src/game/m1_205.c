/* Area m1, file 205: collision helpers. Names inferred. */
#include <stdint.h>

float sub_001B2770(const float *a, const float *b);
void  a3c_VecCopy(float *dst, const float *src);
void  rbj_VecSub(float *dst, const float *a, const float *b);
void  sub_001ADBA0(float *dst, const float *src, float s);
void  r4c_VecAdd(float *dst, const float *a, const float *b);

/* 0xEE2B0: do sphere a (pos, radius [4]) and capsule b (pos, radius [4], height [5]) overlap? If so write their contact midpoint (when asked) and return 1. */
int m1_SphereVsCapsule0EE2B0(const float *a, const float *b, float *mid) {
    float t;
    if (a == 0 || b == 0) return 0;
    if (sub_001B2770(a, b) > b[4] + a[4]) return 0;
    if (!(b[1] >= a[1] - a[4])) return 0;
    t = b[1] - b[5];
    if (!(a[4] + a[1] >= t)) return 0;
    if (mid != 0) {
        if (a[1] > b[1]) {
            a3c_VecCopy(mid, b);
            rbj_VecSub(mid, mid, a);
        } else if (t > a[1]) {
            a3c_VecCopy(mid, b);
            mid[1] = mid[1] - b[5];
            rbj_VecSub(mid, mid, a);
        } else {
            rbj_VecSub(mid, b, a);
            mid[1] = 0.0f;
        }
        sub_001ADBA0(mid, mid, 0.5f);
        r4c_VecAdd(mid, a, mid);
    }
    return 1;
}

typedef struct M1Sp205 { uint8_t unk00[4]; int32_t bit4; int8_t b8, b9, bA; uint8_t pad; uint8_t useRotC; uint8_t unkD[0xF]; float rot1C; float pos20[3]; uint8_t unk2C[4]; } M1Sp205;
typedef struct M1SpH205 { uint8_t unk00[8]; int32_t n8; uint8_t unk0C[4]; M1Sp205 recs10[1]; } M1SpH205;
extern M1SpH205 *a80_g3ED214;
extern M1Sp205 *a80_g3ED218;
int  r2b_TestBit(int bit);
int  sub_00086250(int a, int b);
void sub_000ED630(int a, int b, float *pos, float *rot, int flags);

/* 0x87220: spawn every placed object whose story bit is set and whose slot is free, at its position and yaw, with the current record exposed while spawning. */
void m1_SpawnPlaced087220(void) {
    M1SpH205 *h = a80_g3ED214; M1Sp205 *r = h->recs10; int i;
    float rot[4], pos[4], y;
    for (i = 0; i < h->n8; i++, r++) {
        if (!r2b_TestBit(r->bit4)) continue;
        if (!sub_00086250(r->b8, r->b9)) continue;
        pos[0] = r->pos20[0]; pos[1] = r->pos20[1]; pos[2] = r->pos20[2]; pos[3] = 1.0f;
        rot[0] = 0.0f; rot[2] = 0.0f; rot[3] = 0.0f;
        y = 0.0f;
        if (r->useRotC) y = r->rot1C;
        rot[1] = y;
        a80_g3ED218 = r;
        sub_000ED630(r->b8, r->b9, pos, rot, r->bA | 0x80000000);
        a80_g3ED218 = 0;
    }
}

typedef struct M1SpD205 { int32_t id0; uint8_t unk04; int8_t b5; uint8_t kind6; int8_t scale7; int32_t bit8; int32_t argC; float pos10[3]; float rot1C; } M1SpD205;
typedef struct M1SpN205 { M1SpD205 *def0; int32_t live4; int32_t h8; } M1SpN205;
int m1_VoiceStartA93F0(int id, int b, int c, float *pos, float *rot);
int sub_000A9440(int id, int b, int c, float *pos, float *rot, float scale);

/* 0x85F90: spawn a story-gated object (kind 1 or 2) from its definition at its position and yaw, optionally scaled; remember the handle. */
void m1_SpawnDef085F90(M1SpN205 *s) {
    M1SpD205 *d = s->def0; float pos[4], rot[4];
    if (d->kind6 != 1 && d->kind6 != 2) return;
    if (!r2b_TestBit(d->bit8)) return;
    pos[0] = d->pos10[0]; pos[1] = d->pos10[1]; pos[2] = d->pos10[2]; pos[3] = 1.0f;
    rot[0] = 0.0f; rot[1] = d->rot1C; rot[2] = 0.0f; rot[3] = 0.0f;
    if (d->scale7 == 0) {
        s->h8 = m1_VoiceStartA93F0(d->id0, d->b5, d->argC, pos, rot);
        s->live4 = 1;
        return;
    }
    s->h8 = sub_000A9440(d->id0, d->b5, d->argC, pos, rot, (float)d->scale7);
    s->live4 = 1;
}
