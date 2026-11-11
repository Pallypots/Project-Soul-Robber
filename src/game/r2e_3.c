/* Area r2e, group 3: enemy behaviour helpers (0x00109170..0x0012828A). Names inferred. */
#include "r2e.h"

/* 0x00109170: once the target reaches 0.05, push the object with 0.5 and
   send event 3 to its part 5 unless that part is already in state 3. */
void r2e_PushPart5(void *o, R2eObj68 *t)
{
    R2eMdl6C *m;
    if (t->f68 >= 0.05f) {
        sub_000F3F00(o, 0.5f);
        if (!o)
            for (;;) ;
        m = sub_0001D960(o, 5);
        if (m->state6C != 3)
            sub_000F3D10(o, m, 3);
    }
}

/* 0x00100D50: put both boss parts into animation 0x27 and clear the
   controller timer (hang if anything is missing). */
void r2e_CtlReset(void)
{
    R2eCtl *c = r2e_ctl3F6128;
    if (!c)
        for (;;) ;
    if (!c->a8C)
        for (;;) ;
    sub_000832D0(c->a8C->p30, 0x27);
    sub_000832D0(r2e_ctl3F6128->b90->p30, 0x27);
    c->v9C = 0;
    c->fA0 = 0.0f;
}

/* 0x00109AC0: when the target is idle with a positive +0xBC and the actor
   has flag 0x18, zero its +0x50 and send event 2 (moving) or 0x1A to part 5.
   calls 0x00108B80 with ESI=o EDI=k */
void r2e_ActorStop(R2eActor *o, R2eActor *t)
{
    if (t->vA8 == 0 && t->fBC > 0.0f) {
        if (o->flags128 & 0x18) {
            o->f50 = 0.0f;
            r2e_Part5Event(o, t->f54 > 0.0f ? 2 : 0x1A);
        }
    }
}

/* 0x00114A30: move the actor +0x78 vector toward the body target and
   damp it by 0.95 of the move +0xE8, then clear body flag 0x8000. */
void r2e_ActorDamp(R2eActor *a, R2eMove *m)
{
    R2eBody *b = a->body278;
    sub_00145C90(a->v78, m->v20, b->v2C);
    sub_00145CD0(a->v78, a->v78, m->fE8 * 0.95f);
    b->flags4 &= ~0x8000u;
}

/* 0x00115D60: run state 0x15 (releasing a on success) and reset the
   body vector to (0, 0, 0, 1). */
void r2e_BodyReset(void *a, R2eActor *o)
{
    R2eBody *b;
    if (sub_001456E0(a, o, 0x15, 0) == 1)
        sub_0001D4E0(a);
    b = o->body278;
    b->v2C[2] = 0.0f;
    b->v2C[1] = 0.0f;
    b->v2C[0] = 0.0f;
    b->f38 = 1.0f;
}

/* 0x0012D2F0: test condition c (another actor of kind 5, or else kind 0xF,
   carries its mask), inverted when c->invC is zero.
   calls 0x0011FB40 with EAX=id EDI=self ESI=c->mask8 */
int r2e_CondOther(void *self, R2eCond *c)
{
    int r;
    if (r2e_FindOther(5, self, c->mask8))
        r = 1;
    else
        r = r2e_FindOther(0xF, self, c->mask8) != 0;
    if (c->invC)
        return r == 1;
    return r != 1;
}

/* 0x0010B550: set the actor +0xB4 timer to 98 frames worth of seconds and
   clear the seven values after it. */
void r2e_ActorTimerReset(void *unused, R2eActor *o)
{
    o->fB4 = r2e_frameSeconds * 98.0f;
    o->fC0 = 0.0f;
    o->fBC = 0.0f;
    o->fB8 = 0.0f;
    o->vC4[3] = 0.0f;
    o->vC4[2] = 0.0f;
    o->vC4[1] = 0.0f;
    o->vC4[0] = 0.0f;
}

/* 0x00115840: run state 0 (releasing a on success), reset the body
   vector to (0, 0, 0, 1) and set flags 0x70 at +0x4C. */
