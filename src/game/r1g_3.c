/* Area r1g, group 3: HUD counter and combo banner requests 0x00025C10..0x00025D50. Names inferred. */
#include "r1g.h"

/* 0x00025C10: request for the counter display (stage G).
   kind 0: hide; kind 1: show with maximum n and count 0;
   kind 2: add n to the count (clamped to the maximum) and replay the
   update sequence for the current display state. */
void r1g_CounterRequest(int kind, int n)
{
    R1gStageG *g = &r1f_seqG37E090;
    sub_00032140(1, 0, 0);
    switch (kind) {
    case 0:
        g->q[0] = 2;
        g->q[1] = 0;
        g->state = 0;
        break;
    case 1:
        g->q[3] = 0;
        g->cur = 0;
        g->state = 0;
        g->q[0] = 1;
        g->q[1] = 3;
        g->q[2] = 2;
        g->max = (uint16_t)n;
        break;
    case 2:
        g->cur += (uint16_t)n;
        if (g->max < g->cur)
            g->cur = g->max;
        switch (g->q[0]) {
        case 1:
            g->q[4] = 0;
            g->q[0] = 1;
            g->q[1] = 4;
            g->q[2] = 3;
            g->q[3] = 2;
            break;
        case 3:
            g->q[3] = 0;
            g->state = 0;
            g->q[0] = 4;
            g->q[1] = 3;
            g->q[2] = 2;
            break;
        case 4:
            g->q[3] = 0;
            g->q[0] = 4;
            g->q[1] = 3;
            g->q[2] = 2;
            break;
        }
        break;
    }
}

/* 0x00025D50: request for the combo banner (stage K, with stage H).
   kind 0: hide; kind 1: add n hits (max 999), record the best combo and
   show the banner, announcing each threshold of the current row reached;
   kind 2: select threshold row n (0 or 1) and reset; kind 3: reset. */
void r1g_ComboRequest(int kind, int n)
{
    R1gStageH *h = &r1f_seqH37EDEC;
    R1gStageK *k = &r1g_stageK37EEC8;
    short c;
    switch (kind) {
    case 0:
        switch (k->q[0]) {
        case 1:
            k->q[0] = 0;
            h->q[0] = 0;
            k->state = 0;
            break;
        case 3:
            k->q[0] = 2;
            h->q[0] = 2;
            k->q[1] = 0;
            h->q[1] = 0;
            k->state = 0;
            break;
        }
        return;
    case 1:
        r1g_combo37EEBE += (short)n;
        if (r1g_combo37EEBE > 999)
            r1g_combo37EEBE = 999;
        Grade_AddBestCombo(r1g_combo37EEBE);
        c = r1g_combo37EEBE;
        if (r1g_comboReset37EEC4 == 1 && c < 5)
            return;
        r1g_comboReset37EEC4 = 0;
        r1g_comboShown37EEC2 = c;
        switch (k->q[0]) {
        case 0:
            k->q[0] = 1;
            k->q[1] = 3;
            k->q[2] = 2;
            k->q[3] = 0;
            k->state = 0;
            break;
        case 1:
        case 3:
            k->state = 0;
            break;
        case 2:
            k->q[0] = 3;
            h->q[0] = 3;
            k->q[1] = 2;
            h->q[1] = 2;
            k->q[2] = 0;
            h->q[2] = 0;
            h->state = 0;
            k->state = 0;
            break;
        }
        if (r1g_comboSteps28090C[h->table][r1g_comboRank37EEBC] > c)
            return;
        sub_00048AF0(r1g_comboRank37EEBC + 0x7D);
        h->q[2] = 2;
        h->q[3] = 0;
        h->state = 0;
        k->b28 = 0;
        h->q[1] = 3;
        r1g_comboRank37EEBC++;
        r1g_comboRankShown37EEC0 = r1g_comboRank37EEBC;
        h->q[0] = 1;
        return;
    case 2:
        if (n != 0 && n != 1)
            for (;;) ;
        if (h->table == n)
            return;
        h->table = n;
        /* fall through */
    case 3:
        r1g_comboReset37EEC4 = 1;
        r1g_combo37EEBE = 0;
        r1g_comboRank37EEBC = 0;
        return;
    }
}
