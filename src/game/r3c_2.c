/* Area r3c: game functions in 0x00160000..0x0017FFFF (r3c_2). Names inferred. */
#include "r3c.h"

/* 0x00174CD0: release every loaded id of the table at 0x00279F00 (except 0x21D). */
void r3c_ReleaseIds174CD0(void)
{
    int i, id;

    sub_000ED600(4);
    for (i = 0; i < 40; i++) {
        id = r3c_ids279F00[i].id;
        if (id != 0x21D && sub_0004F6D0(id))
            sub_0004F5D0(id);
    }
}

/* 0x00178C50: step, then leave to state 1 once act->f5C passes 10 frames. */
void r3c_Step178C50(R3cObj *obj, R3cObj *act)
{
    sub_001789E0(obj, act);
    if (act->f5C > r3c_frameSeconds * 10.0f)
        sub_00113040(obj, act, 1);
}

/* 0x001740A0: when 0x001730A0 accepts, reset b's state and run fsm entry 1.
   calls 0x001730A0 with EAX=a EBX=b and 1.0f on the stack. */
void r3c_Enter1740A0(R3cObj *a, R3cObj *b)
{
    if (sub_001730A0(a, b, 1.0f)) {
        b->flags4C = 1;
        b->state50 = 0;
        b->f54 = 0.0f;
        r3_fsmEnter32B1B0[1](a, b);
    }
}

/* 0x00176EC0: apply the jump impulse once (work flag 0x10), then enter state 3. */
void r3c_Jump176EC0(R3cObj *obj, R3cObj *act)
{
    if (!(act->work278->flags00 & 0x10)) {
        obj->pos60[1] += obj->f70 * 30.0f;
        act->work278->flags00 |= 0x10;
    }
    sub_00113090(obj, act, 3);
}

/* 0x00177FC0: enter state 3, then apply the jump impulse once (work flag 0x100). */
void r3c_Jump177FC0(R3cObj *obj, R3cObj *act)
{
    R3cWork *w = act->work278;

    sub_00113090(obj, act, 3);
    if (!(w->flags00 & 0x100)) {
        obj->pos60[1] += obj->f70 * 30.0f;
        w->flags00 |= 0x100;
    }
}

/* 0x001790F0: in game modes 0 and 1, start effect 0xE for every set slot of 0x003FDAE0. */
void r3c_Effects1790F0(void)
{
    int i;

    if (sub_000E0770()->i324 != 0 && sub_000E0770()->i324 != 1)
        return;
    for (i = 0; i < 9; i++) {
        if (r3c_s3FDAE0[i] != 0)
            sub_000ED630(4, 0xE, 0, 0, i);
    }
}

/* 0x0017B0B0: set the node timer to -2 frames, flag the object and spawn effect 0x19C at it. */
void r3c_Spawn17B0B0(R3cObj *obj, void *act)
{
    sub_001133E0(act, 0)->f10 = r3c_frameSeconds * -2.0f;
    sub_00036750(obj, 1);
    sub_000494D0(0x19C, obj->pos60, 0);
}

/* 0x0017C4F0: release the objects of the six records at 0x003FDC70. */
void r3c_Release17C4F0(void)
{
    int i;
    R3cA4290 *x;

    for (i = 0; i < 6; i++) {
        if (r3c_recs3FDC70[i].obj != 0) {
            x = sub_000A4290(r3c_recs3FDC70[i].id18);
            sub_000A22C0(x, r3c_recs3FDC70[i].obj);
            sub_000ED780(r3c_recs3FDC70[i].obj);
            x->i40 = 6;
        }
    }
}

/* 0x0017CB10: clear obj flag 0x200 and reset the work block (rate 38 per second). */
void r3c_Reset17CB10(R3cObj *obj, R3cObj *act)
{
    R3cWork *w;

    obj->flags0C &= ~0x200u;
    w = act->work278;
    w->f44 = 0.0f;
    w->i14 = 0;
    w->s26 = 1;
    w->f48 = 38.0f / r3c_framesPerSecond;
}