void r2e_BodyReset0(void *a, R2eActor *o)
{
    R2eBody *b;
    if (sub_001456E0(a, o, 0, 0) == 1)
        sub_0001D4E0(a);
    b = o->body278;
    b->v2C[2] = 0.0f;
    b->v2C[1] = 0.0f;
    b->v2C[0] = 0.0f;
    b->f38 = 1.0f;
    o->flags4C |= 0x70;
}

/* 0x00115C60: run state 0x13 (releasing a on success), reset the body
   vector to (0, 0, 0, 1) and add one exclamation point. */
void r2e_BodyReset13(void *a, R2eActor *o)
{
    R2eBody *b;
    if (sub_001456E0(a, o, 0x13, 0) == 1)
        sub_0001D4E0(a);
    b = o->body278;
    b->v2C[2] = 0.0f;
    b->v2C[1] = 0.0f;
    b->v2C[0] = 0.0f;
    b->f38 = 1.0f;
    Grade_AddExclamations(1);
}

/* 0x00116E40: run state 0x40 (releasing a on success), reset the body
   vector to (0, 0, 0, 1) and clear flag 0x20 of a. */
void r2e_BodyReset40(R2eActor *a, R2eActor *o)
{
    R2eBody *b;
    if (sub_001456E0(a, o, 0x40, 0) == 1)
        sub_0001D4E0(a);
    b = o->body278;
    b->v2C[2] = 0.0f;
    b->v2C[1] = 0.0f;
    b->v2C[0] = 0.0f;
    b->f38 = 1.0f;
    a->flags0C &= ~0x20u;
}

/* 0x0011AE60: when o +0x30 object is live, set (kind 0x3B) or clear body
   flag 0x80000000 of a and send event 0x15. */
void r2e_MarkKind3B(R2eObj30 *o, R2eActor *a)
{
    R2eBody *b;
    if (sub_000833E0(o->p30)) {
        b = a->body278;
        if (a->kind64 == 0x3B) {
            b->flags4 |= 0x80000000u;
            sub_00113040(o, a, 0x15);
        } else {
            b->flags4 &= 0x7FFFFFFFu;
            sub_00113040(o, a, 0x15);
        }
    }
}

/* 0x0012D9A0: move the actor +0x78 vector toward body +0x164, damp it by
   0.9 of the move +0xE8 and clear body flag 0x80000 at +0x0C. */
void r2e_ActorDamp164(R2eActor *a, R2eMove *m)
{
    R2eBody *b = a->body278;
    sub_00145C90(a->v78, m->v20, b->v164);
    sub_00145CD0(a->v78, a->v78, m->fE8 * 0.9f);
    b->flagsC &= ~0x80000u;
}

/* 0x001158A0: run state 0 (releasing a on success), reset the body
   vector to (0, 0, 0, 1), set flags 0x70 at +0x4C and +0x74 to 1. */
void r2e_BodyReset0b(void *a, R2eActor *o)
{
    R2eBody *b;
    if (sub_001456E0(a, o, 0, 0) == 1)
        sub_0001D4E0(a);
    b = o->body278;
    b->v2C[2] = 0.0f;
    b->v2C[1] = 0.0f;
    b->v2C[0] = 0.0f;
    b->f38 = 1.0f;
    o->flags4C |= 0x70;
    o->f74 = 1.0f;
}

/* 0x00115B80: run state 0x1B (releasing a on success), reset the body
   vector, set flags 0x70 at +0x4C and body flag 4. */
void r2e_BodyReset1B(void *a, R2eActor *o)
{
    R2eBody *b0 = o->body278;
    R2eBody *b;
    if (sub_001456E0(a, o, 0x1B, 0) == 1)
        sub_0001D4E0(a);
    b = o->body278;
    b->v2C[2] = 0.0f;
    b->v2C[1] = 0.0f;
    b->v2C[0] = 0.0f;
    b->f38 = 1.0f;
    o->flags4C |= 0x70;
    b0->flags4 |= 4;
}

