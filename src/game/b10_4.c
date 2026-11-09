/* Area b10, group 4: actor callbacks and size getters 0x00114640-0x0012D660. Names inferred. */
#include "b10.h"

/* 0x00114640: object size 0x8C. */
int b10_Size8C(void) { return 0x8C; }

/* 0x00119F20: object size 0x44. */
int b10_Size44(void) { return 0x44; }

/* 0x0011AE20: apply list 0x0031DBD4 and run 0x000ED780 when +0x5C exceeds 1. */
void b10_ActorApplyList(void *o, B10Actor *a)
{
    sub_0013A380(o, 2, b10_list31DBD4);
    if (a->f5C > 1.0f)
        sub_000ED780(o);
}

/* 0x0011E010: object size 0x678. */
int b10_Size678(void) { return 0x678; }

/* 0x0011E480: run 0x000ED780 when the actor's handle is live. */
void b10_ActorIfLive(B10Actor *a)
{
    if (sub_000833E0(a->handle) != 0)
        sub_000ED780(a);
}

/* 0x0011E4A0: run 0x000ED780 on o when the info flag 0x400 is set. */
void b10_ActorIfFlag400(void *o, B10Actor *a)
{
    if (a->info->flags & 0x400)
        sub_000ED780(o);
}

/* 0x0011E4C0: test then apply via 0x00145940/0x001459D0 with the condition record. */
void b10_ActorTestApply(void *o, B10Actor *a, B10Cond *c)
{
    B10Info *i = a->info;
    if (sub_00145940(o, i->i10, i->i18, c->c, c->d) != 0)
        sub_001459D0(o, i->i10, i->i18, c->e);
}

/* 0x0011EFA0: 1 if info +0x7C lies in [lo, hi]. */
int b10_InfoInRange(void *o, B10Actor *a, B10CondF *c)
{
    B10Info *i = a->info;
    if (i->f7C >= c->lo && c->hi >= i->f7C)
        return 1;
    return 0;
}

/* 0x0011F070: test info flags against a mask; mode selects set or clear. */
int b10_InfoFlagTest(void *o, B10Actor *a, B10Cond *c)
{
    uint32_t f = a->info->flags;
    if (c->b == 0)
        return (f & c->a) == 0;
    return (f & c->a) != 0;
}

/* 0x0011F0A0: 1 if info +0x8C is not positive. */
int b10_InfoDepleted(void *o, B10Actor *a)
{
    if (a->info->f8C <= 0.0f)
        return 1;
    return 0;
}

/* 0x0011F620: combine o+0x40 with b+0x18 in place. */
void b10_Combine40(uint8_t *o, uint8_t *b)
{
    sub_001AD7C0(o + 0x40, o + 0x40, b + 0x18);
}

/* 0x0012D2A0: 1 if 0x00135E10() lies in the record's [+0x08, +0x0C] range (unsigned). */
int b10_InRangeU(void *a, void *b, B10Cond *c)
{
    uint32_t v = sub_00135E10();
    if (v >= c->a && v <= c->b)
        return 1;
    return 0;
}

/* 0x0012D660: object size 0x1C8. */
int b10_Size1C8(void) { return 0x1C8; }
