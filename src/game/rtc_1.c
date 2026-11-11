/* Area rtc, group 1: tail-call wrappers in 0x0001C4F0..0x0008FAC0. Names inferred. */
#include "rtc.h"

/* 0x0001C4F0: run the handler for an actor in state 12 or 13; the state-13
   handler takes its arguments the other way round. */
void rtc_ActorStateHandler(void *ctx, RtcActor *a)
{
    switch (a->stateD0) {
    case 12:
        sub_0001BEE0(ctx, a);
        break;
    case 13:
        sub_0001C160(a, ctx);
        break;
    }
}

/* 0x000385B0: draw a glyph with a colour given as an index into the colour
   table at 0x002C4468 (bit 7 of the index is ignored). */
void *rtc_DrawGlyphIndexed(void *ctx, int x, int y, int z, void *size, int colour,
                           float sx, float sy, int ch)
{
    if ((int8_t)colour < 0)
        colour &= ~0x80;
    return sub_000380A0(ctx, x, y, z, size, rtc_colours2C4468[colour], sx, sy, ch);
}

/* 0x0003FBD0: draw an item's text unless it has none or is of kind 5;
   returns ctx unchanged when nothing is drawn. */
void *rtc_ItemTextDraw(void *ctx, RtcObj *item)
{
    if (item->p8 && item->kind4 != 5)
        return r6d_TextDraw(ctx, item->p8);
    return ctx;
}

/* 0x0003FBF0: as 0x0003FBD0 with an alpha value. */
void *rtc_ItemTextDrawAlpha(void *ctx, RtcObj *item, int alpha)
{
    if (item->p8 && item->kind4 != 5)
        return r6d_TextDrawAlpha(ctx, item->p8, alpha);
    return ctx;
}

/* 0x000487C0: store a scale clamped to at most 1.0, then reapply the
   current level through 0x000486F0. */
void rtc_SetScale(float scale)
{
    if (scale > 1.0f)
        scale = 1.0f;
    rtc_scale3DFEDC = scale;
    sub_000486F0(rtc_level3DFED8);
}

/* 0x00053820: allocate from the heap of a memory slot (slot 10 uses the
   high allocator on heap 8; slots 9 and above otherwise hang). */
void *a50_Alloc(int slot, int size, int a, int b)
{
    if (slot != 10) {
        if (slot >= 9)
            for (;;) ;
        return sub_00047390(a50_slotHeap[slot], size, a, b);
    }
    return sub_00047450(a50_slotHeap[8], size, a, b);
}

/* 0x00053850: as 0x00053820 but always from the high end of the heap. */
void *a50_AllocHigh(int slot, int size, int a, int b)
{
    if (slot == 10)
        return sub_00047450(a50_slotHeap[8], size, a, b);
    if (slot >= 9)
        for (;;) ;
    return sub_00047450(a50_slotHeap[slot], size, a, b);
}

/* 0x0008BD80: allocate size bytes in slot 10 (kind 5) or slot 4 (others);
   0 when p is null. */
void *rtc_AllocForKind(int kind, void *p, int size)
{
    if (!p)
        return 0;
    return a6b_HeapAlloc(kind == 5 ? 10 : 4, p, size);
}

/* 0x0008D1B0: release the process reference stored at +0x0C. */
void rtc_ReleaseRefC(RtcObj *o)
{
    sub_00089420(o->iC);
}

/* 0x0008FAC0: field +8 of table entry 0 of the object's table (0 without
   a table). */
int rtc_TableEntry0Get8(RtcObj *o)
{
    if (o->p8)
        return r4b_Get8(a12_Table_Get(o->p8, 0));
    return r4b_Get8(0);
}

/* 0x0001EF00: copy a vector into the texture record of a packet whose flag
   0x10 is set (hangs if the record's handler is not 0x0001ED90). */
void rtc_PktTexSetVec(RtcPkt *p, const float *v)
{
    RtcPktInfo *info;
    RtcPktTex *t;
    if (!p || !(p->flagsC & 0x10))
        return;
    info = p->info28;
    if (!info)
        return;
    t = info->texA8;
    if (!t)
        return;
    if (t->fn8 != (void *)r1c_PktTexBase)
        for (;;) ;
    sub_000F5D40(t->v1C, v);
}

/* 0x00039FE0: load matrix 0 (and set its w to 1.0) or matrix 1 of the pair
   at 0x003DCE70 from src. */
void rtc_LoadViewMatrix(int which, const void *src)
{
    switch (which) {
    case 0:
        sub_001ADA40(rtc_mtx3DCE70[0], src);
        rtc_mtx3DCE70[0][15] = 1.0f;
        break;
    case 1:
        sub_001ADA40(rtc_mtx3DCE70[1], src);
        break;
    }
}

/* 0x00049490: run 0x00048D70 directly (direct != 0) or start it as a job
   with argument 0, recording which in 0x003DFFF8. */
void rtc_StartWorker(int direct)
{
    if (direct) {
        a4c_g3DFFF8 = 0;
        sub_00048D70(1);
        return;
    }
    a4c_g3DFFF8 = 1;
    sub_00058540(sub_00048D70, 0);
}

