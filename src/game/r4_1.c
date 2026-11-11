/* Area r4: work-slot setup helpers around 0x00193990-0x00196AD5 (r4_1). Names inferred. */
#include "r4.h"

/* Clear one work slot (inlined helper). */
static void SlotClear(R4Slot *s)
{
    if (s) {
        s->actor = 0;
        s->i00 = 0;
        s->ctl = 0;
        s->type = -1;
        s->w58 = 0;
    }
}

/* 0x00196750: clear all 18 work slots at 0x00400E50. No register inputs. */
void r4_SlotClearAll(void)
{
    int i;
    for (i = 0; i < 18; i++)
        SlotClear(&a9b_g400E50[i]);
}

/* 0x00195150: slot controller release callback: frees the slot of actor a. Stack args (a ctl msg). */
int r4_SlotRelease(R4Actor *a, R4Ctl *ctl, void *msg)
{
    R4Slot *s;
    int i = 0;
    for (s = a9b_g400E50; s < a9b_g400E50 + 18; s++, i++) {
        if (s->actor == a) {
            sub_00033B30(a);
            SlotClear(&a9b_g400E50[i]);
            ctl->slot74 = 0;
            sub_0001EB80(a);
            a->flagsC &= ~1u;
            a->flags10 |= 0xD;
            return 1;
        }
    }
    if (i >= 18)
        for (;;) ;
    return 0;
}

/* 0x001953B0: slot type 2 setup. regargs: s=EDI. */
void r4_SlotInitType2(R4Slot *s)
{
    R4Actor *a = s->actor;
    a->flagsC &= ~0xE0u;
    a->flags10 |= 0x44D;
    if (a->p28)
        sub_0001EE80(a, (void *)sub_00196B40);
    s->f18 = 0.7f;
    R4_ACTOR_F64(a) = -500.0f;
}

/* 0x00196850: slot type 3 setup. regargs: s=EDI. */
void r4_SlotInitType3(R4Slot *s)
{
    R4Actor *a = s->actor;
    a->flagsC = (a->flagsC & ~0x60u) | 0x80;
    a->flags10 |= 0x41;
    a->i124 = 1;
    sub_0001D7A0(a);
    a->i118 = 1;
    s->ctl->fn80 = (void *)sub_00195400;
}

/* 0x001968A0: slot type 4 setup. regargs: s=EDI. */
void r4_SlotInitType4(R4Slot *s)
{
    R4Actor *a = s->actor;
    a->flagsC = (a->flagsC & ~0x60u) | 0x80;
    a->flags10 |= 0x41;
    a->i124 = 1;
    sub_0001D7A0(a);
    a->i118 = 1;
    s->ctl->fn80 = (void *)sub_00195400;
    sub_00189DA0(s->actor, s->ctl, 0xC);
}

/* 0x00196790: slot type 0/1 setup. regargs: s=ESI. */
void r4_SlotInitType0(R4Slot *s)
{
    R4Ctl *c = s->ctl;
    R4Actor *a = s->actor;
    float v[4];
    a->flags10 |= 0x200;
    a->i124 = 1;
    sub_0001EBF0(a, 2);
    c->f28 = 0.0f;
    c->fn80 = (void *)sub_00195210;
    c->f2C = -9.0f;
    sub_00189DA0(a, s->ctl, 1);
    s->w80 = 0;
    s->w82 = 0;
    s->f1C = 1.0f;
    v[0] = 0.0f;
    v[1] = 2.5f;
    v[2] = 0.0f;
    v[3] = 1.0f;
    sub_0001EF00(a, v);
    s->f18 = 1.0f;
}

/* 0x00196A70: copy matrix m onto the linked actor a and mark it. Stack args (a m). */
void r4_LinkSetMatrix(R4Actor *a, float *m)
{
    R4Link44 *e;
    int i;
    if (!a)
        return;
    e = a19_g401828;
    for (i = 0; i < 6; i++, e++)
        if (e->actor == a)
            break;
    if (i >= 6)
        return;
    sub_001ADA40(e->actor->p20, m);
    sub_000F5D40(e->actor->pos60, m + 12);
    sub_000385D0(e->actor->p20, e->actor->p20);
    a->flagsC |= 0x100;
    e->wE = 1;
}
