/* Area rtc, group 2: tail-call wrappers in 0x000D4590..0x000FD160. Names inferred. */
#include "rtc.h"

/* 0x000D4590: detach the nodes of the actor's node record when it has any. */
void rtc_ActorDetachNodes(RtcActor *a)
{
    RtcObj *n = a->node3B0;
    if (n->p20)
        r1b_RecDetachNodes(n);
}

/* 0x000D51E0: hide the actor's node. */
void rtc_ActorHideNode(RtcActor *a)
{
    r1_NodeHide(a->node3B0);
}

/* 0x000DE8E0: select value v through 0x00037FD0 and remember the previous
   one; 7 restores the remembered value instead. */
int rtc_SelectRemember(int v)
{
    int old;
    if (v == 7)
        return sub_00037FD0(adc_30D6BC);
    old = sub_00037FD0(v);
    adc_30D6BC = old;
    return old;
}

/* 0x000E07F0: query the actor's handle at +0x2EC (hangs on a null actor). */
int rtc_ActorHandleQuery(RtcActor *a)
{
    if (!a)
        for (;;) ;
    return sub_0019A900(a->handle2EC);
}

/* 0x000E9DF0: apply the item's value at +0x0C to the player stats. */
void rtc_ApplyItemToStats(void *unused, RtcObj *item)
{
    if (item)
        sub_000D2A50(&g_stats, item->iC);
}

/* 0x000EA770: start screen mode 1. */
void rtc_ScreenMode1(int unused1, int unused2)
{
    sub_000E8A50(1, 0);
}

/* 0x000EA790: start screen mode 0. */
void rtc_ScreenMode0(int unused1, int unused2)
{
    sub_000E8A50(0, 0);
}

/* 0x000EA900: free a stage link using the 16-bit id at +0x0C of p. */
void rtc_StageLinkFreeById(void *stage, RtcObj *p)
{
    if (stage && p)
        r2d_StageLinkFree(stage, (int16_t)p->iC);
}

/* 0x000EADF0: call 0x000E1F30 with the id at +0x0C of p. */
void rtc_StageCallById(void *stage, RtcObj *p)
{
    if (stage && p)
        sub_000E1F30(stage, p->iC);
}

/* 0x000F9590: set animation 0x18 on the behaviour object of o. */
void rtc_SetAnim18(void *o)
{
    afc_SetBothAnims(afc_DispatchByType(o), 0x18);
}

/* 0x000F9D90: set animation 2 on the behaviour object of o. */
void rtc_SetAnim2(void *o)
{
    afc_SetBothAnims(afc_DispatchByType(o), 2);
}

/* 0x000FAEB0: set animation 0x33 on the behaviour object of o. */
void rtc_SetAnim33(void *o)
{
    afc_SetBothAnims(afc_DispatchByType(o), 0x33);
}

/* 0x000FAF10: set animation 0x40 on the behaviour object of o. */
void rtc_SetAnim40(void *o)
{
    afc_SetBothAnims(afc_DispatchByType(o), 0x40);
}

/* 0x000FB260: set animation 0x30 on the behaviour object of o. */
void rtc_SetAnim30(void *o)
{
    afc_SetBothAnims(afc_DispatchByType(o), 0x30);
}

/* 0x000FD160: set animation 1 on the helper's linked actor (hangs while it
   has none). */
void rtc_HelperLinkAnim1(int unused1, int unused2)
{
    RtcActor *l = afc_helper->link8C;
    if (!l)
        for (;;) ;
    sub_000832D0(l->anim30, 1);
}

/* 0x000E3C00: pause the actor's track once (hangs on a null actor). */
void rtc_ActorPauseTrack(RtcActor *a)
{
    if (!a)
        for (;;) ;
    if (a->handle2EC < 0 || a->paused2F8)
        return;
    a5b_SndPause();
    a->paused2F8 = 1;
    r4d_TrackPause(a->handle2EC);
}

/* 0x000EA3C0: play the item's rumble effect when rumble is enabled. */
void rtc_ItemShock(void *owner, RtcObj *item)
{
    if (item && owner && aa0_enabled413142)
        a5b_ShockPlay(0, item->iC);
}

/* 0x000EB000: call 0x00019350 with the item's time (+0x0C, scaled by the
   frame rate and 0.001) and its value at +0x10. */
