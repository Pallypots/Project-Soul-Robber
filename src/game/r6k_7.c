/* Area r6k: Jack action states (r6k_7). Names inferred. */
#include "r6k.h"

/* 0x000BE260: another of Jack's action states. Clears the velocity
   +0x110..+0x118. Step 0 clears flag 0x800 and sets 0x68000001, calls
   0x000193C0, starts effect 0xB at 80.0 (0x00019370) when +0xD4 is 1, moves
   on with animation 6 and 0x000CB990(8.0). Step 1 waits for the timer
   (0x000CF070), then 0x000193C0 and 0x000C53B0 and clears flag 0x40000000.
   Step 8 sets 0x000CFF90(j, 1, 2.0), waits for the timer, then
   0x000D0200(j, 0, 0), animation 0 and clears flags 0x40000002. Steps 1
   and 8 then go to state 7 when Jack is active (0x000CF1A0 > 0), else to
   state 1. */
void r6k_JackActionBE260(R6kJack *j)
{
    int active;

    j->vel110[2] = 0.0f;
    j->vel110[1] = 0.0f;
    j->vel110[0] = 0.0f;
    switch (j->subE0) {
    case 0:
        j->flags150 = (j->flags150 & ~0x800u) | 0x68000001;
        sub_000193C0();
        if (j->unkD4 == 1)
            sub_00019370(0xB, 80.0f);
        j->subE0++;
        j->anim12C = 6;
        sub_000CB990(j, 8.0f);
        return;
    case 1:
        if (PlayerObj_TimerDone((PlayerObj *)j) == 0)
            return;
        sub_000193C0();
        sub_000C53B0(j);
        j->flags150 &= 0xBFFFFFFF;
        active = PlayerObj_IsActive((PlayerObj *)j);
        break;
    case 8:
        sub_000CFF90(j, 1, 2.0f);
        if (PlayerObj_TimerDone((PlayerObj *)j) == 0)
            return;
        sub_000D0200(j, 0, 0);
        active = PlayerObj_IsActive((PlayerObj *)j);
        j->anim12C = 0;
        j->flags150 &= 0xBFFFFFFD;
        break;
    default:
        return;
    }
    if (active > 0)
        sub_000BD4D0(j, 7);
    else
        sub_000BD4D0(j, 1);
}

/* 0x000C22D0: a variant of the action state at 0x000BE260. Step 0 also
   clears the timer +0xE8 and uses animation 0x206. Step 8 then goes to state
   7 while Jack is active (0x000CF1A0 > 0), else to state 1; step 1 goes to
   state 1 while active, else to state 6. */
void r6k_JackActionC22D0(R6kJack *j)
{
    j->vel110[2] = 0.0f;
    j->vel110[1] = 0.0f;
    j->vel110[0] = 0.0f;
    switch (j->subE0) {
    case 0:
        j->flags150 = (j->flags150 & ~0x800u) | 0x68000001;
        sub_000193C0();
        if (j->unkD4 == 1)
            sub_00019370(0xB, 80.0f);
        j->subE0++;
        j->anim12C = 0x206;
        j->timerE8 = 0.0f;
        sub_000CB990(j, 8.0f);
        break;
    case 8:
        sub_000CFF90(j, 1, 2.0f);
        if (PlayerObj_TimerDone((PlayerObj *)j) == 0)
            break;
        sub_000D0200(j, 0, 0);
        j->anim12C = 0;
        j->flags150 &= 0xBFFFFFFD;
        if (PlayerObj_IsActive((PlayerObj *)j) > 0)
            sub_000BD4D0(j, 7);
        else
            sub_000BD4D0(j, 1);
        break;
    case 1:
        if (PlayerObj_TimerDone((PlayerObj *)j) == 0)
            break;
        sub_000C53B0(j);
        j->flags150 &= 0xBFFFFFFF;
        if (PlayerObj_IsActive((PlayerObj *)j) > 0)
            sub_000BD4D0(j, 1);
        else
            sub_000BD4D0(j, 6);
        break;
    }
}