/* 0x0012DCE0: is the distance from a to the range target (player for mode
   1, a itself for mode 2) within [min, max]?  Mode 3 is never in range. */
int r2e_InRange(uint8_t *a, int unused, R2eRange *r)
{
    uint8_t *t;
    float d;
    switch (r->mode0) {
    case 1:
        t = (uint8_t *)g_playerObj;
        break;
    case 2:
        t = a;
        break;
    case 3:
        return 0;
    default:
        for (;;) ;
    }
    if (t) {
        d = sub_001B2770(a + 0x60, t + 0x60);
        if (d >= r->f10 && r->f14 >= d)
            return 1;
    }
    return 0;
}

/* 0x0012F9F0: run state 0x15 (releasing a on success) and reset the body
   +0x164 vector to (0, 0, 0, 1). */
void r2e_BodyReset164(void *a, R2eActor *o)
{
    R2eBody *b;
    if (sub_001456E0(a, o, 0x15, 0) == 1)
        sub_0001D4E0(a);
    b = o->body278;
    b->v164[2] = 0.0f;
    b->v164[1] = 0.0f;
    b->v164[0] = 0.0f;
    b->v164[3] = 1.0f;
}

/* 0x00109E40: release the target (+0xA8 = 0), set the actor angle to pi,
   arm a quarter-turn timer and clear the actor flags 0x44 and 0x20. */
void r2e_ActorFlip(R2eActor *o, R2eActor *t)
{
    t->vA8 = 0;
    o->f50 = 3.14159274f;
    t->vC4[0] = r2e_frameSeconds * 0.785398185f;
    t->vC4[2] = 0.0f;
    sub_000F3B00(o, 0x44);
    sub_000F3B30(o, 0x20);
    sub_000F3F00(o, 0.0f);
}

/* 0x001155C0: prepare a for o, run state 1 (releasing a on success),
   reset the body vector and set flags 0x70 at +0x4C.
   calls 0x00115000 with EAX=o */
void r2e_BodyReset1(void *a, R2eActor *o)
{
    R2eBody *b;
    sub_00115000(a, o);
    if (sub_001456E0(a, o, 1, 0) == 1)
        sub_0001D4E0(a);
    b = o->body278;
    b->v2C[2] = 0.0f;
    b->v2C[1] = 0.0f;
    b->v2C[0] = 0.0f;
    b->f38 = 1.0f;
    o->flags4C |= 0x70;
}

/* 0x00116040: run state 0 (releasing a on success), reset the body
   vector, set flags 0x70 at +0x4C and body flag 4. */
void r2e_BodyReset0c(void *a, R2eActor *o)
{
    R2eBody *b0 = o->body278;
    R2eBody *b;
    if (sub_001456E0(a, o, 0, 0) == 1)
        sub_0001D4E0(a);
    b = o->body278;
    b->v2C[2] = 0.0f;
    b->v2C[1] = 0.0f;
    b->v2C[0] = 0.0f;
    b->f38 = 1.0f;
    o->flags4C |= 0x70;
    b0->flags4 |= 4;
}

/* 0x00116280: run state 0x33 (releasing a on success), reset the body
   vector and set flags 0xD of a when body flag 0x10 is set. */
void r2e_BodyReset33(R2eActor *a, R2eActor *o)
{
    R2eBody *b0 = o->body278;
    R2eBody *b;
    if (sub_001456E0(a, o, 0x33, 0) == 1)
        sub_0001D4E0(a);
    b = o->body278;
    b->v2C[2] = 0.0f;
    b->v2C[1] = 0.0f;
    b->v2C[0] = 0.0f;
    b->f38 = 1.0f;
    if (b0->flags4 & 0x10)
        a->v10 |= 0xD;
}

/* 0x0011D580: when o +0x30 object is live, clear its flag 4, pick event 4
   (body flag 0x40 without 0x10) or 5 (zeroing a +0x74), set a step 2 and
   send the event. */
