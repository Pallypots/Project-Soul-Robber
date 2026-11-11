/* Area rbi: boss effect set-up (rbi_5). Names inferred. */
#include "rbi.h"

/* 0x000FBD50: set up the body object of the boss whose controller is *0x003F6114: scale
   1.25, collision sizes, the component-0xD offsets (-6.25, -12.5), the controller's two
   tables and its six colour entries with the 50/100 ranges.
   regargs: o=ESI */
void rbi_BossSetup0FBD50(RbiFxObj *o)
{
    RbiFxComp *c = rbi_Comp1D960(o, 0xD);
    RbiBossCtl *ctl = afc_body;

    o->scale70.z = 1.25f;
    o->scale70.y = 1.25f;
    o->scale70.x = 1.25f;
    o->flags0C |= 3;
    o->scale70.w = 1.0f;
    o->i124 = 1;
    sub_000F5D60(o, 1.25f, -10.0f, 4.0f, rbi_v278A88);
    sub_000F5DD0(o, 1.25f, 5.0f, rbi_v278A9C);
    o->iF0 = 2;
    o->iF4 = 2;
    sub_000F5E30(o, 1.25f, rbi_v278AAC, rbi_v278ABC);
    o->i11C = 1;
    o->i120 = 2;
    c->f18 = -6.25f;
    c->f1C = -12.5f;
    ctl->p74 = rbi_d319078;
    ctl->p78 = rbi_d3190F8;
    sub_000F90D0(ctl);
    ctl->fC0 = 50.0f;
    ctl->fC4 = 100.0f;
    ctl->colC8[0] = &rbi_c318FE8;
    ctl->colC8[1] = &rbi_c318FB8;
    ctl->colC8[2] = &rbi_c318FF8;
    ctl->colC8[3] = &rbi_c318FC8;
    ctl->colC8[4] = &rbi_c319008;
    ctl->colC8[5] = &rbi_c318FD8;
}

/* 0x001003A0: the same set-up for the boss whose controller is *0x003F6128, with its own
   tables, offsets (-6.25, -16.25) and ranges 40/80.
   regargs: o=ESI */
void rbi_BossSetup1003A0(RbiFxObj *o)
{
    RbiFxComp *c = rbi_Comp1D960(o, 0xD);
    RbiBossCtl *ctl = b10_ctl;

    o->scale70.z = 1.25f;
    o->scale70.y = 1.25f;
    o->scale70.x = 1.25f;
    o->flags0C |= 3;
    o->scale70.w = 1.0f;
    o->i124 = 1;
    sub_000F5D60(o, 1.25f, -10.0f, 4.0f, rbi_v278D20);
    sub_000F5DD0(o, 1.25f, 5.0f, rbi_v278D34);
    o->iF0 = 2;
    o->iF4 = 2;
    sub_000F5E30(o, 1.25f, rbi_v278D44, rbi_v278D54);
    o->i11C = 1;
    o->i120 = 2;
    c->f18 = -6.25f;
    c->f1C = -16.25f;
    ctl->p74 = rbi_d319368;
    ctl->p78 = rbi_d319410;
    sub_000F90D0(ctl);
    ctl->fC0 = 40.0f;
    ctl->fC4 = 80.0f;
    ctl->colC8[0] = &rbi_c318F28;
    ctl->colC8[1] = &rbi_c318EF8;
    ctl->colC8[2] = &rbi_c318F38;
    ctl->colC8[3] = &rbi_c318F08;
    ctl->colC8[4] = &rbi_c318F48;
    ctl->colC8[5] = &rbi_c318F18;
}

/* 0x000FE040: set up the helper body of the boss (*0x003F611C): flags 3 and 0x441, scale
   1.35, collision sizes, the hit component (kind 0xD) with 17 hit points and its three
   handlers, the state component (kind 5) with its two tables and the kind's health, and the
   helper's timers (rate 40 per second, 4.0, 120.0) and counters cleared.
   regargs: o=ESI */
void rbi_HelperSetup0FE040(RbiFxObjB *o)
{
    RbiHitComp2 *h = (RbiHitComp2 *)rbi_Comp1D960(o, 0xD);
    RbiStateCompB *s = (RbiStateCompB *)rbi_Comp1D960(o, 5);
    RbiHelper *hp = afc_helper;

    o->flags0C |= 3;
    o->flags10 |= 0x441;
    h->flags10 |= 0x80000000u;
    o->scale70.z = 1.35000002f;
    o->scale70.y = 1.35000002f;
    o->scale70.x = 1.35000002f;
    o->scale70.w = 1.0f;
    o->i124 = 1;
    sub_000F5D60(o, 1.35000002f, -17.0f, 5.5f, rbi_v278B28);
    sub_000F5DD0(o, 1.35000002f, 5.69999981f, rbi_v278B3C);
    o->iF0 = 2;
    o->iF4 = 2;
    sub_000F5E30(o, 1.35000002f, rbi_v278B4C, rbi_v278B5C);
    o->i11C = 1;
    o->i120 = 2;
    h->f18 = -10.8000002f;
    h->f1C = -21.6000004f;
    h->i14 = 0x11;
    h->fn24 = r2c_HelperDetach;
    h->fn28 = sub_000FDD70;
    h->fn2C = sub_000FD420;
    s->tab74 = rbi_tab3191B0;
    s->tab78 = rbi_tab3191DC;
    sub_000F3B70(o, 0);
    s->hpMax58 = s->hp54 = sub_00171D50(o->kind04, o->var08, 0);
    hp->rateA8 = 40.0f / a50_framesPerSecond;
    hp->iE4 = 0;
    hp->iE8 = 0;
    hp->i90 = 0;
    hp->fD4 = 0.0f;
    hp->fD8 = 0.0f;
    hp->fAC = 4.0f;
    hp->iC0 = 0;
    hp->sEC = 0;
    hp->iF8 = 0;
    hp->fF0 = 120.0f;
}