/* 0x000C1930: a variant of the action state at 0x000C22D0 with animation
   0x306: step 0 also calls 0x000D0530(j, 1, 4) (and does not clear the
   timer); step 1 clears flags 0x40000002 and calls 0x000D0530(j, -1, 4)
   before choosing state 1 (active) or 6. */
void r6k_JackActionC1930(R6kJack *j)
{
    j->vel110[2] = 0.0f;
    j->vel110[1] = 0.0f;
    j->vel110[0] = 0.0f;
    switch (j->subE0) {
    case 0:
        j->flags150 = (j->flags150 & ~0x800u) | 0x68000001;
        sub_000193C0();
        if (j->unkD4 == 1)
            sub_00019370(0xB, 80.0f);
        j->anim12C = 0x306;
        sub_000D0530(j, 1, 4);
        j->subE0++;
        sub_000CB990(j, 8.0f);
        break;
    case 8:
        sub_000CFF90(j, 1, 2.0f);
        if (PlayerObj_TimerDone((PlayerObj *)j) == 0)
            break;
        sub_000D0200(j, 0, 0);
        j->anim12C = 0;
        j->flags150 &= 0xBFFFFFFD;
        if (PlayerObj_IsActive((PlayerObj *)j) > 0)
            sub_000BD4D0(j, 7);
        else
            sub_000BD4D0(j, 1);
        break;
    case 1:
        if (PlayerObj_TimerDone((PlayerObj *)j) == 0)
            break;
        sub_000C53B0(j);
        j->flags150 &= 0xBFFFFFFD;
        sub_000D0530(j, -1, 4);
        if (PlayerObj_IsActive((PlayerObj *)j) > 0)
            sub_000BD4D0(j, 1);
        else
            sub_000BD4D0(j, 6);
        break;
    }
}

/* 0x000C2020: Jack's standing state (animation 0x200). Clears the velocity.
   Step 0 clears flags 0x7C000B01, animation 0x200, timer and velocity;
   when Jack is active (0x000CF1A0 > 0) goes to step 8, else to step 1.
   Step 1 returns to step 0 when active; unless flags 0x80000020 are set,
   after 605 time units sets flag 0x20000000 and animation 0x201 (idle
   fidget) and moves on. Step 2 (not while flag bit 31 is set) waits for
   the timer (0x000CF070), then clears flag 0x20000000 and the timer and
   goes back a step with animation 0x200. Step 8 (not while bit 31 is set)
   keeps animation 0x200 while active, else returns to step 0. */
void r6k_JackStandC2020(R6kJack *j)
{
    j->vel110[2] = 0.0f;
    j->vel110[1] = 0.0f;
    j->vel110[0] = 0.0f;
    switch (j->subE0) {
    case 0:
        j->flags150 &= 0x83FFF4FE;
        j->anim12C = 0x200;
        j->timerE8 = 0.0f;
        j->vel110[2] = 0.0f;
        j->vel110[1] = 0.0f;
        j->vel110[0] = 0.0f;
        if (PlayerObj_IsActive((PlayerObj *)j) > 0) {
            j->subE0 = 8;
            j->anim12C = 0x200;
            return;
        }
        j->subE0++;
        return;
    case 1:
        if (PlayerObj_IsActive((PlayerObj *)j) > 0)
            j->subE0 = 0;
        if (j->flags150 & 0x80000020)
            return;
        if (j->timerE8 > 605.0f) {
            j->flags150 |= 0x20000000;
            j->anim12C = 0x201;
            j->subE0++;
        }
        return;
    case 2:
        if ((int32_t)j->flags150 < 0)
            return;
        if (PlayerObj_TimerDone((PlayerObj *)j) == 0)
            return;
        j->flags150 &= 0xDFFFFFFF;
        j->timerE8 = 0.0f;
        j->subE0--;
        j->anim12C = 0x200;
        return;
    case 8:
        if ((int32_t)j->flags150 < 0)
            return;
        if (PlayerObj_IsActive((PlayerObj *)j) >= 0) {
            j->anim12C = 0x200;
            return;
        }
        j->subE0 = 0;
        return;
    }
}

