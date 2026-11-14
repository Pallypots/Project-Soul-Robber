/* Area m1, file 125: fades and resets. Names inferred. */
#include <stdint.h>

/* Fade step on (flags, mode, step, value): while flag 1 is set, mode 0 fades the value down
 * by step to 0 (then flag 2), mode 1 fades it up to 128 (then flag 4). */
#define M1_FADE125(name, flags, mode, step, val)                    \
extern uint32_t flags;                                              \
extern int32_t mode;                                                \
extern float step, val;                                             \
void name(void)                                                     \
{                                                                   \
    uint32_t f = flags;                                             \
    float v;                                                        \
    if (!(f & 1))                                                   \
        return;                                                     \
    switch (mode) {                                                 \
    case 0:                                                         \
        v = val;                                                    \
        if (v > 0.0f) {                                             \
            v -= step;                                              \
            val = v;                                                \
            if (!(0.0f >= v))                                       \
                return;                                             \
        }                                                           \
        flags = (f & ~1u) | 2;                                      \
        step = 0.0f;                                                \
        val = 0.0f;                                                 \
        return;                                                     \
    case 1:                                                         \
        v = val;                                                    \
        if (128.0f > v) {                                           \
            v = step + v;                                           \
            val = v;                                                \
            if (!(v >= 128.0f))                                     \
                return;                                             \
        }                                                           \
        step = 0.0f;                                                \
        val = 128.0f;                                               \
        flags = (f & ~1u) | 4;                                      \
        return;                                                     \
    }                                                               \
}

/* 0x00036C90: fade A (0x3DA098). */
M1_FADE125(m1_FadeA036C90, m1_fadeA3DA098, m1_fadeA3DA09C, m1_fadeA3DA0A0, m1_fadeA3DA0B0)
/* 0x000AA000: fade B (0x3ED970). */
M1_FADE125(m1_FadeB0AA000, m1_fadeB3ED970, m1_fadeB3ED974, m1_fadeB3ED978, m1_fadeB3ED988)

typedef struct M1Anim125 { uint8_t unk00[8]; int32_t clip08; uint8_t unk0C[0x14 - 0xC]; void *mdl14; } M1Anim125;
typedef struct M1Clip125 { uint8_t unk00[0x10]; int32_t i10; } M1Clip125;
typedef struct M1Pl125 { uint8_t unk00[0x30]; M1Anim125 *anim30; uint8_t unk34[0x90 - 0x34]; float v90[4]; } M1Pl125;
extern M1Pl125 *g_playerObj;
extern int32_t m1_g42007C;
extern uint8_t m1_tbl276DBC[];
extern uint8_t m1_stats41FEC0[];
void sub_000D24A0(void *s);
void sub_000BC6F0(void *t, int a);
M1Clip125 *sub_00083120(void *a, int clip);
void sub_001AEDD0(void *m, int v);
void sub_001ADBA0(float *d, const float *s, float k);
void sub_000D04E0(void *o, const float *v);
void sub_0001D7A0(void *o);

/* 0x000BCBE0: player respawn reset: clear 0x42007C, reset the stats and table 0x276DBC, rebind
 * the current clip, and re-apply the player's +0x90 vector. */
void m1_PlayerReset0BCBE0(void)
{
    float v[4];
    M1Anim125 *a;
    v[0] = 16.0f;
    v[1] = 16.0f;
    v[2] = 16.0f;
    v[3] = 128.0f;
    m1_g42007C = 0;
    sub_000D24A0(m1_stats41FEC0);
    sub_000BC6F0(m1_tbl276DBC, 0);
    a = g_playerObj->anim30;
    sub_001AEDD0(g_playerObj->anim30->mdl14, sub_00083120(a, a->clip08)->i10);
    sub_001ADBA0(v, g_playerObj->v90, 1.0f);
    sub_000D04E0(g_playerObj, v);
    sub_0001D7A0(g_playerObj);
}