void rtc_ItemTimedCall(void *owner, RtcObj *item)
{
    if (item)
        sub_00019350(RTC_FTOI((float)item->iC * rfl_fps42C964 * 0.001f), item->i10);
}

/* 0x000F5330: when the boss is active set animation 0x10 on its linked actor
   and on records 0 and 1 (hangs while it has no linked actor). */
void rtc_BossAnim10(int unused1, int unused2)
{
    RtcActor *l;
    if (!g_acb_bossMgr->activeA8)
        return;
    l = g_acb_bossMgr->link8C;
    if (!l)
        for (;;) ;
    sub_000832D0(l->anim30, 0x10);
    rtc_RecSetAnim(0, 0x10);
    rtc_RecSetAnim(1, 0x10);
}

/* 0x000F9280: clear +0x9C of the behaviour object and switch it to
   animation 0x1C unless that is already playing. */
void rtc_SetAnim1CIfNot(RtcActor *o)
{
    RtcObj *s = afc_DispatchByType(o);
    s->i9C = 0;
    if (o->anim30->cur8 != 0x1C)
        afc_SetBothAnims(s, 0x1C);
}

/* 0x000FC8C0: set animation 0 on the helper's linked actor (hangs while it
   has none). */
void rtc_HelperLinkAnim0(int unused1, int unused2)
{
    RtcActor *l = afc_helper->link8C;
    if (!l)
        for (;;) ;
    sub_000832D0(l->anim30, 0);
}

/* 0x000FFDD0: set animation 0x2C on both actors linked to the minion. */
void rtc_MinionAnim2C(int unused1, int unused2)
{
    RtcActor *l;
    if (!afc_minion)
        for (;;) ;
    l = afc_minion->link8C;
    if (!l)
        for (;;) ;
    sub_000832D0(l->anim30, 0x2C);
    sub_000832D0(afc_minion->link90->anim30, 0x2C);
}

/* 0x00100C00: set animation 0x26 on both actors linked to the controller. */
void rtc_CtlAnim26(int unused1, int unused2)
{
    RtcActor *l;
    if (!b10_ctl)
        for (;;) ;
    l = b10_ctl->link8C;
    if (!l)
        for (;;) ;
    sub_000832D0(l->anim30, 0x26);
    sub_000832D0(b10_ctl->link90->anim30, 0x26);
}

/* 0x00100FA0: set animation 0x28 on both actors linked to the controller. */
void rtc_CtlAnim28(int unused1, int unused2)
{
    RtcActor *l;
    if (!b10_ctl)
        for (;;) ;
    l = b10_ctl->link8C;
    if (!l)
        for (;;) ;
    sub_000832D0(l->anim30, 0x28);
    sub_000832D0(b10_ctl->link90->anim30, 0x28);
}

/* 0x001010F0: set animation 0x2A on both actors linked to the controller. */
void rtc_CtlAnim2A(int unused1, int unused2)
{
    RtcActor *l;
    if (!b10_ctl)
        for (;;) ;
    l = b10_ctl->link8C;
    if (!l)
        for (;;) ;
    sub_000832D0(l->anim30, 0x2A);
    sub_000832D0(b10_ctl->link90->anim30, 0x2A);
}

/* 0x000D2360: player event: refresh the stats, set flag 0x80000, and unless
   in mode 0x1B/0x1C switch to state 10 (setting +0xE0 to 0x20 when flag is
   set); then run 0x000C5B10 and post 0x10000. */
void rtc_PlayerEventA(int flag)
{
    sub_000D1930(&rtc_stats);
    rtc_stats.flags150 |= 0x80000;
    sub_00023BC0(0);
    if (rtc_stats.modeD8 != 0x1B && rtc_stats.modeD8 != 0x1C) {
        abc_SetState(&rtc_stats, 10);
        if (flag)
            rtc_stats.iE0 = 0x20;
    }
    sub_000C5B10();
    sub_0019BE90(0x10000);
}

/* 0x000D3620: as 0x000D2360 without the +0xE0 update. */
void rtc_PlayerEventB(int unused)
{
    sub_000D1930(&rtc_stats);
    rtc_stats.flags150 |= 0x80000;
    sub_00023BC0(0);
    if (rtc_stats.modeD8 != 0x1B && rtc_stats.modeD8 != 0x1C)
        abc_SetState(&rtc_stats, 10);
    sub_000C5B10();
    sub_0019BE90(0x10000);
}

