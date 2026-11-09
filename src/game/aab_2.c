/* Area aab, group 2: records, callbacks and dispatch (0x000A58B0..0x000A9FE0). Names inferred. */
#include "aab.h"

/* 0x000A58B0: dispatch on the kind at +0x1C. */
void aab_DispatchObj1C(AabObj1C *o) { aab_obj1CHandlers[o->kind](o); }

/* 0x000A79B0: -1 when record i is inactive or bit 30/10 set, else 1. */
int aab_RecDCState(int i)
{
    uint32_t f = aab_recDC[i].flags;
    if (!(f & 0x80000001)) return -1;
    return (f & 0x40000400) ? -1 : 1;
}

/* 0x000A7AF0: create the +0xD4 handle from the +0xD8 source once it is ready. */
void aab_SfxAttach(AabSfxObj *o, int a)
{
    if (!o->hD4 && o->srcD8 && o->srcD8->ready20)
        o->hD4 = aab_Attach36750(o->srcD8, a);
}

/* 0x000A7B30: free the source's +0x134 handle and the +0xD4 handle. */
void aab_SfxFree(AabSfxObj *o)
{
    AabSfxHolder *h = (AabSfxHolder *)o->srcD8;
    if (h->h134) aab_Free33C20(h->h134);
    h->h134 = 0;
    if (o->hD4) aab_Free33A40(o->hD4);
}

/* 0x000A9930: mark done while bit 19 of 0x00420010 is set, else dispatch on kind. */
void aab_KindDispatch(AabKindObj *o)
{
    if (aab_flags420010 & 0x80000) { o->flags |= 0x40000000; return; }
    aab_kindHandlers[o->kind](o);
}

/* 0x000A9970: count the pickup in the stats, mark done, spawn effect 0x5A at Jack. */
void aab_KindCollect(AabKindObj *o)
{
    if (o->kind != 0x1C) aab_StatD1E10(aab_stats, o->kind + 0xD, 1);
    o->flags |= 0x40000000;
    aab_Effect494D0(0x5A, aab_player + 0x60, 0);
}

/* 0x000A9CC0: send message 2 to every callback record. */
void aab_CbBroadcast2(void)
{
    int i, n;
    if (!aab_cbTable) return;
    n = aab_cbCount;
    for (i = 0; i < n; i++) aab_cbTable[i].fn(2, &aab_cbTable[i].flag);
}

/* 0x000A9D00: send message 3 to every callback record. */
void aab_CbBroadcast3(void)
{
    int i, n;
    if (!aab_cbTable) return;
    n = aab_cbCount;
    for (i = 0; i < n; i++) aab_cbTable[i].fn(3, &aab_cbTable[i].flag);
}

/* 0x000A9D40: send message 1 to record i unless its flag bit 0 is set. */
void aab_CbSend1(int i)
{
    AabCb16 *r;
    if (i >= aab_cbCount) for (;;) ;
    r = &aab_cbTable[i];
    if (!(r->flag & 1)) r->fn(1, &r->flag);
}

/* 0x000A9FA0: mark record i triggered; bit 2 picks a random 0..1 value at +0x14. */
void aab_Rec34Trigger(int i)
{
    AabRec34 *r;
    if (i >= 10) for (;;) ;
    r = &aab_rec34[i];
    if (r->flags30 & 1) {
        r->flags30 |= 2;
        if (r->flags30 & 4) r->f14 = (float)aab_Rand() * (1.0f / 32767.0f);
    }
}

/* 0x000A9020: claim a free 0xDC record for (o + 0x18, b) and mark it in use; -1 when full. */
int aab_RecDCClaim(uint8_t *o, int b)
{
    float v[4];
    int r;
    v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 1.0f;
    if (aab_CountA81C0() >= 0x30) return -1;
    r = aab_FindA88B0(o + 0x18, b, v);
    if (r < 0) return -1;
    aab_recDC[r].inUse1C = 1;
    return r;
}

/* 0x000A96D0: advance the 0x00420EFC timer while armed; fire 0x000A94B0 every 2 units. */
void aab_TickTimer(void)
{
    if (aab_flags420EF8 & 1) {
        aab_timer420EFC += aab_frameUnits;
        if (aab_timer420EFC >= 2.0f) {
            aab_TimerA94B0();
            aab_timer420EFC = 0.0f;
        }
    }
}

/* 0x000A99B0: collect a stat pickup; at the maximum set flag 2 instead; effect 0x18 at Jack. */
void aab_KindCollectCapped(AabKindObj *o)
{
    int cur = aab_StatGet(aab_stats, o->kind + 0xD);
    if (cur != aab_StatMax(o->kind)) {
        aab_Sound260C0(0, 1, 1);
        aab_StatD1E10(aab_stats, o->kind + 0xD, 1);
    } else {
        aab_StatFlag2(aab_stats);
    }
    aab_Effect494D0(0x18, aab_player + 0x60, 0);
    o->flags |= 0x40000000;
}

/* 0x000A9C60: mark done, effect 0x59 at the object; bit 27 grants 10..500 souls. */
void aab_KindSouls(AabKindObj *o)
{
    int n;
    o->flags |= 0x40000000;
    aab_Effect494D0(0x59, (uint8_t *)o + 0x40, 0);
    if (o->flags & 0x8000000) {
        n = aab_Rand() % 0x1EB + 10;
        aab_Add261A0(1, n);
        aab_Add24D30(2, n);
        aab_StatD1E10(aab_stats, 0xC, n);
        aab_SoulsAdd(n);
    }
}

/* 0x000AA490: send message 3 to record i when its flag bit 0 is set. */
void aab_CbSend3(int i)
{
    AabCb16 *r;
    if (!aab_cbTable) return;
    r = &aab_cbTable[i];
    if (r->flag & 1) r->fn(3, &r->flag);
}

/* 0x000AA4C0: reset via 0x000A9DC0 and clear the 0x003ED970 block. */
void aab_ResetBlock3ED970(void)
{
    aab_ResetA9DC0();
    aab_word3ED970 = 0;
    aab_word3ED974 = 0;
    aab_vec3ED978[0] = 0.0f;
    aab_vec3ED978[1] = 0.0f;
    aab_vec3ED978[2] = 0.0f;
    aab_vec3ED978[3] = 0.0f;
    aab_vec3ED978[4] = 0.0f;
}
