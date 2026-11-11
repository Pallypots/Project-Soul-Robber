/* Area r2, group 8: trio cleanup and facing checks (0x000F7100..0x0012E714). Names inferred. */
#include "r2.h"

/* 0x000F7100: for each of the three trio actors release their live +0x134..+0x13C
   effects. */
void r2_TrioReleaseEffects(void)
{
    R2EffHolder *o;
    int i;
    for (i = 0; i < 3; i++) {
        if (i == 0)
            o = (R2EffHolder *)sub_000FE3D0();
        else if (i == 1)
            o = (R2EffHolder *)sub_00100110();
        else if (i == 2)
            o = (R2EffHolder *)sub_000FBAF0();
        if (o->eff134[0] != -1 && sub_00199E70(o->eff134[0])) {
            sub_00048250(o->eff134[0]);
            o->eff134[0] = -1;
        }
        if (o->eff134[1] != -1 && sub_00199E70(o->eff134[1])) {
            sub_00048250(o->eff134[1]);
            o->eff134[1] = -1;
        }
        if (o->eff134[2] != -1 && sub_00199E70(o->eff134[2])) {
            sub_00048250(o->eff134[2]);
            o->eff134[2] = -1;
        }
    }
}

/* 0x001154D0: is the player within 40 units and facing self within 45 degrees?
   0 while the player is busy or obj's state flag 0x80000 is set.
   regargs: obj=EAX; self is the stack arg */
int r2_PlayerInFrontA(R2Body *obj, R2Actor *self)
{
    R2PlayerX *pl = (R2PlayerX *)r2_player;
    R2State *st = obj->st278;
    float f[4], d[4], dot;
    if (!sub_000CF560(&g_stats, 0) || (st->flags04 & 0x80000))
        return 0;
    if (sub_001B2770(self->pos60, pl->pos60) >= 40.0f)
        return 0;
    sub_001ADBA0(f, pl->rot20->row20, -1.0f);
    sub_001AD9F0(d, self->pos60, pl->pos60);
    f[1] = 0.0f;
    d[1] = 0.0f;
    sub_001AD7E0(f, f);
    sub_001AD7E0(d, d);
    dot = sub_001AD9D0(f, d);
    if (sub_001A3EE0(45.0f) > dot)
        return 0;
    return 1;
}

/* 0x0012E630: as 0x1154D0 but blocked by state flag 0x1000000 at +0x0C.
   regargs: obj=EAX; self is the stack arg */
int r2_PlayerInFrontB(R2Body *obj, R2Actor *self)
{
    R2PlayerX *pl = (R2PlayerX *)r2_player;
    R2State *st = obj->st278;
    float f[4], d[4], dot;
    if (!sub_000CF560(&g_stats, 0) || (st->flags0C & 0x1000000))
        return 0;
    if (sub_001B2770(self->pos60, pl->pos60) >= 40.0f)
        return 0;
    sub_001ADBA0(f, pl->rot20->row20, -1.0f);
    sub_001AD9F0(d, self->pos60, pl->pos60);
    f[1] = 0.0f;
    d[1] = 0.0f;
    sub_001AD7E0(f, f);
    sub_001AD7E0(d, d);
    dot = sub_001AD9D0(f, d);
    if (sub_001A3EE0(45.0f) > dot)
        return 0;
    return 1;
}
