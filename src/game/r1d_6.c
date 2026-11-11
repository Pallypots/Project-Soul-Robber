/* Area r1d, group 6: animation binding, model viewer and bank helpers 0x0002EAD0..0x00033390. Names inferred. */
#include "r1d.h"

/* 0x0002EAD0: bind a model to an animated object and load the animation
   table for the model's type; 0 on success, -1 on failure. */
int r1d_AnimObjBind(R1dAnimObj *o, R1dModel *m)
{
    int r = 0;
    const void *t;
    if (o == 0 || m == 0) return -1;
    o->model = m;
    switch (m->type) {
    case 1:  t = r1d_anims282C7C; break;
    case 2:  t = r1d_anims282E24; break;
    case 7:  t = r1d_anims2831F4; break;
    case 8:  t = r1d_anims2833C0; break;
    case 9:  t = r1d_anims282F18; break;
    case 10: t = r1d_anims283008; break;
    default: t = r1d_anims282AD8; break;
    }
    if (sub_0003F9C0(o->anim, t) == 0) r = -1;
    return r;
}

/* 0x00031A10: in viewer mode (100) free the viewer's five textures and its
   heap, then leave the mode. */
void r1d_ViewerRelease(void)
{
    if (a3b_mode381AB8 != 100) return;
    if (r1d_tex381AB4 != -1) {
        sub_001B9FC0(r1d_tex381AB4);
        r1d_tex381AB4 = -1;
    }
    if (r1d_tex381AB0 != -1) {
        sub_001B9FC0(r1d_tex381AB0);
        r1d_tex381AB0 = -1;
    }
    if (r1d_tex381A60 != -1) {
        sub_001B9FC0(r1d_tex381A60);
        r1d_tex381A60 = -1;
    }
    if (r1d_tex381A64 != -1) {
        sub_001B9FC0(r1d_tex381A64);
        r1d_tex381A64 = -1;
    }
    if (r1d_tex381A68 != -1) {
        sub_001B9FC0(r1d_tex381A68);
        r1d_tex381A68 = -1;
    }
    sub_0004F5D0(0xB0);
    sub_00053880(r1d_heap381A5C);
    a3b_mode381AB8 = 0;
}

/* 0x00031AC0: load viewer picture idx (0..13, else 0) into the viewer heap
   and replace the viewer texture with it. */
void r1d_ViewerLoad(unsigned int idx)
{
    if (idx >= 14) idx = 0;
    sub_0004F700(0xB0);
    r1d_sel38182C = idx;
    a6b_Printf2(r1d_path381A70, r1d_fmt2835E8, idx);
    sub_00053E20(r1d_path381A70, r1d_heap381A5C);
    while (sub_00053CA0(1))
        sub_000580D0();
    sub_0004F720();
    if (r1d_tex381AB4 >= 0)
        sub_001B9FC0(r1d_tex381AB4);
    r1d_tex381AB4 = sub_00084C00(r1d_heap381A5C, 0);
}

/* 0x00033280: decode the signed bytes 2 and 3 of a key into (a, b);
   a = -3..0 select fixed pairs or the pair stored in p. Returns 0. */
int r1d_KeyDecode(int key, R1dPair *p, int *outA, int *outB)
{
    int a = (signed char)(key >> 16);
    int b = (signed char)(key >> 24);
    switch (a) {
    case -3:
        *outA = 1;
        *outB = 0xFF;
        return 0;
    case -2:
        *outA = 1;
        *outB = 0;
        return 0;
    case -1:
        if (p != 0) {
            *outA = p->a;
            *outB = p->b;
            return 0;
        }
        /* fall through */
    case 0:
        *outA = 0;
        *outB = -1;
        return 0;
    }
    *outA = a;
    *outB = b;
    return 0;
}

/* 0x00033390: detach the bank's two lists, allocate a fresh bank,
   initialise it and attach its lists again. */
void r1d_BankRealloc(void)
{
    r4_NodeDetach(r1c_bank283698 + 0x5845C);
    r4_NodeDetach(r1c_bank283698 + 0x5850C);
    r1c_bank283698 = a50_Alloc(3, 0x585C0, 0, 0);
    r1_BankInit(r1c_bank283698);
    sub_001B2020(r1_g3DA080, r1c_bank283698 + 0x5845C);
    sub_001B2020(r1_g3DA084, r1c_bank283698 + 0x5850C);
}
