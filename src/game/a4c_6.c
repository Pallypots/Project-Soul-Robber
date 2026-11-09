/* Area a4c, group 6: menu option values 0x0003E9E0..0x0003EC90. Names inferred. */
#include "a4c.h"

/* 0x0003E9E0: number of entries in a menu definition's 0x24-byte table (terminated by a zero first field). */
int a4c_MenuEntryCount(A4cMenuDef *o)
{
    A4cOptEntry *e;
    int n;
    if (o == 0 || o->entries == 0) return 0;
    n = 0;
    for (e = o->entries; e->f00; e++) n++;
    return n;
}
/* 0x0003EA10: set an integer value clamped to [min,max]. */
void a4c_OptSetInt(A4cOption *o, int v)
{
    if (o == 0) return;
    o->kind = 2;
    if (o->min.i > v) o->value.i = o->min.i;
    else if (o->max.i < v) o->value.i = o->max.i;
    else o->value.i = v;
}
/* 0x0003EA80: set a list index; out-of-range values select the last entry. */
void a4c_OptSetIndex(A4cOption *o, int v)
{
    if (o == 0) return;
    o->kind = 4;
    if (o->min.i > v) o->value.i = o->max.i;
    else if (o->max.i < v) o->value.i = o->max.i;
    else o->value.i = v;
}
/* 0x0003EAB0: set a float value clamped to [min,max]. */
void a4c_OptSetFloat(A4cOption *o, float v)
{
    if (o == 0) return;
    o->kind = 6;
    if (o->min.f > v) o->value.f = o->min.f;
    else if (v > o->max.f) o->value.f = o->max.f;
    else o->value.f = v;
}
/* 0x0003EAF0: set a boolean value. */
void a4c_OptSetBool(A4cOption *o, int v)
{
    if (o == 0) return;
    o->kind = 5;
    o->value.i = v != 0;
}
/* 0x0003EB10: current value as an integer. */
int a4c_OptGetInt(A4cOption *o)
{
    if (o == 0) return 0;
    switch (o->kind) {
    case 2: case 3: case 4: return o->value.i;
    case 5: return o->value.i != 0;
    case 6: return (int)o->value.f;
    }
    return 0;
}
/* 0x0003EC90: initialise and mark as kind 3. */
void a4c_OptInitKind3(A4cOption *o, int a, int b, int c, int d, int e)
{
    if (o == 0) return;
    sub_0003EC30(o, a, b, c, d, e);
    o->kind = 3;
}
