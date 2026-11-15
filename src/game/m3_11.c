/* Area m3, file 11: character voice pickers by health. Names inferred. */
#include <stdint.h>

typedef struct M3Voice11 { uint8_t unk00[0xC]; uint16_t idle[2]; uint16_t high[4]; uint16_t low[4]; } M3Voice11;
typedef struct M3Talker11 { int32_t i0; uint8_t unk04[0x2F0]; int32_t mode2F4; uint8_t unk2F8[0x1C]; int32_t ch314; uint8_t unk318[0x14]; int32_t busy32C; } M3Talker11;
typedef struct M3Hp11 { uint8_t unk00[0x54]; float hp54; float max58; } M3Hp11;
void *sub_000E23F0(int a, int b);
M3Hp11 *sub_0001D960(void *o, int kind);
int  aab_Rand(void);
void sub_000E0A80(M3Talker11 *o, int a, int b, int c, int id);

/* Shared body: play a random voice line for character slot ch: the idle pair in mode 0, else the high-health set while health is at least half, else the low-health set; zero entries are not counted. */
#define M3_VOICE_BY_HP(NAME, CH) \
void NAME(M3Talker11 *o, M3Voice11 *v) { \
    int n = 0, id; M3Hp11 *h; \
    if (o == 0 || v == 0) return; \
    h = sub_0001D960(sub_000E23F0(3, CH), 5); \
    o->busy32C = 1; \
    if (o->mode2F4 == 0) { \
        if (v->idle[0]) n = 1; \
        if (v->idle[1]) n++; \
        if (n == 0) return; \
        id = v->idle[aab_Rand() % n]; \
    } else if (h->hp54 >= h->max58 * 0.5f) { \
        if (v->high[0]) n = 1; \
        if (v->high[1]) n++; \
        if (v->high[2]) n++; \
        if (v->high[3]) n++; \
        if (n == 0) return; \
        id = v->high[aab_Rand() % n]; \
    } else { \
        if (v->low[0]) n = 1; \
        if (v->low[1]) n++; \
        if (v->low[2]) n++; \
        if (v->low[3]) n++; \
        if (n == 0) return; \
        id = v->low[aab_Rand() % n]; \
    } \
    if (id) sub_000E0A80(o, 4, o->i0, o->ch314, id); \
}

/* 0xEBAB0: voice for character slot 0. */
M3_VOICE_BY_HP(m3_VoiceHpEBAB0, 0)
/* 0xEBC30: voice for character slot 1. */
M3_VOICE_BY_HP(m3_VoiceHpEBC30, 1)
/* 0xEBDB0: voice for character slot 3. */
M3_VOICE_BY_HP(m3_VoiceHpEBDB0, 3)
/* 0xEC080: voice for character slot 7. */
M3_VOICE_BY_HP(m3_VoiceHpEC080, 7)
/* 0xEC200: voice for character slot 8. */
M3_VOICE_BY_HP(m3_VoiceHpEC200, 8)
