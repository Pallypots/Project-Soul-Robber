/* Area m1, file 276: countdown. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Cd276 {                     /* 0x0037DC48 */
    int32_t phase0;
    float fade4;                             /* 60 -> 0 fade after the count */
    uint8_t alpha8;
    uint8_t unk9[3];
    float frames0C;                          /* remaining frames, shown as seconds */
} M1Cd276;
extern M1Cd276 m1_countdown37DC48;
void sub_000720A0(float *v, int32_t target);
void sub_00048AF0(int32_t snd);

/* 0x00023A70: countdown step. Phase 0 arms it; phase 1 counts the frames down, ticking (sound 0x11) each time
   the shown second drops while 30 s or less remain, and at zero starts a 60-frame fade; phase 2 runs the fade
   (alpha = fade * 2.13) and then ends. */
void m1_Countdown23A70(void)
{
    int32_t was;
    switch (m1_countdown37DC48.phase0) {
    case 0:
        m1_countdown37DC48.phase0 = 1;
        return;
    case 1:
        was = _mm_cvttss_si32(_mm_set_ss((m1_countdown37DC48.frames0C + 59.9f) * 0.016666668f));
        sub_000720A0(&m1_countdown37DC48.frames0C, 0);
        if (_mm_comige_ss(_mm_set_ss(1800.0f), _mm_load_ss(&m1_countdown37DC48.frames0C)) &&
            _mm_cvttss_si32(_mm_set_ss((m1_countdown37DC48.frames0C + 59.9f) * 0.016666668f)) < was)
            sub_00048AF0(0x11);
        if (!_mm_comige_ss(_mm_set_ss(0.0f), _mm_load_ss(&m1_countdown37DC48.frames0C))) return;
        m1_countdown37DC48.frames0C = 0.0f;
        m1_countdown37DC48.fade4 = 60.0f;
        m1_countdown37DC48.phase0++;
        return;
    case 2:
        sub_000720A0(&m1_countdown37DC48.fade4, 0);
        m1_countdown37DC48.alpha8 = (uint8_t)(int32_t)(double)(m1_countdown37DC48.fade4 * 2.1333334f);
        if (!_mm_comige_ss(_mm_set_ss(0.0f), _mm_load_ss(&m1_countdown37DC48.fade4))) return;
        m1_countdown37DC48.phase0++;
        return;
    }
}

typedef struct M1Hm276 { uint8_t unk00[8]; int32_t kind8; } M1Hm276;
typedef struct M1Bn276 { uint8_t unk00[0x70]; float pos70[4]; } M1Bn276;
typedef struct M1Ht276 { uint8_t unk00[0x50]; float v50[3]; float w5C; float pos60[4]; float s70[3]; float w7C;
    uint8_t unk80[0xCC]; int32_t f14C; } M1Ht276;
typedef struct M1Hh276 { uint8_t unk00[0x8C]; M1Hm276 *m8C; uint8_t unk90[8]; M1Ht276 *t98; uint8_t unk9C[0x5C];
    int32_t fF8; float fFC; uint8_t unk100[0x10]; int16_t w110; } M1Hh276;
typedef struct M1Sn276 { uint8_t unk00[4]; } M1Sn276;
extern M1Sn276 *m1_scene42C8E4;
extern float m1_fps42C964;
void sub_0001EB80(M1Ht276 *t);
void sub_0001E9B0(M1Sn276 *sc, M1Ht276 *t, int32_t a, int32_t b, int32_t c);
M1Bn276 *sub_0001D0F0(M1Hm276 *m, int32_t bone);
void sub_000F5D40(float *d, const float *s);

/* 0x000F65E0: re-attach h's held object: kinds 3 and 4 use hand bone 9, kind 5 bone 11, both at scale 1.25 (other
   kinds leave bone and scale undefined in the original: it reuses the argument slot). Reset the object's spin,
   set its scale, re-register it, start a 100-frame hold timer and put it on the bone. */
void m1_Reattach0F65E0(M1Hh276 *h)
{
    M1Hm276 *m;
    M1Ht276 *t;
    int32_t bone;
    union { M1Hh276 *p; float f; int32_t i; } slot;   /* XBOX32: orig reuses the 32-bit arg slot as a float */
    slot.p = h;
    if (!h) return;
    m = h->m8C;
    h->fF8 = 1;
    if (m->kind8 == 3 || m->kind8 == 4) {
        slot.f = 1.25f;
        bone = 9;
    } else if (*(volatile int32_t *)&m->kind8 == 5) {
        slot.f = 1.25f;
        bone = 0xB;
    } else {
        bone = slot.i;
    }
    t = h->t98;
    sub_0001EB80(t);
    sub_0001E9B0(m1_scene42C8E4, t, t->f14C, 5, 0x11);
    h->fFC = 100.0f / m1_fps42C964;
    h->w110 = 0;
    t->v50[2] = 0.0f;
    t->v50[1] = 0.0f;
    t->v50[0] = 0.0f;
    t->w5C = 1.0f;
    t->s70[2] = slot.f;
    t->s70[1] = slot.f;
    t->s70[0] = slot.f;
    t->w7C = 1.0f;
    sub_000F5D40(t->pos60, sub_0001D0F0(m, bone)->pos70);
}
