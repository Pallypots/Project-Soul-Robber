/* Area r1d, group 11: node chains, bank restore and scene objects 0x00035D20..0x00037130. Names inferred. */
#include "r1d.h"

/* 0x00035D20: build a node for every object of the source list; the first
   becomes the head, the others are linked behind it flagged as children. */
R1dNode *r1d_ChainBuild(R1dChainSrc *src, int a, int b, int c, int d)
{
    R1dNode *first = 0;
    R1dNode *n;
    R1dLnk *l;
    for (l = src->head; l != 0; l = l->next) {
        n = sub_00035C60(l->obj, a, b, c, d);
        if (first == 0) {
            first = n;
        } else if (n != 0) {
            n->flags |= 1;
            n->child = first->child;
            first->child = n;
        }
    }
    return first;
}

/* 0x000360E0: clear both pools, detach the bank lists, free the heap bank
   and switch back to the static bank. */
void r1d_BankRestore(void)
{
    char *old;
    r1c_PoolForEach(r1c_bank283698, 0xB40, sub_000335D0, 0);
    r1c_PoolForEach(r1c_bank283698 + 0x55140, 0x6C, sub_00034B50, 0);
    r4_NodeDetach(r1c_bank283698 + 0x5845C);
    r4_NodeDetach(r1c_bank283698 + 0x5850C);
    old = r1c_bank283698;
    r1c_bank283698 = (char *)r1_bank381AC0;
    sub_00053880(old);
    sub_001B2020(r1_g3DA080, r1c_bank283698 + 0x5845C);
    sub_001B2020(r1_g3DA084, r1c_bank283698 + 0x5850C);
}

/* 0x00036390: initialise a timer list entry: no id, all sixteen slots -1. */
void r1d_TEntInit(R1dTEnt *e)
{
    R1dTimers *t;
    int i;
    e->self = e;
    e->id = -1;
    t = &e->t;
    for (i = 0; i < 16; i++)
        t->slot[i] = -1;
    a5b_TimerInit(t);
    sub_00035320(t, 0);
}

/* 0x000370C0: create the scene object and run its set-up steps inside
   heap 4. */
void r1d_SceneCreate(void)
{
    a50_PushHeap(4);
    r1c_scene42C8E4 = (R1dActor *)r6b_Alloc214();
    r6c_ObjInit((R1dSceneObj *)r1c_scene42C8E4);
    r1b_PktOp(r1c_scene42C8E4);
    ((R1dSceneObj *)r1c_scene42C8E4)->d04 =
        sub_00079A00((R1dSceneObj *)r1c_scene42C8E4, ((R1dSceneObj *)r1c_scene42C8E4)->d04);
    sub_0007ABB0((R1dSceneObj *)r1c_scene42C8E4);
    r6c_ObjResetPose((R1dSceneObj *)r1c_scene42C8E4);
    sub_00079E00((R1dSceneObj *)r1c_scene42C8E4);
    sub_00053740();
}

/* 0x00037130: tear down the scene buffers and restore the saved scene
   pointer and texture group. */
void r1d_SceneDestroy(void)
{
    void *a = r1c_bufAData3DA0C0;
    if (r1c_obj2836DC >= 0) {
        sub_0004F5D0(r1c_obj2836DC + 0xE8);
        r1c_obj2836DC = -1;
    }
    sub_0001E550(a);
    sub_00020170(r1c_bufA3DA0C8);
    sub_00020170(r1c_bufB3DA0CC);
    sub_00053880(r1d_heap3DA0D4);
    r1c_scene42C8E4 = r1d_saved3DA0C4;
    r4b_TexSetGroup(r1d_texGrp3DA0B4);
}
