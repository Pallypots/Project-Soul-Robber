/* Area rbh: game functions in 0x00130000..0x0013FFFF (rbh_6). Names inferred. */
#include "rbh.h"

/* 0x0013C7E0: rise-and-attack state of an enemy. Sub-states 0 and 1 are those of 0x0013BAF0
   (44-frame emitter start, event 3 after 56 frames); sub-state 2 waits for the animation, then
   picks the next state: a blocked kind-0xD target gives 0xC; outside a combo, after a dodge a
   1/4 chance of 0x10, else 0xC with a 90-frame timer; a 1/32 chance starts a combo of 2 or 3
   hits; otherwise condition 2 gives 0x13, condition 3 gives 0x14, else 0xD. Combo hits give
   0x13 when condition 2 holds, else 0x14, and the last one 0x1A with a 144-frame timer. Then
   sends event 2, clears actor flag 0x100 and work flag 0x400000 and enters the state.
   calls 0x00139B10 with EAX=k EDX=act and obj on the stack */
void rbh_Rise13C7E0(RbhEnemy *obj, RbhComp *act)
{
    RbhWorkG *w = (RbhWorkG *)act->work278;
    RbhEmit *e;
    int st;

    switch (act->i58) {
    case 0:
        if (act->f5C >= 44.0f / r3_frameUnits * a50_frameSeconds) {
            e = sub_00113400(act, 3);
            e->f10 = 0.0f;
            e->f14 = 0.0f - r3_frameUnits * 0.09773844f;
            act->i58++;
        }
        return;
    case 1:
        if (act->f5C > 56.0f / r3_frameUnits * a50_frameSeconds) {
            sub_00113480(act, 3);
            act->i58++;
        }
        return;
    case 2:
        break;
    default:
        return;
    }
    if (!sub_000833E0(obj->anim30))
        return;
    if (act->iF8 == 1 && (act->target104->flags0C & 1) && act->target104->kind04 == 0xD)
        st = 0xC;
    else if (!(w->flags04 & 2)) {
        if (act->flags4C & 0x100) {
            if (sub_001C7EE1() % 4 < 1)
                st = 0x10;
            else {
                st = 0xC;
                act->f74 = 90.0f / r3_frameUnits * a50_frameSeconds;
            }
        } else if (sub_001C7EE1() % 32 < 1) {
            w->flags04 |= 2;
            w->n24 = (sub_001C7EE1() % 2 < 1) + 2;
            st = r3b_Dispatch139B10(2, act, obj) ? 0x13 : 0x14;
        } else if (r3b_Dispatch139B10(2, act, obj))
            st = 0x13;
        else
            st = r3b_Dispatch139B10(3, act, obj) ? 0x14 : 0xD;
    } else if (--w->n24 == 0) {
        w->flags04 &= ~2u;
        st = 0x1A;
        act->f74 = 144.0f / r3_frameUnits * a50_frameSeconds;
    } else
        st = r3b_Dispatch139B10(2, act, obj) ? 0x13 : 0x14;
    sub_00113480(act, 2);
    act->flags4C &= ~0x100u;
    w->flags04 &= 0xFFBFFFFFu;
    sub_00113040(obj, act, st);
}

/* 0x0013C630: slam attack state of an enemy. Sub-state 0 waits 34 frames, then starts
   emitter 0xA (speed 0.25 * frame units, 68-frame life); sub-state 1 waits past 102 frames,
   sends event 0xA (after a dodge also sets the shared 120-frame timer b10_f3F7504); sub-state 2
   waits for the animation, then picks the next state (after a dodge a 1/4 chance of 0x10,
   else 0xC with a 180-frame timer; condition 0 gives 0x11, condition 1 gives 0x12, else 0xD),
   sends event 2, clears work flag 0x400000 and enters it.
   calls 0x00139B10 with EAX=k EDX=act and obj on the stack */
