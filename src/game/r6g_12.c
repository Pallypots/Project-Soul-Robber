/* Area r6g: 3D object model load (r6g_12). Names inferred. */
#include "r6g.h"

/* Build the collision data of box b in a scratch buffer and keep only the
   bytes used (the whole buffer is freed when nothing was built). */
#define R6G_BOX_BUILD(b, line)                                  \
    buf = sub_00053B70(r6g_srcWorld26F5A4, line);               \
    sub_000AD090();                                             \
    end = sub_00081A20(o->box[b], buf);                         \
    sub_000AD090();                                             \
    if (end)                                                    \
        sub_00053890(buf, end - buf);                           \
    else                                                        \
        sub_00053880(buf)

/* 0x0007D230: load the model of a 3D object from pack: create its six boxes
   (three lit by the object's light), read the model data (format tag
   0x4C474240 or the older one) with texture group 0x1000 selected, then build
   each box's collision data. Returns 0 when the pack has no model, else 1. */
int r6g_ObjLoadModel(R6gObjMdl *o, void *pack)
{
    uint32_t *f;
    void *m;
    int group;
    uint8_t *buf, *end;

    f = sub_00037570(pack, 0x40);
    if (!f)
        return 0;
    m = sub_000847F0(o->mdl, 0);
    o->box[0] = sub_00080DA0(m, o->light);
    o->box[1] = sub_00080DA0(m, o->light);
    o->box[2] = sub_00080DA0(m, o->light);
    o->box[3] = sub_00080DA0(0, 0);
    o->box[4] = sub_00080DA0(0, 0);
    o->box[5] = sub_00080DA0(0, 0);
    sub_00082120(o->box[4], 1);
    group = sub_001BA0D0();
    sub_001BA0B0(0x1000);
    if (*f != 0x4C474240)
        sub_0007B070(o, f);
    else
        sub_0007C2B0(o, f);
    sub_001BA0B0(group);
    R6G_BOX_BUILD(0, 0xCE3);
    R6G_BOX_BUILD(1, 0xCEE);
    R6G_BOX_BUILD(2, 0xCF9);
    R6G_BOX_BUILD(3, 0xD02);
    R6G_BOX_BUILD(4, 0xD0B);
    R6G_BOX_BUILD(5, 0xD14);
    return 1;
}
