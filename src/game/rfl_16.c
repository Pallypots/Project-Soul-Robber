/* Area rfl, group 16: trap and turret steps (0x0016D680..0x00170F06). Names inferred. */
#include "rfl.h"

/* 0x0016D680: turret aim: on the first step arm the link (flags 0x80 and
   0x1000, vector (0, 0, 10, 0) at +0x20, copy +0x10 to +0x40); afterwards
   turn one degree toward the aim point when it is more than 20 degrees
   off. */
void rfl_TurretAim(RflActor *o, RflTrap *e)
{
    RflTrapLink *l = e->link74;
    RflTrapLink *m;
    float a;
    switch (e->step54) {
    case 0:
        l->flags0 |= 0x80;
        m = e->link74;
        m->v20[1] = 0.0f;
        m->v20[3] = 0.0f;
        m->v20[0] = 0.0f;
        m->v20[2] = 10.0f;
        m->flags0 |= 0x1000;
        l->f40 = l->pt0C[1];
        e->step54++;
        break;
    case 1:
        a = sub_00113290(o, l->pt0C);
        if (a > 0.34906587f)
            o->yaw54 += 0.0174532924f;
        else if (-0.34906587f > a)
            o->yaw54 -= 0.0174532924f;
        break;
    }
}

/* 0x0016DA60: trap wait: on the first step disarm the link, start a
   120-frame-unit timer and set +0x50 to 10 degrees; afterwards, once the
   timer has run out and the player is within 20 units, enter state 0x0C.
   calls 0x0016C820 with EAX=e EDI=o and the state on the stack */
void rfl_TrapWait(RflActor *o, RflTrap *e)
{
    RflTrapLink *l = e->link74;
    switch (e->step54) {
    case 0:
        l->flags0 &= ~0x80u;
        e->t5C = 120.0f / a50_frameUnits * a50_frameSeconds;
        e->flags4C &= ~1u;
        o->f50 = 0.174532935f;
        e->step54++;
        break;
    case 1:
        if (0.0f > e->t5C && 20.0f > r4_DistanceXZ(o->pos60, rfl_playerObj->pos60))
            r3_SetState16C820(e, o, 0xC);
        break;
    }
}

/* 0x00170A40: trap hold: step 0 clears actor flag 0x20; step 1 follows the
   player until body flags 6 are set or the player is 60 units away, then
   sets flag 0x20, resets the motion vector and stops. +0x60 is cleared on
   every call. */
void rfl_TrapHold(RflActor *o, RflTrap *e)
{
    switch (e->step54) {
    case 0:
        o->flagsC &= ~0x20u;
        e->step54++;
        break;
    case 1:
        if (!(o->flags128 & 6) && r4_DistanceXZ(o->pos60, rfl_playerObj->pos60) < 60.0f) {
            sub_000C56B0(o);
            break;
        }
        o->flagsC |= 0x20;
        e->t5C = 0.0f;
        e->v60[0] = 0.0f;
        e->v60[1] = 0.0f;
        e->v60[2] = 1.0f;
        sub_000C62A0(o);
        break;
    }
    e->v60[0] = 0.0f;
}

/* 0x00170E40: aim wobble: below 0.05 reset the part's vector at +0x30 to
   (0, 0, 0, 1); otherwise point it in a random direction within +-180
   degrees, radius 0.4.
   regargs: e=EAX o=EDI */
void rfl_TrapWobble(RflTrap *e, RflActor *o)
{
    float v[4];
    float *p;
    float a;
    if (e->f58 >= 0.05f) {
        p = (float *)((uint8_t *)sub_0001D0F0(o, 1) + 0x30);
        p[0] = 0.0f;
        p[1] = 0.0f;
        p[2] = 0.0f;
        p[3] = 1.0f;
        return;
    }
    a = (float)(sub_001C7EE1() % 3600 - 1800) * 0.00174532935f;
    v[0] = sub_001A3ED0(a) * 0.4f;
    v[1] = 0.0f;
    v[2] = sub_001A3EE0(a) * 0.4f;
    v[3] = 1.0f;
    sub_000F5D40((float *)((uint8_t *)sub_0001D0F0(o, 1) + 0x30), v);
}

/* 0x001711F0: hold step: follow the player and set body flags 0x18 while
   close; on body flags 6 or 60 units away aim +0x78 back along -(+0x5C)
   and switch to mode 2. */
void rfl_TrapHoldRelease(RflActor *o, RflTrap *e)
{
    if (!(o->flags128 & 6) && r4_DistanceXZ(o->pos60, rfl_playerObj->pos60) < 60.0f) {
        sub_000C56B0(o);
        o->flags128 |= 0x18;
        return;
    }
    sub_001ADBA0(e->v78, &e->t5C, -1.0f);
    e->mode50 = 2;
    e->step54 = 0;
    e->f58 = 0.0f;
}
