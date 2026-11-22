/* Area m1, file 290: playback clamps. Names inferred. */
#include <stdint.h>

typedef struct M1Key290 { uint8_t unk00[0x1C]; float *t1C; } M1Key290;
typedef struct M1Pb290 { uint32_t flags0; uint8_t unk04[4]; float end8; float prevC; float cur10; uint8_t unk14[4];
    int32_t sec18; } M1Pb290;
void sub_00089460(void);
void sub_000895A0(M1Pb290 *p, int32_t sec, M1Key290 **pair);  /* keys around section sec */

/* 0x00089B50: set playback p's time to t, clamped to [0, end]. In section mode (flag 0x20) the limits are the
   section's start and end keys, and reaching the end parks just before it (end - 0.001). The previous time is
   kept in prevC. */
void m1_SetPlayTime89B50(M1Pb290 *p, float t)
{
    float lo = 0.0f, hi, v;
    M1Key290 *pair[2];
    sub_00089460();
    hi = p->end8;
    if (p->flags0 & 0x20) {
        sub_000895A0(p, p->sec18, pair);
        if (pair[0])
            lo = pair[0]->t1C[0];
        if (pair[1])
            hi = pair[1]->t1C[0];
    }
    v = t;
    if (lo > v) v = lo;
    if (p->flags0 & 0x20) {
        if (v >= hi) {
            p->prevC = p->cur10;
            p->cur10 = hi - 0.001f;
            return;
        }
    } else if (v > hi) {
        v = hi;
    }
    p->prevC = p->cur10;
    p->cur10 = v;
}

typedef struct M1Tk290 { int32_t grp0; uint8_t unk04[0xC]; } M1Tk290;                       /* 0x10 */
typedef struct M1Gp290 { uint8_t unk00[0x10]; int8_t first10, n11; uint8_t unk12[6]; } M1Gp290;   /* 0x18 */
typedef struct M1Vc290 { int32_t on0; uint8_t unk04[0xC]; int32_t state10; uint8_t unk14[0x24]; } M1Vc290;   /* 0x38 */
extern M1Tk290 m1_trk330F30[0x77];
extern M1Gp290 m1_grp3316A0[];
extern M1Vc290 m1_voice401D70[0x2D];
int32_t sub_00199CA0(int32_t t);
int32_t sub_001AB0A0(int32_t v);

/* 0x00199F70: is track t still sounding? -1 gives 0 (and other out-of-range values hang). Tracks not in state 2
   count as sounding; otherwise any voice of the track's group in state -1, 0, 1, 3 or 4 (a missing or
   unassigned voice counts as -1, a voice reported by 0x1AB0A0 as 7) makes it sounding. */
int32_t m1_TrackBusy199F70(int32_t t)
{
    M1Gp290 *g;
    M1Vc290 *v;
    int32_t busy, i, k;
    volatile int32_t vt, vk, st;   /* keep the separate range tests and the state-7 store */
    if (t == -1) return 0;
    vt = t;
    if (vt <= -1 || vt >= 0x77) for (;;) ;
    g = &m1_grp3316A0[m1_trk330F30[t].grp0];
    if (sub_00199CA0(t) != 2) return 1;
    busy = 0;
    for (i = 0; i < g->n11; i++) {
        k = g->first10 + i;
        vk = k;
        if (vk < 0 || vk >= 0x2D || !(v = &m1_voice401D70[k])->on0 || v->state10 < 0)
            st = -1;
        else if (sub_001AB0A0(k))
            st = 7;
        else
            st = v->state10;
        switch (st) {
        case -1: case 0: case 1: case 3: case 4:
            busy = 1;
            break;
        }
    }
    return busy;
}
