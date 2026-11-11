/* Area r2, group 2: actor helpers (0x000FB6C0..0x0010D31D). Names inferred. */
#include "r2.h"

/* 0x000FB6C0: return the actor found by 0x0C7130 for obj's +0x8C link when it is
   within 100 units of that link, otherwise the player.  regargs: obj=EDI */
R2Actor *r2_NearTarget(R2Actor *obj)
{
    R2Actor *t = (R2Actor *)sub_000C7130(obj->link8C);
    if (t && sub_001B2770(obj->link8C->pos60, t->pos60) <= 100.0f)
        return t;
    return r2_player;
}

/* 0x000FC6F0: pass the helper's +0x8C link, the helper and a to 0x0F3D10.  regargs: a=EAX */
void r2_PartCall3D10(int a)
{
    sub_000F3D10(afc_helper->link8C, afc_helper, a);
}

/* 0x00100030: pass obj, the 0x3F612C singleton and arg to 0x0F3D10, then clear the
   controller's +0xBC word.  regargs: obj=ECX; arg is the stack arg */
void r2_PartCallRes(R2Actor *obj, int arg)
{
    R2Actor *r;
    if (!obj)
        for (;;) ;
    r = b10_res3F612C;
    if (!r)
        for (;;) ;
    sub_000F3D10(obj, r, arg);
    b10_ctl->wBC = 0;
}

/* 0x001000C0: reset the animation ids of a's part and b's +0x90 part, then start
   `anim` on b's +0x8C part and on the controller's +0x90 part.
   regargs: a=ECX b=EAX; anim is the stack arg */
void r2_SetPairAnim(R2Actor *a, R2Actor *b, int anim)
{
    R2Actor *l;
    if (!a)
        for (;;) ;
    a->part30->i08 = -1;
    b->link90->part30->i08 = -1;
    l = b->link8C;
    if (!l)
        for (;;) ;
    sub_000832D0(l->part30, anim);
    sub_000832D0(b10_ctl->link90->part30, anim);
}

/* 0x00100FF0: turn obj toward the player by 3 degrees per frame unit and, when
   0x0F5D00 reports it done, send event 0x26 with arg.  Stack args only. */
void r2_TurnAndNotify(R2Actor *obj, int arg)
{
    sub_000F7C40(obj, r2_player, a50_frameUnits * 0.05235988f);
    if (sub_000F5D00(obj))
        sub_000F3D10(obj, (void *)arg, 0x26);
}

/* 0x00107310: spawn effect `id` at offset +0x70 of a's part 0x11, with c.
   regargs: a=ECX c=EAX; id is the stack arg */
void r2_EffectAtPart(void *a, int c, int id)
{
    uint8_t *p = (uint8_t *)sub_0001D0F0(a, 0x11);
    sub_000494D0(id, p + 0x70, c);
}

/* 0x00108B80: tell obj's kind-5 component to switch to `mode` unless it is already
   in that mode (mode 6 is always re-sent).  regargs: obj=ESI mode=EDI */
void r2_SetComp5Mode(R2Actor *obj, int mode)
{
    R2Comp5 *c;
    if (!obj)
        for (;;) ;
    c = (R2Comp5 *)sub_0001D960(obj, 5);
    if (c->mode6C != mode || c->mode6C == 6)
        sub_000F3D10(obj, c, mode);
}

/* 0x0010CB30: as 0x108B80 but modes 6 and 7 are always re-sent.  regargs: obj=ESI mode=EDI */
void r2_SetComp5ModeB(R2Actor *obj, int mode)
{
    R2Comp5 *c;
    if (!obj)
        for (;;) ;
    c = (R2Comp5 *)sub_0001D960(obj, 5);
    if (c->mode6C != mode || mode == 6 || mode == 7)
        sub_000F3D10(obj, c, mode);
}

/* 0x0010D2B0: start effect `id` at obj's position unless the kind-5 component
   already holds one at +0xE4.  regargs: obj=EAX; id is the stack arg */
void r2_Comp5StartE4(R2Actor *obj, int id)
{
    R2Comp5 *c = (R2Comp5 *)sub_0001D960(obj, 5);
    if (c->effE4 < 0)
        c->effE4 = sub_000494D0(id, obj->pos60, 1);
}

/* 0x0010D2F0: release the kind-5 component's +0xE4 effect.  regargs: obj=EAX */
void r2_Comp5ReleaseE4(R2Actor *obj)
{
    R2Comp5 *c = (R2Comp5 *)sub_0001D960(obj, 5);
    if (c->effE4 >= 0) {
        sub_00048250(c->effE4);
        c->effE4 = -1;
    }
}