/* 0x000E9D20: reset a screen's cursor state and, while below its maximum,
   start mode 1. */
void rtc_ScreenReset(RtcScreen *s, int unused)
{
    if (!s)
        return;
    s->i418 = 0;
    s->i41C = 0;
    s->i518 = 1;
    s->i430 = 0;
    if (s->cur40C < s->max410)
        sub_000E8920(1, 0);
}

/* 0x000EB250: show an item on the panel object at 0x003E1270 (mode 1 when
   its id at +0x0C is negative, otherwise mode 2 plus its id and value). */
void rtc_PanelShowItem(void *owner, RtcObj *item)
{
    if (!item)
        return;
    if (item->iC < 0) {
        sub_00019000(ae0_obj3E1270, 1);
        return;
    }
    sub_00019000(ae0_obj3E1270, 2);
    sub_0001AB00(ae0_obj3E1270, 2, 3, item->iC, item->i10);
}

/* 0x000F4E30: boss event: kind 5 restores +0x110 from +0x120 and runs
   0x000F3D10 on the linked actor and the aux object with 4 (hangs while
   either is missing); kind a == 2 runs 0x000F4CA0. */
void rtc_BossEvent(void *o, int a, int kind)
{
    RtcActor *l, *x;
    if (!o)
        for (;;) ;
    if (kind != 5) {
        if (a == 2)
            sub_000F4CA0();
        return;
    }
    {
        g_acb_bossMgr->i110 = g_acb_bossMgr->i120;
        l = g_acb_bossMgr->link8C;
        if (!l)
            for (;;) ;
        x = g_acb_bossAux;
        if (!x)
            for (;;) ;
        sub_000F3D10(l, x, 4);
    }
}

/* 0x000FE540: mode 0 syncs the minion's linked record and hides its
   +0x1A8 record; mode 1 does the opposite. */
void rtc_MinionSwapVisible(int mode)
{
    if (mode == 0) {
        r1b_RecSyncVisible(afc_minion->link8C);
        r1b_RecHideAll(afc_minion->rec1A8);
    } else if (mode == 1) {
        r1b_RecHideAll(afc_minion->link8C);
        r1b_RecSyncVisible(afc_minion->rec1A8);
    }
}

/* 0x000FFD40: set animation 0x2B on both actors linked to the minion. */
void rtc_MinionAnim2B(int unused1, int unused2)
{
    RtcActor *l;
    if (!afc_minion)
        for (;;) ;
    l = afc_minion->link8C;
    if (!l)
        for (;;) ;
    sub_000832D0(l->anim30, 0x2B);
    sub_000832D0(afc_minion->link90->anim30, 0x2B);
}

/* 0x000D5870: update a switch's state from its node flag 0x10000 (state 1
   = on, 2 = off; turning on from off also sets flag 2), resetting its timer
   on a change, then run 0x000D5200. */
void rtc_SwitchUpdate(RtcSwitch *o)
{
    if (!(o->flags0 & 1)) {
        if (o->node3B0->iC & 0x10000) {
            if (o->state14 == 1)
                goto done;
            o->flags0 |= 2;
            o->state14 = 1;
        } else {
            if (o->state14 != 2)
                goto done;
            o->state14 = 1;
        }
    } else {
        if ((o->node3B0->iC & 0x10000) || o->state14 == 2)
            goto done;
        o->state14 = 2;
    }
    o->i18 = 0;
    o->f1C = 0.0f;
    o->f20 = 0.0f;
done:
    sub_000D5200(o);
}

/* 0x000E0D50: open menu page k (0..5); others return 0. */
int rtc_OpenPage(int k)
{
    switch (k) {
    case 0:
        return sub_000E70C0(0);
    case 1:
        return sub_000E70C0(1);
    case 2:
        return sub_000E70C0(2);
    case 3:
        return sub_000E70C0(3);
    case 4:
        return sub_000E70C0(4);
    case 5:
        return sub_000E70C0(5);
    case 6:
        break;
    }
    return 0;
}

/* 0x000E0FB0: hide (on != 0) or show the message window; showing drops a
   stale record handle, refreshes message 0 of the current table at size
   20 and then draws the window (tail jump to 0x0003FCE0, reusing the
   argument slot). Only one argument is read. */
