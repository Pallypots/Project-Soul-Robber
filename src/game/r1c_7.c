/* Area r1c, group 7: object setup and lookups 0x0002E410..0x00048AA0.
   Names inferred. */
#include "r1c.h"

/* 0x0002E410: per-frame pad mode check: while the menu is up keep the
   0x128 pad mask enabled; otherwise drop it and, in mode 10000, run the
   top-level mode handler. */
void r1c_PadModeTick(void)
{
    if (sub_00079460() != 0) {
        if (sub_0019BE70(0x128) == 0)
            sub_0019BE90(0x128);
        return;
    }
    if (sub_0019BE70(0x128) != 0)
        sub_0019BEB0(0x128);
    if (r1c_state3816D0 == 10000)
        r1c_ModeRun();
}

/* 0x00035D80: play the object's motion with this id (no blend range);
   0 when the object has no motion list or no such motion. */
void *r1c_ObjPlayMotion(R1cMotObj *o, int id, int flags)
{
    R1cMotList *l = o->motions;
    R1cMotNode *n;
    if (l == 0) return 0;
    for (n = l->head; n != 0; n = n->next)
        if (n->mot->id == id) break;
    if (n == 0 || n->mot == 0) return 0;
    return sub_00035D20(n->mot, o, -1, -1, flags);
}

/* 0x00035DD0: play the motion with this id from a motion list using the
   list's blend range, adding flag 4; 0 when absent. */
void *r1c_ListPlayMotion(void *o, R1cMotList *l, int id, int flags)
{
    R1cMotNode *n;
    if (l == 0) return 0;
    for (n = l->head; n != 0; n = n->next)
        if (n->mot->id == id) break;
    if (n == 0 || n->mot == 0) return 0;
    return sub_00035D20(n->mot, o, l->from, l->to, flags | 4);
}

/* 0x00036340: reset an object's sixteen slot handles to -1, then reattach
   its block and refresh it. */
void r1c_ObjSlotsReset(R1cSlotObj *o)
{
    o->slot[0] = -1;
    o->slot[1] = -1;
    o->slot[2] = -1;
    o->slot[3] = -1;
    o->slot[4] = -1;
    o->slot[5] = -1;
    o->slot[6] = -1;
    o->slot[7] = -1;
    o->slot[8] = -1;
    o->slot[9] = -1;
    o->slot[10] = -1;
    o->slot[11] = -1;
    o->slot[12] = -1;
    o->slot[13] = -1;
    o->slot[14] = -1;
    o->slot[15] = -1;
    sub_0005A6E0(o);
    sub_00035320(o, 0);
}

/* 0x00037000: load the object's data block (heap 4); returns 1 when the
   allocation fails, 0 on success. */
int r1c_ObjLoadData(R1cDataObj *o)
{
    int size;
    void *p;
    sub_00053710(4);
    size = sub_0004F680(&o->desc);
    p = sub_00053AB0(size, 0, 0x59);
    r1c_data3DA0D0 = p;
    if (p == 0) return 1;
    sub_000512D0(&o->desc, p);
    r1c_obj2836DC = o;
    sub_00053740();
    return 0;
}

/* 0x0003FA20: create a named flag variable: look it up or create it, set
   its value, and copy the name into the 31-char name buffer. */
R1cFlagVar *r1c_FlagVarSet(void *ctx, int value, const char *name)
{
    R1cFlagVar *v = sub_0003F8B0(ctx, r1c_flagType2C4B94, 0);
    if (v != 0) {
        v->value = value != 0;
        a6b_Printf3(r1c_name3DE808, 0x1F, r1c_fmtS25FF04, name);
        r1c_name3DE808[0x1F] = 0;
    }
    return v;
}

/* 0x00048AA0: start the pending sound request on its channel and set the
   volume of the given voice to 0x80.
   regargs: voice=ESI */
void r1c_SndStartPending(int voice)
{
    if (r1c_q3DFECC < 0) return;
    if (r1c_q3DFEC0 < 2) {
        sub_001999E0(r1c_q3DFECC, voice);
        sub_00047DA0(0x80, voice);
        return;
    }
    if (r1c_q3DFEC0 >= 3)
        sub_0019B800(r1c_q3DFECC, voice);
    sub_00047DA0(0x80, voice);
}