void rbh_Slam13C630(RbhEnemy *obj, RbhComp *act)
{
    RbhEmit *e;
    int st;

    switch (act->i58) {
    case 0:
        if (act->f5C >= 34.0f / r3_frameUnits * a50_frameSeconds) {
            e = sub_00113430(act, 0xA);
            e->f10 = r3_frameUnits * 0.25f;
            e->f1C = 68.0f / r3_frameUnits * a50_frameSeconds;
            act->i58++;
        }
        return;
    case 1:
        if (act->f5C > 102.0f / r3_frameUnits * a50_frameSeconds) {
            sub_00113480(act, 0xA);
            if (act->flags4C & 0x100)
                b10_f3F7504 = 120.0f / r3_frameUnits * a50_frameSeconds;
            act->i58++;
        }
        return;
    case 2:
        break;
    default:
        return;
    }
    if (!sub_000833E0(obj->anim30))
        return;
    if (act->flags4C & 0x100) {
        act->flags4C &= ~0x100u;
        if (sub_001C7EE1() % 4 < 1)
            st = 0x10;
        else {
            st = 0xC;
            act->f74 = 180.0f / r3_frameUnits * a50_frameSeconds;
        }
    } else if (r3b_disp31CDFC[0](obj, act, &r3b_recs279728[0]))
        st = 0x11;
    else
        st = r3b_Dispatch139B10(1, act, obj) ? 0x12 : 0xD;
    sub_00113480(act, 2);
    ((RbhWorkG *)act->work278)->flags04 &= 0xFFBFFFFFu;
    sub_00113040(obj, act, st);
}

/* 0x0013C2D0: guard state of an enemy. Condition 7 gives 9 at once. Armed: sub-state 0 waits
   96 frames (after a dodge it also sets the shared 120-frame timer b10_f3F7504), sub-state 1
   waits for the animation; a pending counter (work flag 1) clears itself, swaps actor flags
   0x30 for 0x40 and gives 0x1B or 9 with 1/16 chances each; otherwise condition 2 gives 0x13,
   3 gives 0x14, 4 gives 0x13, else 0xD; then event 2 is sent and obj flag 0x20 cleared.
   Unarmed: after the animation condition 0 gives 0x11, 1 gives 0x12, 5 gives 0xC, else 0xD.
   Both clear work flag 0x400000 and enter the state.
   calls 0x00139B10 with EAX=k EDX=act and obj on the stack */
void rbh_Guard13C2D0(RbhEnemy *obj, RbhComp *act)
{
    RbhWorkG *w;
    float u;
    int st;

    if (r3b_disp31CDFC[7](obj, act, &r3b_recs279728[7])) {
        sub_00113040(obj, act, 9);
        return;
    }
    if (act->flags20 & 1) {
        switch (act->i58) {
        case 0:
            u = 1.0f / r3_frameUnits;
            if (act->f5C >= u * 96.0f * a50_frameSeconds) {
                if (act->flags4C & 0x100)
                    b10_f3F7504 = u * 120.0f * a50_frameSeconds;
                act->i58++;
            }
            return;
        case 1:
            break;
        default:
            return;
        }
        if (!sub_000833E0(obj->anim30))
            return;
        w = (RbhWorkG *)act->work278;
        if (w->flags04 & 1) {
            w->flags04 &= ~1u;
            act->flags4C = (act->flags4C & ~0x30u) | 0x40;
            if (sub_001C7EE1() % 16 < 1) {
                st = 0x1B;
                goto enter;
            }
            if (sub_001C7EE1() % 16 < 1) {
                st = 9;
                goto enter;
            }
        }
        if (r3b_Dispatch139B10(2, act, obj))
            st = 0x13;
        else if (r3b_Dispatch139B10(3, act, obj))
            st = 0x14;
        else
            st = r3b_Dispatch139B10(4, act, obj) ? 0x13 : 0xD;
    enter:
        sub_00113480(act, 2);
        obj->flags10 &= ~0x20u;
        ((RbhWorkG *)act->work278)->flags04 &= 0xFFBFFFFFu;
        sub_00113040(obj, act, st);
    } else {
        if (!sub_000833E0(obj->anim30))
            return;
        if (r3b_disp31CDFC[0](obj, act, &r3b_recs279728[0]))
            st = 0x11;
        else if (r3b_disp31CDFC[1](obj, act, &r3b_recs279728[1]))
            st = 0x12;
        else
            st = r3b_Dispatch139B10(5, act, obj) ? 0xC : 0xD;
        ((RbhWorkG *)act->work278)->flags04 &= 0xFFBFFFFFu;
        sub_00113040(obj, act, st);
    }
}

