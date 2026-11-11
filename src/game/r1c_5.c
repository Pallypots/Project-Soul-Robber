/* Area r1c, group 5: callers of group 3/4 helpers 0x000314F0..0x0005BE30
   (kept apart so cl does not inline the callees). Names inferred. */
#include "r1c.h"

/* 0x000314F0: read the 32-bit value that follows an 8-bit tag in a bit
   stream starting at p.
   calls 0x000310B0 with ESI=&reader and stack=8 then stack=0x20 */
uint32_t r1c_BitReadTagged(uint32_t *p)
{
    R1cBits b;
    b.limit = -1;
    b.base = p;
    b.ptr = p;
    b.bit = 0;
    b.pos = 0;
    b.refill = 0;
    b.d18 = 0;
    r1c_BitRead(&b, 8);
    return r1c_BitRead(&b, 0x20);
}

/* 0x00034CA0: the bank entry (past its 0x10-byte header) whose id matches,
   or 0. */
void *r1c_BankFind(int id)
{
    char *e;
    for (e = r1c_PoolFind(r1c_bank283698, 0xB40, 0, 0); e != 0;
         e = r1c_PoolFind((R1cPool *)e, 0xB40, 0, 0)) {
        if (((R1cBankEnt *)e)->id == id)
            return e + 0x10;
    }
    return 0;
}

/* 0x00058190: finish the calling thread's background job: mark it done,
   release its handle, flush packets and end the thread. */
void r1c_JobFinish(void)
{
    R1cJob *j = (R1cJob *)r1c_JobCurrent();
    if (j != 0) {
        j->state = 3;
        j->thread = -1;
        if (j->handle != -1) {
            sub_001AA310(j->handle);
            j->handle = -1;
        }
        r1b_PktOp(0);
    }
    sub_001AD520();
}

/* 0x0005BE30: stop and clear every channel record owned by owner. */
void r1c_SndOwnerStop(void *owner)
{
    R1cChan *c;
    int n;
    if (owner == 0) return;
    for (c = r1c_chan3E5AD4, n = 32; n != 0; n--, c++) {
        if (c->owner == owner) {
            if (c->handle != -1)
                r1c_SlotStop(c->handle);
            c->handle = -1;
            c->owner = 0;
        }
    }
}
