/* Area rbg: game functions in 0x000E0000..0x000EFFFF (rbg_2). Names inferred. */
#include "rbg.h"

/* 0x000E1350: spawn the object pair for slot idx (once): bind both component objects to their
   resources, register them with the scene, place them at pos, set their render flags and store
   them with value v in the slot. Hangs if a table entry is missing. */
void rbg_SpawnPair0E1350(RbgPairOwner *o, int idx, const float *pos, int v)
{
    RbgPair *p = &o->pairs534[idx];
    RbgRec150 *a, *b;

    if (p->a)
        return;
    if (o->pairs534[idx].b)
        return;
    a = &o->tblA524->recs08[idx];
    b = &o->tblB528->recs08[idx];
    if (!a || !b)
        for (;;)
            ;
    sub_00022380(a, o->resA52C, r3_ctx42C8E4);
    sub_00022380(b, o->resB530, r3_ctx42C8E4);
    sub_0001E9B0(r3_ctx42C8E4, a, 0xB, 5, 0x11);
    sub_0001E9B0(r3_ctx42C8E4, b, 0xB, 5, 0x11);
    sub_0001EBF0(a, 0);
    sub_0001EBF0(b, 0);
    sub_000F5D40(a->pos60, pos);
    sub_000F5D40(a->r20->v30, pos);
    a->r20->flagsE8 = 0x51001;
    a->r20->iEC = 0;
    b->r20->flagsE8 = 0x51001;
    b->r20->iEC = 0;
    p->a = a;
    o->pairs534[idx].b = b;
    o->pairs534[idx].v = v;
    sub_000F5D40(a->r20->pC4->v1E4, rbg_v3F1B44);
    sub_000F5D40(o->pairs534[idx].b->r20->pC4->v1E4, rbg_v3F1B44);
    o->active520 = 1;
}

/* Copy one image header into a layer (all zero without an image). */
static void rbg_SetLayer(RbgLayer *l, RbgImgHdr *h)
{
    if (h) {
        l->n00 = h->w0E;
        l->v04 = h->v08;
        l->w08 = h->w0C;
        l->data0C = h->data10;
    } else {
        l->n00 = 0;
        l->v04 = 0;
        l->w08 = 0;
        l->data0C = 0;
    }
}

/* 0x000E3820: fill the eight image layers of a page from its four fixed images, the selected
   set and three more images, and publish the selected set's value in rbg_g3F1B1C. */
void rbg_PageLayers0E3820(RbgPage *p)
{
    RbgImgHdr *h;

    rbg_SetLayer(&p->layers0C[0], p->srcAC[0]);
    rbg_SetLayer(&p->layers0C[1], p->srcAC[1]);
    rbg_SetLayer(&p->layers0C[2], p->srcAC[2]);
    rbg_SetLayer(&p->layers0C[3], p->srcAC[3]);
    p->i318 = 0;
    if (p->sel314 >= 0)
        h = p->setsBC[p->sel314].hdr;
    else
        h = 0;
    rbg_SetLayer(&p->layers0C[4], h);
    rbg_SetLayer(&p->layers0C[5], p->src2BC[0]);
    rbg_SetLayer(&p->layers0C[6], p->src2BC[1]);
    rbg_SetLayer(&p->layers0C[7], p->src2BC[2]);
    if (p->sel314 != -1)
        rbg_g3F1B1C = p->vals2C8[p->sel314];
}

/* 0x000E2E70: fire the next item of track 7 at pos, skipping the item skip. When the page has
   run to its end, mark all tracks done, close the message window, start the page sound once,
   wait for the stream and refill its 0x214 entries. Returns the item (0 when none).
   regargs: o=ESI skip=EAX pos=ECX */
void *rbg_PageNext0E2E70(RbgPage *o, void *skip, uint32_t pos)
{
    void *it;
    uint32_t lim;
    int n, i;

    do {
        it = r2b_TrackFire(o, 7, pos, 0);
        if (!it)
            return 0;
    } while (it == skip);
    if (o->pos40C >= o->end410) {
        lim = rbg_len317B64[o->id00] - 4000;
        sub_00048530(o->res2E8);
        sub_00048560(o->res2E8);
        o->done328 = 1;
        r2b_TrackMarkBefore(o, 1, lim, 0);
        r2b_TrackMarkBefore(o, 2, lim, 0);
        r2b_TrackMarkBefore(o, 5, lim, 0);
        r2b_TrackMarkBefore(o, 6, lim, 0);
        r2b_TrackMarkBefore(o, 7, lim, 0);
        sub_000E0FB0(0);
        if (o->snd2EC >= 0 && !o->started2F8) {
            sub_00054040();
            o->started2F8 = 1;
            sub_0019AB40(o->snd2EC);
            if (o->b2F4 & 1)
                sub_0019AAC0(o->snd2EC, 0);
            else
                sub_0019AAC0(o->snd2EC, 1);
            sub_00053F70(lim);
            sub_00054010();
        }
        while (sub_0019A900(o->strm2FC) != 2)
            sub_000580D0();
        sub_0019B800(o->strm2FC, 0x64);
        n = sub_0019ADE0(0x214);
        for (i = 0; i < n; i++)
            sub_0019AC20(o->strm2FC, i, sub_0019AD10(0x214, i));
    }
    return it;
}

