/* Area a8c, group 2: demo sound slots and state tables (0x847D0-0x87B60). Names inferred. */
#include "a8c.h"

/* 0x000847D0: set slot i word +0. */
void a8c_SlotSet00(A8cSlotOwner *o, int i, int v) { o->slots04[i].i00 = v; }
/* 0x000847F0: address of slot i sub-block +0x24. */
uint8_t *a8c_SlotSub(A8cSlotOwner *o, int i) { return o->slots04[i].sub24; }
/* 0x00084810: set slot i word +8. */
void a8c_SlotSet08(A8cSlotOwner *o, int i, int v) { o->slots04[i].i08 = v; }
/* 0x00084830: set slot i word +0xC. */
void a8c_SlotSet0C(A8cSlotOwner *o, int i, int v) { o->slots04[i].i0C = v; }

/* 0x00084B10: run 0x1B2490 on slot i's sub-block inside the 0x1B1FC0/0x1B1FE0 bracket. */
void a8c_SlotUpdate(A8cSlotOwner *o, int i)
{
    A8cSlot *s = &o->slots04[i];
    sub_001B1FC0();
    sub_001B2490(s->sub24);
    sub_001B1FE0();
}

/* 0x00084C00: open a handle, optionally releasing via 0x102FA0. */
int a8c_OpenHandle(int a, int release)
{
    int h = sub_001BA7F0(a);
    if (release) a8c_Release102FA0(h);
    return h;
}

/* 0x00084C50: query 0x1BA7C0, 0 for null input or negative result. */
int a8c_QueryHandle(int a)
{
    int r;
    if (a == 0) return 0;
    r = sub_001BA7C0(a);
    if (r < 0) return 0;
    return r;
}

/* 0x00084C70: set voice +0x34 to (v & 0x1FF) * 8. */
void a8c_VoiceSet34(int a, int v)
{
    sub_001B9650(a)->i34 = (v & 0x1FF) << 3;
}

/* 0x00084D30: clear the list at 0x3ED1B4 and its globals. */
void a8c_ClearList3ED1B4(void)
{
    a8c_g3ED1B0 = 0;
    sub_0003D860(a8c_list3ED1B4);
    a8c_g3ECCA8 = 0;
}

/* 0x00084ED0: free the block at 0x3ECCA8. */
void a8c_Free3ECCA8(void)
{
    void *p = a8c_g3ECCA8;
    a8c_g3ED1B0 = 0;
    sub_00053880(p);
    a8c_g3ECCA8 = 0;
}

/* 0x00085390: state handler i if the system is active, else 0. */
int a8c_Dispatch2E03A0(int i)
{
    if (!a8c_g3ED1CC) return 0;
    return a8c_tbl2E03A0[i]();
}

/* 0x00085DB0: free the block at 0x3ED1D0. */
void a8c_Free3ED1D0(void)
{
    void *p = a8c_g3ED1D0;
    a8c_g3ED1D4 = 0;
    sub_00053880(p);
    a8c_g3ED1D0 = 0;
}

/* 0x00086C30: nonzero if active and the current job is neither 0x862A0 nor 0x86460. */
int a8c_JobIsOther(void)
{
    if (!a8c_g3ED1F4) return 0;
    if (sub_00057E90() == (void *)sub_000862A0) return 0;
    return sub_00057E90() != (void *)sub_00086460;
}

/* 0x00087550: handler i of table 0x2E0438. */
void a8c_Dispatch2E0438(int i) { a8c_tbl2E0438[i](); }
/* 0x00087560: handler i of table 0x2E0450. */
void a8c_Dispatch2E0450(int i) { a8c_tbl2E0450[i](); }
/* 0x00087A40: current handler of table 0x2E0468. */
void a8c_Dispatch2E0468(void) { a8c_tbl2E0468[a8c_g3ED274](); }

/* 0x00087B60: set or clear bit 20 of the flags at 0x3ED258. */
void a8c_SetFlag100000(int on)
{
    if (on) a8c_g3ED258 |= 0x100000;
    else a8c_g3ED258 &= ~0x100000u;
}

/* 0x00084790: run 0x1B7100 on every slot sub-block. */
void a8c_SlotsApply7100(A8cSlotOwner *o, int a)
{
    uint32_t i;
    for (i = 0; i < o->count00; i++) sub_001B7100(o->slots04[i].sub24, a);
}
/* 0x00084890: run 0x1B72E0 on every slot sub-block. */
void a8c_SlotsApply72E0(A8cSlotOwner *o, int a)
{
    uint32_t i;
    for (i = 0; i < o->count00; i++) sub_001B72E0(o->slots04[i].sub24, a);
}
/* 0x000848D0: run 0x1B7300 on every slot sub-block. */
void a8c_SlotsApply7300(A8cSlotOwner *o, int a)
{
    uint32_t i;
    for (i = 0; i < o->count00; i++) sub_001B7300(o->slots04[i].sub24, a);
}

/* 0x00084850: push a new 0x10-byte node holding v onto slot i list. */
int32_t *a8c_SlotPushNode(A8cSlotOwner *o, int i, int v)
{
    int32_t *n = (int32_t *)a5b_AllocCur(0x10, 0, 0xF8);
    A8cSlot *s;
    n[0] = v;
    s = &o->slots04[i];
    n[1] = (int32_t)(intptr_t)s->list10;
    s->list10 = n;
    return n;
}

