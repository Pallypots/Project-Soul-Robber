/* Area r1b, group 4: packet init, steppers, track records 0x00014B60..0x0001B0A0. Names inferred. */
#include "r1b.h"

/* 0x00014B60: set up the two packet buffers and the fixed packet. */
void r1b_PktInit(void)
{
    r1b_PktOp(&r1b_pkts37B4AC[0], 0x70003BF0);
    r1b_PktOp(&r1b_pkts37B4AC[1], 0x70003DF0);
    r1b_PktOp(&r1b_pkt37B540, 0x70003FF0);
    r1b_dev37B4A4 = sub_001A1FD0(2);
    r1b_PktOp(&r1b_pkt37B540);
    r1b_PktOp(&r1b_pkt37B540, 0, 0, 0);
    sub_000AD090(&r1b_pkt37B540);
    r1b_pktIdx37B4A0 = 0;
    r1b_dma37B390 = 0;
    r1b_g432680 = 0;
    r1b_g432684 = 0;
    r1b_g432688 = 0;
}

/* 0x00014E30: start a stepper on animation entry idx. */
void r1b_StepperSet(R1bStepper *s, int idx, float a, float b, int arg)
{
    s->f00 = a;
    s->cur = idx;
    s->time = 0;
    s->f04 = b;
    s->u10.length = s->set->entries[idx]->length;
    s->i28 = 0;
    s->flags &= ~1u;
    s->arg18 = arg;
}

/* 0x000150E0: step a stepper until it has advanced n times or finishes,
   then restore its flags. */
void r1b_StepperRun(R1bStepper *s, int n)
{
    uint32_t saved;
    s->time = 0;
    s->u10.length = s->set->entries[s->cur]->length;
    saved = s->flags;
    s->i28 = 0;
    s->flags = (saved & 0xFFFFFF76) | 6;
    if (n != 0) {
        do {
            s->u10.t10 = 0.0f;
            sub_00014E80(s);
            if ((int8_t)s->flags < 0) break;
        } while (s->time != n);
    }
    s->flags = saved;
}

/* 0x00017D50: initialise a track record. */
void r1b_TrackInit(R1bTrack *t, int32_t *start, int a, int b, int c, int d,
                   int e, int f, int g, int h)
{
    t->v0C = a;
    t->v10 = b;
    t->v14 = c;
    t->v18 = d;
    t->v1C = e;
    t->v20 = f;
    t->v24 = g;
    t->v28 = h;
    t->items = 0;
    t->count = 0;
    t->start = start;
    t->begin = start;
    t->cur = start;
    t->t34 = 0.0f;
    t->w2C = 0;
    t->w2E = 0;
    t->w30 = 0;
}

/* 0x00018150: release a track record's entries and rewind it. */
void r1b_TrackReset(R1bTrack *t)
{
    uint32_t i;
    if (t->items) {
        for (i = 0; i < t->count; i++) t->items[i].flags = 0;
        t->items = 0;
    }
    t->count = 0;
    t->w2C = 0;
    t->w2E = 0;
    t->w30 = 0;
    t->begin = t->start;
    t->cur = t->start;
    t->t34 = 0.0f;
}

/* 0x00018B10: free the four slot buffers and the extra buffer of a holder. */
void r1b_SlotsFree(R1bSlots *h)
{
    int i;
    if (h == 0) return;
    for (i = 0; i < 4; i++) {
        if (h->slot[i].buf) {
            sub_00053880(h->slot[i].buf);
            h->slot[i].buf = 0;
        }
        h->slot[i].a = 0;
        h->slot[i].b = 0;
    }
    if (h->extra) {
        sub_00053880(h->extra);
        h->extra = 0;
    }
}

/* 0x00018EF0: interpolate three vectors and a scalar between two poses. */
void r1b_PoseLerp(R1bPose *dst, R1bPose *from, R1bPose *to, float t)
{
    sub_001ADCD0(dst->v10, to->v10, from->v10, t);
    sub_001ADCD0(dst->v20, to->v20, from->v20, t);
    sub_001ADCD0(dst->v30, to->v30, from->v30, t);
    dst->f40 = (to->f40 - from->f40) * t + from->f40;
}

/* 0x00019370: start a global fade of the given mode and duration. */
void r1b_FadeStart(int mode, float duration)
{
    if (a1b_i37C050 == 7) {
        a1b_i37C05C = a1b_i37C05C < 4 ? a1b_i37C05C + 1 : 4;
    } else {
        a1b_i37C05C = 0;
    }
    a1b_f37C054 = duration;
    a1b_i37C050 = mode;
    a1b_f37C058 = 0.0f;
}

/* 0x0001A7A0: refresh an object's matrix from its source. */
void r1b_ObjSyncMatrix(R1bXObj *o)
{
    if (o->src->kind <= 1u) {
        sub_001ADA40(o->mat, o->src->mat);
        o->fF0 = o->src->f60;
        return;
    }
    sub_000191F0(o->mat, o->m2A0, o->i50);
}

/* 0x0001A9B0: aim an object at the player, or reset its value when it has no target. */
void r1b_ObjAim(R1bXObj *o)
{
    if (r1b_g42C8F8 == 0) return;
    if (o->target >= 0) {
        sub_0001A710(o, (uint8_t *)g_playerObj + 0x60);
        return;
    }
    o->f1E0 = o->fF0;
}

/* 0x0001AEC0: in chapters 3..5 (outside the special mode) set events 0xF9..0xFC. */
void r1b_Act_1AEC0(void)
{
    if (a30_g41316C != 0) return;
    if (a30_g413170 < 3 || a30_g413170 > 5) return;
    sub_000D9AB0(0xF9);
    sub_000D9AB0(0xFA);
    sub_000D9AB0(0xFB);
    sub_000D9AB0(0xFC);
    sub_00048AF0(1);
}

/* 0x0001AF70: set event 0xF5 and give two of each of items 8..11. */
void r1b_Act_1AF70(void)
{
    sub_000D9AB0(0xF5);
    Stats_Set(&g_stats, 8, 2);
    Stats_Set(&g_stats, 9, 2);
    Stats_Set(&g_stats, 10, 2);
    Stats_Set(&g_stats, 11, 2);
    sub_00048AF0(1);
}

/* 0x0001AFC0: in chapters 3..5 set the two event words at 0x00413408 to all ones. */
void r1b_Act_1AFC0(void)
{
    if (a30_g41316C != 0) return;
    if (a30_g413170 < 3 || a30_g413170 > 5) return;
    r1b_ev413408[0] = -1;
    r1b_ev413408[1] = -1;
    sub_00048AF0(1);
}

/* 0x0001B0A0: in chapters 3..5 set the four event words at 0x00413410 to all ones. */
void r1b_Act_1B0A0(void)
{
    if (a30_g41316C != 0) return;
    if (a30_g413170 < 3 || a30_g413170 > 5) return;
    r1b_ev413408[2] = -1;
    r1b_ev413408[3] = -1;
    r1b_ev413408[4] = -1;
    r1b_ev413408[5] = -1;
    sub_00048AF0(1);
}

/* 0x00018620: apply layout idx (default target 0x0037B560) to a menu object. */
void r1b_ApplyLayout(R1bMenu *m, int idx)
{
    const R1bLayout *l = &r1b_layouts2804E0[idx];
    if (m == 0) m = &a1b_obj37B560;
    a60_RectSet0(m->rect, l->x0, l->y0);
    a60_RectSet1(m->rect, l->x1, l->y1);
    m->rect->w1A = l->w18;
    m->rect->w18 = l->w1C;
    m->rect->d10 = l->d10;
    m->rect->d14 = l->d14;
}
