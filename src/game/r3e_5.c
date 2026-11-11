/* Area r3e: game functions in 0x00160000..0x0017FFFF (r3e_5). Names inferred. */
#include "r3e.h"

/* 0x00173EC0: add b's +0x54 step to a; once b's +0x58 timer has run out reset b (+0x4C = 2,
   +0x50 = 0, +0x54 = 0) and run state-enter handler 2 on (a, b). */
void r3e_Step173EC0(R3eObj *a, R3eObj *b)
{
    a->f54 += b->f54;
    if (b->f58 <= 0.0f) {
        b->i4C = 2;
        b->state50 = 0;
        b->f54 = 0.0f;
        r3_fsmEnter32B1B0[2](a, b);
    }
}

/* 0x00173610: clear a's flag 4 and b's flag 1, play animation 3 (10 for kind 9 with b flag
   0x1000) and set b's mode +0xB8 to 2. calls 0x00172C90 with EAX=b ESI=a EDI=anim. */
void r3e_Anim173610(R3eObj *a, R3eObj *b)
{
    int k = 0;

    a->flags10 &= ~4u;
    b->flags5C &= ~1u;
    if (a->i08 == 9 && (b->flags5C & 0x1000))
        k = 7;
    k += 3;
    sub_00172C90(a, b, k);
    b->iB8 = 2;
}

/* 0x00173660: set a's flag 4, play animation 5 (12 for kind 9 with b flag 0x1000), set b's mode
   +0xB8 to 0 and b's flag 1. calls 0x00172C90 with EAX=b ESI=a EDI=anim. */
void r3e_Anim173660(R3eObj *a, R3eObj *b)
{
    int k = 0;

    a->flags10 |= 4;
    if (a->i08 == 9 && (b->flags5C & 0x1000))
        k = 7;
    k += 5;
    sub_00172C90(a, b, k);
    b->iB8 = 0;
    b->flags5C |= 1;
}

/* 0x0017B010: spawn the effect chosen by 0x0017AF00 at a (velocity b+0x78), then release node 2
   of b and its effect handle. regargs: a=EAX b=EDI; calls 0x0017AF00 with EAX=b (a on the stack). */
void r3e_Spawn17B010(R3eObj *a, R3eObj *b)
{
    R3eNode *n;

    sub_000A8ED0(sub_0017AF00(b, a), a->pos60, b->v78, 0);
    n = sub_001133E0(b, 2);
    if (n != 0) {
        if (n->i14 >= 0)
            sub_000A7950(n->i14);
        sub_00113370(b, n);
    }
}

/* 0x00169DA0: mark every active pool entry other than self with flag 0x20.
   regargs: self=ESI. */
void r3e_MarkOthers169DA0(R3ePool20 *self)
{
    int i;

    for (i = 0; i < 16; i++) {
        if ((b16_pool20[i].flags & 1) && &b16_pool20[i] != self)
            b16_pool20[i].flags |= 0x20;
    }
}

/* 0x00170400: restart obj's task: find the task record of kind (obj kind mod 10) + 6 (hangs if
   none), reset it (0x0016FE00), keep obj's kind and set its +0x04 mode to 8. regargs: obj=EAX. */
void r3e_Restart170400(R3eObj *obj)
{
    int kind = obj->i08;
    int want = kind;
    int n, i;

    if (kind >= 10)
        want -= 10;
    n = *b16_task3F92E8;
    want += 6;
    for (i = 0; i < n; i++) {
        if (b16_taskId3F92EC[i].kind08 == want)
            break;
    }
    if (i >= n)
        for (;;) ;
    sub_0016FE00(&b16_taskId3F92EC[i]);
    obj->i08 = kind;
    obj->type04 = 8;
}

/* 0x0016E990: on message 5 (state 0x11) or 0x24 (state 0xF, 0x10 or 0x12 by 0x000CF6B0) switch
   obj's component while its flags have 0x100000 without 0x200000; returns 0.
   calls 0x0016C820 with EAX=obj EDI=obj (state on the stack). */
