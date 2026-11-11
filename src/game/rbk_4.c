/* Area rbk: Jack's aim rig, callers of the reach test (kept apart from rbk_3.c so cl does
   not inline 0x000D58F0). Names inferred. */
#include "rbk.h"

/* 0x000D60F0: reach the whole rig. The segment from Jack's feet (15 below his position)
   through the last joint, extended by the reach, is registered with the world
   (0x00082200). Every rest point is reset to its joint; while +0 is negative, rest points
   2..15 also reach out (0x000D58F0 with mask 0). Called with stack arg (r). */
void rbk_RigReachAll0D60F0(RbkRig *r)
{
    void *world = ((RbkScene54 *)rbj_scene42C8E4)->world54;
    RbjVec4 feet, end, dir;
    float reach;
    int i;

    feet.x = 0.0f;
    feet.y = 0.0f;
    feet.z = 0.0f;
    feet.w = 1.0f;
    end.x = 0.0f;
    end.y = 0.0f;
    end.z = 0.0f;
    end.w = 1.0f;
    dir.x = 0.0f;
    dir.y = 0.0f;
    dir.z = 0.0f;
    dir.w = 1.0f;
    reach = sub_000CA300(RBK_JACK);
    sub_000F5D40(&feet, (const RbjVec4 *)((uint8_t *)g_playerObj + 0x60));
    feet.y = feet.y - 15.0f;
    sub_000F5D40(&end, &r->pos84[15]);
    rbj_VecSub(&dir, &end, &feet);
    rbj_VecNormalize(&dir, &dir);
    rbj_VecScale4(&dir, &dir, reach);
    rbj_VecAdd(&end, &end, &dir);
    sub_00082200(world, &feet, &end, 0);
    for (i = 0; i < 16; i++) {
        sub_000F5D40(&r->rest294[i], &r->pos84[i]);
        if (r->a00 < 0 && i >= 2)
            rbk_RigReach0D58F0(r, world, 0, 0, i);
    }
}
