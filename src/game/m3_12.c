/* Area m3, file 12: camera tilt-down. Names inferred. */
#include <stdint.h>

typedef struct M3Cam12 { uint8_t unk00[0xB2]; int16_t hB2; uint8_t unkB4[4]; uint8_t *viewB8; uint8_t *outBC; float baseC0[16]; uint8_t unk100[0x18]; float tilt118; } M3Cam12;
extern M3Cam12 *m1_cam3F610C;
extern float m1_frameTime42C858;
void sub_000F3F90(int a);
void rbj_MatIdentity(float *m);
void rbj_MatRotX(float *d, const float *s, float a);
void rbj_MatMul(float *d, const float *a, const float *b);
int  afc_NodeActive(void *n);

/* 0xF4820: tilt the camera down: when animating, lower the tilt by pi/2 over 20 frame units and signal step 4 once it passes -pi/2; otherwise (when the node is active) jump straight to -pi/2 and signal step 4. The output matrix is the view times the base, rotated by the tilt. */
void m3_CamTiltF4820(void *node) {
    M3Cam12 *c = m1_cam3F610C; uint8_t *v = c->viewB8, *out = c->outBC; float m[16];
    if (c->hB2 == 0) {
        float *t = &c->tilt118;
        *t = *t - 1.5707964f / (20.0f / m1_frameTime42C858);
        if (-1.5707964f > *t) sub_000F3F90(4);
        rbj_MatIdentity(m);
        rbj_MatRotX(m, m, *t);
        rbj_MatMul((float *)(out + 0x40), (float *)(v + 0x40), c->baseC0);
        rbj_MatMul((float *)(out + 0x40), (float *)(out + 0x40), m);
        return;
    }
    if (!afc_NodeActive(node)) return;
    rbj_MatIdentity(m);
    rbj_MatRotX(m, m, -1.5707964f);
    rbj_MatMul((float *)(out + 0x40), (float *)(v + 0x40), c->baseC0);
    rbj_MatMul((float *)(out + 0x40), (float *)(out + 0x40), m);
    sub_000F3F90(4);
}

typedef struct M3Ob12 { uint8_t unk00[0x54]; float yaw54; } M3Ob12;
typedef struct M3Anim12 { uint8_t unk00[0xB8]; float waitB8; uint8_t unkBC[0x32]; int16_t hEE; } M3Anim12;
typedef struct M3Mgr12 { uint8_t unk00[0xF4]; float coolF4; } M3Mgr12;
typedef struct M3Pl12 { uint8_t unk00[0x60]; float pos60[4]; } M3Pl12;
extern M3Pl12 *g_playerObj;
M3Anim12 *afc_DispatchByType(M3Ob12 *o);
M3Mgr12 *sub_000FE3D0(void);
float rfl_TurnDelta(M3Ob12 *o, const float *target);
void afc_SetBothAnims(M3Anim12 *a, int id);
int  aab_Rand(void);
void sub_000FB580(M3Ob12 *o, int a);

/* 0xFB870: idle look-around: turn 27 degrees towards the player when the turn delta is beyond +-27 degrees (yaw wrapped), start anim 2 with a random wait of 1.7..3.2, and when the manager cooldown has run out, one time in seven trigger 0xFB580 and restart the cooldown at 6. */
void m3_IdleLookFB870(M3Ob12 *o) {
    M3Anim12 *a = afc_DispatchByType(o); M3Mgr12 *m = sub_000FE3D0(); float d, y;
    d = rfl_TurnDelta(o, g_playerObj->pos60);
    if (0.47123891f > d) {
        y = o->yaw54 + 0.47123891f;
        o->yaw54 = y;
        if (y > 3.1415927f) o->yaw54 = y - 6.2831855f;
    } else if (d > -0.47123891f) {
        y = o->yaw54 - 0.47123891f;
        o->yaw54 = y;
        if (-3.1415927f > y) o->yaw54 = y + 6.2831855f;
    }
    afc_SetBothAnims(a, 2);
    a->waitB8 = (float)(aab_Rand() % 16 + 0x11) * 0.1f;
    a->hEE = 0;
    if (0.0f >= m->coolF4 && aab_Rand() % 7 == 0) {
        sub_000FB580(o, 1);
        m->coolF4 = 6.0f;
    }
}