int r3e_OnMsg16E990(void *unused, R3eObj *obj, int *msg)
{
    int states[3];
    int st;

    if ((*(uint32_t *)obj->p74 & 0x100000) && !(*(uint32_t *)obj->p74 & 0x200000)) {
        st = 0x11;
        if (*msg != 5) {
            if (*msg != 0x24)
                return 0;
            states[0] = 0xF;
            states[1] = 0x10;
            states[2] = 0x12;
            st = states[Stats_Get1B8()];
        }
        r3_SetState16C820(obj, obj, st);
    }
    return 0;
}

/* 0x00178860: while act flag 1 is set update obj (0x000C56B0) and send it to state 3 when its
   +0x128 flags have any of 0x1E or it is more than 80 away from the player. */
void r3e_Watch178860(R3eObj *obj, R3eObj *act)
{
    if (!(act->flags278 & 1))
        return;
    sub_000C56B0(obj);
    if (obj->flags128 & 0x1E)
        sub_00113040(obj, act, 3);
    if (sub_001B2770(obj->pos60, ((R3eObj *)g_playerObj)->pos60) > 80.0f)
        sub_00113040(obj, act, 3);
}

/* 0x001734F0: set a's flags 0x45, detach its nodes, register it with the scene (0xE, 5, 0x11),
   play animation 0xD (0x14 for kind 9 with b flag 0x1000), set b's mode +0xB8 to 0, b's flag 1
   and b's +0x58 timer to 5. calls 0x00172C90 with EAX=b ESI=a EDI=anim. */
void r3e_Anim1734F0(R3eObj *a, R3eObj *b)
{
    int k = 0;

    a->flags10 |= 0x45;
    sub_0001EB80(a);
    sub_0001E9B0(r3_ctx42C8E4, a, 0xE, 5, 0x11);
    if (a->i08 == 9 && (b->flags5C & 0x1000))
        k = 7;
    k += 0xD;
    sub_00172C90(a, b, k);
    b->iB8 = 0;
    b->flags5C |= 1;
    b->f58 = 5.0f;
}

/* 0x00170200: map message *msg to a state of obj's kind-10 component (hangs if missing): 6, 7 or
   5 by message, none for message 14; ignored in states 4 and 5 or when already in it. Returns 1
   when the message was taken. */
int r3e_OnMsg170200(R3eObj *obj, int *msg)
{
    R3eObj *c = sub_0001D960(obj, 10);
    int st;

    if (c == 0)
        for (;;) ;
    if (c->state50 == 4 || c->state50 == 5)
        return 0;
    st = -1;
    switch (*msg) {
    case 1: case 2: case 3: case 5: case 6: case 7: case 8: case 9: case 10: case 11:
    case 29: case 34: case 35: case 36:
        st = 6;
        break;
    case 14:
        break;
    case 26: case 28:
        st = 7;
        break;
    case 30: case 31: case 32: case 33:
        st = 5;
        break;
    default:
        return 0;
    }
    if (c->state50 == st)
        return 0;
    if (st >= 0) {
        c->state50 = st;
        c->f54 = 0.0f;
        c->f58 = 0.0f;
    }
    return 1;
}

/* 0x001740F0: map message *msg to state 7 or 8 of obj's kind-8 component (hangs if missing);
   ignored for kinds 7, 0x17 and 0x10..0x14 and in component states 3, 4 and 9. Returns 1 when
   taken. calls 0x00172B50 with EAX=state ECX=component (obj on the stack). */
int r3e_OnMsg1740F0(R3eObj *obj, int *msg)
{
    R3eObj *c = sub_0001D960(obj, 8);
    int st;

    if (c == 0)
        for (;;) ;
    if (obj->i08 == 0x17 || obj->i08 == 7 || (obj->i08 >= 0x10 && obj->i08 <= 0x14))
        return 0;
    if (c->i4C == 4 || c->i4C == 3 || c->i4C == 9)
        return 0;
    switch (*msg) {
    case 1: case 2: case 3: case 5: case 6: case 7: case 10: case 11: case 14: case 29:
    case 34: case 35: case 36:
        st = 7;
        break;
    case 30: case 31: case 32:
        st = 8;
        break;
    default:
        return 0;
    }
    if (c->i4C != st)
        r3_FsmEnter172B50(st, c, obj);
    return 1;
}