void r2e_HitReact(R2eActor *o, R2eActor *a)
{
    uint32_t f;
    int k;
    if (sub_000833E0(o->p30)) {
        o->v10 &= ~4u;
        f = a->body278->flags4;
        if (!(f & 0x10) && (f & 0x40)) {
            k = 4;
        } else {
            k = 5;
            a->f74 = 0.0f;
        }
        sub_00113480(a, 2);
        sub_00113040(o, a, k);
    }
}

/* 0x0012EEB0: run state 0 (releasing a on success), reset the body
   +0x164 vector to (0, 0, 0, 1) and set flags 0x70 at +0x4C. */
void r2e_BodyReset164b(void *a, R2eActor *o)
{
    R2eBody *b;
    if (sub_001456E0(a, o, 0, 0) == 1)
        sub_0001D4E0(a);
    b = o->body278;
    b->v164[2] = 0.0f;
    b->v164[1] = 0.0f;
    b->v164[0] = 0.0f;
    b->v164[3] = 1.0f;
    o->flags4C |= 0x70;
}

/* 0x00115900: run state 0 (releasing a on success), reset the body
   vector, set flags 0x70 at +0x4C and +0x74 to 2. */
void r2e_BodyReset0d(void *a, R2eActor *o)
{
    R2eBody *b;
    if (sub_001456E0(a, o, 0, 0) == 1)
        sub_0001D4E0(a);
    b = o->body278;
    b->v2C[2] = 0.0f;
    b->v2C[1] = 0.0f;
    b->v2C[0] = 0.0f;
    b->f38 = 1.0f;
    o->flags4C |= 0x70;
    o->f74 = 2.0f;
}

/* 0x0012CA30: step 1 when a passed 5.0, then while a +0x30 object is live
   raise event 1 (body flag 0x10000000 or 15 of 16 random draws) or 0x11.
   calls 0x0011F2B0 with EDI=a EBX=k */
void r2e_RandEvent(R2eActor *a, R2eActor *o)
{
    R2eBody *b = o->body278;
    int k;
    if (sub_00145780(a, 5.0f))
        sub_00113480(o, 1);
    if (sub_000833E0(a->p30)) {
        if ((b->flags4 & 0x10000000) || (sub_001C7EE1() & 0xF))
            k = 1;
        else
            k = 0x11;
        sub_0011F2B0(a, o, k);
    }
}

/* 0x0012EC00: prepare a for o, run state 1 (releasing a on success),
   reset the body +0x164 vector and set flags 0x70 at +0x4C.
   calls 0x0012E190 with EAX=o */
void r2e_BodyReset164c(void *a, R2eActor *o)
{
    R2eBody *b;
    sub_0012E190(a, o);
    if (sub_001456E0(a, o, 1, 0) == 1)
        sub_0001D4E0(a);
    b = o->body278;
    b->v164[2] = 0.0f;
    b->v164[1] = 0.0f;
    b->v164[0] = 0.0f;
    b->v164[3] = 1.0f;
    o->flags4C |= 0x70;
}

/* 0x0012EF20: run state 0 (releasing a on success), reset the body
   +0x164 vector, set flags 0x70 at +0x4C and +0x74 to 1. */
void r2e_BodyReset164d(void *a, R2eActor *o)
{
    R2eBody *b;
    if (sub_001456E0(a, o, 0, 0) == 1)
        sub_0001D4E0(a);
    b = o->body278;
    b->v164[2] = 0.0f;
    b->v164[1] = 0.0f;
    b->v164[0] = 0.0f;
    b->v164[3] = 1.0f;
    o->flags4C |= 0x70;
    o->f74 = 1.0f;
}

/* 0x0010B0E0: as 0x0010B550, then set +0xC0 to +0xD4 times the frame
   time. */
void r2e_ActorTimerReset2(void *unused, R2eActor *o)
{
    o->fB4 = r2e_frameSeconds * 98.0f;
    o->fC0 = 0.0f;
    o->fBC = 0.0f;
    o->fB8 = 0.0f;
    o->vC4[3] = 0.0f;
    o->vC4[2] = 0.0f;
    o->vC4[1] = 0.0f;
    o->vC4[0] = 0.0f;
    o->fC0 = o->fD4 * r2e_frameSeconds;
}

