/* Area r3b: small helpers in 0x00160000..0x0018FFFF (r3b_2). Names inferred. */
#include "r3b.h"

/* 0x001771D0: forward to 0x00113A40. */
void r3b_Fwd1771D0(void *obj, void *act)
{
    b1b_EnemyMarkParts(obj, act);
}

/* 0x00166CD0: forward to the timer tick 0x00167670. */
void r3b_Fwd166CD0(void)
{
    b16_TickTimer();
}

/* 0x0017E300: forward to 0x0017D780. */
void r3b_Fwd17E300(void)
{
    sub_0017D780();
}

/* 0x0017F280: enter `state` on obj's kind-6 component, if it has one.
   regargs: obj=ESI state=stack. */
void r3b_Enter17F280(R3bObj *obj, int state)
{
    R3bAct *c = sub_0001D960(obj, 6);

    if (c)
        sub_00113040(obj, c, state);
}

/* 0x001833B0: count the timer at 0x003FE39C down by one frame while positive. */
void r3b_Tick1833B0(void)
{
    if (r3b_timer3FE39C > 0.0f)
        r3b_timer3FE39C -= r3_frameDelta;
}

/* 0x001833E0: clear 0x003FE398. */
void r3b_Clear1833E0(void)
{
    r3b_i3FE398 = 0;
}

/* 0x00183A70: clear 0x003FE38C and 0x003FE390. */
void r3b_Clear183A70(void)
{
    r3b_i3FE38C = 0;
    r3b_i3FE390 = 0;
}

/* 0x00183C10: drop bit 0 of a's flags and refresh it; hangs on a null object. Returns 1. */
int r3b_Unmark183C10(R3bObj *a)
{
    if (!a)
        for (;;) ;
    if (a->flags0C & 1) {
        a->flags0C &= ~1u;
        sub_0001EB80(a);
    }
    return 1;
}

/* 0x00184020: clear 0x003FE3A4 and 0x003FE3A8 (0x003FE3A4 is stored twice in the original). */
void r3b_Clear184020(void)
{
    r3b_i3FE3A4 = 0;
    r3b_i3FE3A8 = 0;
    r3b_i3FE3A4 = 0;
}

/* 0x00184240: make b target the player. */
void r3b_TargetPlayer184240(void *a, R3bObj *b)
{
    b->p104 = (R3bObj *)g_playerObj;
    b->iF8 = 1;
}

/* 0x00184370: 0x001456E0 with the last two arguments 0. */
int r3b_Check184370(R3bObj *obj, R3bAct *act)
{
    return sub_001456E0(obj, act, 0, 0);
}

/* 0x00184510: reset act and enter state 1. */
void r3b_Enter184510(R3bObj *obj, R3bAct *act)
{
    sub_001134B0(act);
    sub_00113040(obj, act, 1);
}

/* 0x001854D0: hand v to obj's kind-6 component and raise its flag bit 0. Hangs if the component is not kind 6. */
void r3b_Give1854D0(R3bObj *obj, void *v)
{
    R3bAct *c = sub_0001D960(obj, 6);
    R3bWork *w;

    if (c->kind00 != 6)
        for (;;) ;
    w = c->work278;
    w->u04.p = v;
    w->flags18 |= 1;
}

/* 0x00185DA0: forward to 0x001859C0. */
void r3b_Fwd185DA0(void *obj, void *act)
{
    sub_001859C0(obj, act);
}

/* 0x00185DB0: forward to 0x00185C90. */
void r3b_Fwd185DB0(void *obj, void *act)
{
    sub_00185C90(obj, act);
}

/* 0x001863E0: bit 3 of the work block's flags. */
int r3b_Bit1863E0(void *obj, R3bAct *act)
{
    return (act->work278->flags18 >> 3) & 1;
}

/* 0x00186460: 1 when 0x003ED238 is set. */
int r3b_IsSet186460(void)
{
    return a80_Get3ED238() != 0;
}

/* 0x00188E90: zero the work block's +0x0C value. */
void r3b_Zero188E90(void *obj, R3bAct *act)
{
    act->work278->f0C = 0.0f;
}

/* 0x00189A70: 0x000ED600(5). */
void r3b_Call189A70(void)
{
    sub_000ED600(5);
}

/* 0x0018AB50: raise a's flag bit 0 and zero b's +0x70. */
void r3b_Mark18AB50(R3bObj *a, R3bObj *b)
{
    a->flags10 |= 1;
    b->f70 = 0.0f;
}

/* 0x0018B100: reset b's +0x4C..+0x58 to (0, 0, 0, 1). */
void r3b_Reset18B100(void *a, R3bObj *b)
{
    b->f4C = 0.0f;
    b->f50 = 0.0f;
    b->f54 = 0.0f;
    b->f58 = 1.0f;
}

/* 0x0018C3E0: clear the 0x140-byte block at 0x003FFB38. */
void r3b_ClearBlock18C3E0(void)
{
    int i;

    for (i = 0; i < 0x50; i++)
        r3b_block3FFB38[i] = 0;
}

/* 0x0018C6A0: release p through 0x000ED780. */
void r3b_Release18C6A0(void *p)
{
    sub_000ED780(p);
}

/* 0x0018C790: drop bit 0 of b's motion flags. Returns 1. */
int r3b_Stop18C790(void *a, R3bComp74 *b)
{
    b->p74->flags &= ~1u;
    return 1;
}

/* 0x0018D3A0: clear the 0x168-byte block at 0x003FFC78. */
void r3b_ClearBlock18D3A0(void)
{
    int i;

    for (i = 0; i < 0x5A; i++)
        r3b_block3FFC78[i] = 0;
}

/* 0x0018D650: clear the +0x14 handle of a's kind-7 component, if any. */
void r3b_Unlink18D650(R3bObj *a)
{
    R3bComp74 *c;

    if (a) {
        c = sub_0001D960(a, 7);
        if (c)
            c->p74->p14 = 0;
    }
}

/* 0x0018D740: drop bit 0 of b's motion flags and notify its +0x14 handle. Returns 1. */
int r3b_Stop18D740(void *a, R3bComp74 *b)
{
    R3bMotion *s = b->p74;

    s->flags &= ~1u;
    if (s->p14)
        sub_001751D0(s->p14, a);
    return 1;
}

/* 0x0018ECB0: when 0x003ED238 is set, 0x00189DA0(a, b, 7). */
void r3b_Call18ECB0(void *a, void *b)
{
    if (a80_Get3ED238())
        sub_00189DA0(a, b, 7);
}
