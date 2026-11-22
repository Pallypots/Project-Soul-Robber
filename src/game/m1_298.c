/* Area m1, file 298: boss phases. Names inferred. */
#include <stdint.h>

typedef struct M1Bo298 { uint8_t unk00[0x30]; int32_t h30; } M1Bo298;
typedef struct M1Bs298 { uint8_t unk00[0x60]; int32_t stage60; } M1Bs298;
typedef struct M1Ba298 { uint8_t unk00[0x58]; int32_t st58; uint8_t unk5C[0x18]; float wait74; uint8_t unk78[0x200];
    M1Bs298 *s278; } M1Ba298;
int32_t sub_000833E0(int32_t h);
void sub_00117580(M1Bo298 *o, int32_t st);                    /* regargs: a=EDI */

/* 0x00118B70: when o's animation ends in phase 10 or 20, go to state 0xE; in phase 30 go to state 0xD and set
   the next wait by stage (3, 4.5 or 6 s; any other stage hangs). Phase 0 hangs. */
void m1_BossPhase118B70(M1Bo298 *o, M1Ba298 *a)
{
    M1Bs298 *s = a->s278;
    int32_t k;
    switch (a->st58) {
    case 0:
        for (;;) ;
    case 10:
    case 20:
        if (sub_000833E0(o->h30))
            sub_00117580(o, 0xE);
        return;
    case 30:
        if (!sub_000833E0(o->h30)) return;
        sub_00117580(o, 0xD);
        k = s->stage60;
        if (k == 0)
            a->wait74 = 3.0f;
        else if (k == 1)
            a->wait74 = 4.5f;
        else if (k == 2)
            a->wait74 = 6.0f;
        else
            for (;;) ;
        return;
    }
}

typedef struct M1Bt298 { uint8_t unk00[4]; uint8_t b4; uint8_t unk05[0x43]; float t48; } M1Bt298;
typedef struct M1Bb298 { uint8_t unk00[0x278]; M1Bt298 *s278; } M1Bb298;
int32_t sub_001154D0(M1Bb298 *a, M1Bo298 *o);                 /* regargs: a=EAX */
void sub_00117580b(M1Bo298 *o, int32_t st);                   /* aliases keep the three state calls apart */
void sub_00117580c(M1Bo298 *o, int32_t st);

/* 0x00118C60: when o's animation ends, pick the next state: 0x23 when flagged (bit 4), 9 (with a 0.3 s timer)
   when 0x1154D0 agrees, otherwise 1. */
void m1_BossNext118C60(M1Bo298 *o, M1Bb298 *a)
{
    M1Bt298 *s = a->s278;
    if (!sub_000833E0(o->h30)) return;
    if (s->b4 & 0x10) {
        sub_00117580(o, 0x23);
        return;
    }
    if (sub_001154D0(a, o)) {
        s->t48 = 0.3f;
        sub_00117580b(o, 9);
        return;
    }
    sub_00117580c(o, 1);
}
