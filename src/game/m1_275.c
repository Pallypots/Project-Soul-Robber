/* Area m1, file 275: rewards and checks. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Ob275 { uint8_t unk00[0x60]; float x60, y64, z68, w6C; uint8_t unk70[0x68]; float dD8, dDC, dE0;
    uint8_t unkE4[4]; float rE8; } M1Ob275;
typedef struct M1Sp275 { float pos[4]; float r; } M1Sp275;
typedef struct M1Vw275 { float a[4]; float b[2]; } M1Vw275;
extern uint8_t m1_stats41FEC0[];
void sub_000C4250(void *stats, M1Vw275 *a, float *b);
int32_t sub_000EE2B0(M1Sp275 *s, M1Vw275 *v, int32_t z);
int32_t sub_000CF790(void *stats, int32_t stat);
int32_t sub_000D1F40(int32_t n);

/* 0x0017AE00: when o's bounding sphere is on screen, grant a reward scaled from stat 12 (5% of it, clamped to
   1..100) and return 0xD1F40's result; otherwise 0. regargs: o=ESI. */
int32_t m1_RewardIfSeen17AE00(M1Ob275 *o)
{
    M1Vw275 v;
    float b[4], f;
    M1Sp275 s;
    sub_000C4250(m1_stats41FEC0, &v, b);
    v.b[0] = b[0];
    v.b[1] = b[1];
    s.pos[0] = o->dD8 + o->x60;
    s.pos[1] = o->y64 + o->dDC;
    s.pos[2] = o->z68 + o->dE0;
    s.pos[3] = o->w6C;
    s.r = o->rE8;
    if (sub_000EE2B0(&s, &v, 0)) {
        f = (float)sub_000CF790(m1_stats41FEC0, 0xC) * 0.05f;
        if (f > 0.0f) {
            if (1.0f > f)
                f = 1.0f;
            else if (f > 100.0f)
                f = 100.0f;
            { float g = *(volatile float *)&f; return sub_000D1F40(_mm_cvttss_si32(_mm_set_ss(g))); }   /* volatile join keeps a single call */
        }
    }
    return 0;
}

typedef struct M1Hs275 { uint8_t unk00[0x38]; int32_t f38; uint8_t unk3C[0x14]; uint32_t flags50; int32_t f54; } M1Hs275;
typedef struct M1Hl275 { uint8_t unk00[0x20]; uint32_t b20; uint8_t unk24[0x254]; M1Hs275 *s278; } M1Hl275;
typedef struct M1He275 { uint8_t unk00[4]; int32_t kind4; int32_t sub8; uint8_t bC; } M1He275;
M1Hl275 *sub_0001D960(M1He275 *e, int32_t kind);
void sub_00147580(M1He275 *obj, int32_t st, M1Hl275 *act);   /* regargs: st=EBX act=ESI */
void sub_00147580b(M1He275 *obj, int32_t st, M1Hl275 *act);  /* same function (alias keeps the reset calls apart) */

/* 0x00147FD0: hit reaction for an active kind-2/7 object e: hits 0, 1 and 3 clear its guard bit; unless it is
   in the reacting state (flag 0x100), a type-1 hit on a grounded actor only marks it (0x200). Otherwise, with a
   target set, pick the reaction for hit type k (0-4) and start it. */
void m1_HitReaction147FD0(M1He275 *e, int32_t k)
{
    M1Hl275 *l;
    M1Hs275 *s;
    uint32_t fl;
    volatile int32_t st;   /* volatile join stops cl duplicating the reset/set calls into each case */
    if (!e || !(e->bC & 1) || e->kind4 != 2 || e->sub8 != 7) return;
    l = sub_0001D960(e, 4);
    if (!l) return;
    s = l->s278;
    if (k == 3 || k == 0 || k == 1)
        s->flags50 &= ~0x400u;
    fl = s->flags50;
    if (!(fl & 0x100)) {
        if (k == 1 && !(l->b20 & 1))
            s->flags50 = fl | 0x200;
        return;
    }
    if (!s->f38) return;
    switch (k) {
    case 0:
        st = ((int8_t)l->b20 & 1) | 8;
        goto set;
    case 1:
        if (l->b20 & 1) {
            st = 9;
            goto set;
        }
        st = 0xB;
        goto reset;
    case 2:
        st = 0x10;
        goto set;
    case 3:
        st = 1;
        goto reset;
    case 4:
        if (l->b20 & 1) for (;;) ;
        st = 0xA;
        goto set;
    }
    return;
reset:
    s->f54 = 0;
    sub_00147580b(e, st, l);
    return;
set:
    s->f54 = st;
    sub_00147580(e, 0x16, l);
}