/* 0x0013C0E0: walk state of an enemy. Sub-state 0 sets the turn speed of emitter 3 (armed
   0.026; unarmed within 40 units 0.014 or, 3 times in 4, 0.0105; otherwise 0.007, all scaled
   by the frame units) and moves on; sub-state 1 restarts the walk cycle when its timer runs
   out. Then picks the next state from the condition records (armed: 7 gives 9, work flag 1
   gives 0x10, 5 gives 0xC, 2 gives 0x13, condition 3 gives 0x14; unarmed: 7 gives 9, 5 gives
   0xC, 0 gives 0x11, 1 gives 0x12), clears obj flag 0x20, enters it and hands the emitter to
   0x00113370. Without a match the walk continues.
   calls 0x00139B10 with EAX=k EDX=act and obj on the stack */
void rbh_Walk13C0E0(RbhEnemy *obj, RbhComp *act)
{
    RbhEmit *e = sub_00113400(act, 3);
    RbhAnimClip *c;
    int st;

    switch (act->i58) {
    case 0:
        if (act->flags20 & 1)
            e->f10 = r3_frameUnits * 0.02617994f;
        else if (40.0f >= act->f100) {
            if (sub_001C7EE1() % 4 < 1)
                e->f10 = r3_frameUnits * 0.013962635f;
            else
                e->f10 = r3_frameUnits * 0.010471976f;
        } else
            e->f10 = r3_frameUnits * 0.0069813174f;
        e->f14 = 0.0f - e->f10;
        act->i58++;
    case 1:
        if (a50_frameSeconds > act->f74) {
            c = obj->player30->clip14;
            act->f74 = c->fDC / c->fC4 * a50_frameSeconds;
            act->i58 = 0;
        }
        break;
    }
    if (act->flags20 & 1) {
        if (r3b_disp31CDFC[7](obj, act, &r3b_recs279728[7]))
            st = 9;
        else if (((RbhWorkG *)act->work278)->flags04 & 1)
            st = 0x10;
        else if (r3b_disp31CDFC[5](obj, act, &r3b_recs279728[5]))
            st = 0xC;
        else if (r3b_disp31CDFC[2](obj, act, &r3b_recs279728[2]))
            st = 0x13;
        else if (r3b_Dispatch139B10(3, act, obj))
            st = 0x14;
        else
            return;
    } else {
        if (r3b_disp31CDFC[7](obj, act, &r3b_recs279728[7]))
            st = 9;
        else if (r3b_disp31CDFC[5](obj, act, &r3b_recs279728[5]))
            st = 0xC;
        else if (r3b_disp31CDFC[0](obj, act, &r3b_recs279728[0]))
            st = 0x11;
        else if (r3b_disp31CDFC[1](obj, act, &r3b_recs279728[1]))
            st = 0x12;
        else
            return;
    }
    obj->flags10 &= ~0x20u;
    sub_00113040(obj, act, st);
    sub_00113370(act, e);
}

/* 0x0013BAF0: rise state of an enemy. Sub-state 0 waits 44 frames and starts emitter 3 with
   a downward speed, sub-state 1 waits past 56 frames and sends event 3, sub-state 2 waits for
   the animation, then picks the next state (1/4 chance of 0x10; condition 2 gives 0x13,
   condition 3 gives 0x14, else 0xD), sets obj flag 0x20, clears obj flags 2/4, sets actor
   flags 0x30, sends event 2 and enters it.
   calls 0x00139B10 with EAX=k EDX=act and obj on the stack */
void rbh_Rise13BAF0(RbhEnemy *obj, RbhComp *act)
{
    RbhEmit *e;
    int st;

    switch (act->i58) {
    case 0:
        if (act->f5C >= 44.0f / r3_frameUnits * a50_frameSeconds) {
            e = sub_00113400(act, 3);
            e->f10 = 0.0f;
            e->f14 = 0.0f - r3_frameUnits * 0.09773844f;
            act->i58++;
        }
        return;
    case 1:
        if (act->f5C > 56.0f / r3_frameUnits * a50_frameSeconds) {
            sub_00113480(act, 3);
            act->i58++;
        }
        return;
    case 2:
        break;
    default:
        return;
    }
    if (!sub_000833E0(obj->anim30))
        return;
    if (sub_001C7EE1() % 4 < 1)
        st = 0x10;
    else if (r3b_disp31CDFC[2](obj, act, &r3b_recs279728[2]))
        st = 0x13;
    else
        st = r3b_Dispatch139B10(3, act, obj) ? 0x14 : 0xD;
    obj->flags0C |= 0x20;
    obj->flags10 &= ~6u;
    act->flags4C |= 0x30;
    sub_00113480(act, 2);
    sub_00113040(obj, act, st);
}

