/* Area r6c: callers kept apart from their callees so cl does not inline them (r6c_5). Names inferred. */
#include "r6c.h"

/* 0x0007A9F0: light, tint and colour the object for drawing. */
void r6c_ObjPrepare(R6cObj7 *o, R6cDraw *d, int flags)
{
    r6c_ApplyVecs(o->mdl, &o->light);
    r6c_ObjApplyTint(o);
    sub_00079B40(o);
    r6c_ObjCopyColour(o, d, flags);
}

/* 0x00087570: step an event jump: 0 when finished, 1 while running. */
int r6c_EvJumpStep(int a, int b)
{
    switch (r6c_step3ED244) {
    case 0:
        if (!sub_00085390(1)) {
            r6c_EvJump(0);
            return 0;
        }
        r6c_step3ED244 = 10;
        /* fall through */
    case 10:
        if (sub_00086230(a, b, 0))
            return 1;
        r6c_step3ED244 = 0;
        return 0;
    }
    return 1;
}

/* 0x00087B00: reset the event scene state and point the camera at the player. */
void r6c_EvSceneReset(void)
{
    sub_000D2A50(&g_stats, 0);
    r6c_grp3ED254 = 0;
    r6c_v3ED258 = 0;
    r6c_v3ED25C = -1;
    r6c_f3ED260[0] = 0.0f;
    r6c_f3ED260[1] = 0.0f;
    r6c_f3ED260[2] = 0.0f;
    r6c_v3ED26C = 0;
    r6c_v3ED274 = 0;
    r6c_CamFollowPlayer();
    sub_000EE0C0();
}

/* 0x00087F70: advance the event timer; when it runs out (or bit 16 is set) reset the event scene. */
void r6c_EvTimerTick(void)
{
    r6c_f3ED260[1] += a50_frameSeconds;
    if (r6c_f3ED260[1] >= r6c_f3ED260[2] || (r6c_v3ED258 & 0x10000)) {
        r6c_grp3ED254 = 0;
        r6c_v3ED258 = 0;
        r6c_v3ED25C = -1;
        r6c_f3ED260[0] = 0.0f;
        r6c_f3ED260[1] = 0.0f;
        r6c_f3ED260[2] = 0.0f;
        r6c_v3ED26C = 0;
        r6c_CamFollowPlayer();
        r6c_v3ED274 = 0;
    }
}