void rtc_MsgWindow(int on)
{
    if (on) {
        rtc_hidden3F0A68 = 0;
        return;
    }
    rtc_hidden3F0A68 = 1;
    if (rtc_rec3F0A74 >= 0 && !r1c_GetRecThunk(rtc_rec3F0A74))
        rtc_rec3F0A74 = -1;
    if (r2b_g3F1B1C) {
        sub_0003FC10(aec_3F118C);
        sub_0003FCB0(aec_3F118C, r6d_MsgGet(r2b_g3F1B1C, 0), 0, 20.0f, -1.0f);
    }
    sub_0003FCE0(aec_3F118C);
}

/* 0x000E6CE0: reset the menu block at 0x003F0758 for mode k (any mode but
   6 also clears cheat flag 2), refresh 0x000EC320 and open it. */
void rtc_MenuReset(int k)
{
    int i;
    uint32_t *w;
    if (k != 6)
        rtc_cheatFlags413130 &= ~2u;
    w = (uint32_t *)&g_acb_3F0758;
    for (i = 0; i < (int)(sizeof(g_acb_3F0758) / 4); i++)
        w[i] = 0;
    g_acb_3F0758.cur4 = -1;
    g_acb_3F0758.mode0 = k;
    for (i = 0; i < 9; i++)
        g_acb_3F0758.items8[i].v0 = 0;
    g_acb_3F0758.sel2E8 = -1;
    g_acb_3F0758.sel2EC = -1;
    g_acb_3F0758.i2F0 = 0;
    g_acb_3F0758.i2F4 = 0;
    g_acb_3F0758.i2F8 = 1;
    g_acb_3F0758.i2FC = -1;
    g_acb_3F0758.i314 = 0;
    sub_000EC320();
    sub_000E66F0(&g_acb_3F0758);
}

/* 0x000EA500: give the player item id (+0x0C): with an owner, as an
   animation when the player model is the stats model, otherwise through
   0x000D0200; without one, also start the item stage. A negative id starts
   the owner's stage instead. */
void rtc_GiveItem(void *owner, RtcObj *item)
{
    int id;
    if (!item)
        return;
    id = item->iC;
    if (id >= 0) {
        if (owner) {
            if (rtc_playerObj->anim30 == rtc_stats.modelEF4) {
                PlayerObj_SetAnim((PlayerObj *)&rtc_stats, id);
                return;
            }
            sub_000D0200(&rtc_stats, 1, id);
            return;
        }
        if (rtc_playerObj->anim30 != rtc_stats.modelEF4)
            sub_000D0200(&rtc_stats, 1, id);
        sub_000E1060(rtc_playerObj, item->iC, 0, 0);
        return;
    }
    if (owner)
        r2d_StageStart(owner);
}

/* 0x000EA6F0: close the menu page; page 6 stops its stream, others mark
   the track entries 1 and 7 before *pos and go to state 3. */
void rtc_MenuClose(RtcScreen *s, int *pos)
{
    sub_000E63A0(1);
    if (!s)
        return;
    if (s->kind0 != 6) {
        sub_000E8690(4, s->cur40C);
        r2b_TrackMarkBefore(s, 1, *pos, 0);
        r2b_TrackMarkBefore(s, 7, *pos, 0);
        sub_000E8690(1, 0);
        sub_000D2A50(&g_stats, 3);
        return;
    }
    r2d_StageStreamStop(s);
    sub_000E0780();
}

/* 0x000F5410: put the boss into phase 3 facing -pi/2, flag its part and,
   when active, set animation 0x10 on its linked actor and records 0 and 1. */
void rtc_BossPhase3(int unused1, int unused2)
{
    RtcActor *m = g_acb_bossMgr;
    RtcActor *l;
    m->yaw118 = -1.57079637f;
    m->phase100 = 3;
    m->f9C = 0.0f;
    m->partBC->flags90 |= 0x40;
    if (!m->activeA8)
        return;
    l = m->link8C;
    if (!l)
        for (;;) ;
    sub_000832D0(l->anim30, 0x10);
    rtc_RecSetAnim(0, 0x10);
    rtc_RecSetAnim(1, 0x10);
}

/* 0x000CC180: choose the camera mode: when the camera is free, compare the
   target distance (0x000CBB70, or -1 when the current step is of kind 1 or
   6) with the camera value; apply the first camera when it is farther,
   otherwise (or when either is negative or the camera is locked) refresh
   0x000CC070 and, except in the nearer case, apply the first camera too. */
