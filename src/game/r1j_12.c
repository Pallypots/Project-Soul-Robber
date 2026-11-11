/* Area r1j, group 12: camera occluder fade 0x0003AF70.
   Names inferred. */
#include "r1j.h"

/* first / next item of the occluder list (each item sits 0x10 bytes into
   its list node; node->data points at the item) */
#define R1J_OCC_FIRST() \
    (r1j_occList3DDC60.first != 0 ? r1j_occList3DDC60.first->data : 0)
#define R1J_OCC_NEXT(it) \
    (((R1jOccNode *)((char *)(it) - 0x10))->next != 0 \
     ? ((R1jOccNode *)((char *)(it) - 0x10))->next->data : 0)

/* 0x0003AF70: set the fade value of every camera occluder. When there are
   occluders, the player exists, input bit 0x4001 is not held and the
   camera is not locked (0x0042CB04 == 1 with the player flag at +0xD4,
   unless the stage mode at +0x20C is 9): an enabled occluder whose point
   (0x0003AAF0) exists gets its distance from the player, 0 when its
   object has bit 0 at +0x34, and -1 beyond r1j_occRange; the rest get -1;
   then the list is sorted (0x0003DB40 with 0x0003A950). Otherwise every
   occluder gets -1. */
void r1j_OccluderUpdate(void)
{
    R1jOccItem *it;
    float eye[4], d[4], pt[4], n[4];
    float a;
    if (r1j_occList3DDC60.count > 0 && g_playerObj != 0 && sub_0019BE60(0x4001) == 0
        && (r1j_camLock42CB04 != 1 || g_stats.unkD4 == 0
            || (r1j_stage42C8E4 != 0 && r1j_stage42C8E4->mode == 9))) {
        sub_000F5D40(eye, (char *)g_playerObj + 0x60);
        for (it = R1J_OCC_FIRST(); it != 0; it = R1J_OCC_NEXT(it)) {
            if (!(it->flags & 1) || sub_0003AAF0(it, pt) != 0) {
                a = -1.0f;
            } else {
                sub_001AD9F0(d, pt, eye);
                sub_001AD7E0(n, d);
                a = sub_001AD9D0(n, d);
                if (it->obj != 0 && (it->obj->flags34 & 1))
                    a = 0.0f;
                else if (a > (float)r1j_occRange)
                    a = -1.0f;
            }
            it->fade = a;
        }
        sub_0003DB40(&r1j_occList3DDC60, (void *)sub_0003A950);
        return;
    }
    for (it = R1J_OCC_FIRST(); it != 0; it = R1J_OCC_NEXT(it))
        it->fade = -1.0f;
}
