/* Area rbg: game functions in 0x000F0000..0x000FFFFF (rbg_3). Names inferred. */
#include "rbg.h"

/* 0x000F0430: play animation anim (args a, b) on actor (3, 7) unless it is already playing or
   the actor is in mode 0x12 (only anim 0x21 allowed there), then apply the expression slot
   that belongs to the animation (ids 0..11 -> 1..12, 16..26 -> 13..23, 32..39 -> 24..31). */
void rbg_ActorAnim0F0430(int anim, int a, int b)
{
    RbgRec150 *o = sub_000E23F0(3, 7);
    RbgComp *c = sub_0001D960(o, 5);
    int k;

    if (!o)
        return;
    if (anim == o->anim30->i08)
        return;
    if (c->kind6C == 0x12 && anim != 0x21)
        return;
    sub_000E1040(o);
    sub_000E1060(o, anim, a, b);
    k = 0;
    switch (anim) {
    case 0:  k = 1;  break;
    case 1:  k = 2;  break;
    case 2:  k = 3;  break;
    case 3:  k = 4;  break;
    case 4:  k = 5;  break;
    case 5:  k = 6;  break;
    case 6:  k = 7;  break;
    case 7:  k = 8;  break;
    case 8:  k = 9;  break;
    case 9:  k = 10; break;
    case 10: k = 11; break;
    case 11: k = 12; break;
    case 16: k = 13; break;
    case 17: k = 14; break;
    case 18: k = 15; break;
    case 19: k = 16; break;
    case 20: k = 17; break;
    case 21: k = 18; break;
    case 22: k = 19; break;
    case 23: k = 20; break;
    case 24: k = 21; break;
    case 25: k = 22; break;
    case 26: k = 23; break;
    case 32: k = 24; break;
    case 33: k = 25; break;
    case 34: k = 26; break;
    case 35: k = 27; break;
    case 36: k = 28; break;
    case 37: k = 29; break;
    case 38: k = 30; break;
    case 39: k = 31; break;
    }
    sub_000F3D10(o, sub_0001D960(o, 5), k);
}

/* 0x000F3DA0: switch every model of group g to animation entry anim (anim < 0 restarts the
   current entry) with a blend of ms milliseconds (converted to frames; 0 uses the entry's own
   length) and blend mask mode (1..4, 0 uses the entry's mask), then apply loop flag and speed. */
void rbg_GroupAnim0F3DA0(RbgRec150 *g, int anim, int ms, int mode)
{
    int masks[4];
    int n;
    RbgRec150 *r;
    RbgAnim *a;
    RbgAnimEnt *e;
    int t;

    masks[0] = 4;
    masks[1] = 8;
    masks[2] = 0x10;
    masks[3] = 0x20;
    if (!g)
        return;
    n = sub_000F3140(g->i08);
    if (n <= 0)
        return;
    r = g;
    do {
        a = r->anim30;
        if (anim != a->i08) {
            a->i08 = anim < 0 ? a->i08 : anim;
            e = sub_00083120(a, a->i08);
            if (e && e->i0C) {
                if (ms > 0)
                    t = ms * 60 / 1000;
                else if (ms < 0)
                    t = 0;
                else
                    t = sub_00082FC0(e, a->i08);
                sub_001AEFD0(a->node14, e->i0C, masks[mode ? mode - 1 : e->i18] | 2, t);
                sub_001AEF10(a->node14, 2);
                if (!(e->b08 & 1))
                    sub_001AEED0(a->node14, 4);
                else
                    sub_001AEF10(a->node14, 4);
                sub_001AEDD0(a->node14, e->f10);
                sub_00082F90(a, e);
            }
        }
        r++;
    } while (--n);
}

/* 0x000FB580: play the sound of event ev (0..2) for an object of kind 3, 4 or 5 at its
   position. */
void rbg_KindSound0FB580(RbgRec150 *o, int ev)
{
    int k3, k4, k5;

    if (!o)
        return;
    k3 = o->i08 == 3;
    k4 = o->i08 == 4;
    k5 = o->i08 == 5;
    switch (ev) {
    case 0:
        if (k3)
            sub_000494D0(0x16E, o->pos60, 1);
        else if (k4)
            sub_000494D0(0x167, o->pos60, 1);
        else if (k5)
            sub_000494D0(0x16C, o->pos60, 1);
        break;
    case 1:
        if (k3)
            sub_000494D0(0x171, o->pos60, 1);
        else if (k4)
            sub_000494D0(0x166, o->pos60, 1);
        else if (k5)
            sub_000494D0(0x16B, o->pos60, 1);
        break;
    case 2:
        if (k3)
            sub_000494D0(0x170, o->pos60, 1);
        else if (k4)
            sub_000494D0(0x168, o->pos60, 1);
        else if (k5)
            sub_000494D0(0x172, o->pos60, 1);
        break;
    }
}
