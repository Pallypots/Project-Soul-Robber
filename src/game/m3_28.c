/* Area m3, batch 28. Names inferred. */
#include <stdint.h>

typedef struct M3Ob28 { uint8_t unk000[0x118]; float v118[4]; volatile int16_t h128; } M3Ob28;
M3Ob28 *afc_DispatchByType(void *o);
float rfl_ActorHeading(void *o);
float sub_001A3EE0(float a);
float sub_001A3ED0(float a);
float sub_001A3F20(float a);
float sub_001AD9D0(const float *a, const float *b);
void afc_SetBothAnims(void *e, int v);
void a3c_VecCopy(float *dst, const float *src);

/* 0xFA7A0: is the actor's stored direction (flattened, flipped) within 90 degrees of its heading? Sets anim 0x32 and flag 1 if not, else anim 0x31 and flag 0. */
void m3_FacingCheckFA7A0(void *o) {
    float d, a, v[4], w[4];
    M3Ob28 *s = afc_DispatchByType(o);
    a3c_VecCopy(v, s->v118);
    v[0] *= -1.0f;
    v[2] *= -1.0f;
    v[3] = 0.0f;
    v[1] = 0.0f;
    a = rfl_ActorHeading(o);
    w[0] = sub_001A3EE0(a);
    w[2] = sub_001A3ED0(a);
    w[3] = 0.0f;
    w[1] = 0.0f;
    d = sub_001AD9D0(v, w);
    if (d > 1.0) d = 1.0f;
    else if (-1.0f > d) d = -1.0f;
    if (sub_001A3F20(d) >= 1.5707964f) {
        afc_SetBothAnims(s, 0x32);
        s->h128 = 1;
    } else {
        afc_SetBothAnims(s, 0x31);
        s->h128 = 0;
    }
}

typedef struct M3St28 { uint8_t unk00[4]; uint32_t f4; uint8_t unk08[0x10]; float f18; uint8_t unk1C[4]; int f20; } M3St28;
typedef struct M3En28 { uint8_t unk00[0x4C]; uint32_t f4C; uint8_t unk50[0x28]; float v78[3]; float f84; float x88; float y8C; float z90;
                        uint8_t unk94[0x278 - 0x94]; M3St28 *st278; } M3En28;
typedef struct M3Ai28 { uint8_t unk00[0xC]; uint32_t fC; } M3Ai28;
float sub_001A3F50(float a);
int  sub_001C7EE1(void);
void sub_001ADBA0(float *d, const float *a, float s);
void sub_00113090(void *a, void *o, int s);
void sub_00142330(void *a, void *o);

/* 0x11AA10: knock an AI back along its horizontal velocity with a random 27..33 speed, into state 0x36 (0x3B if the facing sign bit is set). */
void m3_AiKnock11AA10(M3Ai28 *a, M3En28 *o) {
    M3St28 *st = o->st278;
    float v[4], inv;
    volatile uint32_t sg;
    st->f18 = 0.0f;
    sg = st->f4 & 0x80000000u;
    inv = 1.0f / sub_001A3F50(o->x88 * o->x88 + o->z90 * o->z90);
    v[0] = o->x88 * inv;
    v[1] = 0.0f;
    v[2] = o->z90 * inv;
    v[3] = 0.0f;
    sub_001ADBA0(o->v78, v, ((float)sub_001C7EE1() * 3.0518509e-05f * 0.2f - 0.1f + 1.0f) * 30.0f);
    o->f84 = 0.0f;
    sub_00113090(a, o, sg ? 0x3B : 0x36);
    a->fC |= 0x20;
    o->f4C &= ~8u;
    if (st->f20) sub_00142330(a, o);
}

typedef struct M3Mn28 { uint8_t unk00[0x8C]; uint8_t *p8C; uint8_t unk90[4]; void *o94; uint8_t unk98[0xBC - 0x98]; int16_t hBC;
                        uint8_t unkBE[0x168 - 0xBE]; float f168, f16C, f170; uint8_t unk174[0x1B0 - 0x174]; int f1B0; } M3Mn28;
typedef struct M3Tg28 { uint8_t unk00[0x68]; float f68; } M3Tg28;
extern M3Mn28 *afc_minion;
extern uint8_t *g_playerObj;
extern float a50_frameUnits, a50_framesPerSecond;
float sub_000F7C40(void *o, void *tgt, float k);
void rfl_ActorStep(void *o, float rise);
void sub_000FE7E0(void);
void aab_Hide1D700(void *o);
float sub_001B2770(const float *a, const float *b);
void sub_001ADB60(float *d, const float *s, int k);
void sub_000F3D10(void *o, void *c, int mode);

