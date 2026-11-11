/* Ranges, controller shock tables and channel records (0x0005A400-0x0005FFAA),
 * second pass. Reference build OOGIE-XBOX-US-RETAIL. Names inferred. */
#include "a5b.h"

/* 0x0005A400: reset a range record (scale 1). */
void a5b_RangeInit(A5bRange *r)
{
    r->f08 = 0.0f;
    r->unk00 = 0;
    r->unk04 = 0;
    r->f0C = 1.0f;
    r->unk10 = 0;
}

/* 0x0005EB10: play shock table `i` (< 64) at full strength. */
int a5b_ShockPlay(int a, int i)
{
    if (i >= 0x40)
        return -1;
    return sub_0005EA60(a, a5b_cellTables[i], 1.0f);
}

/* 0x0005EB40: setter for 0x003E608C. */
void a5b_Set3E608C(int v)
{
    a5b_g3E608C = v;
}

/* 0x0005EB50: clear both channel records and reset their outputs. */
void a5b_ChansReset(void)
{
    int i, k;
    for (i = 0; i < 2; i++) {
        for (k = 0; k < 2; k++) {
            a5b_chans[i].sub[k].a = 0;
            a5b_chans[i].sub[k].b = 0;
            a5b_chans[i].sub[k].c = 0;
            a5b_chans[i].sub[k].d = 0;
        }
        sub_0004ED60(i, 0, 0);
    }
}

/* 0x0005EBA0: shock table pointer `i`. */
A5bCell **a5b_ShockTable(int i)
{
    return a5b_cellTables[i];
}

/* 0x0005ECF0: format the shock data file name for number `n` (< 0x100). */
void a5b_ShockFileName(char *dst, int n)
{
    if (n < 0x10)
        a6b_Printf2(dst, a5b_strShock0, n);
    else if (n < 0x100)
        a6b_Printf2(dst, a5b_strShock, n);
}

/* 0x0005EDA0: delete cell `b` of row `c` in table `t`, shifting the rest
 * down; 0 if the cell was already empty. */
int a5b_CellDelete(int t, int b, int c)
{
    A5bCell *e = a5b_cellTables[t][c] + b;
    if (e->n <= 0)
        return 0;
    do {
        e[0].a = e[1].a;
        e[0].n = e[1].n;
        e++;
    } while (e->n > 0);
    return 1;
}

/* 0x0005FFA0: clear mode 0x003E64C0. */
void a5b_ClearMode3E64C0(void)
{
    a60_mode3E64C0 = 0;
}
