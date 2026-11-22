/* Area m1, file 296: enemy routines. Names inferred. */
#include <stdint.h>

typedef struct M1Eo296 { uint8_t unk00[0x54]; float yaw54; uint8_t unk58[0x30]; float y88; } M1Eo296;
typedef struct M1Es296 { uint32_t flags0; uint8_t unk04[0x58]; int32_t h5C; } M1Es296;
typedef struct M1Ea296 { uint8_t unk00[0x54]; int32_t st54; uint8_t unk58[4]; float t5C; uint8_t unk60[0x14]; M1Es296 *s74; } M1Ea296;
extern float m1_frameRate42C85C, m1_frameTime42C858;
void sub_001671D0(M1Eo296 *o, M1Ea296 *a, int32_t st);
void m1_FxJitter167D00(M1Ea296 *a);                           /* regargs: a=EAX */
void sub_00167D90(M1Eo296 *o);                                /* regargs: o=EAX */
void m1_PoolHit167C30(M1Eo296 *t);                            /* regargs: t=EBX */
int32_t sub_00036750(M1Eo296 *o, int32_t kind);
int32_t sub_00036750b(M1Eo296 *o, int32_t kind);             /* same function (alias keeps both branch calls) */
void sub_00033A70(int32_t h);
void sub_00033AB0(int32_t h);
void sub_000414A0(int32_t d);
int32_t sub_001C7EE1(void);                                   /* rand */

/* 0x00168B00: hop-and-turn routine. Step 0 resets the flags, swaps in the jump effect (6 when flag 0x20, else
   3) and starts a 0.5 s (1 s when charged) timer; step 1 checks hits near the end of a charged hop, then turns
   180 degrees and waits 2-4 s; step 2 sinks o until the timer runs out and returns to state 5. */
void m1_HopTurn168B00(M1Eo296 *o, M1Ea296 *a)
{
    M1Es296 *s = a->s74;
    int32_t h, d;
    switch (a->st54) {
    case 0:
        s->flags0 &= 0xEBF58A73u;
        m1_FxJitter167D00(a);
        s->flags0 |= 0x80480;
        if (s->h5C) sub_00033A70(s->h5C);
        if (s->flags0 & 0x20) {
            h = sub_00036750(o, 6);
            d = -1;
        } else {
            h = sub_00036750b(o, 3);
            d = 1;
        }
        s->h5C = h;
        sub_000414A0(d);
        sub_00033AB0(s->h5C);
        a->t5C = 0.5f;
        if (s->flags0 & 0x8000000) a->t5C = 1.0f;
        a->st54++;
        sub_00167D90(o);
        /* fall through */
    case 1:
        if ((s->flags0 & 0x8000000) && 0.2f > a->t5C)
            m1_PoolHit167C30(o);
        if (0.0f > a->t5C) {
            o->yaw54 = o->yaw54 + 3.1415927f;
            a->t5C = (float)(sub_001C7EE1() % 20 + 20) * 0.1f;
            s->flags0 &= 0xE7FFFFFFu;
            a->st54++;
        }
        return;
    case 2:
        o->y88 = o->y88 - m1_frameRate42C85C * 50.0f * m1_frameTime42C858;
        if (0.0f > a->t5C)
            sub_001671D0(o, a, 5);
        return;
    }
}