/* 0x00113D90: tear down the type-2 effect set: notify, free its table,
   stop job 0x00112A80, release the 0x003F616C object and clear the six
   unit records. */
void r2e_FxSetFree(void)
{
    if (r2e_g3F74F4) {
        sub_000ED560(2);
        sub_00020170(r2e_g3F74F0);
        r2e_g3F74F0 = 0;
        r2e_g3F74F4 = 0;
        sub_000ED9E0(sub_00112A80);
        sub_00053880(r2e_g3F616C);
        r2e_g3F616C = 0;
        r2e_units3F63E8[0].v0 = 0;
        r2e_units3F63E8[1].v0 = 0;
        r2e_units3F63E8[2].v0 = 0;
        r2e_units3F63E8[3].v0 = 0;
        r2e_units3F63E8[4].v0 = 0;
        r2e_units3F63E8[5].v0 = 0;
    }
}

/* 0x00117E60: step 1 when a passed 9.0, then while a +0x30 object is live
   reset every kind-1 actor and send event 1.
   calls 0x00117580 with EDI=o */
void r2e_ResetKind1(R2eActor *a, R2eActor *o)
{
    void *e;
    if (sub_00145780(a, 9.0f))
        sub_00113480(o, 1);
    if (sub_000833E0(a->p30)) {
        for (e = sub_000EDC20(2, 1); e; e = sub_000EDC20(-1, -1))
            sub_0013DF90(e, 0);
        sub_00117580(a, 1, o);
    }
}

/* 0x0011C8E0: when o +0x30 object is live, send event 3 if the 0x0031B0C4
   test passes, else event 5 with a +0x74 of 60 frames; set a flag 0x10. */
void r2e_TestEvent(R2eActor *o, R2eActor *a)
{
    int k;
    if (sub_000833E0(o->p30)) {
        k = 3;
        if (!r2e_fn31B0C4(o, a, r2e_vec279598)) {
            a->f74 = 60.0f / r2e_frameUnits * r2e_frameSeconds;
            k = 5;
        }
        a->flags4C |= 0x10;
        sub_00113040(o, a, k);
    }
}

/* 0x0012FC30: run state 0x33 (releasing a on success), reset the body
   +0x164 vector and set flags 0xD of a when body flag 0x20 at +0x0C is set. */
void r2e_BodyReset164e(R2eActor *a, R2eActor *o)
{
    R2eBody *b0 = o->body278;
    R2eBody *b;
    if (sub_001456E0(a, o, 0x33, 0) == 1)
        sub_0001D4E0(a);
    b = o->body278;
    b->v164[2] = 0.0f;
    b->v164[1] = 0.0f;
    b->v164[0] = 0.0f;
    b->v164[3] = 1.0f;
    if (b0->flagsC & 0x20)
        a->v10 |= 0xD;
}

/* 0x0010F010: drop the attach flag of every entry (count from key8),
   then detach and remove the object's part 0x0D; returns 1 (hang on a
   null object). */
int r2e_EntsRelease(R2eEnt *o)
{
    int i;
    void *m;
    if (!o)
        for (;;) ;
    sub_0001D960(o, 0xD);
    for (i = 0; i < sub_000F3140(o->key8); i++) {
        if (o[i].flagsC & 1) {
            o[i].flagsC &= ~1u;
            sub_0001EB80(&o[i]);
        }
    }
    m = sub_0001D960(o, 0xD);
    sub_000EE270(m);
    sub_0001D910(o, m);
    return 1;
}

/* 0x0011AB30: send hit event 0x12/0x13, add an exclamation point and
   raise (body flag 0x20000000) or lower the body gauge, flagging a. */
