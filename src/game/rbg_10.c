/* Area rbg: game functions in 0x00130000..0x0014FFFF (rbg_10). Names inferred. */
#include "rbg.h"

/* 0x0013D4E0: an enemy holding reference ref in work slot 1 or 2 reacts to event mode:
   mode 0 grabs it (one chance in 16 to refuse and go to state 0x30), mode 1 lets it go and,
   when nothing else is held and the enemy is in state 0x14 or 0x2E, rests (node 8 = 0x52/0x28)
   and returns to state 0. Returns 0 when inactive or refused, else 1. Hangs when ref is not
   held. */
int rbg_HoldRef13D4E0(RbgRec150 *obj, void *ref, int mode)
{
    RbgComp *act;
    RbgWork *w;
    RbgNode *n;
    int slot, other, ret;

    if (!(obj->flags0C & 1) || (obj->flags10 & 8))
        return 0;
    act = sub_0001D960(obj, 4);
    if (!act)
        for (;;)
            ;
    w = act->work278;
    other = 0;
    slot = -1;
    if (w->refs34[1]) {
        if (w->refs34[1] == ref)
            slot = 1;
        else
            other = 1;
    }
    if (w->refs34[2]) {
        if (w->refs34[2] == ref)
            slot = 2;
        else
            other = 1;
    }
    if (slot < 0)
        for (;;)
            ;
    ret = 1;
    switch (mode) {
    case 0:
        if (sub_001C7EE1() % 16 < 1) {
            sub_00113040(obj, act, 0x30);
            ret = 0;
        } else {
            w->refs34[0] = ref;
            w->refs34[slot] = 0;
            sub_00113190(obj, act, 1);
            sub_00113040(obj, act, 0x2F);
        }
        break;
    case 1:
        w->refs34[slot] = 0;
        if (!other && !w->refs34[0] && (act->i50 == 0x14 || act->i50 == 0x2E)) {
            n = sub_00113430(act, 8);
            n->i10 = 0x52;
            n->i14 = 0x28;
            sub_00113040(obj, act, 0);
        }
        break;
    }
    return ret;
}

/* 0x0013BF80: idle state of an enemy: after the start delay, pick the next state from the
   condition records (7: 9; armed: 0x10, else a 1/128 chance of 4 or condition 2 gives 0x13,
   condition 5 keeps idling, 3 gives 0x14 else 0xD; unarmed: 5 keeps idling, 0 gives 0x11,
   1 gives 0x12 else 0xD), clear obj flag 0x20 and enter it.
   calls 0x00139B10 with EAX=k EDX=act and obj on the stack */
void rbg_Idle13BF80(RbgRec150 *obj, RbgComp *act)
{
    int st;

    switch (act->i58) {
    case 0:
        if (!(r3e_frameSeconds > act->f74))
            return;
        act->i58 = 1;
    case 1:
        break;
    default:
        return;
    }
    if (act->flags20 & 1) {
        st = 9;
        if (!r3b_disp31CDFC[7](obj, act, &r3b_recs279728[7])) {
            st = 0x10;
            if (!(act->work278->flags04 & 1)) {
                st = 0x13;
                if (!(sub_001C7EE1() % 128 < 1 && r3b_Dispatch139B10(4, act, obj))) {
                    if (r3b_Dispatch139B10(5, act, obj))
                        return;
                    if (!r3b_Dispatch139B10(2, act, obj))
                        st = r3b_Dispatch139B10(3, act, obj) ? 0x14 : 0xD;
                }
            }
        }
    } else {
        st = 9;
        if (!r3b_disp31CDFC[7](obj, act, &r3b_recs279728[7])) {
            if (r3b_disp31CDFC[5](obj, act, &r3b_recs279728[5]))
                return;
            st = 0x11;
            if (!r3b_disp31CDFC[0](obj, act, &r3b_recs279728[0]))
                st = r3b_Dispatch139B10(1, act, obj) ? 0x12 : 0xD;
        }
    }
    obj->flags10 &= ~0x20u;
    sub_00113040(obj, act, st);
}

/* 0x0013A670: three-step landing state: 0 waits for the current animation, then plays 0x62
   (0x3D when work flag 0x80000000 is set) at 0.08 times its speed; 1 waits for the impact
   flags 0x18, then plays at triple speed with sound 0x88 and effect 7 and clears the flags;
   2 returns 1 when the animation has finished. */
