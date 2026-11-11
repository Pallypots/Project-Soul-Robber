/* Area rbg: game functions in 0x000D0000..0x000DFFFF (rbg_1). Names inferred. */
#include "rbg.h"

/* 0x000D00B0: load Mayor dance script idx (0..6): open its movie archive, keep the movie id in
   g_3EDB38, allocate the script node, parse the text file and start its first entry. */
void rbg_LoadDance0D00B0(RbgJack *m, int idx)
{
    int ids[7];
    const char *names[7];
    int movie;
    void *node;
    RbgAnim *h;
    int *e;

    ids[0] = 0x65;
    ids[1] = 0x66;
    ids[2] = 0x67;
    ids[3] = 0x68;
    ids[4] = 0x69;
    ids[5] = 0x6A;
    ids[6] = 0x6A;
    movie = ids[idx];
    names[0] = rbg_sDance00;
    names[1] = rbg_sDance01;
    names[2] = rbg_sDance02;
    names[3] = rbg_sDance03;
    names[4] = rbg_sDance04;
    names[5] = rbg_sDance05;
    names[6] = rbg_sDance05;
    sub_0004FA70(movie, sub_00053AB0(sub_0004F680(movie), 0, 0xCD4));
    sub_0004F4E0();
    sub_0004F700(movie);
    g_3EDB38 = movie;
    g_3EDB3C = sub_00053BC0(rbg_sJkMngSub, 0xCDA);
    node = sub_00053AB0(0xE0, 0, 0xCDC);
    sub_001AE970(node);
    h = sub_00083030(node, 1, abc_p42C8E0);
    m->danceEF4 = h;
    sub_0001DA90(h, names[idx]);
    e = sub_00083140(m->danceEF4, 0);
    if (e)
        sub_000831A0(m->danceEF4, 0, *e);
    else
        m->danceEF4 = 0;
    sub_0004F720();
    sub_00053BE0();
}

/* 0x000D0200: switch Jack's model animation to the dance script (on != 0) or back to the
   default player (on == 0), keeping the node and timing, rebinding the component, and
   starting animation anim (0x90 when on and anim == 0). Releases the two model effects. */
void rbg_SetDance0D0200(RbgJack *m, int on, int anim)
{
    RbgModel *o;
    RbgAnimNode *node;
    int t18;
    RbgComp *c;
    RbgAnim *a;

    if (!m->danceEF4)
        return;
    o = m->modelFD8;
    node = o->anim30->node14;
    t18 = o->anim30->i18;
    sub_0001EB80(o);
    c = sub_0001D960(&m->tblFD4->recs08[m->i1B8], 1);
    if (on)
        a = m->danceEF4;
    else
        a = abc_p42C8E0->anim2D0;
    m->modelFD8->anim30 = a;
    m->modelFD8->anim30->node14 = node;
    m->modelFD8->anim30->i18 = t18;
    m->modelFD8->anim30->node14->i84 = 0;
    m->modelFD8->anim30->node14->i88 = 0;
    m->modelFD8->anim30->owner1C = m->modelFD8;
    sub_000831A0(m->modelFD8->anim30, 0, *sub_00083140(m->modelFD8->anim30, 0));
    sub_00083160(m->modelFD8->anim30, m->modelFD8->i20);
    if (c->i30 > -1) {
        sub_0007FD30(m->modelFD8->anim30->node14, m->modelFD8->i34, c->i30);
        sub_0007FD60(m->modelFD8->i20, c->i30);
    }
    sub_0001E9B0(m->sceneFD0, m->modelFD8, m->modelFD8->i14C, 5, 0x11);
    if (on) {
        if (!anim)
            anim = 0x90;
        if (m->iD4 != 4 && m->iD4 != 5) {
            m->iE0 = 8;
            m->fE8 = 0.0f;
        }
    }
    m->modelFD8->anim30->i08 = -1;
    sub_000832D0(m->modelFD8->anim30, anim);
    sub_001B1190(m->modelFD8->anim30->node14, 1.0f);
    a = m->modelFD8->anim30;
    sub_001AEDD0(m->modelFD8->anim30->node14, ((RbgAnimEnt *)sub_00083120(a, a->i08))->f10);
    sub_001AEF10(m->modelFD8->anim30->node14, 3);
    o = m->modelFD8;
    if (o->h13C)
        sub_0005BC50(o->h13C);
    if (o->h134)
        sub_00033C20(o->h134);
    o->h13C = 0;
    o->h134 = 0;
    m->anim12C = anim;
    m->anim128 = anim;
}


