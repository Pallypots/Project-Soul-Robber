/* Area a3b, group 1: small record and state helpers near 0x00031070. Names inferred. */
#include "a3b.h"

/* 0x00031070: reset a 0x1C-byte record (id -1, rest zero). */
void a3b_Rec1CReset(A3bRec1C *r)
{
    r->id = -1;
    r->f04 = 0; r->f08 = 0; r->f0C = 0; r->f10 = 0; r->f14 = 0; r->f18 = 0;
}

/* 0x00031090: initialise a 0x14-byte record. */
void a3b_Rec14Init(A3bRec14 *r, int v, int first)
{
    r->f08 = v;
    r->f04 = v;
    r->f00 = first;
    r->f0C = 0;
    r->f10 = 0;
}

/* 0x00031540: copy a string into the global name buffer. */
void a3b_SetName(const char *s)
{
    char *d = a3b_name3817A0;
    while ((*d++ = *s++) != 0)
        ;
}

/* 0x00031C50: is the special mode (100) active. */
int a3b_IsMode100(void) { return a3b_mode381AB8 == 100; }

/* 0x00032450: is the selected state nonzero. */
int a3b_StateSet(int second)
{
    int v = a3b_g381834;
    if (second) v = a3b_g381850;
    return v != 0;
}

/* 0x00032470: state differs from its idle value (1 or 3). */
int a3b_StateNotIdle(int second)
{
    if (!second) return a3b_g381834 != 1;
    return a3b_g381850 != 3;
}

/* 0x000324A0: table lookup. */
int a3b_Tbl381A60Get(int i) { return a3b_tbl381A60[i]; }

/* 0x000325A0: store flag and forward 2 or 0. */
void a3b_SetFlag381884(int v)
{
    a3b_g381884 = v;
    sub_001A8A70(v ? 2 : 0);
}

/* 0x000325D0: read flag. */
int a3b_GetFlag381884(void) { return a3b_g381884; }

/* 0x000325E0: map a value in special mode, else pass through. */
int a3b_MapIfMode100(int v)
{
    if (a3b_mode381AB8 == 100) return sub_00031C60(v);
    return v;
}
