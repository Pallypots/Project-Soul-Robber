/* Area r4h: lobbed effect aim (r4h_11). Names inferred. */
#include "r4h.h"

/* 0x00190E80: aim a lobbed effect at the point from 0x00101340: ground
   direction and distance, a flight time between 40 and 74 frames growing
   with the distance, a random launch height (-5..+25 around 105 above the
   node), the vertical speed (mode 1: from that height, else towards Jack's
   height less 9) and the arc terms. Stack args (o a). */
void r4h_FxLobAim(R4hFxNodeD *o, R4hLobAct *a)
{
    R4hLobRec *rec = a->work;
    float target[4];
    float d[4];
    float dist;
    float inv;
    float t;
    float invT;
    float h;
    float q;
    float *vel;
    int r;

    sub_00101340(target);
    sub_001AD9F0(d, target, o->pos60);
    dist = sub_000F5F50(d);
    d[3] = 0.0f;
    d[1] = 0.0f;
    sub_001AD7E0(d, d);
    r = sub_001C7EE1() % 3000;
    inv = 1.0f / r4c_frameUnits;
    t = (inv * 74.0f - inv * 40.0f) * (dist * 0.008163265f) + inv * 40.0f;
    invT = 1.0f / t;
    h = (float)(r - 500) * 0.01f + o->pos60[1] + 105.0f;
    if (rec->mode10 == 1)
        rec->vy2C = 0.0f - invT * h;
    else
        rec->vy2C = (o->pos60[1] - (((float *)((char *)g_playerObj + 0x60))[1] - 9.0f)) * invT;
    q = invT * h * 2.0f * 2.0f;
    rec->g28 = (h - q * t * 0.5f) * 8.0f / (t * t);
    vel = rec->vel14;
    sub_001ADB60(vel, d, invT * dist);
    vel[1] = 0.0f - q;
    vel[3] = 0.0f;
}

/* 0x001956A0: aim a hopping effect at Jack: ground direction, scale 0.3
   and the hop arc to a point 16 units above the ground. Mode 1: the
   distance is clamped to 10..55, the speed random (0.85-1.15 times 40 per
   second) and the direction turned by a random angle (about -0.54..0.54
   rad); otherwise a fixed speed and time (33 per second for 36 units when
   nearer than 56, else 63 per second for 76 units). Stack args (o a);
   calls 0x001955B0 with EAX=o and 0.3 on the stack. */
void r4h_FxHopAim(R4hFxNodeD *o, R4hHopAct *a)
{
    R4hHopRec *rec = a->work;
    float *target = (float *)((char *)g_playerObj + 0x60);
    float h;
    float d[4];
    float dir[4];
    float m[16];
    float dist;
    float speed;
    float t;
    float q;

    h = 16.0f - (0.0f - o->pos60[1]);
    sub_001AD9F0(d, target, o->pos60);
    d[3] = 0.0f;
    d[1] = 0.0f;
    sub_001AD7E0(dir, d);
    rec->f14 = 0.3f;
    r4c_FxScale(o, 0.3f);
    dist = sub_001B2770(o->pos60, target);
    rec->vel44[0] = 0.0f;
    rec->vel44[1] = 0.0f;
    rec->vel44[2] = 0.0f;
    rec->vel44[3] = 0.0f;
    if (rec->mode10 == 1) {
        if (10.0f > dist)
            dist = 10.0f;
        else if (dist > 55.0f)
            dist = 55.0f;
        speed = (float)(sub_001C7EE1() % 31 + 0x55) * 0.01f * (40.0f / a50_framesPerSecond);
        t = dist / speed;
        sub_001ADB60(d, dir, speed);
        sub_001AD940(m);
        sub_001AD8E0(m, m, (float)(sub_001C7EE1() % 0x26D - 0x136) * 0.31415927f * 0.0055555557f);
        sub_001AD9B0(rec->vel44, m, d);
    } else {
        if (56.0f > dist) {
            speed = 33.0f / a50_framesPerSecond;
            t = 36.0f / speed;
        } else {
            speed = 63.0f / a50_framesPerSecond;
            t = 76.0f / speed;
        }
        sub_001ADB60(d, dir, speed);
        rec->vel44[0] = d[0];
        rec->vel44[2] = d[2];
    }
    q = h / t * 2.0f * 2.0f;
    rec->g84 = (h - q * t * 0.5f) * 8.0f / (t * t);
    rec->vel44[1] = 0.0f - q;
    rec->t0C = 0.0f;
}
