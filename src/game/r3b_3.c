/* Area r3b: character state helpers in 0x00130000..0x0013FFFF (r3b_3). Names inferred. */
#include "r3b.h"

/* 0x00130AF0: finish animation 0x40 and reset the work block's motion vector to (0, 0, 0) with weight 1. */
void r3b_Reset130AF0(R3bObj *obj, R3bAct *act)
{
    R3bWork *w;

    if (sub_001456E0(obj, act, 0x40, 0) == 1)
        sub_0001D4E0(obj);
    w = act->work278;
    w->v160[3] = 0.0f;
    w->v160[2] = 0.0f;
    w->v160[1] = 0.0f;
    w->f170 = 1.0f;
    obj->flags0C &= ~0x20u;
}

/* 0x00135500: step act's +0x78 vector toward the work block's target and scale it by obj speed * 0.9. */
void r3b_Step135500(R3bObj *obj, R3bAct *act)
{
    float *v = act->v78;

    sub_00145C90(v, obj->p20, act->work278->v160);
    sub_00145CD0(v, v, obj->fE8 * 0.9f);
}

/* 0x001356D0: condition callback: when the animation window (c->a10.f, c->a14.f) is reached, apply c->i18. */
void r3b_AnimCond1356D0(R3bObj *obj, R3bAct *act, R3bCond *c)
{
    R3bWork *w = act->work278;

    if (sub_00145940(obj, w->i140, w->i148, c->a10.f, c->a14.f))
        sub_001459D0(obj, w->i140, w->i148, c->i18);
}

/* 0x00135780: 1 when some live object of type (2, kind) has a kind-4 component with bit 0x100 set.
   regargs: kind=EAX. */
int r3b_Any135780(int kind)
{
    void *o;
    R3bAct *c;

    for (o = sub_000EDC20(2, kind); o; o = sub_000EDC20(-1, -1)) {
        c = sub_0001D960(o, 4);
        if (c && (c->flags4C & 0x100))
            return 1;
    }
    return 0;
}

/* 0x00135C10: copy the vector keyed by `key` from record idx of 0x0031C878 to dst (when the work block allows it).
   regargs: act=ECX idx=EAX key=ESI dst=stack. Hangs if the key is not in the record. */
void r3b_KeyVec135C10(R3bAct *act, int idx, int key, float *dst)
{
    R3bKeyVec *r;
    int i;

    if (act->work278->flags08 & 1) {
        r = &r3b_keyvec31C878[idx];
        for (i = 0; i < 2; i++)
            if (r->key[i] == key)
                break;
        if (i >= 2)
            for (;;) ;
        sub_000F5D40(dst, r->v[i]);
    }
}

/* 0x00136070: when the animation has finished and work flag 0x80000 is up, drop it and notify 0x00088190. */
void r3b_AnimDone136070(R3bObj *obj, R3bAct *act)
{
    R3bWork *w;

    if (sub_000833E0(obj->anim30)) {
        w = act->work278;
        if (w->flags08 & 0x80000) {
            w->flags08 &= ~0x80000u;
            sub_00088190();
        }
    }
}

/* 0x001383F0: enter state 0x22 and arm timer slot 2 with (1, 3). */
void r3b_State1383F0(R3bObj *obj, R3bAct *act)
{
    R3bTimer *t;

    sub_00113090(obj, act, 0x22);
    obj->flags10 |= 0x20;
    act->flags4C &= ~0x100u;
    act->work278->u04.flags |= 0x400000;
    t = sub_00113430(act, 2);
    t->a10.i = 1;
    t->a14.i = 3;
}

/* 0x00138450: enter state 0x21 and arm timer slot 2 with (2, 4). */
void r3b_State138450(R3bObj *obj, R3bAct *act)
{
    R3bTimer *t;

    sub_00113090(obj, act, 0x21);
    obj->flags10 |= 0x20;
    act->flags4C &= ~0x100u;
    act->work278->u04.flags |= 0x400000;
    t = sub_00113430(act, 2);
    t->a10.i = 2;
    t->a14.i = 4;
}