/* 0xFEAC0: minion follow step: turn toward the player and rise; hide when the target is high or busy, else when the player is within 20 units launch a hop (speed 40, 65 per second). */
void m3_MinionFollowFEAC0(void *o, M3Tg28 *t) {
    float v[4];
    M3Mn28 *m = afc_minion;
    sub_000F7C40(o, g_playerObj, a50_frameUnits * 0.024434609f);
    rfl_ActorStep(o, 50.0f / a50_framesPerSecond);
    sub_000FE7E0();
    if (t->f68 > 2.0f) {
        aab_Hide1D700(m->o94);
        m->hBC = 1;
        return;
    }
    if (m->f1B0) {
        aab_Hide1D700(m->o94);
        m->hBC = 1;
        return;
    }
    if (20.0f > sub_001B2770((float *)(m->p8C + 0x60), (float *)(g_playerObj + 0x60))) {
        sub_001ADB60(v, v, 0x42200000);
        m->f168 = 40.0f / (65.0f / a50_framesPerSecond);
        m->f16C = 11.5f;
        m->f170 = 40.0f;
        sub_000F3D10(o, t, 0x1F);
    }
}

typedef struct M3Stg28 { uint8_t unk00[0x9C]; int f9C; int fA0; uint8_t *pA4; uint8_t unkA8[0x2E8 - 0xA8]; void *p2E8;
                         uint8_t unk2EC[0x408 - 0x2EC]; int f408; int f40C; int f410; } M3Stg28;
int  r2d_StageStreamPos(void *s);
uint8_t *r2b_TrackFind(void *s, int k, int v, int z);
void r2c_FaderC(int k, int t);
void sub_000E0B70(void *o, int a, int b, int c);
int  r1c_LookupA(void *p);
int  r1c_LookupB(void *p);
uint8_t *r2b_TrackFire(void *s, int k, int v, int z);

/* 0xE5070: when a stage stream is armed and caught up, find the track entry at the current position (or the last one fired from the lookup point) and fade toward it, then restart track 7 there. */
void m3_StageTrackE5070(M3Stg28 *s) {
    int cur, a, b;
    uint8_t *p, *last, *end;
    int *q;
    if (!s->f408 || s->f40C < s->f410) return;
    cur = r2d_StageStreamPos(s);
    p = r2b_TrackFind(s, 7, cur, 0);
    if (!p) return;
    end = s->pA4 + s->fA0 * s->f9C;
    q = (int *)(p + 0x1C);
    if (!q) return;
    if ((uint8_t *)q < end) {
        r2c_FaderC(1, *q - cur + 4000);
        sub_000E0B70(s, 7, cur, 0);
        return;
    }
    a = r1c_LookupA(s->p2E8);
    b = r1c_LookupB(s->p2E8);
    sub_000E0B70(s, 7, 0, 0);
    last = 0;
    for (p = r2b_TrackFire(s, 7, a, 0); p; p = r2b_TrackFire(s, 7, a, 0)) last = p;
    q = (int *)(last + 0x1C);
    if (last && q && (uint8_t *)q < end)
        r2c_FaderC(1, *q - a - cur + b + 4000);
    sub_000E0B70(s, 7, cur, 0);
}

typedef struct M3Rd28 { uint8_t unk00[0x78]; float f78; } M3Rd28;
typedef struct M3Ac28 { uint8_t unk00[0x34]; M3Rd28 *p34; uint8_t unk38[0x54 - 0x38]; float f54; uint8_t unk58[8]; float pos60[4];
                        uint8_t unk70[0xB0 - 0x70]; float fB0; } M3Ac28;
typedef struct M3Scr28 { uint8_t unk00[0x8C]; M3Ac28 *p8C; } M3Scr28;
extern M3Scr28 *b10_scr;
extern float r2_center3194C8[4];
void aab_Vec1AD9F0(float *d, const float *a, const float *b);
float afc_VecLengthXZ(const float *v);
float sub_000F7720(void *o, const float *v);
void m1_AngWrap0F5ED0(float *a);

/* 0x105330: screen actor drift: past 72 units from the player it turns toward the arena center direction (scaled 90/len) with a capped turn rate, else it turns toward the player; then it steps with the ride rise. */
void m3_ScrDrift105330(void) {
    float k, d, rise, dir[4], x;
    volatile int z;
    M3Ac28 *o = b10_scr->p8C;
    k = a50_frameUnits * 0.018325957f;
    rise = 0.0f - o->p34->f78;
    d = sub_001B2770(o->pos60, (float *)(g_playerObj + 0x60)) - o->fB0;
    if (0.0f > d) d = 0.0f;
    if (d > 72.0f) {
        aab_Vec1AD9F0(dir, (float *)(g_playerObj + 0x60), r2_center3194C8);
        ((void (*)(float *, const float *, float))sub_001ADB60)(dir, dir, 90.0f / afc_VecLengthXZ(dir));
        d = sub_000F7720(o, dir);
        if (d > k) x = k;
        else if (-k > d) x = -k;
        else x = d;
        o->f54 += x;
        m1_AngWrap0F5ED0(&o->f54);
        rfl_ActorStep(o, rise);
        z = 0;
        return;
    }
    sub_000F7C40(o, g_playerObj, k);
    rfl_ActorStep(o, rise);
}
