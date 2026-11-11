/* Area r2c, group 8: enemy step selectors (0x0012B080..0x0012E62E). Names inferred. */
#include "r2c.h"

/* 0x0012B080: with description flag 0x400 drop obj (0x0ED780); otherwise,
   in state 0 with flag 0x20, go to step 0x2F.
   Calls 0x0011F2B0 with EDI=obj EBX=0x2F and z on the stack. */
void r2c_DescStep2F(void *obj, R2cActor *z)
{
    uint32_t fl = z->p278->flags4;
    if (fl & 0x400) {
        sub_000ED780(obj);
        return;
    }
    if (z->v58 == 0 && (fl & 0x20))
        sub_0011F2B0(obj, 0x2F, z);
}

/* 0x0012BA10: go to step 0x2F.
   Calls 0x0011F2B0 with EDI=obj EBX=0x2F and a on the stack. */
void r2c_Step2F(void *obj, void *a)
{
    sub_0011F2B0(obj, 0x2F, a);
}

/* 0x0012C7C0: when o's animation has finished go to step 1.
   Calls 0x0011F2B0 with EDI=o EBX=1 and a on the stack. */
void r2c_AnimDoneStep1(R2cActor *o, void *a)
{
    if (sub_000833E0(o->p30))
        sub_0011F2B0(o, 1, a);
}

/* 0x0012CEE0: go to step 1.
   Calls 0x0011F2B0 with EDI=obj EBX=1 and a on the stack. */
void r2c_Step1(void *obj, void *a)
{
    sub_0011F2B0(obj, 1, a);
}

/* 0x0012D2C0: 1 when neither kind 5 nor kind 0x0F has flag 0x2000 set for
   self. regargs: none (self on the stack); calls 0x0011FAC0 with EAX=kind
   EDI=self. */
int r2c_NoFlag2000(void *self)
{
    if (r2_AnyFlag2000(5, self) || r2_AnyFlag2000(0xF, self))
        return 0;
    return 1;
}

/* 0x0012DD40: 1 when 0x135780 reports kind 0 or kind 0x0E.
   Calls 0x00135780 with EAX=kind. */
int r2c_Any0or14(void)
{
    if (r3b_Any135780(0))
        return 1;
    return r3b_Any135780(0xE) != 0;
}

/* 0x0012E5E0: pass every key of kind 2 with sub-id 0 and then sub-id 0x0E
   to 0x137F50 together with p. regargs: p=ESI (passed on to 0x137F50 as its
   second argument). */
void r2c_NotifyKind2B(void *p)
{
    void *k;
    for (k = r2c_FindKey(2, 0); k; k = r2c_FindKey(-1, -1))
        sub_00137F50(k, p);
    for (k = r2c_FindKey(2, 0xE); k; k = r2c_FindKey(-1, -1))
        sub_00137F50(k, p);
}
