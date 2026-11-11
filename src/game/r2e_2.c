/* Area r2e, group 2: minion and object helpers (0x000F25A0..0x001197A5). Names inferred. */
#include "r2e.h"

/* 0x000F25A0: forward a to 0x000F09E0.  calls 0x000F09E0 with EAX=a */
void r2e_Forward0F09E0(int a)
{
    sub_000F09E0(a);
}

/* 0x000F8C20: dispatch on mode 5 or kind 2 (hang on a null object). */
void r2e_TrioDispatch(void *o, int kind, int mode)
{
    if (!o)
        for (;;) ;
    if (mode != 5) {
        if (kind == 2)
            sub_000F8940(o, kind, mode);
    } else {
        sub_000F8B40();
    }
}

/* 0x000FA8C0: flag the object's record when the target is above 0.65
   or the node is active. */
void r2e_FlagIfAboveA(void *o, R2eObj68 *t)
{
    R2eObjBC *r = sub_000F5F80(o);
    if (t->f68 > 0.65f || sub_000F5D00(o))
        r->wBC = 1;
}

/* 0x000FAED0: same with the threshold 0.8. */
void r2e_FlagIfAboveB(void *o, R2eObj68 *t)
{
    R2eObjBC *r = sub_000F5F80(o);
    if (t->f68 > 0.8f || sub_000F5D00(o))
        r->wBC = 1;
}

/* 0x000FFD90: when the node is active, set the minion's +0x1B8 to 2.5 and send
   event 0x28 with a. */
void r2e_MinionKick(void *o, void *a)
{
    if (sub_000F5D00(o)) {
        r2e_minion3F6120->f1B8 = 2.5f;
        sub_000F3D10(o, a, 0x28);
    }
}

/* 0x001179A0: send event 3.  calls 0x00117580 with EDI=c */
void r2e_Event3(void *o, void *c)
{
    sub_00117580(o, 3, c);
}

/* 0x00119770: send event 0x1F.  calls 0x00117580 with EDI=c */
void r2e_Event1F(void *o, void *c)
{
    sub_00117580(o, 0x1F, c);
}

/* 0x000F32F0: notify type 3 if the 0x003F6100 object exists, then release
   every live id of the 16-entry table at 0x00318CA8. */
void r2e_ReleaseIds(void)
{
    int32_t *p;
    if (r2e_g3F6100)
        sub_000ED600(3);
    for (p = r2e_ids318CA8; p < r2e_ids318CA8 + 16; p++) {
        if (*p != -1 && sub_0004F6D0(*p))
            sub_0004F5D0(*p);
    }
}

/* 0x000F6F00: place the player at (14, 0, -28, 1) and apply the vector at
   0x00318E18 with weight 1. */
void r2e_PlayerPlaceStart(void)
{
    float pos[4];
    pos[0] = 14.0f;
    pos[1] = 0.0f;
    pos[2] = -28.0f;
    pos[3] = 1.0f;
    r2d_PlayerPlace(r2e_player41FEC0, pos);
    sub_000CF330(r2e_player41FEC0, r2e_vec318E18, 1.0f);
}

/* 0x000FF070: put both minion parts into animation 0x21, clear its timer
   and set +0xA6 (hang if anything is missing). */
void r2e_MinionReset(void)
{
    R2eCtl *c = r2e_minion3F6120;
    if (!c)
        for (;;) ;
    if (!c->a8C)
        for (;;) ;
    sub_000832D0(c->a8C->p30, 0x21);
    sub_000832D0(r2e_minion3F6120->b90->p30, 0x21);
    c->v9C = 0;
    c->fA0 = 0.0f;
    c->wA6 = 1;
}

/* 0x000F25B0: zero the velocity vector (scaled by the frame time) and the
   two words at +0x110 (hang on a null object). */
void r2e_VelClear(void *unused, R2eVel *o)
{
    if (!o)
        for (;;) ;
    o->vF0[0] = r2e_frameSeconds * 0.0f;
    o->vF0[1] = r2e_frameSeconds * 0.0f;
    o->vF0[2] = r2e_frameSeconds * 0.0f;
    o->vF0[3] = r2e_frameSeconds * 0.0f;
    o->v110 = 0;
    o->v114 = 0;
}

/* 0x000FD870: drain the helper's +0x54 gauge by its node's whole rate
   (crediting the drained amount to counter 2) and fire event 0x0A at 0. */
void r2e_HelperDrain(void)
{
    R2eHelper *h = r2e_helper3F611C;
    R2eActor *n = (R2eActor *)h->p8C;
    int k = (int)sub_000F3C70(n);
    sub_000F3C40(n);
    ((R2eActor *)h)->f54 -= (float)k;
    if (k > 0)
        sub_000253D0(2, k);
    if (0.0f >= ((R2eActor *)h)->f54) {
        sub_000F3D10(r2e_helper3F611C->p8C, r2e_helper3F611C, 0xA);
        sub_000F3B70(n, 3);
        n->v10 |= 0xD;
    }
}
