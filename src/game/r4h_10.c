/* Area r4h: slot throw velocity (r4h_10). Names inferred. */
#include "r4h.h"

/* 0x00192730: aim a held slot effect: pick a throw distance (0.00-0.20 or
   0.80-1.00 of 8.5 units, alternating), a random yaw in -pi..pi, rotate
   the offset, add the aim point at +0x78, subtract the node position and
   divide by the animation length ratio to get the velocity at +0x2C (with
   no vertical part). regargs: rec=ESI. */
void r4h_SlotThrow(R4hSlot88 *rec)
{
    R4hAnimInfo *inf = rec->obj->anim30->info14;
    float ratio;
    float angle;
    float v[4];
    float m[16];
    int r;

    ratio = inf->fDC / inf->fC4;
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 0.0f;
    if (rec->toggle70 == 0) {
        rec->toggle70 = 1;
        r = sub_001C7EE1() % 21;
    } else {
        rec->toggle70 = 0;
        r = sub_001C7EE1() % 21 + 80;
    }
    v[0] = (float)r * 0.01f * 8.5f;
    angle = (float)(sub_001C7EE1() % 100) * 0.01f * 6.2831855f - 3.1415927f;
    sub_000F5ED0(&angle);
    sub_001AD940(m);
    sub_001AD8E0(m, m, angle);
    sub_001AD9B0(v, m, v);
    sub_001ADAF0(v, v, rec->aim78);
    sub_001AD9F0(v, v, rec->obj->pos60);
    sub_001ADB60(rec->vel2C, v, 1.0f / ratio);
    rec->vel2C[3] = 0.0f;
    rec->vel2C[1] = 0.0f;
}

/* 0x00192EC0: aim a slot effect at the system target: flight time from
   the ground distance at 110 units per second, ground direction scaled by
   that speed, the vertical launch terms for a -9.2 gravity arc landing at
   height -4.6 above -13.5, the start position, and the turn toward Jack.
   Stack args (o a). */
void r4h_FxSlotAim(R4hFxNodeD *o, R4hFxActD *a)
{
    R4hSlot88 *rec = a->work;
    R4hSys *sys = sub_000F3F80();
    float *target;
    float speed;
    float t;
    float inv;
    float g;
    float v[4];

    speed = 110.0f / a50_framesPerSecond;
    o->flagsC &= ~0xE0u;
    target = sys->target8C->pos60;
    t = sub_001B2770(target, o->pos60) / speed;
    rec->vel2C[0] = 0.0f;
    rec->vel2C[1] = 0.0f;
    rec->vel2C[2] = 0.0f;
    rec->vel2C[3] = 0.0f;
    sub_001AD9F0(v, target, o->pos60);
    v[3] = 0.0f;
    v[1] = 0.0f;
    sub_001AD7E0(rec->dir1C, v);
    rec->dir1C[0] = rec->dir1C[0] * speed;
    rec->dir1C[2] = rec->dir1C[2] * speed;
    inv = 1.0f / t;
    g = inv * -9.2f * 2.0f;
    rec->v50 = g;
    rec->g4C = (-4.6f - g * t * 0.5f) * 8.0f / (t * t);
    rec->v54 = (o->pos60[1] - -13.5f) * inv;
    sub_000F5D40(rec->start3C, o->pos60);
    sys->turn114 = sub_000F7720(sys->target8C, (float *)((char *)g_playerObj + 0x60));
    rec->time5C = t;
    rec->t0C = 0.0f;
}