/* 0x001384B0: enter state 0x23 and arm timer slot 2 with (3, 5). */
void r3b_State1384B0(R3bObj *obj, R3bAct *act)
{
    R3bTimer *t;

    sub_00113090(obj, act, 0x23);
    act->work278->u04.flags |= 0x400000;
    obj->flags10 |= 0x20;
    act->flags4C &= ~0x100u;
    t = sub_00113430(act, 2);
    t->a10.i = 3;
    t->a14.i = 5;
}

/* 0x00138500: enter state 0x30, 0x64 or 0x65 depending on work flags 0x8000000 / 0x4000000, clearing them. */
void r3b_State138500(R3bObj *obj, R3bAct *act)
{
    R3bWork *w = act->work278;
    uint32_t f = w->u04.flags;
    int st;

    if (f & 0x8000000)
        st = 0x30;
    else
        st = (~(f >> 26) & 1) | 0x64;
    w->u04.flags = f & 0xF1FFFFFF;
    sub_00113090(obj, act, st);
    obj->flags10 |= 0x24;
}

/* 0x00138550: enter state 0x14, award one exclamation, and raise obj flag 4 unless only work flag 0x20000000 is up. */
void r3b_State138550(R3bObj *obj, R3bAct *act)
{
    R3bWork *w = act->work278;

    sub_00113090(obj, act, 0x14);
    Grade_AddExclamations(1);
    obj->flags10 |= 0x20;
    if ((w->u04.flags & 0x40000000) || !(w->u04.flags & 0x60000000))
        obj->flags10 |= 4;
}

/* 0x001385A0: enter state 0x15, start effect 0xA4 at the model position and attach part 9. */
void r3b_State1385A0(R3bObj *obj, R3bAct *act)
{
    sub_00113090(obj, act, 0x15);
    act->h6C = sub_000494D0(0xA4, (const float *)(obj->p20 + 0x30), 0);
    obj->flags10 |= 0x30;
    act->h70 = sub_00036750(obj, 9);
}

/* 0x001385F0: enter state 0x10 or 0x11 (by side bit) and set the matching flags. */
void r3b_State1385F0(R3bObj *obj, R3bAct *act)
{
    sub_00113090(obj, act, (act->b22 & 1) + 0x10);
    obj->flags10 = (obj->flags10 & ~0x20u) | 6;
    act->flags4C &= ~0x18u;
    act->work278->u04.flags |= 0x800000;
}

/* 0x00138840: unless already in sub-state 0x24, enter state 0x42 and start timer slot 4. */
void r3b_State138840(R3bObj *obj, R3bAct *act)
{
    if (act->i54 != 0x24) {
        sub_00113090(obj, act, 0x42);
        obj->flags0C &= ~0x20u;
        obj->flags10 &= ~0x10u;
        act->flags4C &= ~8u;
        sub_00113400(act, 4);
        act->work278->u04.flags |= 0x100000;
    }
}

/* 0x001388A0: enter state 0 with speed 10. */
void r3b_State1388A0(R3bObj *obj, R3bAct *act)
{
    obj->flags10 = (obj->flags10 & ~0x20u) | 5;
    act->flags4C = (act->flags4C & 0xFEFFFF8F) | 0x200;
    act->f74 = 10.0f;
    sub_00113090(obj, act, 0);
}

/* 0x001388E0: enter state 0x20 with speed 10. */
void r3b_State1388E0(R3bObj *obj, R3bAct *act)
{
    obj->flags10 = (obj->flags10 & ~0x20u) | 5;
    act->flags4C = (act->flags4C & 0xFEFFFF8F) | 0x200;
    act->f74 = 10.0f;
    sub_00113090(obj, act, 0x20);
}

/* 0x00138920: enter state 0x41 with speed 10. */
void r3b_State138920(R3bObj *obj, R3bAct *act)
{
    obj->flags10 = (obj->flags10 & ~0x20u) | 5;
    act->flags4C = (act->flags4C & 0xFEFFFF8F) | 0x200;
    act->f74 = 10.0f;
    sub_00113090(obj, act, 0x41);
}

/* 0x00138960: when the animation has finished, enter state 0xD. */
void r3b_State138960(R3bObj *obj, R3bAct *act)
{
    if (sub_000833E0(obj->anim30)) {
        obj->flags10 &= ~6u;
        obj->flags0C |= 0x20;
        act->flags4C |= 0x30;
        sub_00113040(obj, act, 0xD);
    }
}