/* 0x000C1540: a standing state variant with animations 0 / 0x301 / 0x302.
   Step 0 also clears the mode +0xEC and calls 0x000D0560(j, 0, 3) (with
   animation 0x302 and step 8 when Jack is active, else the next step);
   steps 1, 2 and 8 work like 0x000C2020 with animation 0x301 for the
   fidget, 0 after it, and 0x302 while active in step 8. */
void r6k_JackStandC1540(R6kJack *j)
{
    j->vel110[2] = 0.0f;
    j->vel110[1] = 0.0f;
    j->vel110[0] = 0.0f;
    switch (j->subE0) {
    case 0:
        j->flags150 &= 0x83FFF4FE;
        j->anim12C = 0;
        j->timerE8 = 0.0f;
        j->vel110[2] = 0.0f;
        j->vel110[1] = 0.0f;
        j->vel110[0] = 0.0f;
        j->modeEC = 0;
        if (PlayerObj_IsActive((PlayerObj *)j) > 0) {
            j->anim12C = 0x302;
            sub_000D0560(j, 0, 3);
            j->subE0 = 8;
            return;
        }
        j->subE0++;
        sub_000D0560(j, 0, 3);
        return;
    case 1:
        if (PlayerObj_IsActive((PlayerObj *)j) > 0)
            j->subE0 = 0;
        if (j->flags150 & 0x80000020)
            return;
        if (j->timerE8 > 605.0f) {
            j->flags150 |= 0x20000000;
            j->subE0++;
            j->anim12C = 0x301;
        }
        return;
    case 2:
        if ((int32_t)j->flags150 < 0)
            return;
        if (PlayerObj_TimerDone((PlayerObj *)j) == 0)
            return;
        j->flags150 &= 0xDFFFFFFF;
        j->subE0--;
        j->anim12C = 0;
        j->timerE8 = 0.0f;
        return;
    case 8:
        if ((int32_t)j->flags150 < 0)
            return;
        if (PlayerObj_IsActive((PlayerObj *)j) >= 0) {
            j->anim12C = 0x302;
            return;
        }
        j->subE0 = 0;
        return;
    }
}

/* 0x000BD8C0: Jack's main standing state (animations 0 / 1 / 2 / 0xB).
   Step 0 clears flags 0x7C000B01, animation, timer and velocity, calls
   0x000CA600 and 0x000D5620(0), then goes to step 8 with animation 2 when
   Jack is active (0x000CF1A0 > 0), else to step 1. Step 1 returns to step
   0 when active; unless flags 0x80000020 are set, after 605 time units sets
   flag 0x20000000 and animation 1 with the timer cleared and moves on.
   Step 2 after 30 units calls 0x000CEE40(1, 1), step 3 after 160 units
   0x000CEE40(0, 0), each moving on. Step 4 waits for the timer
   (0x000CF070), clears flag 0x20000000, animation and timer and goes to
   step 1. Step 8 (not while flag bit 31 is set) returns to step 0 when Jack
   is not active, uses animation 0xB while mode bits 0x43 are set, else
   animation 2 (and checks the activity again). */
void r6k_JackStandBD8C0(R6kJack *j)
{
    float limit;
    int on;

    j->vel110[2] = 0.0f;
    j->vel110[1] = 0.0f;
    j->vel110[0] = 0.0f;
    switch (j->subE0) {
    case 0:
        j->flags150 &= 0x83FFF4FE;
        j->anim12C = 0;
        j->timerE8 = 0.0f;
        j->vel110[2] = 0.0f;
        j->vel110[1] = 0.0f;
        j->vel110[0] = 0.0f;
        sub_000CA600(j);
        sub_000D5620(0);
        if (PlayerObj_IsActive((PlayerObj *)j) > 0) {
            j->anim12C = 2;
            j->subE0 = 8;
            return;
        }
        j->subE0++;
        return;
    case 1:
        if (PlayerObj_IsActive((PlayerObj *)j) > 0)
            j->subE0 = 0;
        if (j->flags150 & 0x80000020)
            return;
        if (j->timerE8 > 605.0f) {
            j->flags150 |= 0x20000000;
            j->anim12C = 1;
            j->timerE8 = 0.0f;
            j->subE0++;
        }
        return;
    case 2:
        limit = 30.0f;
        on = 1;
        goto wait_limit;
    case 3:
        limit = 160.0f;
        on = 0;
    wait_limit:
        if (j->timerE8 > limit) {
            sub_000CEE40(on, on);
            j->subE0++;
        }
        return;
    case 4:
        if (PlayerObj_TimerDone((PlayerObj *)j) == 0)
            return;
        j->flags150 &= 0xDFFFFFFF;
        j->anim12C = 0;
        j->timerE8 = 0.0f;
        j->subE0 = 1;
        return;
    case 8:
        if ((int32_t)j->flags150 < 0)
            return;
        if (PlayerObj_IsActive((PlayerObj *)j) < 0)
            j->subE0 = 0;
        if (j->modeEC & 0x43) {
            j->anim12C = 0xB;
            return;
        }
        j->anim12C = 2;
        if (PlayerObj_IsActive((PlayerObj *)j) < 0)
            j->subE0 = 0;
        return;
    }
}