/* 0x00170F10: when b is flagged and its timer ran out, reset its motion and enter state 2. */
void r3c_Land170F10(void *a, R3cObj *b)
{
    if ((b->flags4C & 1) && b->f70 <= 0.0f) {
        b->f78 = 0.0f;
        b->f7C = -1.0f;
        b->f80 = 0.0f;
        b->f84 = 0.0f;
        b->state50 = 2;
        b->i54 = 0;
        b->f58 = 0.0f;
    }
}

/* 0x00171AA0: player parameter idx (integer table, three columns; second set for the alternate mode). */
int r3c_ParamI171AA0(R3cPlayer *p, void *unused, int idx)
{
    R3cParams *t = *r3c_params32B114;

    if (!(p->bEC & 0x40) && !(p->flagsD60 & 2))
        return t->i[idx * 3 + p->iD6C];
    return t->i[idx * 3 + 0x2A + p->iD6C];
}

/* 0x00171AF0: player float parameter at 0x54 (0x57 in the alternate set). */
float r3c_ParamF171AF0(R3cPlayer *p)
{
    R3cParams *t = *r3c_params32B114;

    if (!(p->bEC & 0x40))
        return t->f[0x54 + p->iD6C];
    return t->f[0x57 + p->iD6C];
}

/* 0x00171B40: player float parameter at 0x5A (0x5D in the alternate set). */
float r3c_ParamF171B40(R3cPlayer *p)
{
    R3cParams *t = *r3c_params32B114;

    if (!(p->bEC & 0x40))
        return t->f[0x5A + p->iD6C];
    return t->f[0x5D + p->iD6C];
}

/* 0x00171B90: player float parameter at 0x6C (0x6F in the alternate set). */
float r3c_ParamF171B90(R3cPlayer *p)
{
    R3cParams *t = *r3c_params32B114;

    if (!(p->bEC & 0x40))
        return t->f[0x6C + p->iD6C];
    return t->f[0x6F + p->iD6C];
}

/* 0x00171BE0: player float parameter at 0x72 (0x75 in the alternate set). */
float r3c_ParamF171BE0(R3cPlayer *p)
{
    R3cParams *t = *r3c_params32B114;

    if (!(p->bEC & 0x40))
        return t->f[0x72 + p->iD6C];
    return t->f[0x75 + p->iD6C];
}

/* 0x00175DB0: enter state 3, then apply the jump impulse once (work flag 0x100). */
void r3c_Jump175DB0(R3cObj *obj, R3cObj *act)
{
    sub_00113090(obj, act, 3);
    if (!(act->work278->flags00 & 0x100)) {
        obj->pos60[1] += obj->f70 * 30.0f;
        act->work278->flags00 |= 0x100;
    }
}

/* 0x00179D70: is the tracked object at 0x003FDC68 touching the player (radii + 4)? */
int r3c_Touch179D70(void)
{
    R3cObj *e = r3c_obj3FDC68;
    R3cObj *p = (R3cObj *)g_playerObj;

    if ((r3c_flags3FDC3C & 8) &&
        p->fB0 + e->fB0 + 4.0f > sub_001B2770(e->pos60, p->pos60))
        return 1;
    return 0;
}

/* 0x0017B060: refresh obj, set the node timer to -2 frames, flag obj and spawn effect 0x19C at it. */
void r3c_Spawn17B060(R3cObj *obj, void *act)
{
    sub_0001D700(obj);
    sub_001133E0(act, 0)->f10 = r3c_frameSeconds * -2.0f;
    sub_00036750(obj, 1);
    sub_000494D0(0x19C, obj->pos60, 0);
}

