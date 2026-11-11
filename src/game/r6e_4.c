/* Area r6e: sound channels, globals and player helpers around 0x0006C720-0x000CFFF9 (r6e_4). Names inferred. */
#include "r6e.h"

/* 0x0006C720: store three values and the default scale 110.0. */
void r6e_SetView3(int a, int b, int c)
{
    r6e_g42C5D8 = a;
    r6e_g42C5E0 = b;
    r6e_g42C5E4 = c;
    r6e_f42C5DC = 110.0f;
}

/* 0x000CC4D0: pick the two blend widths from +0x18C.
   regargs: p=EAX */
void r6e_PlayerBlend(R6ePlayer *p)
{
    if (p->i18C) {
        r6e_g41CD2C = 0x80;
        r6e_g41CD30 = 0x10;
    } else {
        r6e_g41CD2C = 0x10;
        r6e_g41CD30 = 0x80;
    }
}

/* 0x000CD600: when nothing blocks it and an enabled button is held, queue the player's action.
   calls 0x000CD300 with EAX=p */
void r6e_PlayerQueueAction(R6ePlayer *p)
{
    if (aa0_flags420010 & 0x82006)
        return;
    if (r6e_g41FF94 == 2 || r6e_g41FF94 == 4 || r6e_g41FF94 == 5)
        return;
    if (sub_0019BE60(0x4101))
        return;
    if (r6e_g41CD18 & g_ac0_42CA38)
        sub_000BC6B0(r6e_obj420EC0, sub_000CD300(p) + 0x2E);
}

/* 0x000CD930: start the player action for a held button once.
   regargs: p=ESI mask=ECX; calls 0x000CD300 with EAX=p */
void r6e_PlayerStartAction(R6ePlayer *p, uint32_t mask)
{
    int v;
    if (!(p->flags150 & 1) && (r6e_g41CD18 & mask)) {
        p->flags150 |= 0x101;
        v = sub_000CD300(p);
        p->i1D8 = v;
        sub_000BD4D0(p, v + 0x13);
    }
}

/* 0x000CFFB0: whether the player may act: -1 blocked, 2 with flag bit 0, else 1. */
int r6e_PlayerCanAct(void)
{
    if (sub_0019BE60(0x10000))
        return -1;
    if (aa0_flags420010 & 0x80080010)
        return -1;
    if (r6e_g420BEC)
        return -1;
    if (r6e_g41FF94 == 4 || r6e_g41FF94 == 5)
        return -1;
    return (g_stats.flags & 1) ? 2 : 1;
}
