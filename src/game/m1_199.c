/* Area m1, file 199: player turn and HUD layout helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Pl199 { uint8_t unk00[0x54]; float yaw54; } M1Pl199;
typedef struct M1PlE199 { uint8_t unk00[0xA4]; float turnA4; uint8_t unkA8[0x44]; int32_t iEC; float velF0[4]; uint8_t unk100[0x10]; int32_t i110, i114; } M1PlE199;
extern float m1_frameRate42C85C;
void sub_000A34B0(int a, int b, int c);

/* 0xF1120: turn around: cancel the stop cue if it is playing, stop the player and turn by the pending amount plus pi; next pending turn -pi. */
void m1_TurnAround0F1120(M1Pl199 *o, M1PlE199 *e) {
    int32_t *z;
    if (e->iEC) { sub_000A34B0(0, 8, 0); e->iEC = 0; }
    e->velF0[0] = m1_frameRate42C85C * 0.0f;
    e->velF0[1] = m1_frameRate42C85C * 0.0f;
    e->velF0[2] = m1_frameRate42C85C * 0.0f;
    e->velF0[3] = m1_frameRate42C85C * 0.0f;
    { int32_t *volatile zv = &e->i110; z = zv; }
    z[0] = 0; z[1] = 0;
    o->yaw54 -= e->turnA4 + 3.14159274f;
    e->turnA4 = -3.14159274f;
}

extern float  m1_camLim2E6850[16];
extern float *m1_camLimA41FF78;
extern float *m1_camLimB41FF3C;
extern int32_t m1_gameMode41FF94;

/* 0xBC1D0: choose the camera swing limits: off uses the fixed sets; on fills the live sets with +/-10 and +/-15 degrees (normal) or +/-40 and +/-60 degrees (other modes). */
void m1_CamLimits0BC1D0(int on) {
    float a, b, c;
    if (!on) { m1_camLimA41FF78 = &m1_camLim2E6850[15]; m1_camLimB41FF3C = &m1_camLim2E6850[10]; return; }
    if (m1_gameMode41FF94 == 0) {
        m1_camLim2E6850[3] = 0.261799395f; a = 0.174532935f; b = -0.174532935f; c = -0.261799395f;
    } else {
        m1_camLim2E6850[3] = 1.04719758f; a = 0.698131740f; b = -0.698131740f; c = -1.04719758f;
    }
    m1_camLim2E6850[1] = a; m1_camLim2E6850[2] = b; m1_camLim2E6850[4] = c;
    m1_camLim2E6850[6] = a; m1_camLim2E6850[7] = b;
    m1_camLim2E6850[8] = a; m1_camLim2E6850[9] = b;
    m1_camLimA41FF78 = &m1_camLim2E6850[5];
    m1_camLimB41FF3C = &m1_camLim2E6850[0];
}

typedef struct M1AnE199 { uint8_t unk00[8]; int32_t i8; uint16_t wC, wE; } M1AnE199;
extern uint8_t aec_413140;
extern int32_t r2b_g3F1B1C;
extern uint8_t aec_3F118C[];
void sub_0003FC10(void *v);
int  sub_0003FA70(int snd, int k);
void sub_0003FCB0(void *v, int r, int a, float b, float c);

