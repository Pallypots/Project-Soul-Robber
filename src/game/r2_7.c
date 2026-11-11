/* Area r2, group 7: boss-stage helpers (0x000FBEF0..0x0010D3D4). Names inferred. */
#include "r2.h"

/* 0x000FBEF0: turn obj toward the player (3 degrees per frame unit); show the body's
   +0x94 object once arg's +0x68 passes 0.333, and send event 0x1D when it passes 0.7
   while the turn angle is below 1.2217.  Stack args obj arg. */
void r2_BodyTurn(R2Actor *obj, R2Arg68 *arg)
{
    R2Minion *m = (R2Minion *)afc_body;
    float a = sub_000F7C40(obj, r2_player, a50_frameUnits * 0.05235988f);
    if (!m->i9C && arg->f68 > 0.333f) {
        sub_0001D610(m->obj94);
        m->i9C++;
    }
    if (arg->f68 > 0.7f && 1.2217305f > a)
        sub_000F3D10(obj, arg, 0x1D);
}

/* 0x00100640: turn obj toward the player (4.5 degrees per frame unit); step 0 shows
   the controller's +0x94 object once arg's +0x68 passes 0.1, step 1 sends event 0x1E
   once it passes 0.6333, later steps send it at once.  Stack args obj arg. */
void r2_CtlTurn(R2Actor *obj, R2Arg68 *arg)
{
    R2Minion *m = (R2Minion *)b10_ctl;
    sub_000F7C40(obj, r2_player, a50_frameUnits * 0.07853982f);
    switch (m->i9C) {
    case 0:
        if (arg->f68 > 0.1f) {
            sub_0001D610(m->obj94);
            m->i9C++;
        }
        break;
    case 1:
        if (arg->f68 > 0.6333f)
            sub_000F3D10(obj, arg, 0x1E);
        break;
    default:
        sub_000F3D10(obj, arg, 0x1E);
        break;
    }
}

/* 0x00103200: when the screen object's +0x8C actor is within 48 units of the player
   (beyond its +0xB0 radius) send it event 1 and set +0x1C0, else clear +0x1AC and
   switch to state 3. */
void r2_ScrApproach(void)
{
    R2Scr3 *s = (R2Scr3 *)b10_scr;
    R2Actor *l = s->link8C;
    float d = sub_001B2770(l->pos60, r2_player->pos60) - l->fB0;
    float v = 0.0f;
    if (!(0.0f > d))
        v = d;
    if (48.0f > v) {
        R2Scr3 *s2 = (R2Scr3 *)b10_scr;
        R2Actor *p = s2->link8C;
        if (!p)
            for (;;) ;
        sub_000F3D10(p, s2, 1);
        ((R2Scr3 *)b10_scr)->i1C0 = 1;
        return;
    }
    s->f1AC = 0.0f;
    sub_00101280(3);
}

/* 0x0010D320: set obj's scale to s and derive its size-dependent values and those
   of its kind-13 component.  regargs: obj=ESI; s is the stack arg */
void r2_SetScaleB(R2Mover2 *obj, float s)
{
    R2Comp13B *c;
    if (!obj)
        for (;;) ;
    c = (R2Comp13B *)sub_0001D960(obj, 0xD);
    obj->fB0 = s * 23.900001525878906f;
    obj->fB4 = s * -30.0f;
    obj->fA4 = s * 0.0f;
    obj->fE8 = s * 27.9f;
    obj->fDC = s * -32.0f;
    obj->fFC = s * -15.0f;
    obj->scale70[2] = s;
    obj->scale70[1] = s;
    obj->scale70[0] = s;
    c->f18 = s * -20.0f;
    c->f1C = s * -33.0f;
}

/* 0x000F8B40: when the first trio actor's part is in state 2, reset all three trio
   actors (flags, event 3), release their effects and mark the helper's three
   active parts with 0x20. */
void r2_TrioReset(void)
{
    R2Trio *o;
    R2TrioHelper *h;
    uint32_t *f;
    int i;
    if (sub_000F3B50(((R2Trio *)sub_000FE3D0())->link8C) == 2) {
        for (i = 0; i < 3; i++) {
            if (i == 0)
                o = (R2Trio *)sub_000FE3D0();
            else if (i == 1)
                o = (R2Trio *)sub_00100110();
            else if (i == 2)
                o = (R2Trio *)sub_000FBAF0();
            o->wA4 = 0;
            f = &o->link8C->flags10;
            *f &= ~0x44;
            o->link8C->flags10 |= 0x220;
            *f = (*f & ~0x141) | 0x200;
            sub_000F3D10(o->link8C, o, 3);
            o->wBC = 0;
        }
    }
    r2_TrioReleaseEffects();
    h = (R2TrioHelper *)sub_000FC4D0();
    for (i = 0; i < 3; i++) {
        R2FlagPart *p = h->partB4[i];
        if (p && (p->flags0C & 1)) {
            p->flags10 &= ~8;
            p->flags0C |= 0x20;
        }
    }
}
