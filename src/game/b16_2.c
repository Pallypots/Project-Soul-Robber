/* Area b16, group 2: actor state handlers 0x00167270-0x0016FC90. Names inferred. */
#include "b16.h"

/* 0x00167270: set flag 2 on the actor and on every linked model's part. */
void b16_HoldAll(B16Model *m, B16Act *a)
{
    a->flags4C |= 2;
    for (; m != 0; m = m->next)
        if (m->anim != 0 && m->anim->part != 0)
            m->anim->part->flags |= 2;
}

/* 0x001672B0: clear flag 2 everywhere and restart the current animation. */
void b16_ReleaseAll(B16Model *m, B16Act *a)
{
    B16Model *n;
    a->flags4C &= ~2;
    for (n = m; n != 0; n = n->next)
        if (n->anim != 0 && n->anim->part != 0)
            n->anim->part->flags &= ~2;
    b16_PlayAnim(m, a, a->animId);
}

/* 0x00167380: initialise the embedded link and attach it to a bank. */
void b16_LinkInit(B16Model *m, B16Act *a, int bank)
{
    B16Link *l = &a->link;
    sub_001B2150(l);
    l->owner = m;
    l->fn04 = (void *)sub_00166FF0;
    l->i10 = 0;
    l->i1C = 0;
    l->f14 = 0.0f;
    l->f2C = 0.0f;
    l->f30 = 0.0f;
    sub_001B2160(m->ctx->banks + bank * 0x180, l);
}

/* 0x001677A0: release the work block. */
int b16_WorkFree(B16Model *m, B16Act *a)
{
    B16Work *w = a->work;
    if (w->flags & 0x200000)
        sub_000D9B30(0x3FF);
    if (w->obj3C != 0)
        b16_Free33A40(w->obj3C);
    B16_ZERO(a->work, sizeof(B16Work));
    w->flags &= ~1;
    return 1;
}

/* 0x00167DF0: idle animation, flags 0x42 and work flag 0x40. */
void b16_StartIdle(B16Model *m, B16Act *a)
{
    B16Work *w = a->work;
    b16_PlayAnim(m, a, 0);
    a->flags10 |= 0x42;
    w->flags |= 0x40;
}

/* 0x00169A30: go to state 12 unless work flag 0x1000. */
void b16_To12(B16Model *m, B16Act *a)
{
    if (!(a->work->flags & 0x1000))
        b16_SetState(m, a, 12);
}

/* 0x0016A570: go to state 7 when the animation ends. */
void b16_AnimDoneTo7(B16Model *m, B16Act *a)
{
    if (sub_000833E0(m->anim))
        b16_SetState(m, a, 7);
}

/* 0x0016A5A0..0x0016E450: play a fixed animation. */
void b16_Anim5(B16Model *m, B16Act *a) { b16_PlayAnim(m, a, 5); }
void b16_Anim4(B16Model *m, B16Act *a) { b16_PlayAnim(m, a, 4); }
void b16_Anim3(B16Model *m, B16Act *a) { b16_PlayAnim(m, a, 3); }
void b16_Anim0(B16Model *m, B16Act *a) { b16_PlayAnim(m, a, 0); }
void b16_Anim1(B16Model *m, B16Act *a) { b16_PlayAnim(m, a, 1); }
void b16_Anim2(B16Model *m, B16Act *a) { b16_PlayAnim(m, a, 2); }

/* 0x0016A6B0: copy the target point, raised by 13, into the model position. */
void b16_AimAtPoint(B16Model *m, B16Act *a)
{
    float v[4];
    int i = a->work->point;
    const float *p = i < 0 ? (const float *)(b16_player + 0x60) : b16_points[i];
    b16_VecCopy(v, p);
    v[1] += 13.0f;
    b16_VecCopy(m->pos60, v);
}

/* 0x0016ACD0: work flag 0x40, notify, then state 4. */
void b16_Enter4(B16Model *m, B16Act *a)
{
    a->work->flags |= 0x40;
    b16_Notify36750(m, 1);
    sub_000414A0(-1);
    b16_SetState(m, a, 4);
}

/* 0x0016AFA0: set work flag 4. */
void b16_WorkFlag4(B16Model *m, B16Act *a) { a->work->flags |= 4; }

/* 0x0016B0E0: wait a random 30..59 frames, then state 15. */
void b16_WaitTo15(B16Model *m, B16Act *a)
{
    switch (a->step) {
    case 0:
        a->timer = ((float)(sub_001C7EE1() % 30) + 30.0f) / b16_frameUnits * b16_frameDelta;
        a->step++;
    case 1:
        if (a->timer < 0.0f)
            b16_SetState(m, a, 15);
    }
}

/* 0x0016B2F0: go to state 14 when the animation ends. */
void b16_AnimDoneTo14(B16Model *m, B16Act *a)
{
    if (sub_000833E0(m->anim))
        b16_SetState(m, a, 14);
}

/* 0x0016B910: update, and on work flag 8 go to state 3. */
void b16_CheckTo3(B16Model *m, B16Act *a)
{
    B16Work *w = a->work;
    sub_001AD940(m->ctx);
    if (w->flags & 8) {
        b16_SetState(m, a, 3);
        w->flags &= ~8;
    }
}

/* 0x0016BD60: idle animation with a random timer. */
void b16_IdleRandom(B16Model *m, B16Act *a)
{
    b16_PlayAnim(m, a, 0);
    a->timer = ((float)(sub_001C7EE1() % 60) + 30.0f) * b16_frameDelta;
}

/* 0x0016C440: release the work block's object and detach it. */
int b16_WorkDetach(B16Model *m, B16Act *a)
{
    B16Work *w = a->work;
    if (w->obj4C != 0) {
        sub_00033A70(w->obj4C);
        w->obj4C = 0;
    }
    w->flags &= ~0x40000000;
    a->work = 0;
    return 1;
}

/* 0x0016FC90: clear bit 0 at +0x0C and call 0x0001EB80. */
int b16_Stop1EB80(B16Flag0C *o)
{
    o->flags &= ~1;
    sub_0001EB80(o);
    return 1;
}
