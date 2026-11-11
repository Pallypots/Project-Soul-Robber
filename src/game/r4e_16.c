/* Area r4e: motion start at 0x001AEFD0 (r4e_16). Names inferred. */
#include "r4e.h"

/* 0x001AEFD0: start animation anim on o lasting frames ticks of the current rate,
   with new state flags; if flag 2 was set before, also re-pose o (0x001AEF60, o in EAX).
   Stack args (o anim flags frames). */
void r4e_MotionStart(R4eMotion *o, int anim, int flags, int frames)
{
    if (*(uint8_t *)&o->flagsBC & 2) {
        *(uint8_t *)&o->flagsBC = 0;
        o->animC8 = anim;
        o->flagsBC |= (uint8_t)flags;
        o->framesCC = (int)(1.0 / sub_001BBD80() * frames + 0.5);
        o->frameD0 = 0;
        sub_001AEBF0(o, anim, 3);
        sub_001AEF60(o);
        return;
    }
    *(uint8_t *)&o->flagsBC = 0;
    o->animC8 = anim;
    o->flagsBC |= (uint8_t)flags;
    o->framesCC = (int)(1.0 / sub_001BBD80() * frames + 0.5);
    o->frameD0 = 0;
    sub_001AEBF0(o, anim, 3);
}
