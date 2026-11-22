/* Area m1, file 294: script conditions. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Ob294 { uint8_t unk00[0x64]; float y64; } M1Ob294;
typedef struct M1Ai294 { uint8_t unk00[4]; M1Ob294 *t4; } M1Ai294;
typedef struct M1Ac294 { uint8_t unk00[0x278]; M1Ai294 *s278; } M1Ac294;
typedef struct M1Cd294 { int32_t who0; uint8_t unk04[0xC]; float lo10, hi14; } M1Cd294;
extern M1Ob294 *g_playerObj;
float sub_001A3F30(float x);                                   /* fabs */

/* 0x00186280: condition: is the height difference between self and the chosen object (the player, a's target or
   self, by c->who0) within [lo, hi]? Choices 2 and 5 are always false; other values hang. */
int32_t m1_CondHeight186280(M1Ob294 *self, M1Ac294 *a, M1Cd294 *c)
{
    M1Ob294 *k;
    float d;
    switch (c->who0) {
    case 1: k = g_playerObj; break;
    case 3: k = a->s278->t4; break;
    case 4: k = self; break;
    case 2: case 5: return 0;
    default: for (;;) ;
    }
    if (!k) return 0;
    d = sub_001A3F30(self->y64 - k->y64);
    if (!_mm_comige_ss(_mm_set_ss(d), _mm_load_ss(&c->lo10))) return 0;
    if (!_mm_comige_ss(_mm_load_ss(&c->hi14), _mm_set_ss(d))) return 0;
    return 1;
}

typedef struct M1Mg294 { int32_t id0; uint8_t unk04[8]; int32_t fC; float pos10[1]; float y14; } M1Mg294;
typedef struct M1Ml294 { uint8_t unk00[0x5C]; float f5C; } M1Ml294;
typedef struct M1Mo294 { uint8_t unk00[0x60]; float pos60[4]; } M1Mo294;
typedef struct M1Pp294 { uint8_t unk00[0x60]; float pos60[4]; } M1Pp294;
extern M1Pp294 *g_playerPos420E98;
M1Ml294 *sub_0001D960(M1Mo294 *o, int32_t kind);
int32_t sub_0019BE60(int32_t mask);
void sub_001AD9F0(float *d, const float *a, const float *b);   /* d = a - b */
void sub_001AD7E0(float *d, const float *s);                  /* normalise */
void *sub_00035D80(M1Mo294 *o, int32_t a, int32_t b);
void sub_00034DD0(void *h, const float *pos, const float *dir, const float *up);
void sub_000C75E0(M1Mo294 *o);
void sub_000F3BF0(M1Mo294 *o, int32_t v, int32_t a);
void sub_00025D50(int32_t a, int32_t b);

/* 0x001063C0: message handler (sibling of 0x000EEE10): ignored while input is blocked. Message 1 spawns a hit
   effect at the hit point mirrored through o (at the message's height), facing the player; messages 1-3, 5-11,
   32, 34, 35 are then taken (32 also calls 0xC75E0; 34 is refused while o's timer runs). Returns 1 if taken. */
int32_t m1_OnMsg1063C0(M1Mo294 *o, M1Mg294 *msg)
{
    M1Ml294 *l = sub_0001D960(o, 5);
    float a[4], c[4], down[4];
    if (sub_0019BE60(0x10000)) return 0;
    switch (msg->id0) {
    case 1:
        down[0] = 0.0f;
        down[2] = 0.0f;
        down[3] = 1.0f;
        down[1] = -1.0f;
        sub_001AD9F0(a, msg->pos10, o->pos60);
        sub_001AD9F0(a, o->pos60, a);
        a[1] = msg->y14;
        a[3] = 1.0f;
        sub_001AD9F0(c, g_playerPos420E98->pos60, o->pos60);
        c[3] = 1.0f;
        sub_001AD7E0(c, c);
        sub_00034DD0(sub_00035D80(o, 1, 1), a, c, down);
        /* fall through */
    case 2: case 3: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 32: case 34: case 35:
        if (msg->id0 == 32) sub_000C75E0(o);
        if (msg->id0 == 34 && l->f5C > 0.0f) return 0;
        sub_000F3BF0(o, msg->fC, 1);
        sub_00025D50(1, 1);
        return 1;
    }
    return 0;
}
