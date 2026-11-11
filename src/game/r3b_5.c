/* Area r3b: state callbacks and script steps in 0x00138000..0x0013BFFF (r3b_5). Names inferred. */
#include "r3b.h"

/* 0x001389B0: when the animation has finished, enter state 0x10 one time in 16, else stop and enter state 0xC. */
void r3b_State1389B0(R3bObj *obj, R3bAct *act)
{
    if (sub_000833E0(obj->anim30)) {
        if (sub_001C7EE1() % 16 < 1) {
            sub_00113040(obj, act, 0x10);
        } else {
            act->f74 = 0.0f;
            sub_00113040(obj, act, 0xC);
        }
    }
}

/* 0x00139480: script step: phase 0 enters state s->a10, phase 1 waits for the animation, then enters s->i14 and finishes. */
void r3b_StepAnim139480(R3bObj *obj, R3bAct *act, R3bStep *s)
{
    switch (s->phase0C) {
    case 0:
        sub_00113090(obj, act, s->a10.i);
        s->phase0C++;
        /* fall through */
    case 1:
        if (sub_000833E0(obj->anim30)) {
            sub_00113040(obj, act, s->i14);
            sub_00113370(act, s);
        }
        break;
    }
}

/* 0x001394E0: when b's +0xFC value is outside [c->min1C, c->max18], move it (clamped to [lo14, hi10]) into a's +0x54. */
void r3b_Transfer1394E0(R3bObj *a, R3bObj *b, R3bClamp *c)
{
    float v = b->fFC;

    if (c->min1C > v || v > c->max18) {
        if (v > c->hi10)
            v = c->hi10;
        if (c->lo14 > v)
            v = c->lo14;
        a->f54 += v;
        b->fFC -= v;
    }
}

/* 0x00139A70: script step: count phases 0 and 1, then in phase 2 enter state s->a10 and finish. */
void r3b_StepWait139A70(R3bObj *obj, R3bAct *act, R3bStep *s)
{
    int ph = s->phase0C;

    if (ph >= 0) {
        if (ph <= 1) {
            s->phase0C = ph + 1;
        } else if (ph == 2) {
            sub_00113040(obj, act, s->a10.i);
            sub_00113370(act, s);
        }
    }
}

/* 0x00139AB0: script step: raise obj flag 4 for the step's time (s->a10 seconds), then drop it and finish. */
void r3b_StepFlag139AB0(R3bObj *obj, R3bAct *act, R3bStep *s)
{
    switch (s->phase0C) {
    case 0:
        obj->flags10 |= 4;
        if (s->i00)
            s->i00 = 2;
        s->phase0C++;
        break;
    case 1:
        if (s->f08 >= s->a10.f) {
            obj->flags10 &= ~4u;
            if (s->i00)
                s->i00 = 1;
            sub_00113370(act, s);
        }
        break;
    }
}

/* 0x00139C50: 1 when b targets a type-13 object with flag bit 0, c->f0 >= b's +0x100 and c->f4 >= |b's +0xFC|. */
int r3b_InReach139C50(R3bObj *a, R3bObj *b, R3bPair *c)
{
    R3bObj *t;

    if (b->iF8 == 1) {
        t = b->p104;
        if ((t->flags0C & 1) && t->type04 == 0xD && c->f0 >= b->f100
            && c->f4 >= sub_001A3F30(b->fFC))
            return 1;
    }
    return 0;
}

/* 0x00139CB0: 1 when b's +0x100 <= c->f0 and |b's +0xFC| <= c->f4. */
int r3b_InRange139CB0(R3bObj *a, R3bObj *b, R3bPair *c)
{
    if (b->f100 > c->f0)
        return 0;
    if (sub_001A3F30(b->fFC) > c->f4)
        return 0;
    return 1;
}

/* 0x00139CF0: raise work flag bit 0 on every active item of type 0 or 14 among the first six items. */
void r3b_MarkItems139CF0(void)
{
    int i;
    R3bItem *e;
    R3bAct *c;

    for (i = 0; i < 6; i++) {
        e = &r3b_items3F74FC[i];
        if ((e->flags0C & 1) && (e->type08 == 0 || e->type08 == 0xE)) {
            c = sub_0001D960(e, 4);
            c->work278->u04.flags |= 1;
        }
    }
}

/* 0x00139DB0: 1 when b is active (+0x54) and its +0x64 id is one of 0, 1, 0x16, 0x17. */
int r3b_IdInList139DB0(void *a, R3bAct *b)
{
    int ids[5];
    int *p;

    ids[0] = 0;
    ids[1] = 1;
    ids[2] = 0x16;
    ids[3] = 0x17;
    ids[4] = -1;
    if (b->i54)
        for (p = ids; *p != -1; p++)
            if (b->i64 == *p)
                return 1;
    return 0;
}

/* 0x0013B390: enter state 7: hide, restart the animation, attach part 1 and set speed 25 units per second. */
void r3b_State13B390(R3bObj *obj, R3bAct *act)
{
    sub_0001D700(obj);
    obj->flags10 |= 5;
    act->flags4C &= ~0x78u;
    sub_00113090(obj, act, 7);
    sub_001AEDD0(obj->pa30->inst14, 0);
    sub_00036750(obj, 1);
    act->f74 = 25.0f / r3_frameUnits * r3_frameDelta;
}