typedef struct M3Hop12 { uint8_t unk00[0x54]; float yaw54; uint8_t unk58[0xC]; float y64; uint8_t unk68[0xC0]; uint8_t b128; } M3Hop12;
typedef struct M3HopA12 { uint8_t unk00[0x9C]; int32_t done9C; uint8_t unkA0[0xD8]; float rise178; } M3HopA12;
typedef struct M3Ev12 { uint8_t unk00[0x68]; float t68; } M3Ev12;
extern float a50_framesPerSecond;
extern float m1_frameTime42C858;
M3HopA12 *sub_000F5F80(M3Hop12 *o);
void sub_000F63D0(float *v);
float sub_000F7720(M3Hop12 *o, const float *target);
void m1_AngWrap0F5ED0(float *a);
void sub_000F62C0(M3HopA12 *a, int id);
void sub_000F62F0(M3HopA12 *a, int id);
int  sub_000F5D00(void *n);

/* 0xFAF60: hop towards the player: rise by the hop speed (which grows by 3 per second), turn 3.5 degrees per frame unit towards the player; on landing (flags 0x18) either start anim 0x12 and finish when the event time passed 0.08, or reset the speed and play anim 9. Once finished, play anim 9 when the node is active. */
void m3_HopFAF60(M3Hop12 *o, M3Ev12 *e) {
    M3HopA12 *a = sub_000F5F80(o); float *r, d, s;
    o->y64 = o->y64 + a->rise178;
    r = &a->rise178;
    *r = 3.0f / a50_framesPerSecond + *r;
    sub_000F63D0(r);
    if (a->done9C == 0) {
        d = sub_000F7720(o, g_playerObj->pos60);
        s = m1_frameTime42C858 * 0.061086524f;
        if (!(d > 0.0f)) s = 0.0f - s;
        o->yaw54 = o->yaw54 - s;
        m1_AngWrap0F5ED0(&o->yaw54);
        if (!(o->b128 & 0x18)) return;
        if (e->t68 > 0.08f) {
            sub_000F62F0(a, 0x12);
            a->done9C = 1;
            return;
        }
        *r = 0.0f;
        sub_000F62C0(a, 9);
        return;
    }
    if (sub_000F5D00(o)) sub_000F62C0(a, 9);
}

typedef struct M3Body12 { uint8_t unk00[0x78]; float rise78; } M3Body12;
typedef struct M3Hero12 { uint8_t unk00[0x34]; M3Body12 *body34; uint8_t unk38[0x28]; float pos60[4]; uint8_t unk70[0x40]; float radB0; } M3Hero12;
typedef struct M3Scr12 { uint8_t unk00[0x8C]; M3Hero12 *hero8C; uint8_t unk90[0x11C]; float t1AC; } M3Scr12;
typedef struct M3Tgt12 { uint8_t unk00[0x60]; float pos60[4]; } M3Tgt12;
typedef struct M3Clk12 { uint8_t unk00[0x68]; float t68; } M3Clk12;
extern M3Scr12 *m1_scr3F6130;
extern float b10_frameDelta;
float rbj_Distance(const float *a, const float *b);
float r2c_DistTo(void *o, void *t, float s);
void rfl_ActorStep(void *o, float rise);
void sub_00102F10(void);
void sub_00105330(void);

/* 0x105480: chase step while the hero follows the player: gap = distance minus the hero radius (not below 0); when the player is above -30 step towards it (1.05 degrees per frame unit) and stop near 28 units, else run 0x105330 and stop near 48; also stop after 8 time units; otherwise count the chase time. */
void m3_ChaseStep105480(void *o, M3Clk12 *c) {
    M3Scr12 *s = m1_scr3F6130; M3Hero12 *h = s->hero8C; float gap, step;
    step = m1_frameTime42C858 * 0.018325957f;
    gap = rbj_Distance(h->pos60, g_playerObj->pos60) - h->radB0;
    if (0.0f > gap) gap = 0.0f;
    if (g_playerObj->pos60[1] > -30.0f) {
        r2c_DistTo(o, g_playerObj, step);
        rfl_ActorStep(o, 0.0f - m1_scr3F6130->hero8C->body34->rise78);
        if (28.0f > gap) { volatile int z; z = 0; sub_00102F10(); return; }
    } else {
        sub_00105330();
        if (48.0f > gap) { volatile int z; z = 0x60; sub_00102F10(); return; }
    }
    if (c->t68 > 8.0f) { sub_00102F10(); return; }
    s->t1AC = s->t1AC + b10_frameDelta;
}