/* 0x0017B2D0: clear the node timer, step act's vectors at rate 60 and turn obj toward the player. */
void r3c_Turn17B2D0(R3cObj *obj, R3cObj *act)
{
    sub_001133E0(act, 0)->f10 = 0.0f;
    sub_001ADB60(&act->f78, &act->f84 + 1, 60.0f);
    obj->f54 += sub_00113200(obj, ((R3cObj *)g_playerObj)->pos60);
}

/* 0x0017D920: count the work timer down and stop the owner (state 3) when the stage is in mode 2. */
void r3c_Tick17D920(void *obj, R3cObj *act)
{
    R3cWork *w = act->work278;

    if (w->f6C > 0.0f)
        w->f6C -= r3c_frameSeconds;
    if (sub_000F40B0() == 2 && w->act04->state50 == 2)
        sub_00113040(w->obj00, w->act04, 3);
}

/* 0x0017E690: report progress to 0x0003AEB0 and release o when the stage reaches step 3. */
void r3c_Report17E690(void *o, R3cObj *act)
{
    R3cWork *w = act->work278;

    sub_0003AEB0(w->i14 + 1, w->i10 == 0);
    if (sub_000F3B50(sub_00101220()) == 3)
        sub_000ED780(o);
}

/* 0x0017E8C0: make sure the object has its handle and its effect 0x333. */
void r3c_Ensure17E8C0(R3cObj *obj, R3cObj *act)
{
    R3cWork *w = act->work278;

    w->i10 = 0;
    if (w->i08 == 0)
        w->i08 = sub_00036750(obj, 0);
    if (w->i20 == -1)
        w->i20 = sub_000494D0(0x333, obj->pos60, 1);
}

/* 0x00171CF0: random player float parameter 0x78..0x87 scaled by the difficulty factor (0.5, 1, 1.5). */
float r3c_RandParam171CF0(void)
{
    int r = sub_001C7EE1() % 16;
    float scale[3];

    scale[0] = 0.5f;
    scale[1] = 1.0f;
    scale[2] = 1.5f;
    return (*r3c_params32B114)->f[0x78 + r] * scale[r3c_i413178];
}

/* 0x00172340: deactivate o, drop component 8's sound handle and finish through 0x000CE9F0. */
int r3c_End172340(R3cObj *o)
{
    R3cObj *c = sub_0001D960(o, 8);

    if (c == 0)
        for (;;)
            ;
    o->flags0C &= ~1u;
    sub_0001EB80(o);
    if (c->i68 >= 0) {
        sub_00048250(c->i68);
        c->i68 = -1;
    }
    sub_000CE9F0(o);
    return 1;
}

/* 0x001723A0: run component 8's state callback, advance its two clocks and run its +0x6C callback. */
void r3c_Run1723A0(R3cObj *o)
{
    R3cObj *c = sub_0001D960(o, 8);

    if (c == 0)
        for (;;)
            ;
    r3c_fns32B1DC[c->flags4C](o, c);
    c->f58 -= r3c_frameSeconds;
    c->pos60[1] += r3c_frameSeconds;
    c->fn6C(o, c);
}

/* 0x00174410: make o (a kind-6 object) the global controlled object and enter fsm state 9. */
void r3c_Take174410(R3cObj *o)
{
    R3cObj *c;

    if (o == 0 || o->type04 != 6 || r3c_obj3FD7C4 != 0)
        for (;;)
            ;
    c = sub_0001D960(o, 8);
    if (c == 0)
        for (;;)
            ;
    c->flags4C = 9;
    c->state50 = 0;
    c->f54 = 0.0f;
    r3_fsmEnter32B1B0[9](o, c);
    r3c_obj3FD7C4 = o;
}

/* 0x0017B100: flag obj, set the node timer to -15 frames and restart the current animation key. */
void r3c_Restart17B100(R3cObj *obj, void *act)
{
    R3cAnim *a;

    obj->flags10 |= 0x20;
    sub_001133E0(act, 0)->f10 = r3c_frameSeconds * -15.0f;
    a = obj->pa30;
    sub_001AEDD0(obj->pa30->inst14, sub_00083120(a, a->i08)->i10);
}

