/* Area r1c, group 8: setup and job helpers 0x00022920..0x0005D1F0.
   Names inferred. */
#include "r1c.h"

/* 0x00022920: reset the game state: clear the work area, free the nine
   loaded textures, clear the state block at 0x0037C4F8 and reinitialise
   the player record. */
void r1c_GameStateReset(void)
{
    int i;
    r1c_ClearWork42CE80();
    for (i = 0; i < 9; i++) {
        if (r1c_tex380C24[i] != -1) {
            sub_001B9FC0(r1c_tex380C24[i]);
            r1c_tex380C24[i] = -1;
        }
    }
    R1C_ZERO(r1c_state37C4F8, sizeof(r1c_state37C4F8));
    sub_0004F5D0((char *)sub_000529F0() + 0xA8);
    r1c_g3813B4 = 0;
}

/* 0x0002C150: run step 1..6 of the first sequencer, or clear its busy bit
   in step 0. */
void r1c_SeqARun(void)
{
    switch (r1c_seqStep37C544) {
    case 0: r1c_seqFlags37C540 &= ~1u; break;
    case 1: sub_00028630(); break;
    case 2: sub_00028740(); break;
    case 3: sub_00028890(); break;
    case 4: sub_00028930(); break;
    case 5: sub_00028B10(); break;
    case 6: sub_00028CB0(); break;
    }
}

/* 0x0002C2A0: run step 1..6 of the second sequencer, or clear its busy bit
   in step 0. */
void r1c_SeqBRun(void)
{
    switch (r1c_seqStep37ED04) {
    case 0: r1c_seqFlags37ED00 &= ~1u; break;
    case 1: sub_0002A070(); break;
    case 2: sub_0002A160(); break;
    case 3: sub_0002A240(); break;
    case 4: sub_0002A2C0(); break;
    case 5: sub_0002A3A0(); break;
    case 6: sub_0002A460(); break;
    }
}

/* 0x000356A0: drop an object's pending effect and re-apply the motion entry
   matching its current state. */
void r1c_ObjRefreshMotion(void *unused, R1cActor *o)
{
    R1cMotNode *n;
    int id;
    (void)unused;
    if (o == 0) return;
    if (o->effect != 0) {
        sub_00033C20(o->effect);
        o->effect = 0;
    }
    if (o->table == 0 || (n = o->table->head) == 0) return;
    id = o->state->id;
    for (; n != 0; n = n->next) {
        if (n->mot->id == id) {
            sub_00033D10(o, (char *)n->mot + 0x14);
            return;
        }
    }
}

/* 0x00037060: create the two shared render buffers and register the second
   with the current scene (heap 4). */
void r1c_RenderBufsCreate(void)
{
    R1cRBuf *a, *b;
    sub_00053710(4);
    a = sub_0001F210(3, 3);
    r1c_bufA3DA0C8 = a;
    r1c_bufAData3DA0C0 = a->data;
    sub_0001DA40(a);
    b = sub_00022260(3, 3, 10, 3);
    r1c_bufB3DA0CC = b;
    r1c_bufBData3DA0B8 = b->data;
    sub_0001CFF0(r1c_scene42C8E4->root, b, 0);
    sub_00053740();
}

/* 0x0003A8F0: initialise the camera system: flags, the active and free
   lists, and the 99 camera nodes (all placed on the free list). */
void r1c_CamInit(void)
{
    R1cCamNode *n;
    int i;
    r1c_camFlag42CB04 = 1;
    r1c_camFlag42CB08 = 1;
    r1c_camFlag42CB0C = 0;
    sub_0003D860(r1c_camList3DDC60);
    sub_0003D860(r1c_free3DCFF0);
    for (n = r1c_camNodes3DD000, i = 99; i != 0; i--, n++) {
        n->set = &n->setData;
        sub_0003D880(r1c_free3DCFF0, n);
    }
}

/* 0x00040900: stop the current stage's ambient sound and start the one
   selected by id. */
void r1c_StageAmbient(int id)
{
    R1cStage *s = r1c_stage3DFA5C;
    sub_00076060(s->amb.handle);
    sub_0003FCB0(&r1c_stage3DFA5C->amb,
                 sub_0003FA70(r1c_stage3DFA5C->ambTable, id), 0, 0, -1.0f);
}

/* 0x000470E0: set up an aligned work heap in buf (size bytes) and register
   it; 1 when the buffer is too small, 0 on success (hangs if registration
   fails). */
int r1c_HeapSetup(R1cHeap *buf, int size)
{
    R1cHeapReg reg;
    if ((uint32_t)size <= 0x80) return 1;
    buf->d00 = 1;
    reg.d04 = 1;
    reg.d08 = 1;
    buf->start = (char *)(((uintptr_t)buf + 0x7F) & ~(uintptr_t)0x3F);
    buf->end = (char *)buf + size;
    reg.d14 = 0;
    buf->id = sub_001AA240(&reg);
    if (buf->id == -1) for (;;) ;
    return 0;
}

/* 0x00058260: reset the main background job record. */
void r1c_JobReset(void)
{
    R1cJobFull *j = (R1cJobFull *)&g_job;
    if (j->thread != -1) {
        sub_001AD440(j->thread);
        if (j->handle != -1)
            sub_001AA310(j->handle);
    }
    j->state = 0;
    j->thread = -1;
    j->handle = -1;
    j->d10 = 0;
    j->d14 = 0;
    j->func = 0;
    j->arg = 0;
}

/* 0x000580D0: yield point: let the main job run, wake a background job's
   handle, or record and suspend an unknown thread; always ends with the
   frame sync 0x001AD6E0. */
void r1c_JobYield(void)
{
    BackgroundJob *j;
    int tid;
    sub_001AD6E0();
    j = r1c_JobCurrent();
    if (j == &g_job) {
        sub_001AD6A0();
        sub_001AD6E0();
        return;
    }
    if (j != 0) {
        sub_001AA460(((R1cJob *)j)->handle);
        sub_001AD6E0();
        return;
    }
    tid = sub_001AD560();
    r1c_threads3E46A0[r1c_nThreads3E46DC] = tid;
    r1c_nThreads3E46DC++;
    sub_001AD4B0(tid);
    sub_001AD6E0();
}

/* 0x0005CC70: the data entry with this id in a list, created (0x470 bytes)
   and appended when missing; 0 when allocation fails. */
R1cIdEnt *r1c_IdListGet(R1cIdList *l, int id)
{
    R1cIdNode *n;
    R1cIdEnt *e;
    for (n = l->head; n != 0; n = n->next)
        if (n->ent->id == id)
            return n->ent;
    e = sub_00053AB0(0x470, 0, 0x468);
    if (e != 0) {
        e->self = e;
        e->id = -1;
        sub_0005CAF0(e->body);
        sub_0003D880(l, e);
        e->id = id;
    }
    return e;
}

/* 0x0005D1F0: default event handling, then on event 1 for an idle object
   whose kind has flag 0x20, queue its child for the 0x0005D030 callback. */
int r1c_ObjEventEx(int ev, R1cEvObj *o, int mode)
{
    int r = sub_0003F780(ev, o, mode);
    if (mode == 1 && o->busy == 0 && (sub_0004ECE0(o->kind) & 0x20))
        sub_0005A990(o->child, sub_0005D030, r1c_ctx2DD624);
    return r;
}
