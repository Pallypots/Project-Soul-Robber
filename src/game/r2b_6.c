/* Area r2b, group 6: script driver helpers (0x000E0000..0x000E0FFF). Names inferred. */
#include "r2b.h"

/* 0x000E01D0: reset record idx of table 0x3F0740 and, when b is set, store the item
   built from (a, b, c, 30, -1) in it. */
void r2b_TableSet(void *tbl, int b, int c, int idx)
{
    uint8_t *t = (uint8_t *)g_acb_table;
    sub_0003FC10(t + idx * 32);
    if (b != -1)
        sub_0003FCB0((uint8_t *)g_acb_table + idx * 32, sub_0003FA70(tbl, b, c, 30.0f, -1.0f));
}

/* 0x000E0570: per-frame script work in driver state 3: run the threads, the stage
   handlers of mode 1 and the step handler. */
void r2b_ScriptTick(void)
{
    if (af0_var3F0734 != 3)
        return;
    r2b_RunThreads();
    if (r2b_GetMode0() == 1) {
        if (r2b_StageFlag200())
            sub_000D75E0();
        else
            sub_000D7C10();
    }
    if (r2b_GetModeA8() == 1)
        sub_000D8820();
}

/* 0x000E0790: map kind 0..6 to 6, 3, 5, 4, 7, 8, 0xB; -1 otherwise. */
int r2b_MapKind(int k)
{
    switch (k) {
    case 0: return 6;
    case 1: return 3;
    case 2: return 5;
    case 3: return 4;
    case 4: return 7;
    case 5: return 8;
    case 6: return 0xB;
    }
    return -1;
}

/* 0x000E0870: format the name of kind into buf (256 bytes); kinds 1, 2, 5, 6 and 7
   print zeros for b and c. */
char *r2b_FormatName(char *buf, int kind, int a, int b, int c)
{
    if (kind == 1 || kind == 2 || kind == 5 || kind == 6 || kind == 7) {
        c = 0;
        b = 0;
    }
    a6b_Printf3(buf, 0x100, r2b_fmt27772C, r2b_str317CBC, r2b_names317CD0[kind], a, b, c);
    return buf;
}

/* 0x000E08D0: make sure resource 0xD9 is loaded (unless loading is busy); returns the
   loaded flag kept at +8. */
int r2b_LoadD9(R2bLoader *o)
{
    if (!o)
        for (;;) ;
    o->loaded08 = 0;
    if (sub_0004F4D0())
        return 0;
    if (!sub_0004F6D0(0xD9)) {
        sub_0004FA70(0xD9, sub_00053820(4, sub_0004F680(0xD9), 0, 0));
        sub_0004F4E0();
        o->loaded08 = 1;
    }
    return o->loaded08;
}

/* 0x000E0B70: mark every item of track idx whose end (pos + len + base) lies before lim. */
void r2b_TrackMarkBefore(R2bTracks *o, int idx, uint32_t lim, uint32_t base)
{
    R2bTrack *t;
    uint8_t *p;
    uint32_t i;
    if (!o)
        for (;;) ;
    t = &o->tr0C[idx];
    p = t->items0C;
    for (i = 0; i < t->count04; i++) {
        R2bTimed *e = (R2bTimed *)p;
        e->on06 = e->pos00 + e->len04 + base < lim;
        p += t->stride08;
    }
}

/* 0x000E0BD0: first unmarked item of track idx whose end has been reached by pos; it
   is marked and returned (0 when none). */
R2bTimed *r2b_TrackFire(R2bTracks *o, int idx, uint32_t pos, uint32_t base)
{
    R2bTrack *t;
    uint8_t *p;
    uint32_t i;
    if (!o)
        for (;;) ;
    t = &o->tr0C[idx];
    p = t->items0C;
    for (i = 0; i < t->count04; i++) {
        R2bTimed *e = (R2bTimed *)p;
        if (pos >= e->pos00 + e->len04 + base && !e->on06) {
            e->on06 = 1;
            return e;
        }
        p += t->stride08;
    }
    return 0;
}

/* 0x000E0C30: last item of track idx starting at or before pos (the first item when
   none does). */
R2bTimed *r2b_TrackFind(R2bTracks *o, int idx, uint32_t pos, uint32_t base)
{
    R2bTrack *t;
    uint8_t *p, *last;
    uint32_t i;
    if (!o)
        for (;;) ;
    t = &o->tr0C[idx];
    p = t->items0C;
    last = p;
    for (i = 0; i < t->count04; i++) {
        if (pos < ((R2bTimed *)p)->pos00 + base)
            break;
        last = p;
        p += t->stride08;
    }
    return (R2bTimed *)last;
}

/* 0x000E0CD0: ids from 0x10 up are moved up by 0x10 (wrapping at 0x100). */
int r2b_Wrap10(int v)
{
    if (v >= 0x10)
        v = (uint8_t)(v + 0x10);
    return v;
}

/* 0x000E0D30: ids from 0x25 up are moved up by 0x25 (wrapping at 0x100). */
int r2b_Wrap25(int v)
{
    if (v >= 0x25)
        v = (uint8_t)(v + 0x25);
    return v;
}

/* 0x000E0E40: when the hint source 0x3F1B1C exists and hints are allowed (flag
   0x413140, 0x3F0A84 or b == 0), rebuild the hint record 0x3F118C for b. */
void r2b_PlayHint(int b)
{
    if (!r2b_g3F1B1C)
        return;
    if (aec_413140 || aec_3F0A84 || !b) {
        sub_0003FC10(aec_3F118C);
        sub_0003FCB0(aec_3F118C, sub_0003FA70(r2b_g3F1B1C, b, 0, 20.0f, -1.0f));
    }
}
