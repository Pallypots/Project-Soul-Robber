/* Area r1f, group 8: sound name lookups 0x00052E60..0x000531C0. Names inferred. */
#include "r1f.h"

/* 0x00052E60: look up `key` in the sound name table, then `sub` in its
   list; returns the list value (the terminator's value if absent) or 0.
   regargs: key=EDX sub=EDI. The original compiler folded the first table id
   (1) into the search loop; written as an explicit start value */
int r1f_SndLookup(int key, int sub)
{
    R1fKeyVal *e, *p;
    int i, j;
    int id = 1;                 /* r1f_sndTab26BD78[0].id, folded */
    for (i = 0; id != key; ) {
        id = r1f_sndTab26BD78[++i].id;
        if (id == -1)
            break;
    }
    if (r1f_sndTab26BD78[i].id == -1)
        return 0;
    e = r1f_sndTab26BD78[i].list;
    for (j = 0, p = e; p->key != -1; p++, j++)
        if (p->key == sub)
            break;
    return e[j].val;
}

/* 0x00052EC0: store `key` to *outKey and the alternate id of (key, sub) to
   *outSub (sub itself when the table has none).
   regargs: outKey=EAX key=EDX outSub=EBX */
void r1f_SndAlias(int *outKey, int key, int *outSub, int sub)
{
    R1fKeyVal *e, *p;
    int i, j, alt;
    int id = 1;                 /* r1f_sndTab26BD78[0].id, folded */
    if (outKey != 0)
        *outKey = key;
    if (outSub == 0)
        return;
    for (i = 0; id != key; ) {
        id = r1f_sndTab26BD78[++i].id;
        if (id == -1)
            break;
    }
    if (r1f_sndTab26BD78[i].id != -1) {
        e = r1f_sndTab26BD78[i].list;
        for (j = 0, p = e; p->key != -1; p++, j++)
            if (p->key == sub)
                break;
        alt = e[j].alt;
        if (alt != -1)
            sub = alt;
    }
    *outSub = sub;
}

