/* Area b4c, group 2: actor state handlers 0x00169A00-0x0016F860. Names inferred. */
#include "b4c.h"

/* 0x00169A00: clear eight work words, then the active bit. */
int b4c_Reset169A00(B4cModel *m, B4cAct *a)
{
    uint32_t *w = (uint32_t *)a->work;
    w[0] = 0; w[1] = 0; w[2] = 0; w[3] = 0;
    w[4] = 0; w[5] = 0; w[6] = 0; w[7] = 0;
    a->work->flags &= ~1u;
    return 1;
}

/* 0x00169E00: play animation 0 and call 0x000EE6D0. */
void b4c_Idle169E00(B4cModel *m, B4cAct *a)
{
    sub_00167200(m, a, 0);
    sub_000EE6D0(m, 0);
}

/* 0x0016B8E0: clear six work words, then the active bit. */
int b4c_Reset16B8E0(B4cModel *m, B4cAct *a)
{
    uint32_t *w = (uint32_t *)a->work;
    w[0] = 0; w[1] = 0; w[2] = 0;
    w[3] = 0; w[4] = 0; w[5] = 0;
    a->work->flags &= ~1u;
    return 1;
}

/* 0x0016CBA0: animation 3 and a random 120-239 frame wait. */
void b4c_Wait16CBA0(B4cModel *m, B4cAct *a)
{
    B4cWork *w = a->work;
    sub_00167200(m, a, 3);
    w->f34 = 0.0f;
    w->f38 = (float)(sub_001C7EE1() % 120 + 120) / a50_frameUnits * a50_frameSeconds;
    w->flags |= 0x400;
}

/* 0x0016D590: start: animation 0, active bit, 60-frame timer. */
void b4c_Start16D590(B4cModel *m, B4cAct *a)
{
    B4cWork *w = a->work;
    sub_000EE6D0(m, 0);
    sub_00167200(m, a, 0);
    w->flags |= 1;
    a->timer = 60.0f / a50_frameUnits * a50_frameSeconds;
}

/* 0x0016DE90: hide and release the attached object. */
void b4c_Release16DE90(B4cModel *m, B4cAct *a)
{
    aab_Hide1D700(m);
    if (a->work->obj4C) {
        sub_00033A70(a->work->obj4C);
        a->work->obj4C = 0;
    }
}

/* 0x0016DF90: animation 0 and move to point 0x0031F400. */
void b4c_Place16DF90(B4cModel *m, B4cAct *a)
{
    B4cWork *w = a->work;
    sub_00167200(m, a, 0);
    w->flags &= 0xFFDFD37Fu;
    b4c_VecCopy(w->v0C, b4c_vec31F400);
    w->i40 = *(int32_t *)&w->v0C[1];
}

/* 0x0016E470: when the animation is done, enter state 0x11. */
void b4c_Next16E470(B4cModel *m, B4cAct *a)
{
    B4cWork *w;
    if (sub_000833E0(m->anim) == 0) return;
    w = a->work;
    w->flags &= ~0xC00u;
    b16_SetState(m, a, 0x11);
    if (w->flags & 0xC00) {
        w->flags &= ~0x2000u;
    } else {
        w->flags |= 0x2000;
        w->i3C = m->i54;
    }
}

/* 0x0016E620: move to point 0x0031F420 and play animation 2 on model m (third argument). */
void b4c_Place16E620(void *unused, B4cAct *a, B4cModel *m)
{
    B4cWork *w = a->work;
    w->flags |= 0x200000;
    b4c_VecCopy(w->v0C, b4c_vec31F420);
    w->i40 = *(int32_t *)&w->v0C[1];
    w->flags |= 0x1000;
    a->flags4C &= ~1u;
    m->f50 = 0.5235988f;
    sub_00167200(m, a, 2);
}

/* 0x0016EA00: enter state 6. */
void b4c_State16EA00(B4cModel *m, B4cAct *a)
{
    B4cWork *w = a->work;
    w->flags &= ~0xC00u;
    b16_SetState(m, a, 6);
    if (w->flags & 0xC00) {
        w->flags &= ~0x2000u;
    } else {
        w->flags |= 0x2000;
        w->i3C = m->i54;
    }
}

/* 0x0016F7B0: release the registered task. */
void b4c_TaskFree16F7B0(void)
{
    if (b16_taskId3F92EC) {
        sub_000ED560(8);
        sub_00020170(b16_task3F92E8);
        b16_task3F92E8 = 0;
        b16_taskId3F92EC = 0;
    }
}

/* 0x0016F860: send command 8 and stop sound 0x9F if playing. */
void b4c_Stop16F860(void)
{
    sub_000ED600(8);
    if (sub_0004F6D0(0x9F)) sub_0004F5D0(0x9F);
}
