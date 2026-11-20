/* Area m1, file 263: pickups. Names inferred. */
#include <stdint.h>

typedef struct M1Pk263 { uint32_t flags0; int32_t id4; } M1Pk263;
typedef struct M1Pl263 { uint8_t unk00[0x60]; float pos60[4]; } M1Pl263;
extern uint8_t m1_stats41FEC0[];
extern M1Pl263 *g_playerObj;
int32_t sub_000CF790(void *stats, int32_t stat);              /* read stat */
int32_t sub_000CF8E0(int32_t id);                            /* counter cap */
void sub_000260C0(int32_t a, int32_t b, int32_t n);          /* HUD gain popup */
int32_t sub_000D1E10(void *stats, int32_t idx, int32_t delta);
int32_t sub_000494D0(int32_t snd, float *pos, int32_t z);

/* 0x000A9AC0: collect pickup p: add 10 (40 for big ones) to its counter, show the gain (in tens, only up to the
   counter's cap) on the HUD, play the pickup sound at the player and mark p collected. */
void m1_CollectA9AC0(M1Pk263 *p)
{
    int32_t amt = 10, cur, add;
    cur = sub_000CF790(m1_stats41FEC0, p->id4 + 13);
    if (p->flags0 & 0x8000000)
        amt = 40;
    if (cur != sub_000CF8E0(p->id4)) {
        add = amt;
        if (amt + cur > sub_000CF8E0(p->id4))
            add = sub_000CF8E0(p->id4) - cur;
        sub_000260C0(1, 1, (add + 9) / 10);
    }
    sub_000D1E10(m1_stats41FEC0, p->id4 + 13, amt);
    sub_000494D0(0x18, g_playerObj->pos60, 0);
    p->flags0 |= 0x40000000;
}

typedef struct M1Ob263 { uint8_t unk00[0x60]; float pos60[1]; float y64; } M1Ob263;
typedef struct M1Ai263 { uint8_t unk00[0x50]; uint32_t st50; } M1Ai263;
typedef struct M1Rec263 { uint32_t flags0; uint8_t unk04[0x40]; M1Ob263 *o44; M1Ai263 *a48; float pos4C[4];
    uint8_t unk5C[4]; } M1Rec263;                                      /* 0x60 */
extern M1Rec263 m1_pool3F8418[16];
float sub_001B2770(const float *a, const float *b);           /* distance */
void sub_001671D0(M1Ob263 *o, M1Ai263 *a, int32_t st);
void sub_000F5D40(float *d, const float *s);

/* 0x00167C30: for each active record whose actor is not t, is within 50 units and 30 units of height of t, and
   is in state 3, 5 or 6, switch the actor to state 7, mark the record (0x8000000) and store t's position.
   regargs: t=EBX. */
void m1_PoolHit167C30(M1Ob263 *t)
{
    M1Ob263 **volatile pp;         /* walks &rec.o44; flags at -0x44, actor at +4, saved position at +8 */
    uint32_t *fl;
    M1Ai263 *a;
    float dy;
    uint32_t k;
    for (pp = &m1_pool3F8418[0].o44; (intptr_t)pp < (intptr_t)&m1_pool3F8418[16].o44;
         pp = (M1Ob263 **)((uint8_t *)pp + sizeof(M1Rec263))) {
        fl = (uint32_t *)((uint8_t *)pp - 0x44);
        a = *(M1Ai263 **)(pp + 1);
        if (!(*fl & 1) || pp[0] == t || !pp[0] || !a || (*fl & 0x40))
            continue;
        if (sub_001B2770(t->pos60, pp[0]->pos60) > 50.0f)
            continue;
        dy = t->y64 - pp[0]->y64;
        if (-30.0f > dy || dy > 30.0f)
            continue;
        a = *(M1Ai263 **)(pp + 1);
        k = a->st50;
        if (k >= 8)
            continue;
        if (k == 5 || k == 6 || k == 3) {
            sub_001671D0(pp[0], a, 7);
            *fl |= 0x8000000;
            sub_000F5D40((float *)(pp + 2), t->pos60);
        }
    }
}
