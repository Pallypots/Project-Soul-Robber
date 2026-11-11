/* Area rbg: game functions in 0x00100000..0x0010FFFF (rbg_6). Names inferred. */
#include "rbg.h"

/* 0x001089C0: bring the object pair o (body o[0], shadow o[1]) into the scene: take the first
   free 0xE8-byte slot, attach its two component holders, register both objects, release the
   shadow's effect and sound, link the bones and add o to the update list. Hangs on o == 0. */
RbgRec150 *rbg_Spawn1089C0(RbgRec150 *o)
{
    int i;
    RbgSlotE8 *s;
    RbgRender *r;
    RbgRec150 *sh;

    if (!o)
        for (;;)
            ;
    for (i = 0; i < sub_000F30E0(0); i++)
        if (!b10_obj3F6138[i].used4C)
            break;
    s = &b10_obj3F6138[i];
    r = o->r20;
    sub_0001D8B0(s->slot00, 5);
    sub_0001D8D0(o, s->slot00);
    sub_0001D8B0(s->slot10, 0xD);
    sub_0001D8D0(o, s->slot10);
    sub_0001E9B0(r3_ctx42C8E4, o, 6, 5, 0x11);
    sh = &o[1];
    sub_0001E9B0(r3_ctx42C8E4, sh, 0xB, 5, 0x11);
    sub_0001EBF0(o, 1);
    sub_0001EBF0(sh, 1);
    sub_000362B0(sh);
    if (o[1].h134) {
        sub_00033C20(o[1].h134);
        o[1].h134 = 0;
    }
    if (o[1].h13C) {
        sub_0005BC50(o[1].h13C);
        o[1].h13C = 0;
    }
    sub_0001F070(sh, 1);
    r->pC4->i17C = 0;
    sub_00108790(o);
    sub_0001EFE0(s->bones8C, o, sh);
    sub_000192B0(ae0_obj3E1270, o);
    return o;
}

