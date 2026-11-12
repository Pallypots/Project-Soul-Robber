/* Area m1, file 32: the four links at 0x003FE2D8 (0x24 each). Names inferred. */
#include <stdint.h>

typedef struct M1LObj {
    uint8_t unk00[0x30];
    void   *anim30;            /* +0x30 */
    uint8_t unk34[0x50 - 0x34];
    int32_t kind50;            /* +0x50 */
} M1LObj;
typedef struct M1Link24 {
    M1LObj *a00;               /* +0x00 */
    M1LObj *b04;               /* +0x04 */
    M1LObj *c08;               /* +0x08 watched object */
    int32_t key0C;             /* +0x0C */
    uint8_t unk10[0x24 - 0x10];
} M1Link24;
extern M1Link24 m1_links3FE2D8[4];  /* 0x003FE2D8 */
typedef struct M1Part4C {
    uint8_t  unk00[0x4C];
    uint32_t flags4C;          /* +0x4C */
} M1Part4C;
M1Part4C *sub_0001D960(M1LObj *o, int part);
void sub_000832D0(void *anim, int id);
void sub_00113040(void *owner, void *obj, int what);
int  sub_000F5D00(M1LObj *o);

/* 0x00181DA0: resets every link: clears flag 0x1000000 on part 6 of b, plays
 * animation 3 on b and a, and sends event 0 for the watched object. */
void m1_ResetLinks181DA0(void)
{
    int i;
    M1Part4C *p;
    for (i = 0; i < 4; i++) {
        M1LObj *b = m1_links3FE2D8[i].b04;
        M1LObj *a = m1_links3FE2D8[i].a00;
        p = sub_0001D960(b, 6);
        if (p != 0)
            p->flags4C &= ~0x1000000u;
        sub_000832D0(b->anim30, 3);
        sub_000832D0(a->anim30, 3);
        sub_00113040(a, m1_links3FE2D8[i].c08, 0);
    }
}

/* 0x00181D40: 0 if, for a link whose watched object is in state 1, the requested
 * side (bit 1: a, bit 0: b) is not ready (0xF5D00); else 1. */
int m1_LinksReady181D40(uint8_t which)
{
    int i;
    for (i = 0; i < 4; i++) {
        if (m1_links3FE2D8[i].c08->kind50 == 1) {
            if ((which & 2) && sub_000F5D00(m1_links3FE2D8[i].a00) == 0)
                return 0;
            if ((which & 1) && sub_000F5D00(m1_links3FE2D8[i].b04) == 0)
                return 0;
        }
    }
    return 1;
}
