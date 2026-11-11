/* Area r2c, group 1: effect, fader and key-list helpers (0x000E8530..0x000EDCA9). Names inferred. */
#include "r2c.h"

/* 0x000E8530: clear every effect record, every effect slot and the four fader
   blocks. */
void r2c_FxResetAll(void)
{
    int i;
    for (i = 0; i < 32; i++)
        r2c_fx3F1B5C[i].state04 = 0;
    for (i = 0; i < 16; i++)
        r2_slots3F4D10[i].flags = 0;
    r2c_fadeA3F43E0.state = 0;
    r2c_fadeA3F43E0.t04 = 0;
    r2c_fadeA3F43E0.t08 = 0;
    r2c_fadeA3F43E0.t0C = 0;
    r2c_fadeB3F47B8.state = 0;
    r2c_fadeB3F47B8.t04 = 0;
    r2c_fadeB3F47B8.t08 = 0;
    r2c_fadeB3F47B8.t0C = 0;
    r2c_fadeC3F4874.state = 0;
    r2c_fadeC3F4874.t04 = 0;
    r2c_fadeC3F4874.t08 = 0;
    r2c_fadeC3F4874.t0C = 0;
    r2c_fadeD3F4B1C.state = 0;
    r2c_fadeD3F4B1C.t04 = 0;
    r2c_fadeD3F4B1C.t08 = 0;
    r2c_fadeD3F4B1C.t0C = 0;
    aec_3F49D0 = 0;
    aec_3F49D4 = 0;
}

/* 0x000E89F0: switch fader C on (1, remembering v) or off (0); restarts it
   only from the matching resting states. */
void r2c_FaderC(int on, int v)
{
    switch (on) {
    case 0:
        switch (r2c_fadeC3F4874.state) {
        case 1:
        case 3:
            r2c_fadeC3F4874.state = 2;
            r2c_fadeC3F4874.t04 = 0;
            r2c_fadeC3F4874.t10 = 0;
            break;
        }
        break;
    case 1:
        r2c_fadeC3F4874.v1C = v;
        switch (r2c_fadeC3F4874.state) {
        case 0:
        case 2:
            r2c_fadeC3F4874.state = 1;
            r2c_fadeC3F4874.t04 = 0;
            r2c_fadeC3F4874.t10 = 0;
            break;
        }
        break;
    }
}

/* 0x000E98E0: start effect record idx in the given mode (mode below 2 means
   state 5, otherwise state 4, which also allocates a slot). Returns idx or -1
   when the record is not in use. */
int r2c_FxStart(unsigned idx, unsigned mode)
{
    R2cFx *f;
    int state;
    if (idx > 0x20)
        for (;;) ;
    f = &r2c_fx3F1B5C[idx];
    if (!(f->flags & 1))
        return -1;
    f->mode08 = mode;
    state = (mode < 2) ? 5 : 4;
    f->state04 = state;
    f->t0C = 0;
    f->v24 = f->vC4;
    if (state == 4)
        r2_SlotAlloc(f->a2C, f->a30);
    return idx;
}

/* 0x000E9950: with on = 0 set flag 0x3F49D0; otherwise wait until the stage
   clock reaches n ticks, then set flag 0x3F49D4 and remember n. */
void r2c_WaitTicks(int on, unsigned n)
{
    unsigned t;
    if (!on) {
        aec_3F49D0 = 1;
        return;
    }
    do {
        t = (g_acb_3F57BC == 0x2710) ? r2c_clock3F4AB8->ticks18 : 0;
    } while (t < n);
    aec_3F49D4 = 1;
    r2_g3F49DC = n;
}

/* 0x000E9C60: when the gauge is active and full and 0x0E3380 reports 2, play
   the full-gauge cue (0x0E63A0(4), 0x0E8920(1, 0), sound 0x3A7). */
void r2c_GaugeFullCheck(R2cGauge *g)
{
    if (g && g->on408 && g->cur40C >= g->max410 && sub_000E3380() == 2) {
        sub_000E63A0(4);
        sub_000E8920(1, 0);
        sub_00048AF0(0x3A7);
    }
}

/* 0x000EAE50: create part (c+0x10, +0x14, +0x18) and, with a holder, store
   its handle in the holder's slot c->vC. */
void r2c_LinkPart(R2cHolder *h, const R2cCmd *c)
{
    if (!c)
        return;
    if (h)
        h->parts3B0[c->vC] = sub_000E3F20(c->v10, c->v14, c->v18);
    else
        sub_000E3F20(c->v10, c->v14, c->v18);
}

/* 0x000EDA50: 1 when the key list holds a key of kind 2..5, or of kind 8 with
   a sub-id below 10. */
int r2c_ListHasActive(void)
{
    R2cNode *n;
    for (n = r2_list3F5DC0.head; n; n = n->next) {
        R2cKey *k = (R2cKey *)n->data;
        int sub = k->sub;
        int kind = k->kind;
        if (kind >= 2) {
            if (kind <= 5)
                return 1;
            if (kind == 8 && sub < 10)
                return 1;
        }
    }
    return 0;
}

/* 0x000EDB90: continue the r2c_FindFirst iteration. */
void *r2c_FindNext(void)
{
    R2cNode *n = r2_tail3F60E4;
    if (!n)
        return 0;
    do {
        R2cKey *k = (R2cKey *)n->data;
        if (r2c_filter3189CC(k->kind, k->sub)) {
            r2_tail3F60E4 = n->next;
            return n->data;
        }
        n = n->next;
    } while (n);
    r2_tail3F60E4 = n;
    return 0;
}

/* 0x000EDC20: find keys of a kind (and sub-id unless sub < 0) by index; with
   kind >= 0 start a new search, with kind < 0 continue the last one. */
void *r2c_FindKey(int kind, int sub)
{
    int n = r2_list3F5DC0.count;
    int i;
    if (kind >= 0) {
        r2c_kind3189D4 = kind;
        r2c_sub3189D8 = sub;
        i = -1;
    } else {
        i = r2c_iter3189D0;
        if (i < 0 || r2c_kind3189D4 < 0)
            return 0;
        if (i >= n)
            return 0;
    }
    for (r2c_iter3189D0 = i + 1; r2c_iter3189D0 < r2_list3F5DC0.count; r2c_iter3189D0++) {
        R2cKey *k = (R2cKey *)sub_0003D960(&r2_list3F5DC0, r2c_iter3189D0)->data;
        if (k->kind == r2c_kind3189D4 && (r2c_sub3189D8 < 0 || k->sub == r2c_sub3189D8))
            return k;
    }
    return 0;
}