/* 0x000D72B0: build the stage page of the menu: count the five events 0x7F..0x83 still open,
   then add one item per open event (13 + k for the last open one before the final event,
   8 + k otherwise; event 0x83 always adds item 12). */
void rbg_StageMenu0D72B0(void)
{
    int left = 5;
    int n = 0;

    sub_000DFD60(rbg_g41786C, r2b_stages2E7D58[r2_modes3EDB60.stage08].i04, 0x47);
    if (sub_000D9A70(0x7F))
        left = 4;
    if (sub_000D9A70(0x80))
        left--;
    if (sub_000D9A70(0x81))
        left--;
    if (sub_000D9A70(0x82))
        left--;
    if (sub_000D9A70(0x83))
        left--;
    if (!sub_000D9A70(0x7F)) {
        n = 1;
        sub_000DFDB0(rbg_g41786C, left == n ? 0xD : 8, 0xC7);
    }
    if (!sub_000D9A70(0x80)) {
        n++;
        sub_000DFDB0(rbg_g41786C, left == n ? 0xE : 9, 0xC7);
    }
    if (!sub_000D9A70(0x81)) {
        n++;
        sub_000DFDB0(rbg_g41786C, left == n ? 0xF : 0xA, 0xC7);
    }
    if (!sub_000D9A70(0x82)) {
        n++;
        sub_000DFDB0(rbg_g41786C, left == n ? 0x10 : 0xB, 0xC7);
    }
    if (!sub_000D9A70(0x83))
        sub_000DFDB0(rbg_g41786C, 0xC, 0xC7);
}

/* 0x000DE6D0: unlock a gallery item. kind 1 sets event bit rbg_bits30C238[idx] of word 12;
   kind 0 sets the bits of reward idx (0..6) in word 14, reward 5 picks the first of stats
   9..11 that is unlocked and not yet taken. adc_30D6B8 receives the item shown; snd != 0
   plays the jingle. */
void rbg_Unlock0DE6D0(int kind, int idx, int snd)
{
    switch (kind) {
    case 1:
        adc_30D6B8 = rbg_bits30C238[idx];
        adc_var3EDCF4 = 4;
        g_eventFlagBits[12] |= 1u << rbg_bits30C238[idx];
        break;
    case 0:
        adc_var3EDCF4 = 3;
        switch (idx) {
        case 0:
            g_eventFlagBits[14] |= 0x87;
            adc_30D6B8 = 0;
            break;
        case 1:
            g_eventFlagBits[14] |= 0x38;
            adc_30D6B8 = 3;
            break;
        case 2:
            g_eventFlagBits[14] |= 0x40;
            adc_30D6B8 = 6;
            break;
        case 3:
            g_eventFlagBits[14] |= 0x6000;
            adc_30D6B8 = 0xD;
            break;
        case 4:
            g_eventFlagBits[14] |= 0x200;
            adc_30D6B8 = 9;
            break;
        case 5:
            if (!sub_000D9A70(0xF5))
                return;
            adc_30D6B8 = -1;
            if (Stats_Get(&g_stats, 9) >= 0 && !(g_eventFlagBits[14] & 0x400)) {
                g_eventFlagBits[14] |= 0x400;
                adc_30D6B8 = 0xA;
            }
            if (Stats_Get(&g_stats, 10) >= 0 && !(g_eventFlagBits[14] & 0x800)) {
                g_eventFlagBits[14] |= 0x800;
                adc_30D6B8 = 0xB;
            }
            if (Stats_Get(&g_stats, 11) >= 0 && !(g_eventFlagBits[14] & 0x1000)) {
                g_eventFlagBits[14] |= 0x1000;
                adc_30D6B8 = 0xC;
            } else if (adc_30D6B8 == -1)
                return;
            break;
        case 6:
            g_eventFlagBits[14] |= 0x100;
            adc_30D6B8 = 8;
            break;
        }
        break;
    }
    if (snd)
        sub_000252A0(1, 0x258);
}