/* 0x000C2820: Jack's item-use action (animation 0x213). Step 0 sets flags
   0x28000001 and 0x000CFF90(j, 1, 20.0), clears the model animation and
   +0x128 to -1, calls 0x000193C0 and starts effect 3 at 10.0 when +0xD4 is
   1, clears the timer and goes to step 0x10. Step 0x10 after 10 time units
   calls 0x000193C0 and moves on with the timer cleared; when 0x000D08F0
   fails it plays motion 0x44 and sound 0x5E and goes to step 0x12; else
   plays motion +0xD74 + 0x19, sound 0x33 (stat 6 is 0) or 0x3C, effect
   0xB + stat 6 (0x000AA2E0) and 0x000D2CC0(j, 0). Step 0x11 after 8 units
   calls 0x000C5930 and moves on. Step 0x12 waits for the timer, resets
   the input (0x000BC5D0, 0x000BC5F0) and goes to state 1 when Jack is
   active (0x000CF1A0 > 0), else state 6. */
void r6k_JackItemC2820(R6kJack *j)
{
    int motion;

    j->vel110[2] = 0.0f;
    j->vel110[1] = 0.0f;
    j->vel110[0] = 0.0f;
    switch (j->subE0) {
    case 0:
        j->flags150 |= 0x28000001;
        sub_000CFF90(j, 1, 20.0f);
        j->nodeFD8->anim30->i08 = -1;
        j->anim128 = -1;
        j->anim12C = 0x213;
        sub_000193C0();
        if (j->unkD4 == 1)
            sub_00019370(3, 10.0f);
        j->timerE8 = 0.0f;
        j->subE0 = 0x10;
        break;
    case 0x10:
        if (!(j->timerE8 >= 10.0f))
            break;
        motion = j->fD74 + 0x19;
        sub_000193C0();
        j->timerE8 = 0.0f;
        j->subE0++;
        if (sub_000D08F0(j, 0) < 0) {
            PlayerObj_D0030((PlayerObj *)j, 0x44);
            sub_000494D0(0x5E, j->nodeFD8->pos60, 0);
            j->subE0 = 0x12;
            break;
        }
        PlayerObj_D0030((PlayerObj *)j, motion);
        if (Stats_Get((PlayerStats *)j, 6) == 0)
            sub_000494D0(0x33, j->nodeFD8->pos60, 0);
        else
            sub_000494D0(0x3C, j->nodeFD8->pos60, 0);
        sub_000AA2E0(Stats_Get((PlayerStats *)j, 6) + 0xB);
        sub_000D2CC0(j, 0);
        break;
    case 0x11:
        if (!(j->timerE8 >= 8.0f))
            break;
        sub_000C5930(j);
        j->subE0++;
        break;
    case 0x12:
        if (PlayerObj_TimerDone((PlayerObj *)j) == 0)
            break;
        sub_000BC5D0();
        sub_000BC5F0(r6e_obj420EC0);
        if (PlayerObj_IsActive((PlayerObj *)j) > 0)
            sub_000BD4D0(j, 1);
        else
            sub_000BD4D0(j, 6);
        break;
    }
}
