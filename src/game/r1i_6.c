/* Area r1i, group 6: aim direction limit 0x00018B70. Names inferred. */
#include "r1i.h"

/* 0x00018B70: when limiting is on, bring the target into the object's
   frame, measure its yaw and then pitch angle against the forward axis
   (in degrees, relative to half the field of view) and, when either is
   beyond its limit, ease the forward axis 10% towards the clamped
   direction. Then optionally rebuild the side or up axis by cross
   products. regargs: o=EAX */
void r1i_AimLimit(R1iAim *o)
{
    float v[4];
    R1iMat m, mb, ma, inv;
    float a;
    uint32_t f;
    if (!(o->cfg->flags & 2))
        return;
    sub_000385D0(m, o->m);
    sub_000F5D40(m[3], r1i_vec3781A8);
    sub_001AD9A0(inv, m);
    sub_001AD9B0(v, inv, o->target);
    v[0] = 0.0f;
    sub_001AD7E0(v, v);
    sub_001AD9B0(v, m, v);
    a = sub_001A3F20(sub_001AD9D0(o->m[2], v)) * 57.295792f;
    a = a / (o->fov * 0.5f);
    if (a > o->cfg->limYaw) {
        sub_001ADC60(v, o->m[2], v, o->cfg->limYaw / a);
        sub_001ADC60(o->m[2], v, o->m[2], 0.1f);
    }
    sub_001AD9B0(v, inv, o->target);
    v[1] = 0.0f;
    sub_001AD7E0(v, v);
    sub_001AD9B0(v, m, v);
    a = sub_001A3F20(sub_001AD9D0(o->m[2], v)) * 57.295792f;
    a = a / (o->fov * 0.5f);
    if (a > o->cfg->limPitch) {
        sub_001ADC60(v, o->m[2], v, o->cfg->limPitch / a);
        sub_001ADC60(o->m[2], v, o->m[2], 0.1f);
    }
    f = o->cfg->flags;
    if (f & 0x400) {
        sub_000385D0(ma, o->m);
        sub_000385D0(mb, o->mB0);
        sub_001ADA60(o->m[1], ma[2], mb[0]);
        sub_001ADA60(o->m[2], mb[0], o->m[1]);
    } else if (f & 0x800) {
        sub_000385D0(ma, o->m);
        sub_000385D0(mb, o->mB0);
        sub_001ADA60(o->m[0], o->mB0[1], ma[2]);
        sub_001ADA60(o->m[2], o->m[0], mb[1]);
    }
}
