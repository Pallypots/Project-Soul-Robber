/* Area r1e, group 2: effect transforms, effect table lookup, bank update 0x000337A0..0x000367E0. Names inferred. */
#include "r1e.h"

/* 0x000337A0: set an idle node's three axes and re-orthonormalise. */
void r1e_XfSetAxes(R1eXfNode *n, const float *a, const float *b, const float *c)
{
    if (n != 0 && n->busy == 0) {
        sub_000F5D40(n->m[3], a);
        sub_000F5D40(n->m[2], b);
        sub_000F5D40(n->m[1], c);
        n->m[3][3] = 1.0f;
        r1e_MatOrtho(n->m, n->m);
    }
}

/* 0x00033800: build a basis from three axes and multiply it into an idle
   node's transform. */
void r1e_XfApplyAxes(R1eXfNode *n, const float *a, const float *b, const float *c)
{
    R1eMat m;
    if (n != 0 && n->busy == 0) {
        sub_001AD940(m);
        sub_000F5D40(m[3], a);
        sub_000F5D40(m[2], b);
        sub_000F5D40(m[1], c);
        r1e_MatOrtho(m, m);
        sub_001AD7C0(n->m, m, n->m);
        n->m[3][3] = 1.0f;
    }
}

/* 0x00033DF0: look up `key` in the effect table, then `sub` in its list;
   returns the list value (the terminator's value if absent) or 0.
   regargs: key=EDX sub=EDI */
int r1e_FxLookup(int key, int sub)
{
    R1eKeyVal *e, *p;
    int i, j;
    int id = 1;                 /* r1e_fxTab260FC0[0].id, folded */
    for (i = 0; id != key; ) {
        id = r1e_fxTab260FC0[++i].id;
        if (id == -1)
            break;
    }
    if (r1e_fxTab260FC0[i].id == -1)
        return 0;
    e = r1e_fxTab260FC0[i].list;
    for (j = 0, p = e; p->key != -1; p++, j++)
        if (p->key == sub)
            break;
    return e[j].val;
}

/* 0x000362F0: spawn an object for src when its shape has a size; the new
   object takes the spawner's tag. */
R1eSpawned *r1e_SpawnSized(R1eSpawner *sp, R1eSpawnSrc *src)
{
    R1eSpawned *o;
    if (src->shape->w > 0.0f && src->shape->h > 0.0f) {
        o = sub_00035000(sp->owner, src, -1, -1, 0);
        if (o != 0)
            o->tag = sp->tag;
        return o;
    }
    return 0;
}

/* 0x000367E0: update the bank's entries, advance running animations by one
   frame unless paused, then update the main objects. */
int r1e_BankUpdate(void)
{
    char *bank;
    R1eAnimLink *l;
    R1eAnimEnt *e;
    r1c_PoolForEach(r1e_bank283698 + 0x55140, 0x6C, sub_000367B0, 0);
    bank = r1e_bank283698;
    if (!(r1e_flags412F30 & 1)) {
        for (l = *(R1eAnimLink **)(bank + 0x58450); l != 0; l = l->next) {
            e = l->ent;
            if (e != 0 && e->kind == 1)
                e->t += a50_frameUnits;
        }
    }
    r1c_PoolForEach(bank, 0xB40, sub_00036180, 0);
    return 0;
}