/* 0xE3A20: switch an object to animation slot: copy the clip header (frames, rate, flags, data) for its current set, then start the slot's voice clip (or just record it when muted). */
void m1_AnimSlot0E3A20(uint8_t *o, int slot) {
    M1AnE199 *a; int32_t set = *(int32_t *)(o + 0x318);
    if (slot >= 0 && set >= 0) a = *(M1AnE199 **)(o + 0xBC + (slot * 16 + set) * 4);
    else a = 0;
    if (a != 0) {
        *(int32_t *)(o + 0x5C) = a->wE;
        *(int32_t *)(o + 0x60) = a->i8;
        *(int32_t *)(o + 0x64) = a->wC;
        *(void **)(o + 0x68) = (uint8_t *)a + 0x10;
    } else {
        *(int32_t *)(o + 0x5C) = 0; *(int32_t *)(o + 0x60) = 0; *(int32_t *)(o + 0x64) = 0; *(void **)(o + 0x68) = 0;
    }
    if (aec_413140 != 0) {
        r2b_g3F1B1C = *(int32_t *)(o + 0x2C8 + slot * 4);
        *(int32_t *)(o + 0x314) = slot;
        return;
    }
    if (r2b_g3F1B1C != 0) {
        sub_0003FC10(aec_3F118C);
        sub_0003FCB0(aec_3F118C, sub_0003FA70(r2b_g3F1B1C, 0), 0, 20.0f, -1.0f);
    }
    *(int32_t *)(o + 0x314) = slot;
    r2b_g3F1B1C = 0;
}

float r4f_Atan1A3EB0(float t);
float r6c_AngleAdd(float a, float b);

/* 0xBC040: angle of a 2D vector (x, y) in [-pi, pi] from atan(x/y), with y nudged off zero. */
float m1_VecAngle0BC040(float *v) {
    int q = 0; float a;
    if (v[1] == 0.0f) v[1] = 9.99999997e-07f;
    a = r4f_Atan1A3EB0(v[0] / v[1]);
    if (!(a > 0.0f)) a = 0.0f - a;
    if (0.0f > v[0]) q = 1;
    if (0.0f > v[1]) q |= 2;
    switch (q) {
    case 1: return 0.0f - a;
    case 2: return r6c_AngleAdd(0.0f - a, -3.14159274f);
    case 3: return r6c_AngleAdd(a, 3.14159274f);
    }
    return a;
}

#include <intrin.h>
typedef struct M1Trk199 {
    int32_t i0, i4, i8; float fC; int32_t i10, i14, i18, i1C, i20, i24, i28, i2C;
    int32_t ids30[6]; float f48; float t4C[7]; int32_t i68;
} M1Trk199;
extern M1Trk199 r3d_objs3FE050;
float sub_00171D50(int a, int b, int c);

/* 0x17EF30: reset the tracker block: clear it, set every timer to the default length (0x171D50), ids to -1 and counters to 0. */
void m1_TrackerReset17EF30(void) {
    float t;
    __stosd((unsigned long *)&r3d_objs3FE050, 0, 0x1B);
    t = sub_00171D50(4, 0x10, 0);
    r3d_objs3FE050.t4C[0] = t; r3d_objs3FE050.t4C[1] = t; r3d_objs3FE050.t4C[2] = t; r3d_objs3FE050.t4C[3] = t;
    r3d_objs3FE050.i0 = 0;
    r3d_objs3FE050.t4C[4] = t;
    r3d_objs3FE050.i4 = 0;
    r3d_objs3FE050.t4C[5] = t;
    r3d_objs3FE050.i8 = 0;
    r3d_objs3FE050.i18 = 0;
    r3d_objs3FE050.t4C[6] = t;
    r3d_objs3FE050.i1C = 0; r3d_objs3FE050.i20 = 0; r3d_objs3FE050.i24 = 0; r3d_objs3FE050.i28 = 0; r3d_objs3FE050.i2C = 0;
    r3d_objs3FE050.i10 = 0; r3d_objs3FE050.i68 = 0;
    r3d_objs3FE050.ids30[0] = -1; r3d_objs3FE050.ids30[1] = -1; r3d_objs3FE050.ids30[2] = -1;
    r3d_objs3FE050.ids30[3] = -1; r3d_objs3FE050.ids30[4] = -1; r3d_objs3FE050.ids30[5] = -1;
    r3d_objs3FE050.i14 = -1;
    r3d_objs3FE050.fC = 0.0f; r3d_objs3FE050.f48 = 0.0f;
}