/* 0x0013BDC0: idle state of an enemy. In sub-state 0, between 96 and 108 frames an unarmed
   enemy has a 1/16 chance to attack at once (condition 2 gives 0x13, condition 3 gives 0x14);
   otherwise it waits for the animation. Then (directly in sub-state 1) it clears obj flags 2/4,
   sets actor flags 0x30 and picks the next state: armed 0x10; condition 2 gives 0x13,
   condition 3 gives 0x14; else facing Jack within 90 degrees a 1/2 chance of 0x10, else 0xD.
   calls 0x00139B10 with EAX=k EDX=act and obj on the stack */
void rbh_Idle13BDC0(RbhEnemy *obj, RbhComp *act)
{
    float u;
    int st;

    switch (act->i58) {
    case 0:
        u = 1.0f / r3_frameUnits;
        if (act->f5C > u * 96.0f * a50_frameSeconds && u * 108.0f * a50_frameSeconds > act->f5C &&
            !(((RbhWorkG *)act->work278)->flags04 & 1) && sub_001C7EE1() % 16 < 1) {
            st = 0x13;
            if (!r3b_Dispatch139B10(2, act, obj)) {
                st = 0x14;
                if (!r3b_Dispatch139B10(3, act, obj))
                    goto wait;
            }
            obj->flags10 &= ~6u;
            act->flags4C |= 0x30;
            sub_00113040(obj, act, st);
            return;
        }
    wait:
        if (!sub_000833E0(obj->anim30))
            return;
        break;
    case 1:
        break;
    default:
        return;
    }
    obj->flags10 &= ~6u;
    act->flags4C |= 0x30;
    if (((RbhWorkG *)act->work278)->flags04 & 1)
        st = 0x10;
    else if (r3b_disp31CDFC[2](obj, act, &r3b_recs279728[2]))
        st = 0x13;
    else if (r3b_disp31CDFC[3](obj, act, &r3b_recs279728[3]))
        st = 0x14;
    else if (sub_001A3F30(sub_00113200(obj, (uint8_t *)g_playerObj + 0x60)) <= 1.5707964f &&
             sub_001C7EE1() % 2 < 1)
        st = 0x10;
    else
        st = 0xD;
    sub_00113040(obj, act, st);
}

/* 0x0013C4F0:wait state of an enemy. Sub-state 0 waits 56 frames (after a dodge it also sets
   the shared 120-frame timer b10_f3F7504); sub-state 1 waits for the animation, then picks
   the next state (after a dodge a 1/4 chance of 0x10, else 0xC with a 180-frame timer;
   condition 0 gives 0x11, condition 1 gives 0x12, else 0xD), sends event 2, clears work flag
   0x400000 and enters it.
   calls 0x00139B10 with EAX=k EDX=act and obj on the stack */
void rbh_Wait13C4F0(RbhEnemy *obj, RbhComp *act)
{
    float u;
    int st;

    switch (act->i58) {
    case 0:
        u = 1.0f / r3_frameUnits;
        if (act->f5C >= u * 56.0f * a50_frameSeconds) {
            if (act->flags4C & 0x100)
                b10_f3F7504 = u * 120.0f * a50_frameSeconds;
            act->i58++;
        }
        return;
    case 1:
        break;
    default:
        return;
    }
    if (!sub_000833E0(obj->anim30))
        return;
    if (act->flags4C & 0x100) {
        act->flags4C &= ~0x100u;
        if (sub_001C7EE1() % 4 < 1)
            st = 0x10;
        else {
            st = 0xC;
            act->f74 = 180.0f / r3_frameUnits * a50_frameSeconds;
        }
    } else if (r3b_disp31CDFC[0](obj, act, &r3b_recs279728[0]))
        st = 0x11;
    else
        st = r3b_Dispatch139B10(1, act, obj) ? 0x12 : 0xD;
    sub_00113480(act, 2);
    ((RbhWorkG *)act->work278)->flags04 &= 0xFFBFFFFFu;
    sub_00113040(obj, act, st);
}

