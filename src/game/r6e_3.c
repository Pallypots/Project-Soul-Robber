/* Area r6e: actor slot helpers around 0x00092450-0x000A9EEC (r6e_3). Names inferred. */
#include "r6e.h"

/* 0x00092450: actor state step: start when 0x000A4180 allows it (state 10), then
   in state 10 reset it and show its model. */
void r6e_ActorStartShow(R6eActor *a)
{
    if (a->state40 != 0) {
        if (a->state40 == 10) {
            sub_000A41D0(a, -1);
            sub_000A4740(a, 0);
        }
    } else if (sub_000A4180(a)) {
        a->state40 = 10;
    }
}

/* 0x00092700: actor step: in state 0, when 0x000A33E0 allows it, reset the actor
   and clear flag 0x10. */
void r6e_ActorReset10(R6eActor *a)
{
    if (a->state40 == 0 && sub_000A33E0(a)) {
        sub_000A41D0(a, -1);
        a->flags &= ~0x10u;
    }
}

/* 0x00092E60: actor state step: start when allowed (state 10), then in state 10
   reset it and set flag 0x80. */
void r6e_ActorStartFlag80(R6eActor *a)
{
    if (a->state40 != 0) {
        if (a->state40 == 10) {
            sub_000A41D0(a, -1);
            a->flags |= 0x80;
        }
    } else if (sub_000A4180(a)) {
        a->state40 = 10;
    }
}

/* 0x00098430: number of actors 0x10..0x14 without flag 0x800. */
int r6e_ActorCountFree(void)
{
    int n = 0;
    int i;
    for (i = 0x10; i <= 0x14; i++)
        if (!(sub_000A4290(i)->flags & 0x800))
            n++;
    return n;
}

/* 0x0009F010: actor step: show the model once (state 0 -> 1). */
void r6e_ActorShowOnce(R6eActor *a)
{
    if (a->model && a->state40 == 0) {
        sub_000A4740(a, 0);
        a->state40 = 1;
    }
}

/* 0x0009F6D0: send an event to an actor through its handler table; 0 when it has none. */
int r6e_ActorSend(int id, int arg, int v)
{
    R6eActor *a = sub_000A42C0(id);
    if (a) {
        a->i124 = v;
        if (a->kind44 != -1)
            return r6e_actorFns2E17C0[a->kind44](a, arg);
    }
    return 0;
}

/* 0x000A1020: in chapter 4 stage 5 broadcast every kind-2 object found. */
void r6e_Stage45Broadcast(void)
{
    R6eKindObj *o;
    if (a30_g41316C != 4 || a30_g413170 != 5)
        return;
    o = sub_000EDB10(0);
    if (!o)
        return;
    do {
        if (o->kind == 2)
            sub_000A0FD0(o);
        o = sub_000EDB90();
    } while (o);
}

/* 0x000A2360: clear the link slot that holds v. */
void r6e_ActorUnlink(R6eActor *a, R6eActor *v)
{
    short i;
    for (i = 0; i < 8; i++) {
        if (a->links[i] == v) {
            a->links[i] = 0;
            return;
        }
    }
}

/* 0x000A25A0: move an actor and its second vector to the attachment point it reports. */
void r6e_ActorSnap(R6eActor *a)
{
    uint8_t *p = 0;
    float *q;
    sub_000A21C0(a, &p);
    q = (float *)(p + 0x70);
    sub_000F5D40(a->vec90, q);
    r4c_VecSub(a->vec90, a->vec90, a->vecF0);
    sub_000F5D40(a->vecF0, q);
}

/* 0x000A25F0: move every linked actor that is not pinned (flag 8) by the actor's offset. */
void r6e_ActorDragLinks(R6eActor *a)
{
    int i;
    R6eActor *l;
    for (i = 0; i < 8; i++) {
        l = a->links[i];
        if (l && !(l->flags128 & 8))
            r4c_VecAdd(l->pos60, l->pos60, a->vec90);
    }
}

/* 0x000A2830: set and clear the player stat flags for this scene and pin the player. */
void r6e_PlayerPin(void)
{
    PlayerObj_SetFlags((PlayerObj *)&g_stats, 0x80, 0);
    PlayerObj_ClearFlags((PlayerObj *)&g_stats, 0x200000, 0);
    PlayerObj_ClearFlags((PlayerObj *)&g_stats, 0x800000, 0);
    PlayerObj_ClearFlags((PlayerObj *)&g_stats, 0x40, 0);
    ((R6eObj128 *)g_playerObj)->flags128 |= 0x18;
}

/* 0x000A2F50: direction from actor i's model to another actor's position, passed to 0x00082D70. */
void r6e_ActorFace(int i, R6eActor *b)
{
    float v[4];
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 1.0f;
    r4c_VecSub(v, (float *)((uint8_t *)aab_slots[i].model + 0x60), b->pos60);
    sub_00082D70(v);
}

/* 0x000A4740: hide (on == 0) or show an actor's model; clears flag 0x40000000. */
void r6e_ActorShow(R6eActor *a, int on)
{
    if (!on) {
        sub_0001D700(a->model);
        a->flags |= 0x20000000;
        a->flags &= ~0x40000000u;
    } else {
        sub_0001D610(a->model);
        a->flags &= ~0x20000000u;
        a->flags &= ~0x40000000u;
    }
}

/* 0x000A7950: release record i (model, handle) and reset it. */
void r6e_RecRelease(int i)
{
    R6eRecDC *r = &aab_recDC[i];
    if (r->flags & 1) {
        r->modelD8->flags0C &= ~1u;
        sub_0001EB80(r->modelD8);
        if (r->hD4)
            sub_00033A40(r->hD4);
        sub_000A7700(r);
    }
    sub_000A7700(r);
}