void r2e_HitGauge(R2eActor *a, R2eActor *o)
{
    R2eBody *b = o->body278;
    sub_00113090(a, o, (o->b22 & 1) + 0x12);
    Grade_AddExclamations(1);
    if (b->flags4 & 0x20000000) {
        sub_00113C60(b->v14, 40.0f, 255.0f);
        return;
    }
    sub_00113CB0(b->v14, 20.0f, 0.0f);
    if (o->b20 & 1) {
        a->v10 |= 6;
        o->v58 = 1;
    }
}

/* 0x00109690: while the target's +0xBC is positive, push the actor by
   (target +0x68 - 0.3) * 5/3 and, with actor flag 0x18, send event 0x17
   to part 5 unless already in that state. */
void r2e_ActorPush17(R2eActor *o, R2eActor *t)
{
    R2eMdl6C *m;
    if (t->fBC > 0.0f)
        sub_000F3F00(o, (t->f68 - 0.3f) * 1.66666663f);
    if (t->fBC > 0.0f && (o->flags128 & 0x18)) {
        m = sub_0001D960(o, 5);
        if (m->state6C != 0x17)
            sub_000F3D10(o, m, 0x17);
    }
}

/* 0x001125B0: command state machine: in state 0 start command idx
   (0..16) of the table at 0x00279330 unless it is 0x21D or already
   loaded; -1 on a bad index or no effect set, 1 in unknown states. */
int r2e_CmdStart(int idx)
{
    int id;
    switch (r2e_state3F7500) {
    case 0:
        if (!r2e_g3F74F4 || idx < 0 || idx >= 0x11)
            return -1;
        id = r2e_cmds279330[idx].id;
        if (id == 0x21D || sub_0004F6D0(id))
            return 0;
        sub_000512D0(id, sub_00053AB0(sub_0004F680(id), 0, 0x10E));
        r2e_state3F7500 = 0;
        return 0;
    case 1:
        r2e_state3F7500 = 0;
        return 0;
    }
    return 1;
}

/* 0x00115BE0: run state 0x38 (releasing a on success), reset the body
   vector and set body +0x44 to a random 10..20. */
void r2e_BodyReset38(void *a, R2eActor *o)
{
    R2eBody *b0 = o->body278;
    R2eBody *b;
    if (sub_001456E0(a, o, 0x38, 0) == 1)
        sub_0001D4E0(a);
    b = o->body278;
    b->v2C[2] = 0.0f;
    b->v2C[1] = 0.0f;
    b->v2C[0] = 0.0f;
    b->f38 = 1.0f;
    b0->f44 = ((float)sub_001C7EE1() * 3.05185094e-05f + 1.0f) * 10.0f;
}

/* 0x0012B990: spawn effect 0xF7 at o, notify it (0xE when a flag bit 0 is
   set, else 0), flag both and reset a's step 6. */
void r2e_HitStep6(R2eActor *o, R2eActor *a)
{
    R2eStep *s;
    sub_000494D0(0xF7, (uint8_t *)o + 0x60, 0);
    sub_00036750(o, (a->b20 & 1) ? 0xE : 0);
    o->v10 |= 0xD;
    a->flags4C &= 0xFEFFFF8Fu;
    s = sub_00113400(a, 6);
    s->f10 = 1.0f;
    s->f14 = 0.0f;
    s->f18 = 0.0f;
    s->f1C = 0.0f;
    if (s->v0)
        s->v0 = 2;
}

/* 0x0012F8F0: run state 0x2B (releasing a on success), reset the body
   +0x164 vector, set body flag 0x1000000 at +0x0C and +0x188 to 3. */
void r2e_BodyReset2B(void *a, R2eActor *o)
{
    R2eBody *b0 = o->body278;
    R2eBody *b;
    if (sub_001456E0(a, o, 0x2B, 0) == 1)
        sub_0001D4E0(a);
    b = o->body278;
    b->v164[2] = 0.0f;
    b->v164[1] = 0.0f;
    b->v164[0] = 0.0f;
    b->v164[3] = 1.0f;
    b0->flagsC |= 0x1000000;
    b0->f188 = 3.0f;
}

/* 0x0010B060: reset the target's timer block, zero the actor's +0x50 and
   free the target's +0x94 effect. */
