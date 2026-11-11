/* Area r1d, group 12: callers of 0x00036390 and 0x000370C0 (kept apart). Names inferred. */
#include "r1d.h"

/* 0x000363F0: the timer entry with id from the list, or a new one appended
   to it (0 when memory runs out). */
R1dTEnt *r1d_TListFindAdd(R1dTList *l, int id)
{
    R1dTEnt *p, *e;
    for (p = l->head; p != 0; p = p->next) {
        if (p->self->id == id)
            return p->self;
    }
    e = sub_00053AB0(0x6C, 0, 0xA61);
    r1c_ObjSlotsReset(&e->t);
    if (e != 0) {
        r1d_TEntInit(e);
        a4c_ListAppend(l, e);
        e->id = id;
    }
    return e;
}

/* 0x00037230: save the scene state, open the scene heap and create a fresh
   scene with empty buffers. */
void r1d_SceneSetup(void)
{
    a50_PushHeap(4);
    r1d_texGrp3DA0B4 = r4b_TexSetGroup(0x7000);
    r1d_saved3DA0C4 = r1c_scene42C8E4;
    r1d_heap3DA0D4 = a50_AllocTop(r1d_name261588, 0x106);
    r1d_SceneCreate();
    a5b_CurSlotEndTemp();
    r1c_bufAData3DA0C0 = 0;
    r1c_bufBData3DA0B8 = 0;
    r1c_bufA3DA0C8 = 0;
    r1c_bufB3DA0CC = 0;
    r1c_data3DA0D0 = 0;
    r1d_g3DA0BC = 0;
    r1c_obj2836DC = -1;
    sub_00053740();
}