/* 0x00083160: pass the source's value at +0x14 to a model (kind 9) or a
   mesh (kind 1). */
void rtc_ApplyValueToModel(RtcObj *src, uint8_t *m)
{
    switch (*(int32_t *)(m + 0x8C)) {
    case 1:
        r4b_MeshSetC8(m, src->i14);
        break;
    case 9:
        r4_ModelSetPartValue(m, src->i14);
        break;
    }
}

/* 0x00084CE0: find a texture by file name (extension stripped); when not
   found, load it with flag 0x40 and return its group texture. */
int rtc_TexFindOrLoad(const char *name)
{
    const char *base = sub_000133B0(name);
    int r;
    void *t;
    if (!base)
        r = -1;
    else {
        r = r4_TexFindNamed(base);
        if (r >= 0)
            return r;
    }
    t = sub_00037570(name, 0x40);
    if (t)
        return r4b_TexWithGroup(t);
    return r;
}

/* 0x0008E1C0: create the actor's ramp on first use, otherwise update it. */
void rtc_RampCreateOrSet(RtcActor *a, int p1, int p2, int p3, int p4)
{
    if (!a->ramp120) {
        a->ramp120 = sub_000904F0(p1, p2, p3, p4);
        return;
    }
    r6e_RampSet(a->ramp120, p1, p2, p3, p4);
}

/* 0x00033C20: free the 16 slots of an owner (releasing the emitter set of
   slots whose first word is 0 and freeing their chains), then pass the
   enclosing object (owner - 0x10) to 0x00036B10. */
void rtc_SlotsFreeAll(RtcSlotOwner *o)
{
    RtcSlot **pp = o->slots;
    int n = 16;
    do {
        RtcSlot *s = *pp;
        if (s) {
            if (s->i0 == 0) {
                r4b_EmitSetReleaseAll(s->emit20);
                r4_EmitSetFlag8(s->emit20);
            }
            if (s->chain10)
                r1c_NodeFreeChain(s->chain10);
            r1d_NodeFree(s);
        }
        pp++;
    } while (--n);
    sub_00036B10((uint8_t *)o - 0x10);
}

/* 0x00052900: select video rate mode and recompute the frame timing
   globals (units per frame at 60 Hz scale, seconds per frame, frames per
   second). */
void rtc_SetRateMode(int mode)
{
    float t = 1.0f / a50_rateHz[mode];
    float sec;
    g_videoRateMode = mode;
    a50_frameUnits = t * a50_timeScale * 60.0f;
    sec = t * a50_timeScale;
    a50_frameSeconds = sec;
    rfl_fps42C964 = 1.0f / sec;
    r4b_SetFactor(a50_frameUnits);
}

/* 0x00052970: set the time scale and recompute the frame timing globals. */
void rtc_SetTimeScale(float scale)
{
    float t = 1.0f / a50_rateHz[g_videoRateMode];
    float sec;
    a50_frameUnits = t * scale * 60.0f;
    sec = t * scale;
    a50_timeScale = scale;
    a50_frameSeconds = sec;
    rfl_fps42C964 = 1.0f / sec;
    r4b_SetFactor(a50_frameUnits);
}

/* 0x0005A9C0: mode 1 handles b in place (0x0003E410 when 0x0003F770 is
   false and flag 0x20 of its +0x28 entry is set) and returns a; other modes
   go to 0x0003F780. */
void *rtc_ModeDispatch(void *a, RtcEntry *b, int mode)
{
    switch (mode) {
    case 0:
        return sub_0003F780(a, b, 0);
    case 1:
        if (!sub_0003F770(b) && (sub_0004ECE0(b->i28) & 0x20))
            sub_0003E410(b, b->i4);
        return a;
    }
    return sub_0003F780(a, b, mode);
}

/* 0x000893C0: shut down a task owner: reset sound channels, flush and free
   its task lists, then release it through 0x0008FB80. */
void rtc_TaskOwnerShutdown(RtcTaskOwner *o)
{
    sub_00018610();
    a5b_ChansReset();
    if (o->list20)
        r6e_TaskSendAll(o->list20, o);
    sub_0008B400(o->list1C);
    o->list1C = 0;
    r6e_TaskFreeList(o->list20);
    o->list20 = 0;
    r6b_ReturnZero(0, 0);
    sub_0008FB80(o->ref48);
}

/* 0x0002E280: in state 10000 draw x through 0x0002CF80 (modes 0..2) or as
   a 528x464 half-black panel centred on the screen, then finish with
   0x00079480; other states return x unchanged. */
void *rtc_DrawPanelOrText(void *x)
{
    if (r1c_state3816D0 != 10000)
        return x;
    if (r1c_mode381400 < 3)
        return sub_00079480(sub_0002CF80(x));
    return sub_00079480(sub_000720D0(x, -264.0f, -232.0f, 528.0f, 464.0f, 0,
                                     0x80000000u, 0x80000000u, 0x80000000u, 0x80000000u));
}

