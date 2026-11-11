/* Area r1h, group 17: screen marker projection 0x000264F0. Names inferred. */
#include "r1h.h"

/* 0x000264F0: when markers are enabled, project pos (raised by yofs) with
   camera 9 of the world and, when the depth is between 0 and 200, append
   a marker with the screen position (12.4 and 13.3 fixed point minus the
   32/8 offsets), depth, obj and tag. obj must not be null (assert hang). */
void r1h_MarkAdd(const float *pos, float yofs, void *obj, int tag)
{
    R1hCamModel *cam;
    float v[4], w[4];
    int xy[2], z;
    if (!obj)
        for (;;) ;
    if (!(r1h_flags37C4F8 & 1))
        return;
    cam = sub_000847F0(((R1hWorld44 *)r1h_world42C8E4)->cams, 9);
    sub_000F5D40(v, pos);
    v[1] += yofs;
    sub_001AD9B0(w, cam->mtx230, v);
    if (w[2] > 0.0f && 200.0f > w[2]) {
        sub_001AE140(xy, cam->vp1F0, &z, 0);
        r1h_marks37F0F0.m[r1h_marks37F0F0.n].x = (float)((xy[0] - 0x8000) >> 4) - 32.0f;
        r1h_marks37F0F0.m[r1h_marks37F0F0.n].y = (float)((xy[1] - 0x8000) >> 3) - 8.0f;
        r1h_marks37F0F0.m[r1h_marks37F0F0.n].z = w[2];
        r1h_marks37F0F0.m[r1h_marks37F0F0.n].obj = obj;
        r1h_marks37F0F0.m[r1h_marks37F0F0.n].tag = tag;
        r1h_marks37F0F0.n++;
    }
}