/* 0x0013CA10:wait state of an enemy: once the animation ends pick the next state. Outside a
   combo: after a dodge (actor flag 0x100) a 1/4 chance of 0x10, else 0xC with a 90-frame timer;
   a 1/32 chance starts a combo of 2 or 3 hits (0x14 when condition 3 holds, else 0x13);
   otherwise condition 2 gives 0x13 and condition 3 gives 0x14, else 0xD. Inside a combo the
   last hit ends it with 0x1A and a 144-frame timer, earlier hits give 0x14 when condition 3
   holds, else 0x13. Then sends event 2, clears work flag 0x400000 and enters the state.
   calls 0x00139B10 with EAX=k EDX=act and obj on the stack */
void rbh_Wait13CA10(RbhEnemy *obj, RbhComp *act)
{
    RbhWorkG *w = (RbhWorkG *)act->work278;
    int st;

    if (act->i58 != 0)
        return;
    if (!sub_000833E0(obj->anim30))
        return;
    if (!(w->flags04 & 2)) {
        if (act->flags4C & 0x100) {
            act->flags4C &= ~0x100u;
            if (sub_001C7EE1() % 4 < 1)
                st = 0x10;
            else {
                st = 0xC;
                act->f74 = 90.0f / r3_frameUnits * a50_frameSeconds;
            }
        } else if (sub_001C7EE1() % 32 < 1) {
            w->flags04 |= 2;
            w->n24 = (sub_001C7EE1() % 2 < 1) + 2;
            st = r3b_Dispatch139B10(3, act, obj) ? 0x14 : 0x13;
        } else if (r3b_Dispatch139B10(2, act, obj))
            st = 0x13;
        else
            st = r3b_Dispatch139B10(3, act, obj) ? 0x14 : 0xD;
    } else if (--w->n24 == 0) {
        w->flags04 &= ~2u;
        st = 0x1A;
        act->f74 = 144.0f / r3_frameUnits * a50_frameSeconds;
    } else
        st = r3b_disp31CDFC[3](obj, act, &r3b_recs279728[3]) ? 0x14 : 0x13;
    sub_00113480(act, 2);
    w->flags04 &= 0xFFBFFFFFu;
    sub_00113040(obj, act, st);
}

/* 0x0013CD00:recover state of an enemy. Sub-state 0 waits until the timer reaches 24 frames
   (scaled by the frame time), clears work flag 0x800000 and moves on; sub-state 1 waits for
   the animation, then picks the next state (armed: condition 2 gives 0x13, condition 3 gives
   0x14; work flag 4: 1/16 chance of 0xA, else 0x10; unarmed: condition 0 gives 0x11,
   1 gives 0x12; otherwise a 1/8 chance of 0x10, else 0xD), clears obj flags 2/4, sets actor
   flags 0x38 and enters it.
   calls 0x00139B10 with EAX=k EDX=act and obj on the stack */
void rbh_Recover13CD00(RbhEnemy *obj, RbhComp *act)
{
    RbhWorkG *w = (RbhWorkG *)act->work278;
    int st;

    switch (act->i58) {
    case 0:
        if (act->f5C >= 24.0f / r3_frameUnits * a50_frameSeconds) {
            w->flags04 &= 0xFF7FFFFFu;
            act->i58++;
        }
        return;
    case 1:
        break;
    default:
        return;
    }
    if (!sub_000833E0(obj->anim30))
        return;
    if (act->flags20 & 1) {
        if (r3b_disp31CDFC[2](obj, act, &r3b_recs279728[2])) {
            st = 0x13;
            goto enter;
        }
        if (r3b_Dispatch139B10(3, act, obj)) {
            st = 0x14;
            goto enter;
        }
    } else if (w->flags04 & 4) {
        st = (sub_001C7EE1() % 16 < 1) ? 0xA : 0x10;
        w->flags04 &= ~4u;
        goto enter;
    } else if (r3b_Dispatch139B10(0, act, obj)) {
        st = 0x11;
        goto enter;
    } else if (r3b_Dispatch139B10(1, act, obj)) {
        st = 0x12;
        goto enter;
    }
    st = (sub_001C7EE1() % 8 < 1) ? 0x10 : 0xD;
enter:
    obj->flags10 &= ~6u;
    act->flags4C |= 0x38;
    sub_00113040(obj, act, st);
}
