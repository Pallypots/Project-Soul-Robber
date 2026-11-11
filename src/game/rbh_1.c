/* Area rbh: game functions in 0x00100000..0x0010FFFF (rbh_1). Names inferred. */
#include "rbh.h"

/* 0x0010C6B0: attach a free effect record (first with used4C clear) to obj: bind its two
   component slots (kinds 5 and 0xD), register obj with the scene, run the setup 0x0010A7A0,
   place it at pos facing dir (each optional), copy the descriptor (mode 0/2/1 for kinds
   1/14/15), set the colour from the table and, for i08 == 1, add obj to ae0_obj3E1270.
   Hangs without obj or descriptor. Returns obj.
   calls 0x0010A7A0 with ESI=obj */
RbhSceneObj *rbh_FxAttach10C6B0(RbhSceneObj *obj, const float *pos, const float *dir,
                                const RbhFxDesc *d)
{
    RbhFxRec *r;
    int i;

    if (!obj || !d)
        for (;;)
            ;
    for (i = 0; i < sub_000F30E0(2); i++)
        if (!b10_obj3F6150[i].used4C)
            break;
    r = &b10_obj3F6150[i];
    sub_0001D8B0(r->slot00, 5);
    sub_0001D8D0(obj, r->slot00);
    sub_0001D8B0(r->slot10, 0xD);
    sub_0001D8D0(obj, r->slot10);
    sub_0001E9B0(r3_ctx42C8E4, obj, obj->res14C, 5, 0x11);
    sub_0001EBF0(obj, 1);
    sub_0010A7A0(obj);
    if (pos)
        sub_000F5D40(obj->pos60, pos);
    if (dir)
        sub_000F5D40(obj->v50, dir);
    r->kind90 = d->kind00;
    r->f58 = r->f54 = d->f04;
    r->iA0 = d->i08;
    r->iA4 = d->color0C;
    switch (d->kind00->kind08) {
    case 1:
        r->mode9C = 0;
        break;
    case 14:
        r->mode9C = 2;
        break;
    case 15:
        r->mode9C = 1;
        break;
    }
    sub_000F5D40(obj->node3C->r20->pC4->vDC, rbh_colors3196A0[d->color0C]);
    if (r->iA0 == 1)
        sub_000192B0(ae0_obj3E1270, obj);
    return obj;
}

/* 0x001051D0: hand hit test of Jack's actor. Clears the hit flag; in the attack states (2..6,
   0xB, 0xC, 0x11) with f68 at least 0.25 and a model kind 1/2/3/0x37/0x38 (kinds 1/2 only while
   0x00102F40 agrees), places a 13.125-radius sphere at each of the two attachments (offset by
   the yaw-rotated hand offset) and sets the flag when 0x000F61D0 reports a hit. */
void rbh_HandHit1051D0(void)
{
    RbhScr *g = b10_scr;
    RbhBody **body = &g->body8C;
    int state = g->state6C;
    int kind = g->body8C->model30->kind08;
    int32_t *hit = &g->hands12C[1].hit44;
    int i;
    RbhHand *h;
    RbhObj *obj;
    float v[4], tmp[4];
    RbhSphere s;
    float m[16];

    *hit = 0;
    if (sub_000F6A80())
        return;
    if (state != 2 && state != 3 && state != 6 && state != 0xB && state != 4 && state != 5 &&
        state != 0xC && state != 0x11)
        return;
    if (0.25f > g->f68)
        return;
    if ((kind == 1 || kind == 2) && !r2d_ScnInWindow())
        return;
    if (kind != 1 && kind != 2 && kind != 3 && kind != 0x37 && kind != 0x38)
        return;
    h = g->hands12C;
    for (i = 0; i < 2; i++) {
        obj = h->obj;
        sub_000F5D40(v, rbh_ofs278EB0[i]);
        sub_001AD940(m);
        sub_001AD8E0(m, m, (*body)->yaw54);
        sub_001AD9B0(v, m, v);
        s.r = 13.124999f;
        r4e_VecAdd4(s.c, obj->pos60, v);
        if (sub_000F61D0(*body, &s, 4, tmp) != -1)
            *hit = 1;
        h++;
    }
}
