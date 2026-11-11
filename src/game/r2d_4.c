/* Area r2d, group 4: player guard, pulse and turning (0x000D0930..0x000D0F4A). Names inferred. */
#include "r2d.h"

/* 0x000D0930: build the light set at 0x418A80 (lights 15..0) on the rig's
   node and load its texture. */
void r2d_LightSetInit(void)
{
    int ids[17];
    void *h;
    h = sub_000847F0(r2d_ctx->v44, 0xE);
    ids[0] = 15;
    ids[1] = 14;
    ids[2] = 13;
    ids[3] = 12;
    ids[4] = 11;
    ids[5] = 10;
    ids[6] = 9;
    ids[7] = 8;
    ids[8] = 7;
    ids[9] = 6;
    ids[10] = 5;
    ids[11] = 4;
    ids[12] = 3;
    ids[13] = 2;
    ids[14] = 1;
    ids[15] = 0;
    ids[16] = -1;
    sub_001BA820(&r2d_lightSet);
    r2d_lightSet.pD4 = r2d_lightSet.data100;
    sub_001BA910(&r2d_lightSet, ((R2dRig *)g_42C8EC)->node3B0->part20, ids, r2d_lightSet.data100);
    sub_001BA8B0(&r2d_lightSet, 10);
    sub_001B2020(h, &r2d_lightSet);
    r2d_lightSet.fEC = 0.1f;
    r2d_lightSet.texE8 = sub_00084CE0(r2d_str27724C);
}

/* 0x000D0A50: advance the player's pulse timer: after 18 units the pending
   bits 0x10/0x20 become 1/2 (effect 0x1C, sound); after 120 units bits 1/2
   become 4/8 and the pulse ends (effect 0x1D, sounds, effect 0x46). */
void r2d_PlayerPulse(R2dPlayer *p)
{
    int v;
    if (p->mode1B8 != 0 || p->v164 > 0 || (p->vEC & 0x40) || (p->flags150 & 0x40001800))
        return;
    if (p->vEC & 0x30) {
        p->fF0 = a50_frameUnits + p->fF0;
        if (!(p->fF0 >= 18.0f))
            return;
        if (p->vEC & 0x10)
            p->vEC |= 1;
        if (p->vEC & 0x20)
            p->vEC |= 2;
        p->vEC &= ~0x30u;
        p->fF0 = 0.0f;
        if (p->fx5F0 < 0)
            p->fx5F0 = sub_000494D0(0x1C, p->nodeFD8->pos60, 1);
        if (p->snd600 == 0)
            p->snd600 = PlayerObj_D0030((PlayerObj *)p, Stats_Get((PlayerStats *)p, p->mode1B8 + 4) + 3);
    } else if (p->vEC & 3) {
        p->fF0 = a50_frameUnits + p->fF0;
        if (!(p->fF0 >= 120.0f))
            return;
        if (p->vEC & 1)
            p->vEC |= 4;
        if (p->vEC & 2)
            p->vEC |= 8;
        p->vEC = (p->vEC & ~3u) | 0x40;
        p->fF0 = 0.0f;
        if (p->fx5F0 >= 0) {
            sub_00048250(p->fx5F0);
            p->fx5F0 = sub_000494D0(0x1D, p->nodeFD8->pos60, 1);
        }
        if (p->snd600) {
            v = Stats_Get((PlayerStats *)p, p->mode1B8 + 4);
            sub_00033A40(p->snd600);
            p->snd600 = 0;
            p->snd608 = PlayerObj_D0030((PlayerObj *)p, v + 0x13);
            p->snd600 = PlayerObj_D0030((PlayerObj *)p, v + 8);
        }
        sub_000494D0(0x46, p->nodeFD8->pos60, 0);
    }
}

/* 0x000D0C50: raise the player's guard (flag 0x1000, timer 600): start the
   guard sounds and effects 0x1D and 0x46. */
void r2d_PlayerGuardOn(R2dPlayer *p)
{
    int v;
    if (p->mode1B8 != 0 || p->vEC != 0 || (p->flags150 & 0x1000))
        return;
    p->flags150 |= 0x1000;
    p->f168 = 600.0f;
    v = Stats_Get((PlayerStats *)p, 4);
    p->snd608 = (p->nodeFD8 && p->nodeFD8->part20) ? sub_00036750(p->nodeFD8, v + 0x13) : 0;
    p->snd600 = (p->nodeFD8 && p->nodeFD8->part20) ? sub_00036750(p->nodeFD8, v + 8) : 0;
    p->fx5F0 = sub_000494D0(0x1D, p->nodeFD8->pos60, 1);
    sub_000494D0(0x46, p->nodeFD8->pos60, 0);
}

/* 0x000D0D30: lower the player's guard: drop the effect and replace the
   guard sound with sound 0xB. */
void r2d_PlayerGuardOff(R2dPlayer *p)
{
    p->flags150 &= ~0x1000u;
    p->f168 = 0.0f;
    if (p->fx5F0 >= 0) {
        sub_00048250(p->fx5F0);
        p->fx5F0 = -1;
    }
    if (p->snd600) {
        sub_00033A40(p->snd600);
        p->snd600 = 0;
        p->snd600 = (p->nodeFD8 && p->nodeFD8->part20) ? sub_00036750(p->nodeFD8, 0xB) : 0;
    }
}

/* 0x000D0EA0: turn the facing angle (+0x108) toward the target (+0xFC) by
   the wrapped difference over the turn time (+0x10C), wrapping to -pi..pi.
   Skipped in state 5 while +0xE8 is below 10. */
void r2d_PlayerTurn(R2dPlayer *p)
{
    float d;
    if (p->stateD8 == 5 && 10.0f > p->fE8)
        return;
    d = p->fFC - p->f108;
    if (d > 3.14159274f)
        d -= 6.28318548f;
    if (-3.14159274f > d)
        d += 6.28318548f;
    p->f108 = d / p->f10C * a50_frameUnits + p->f108;
    if (p->f108 > 3.14159274f)
        p->f108 -= 6.28318548f;
    if (-3.14159274f > p->f108)
        p->f108 += 6.28318548f;
}
