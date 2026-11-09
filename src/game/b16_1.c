/* Area b16, group 1: slot table, pools, tasks and actor state core. Names inferred. */
#include "b16.h"

/* 0x00166040: clear the slot table, mark it active and every slot idle. */
void b16_SlotSysInit(void)
{
    int i;
    B16_ZERO(&b16_slotSys, sizeof b16_slotSys);
    b16_slotSys.flags |= 1;
    for (i = 0; i < 6; i++)
        b16_slotSys.slots[i].flags &= ~1;
}

/* 0x001660C0: mark the slot table and every slot inactive. */
void b16_SlotSysStop(void)
{
    int i;
    b16_slotSys.flags &= ~1;
    for (i = 0; i < 6; i++)
        b16_slotSys.slots[i].flags &= ~1;
}

/* 0x00166100: clear slot table flag 2. */
void b16_SlotSysClear2(void) { b16_slotSys.flags &= ~2; }

/* 0x001661B0: clear bit 0 of a flag word. */
void b16_ClearBit0(uint32_t *flags) { *flags &= ~1; }

/* 0x001661C0: set two floats. */
void b16_SetFloats(B16Pair *p, float a, float b) { p->f08 = a; p->f0C = b; }

/* 0x001661E0: set two ints. */
void b16_SetInts(B16Pair *p, int a, int b) { p->i40 = a; p->i44 = b; }

/* 0x00166200: store a vector into slot 0..2. */
void b16_VecSet(B16Vecs *o, const float *v, int which)
{
    switch (which) {
    case 0: b16_VecCopy(o->v10, v); return;
    case 1: b16_VecCopy(o->v30, v); return;
    case 2: b16_VecCopy(o->v20, v); return;
    }
    for (;;) ;
}

/* 0x00166260: fetch a vector from slot 0..2. */
void b16_VecGet(B16Vecs *o, float *v, int which)
{
    switch (which) {
    case 0: b16_VecCopy(v, o->v10); return;
    case 1: b16_VecCopy(v, o->v30); return;
    case 2: b16_VecCopy(v, o->v20); return;
    }
    for (;;) ;
}

/* 0x001662C0: 1 if any of the mask bits are set. */
int b16_TestFlags(B16Pair *p, uint32_t mask) { return (p->flags & mask) != 0; }

/* 0x00169710: clear the 0x20-byte record pool. */
int b16_Pool20Init(void) { B16_ZERO(b16_pool20, sizeof b16_pool20); return 1; }

/* 0x001675D0: reset the timer and clear the head of the 0x60-byte pool. */
int b16_Pool60Init(void)
{
    b16_timer3F8410 = 0.0f;
    B16_ZERO(b16_pool60, 0x120);
    return 1;
}

/* 0x00167600: take a free 0x60-byte record, zeroed and marked used. */
B16Rec60 *b16_Pool60Alloc(void)
{
    int i;
    B16Rec60 *r;
    for (i = 0; i < 16; i++)
        if (!(b16_pool60[i].flags & 1))
            break;
    if (i == 16)
        return 0;
    r = &b16_pool60[i];
    B16_ZERO(r, sizeof *r);
    r->flags |= 1;
    return r;
}

/* 0x00167670: count the timer down by the frame time. */
void b16_TickTimer(void) { b16_timer3F8410 -= b16_frameDelta; }

/* 0x0016B880: clear the 0x18-byte pool. */
int b16_Pool18Init(void) { B16_ZERO(b16_pool18, sizeof b16_pool18); return 1; }

/* 0x0016B8A0: take a free 0x18-byte record and mark it used. */
B16Rec18 *b16_Pool18Alloc(void)
{
    int i;
    for (i = 0; i < 5; i++)
        if (!(b16_pool18[i].flags & 1))
            break;
    if (i == 5)
        return 0;
    b16_pool18[i].flags |= 1;
    return &b16_pool18[i];
}

/* 0x0016C3B0: clear a 0x50-byte block. */
int b16_Buf3F8C98Init(void) { B16_ZERO(b16_buf3F8C98, sizeof b16_buf3F8C98); return 1; }

/* 0x001671D0: switch the actor to a state and run its handler. */
int b16_SetState(B16Model *m, B16Act *a, int state)
{
    if (state < 0)
        for (;;) ;
    if (a->fns[state] == 0)
        for (;;) ;
    a->state = state;
    a->step = 0;
    return a->fns[state](m, a);
}

/* 0x00167200: start (or restart) an animation on the model. */
void b16_PlayAnim(B16Model *m, B16Act *a, int id)
{
    a->flags4C &= ~2;
    if (a->animId == id) {
        b16_AnimSet(m->anim, -1);
    } else {
        b16_AnimSet(m->anim, id);
        a->animId = id;
    }
    sub_0001D7F0(m->next, id, 0);
    if (m->anim->cur != a->animId)
        for (;;) ;
    a->animTime = 0.0f;
}

/* 0x00167300: register the task once. */
void b16_TaskStart(void)
{
    if (b16_taskId3F8404 == 0) {
        B16Task *t = sub_0001F210(3, 1);
        b16_task3F8400 = t;
        b16_taskId3F8404 = t->id;
        sub_0001DA40(t);
        sub_000ED9A0(sub_00166CD0);
    }
}

/* 0x00167340: unregister the task. */
void b16_TaskStop(void)
{
    if (b16_taskId3F8404 != 0) {
        sub_000ED560(7);
        sub_00020170(b16_task3F8400);
        b16_task3F8400 = 0;
        b16_taskId3F8404 = 0;
        sub_000ED9E0(sub_00166CD0);
    }
}

/* 0x0016F780: register the second task once. */
void b16_Task2Start(void)
{
    if (b16_taskId3F92EC == 0) {
        B16Task *t = sub_0001F210(0xC, 0);
        b16_task3F92E8 = t;
        b16_taskId3F92EC = t->id;
        sub_0001DA40(t);
    }
}

/* 0x00171F90: register the third task once. */
void b16_Task3Start(void)
{
    if (b16_taskId3FD7B4 == 0) {
        B16Task *t = sub_0001F210(6, 0xC);
        b16_task3FD7B0 = t;
        b16_taskId3FD7B4 = t->id;
        sub_0001DA40(t);
    }
}

/* 0x00175170: clear a 0xF0-byte block. */
void b16_Buf3FD7E0Init(void) { B16_ZERO(b16_buf3FD7E0, sizeof b16_buf3FD7E0); }
/* 0x00176480: clear a 0x104-byte block. */
void b16_Buf3FD8D0Init(void) { B16_ZERO(b16_buf3FD8D0, sizeof b16_buf3FD8D0); }
/* 0x00177740: clear a 0x104-byte block. */
void b16_Buf3FD9D8Init(void) { B16_ZERO(b16_buf3FD9D8, sizeof b16_buf3FD9D8); }
