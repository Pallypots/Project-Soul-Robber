/* Area ac0, group 2: companion slots and link queries 0x000C6B50-0x000CA540. Names inferred. */
#include "ac0.h"

/* 0x000C6B50: put slot index v in the first free entry; returns its index (3 if full). */
int ac0_Slots_Add(Ac0Actor *a, int v)
{
    int i;
    for (i = 0; i < 3; i++) {
        if (a->slots[i] < 0) {
            a->slots[i] = v;
            if (a->curSlot < 0) a->curSlot = i;
            return i;
        }
    }
    return i;
}
/* 0x000C6C60: move the current slot's companion from state 0x10000000 to 0x20000000. */
void ac0_Slots_Promote(Ac0Actor *a)
{
    int k;
    Ac0Slot *s;
    if (a->curSlot < 0) return;
    k = a->slots[a->curSlot];
    if (k < 0) return;
    s = &g_ac0_slots[k];
    if (s->flags & 0x10000000)
        s->flags = (s->flags & ~0x10000000) | 0x20000000;
}
/* 0x000C6CA0: number of active companion slots. */
int ac0_Slots_CountActive(Ac0Actor *unused)
{
    int n = (g_ac0_slots[0].flags & 1) ? 1 : 0;
    if (g_ac0_slots[1].flags & 1) n++;
    if (g_ac0_slots[2].flags & 1) n++;
    return n;
}
/* 0x000C7280: the active slot owned by `o`, or NULL. */
Ac0Slot *ac0_Slots_FindOwner(Ac0Link *o)
{
    int i;
    Ac0Slot *s;
    if (!o) return 0;
    for (i = 0; i < 3; i++) {
        s = &g_ac0_slots[i];
        if ((s->flags & 1) && (s->owner->flags & 1) && s->owner == o)
            break;
    }
    if (i >= 3) return 0;
    return s;
}
/* 0x000C7D90: reset via 0x000C7CC0 and set four limits to 32. */
void ac0_ResetLimits(int a)
{
    sub_000C7CC0(a);
    g_ac0_41CD50 = 0x20;
    g_ac0_41CDAC = 0x20;
    g_ac0_41CE08 = 0x20;
    g_ac0_41CE64 = 0x20;
}
/* 0x000C9B20: forward to 0x000D45B0 on the global object with -1, -1. */
void ac0_Call_D45B0(int a)
{
    sub_000D45B0(g_42C8EC, a, -1.0f, -1.0f);
}
/* 0x000C9E00: store a 3-vector globally. */
void ac0_SetVec418B30(const float *v)
{
    g_ac0_418B30[0] = v[0];
    g_ac0_418B30[1] = v[1];
    g_ac0_418B30[2] = v[2];
}
/* 0x000CA300: the link's range if flagged and at least 6.0, else 6.0. */
float ac0_LinkRange(Ac0Actor *a)
{
    Ac0Link *l = a->linkEFC;
    if (l && (l->flags & 0x40) && !(6.0f > l->fE8))
        return l->fE8;
    return 6.0f;
}
/* 0x000CA540: attach a link and restart its timer. */
void ac0_SetLink(Ac0Actor *a, Ac0Link *l, int v)
{
    a->vEF8 = v;
    a->linkEFC = l;
    a->vFA8 = 0;
    a->fFAC = sub_00171B40(a);
}

/* 0x000C70C0: 1 if anything is within radius 2.5 of obj + 0x34. */
int ac0_AnyNear(uint8_t *obj)
{
    float a[4], b[4];
    a[0] = 0.0f; a[1] = 0.0f; a[2] = 0.0f; a[3] = 1.0f;
    b[0] = 0.0f; b[1] = 0.0f; b[2] = 0.0f; b[3] = 1.0f;
    return sub_000D0DC0(obj + 0x34, 2.5f, b, a) > 0;
}
/* 0x000C9210: reset the 20 transform records to identity. */
void ac0_Xforms_Reset(void)
{
    int i;
    for (i = 0; i < 20; i++) {
        Ac0Xform *x = &g_ac0_xforms[i];
        x->i00 = 0; x->f04 = 0.0f; x->f08 = 1.0f; x->f0C = 0.0f;
        x->i10 = 0;
        x->f1C = 0.0f; x->f18 = 0.0f; x->f14 = 0.0f;
        x->f2C = 0.0f; x->f28 = 0.0f; x->f24 = 0.0f;
        x->f30 = 1.0f; x->f20 = 1.0f;
        x->iE8 = 0;
    }
}
/* 0x000C9FB0: in mode 0, copy colour v (alpha forced to 128) into the model. */
void ac0_SetColour(Ac0Actor *a, float *v)
{
    uint8_t *r, *m;
    if (a->mode1B8 != 0) return;
    r = sub_0001D290(a->subFD8, 1);
    v[3] = 128.0f;
    m = *(uint8_t **)(r + 0x20);
    ((int32_t *)(m + 0xD0))[0] = ((int32_t *)v)[0];
    ((int32_t *)(m + 0xD0))[1] = ((int32_t *)v)[1];
    ((int32_t *)(m + 0xD0))[2] = ((int32_t *)v)[2];
    ((int32_t *)(m + 0xD0))[3] = ((int32_t *)v)[3];
}