/* 0x0017CEC0: nonzero when actor (3, 7) is selected, its animation kind is 0x23..0x25 or 0x27 and
   the player lies within 60 degrees of its facing. */
int r3e_Facing17CEC0(void)
{
    R3eObj *a = sub_000E23F0(3, 7);
    int k = ((R3eObj *)sub_000E23F0(3, 7))->pa30->kind08;
    float ang;

    if ((k == 0x23 || k == 0x24 || k == 0x25 || k == 0x27) && sub_000CB9B0() == a) {
        ang = sub_000F7720(a, ((R3eObj *)g_playerObj)->pos60);
        if (!(ang > 1.0471976f) && !(-1.0471976f > ang))
            return 1;
    }
    return 0;
}

/* 0x0017FF30: clear the three records at 0x003FE0C0 (three words and three floats) and continue
   in 0x0017EF30. */
void r3e_Clear17FF30(void)
{
    int i;

    for (i = 0; i < 3; i++) {
        r3e_recs3FE0C0[i].i00 = 0;
        r3e_recs3FE0C0[i].i04 = 0;
        r3e_recs3FE0C0[i].i08 = 0;
        r3e_recs3FE0C0[i].f40 = 0.0f;
        r3e_recs3FE0C0[i].f1C = 0.0f;
        r3e_recs3FE0C0[i].f20 = 0.0f;
    }
    sub_0017EF30();
}

/* 0x0016BF00: two-step state: first set a's +0x50 to 30 degrees, reset it (0x00035D80), set b's
   block rate to 0.02, arm b's +0x5C timer for 60 frames and clear a's flags 0xC0; then once the
   timer has run out switch to state 2. */
void r3e_State16BF00(R3eObj *a, R3eObj *b)
{
    R3eBlk74 *blk = b->b74;

    switch (b->i54) {
    case 0:
        a->f50 = 0.5235988f;
        sub_00035D80(a, 0, 0);
        blk->f04 = 0.02f;
        b->f5C = r3e_frameSeconds * 60.0f;
        a->flags0C &= ~0xC0u;
        b->i54++;
        /* fall through */
    case 1:
        if (b->f5C < 0.0f)
            sub_001671D0(a, b, 2);
        break;
    }
}

/* 0x0017BB40: unless the player is more than 160 degrees off obj's facing, turn obj's yaw +0x54
   toward the opposite direction by at most 2 degrees per call. */
void r3e_TurnAway17BB40(R3eObj *obj)
{
    float a = sub_00113200(obj, ((R3eObj *)g_playerObj)->pos60);

    if (sub_001A3F30(a) <= 2.792527f) {
        if (a > 0.0f)
            a -= 3.1415927f;
        else if (0.0f > a)
            a += 3.1415927f;
        if (a > 0.034906585f)
            a = 0.034906585f;
        else if (-0.034906585f > a)
            a = -0.034906585f;
        obj->f54 += a;
    }
}

/* 0x0016F6F0: reset the task table pointers, set up the two slots of each component holder
   (kinds 10/0xD and 0xB/0xD) and clear the sound request state. */
void r3e_InitHolds16F6F0(void)
{
    R3eHold78 *a;
    R3eHold88 *b;

    b16_task3F92E8 = 0;
    b16_taskId3F92EC = 0;
    r3e_i3F92F0 = 0;
    r3e_i3F92F4 = 0;
    r3e_i3F92F8 = 0;
    r3e_i3F92FC = 0;
    for (a = r3e_holds3F8CE8; a < r3e_holds3F8CE8 + 6; a++) {
        sub_0001D8B0(a->slot00, 10);
        sub_0001D8B0(a->slot10, 0xD);
    }
    for (b = r3e_holds3F8FB8; b < r3e_holds3F8FB8 + 6; b++) {
        sub_0001D8B0(b->slot00, 0xB);
        sub_0001D8B0(b->slot10, 0xD);
    }
    r3d_i3F9300 = 0;
}