void rtc_CameraChoose(RtcCamUser *o)
{
    float d, v;
    if (!r1c_camFlag42CB0C) {
        int k;
        if (o->on318 && (k = o->kinds3A8[o->steps528[o->cur31C]]) != 6 && k != 1)
            d = sub_000CBB70(o);
        else
            d = -1.0f;
        v = r1c_CamValue();
        if (d >= 0.0f && v >= 0.0f) {
            if (d > v) {
                r1e_CamApplyFirst();
                return;
            }
            sub_000CC070(o);
            return;
        }
    }
    sub_000CC070(o);
    r1e_CamApplyFirst();
}

/* 0x000E0EE0: query flag n of group k (0..6; groups 5 and 6 share a
   block); -1 for a negative n or an unknown group. */
int rtc_GroupFlag(int k, int n)
{
    if (n < 0)
        return -1;
    switch (k) {
    case 0:
        return sub_00048B20(0x1CA + n, 0);
    case 1:
        return sub_00048B20(0x1D4 + n, 0);
    case 2:
        return sub_00048B20(0x1DE + n, 0);
    case 3:
        return sub_00048B20(0x1E8 + n, 0);
    case 4:
        return sub_00048B20(0x1F2 + n, 0);
    case 5:
    case 6:
        return sub_00048B20(0x1FC + n, 0);
    }
    return -1;
}

/* 0x000D7100: look up the stage entry for the buttons b in the table at
   0x002E7D58 (ended by id -1); on a match whose pair value (or the debug
   flag 0x10) fits one of its 4 slots, start that stage in the mode block
   at 0x003EDB60 and clear script variable 0x003EE6C0, otherwise set mode
   3. regargs: calls 0x000D7090 with EAX=b */
void rtc_StageSelectByButtons(int b)
{
    int id = r2b_TakeButtons((uint16_t)b);
    RtcStageEnt *e;
    int i, j;
    for (i = 0, e = r2b_stages2E7D58; e->id > -1; e++, i++) {
        if (e->id != id)
            continue;
        for (j = 0; j < 4; j++) {
            if (r2b_PairB(0) == e->base10 + j || (r2_modes3EDB60.flagsA4 & 0x10)) {
                r2_modes3EDB60.id78 = id;
                r2_modes3EDB60.slot70 = j;
                r2_modes3EDB60.entry68 = i;
                r2_modes3EDB60.on64 = 1;
                r2_modes3EDB60.mode60 = 1;
                r2_modes3EDB60.v8C[0] = -1;
                r2_modes3EDB60.v8C[1] = -1;
                r2_modes3EDB60.v8C[2] = -1;
                r2_modes3EDB60.v8C[3] = -1;
                r2_modes3EDB60.v8C[4] = -1;
                r2_modes3EDB60.i6C = 0;
                r2_modes3EDB60.t74 = 0.0f;
                r2_modes3EDB60.iA0 = 0;
                af0_ClearVar3EE6C0();
                return;
            }
        }
    }
    r2_modes3EDB60.on64 = 0;
    r2_modes3EDB60.mode60 = 3;
}

/* 0x000E9F30: finish a menu screen once its cursor reached the end (and
   it is page 6 or has +0x328 set): reset the player, clear the screen's
   cursor and entry state, mark track entries 2 and 6 before the position
   pos->base + pos->offset, close the panel and run event (2, 1). */
void rtc_ScreenFinish(RtcScreen *s, RtcTrackPos *pos)
{
    int i;
    if (!s || !pos || !s->i408 || s->cur40C < s->max410)
        return;
    if (s->kind0 != 6 && !s->i328)
        return;
    sub_000D2A50(&g_stats, 4);
    PlayerObj_SetAnim((PlayerObj *)&g_stats, 0);
    sub_000E63A0(2);
    s->i418 = 0;
    s->i41C = 0;
    s->f420 = 0.0f;
    s->i424 = 0;
    s->i428 = 0;
    s->i430 = 0;
    for (i = 0; i < 7; i++)
        s->ents44C[i].v0 = 0;
    r2b_TrackMarkBefore(s, 2, pos->base0 + pos->off4, 0);
    r2b_TrackMarkBefore(s, 6, pos->base0 + pos->off4, 0);
    sub_000253D0(0, 0);
    sub_000E8690(0, 0);
    sub_00019000(ae0_obj3E1270, 2);
    sub_000C85C0();
    sub_000A8B80();
    sub_00025D50(2, 1);
}
