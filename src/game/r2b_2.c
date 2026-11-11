/* Area r2b, group 2: stats and player helpers (0x000D3000..0x000D9FFF). Names inferred. */
#include "r2b.h"

/* 0x000D34E0: hide Jack's model and its shadow, reset the stats, clear the effects
   and restart the idle sequence in modes 0 and 1. */
void r2b_PlayerReset(void)
{
    uint8_t *o = g_42C8EC;
    r1_NodeHide(g_playerObj);
    r1_NodeHide(*(void **)(o + 0x3B0));
    sub_000D1930(&g_stats);
    r2b_ClearEffects();
    sub_000BD4D0(&g_stats, 1);
    r2b_g41FFEC = 0;
    if (g_stats.unk1B8 == 0 || g_stats.unk1B8 == 1) {
        sub_000CE970();
        sub_000CEF60();
    }
}

/* 0x000D4560: store a in the hook record at 0x3EDB40, clear its +4 word and remove
   it from o when o has hooks. */
void r2b_HookStop(int a, int unused, R2bA8 *o)
{
    r2b_hook3EDB40.i10 = a;
    r2b_hook3EDB40.i04 = 0;
    if (o->hookA8)
        r4_HookRemoveA8(o, &r2b_hook3EDB40);
}

/* 0x000D51C0: set flag 2 (k == 0) or 4 (k == 1) in *p. */
void r2b_SetFlagByKind(uint32_t *p, int k)
{
    switch (k) {
    case 0:
        *p |= 2;
        break;
    case 1:
        *p |= 4;
        break;
    }
}

/* 0x000D5620: set or clear the top bit of the first word of object 0x42C8EC. */
void r2b_Set42C8ECTop(int on)
{
    uint32_t *o = (uint32_t *)g_42C8EC;
    if (on)
        *o |= 0x80000000u;
    else
        *o &= 0x7FFFFFFFu;
}

/* 0x000D5650: set flag 2 in the first word of object 0x42C8EC. */
void r2b_Set42C8ECBit2(void)
{
    *(uint32_t *)g_42C8EC |= 2;
}

/* 0x000D5660: load path into the +0x3B0 node of o; when it has render data also
   create the state object 0x42C8DC and load its fixed file. */
void r2b_LoadShadow(uint8_t *o, const char *path)
{
    sub_00022630(*(void **)(o + 0x3B0), path);
    if (*(void **)(*(uint8_t **)(o + 0x3B0) + 0x20)) {
        r2b_state42C8DC = r1_StateNew(0);
        sub_00022630(r2b_state42C8DC, r2b_str277288);
        r2b_g42C8D4 = *(void **)(g_42C8EC + 0x3B0);
    }
}

/* 0x000D7090: move buttons 0x8000, 0x1000, 0x2000, 0x4000 and 0x400 from b into bits
   0..4 of the mode word 0x3EDBA4 and return the remaining buttons.  regargs: b=EAX */
int r2b_TakeButtons(uint16_t b)
{
    uint32_t v = b;
    uint32_t m = r2_modes3EDB60.i44;
    if (v & 0x8000) {
        m |= 1;
        v &= ~0x8000u;
    } else
        m &= ~1u;
    if (v & 0x1000) {
        m |= 2;
        v &= ~0x1000u;
    } else
        m &= ~2u;
    if (v & 0x2000) {
        m |= 4;
        v &= ~0x2000u;
    } else
        m &= ~4u;
    if (v & 0x4000) {
        m |= 8;
        v &= ~0x4000u;
    } else
        m &= ~8u;
    if (v & 0x400) {
        m |= 0x10;
        v &= ~0x400u;
    } else
        m &= ~0x10u;
    r2_modes3EDB60.i44 = m;
    return v;
}

/* 0x000D71E0: first mode word. */
int r2b_GetMode0(void)
{
    return r2_modes3EDB60.i00;
}

/* 0x000D71F0: id of the current stage entry (value + per-flag base), -1 when unset
   or out of range (>= 0x264). */
int r2b_StageEntryId(void)
{
    int a = r2_modes3EDB60.unk08;
    int v = r2b_stages2E7D58[a].ent14[r2_modes3EDB60.i0C].v10;
    uint32_t f;
    if (v <= -1)
        return -1;
    f = r2b_stages2E7D58[a].flags00;
    if (f & 0x100)
        f &= ~0x100u;
    if (f & 0x200)
        f &= ~0x200u;
    v += r2b_tab2772F0[f];
    if (v >= 0x264)
        return -1;
    return v;
}

/* 0x000D7240: number of following stage entries sharing the current value; 0 when the
   run reaches the end or ends at an entry of kind 2 or 5..8 with the same value. */
int r2b_StageRunLength(void)
{
    int j = r2_modes3EDB60.i0C;
    int a = r2_modes3EDB60.unk08;
    int key = r2b_stages2E7D58[a].ent14[j].v10;
    int n = 0;
    for (; j < 32; j++) {
        int k = r2b_stages2E7D58[a].ent14[j].kind0C;
        if (k == 2 || (k > 4 && k <= 8))
            return r2b_stages2E7D58[a].ent14[j].v10 != key ? n : 0;
        if (r2b_stages2E7D58[a].ent14[j].v10 != key)
            return n;
        n++;
    }
    return 0;
}

/* 0x000D74D0: mode word 0x3EDBA8. */
int r2b_GetModeA8(void)
{
    return r2_modes3EDB60.i48[0];
}

/* 0x000D74E0: advance the step counter 0x3EDBB8 when the expected value of table
   0x300D80 for the current mode matches 0x0E0250(). */
int r2b_CheckStep(void)
{
    uint32_t i = (uint32_t)(r2_modes3EDB60.i48[5] - 0x23) >> 1;
    if (r2b_tab300D80[i] == sub_000E0250()) {
        r2_modes3EDB60.i48[4]++;
        return 1;
    }
    return 0;
}

/* 0x000D7510: start cue id + 0x183 (stopping the playing one) unless it is already
   playing or out of range. */
void r2b_PlayCue(int id)
{
    int s = id + 0x183;
    if (s >= 0x264 || s == -1)
        return;
    if (r2_modes3EDB60.i8C != -1) {
        if (s == r2_modes3EDB60.i90)
            return;
        sub_00048330(r2_modes3EDB60.i8C, 0);
        r2_modes3EDB60.i8C = -1;
    }
    if (s != r2_modes3EDB60.i90) {
        r2_modes3EDB60.i90 = s;
        r2_modes3EDB60.i8C = sub_00048B20(s, 0);
    }
}

/* 0x000D7570: stop the playing cue. */
void r2b_StopCue(void)
{
    if (r2_modes3EDB60.i8C != -1) {
        sub_00048330(r2_modes3EDB60.i8C, 0);
        r2_modes3EDB60.i8C = -1;
    }
}

/* 0x000D7590: clear the mode words 0x3EDBC0..0x3EDBE8 and set 0x3EDBDC to 4. */
void r2b_ResetModesD(void)
{
    int32_t *w = r2_modes3EDB60.unk60;
    w[0] = 0;
    w[1] = 0;
    w[2] = 0;
    w[3] = 0;
    w[4] = 0;
    w[5] = 0;
    w[6] = 0;
    w[8] = 0;
    w[9] = 0;
    w[10] = 0;
    w[7] = 4;
}

/* 0x000D7BF0: flag 0x200 of the current stage record. */
int r2b_StageFlag200(void)
{
    return (r2b_stages2E7D58[r2_modes3EDB60.unk08].flags00 >> 9) & 1;
}
