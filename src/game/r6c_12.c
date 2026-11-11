/* Area r6c: event scene steps around 0x00087D90-0x000888BC (r6c_12). Names inferred. */
#include "r6c.h"

/* 0x00087D90: run the group's first job (0x000856F0) in the background, then switch to mode 6. */
void r6c_EvRunJobA(void)
{
    switch (r6c_v3ED270) {
    case 0:
        if (sub_00057E90())
            return;
        sub_00058540((void (*)(void))sub_000856F0, r6c_grp3ED254);
        r6c_v3ED270 = 10;
        /* fall through */
    case 10:
        if (sub_00057E90())
            return;
        r6c_v3ED270 = 0;
        r6c_v3ED274 = 6;
    }
}

/* 0x00087DE0: run the group's second job (0x00085820) in the background, then switch to mode 7. */
void r6c_EvRunJobB(void)
{
    switch (r6c_v3ED250) {
    case 0:
        if (sub_00057E90())
            return;
        sub_00058540((void (*)(void))sub_00085820, r6c_grp3ED254);
        r6c_v3ED250 = 10;
        /* fall through */
    case 10:
        if (sub_00057E90())
            return;
        r6c_v3ED250 = 0;
        r6c_v3ED274 = 7;
    }
}

/* 0x00087E70: run the group's third job (0x00085930) in the background, then switch to mode 10. */
void r6c_EvRunJobC(void)
{
    switch (r6c_v3ED24C) {
    case 0:
        if (sub_00057E90())
            return;
        sub_00058540((void (*)(void))sub_00085930, r6c_grp3ED254);
        r6c_v3ED24C = 10;
        /* fall through */
    case 10:
        if (sub_00057E90())
            return;
        r6c_v3ED24C = 0;
        r6c_v3ED274 = 10;
    }
}

/* 0x00088030: spawn more of the group's enemies while there is room; mode 12 when none are active. */
void r6c_EvSpawnStep(void)
{
    uint32_t f = r6c_v3ED258;
    if (!(f & 0x200000)) {
        if ((f & 0x100000) || (a80_Get3ED238() != 1 && r6c_v3ED26C < r6c_grp3ED254->limit)) {
            int n = sub_000EDAD0(2, -1) + sub_000EDAD0(8, -1);
            if (n < r6c_grp3ED254->total && r6c_grp3ED254->total - n >= r6c_grp3ED254->step)
                r6c_v3ED26C += sub_00085110(r6c_grp3ED254->step);
            return;
        }
    }
    if (!sub_000EDA50())
        r6c_v3ED274 = 12;
}

/* 0x000880C0: clear the scene step states and the nine scene records. */
void r6c_ScnClearAll(void)
{
    a80_curMode = 0;
    r6c_v3ED514 = 0;
    r6c_v3ED510 = 0;
    r6c_recs2E0690[0].a = 0;
    r6c_recs2E0690[0].b = 0;
    r6c_recs2E0690[1].a = 0;
    r6c_recs2E0690[1].b = 0;
    r6c_recs2E0690[2].a = 0;
    r6c_recs2E0690[2].b = 0;
    r6c_recs2E0690[3].a = 0;
    r6c_recs2E0690[3].b = 0;
    r6c_recs2E0690[4].a = 0;
    r6c_recs2E0690[4].b = 0;
    r6c_recs2E0690[5].a = 0;
    r6c_recs2E0690[5].b = 0;
    r6c_recs2E0690[6].a = 0;
    r6c_recs2E0690[6].b = 0;
    r6c_recs2E0690[7].a = 0;
    r6c_recs2E0690[7].b = 0;
    r6c_recs2E0690[8].a = 0;
    r6c_recs2E0690[8].b = 0;
}

/* 0x000881B0: step a scene's enter handler (direct, or as a background job); 0 when done.
   regargs: s=ESI */
