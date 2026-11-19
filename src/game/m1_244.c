/* Area m1, file 244: enemy follow-up pickers (register inputs per docs/verification.md). Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1E244 { uint8_t unk00[0x1C]; float f1C; } M1E244;
typedef struct M1S244 { uint8_t unk00[0x74]; float t74; uint8_t unk78[0x84]; float fFC, f100; uint8_t unk104[0x174];
    M1E244 *ext278; } M1S244;
typedef int (*M1Fn244)(void *o, M1S244 *s, const void *t);
extern M1Fn244 b3b_checkFns31D0B8[];
extern M1Fn244 m1_chkFn31D0C4, m1_chkFn31D0C8;
extern const uint8_t b3b_tbl2797C8[], m1_chkTbl2797F8[], m1_chkTbl279808[];
extern float a50_frameUnits, a50_frameSeconds;
void b10_AddClampF(float *v, float d, float lim);
float sub_001A3F30(float v);
void sub_00113480(M1S244 *s, int32_t k);
void sub_00113040(void *o, M1S244 *s, int32_t mode);

/* 0x00141D70: ease +0x1C toward 1 (0.002 per frame unit), then pick the follow-up mode: 0x2A if check 0 passes or the
   distance is at least 100, 0x14 if check C4 or C8 passes, 0x2B with a 60-frame timer when within 55 units and 60
   degrees, otherwise nothing; a chosen mode calls 0x113480 3 then 0x113040. */
void m1_Follow141D70(void *o, M1S244 *s)
{
    float d, ang;
    int m;
    b10_AddClampF(&s->ext278->f1C, a50_frameUnits * 0.002f, 1.0f);
    d = sub_001A3F30(s->fFC);
    ang = s->f100;
    if (b3b_checkFns31D0B8[0](o, s, b3b_tbl2797C8))
        goto far;
    if (m1_chkFn31D0C4(o, s, m1_chkTbl2797F8))
        goto near;
    if (d >= 100.0f) {
far:
        m = 0x2A;
        goto go;
    }
    if (m1_chkFn31D0C8(o, s, m1_chkTbl279808)) {
near:
        m = 0x14;
        goto go;
    }
    if (!_mm_comige_ss(_mm_set_ss(55.0f), _mm_load_ss(&d)) || !_mm_comige_ss(_mm_set_ss(1.04719758f), _mm_load_ss(&ang)))
        return;
    s->t74 = 60.0f / a50_frameUnits * a50_frameSeconds;
    m = 0x2B;
go:
    sub_00113480(s, 3);
    sub_00113040(o, s, m);
}

typedef struct M1DE244 { uint8_t unk00[0x50]; int32_t n50, n54; float f58; float v5C[3], v68; uint8_t unk6C[4]; float hp70; } M1DE244;
typedef struct M1DO244 { uint8_t unk00[0xC]; uint32_t flagsC; } M1DO244;
typedef struct M1DM244 { int32_t kind; uint8_t unk04[8]; float dmgC; uint8_t unk10[0x10]; float v20[4]; } M1DM244;
M1DE244 *sub_0001D960(M1DO244 *o, int32_t slot);
void sub_001ADB60(float *dst, const float *src, float k);

/* 0x001702B0: damage handler for effect slot 10 (hangs if missing): most hit kinds -> step 3 (kind 11 ignored in step
   4, kind 12 deals 1000x), 14 clears o flag 0x20, 26/28 set it and reset the slot's velocity (step 1), 42 blends it
   toward the message vector (step 4); subtract the damage, step 2 at 0 hp; returns 1 when handled. */
int m1_Damage1702B0(M1DO244 *o, M1DM244 *m)
{
    M1DE244 *e = sub_0001D960(o, 10);
    float dmg;
    int st = -1;
    if (!e)
        for (;;) ;
    dmg = m->dmgC;
    switch (m->kind) {
    case 11:
        if (e->n50 == 4)
            return 0;
    case 1: case 2: case 3: case 5: case 6: case 7: case 8: case 9: case 10:
    case 29: case 30: case 31: case 32: case 33: case 34: case 35: case 36:
        st = 3;
        break;
    case 12:
        dmg *= 1000.0f;
        st = 3;
        break;
    case 14:
        o->flagsC &= ~0x20u;
        break;
    case 26: case 28:
        o->flagsC |= 0x20;
        e->v5C[0] = 0.0f;
        e->v5C[1] = 0.0f;
        e->v5C[2] = 0.0f;
        e->v68 = 1.0f;
        st = 1;
        break;
    case 42:
        st = 4;
        sub_001ADB60(e->v5C, m->v20, 60.0f);
        break;
    default:
        return 0;
    }
    e->hp70 -= dmg;
    if (_mm_comige_ss(_mm_setzero_ps(), _mm_load_ss(&e->hp70))) {
        e->n50 = 2;
    } else {
        if (st < 0)
            return 1;
        if (e->n50 == st)
            return 0;
        e->n50 = st;
    }
    e->n54 = 0;
    e->f58 = 0.0f;
    return 1;
}
