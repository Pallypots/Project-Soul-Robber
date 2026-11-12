/* Area rbl: enemy commands. Names inferred. */
#include "rbl.h"

/* 0x001208A0: send a command to an enemy of type 2 / kind 5 or 15 that is alive and not
   finished (+0x10 bit 3). The enemy's kind-4 component and its state block must exist
   (assert hangs otherwise). Commands 0..5 return 1; 6..8 (only acted on while state bit
   0x4000 is set) return 0, as does an unsuitable object. Unknown commands hang.
   Stack args (e cmd); calls 0x0011F2B0 with EDI=e EBX=step and the component on the stack. */
int rbl_EntCommand1208A0(RblEnt *e, int cmd)
{
    int r = 0;
    RblComp *c;
    RblState *s;

    if (e == 0 || !(e->flags0C & 1) || e->type04 != 2 || (e->sub08 != 5 && e->sub08 != 15))
        return 0;
    if (e->flags10 & 8)
        return 0;
    c = (RblComp *)sub_0001D960(e, 4);
    if (c == 0)
        for (;;) ;
    if (c->kind00 != 4)
        for (;;) ;
    s = c->state278;
    if (s == 0)
        for (;;) ;
    switch (cmd) {
    case 0:
        s->flags04 |= 0x80000;
        return 1;
    case 1:
        s->flags04 &= ~0x80000u;
        sub_0011F2B0(e, 0x35, c);
        return 1;
    case 2:
        s->flags04 &= ~0x80000u;
        sub_0011F2B0(e, 1, c);
        return 1;
    case 3:
        s->flags04 |= 0x8000;
        e->flags10 |= 1;
        return 1;
    case 4:
        e->flags10 |= 8;
        s->flags04 |= 0x20;
        sub_0011F2B0(e, 0x2E, c);
        return 1;
    case 5:
        sub_000ED780(e);
        return 1;
    case 6:
        if (s->flags04 & 0x4000) {
            if (c->flags20 & 1)
                sub_0011F2B0(e, 10, c);
            else
                sub_0011F2B0(e, 0x12, c);
        }
        return r;
    case 7:
        if (s->flags04 & 0x4000) {
            sub_0011F2B0(e, 9, c);
            s->i98 = 12;
        }
        return r;
    case 8:
        if (s->flags04 & 0x4000) {
            sub_0011F2B0(e, 9, c);
            s->i98 = 5;
        }
        return r;
    default:
        for (;;) ;
    }
}