/* 0x0004BDA0: leave a stage: place camera markers, refresh the player
   stats, post event 0x103, clear the scene sound when a script is running,
   run the script until its variable leaves 1, then call 0x000DE9E0(0). */
void rtc_StageLeave(int unused)
{
    r6c_CamMarkersPlace();
    sub_00085DE0();
    sub_000D1D00(&g_stats);
    sub_000D1930(&rtc_stats);
    sub_0019BEB0(0x103);
    if (sub_000DFC00()) {
        a5b_Clear3E6040();
        sub_0005C430(rtc_scene42C8E4->snd1F0);
    }
    while (af0_GetVar3F0738() == 1) {
        r2b_ScriptTick();
        sub_000586E0(0);
    }
    sub_000DE9E0(0);
}

/* 0x0004EA40: set up group handlers 0, 1 and -1 for x, release groups 0
   and -1, apply the volume option, clear the state block at 0x003E0000
   and two counters, then call 0x000325A0(0). */
void rtc_GroupsInit(void *x)
{
    sub_00038960();
    a1a_GroupAdd(x, 0, 1, sub_0004D3E0, 8, 0x4000);
    a1a_GroupAdd(x, 1, 1, sub_0004E9E0, 8, 0x4000);
    a1a_GroupAdd(x, -1, 4, sub_0004E890, 8, 0x4000);
    a1a_GroupReleaseOne(x, 0);
    a1a_GroupReleaseOne(x, -1);
    sub_00048620(r4c_opt413148 * 0x7FF);
    {
        int i;
        for (i = 0; i < 0x14C; i++)
            a4c_state3E0000[i] = 0;
    }
    rtc_count3E059C = 0;
    rtc_count3E0540 = 0;
    sub_000325A0(0);
}

/* 0x00088B80: wait for the stage to unload: wait for 0x000EE240, release
   key pair (0x0041316C, 0x00413170), let streams 10 settle (state 2, then
   idle), drain the stream release queue and jump to event 1. */
void rtc_StageUnloadWait(int unused)
{
    int k1, k2;
    sub_000EE0C0();
    while (!sub_000EE240())
        ;
    k1 = a30_g41316C;
    k2 = a30_g413170;
    r1_KeyReleaseD(k1, k2);
    while (r1_KeyQuery2D(k1, k2))
        ;
    r1e_StagePlace(10);
    if (sub_00047B10(10) != 2) {
        do
            r1e_StagePlace(10);
        while (sub_00047B10(10) != 2);
    }
    sub_00047B30(10);
    if (sub_00047B50(10)) {
        do
            sub_00047B30(10);
        while (sub_00047B50(10));
    }
    while (r6c_StreamReleaseStep())
        ;
    r6c_EvJump(1);
}

/* 0x00079E00: initialise a text box: colours and scale, sizes, an id from
   0x0001CFD0, its layout header at +0x40 (+0x0C = 0x30), and a cleared
   0x268-byte work block from slot 0x10. */
void rtc_TextBoxInit(RtcTextBox *t)
{
    t->f1BC = 0.0f;
    t->f1C0 = 1000.0f;
    t->i1B8 = 0;
    t->rgb1C4[0] = 255.0f;
    t->rgb1C4[1] = 255.0f;
    t->rgb1C4[2] = 255.0f;
    t->v1D0[2] = 0;
    t->v1D0[1] = 0;
    t->v1D0[0] = 0;
    t->i1DC = 0x80;
    t->i1E0 = -11;
    t->id1E8 = sub_0001CFD0();
    t->f1E4 = 10.0f;
    t->hdr40->i8 = 0;
    t->hdr40->i4 = 0;
    t->hdr40->i0 = 0;
    t->hdr40->iC = 0x30;
    t->v1EC[0] = 0;
    t->v1EC[1] = 0;
    t->v1EC[2] = 0;
    t->v1EC[3] = 0;
    t->v1EC[4] = 0;
    t->v1EC[5] = 0;
    t->work204 = a5b_AllocCur(0x10, 0, 0x268);
    a3c_Clear16(t->work204);
}

/* 0x00094F10: when rumble is enabled, trigger effect 0x13 or 0x14 by the
   player's ground distance and height difference to the object (a wider
   0x13 window when the pair value is 8). */
void rtc_ProximityShock(RtcProp *o)
{
    float d, dy;
    if (!aa0_enabled413142)
        return;
    d = r4_DistanceXZ(rtc_playerObj->v60, o->v70);
    dy = o->v70[1] + o->f2C - rtc_playerObj->v60[1];
    if (r2b_PairB(0) == 8) {
        if (d >= 0.0f && 80.0f >= d && 80.0f >= dy)
            sub_000AA2E0(0x13);
        return;
    }
    if (d >= -40.0f && 20.0f >= d && 60.0f >= dy) {
        sub_000AA2E0(0x14);
        return;
    }
    if (d >= -60.0f && 40.0f >= d && 250.0f >= dy)
        sub_000AA2E0(0x13);
}
