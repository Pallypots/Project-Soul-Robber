/* Area m1, file 297: menu loops. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Bl297 { uint32_t flags0; int32_t step4; int32_t wait8; } M1Bl297;
extern float m1_fps42C964;
void sub_000A4340(int32_t w, int32_t pose);
void sub_000A4340b(int32_t w, int32_t pose);                  /* same function (alias keeps the pose-0 call) */
int32_t sub_000A4370(int32_t w);

/* 0x000AB9D0: two-pose idle loop for menu widget 1 (sibling of 0x000ABBF0 with poses 2/3 then 0/1). Command 0
   stops, 1 starts (step 10, wait 3 s), 3 stops and returns 0; otherwise run a step. Step 20 also stops. */
int32_t m1_IdleLoopAB9D0(int32_t cmd, M1Bl297 *s)
{
    int32_t st;
    if (cmd == 0) {
        s->flags0 = 0;
        s->step4 = 0;
        return 1;
    }
    if (cmd == 1) {
        s->flags0 |= 1;
        s->step4 = 10;
        s->wait8 = _mm_cvttss_si32(_mm_set_ss(m1_fps42C964 * 3.0f));
        return 1;
    }
    if (cmd == 3) {
        s->flags0 = 0;
        s->step4 = 0;
        return 0;
    }
    st = s->step4;
    switch (st) {
    case 10:
        sub_000A4340(1, 2);
        s->step4++;
        return 1;
    case 11:
        if (sub_000A4370(1)) {
            sub_000A4340(1, 3);
            s->wait8 = _mm_cvttss_si32(_mm_set_ss(m1_fps42C964 * 3.0f));
            s->step4++;
        }
        return 1;
    case 12:
        if (--s->wait8 > 0) return 1;
        s->step4 = st + 1;
        return 1;
    case 13:
        sub_000A4340b(1, 0);
        s->step4++;
        return 1;
    case 14:
        if (sub_000A4370(1)) {
            sub_000A4340(1, 1);
            s->wait8 = _mm_cvttss_si32(_mm_set_ss(m1_fps42C964 * 3.0f));
            s->step4++;
        }
        return 1;
    case 15:
        if (--s->wait8 > 0) return 1;
        s->step4 = 10;
        return 1;
    case 20:
        s->flags0 = 0;
        s->step4 = 0;
        return 0;
    }
    return 1;
}

typedef struct M1Hh297 { uint8_t unk00[0x30]; int32_t h30; } M1Hh297;
typedef struct M1Pk297 { uint8_t unk00[0xC]; uint8_t bC; } M1Pk297;
typedef struct M1Sq297 { uint8_t unk00[0x40]; int32_t st40; uint8_t unk44[0xDC]; M1Hh297 *m120; uint8_t unk124[8]; M1Pk297 *p12C; } M1Sq297;
typedef struct M1Sn297 { uint8_t unk00[4]; } M1Sn297;
extern M1Sn297 *m1_scene42C8E4;
void sub_0001EB80(M1Hh297 *m);
void sub_0001E9B0(M1Sn297 *sc, M1Hh297 *m, int32_t a, int32_t b, int32_t c);
void sub_000A4010(M1Sq297 *o, int32_t step);
int32_t sub_000833E0(int32_t h);
int32_t sub_0017C4D0(void);
void sub_000A22C0(M1Sq297 *o, M1Pk297 *p);
void sub_000A5440(M1Sq297 *o);
void sub_000A5440b(M1Sq297 *o);                               /* same function (alias keeps both finish calls) */
void sub_000ED780(M1Pk297 *p);

/* 0x0009ED40: scripted sequence for o: re-register its model and play step 1, then advance through steps 4, 5,
   6 (after the gate 0x17C4D0 opens, handing over the held item) and 3 as each animation ends; finally (or when
   aborted at stage 6, dropping an active held item) finish via 0xA5440. */
void m1_Sequence9ED40(M1Sq297 *o)
{
    M1Hh297 *m = o->m120;
    if (!m) return;
    switch (o->st40) {
    case 0:
        sub_0001EB80(m);
        sub_0001E9B0(m1_scene42C8E4, m, 0xC, 5, 0x11);
        sub_000A4010(o, 1);
        o->st40 = 1;
        return;
    case 1:
        if (!sub_000833E0(m->h30)) return;
        sub_000A4010(o, 4);
        o->st40 = 2;
        return;
    case 2:
        if (!sub_000833E0(m->h30)) return;
        sub_000A4010(o, 5);
        o->st40 = 3;
        return;
    case 3:
        if (!sub_0017C4D0()) return;
        if (o->p12C) sub_000A22C0(o, o->p12C);
        sub_000A4010(o, 6);
        o->st40 = 4;
        return;
    case 4:
        if (!sub_000833E0(m->h30)) return;
        sub_000A4010(o, 3);
        o->st40 = 5;
        return;
    case 5:
        if (!sub_000833E0(m->h30)) return;
        sub_000A5440b(o);
        return;
    case 6:
        if (o->p12C && (o->p12C->bC & 1)) sub_000ED780(o->p12C);
        sub_000A5440(o);
        return;
    }
}
