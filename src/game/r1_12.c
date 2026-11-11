/* Area r1, group 12: callers of the timer, bank and record helpers 0x0002C370..0x000533B0. Names inferred. */
#include "r1.h"

/* 0x0002C370: run the two screen-effect slots by their current mode.
   calls 0x0002B380 / 0x0002B450 / 0x0002B520 with ESI=slot */
void r1_FxUpdate(void)
{
    R1FxSlot *f;
    int i;
    for (i = 0; i < 2; i++) {
        f = &r1_fx[i];
        switch (f->t.q[0]) {
        case 0: f->t.flags &= ~1u; break;
        case 1: sub_0002B380(&f->t); break;
        case 2: sub_0002B450(&f->t); break;
        case 3: r1_TimerStep(&f->t); break;
        }
    }
}

/* 0x00034A30: set up the global sound bank and bind both channels.
   calls 0x00033330 with EAX=bank */
int r1_BankSetup(int a, int b)
{
    r1_bank = &r1_bank381AC0;
    r1_BankInit(r1_bank);
    r1_g3DA080 = a;
    r1_g3DA084 = b;
    sub_001B2020(a, &r1_bank->chans[0]);
    sub_001B2020(r1_g3DA084, &r1_bank->chans[1]);
    return 0;
}

/* 0x00053350: age every record matching (a,b) and release expired unlocked ones.
   calls 0x00053230 with EAX=prev stack=a,b */
void r1_EntAge(int a, int b)
{
    R1Ent20 *e;
    for (e = sub_000531C0(a, b); e; e = r1_EntFind(e, a, b)) {
        if (--e->life <= 0 && !(e->flags & 1)) sub_00052E10(e);
    }
}

/* 0x000533B0: release every unlocked record matching (a,b).
   calls 0x00053230 with EAX=prev stack=a,b */
void r1_EntReleaseAll(int a, int b)
{
    R1Ent20 *e;
    for (e = sub_000531C0(a, b); e; e = r1_EntFind(e, a, b)) {
        if (!(e->flags & 1)) sub_00052E10(e);
    }
}

/* 0x000535F0: acquire record (a,b) for slot and return its handle.
   calls 0x00053400 with ECX=slot stack=a then b */
int r1_EntAcquire(int slot, int a, int b)
{
    return sub_00053400(slot, a, b)->used;
}

/* 0x00053610: acquire record (a,b) for slot, lock it and return its handle.
   calls 0x00053400 with ECX=slot stack=a then b */
int r1_EntAcquireLocked(int slot, int a, int b)
{
    R1Ent20 *e = sub_00053400(slot, a, b);
    e->flags |= 1;
    return e->used;
}