/* 0x0017C0E0: two-phase step: phase 0 sets obj flag 4, phase 1 waits for act->f5C to reach st->lo. */
void r3c_Phase17C0E0(R3cObj *obj, R3cObj *act, R3cRange *st)
{
    switch (st->i0C) {
    case 0:
        obj->flags10 |= 4;
        if (st->i00 != 0)
            st->i00 = 2;
        st->i0C++;
        break;
    case 1:
        if (act->f5C >= st->lo) {
            obj->flags10 &= ~4u;
            if (st->i00 != 0)
                st->i00 = 1;
            sub_00113370(act, st);
        }
        break;
    }
}

/* 0x00171EB0: integer table value (table k, entry j, row a, column b); column 0 scales by difficulty (1, 1, 2) except table 0x11. */
int r3c_TableVal171EB0(int k, int j, int a, int b)
{
    int v = r3c_tables32B110[k][j]->vals18[b + a * 3];
    int scale[3];

    if (b == 0 && k != 0x11) {
        scale[0] = 1;
        scale[1] = 1;
        scale[2] = 2;
        v = scale[r3c_i413178] * v;
    }
    return v;
}

/* 0x00178470: release every type-4 kind-0x1A item whose own component is active. */
void r3c_Release178470(void)
{
    int i;
    R3cItem150 *e;
    R3cObj *c;

    if (r3c_items3FD7D4 == 0)
        return;
    for (i = 0; i < 16; i++) {
        e = &r3c_items3FD7D4[i];
        if (e->type04 == 4 && e->i08 == 0x1A) {
            c = sub_0001D960(e, sub_000EE5F0(e));
            if (c != 0 && c->state50 != 0)
                sub_000ED780(e);
        }
    }
}

/* 0x0017B160: flag obj, set the node timer to -30 frames and act->f74 to 2, then spawn effect 0x197 at obj. */
void r3c_Spawn17B160(R3cObj *obj, R3cObj *act)
{
    obj->flags10 |= 0x20;
    sub_001133E0(act, 0)->f10 = r3c_frameSeconds * -30.0f;
    act->f74 = 2.0f;
    sub_00036750(obj, 2);
    sub_000494D0(0x197, obj->pos60, 0);
}

/* 0x00169D30: is the player within 60 of o and inside its 90-degree front cone?
   regargs: o=EDI. */
int r3c_InFront169D30(R3cObj *o)
{
    float *pp = ((R3cObj *)g_playerObj)->pos60;
    float dist = sub_001B2770(o->pos60, pp);
    float ang = sub_00113290(o, pp);

    if (60.0f > dist && 0.78539819f > ang && ang > -0.78539819f)
        return 1;
    return 0;
}

/* 0x00170C10: is o out of the player's reach (busy, beyond 200, or more than 30 apart in height)?
   regargs: o=EDI. */
int r3c_OutOfReach170C10(R3cObj *o)
{
    R3cObj *p = (R3cObj *)g_playerObj;

    if (sub_00087500())
        return 1;
    if (sub_001B2770(o->pos60, p->pos60) >= 200.0f)
        return 1;
    if (sub_001A3F30(o->pos60[1] - p->pos60[1]) >= 30.0f)
        return 1;
    return 0;
}

/* 0x00178010: apply the jump impulse once (work flag 0x100); when 0x00176150 finishes clear flag 2 and leave to state 0. */
void r3c_Jump178010(R3cObj *obj, R3cObj *act)
{
    R3cWork *w = act->work278;

    if (!(w->flags00 & 0x100)) {
        obj->pos60[1] += obj->f70 * 30.0f;
        w->flags00 |= 0x100;
    }
    if (sub_00176150(obj, act, &w->i14)) {
        act->work278->flags00 &= ~2u;
        sub_00113040(obj, act, 0);
    }
}