/* 0x00084C90: prepare voice a3 and start it with eight parameters. */
int a8c_VoiceStart(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
    sub_001A6820(sub_001B9650(a3));
    sub_001A6620(a0, a1, a2, a3, a4, a5, a6, a7);
    return 1;
}

/* 0x00085C00: run every command record through its kind handler. */
void a8c_RunCommands(void)
{
    A8cCmd *c;
    int i;
    if (a8c_g3ED1D4 == 0) return;
    c = (A8cCmd *)a8c_g3ED1D0;
    if (c == 0) return;
    for (i = 0; i < a8c_g3ED1D4->count08; i++, c++)
        a8c_tbl2E03A8[c->kind04](c);
}

/* 0x00086160: reset the demo-system globals. */
void a8c_ResetGlobals3ED1D8(void)
{
    a8c_g3ED208 = 0;
    a8c_g3ED1F4 = 0;
    a8c_g3ED1F0 = 0;
    a8c_g3ED1D8 = 0;
    a8c_handles3ED1DC[0] = -1;
    a8c_handles3ED1DC[1] = -1;
    a8c_handles3ED1DC[2] = -1;
    a8c_g3ED1E8 = 0;
    a8c_g3ED1EC = 0;
    a8c_g3ED20C = 0;
}

/* 0x00086250: 1 if the pair (a, b) is in the table at 0x3ED1F4. */
int a8c_PairExists(int a, int b)
{
    A8cPairTab *t = a8c_g3ED1F4;
    int i;
    if (t == 0) return 0;
    for (i = 0; i < t->count04; i++)
        if (a == t->pairs08[i].a && b == t->pairs08[i].b) return 1;
    return 0;
}

/* 0x00086850: release the three handles at 0x3ED1DC. */
void a8c_ReleaseHandles(void)
{
    int32_t *p;
    for (p = a8c_handles3ED1DC; p < a8c_handles3ED1DC + 3; p++) {
        if (*p != -1) {
            if (sub_000480F0(*p)) sub_00047B70(*p);
            *p = -1;
        }
    }
}

/* 0x00087A50: reset the demo player state. */
void a8c_DemoReset(void)
{
    a8c_g3ED254 = 0;
    a8c_g3ED258 = 0;
    a8c_g3ED25C = -1;
    a8c_g3ED260 = 0.0f;
    a8c_g3ED264 = 0.0f;
    a8c_g3ED268 = 0.0f;
    a8c_g3ED26C = 0;
}

/* 0x00087A90: start demo d with mode bit k. */
void a8c_DemoStart(A8cDemo *d, int k)
{
    a8c_g3ED254 = d;
    a8c_g3ED25C = k;
    a8c_g3ED260 = 0.0f;
    a8c_g3ED258 = 1 << k;
    a8c_g3ED264 = 0.0f;
    a8c_g3ED268 = d->f10;
    a8c_g3ED26C = 0;
}

/* 0x00087CF0: advance the timer; go to state 3 when 0x86230 reports done. */
void a8c_DemoStepWait(void)
{
    a8c_g3ED260 += a50_frameSeconds;
    if (!sub_00086230(a30_g41316C, a30_g413170, 0)) a8c_g3ED274 = 3;
}

/* 0x00087D30: after 1.5 s pick state 7 or 8 by mode. */
void a8c_DemoStepDelay(void)
{
    a8c_g3ED260 += a50_frameSeconds;
    if (a8c_g3ED260 >= 1.5f) {
        switch (a8c_g3ED25C) {
        case 0: a8c_g3ED274 = 7; break;
        case 1: a8c_g3ED274 = 8; break;
        }
    }
}

/* 0x00087E30: state 8 if 0x85590 accepts the demo, else 12 once 0xEDA90 is idle. */
void a8c_DemoStepCheck(void)
{
    if (sub_00085590(a8c_g3ED254)) { a8c_g3ED274 = 8; return; }
    if (!sub_000EDA90()) a8c_g3ED274 = 0xC;
}

/* 0x00087EE0: on completion, optionally run handler 1, then state 13. */
void a8c_DemoStepFinish(void)
{
    if (sub_00086230(a30_g41316C, a30_g413170, 1)) return;
    if (!(a8c_g3ED258 & 2) || a8c_g3ED254->b18 != 1) sub_00087030(1);
    a8c_g3ED274 = 0xD;
}

/* 0x00087F30: restore stats unless flagged, clear mode bits, state 14. */
void a8c_DemoStepRestore(void)
{
    if (!a8c_g3ED254->b18) {
        sub_000DE330(0);
        sub_000D2A50(&g_stats, 0);
    }
    a8c_g3ED258 &= ~3u;
    a8c_g3ED274 = 0xE;
}

/* 0x00087FF0: full demo player reset including the state. */
void a8c_DemoResetAll(void)
{
    a8c_g3ED274 = 0;
    a8c_g3ED254 = 0;
    a8c_g3ED258 = 0;
    a8c_g3ED25C = -1;
    a8c_g3ED260 = 0.0f;
    a8c_g3ED264 = 0.0f;
    a8c_g3ED268 = 0.0f;
    a8c_g3ED26C = 0;
}

/* 0x00088820: wait for 0xEE240, shut channel 2 down, and drain handle 15. */
void a8c_ShutdownAudio(void)
{
    sub_00033BF0(2, -1);
    while (!sub_000EE240()) ;
    sub_000ED600(2);
    sub_000ED560(2);
    sub_000ED4F0(2);
    sub_00047B70(0xF);
    while (sub_00047B90(0xF)) ;
}