int r6c_ScnEnterStep(R6cScn *s)
{
    switch (r6c_v3ED514) {
    case 0:
        s->flags = 0;
        a80_StatePause();
        if (sub_00057EA0()) {
            if (!s->enter) {
                s->flags |= 1;
                return 0;
            }
            s->enter(0);
            s->flags |= 1;
            return 0;
        }
        if (sub_00057E90())
            return 1;
        if (s->enter)
            sub_00058540((void (*)(void))s->enter, 0);
        r6c_v3ED514 = 10;
        /* fall through */
    case 10:
        if (sub_00057E90())
            return 1;
        r6c_v3ED514 = 0;
        s->flags |= 1;
        return 0;
    }
    return 1;
}

/* 0x00088240: step a scene's leave handler (direct, or as a background job); 0 when done.
   regargs: s=ESI */
int r6c_ScnLeaveStep(R6cScn *s)
{
    switch (r6c_v3ED510) {
    case 0:
        a80_StateResume();
        sub_00019000(ae0_obj3E1270, 1);
        sub_000BCA50(0);
        if (sub_00057EA0()) {
            if (!s->leave) {
                s->flags = 0;
                s->state = 0;
                return 0;
            }
            s->leave(0);
            s->flags = 0;
            s->state = 0;
            return 0;
        }
        if (sub_00057E90())
            return 1;
        if (s->leave)
            sub_00058540((void (*)(void))s->leave, 0);
        r6c_v3ED510 = 10;
        /* fall through */
    case 10:
        if (sub_00057E90())
            return 1;
        r6c_v3ED510 = 0;
        s->flags = 0;
        s->state = 0;
        return 0;
    }
    return 1;
}

/* 0x00088400: scene update: lock the player and play effect 11 until the finish flag, then unlock. */
void r6c_ScnUpdate11(R6cScn *s)
{
    R6cScnData *d;
    if (!(s->flags & 1))
        return;
    switch (s->state) {
    case 0:
        sub_000D2A50(&g_stats, 1);
        sub_000DE330(1);
        d = *s->data;
        sub_000ED630(2, 11, d, &d->pos, d->i20);
        s->state = 10;
        /* fall through */
    case 10:
        if (s->flags & 4)
            s->state = 20;
        break;
    case 20:
        sub_000D2A50(&g_stats, 0);
        sub_000DE330(0);
        s->flags = (s->flags & ~5u) | 2;
        s->state = 0;
        break;
    }
}

/* 0x00088710: scene update: lock the player and play effect 12 until the finish flag, then unlock. */
void r6c_ScnUpdate12(R6cScn *s)
{
    R6cScnData *d;
    if (!(s->flags & 1))
        return;
    switch (s->state) {
    case 0:
        sub_000D2A50(&g_stats, 1);
        sub_000DE330(1);
        d = *s->data;
        sub_000ED630(2, 12, d, &d->pos, d->i20);
        s->state = 10;
        /* fall through */
    case 10:
        if (s->flags & 4)
            s->state = 20;
        break;
    case 20:
        sub_000D2A50(&g_stats, 0);
        sub_000DE330(0);
        s->flags = (s->flags & ~5u) | 2;
        s->state = 0;
        break;
    }
}

/* 0x000887A0: stop effect channel 2 and wait for stream 15 to finish (heap 4 while working). */
void r6c_EvStopEffects(void)
{
    sub_00053710(4);
    sub_000ED4C0(2);
    while (sub_000ED520(2, 12))
        ;
    sub_000ED590(2, 12);
    sub_000ED5D0(2);
    sub_00047A80(15);
    while (sub_00047B10(15) != 2)
        ;
    sub_00047B30(15);
    while (sub_00047B50(15))
        ;
    sub_00053740();
}

/* 0x00088870: scene update: play effect 12 once, finish when state 20 is reached. */
void r6c_ScnUpdatePlay12(R6cScn *s)
{
    uint32_t f = s->flags;
    R6cScnData *d;
    if (!(f & 1))
        return;
    switch (s->state) {
    case 0:
        d = *s->data;
        sub_000ED630(2, 12, d, &d->pos, d->i20);
        s->state = 10;
        break;
    case 20:
        s->flags = (f & ~1u) | 2;
        s->state = 0;
        break;
    }
}
