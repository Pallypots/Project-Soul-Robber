/* Area m1, file 293: helper attacks. Names inferred. */
#include <stdint.h>

typedef struct M1Hp293 { uint8_t unk00[0x6C]; int32_t mode6C; uint8_t unk70[0x1C]; void *m8C; uint8_t unk90[0x1C];
    float waitAC; uint8_t unkB0[0x10]; int32_t fC0; uint8_t unkC4[0x20]; int32_t kindE4; uint8_t unkE8[4]; int16_t roundEC;
    uint8_t unkEE[0xA]; int32_t fF8; float fFC; } M1Hp293;
extern M1Hp293 *m1_helper3F611C;
extern float m1_frameRate42C85C;
int32_t sub_000F3B50(void *m);
int32_t sub_000F6A80(void);
void sub_000FC6F0(int32_t k);                                 /* regargs: k=EAX */
void sub_000F3D10(void *m, M1Hp293 *h, int32_t st);
void sub_000FE2E0(int32_t n);
void sub_000FBA00(int32_t n);
void sub_00100020(int32_t n);

/* 0x000FD710: helper attack cycle (modes 2-5, while its model is in state 2 and nothing blocks it). When the
   wait runs out: after two rounds, finish (move 7, or state 2 when flagged) and wait 3.9 s; otherwise fire
   the next of three attack types and wait 2.75 s, or 3.9 s after the third (which ends a round). */
void m1_HelperAttackFD710(void)
{
    M1Hp293 *h = m1_helper3F611C, *g;
    int32_t mode = h->mode6C;
    if (sub_000F3B50(h->m8C) != 2) return;
    if (sub_000F6A80()) return;
    if (mode != 2 && mode != 3 && mode != 4 && mode != 5) return;
    if (!(0.0f > h->waitAC)) {
        h->waitAC = h->waitAC - m1_frameRate42C85C;
        return;
    }
    if (h->roundEC >= 2) {
        if (h->fC0 == 0) {
            sub_000FC6F0(7);
        } else {
            g = m1_helper3F611C;
            g->fF8 = 1;
            g->fFC = 0.0f;
            sub_000F3D10(g->m8C, g, 2);
        }
        h->roundEC = 0;
        h->waitAC = 3.9f;
        return;
    }
    if (h->kindE4 == 0)
        sub_000FE2E0(5);
    else if (h->kindE4 == 1)
        sub_000FBA00(5);
    else if (h->kindE4 == 2)
        sub_00100020(5);
    if (++h->kindE4 == 3) {
        h->roundEC++;
        h->kindE4 = 0;
        h->waitAC = 3.9f;
        return;
    }
    h->waitAC = 2.75f;
}