/* 0x000E63A0: switch the current stage to mode (0..6); leaving mode 0 clears player flag 2,
   leaving mode 5 runs the stage exit. The stage's mode callback is told (new, old), then the
   new mode is entered: 0 sets player flag 2, 2 starts the camera, 4 starts the timeline,
   5 stops the effects, 6 resets the whole stage and plays the stage jingle. Returns the old
   mode. */
int rbg_StageMode0E63A0(int mode)
{
    int old = r2e_stage3F0758.mode324;
    void *h;
    int i;

    if (old == mode)
        return old;
    r2e_stage3F0758.mode324 = mode;
    if (old != 0) {
        if (old == 5)
            sub_000E3390(&r2e_stage3F0758);
    } else {
        PlayerObj_ClearFlags(&g_stats, 2, 0);
        sub_0019BEB0(3);
    }
    h = sub_0001D080(((RbgScene *)r3_ctx42C8E4)->recs1E8, 3, sub_000E2420(&r2e_stage3F0758));
    if (!h || !rbg_modeFn317C7C[r2e_stage3F0758.id00])
        for (;;)
            ;
    rbg_modeFn317C7C[r2e_stage3F0758.id00](h, mode, old);
    switch (r2e_stage3F0758.mode324) {
    case 2:
        sub_00019000(ae0_obj3E1270, 2);
        sub_0001AB00(ae0_obj3E1270, 2, 3, rbg_i317BB8[r2e_stage3F0758.id00], 0);
        break;
    case 4:
        r2e_stage3F0758.len2F0 = rbg_len317B64[r2e_stage3F0758.id00];
        sub_000E5C30(&r2e_stage3F0758);
        r2e_stage3F0758.hidden310 = 0;
        r2e_stage3F0758.done328 = 0;
        r2e_stage3F0758.strm2FC = -1;
        break;
    case 5:
        for (i = 0; i < 8; i++) {
            if (r2e_stage3F0758.fx430[i].fx14 >= 0 && r2e_stage3F0758.fx430[i].on00)
                sub_000E98E0(r2e_stage3F0758.fx430[i].fx14, 0);
            r2e_stage3F0758.fx430[i].on00 = 0;
        }
        break;
    case 0:
        PlayerObj_SetFlags(&g_stats, 2, 0);
        sub_0019BE90(3);
        break;
    case 6:
        sub_0019BE90(0x10000);
        if (aa0_enabled413142)
            sub_0005EB10(0, 0x24);
        sub_000E3BA0(&r2e_stage3F0758);
        if (r2e_stage3F0758.rec31C >= 0) {
            sub_00048330(r2e_stage3F0758.rec31C, 0x64);
            r2e_stage3F0758.rec31C = -1;
        }
        if (r2e_stage3F0758.strm2FC >= 0)
            sub_0019AA00(r2e_stage3F0758.strm2FC, 0x64);
        PlayerObj_SetFlags(&g_stats, 2, 0);
        sub_000CFF90(&g_stats, 1, 36000.0f);
        sub_000CEF00();
        sub_0019BE90(3);
        sub_000E0E40(0);
        sub_000253D0(0, 0);
        sub_000E8690(0, 0);
        sub_000E8920(0, 0);
        sub_000E89F0(0, 0);
        sub_000E8A50(0, 0);
        for (i = 0; i < 8; i++) {
            if (r2e_stage3F0758.fx430[i].fx14 >= 0 && r2e_stage3F0758.fx430[i].on00)
                sub_000E98E0(r2e_stage3F0758.fx430[i].fx14, 0);
            r2e_stage3F0758.fx430[i].on00 = 0;
        }
        for (i = 0; i < 4; i++)
            sub_000E16E0(&r2e_stage3F0758, i, 0.25f);
        sub_000E19F0(&r2e_stage3F0758, 0.25f);
        sub_000C85C0();
        sub_000A8B80();
        switch (r2e_stage3F0758.id00) {
        case 0: sub_00049A40(0, 0x10); break;
        case 1: sub_00049A40(0, 0x11); break;
        case 2: sub_00049A40(0, 0x12); break;
        case 3: sub_00049A40(0, 0x13); break;
        case 4: sub_00049A40(0, 0x14); break;
        case 6: sub_00049A40(0, 0x15); break;
        }
        break;
    }
    return old;
}