void r2e_TimerResetFree(R2eActor *a, R2eActor *o)
{
    o->fB4 = r2e_frameSeconds * 98.0f;
    o->fC0 = 0.0f;
    o->fBC = 0.0f;
    o->fB8 = 0.0f;
    o->vC4[3] = 0.0f;
    o->vC4[2] = 0.0f;
    o->vC4[1] = 0.0f;
    o->vC4[0] = 0.0f;
    a->f50 = 0.0f;
    if (o->p94) {
        sub_00033A70(o->p94);
        o->p94 = 0;
    }
}

/* 0x0010B4C0: reset the target's timer block, zero the actor's +0x50,
   set flag 4, clear flag 0x20 and push it with 0.5. */
void r2e_TimerResetPush(R2eActor *o, R2eActor *t)
{
    t->fB4 = r2e_frameSeconds * 98.0f;
    t->fC0 = 0.0f;
    t->fBC = 0.0f;
    t->fB8 = 0.0f;
    t->vC4[3] = 0.0f;
    t->vC4[2] = 0.0f;
    t->vC4[1] = 0.0f;
    t->vC4[0] = 0.0f;
    o->f50 = 0.0f;
    sub_000F3B30(o, 4);
    sub_000F3B00(o, 0x20);
    sub_000F3F00(o, 0.5f);
}

/* 0x0010BAC0: reset the target's timer block with +0xCC = 16 pi, release
   it and set the actor flags 4 and 0x20. */
void r2e_TimerResetSpin(R2eActor *o, R2eActor *t)
{
    t->fB4 = r2e_frameSeconds * 98.0f;
    t->fC0 = 0.0f;
    t->fBC = 0.0f;
    t->fB8 = 0.0f;
    t->vC4[3] = 0.0f;
    t->vC4[1] = 0.0f;
    t->vC4[0] = 0.0f;
    t->vC4[2] = 50.2654839f;
    t->vA8 = 0;
    sub_000F3B00(o, 4);
    sub_000F3B30(o, 0x20);
}

/* 0x001092F0: at strength 1 attach effect 3 once; at strength 4 hide the
   actor, return part 5 to state 0 and set flag 3. */
void r2e_ActorStrength(R2eActor *o, R2eActor *t)
{
    R2eMdl6C *m;
    if (t->f68 >= 1.0f && !t->p94)
        t->p94 = sub_00109050(o, 3);
    if (t->f68 >= 4.0f) {
        sub_0001D700(o);
        if (!o)
            for (;;) ;
        m = sub_0001D960(o, 5);
        if (m->state6C)
            sub_000F3D10(o, m, 0);
        sub_000F3B70(o, 3);
    }
}

/* 0x00103FE0: screen intro steps: step 0 waits for the node and starts
   cue 0x33, step 1 counts up and fires cue 0x0E after 0.4 s. */
void r2e_ScrIntro(void *node)
{
    R2eScn *s = r2e_scr3F6130;
    switch (s->step1A8) {
    case 0:
        if (sub_000F5D00(node)) {
            sub_00101280(0x33);
            s->step1A8++;
            s->t1AC = 0.0f;
        }
        break;
    case 1:
        if (s->t1AC > 0.4f) {
            sub_00101240(0xE);
            return;
        }
        s->t1AC += r2e_frameSeconds;
        break;
    }
}

/* 0x0012F970: run state 0x14 (releasing a on success), reset the body
   +0x164 vector, flag a and attach effect 0x174 and notify code 2 to it. */
void r2e_BodyReset14(R2eActor *a, R2eActor *o)
{
    R2eBody *b;
    if (sub_001456E0(a, o, 0x14, 0) == 1)
        sub_0001D4E0(a);
    b = o->body278;
    b->v164[2] = 0.0f;
    b->v164[1] = 0.0f;
    b->v164[0] = 0.0f;
    b->v164[3] = 1.0f;
    a->v10 |= 0x10;
    o->v6C = sub_000494D0(0x174, (uint8_t *)a + 0x60, 0);
    o->v70 = sub_00036750(a, 2);
}
