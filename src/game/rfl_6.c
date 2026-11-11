/* Area rfl, group 6: event-script opcode handlers (0x000DA3D0..0x000DD7A0). Names inferred. */
#include "rfl.h"

/* 0x000DA3D0: switch on script variable 0x3EE6C0 through a table of n
   16-bit offsets; out of range skips the table. */
int rfl_Op_SwitchVar(RflScript *s)
{
    int n = s->pc[0];
    int v = sub_000DFE00();
    uint8_t *pc;
    if (v > n)
        return (n * 2 + 2) | 0x2000;
    pc = s->pc;
    s->pc = pc + RFL_RD16(pc + v * 2 + 1) + v * 2 + 1;
    return 0x1000;
}

/* 0x000DA9E0: set node (b0, b1) playing animation b2 (restart when it is
   already current) and wait until it is active. */
int rfl_Op_NodeAnim(RflScript *s)
{
    uint8_t *pc = s->pc;
    int a = pc[1];
    int b = pc[0];
    int anim = pc[2];
    RflNode *n;
    RflAnimComp *c;
    af0_SetVar3EDCF0(anim);
    n = sub_000DE170(b, a);
    if (n) {
        c = (RflAnimComp *)sub_0001D960(n, 8);
        if (!c)
            for (;;) ;
        if (sub_00083120(n->anim30, anim)) {
            if (c->anim60 == anim) {
                sub_000832D0(n->anim30, -1);
            } else {
                sub_000832D0(n->anim30, anim);
                c->anim60 = anim;
            }
            if (n->anim30->cur8 != c->anim60)
                for (;;) ;
            c->t64 = 0.0f;
            sub_0001D4E0(n);
        }
    }
    return 0x2003;
}

/* 0x000DC1B0: wait a random time between two float operands (seconds,
   converted to frames). */
int rfl_Op_WaitRandom(RflScript *s)
{
    uint8_t *pc = s->pc;
    RflBits lo, hi;
    lo.u = RFL_RD32(pc);
    hi.u = RFL_RD32(pc + 4);
    s->wait50 = sub_000DE2F0(lo.f, hi.f) * rfl_fps42C964;
    return 0x2008;
}

/* 0x000DC210: jump through a random entry of a table of n 16-bit offsets. */
int rfl_Op_JumpRandom(RflScript *s)
{
    int n = s->pc[0];
    int i;
    uint8_t *pc;
    if (n)
        n--;
    i = (int)(sub_000DE2F0(0.0f, (float)n) + 0.5f);
    pc = s->pc;
    s->pc = pc + RFL_RD16(pc + i * 2 + 1) + i * 2 + 1;
    return 0x1000;
}

/* 0x000DCEE0: jump by the 16-bit operand while the float at 0x0037DC54 is
   positive. */
int rfl_Op_JumpIfPositive(RflScript *s)
{
    uint8_t *pc;
    if (a12_GetFloat37DC54() > 0.0f) {
        pc = s->pc;
        s->pc = pc + RFL_RD16(pc);
        return 0x4000;
    }
    return 0x2002;
}

/* 0x000DD740: call 0x00019350 with a time operand (seconds to frames) and
   a 32-bit operand. */
int rfl_Op_19350(RflScript *s)
{
    uint8_t *pc = s->pc;
    RflBits t;
    t.u = RFL_RD32(pc);
    sub_00019350(RFL_FTOI(rfl_fps42C964 * t.f), RFL_RD32(pc + 4));
    return 0x2008;
}
