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
