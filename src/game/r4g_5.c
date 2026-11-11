/* Area r4g: music player open at 0x001ABD10 (r4g_5). Names inferred. */
#include "r4g.h"

/* 0x001ABD10: open a music player for id on the current driver mode: pick
   a free player (mode 0 returns at once when the wanted cue < 0x2F is
   already open, and stops the old player for cues >= 0x2F), query the cue
   for modes 1 and 2, count failures (1000 of them raise 0x001A7A70), then
   prepare the cue, and in mode 0 also the mapped cue pair, and record the
   player. Stack args (unused id); XACT callees are stdcall. */
void r4g_MusOpen(int unused, int id)
{
    R4gDrvMsg m, ma, mb;
    R4gMus *t;
    R4gCueMap *p;
    uint32_t c;
    int i, hr, a, b;
    (void)unused;

    for (i = 0, t = r4f_mus40E358; i < 4; i++, t++) {
        if (r4d_drvMode40E348 == 0 && t->cue00 == aac_g365158 && aac_g365158 < 0x2F)
            return;
        if (t->cue00 == -1)
            break;
    }
    if (i == 4)
        return;
    c = (uint32_t)-1;
    hr = 0x80004005;
    if (r4d_drvMode40E348 == 0) {
        c = aac_g365158;
        if (c >= 0x2F) {
            i = sub_001ABC10(t->cue00, id);
            t = &r4f_mus40E358[i];
            t->paused29 = 0;
        }
        hr = 0;
    }
    if (r4d_drvMode40E348 == 1)
        hr = sub_0022268D(r4f_engines40C868[1], &r4f_cues338858[aac_g36515C], &c);
    if (r4d_drvMode40E348 == 2)
        hr = sub_0022268D(r4f_engines40C868[2], &r4f_cues33AE40[aac_g365160], &c);
    if (hr == (int)0x80004005) {
        if (++r4g_fail40C860 >= 1000)
            sub_001A7A70();
        return;
    }
    if (c == (uint32_t)-1)
        return;
    m.kind = 8;
    m.x = c;
    m.f0C = 0;
    m.f08 = 0;
    sub_002226C0(r4f_engines40C868[r4d_drvMode40E348], &m, &r4f_musPlay40E300[i]);
    if (r4d_drvMode40E348 == 0) {
        for (p = r4f_cueMap27B720; p != r4f_cueMap27B720 + 16; p++)
            if (p->id == (int32_t)c)
                break;
        if (p != r4f_cueMap27B720 + 16) {
            a = p->cueA;
            b = p->cueB;
            ma.kind = 8;
            ma.x = a;
            ma.f0C = 0;
            ma.f08 = 0;
            mb.kind = 8;
            mb.x = b;
            mb.f0C = 0;
            mb.f08 = 0;
            sub_002226C0(r4f_engines40C868[0], &ma, &r4f_playA40E5CC);
            sub_002226C0(r4f_engines40C868[r4d_drvMode40E348], &mb, &r4f_playB40E34C);
            r4f_curA40E5D0 = a;
            r4f_curB40C864 = b;
        }
    }
    t->cue00 = c;
    t->id24 = id;
    t->mode04 = r4d_drvMode40E348;
    t->b28 = 1;
    t->paused29 = 0;
}
