/* Area m1, file 299: boss phases. Names inferred. */
#include <stdint.h>

typedef struct M1Bo299 { uint8_t unk00[0x30]; int32_t h30; } M1Bo299;
typedef struct M1Bs299 { uint8_t unk00[0x19C]; int32_t stage19C; } M1Bs299;
typedef struct M1Ba299 { uint8_t unk00[0x58]; int32_t st58; uint8_t unk5C[0x18]; float wait74; uint8_t unk78[0x200];
    M1Bs299 *s278; } M1Ba299;
int32_t sub_000833E0(int32_t h);
void sub_00131310(int32_t st);                                /* regargs: o=EBX a=EDI */

/* 0x00133E60: second boss's phase step (sibling of 0x00118B70): when o's animation ends in phase 10 or 20, go to
   state 0x19; in phase 30 go to state 0x18 and set the next wait by stage (3, 4.5 or 6 s; other stages hang).
   Phase 0 hangs. */
void m1_BossPhase133E60(M1Bo299 *o, M1Ba299 *a)
{
    M1Bs299 *s = a->s278;
    int32_t k;
    switch (a->st58) {
    case 0:
        for (;;) ;
    case 10:
    case 20:
        if (sub_000833E0(o->h30))
            sub_00131310(0x19);
        return;
    case 30:
        if (!sub_000833E0(o->h30)) return;
        sub_00131310(0x18);
        k = s->stage19C;
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