int rbg_Land13A670(RbgRec150 *obj, RbgComp *act)
{
    RbgWork *w = act->work278;

    switch (act->i58) {
    case 0:
        obj->flags128 &= ~0x18u;
        if (sub_000833E0(obj->anim30)) {
            sub_00113090(obj, act, (w->flags04 & 0x80000000u) ? 0x3D : 0x62);
            sub_001AEDD0(obj->anim30->node14,
                         sub_00083120(obj->anim30, obj->anim30->i08)->f10 * 0.08f);
            act->i58++;
        }
        break;
    case 1:
        if (obj->flags128 & 0x18) {
            sub_001B1190(obj->anim30->node14, 3.0f);
            sub_001AEDD0(obj->anim30->node14, sub_00083120(obj->anim30, obj->anim30->i08)->f10);
            sub_000494D0(0x88, obj->r20->v30, 0);
            sub_00036750(obj, 7);
            obj->flags10 &= ~0x10u;
            w->flags04 &= ~0x10000000u;
            act->i58++;
        }
        break;
    case 2:
        if (sub_000833E0(obj->anim30))
            return 1;
        break;
    }
    return 0;
}

/* 0x0014E6B0: when the current animation has finished, either recover (clear the hit flags,
   settle the motion, apply pending events, stop the sound and effect, enter state 0xC) or
   start the pending reaction of the work block.
   calls 0x00147580 with EBX=anim ESI=act and obj on the stack */
void rbg_Recover14E6B0(RbgRec150 *obj, RbgComp *act)
{
    RbgWork *w0 = act->work278;
    RbgWork *w;
    int anim;

    if (!sub_000833E0(obj->anim30))
        return;
    if (sub_00156040()) {
        w = act->work278;
        sub_001134B0(act);
        obj->flags0C |= 0xE0;
        obj->flags10 &= 0xFFFFFEC8u;
        act->flags4C &= ~0x100u;
        w->flags00 &= 0xFFFFFFE8u;
        w->flags50 &= 0xFFDBEEBFu;
        sub_001561D0(w, -10.0f, r3e_frameSeconds * 10.0f);
        if (w->flags50 & 0x10000) {
            sub_00113AA0(obj, act);
            act->flags4C |= 0x200;
            w->flags50 &= ~0x10000u;
        }
        if (w->flags50 & 0x100000) {
            w->flags50 &= ~0x100000u;
            sub_00113190(obj, act, 1);
        }
        if (act->snd6C != -1) {
            sub_00048250(act->snd6C);
            act->snd6C = -1;
        }
        sub_0005BE30(obj->h13C);
        if (act->p70) {
            sub_00033A70(act->p70);
            act->p70 = 0;
        }
        sub_00113040(obj, act, 0xC);
    } else {
        anim = w0->anim54;
        if (!anim)
            for (;;)
                ;
        sub_00147580(obj, anim, act);
        w0->anim54 = 0;
    }
}

/* 0x00146140: choose the reaction state for the hit kind in the work block (1..43; unknown
   kinds give 0x17), with the knock-down flags 2/0x10 overriding it and a repeat of the current
   state falling back to 0x17 (except 0x19). Hangs on state 0.
   regargs: act=EBX */
int rbg_HitState146140(RbgComp *act)
{
    RbgWork *w = act->work278;
    int st;

    w->flags50 &= 0xFFBFFFFBu;
    switch (w->hit1BC) {
    case 1:
    case 6:
    case 29:
        st = 0x1E;
        break;
    case 2:
        st = 0x18;
        break;
    case 3:
        st = 0x1D;
        break;
    case 5:
        st = w->i1C4 ? 0x1E : 0x19;
        break;
    case 7:
    case 9:
        st = 0x19;
        break;
    case 34:
        w->flags50 |= 8;
        st = 0x1F;
        break;
    case 35:
        w->flags50 |= 8;
        st = 0x20;
        break;
    case 10:
        w->flags50 |= 0x400004;
        st = 0x1E;
        break;
    case 11:
        w->flags50 |= 0x400004;
        st = 0x20;
        break;
    case 8:
        st = 0x22;
        break;
    case 14:
        st = 0x24;
        break;
    case 15:
        st = 0x25;
        break;
    case 26:
        st = 0x26;
        break;
    case 17:
        st = 0x28;
        break;
    case 28:
        st = 0x2A;
        break;
    case 16:
    case 18:
    case 19:
    case 20:
    case 21:
        st = 0x27;
        break;
    case 42:
        st = 0x2B;
        sub_000F5D40(act->v88, w->v1DC);
        break;
    case 13:
        st = 0x29;
        break;
    case 36:
        st = 0x1A;
        break;
    case 30:
        st = 0x1B;
        break;
    case 31:
        st = 0x1C;
        break;
    case 32:
        st = 0x21;
        break;
    case 43:
        if ((act->flags20 & 1) || (act->i50 >= 0x17 && act->i50 <= 0x2C))
            st = 0x17;
        else
            st = 0x23;
        w->fDC = 0.05f;
        break;
    case 12:
        w->flags50 |= 0x80000;
    default:
        st = 0x17;
        break;
    }
    if (w->flags50 & 2)
        st = (w->flags50 & 0x10) ? 0x1E : 0x17;
    else if (w->flags50 & 0x10) {
        if (st == 0x17)
            st = 0x2C;
    } else if (st == act->i50 && st != 0x19)
        st = 0x17;
    if (!st)
        for (;;)
            ;
    return st;
}
