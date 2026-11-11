/* Area r4g: pop effect aim at 0x00196E70 (r4g_8). Names inferred. */
#include "r4g.h"

/* 0x00196E70: aim a new pop effect at the player: flight time from the
   horizontal distance, near flag (closer than 30), vertical speed to reach
   the player's height less 8.45, horizontal velocity along the normalized
   direction and the arc terms. Register arg: rec=ESI. */
void r4g_PopAim(R4gPopRec *rec)
{
    const float *ppos = ((R4gPlayer *)g_playerObj)->pos;
    R4gNode *o = rec->obj;
    float d[4], e[4];
    float dist, r, t, inv, a, b;

    rec->s0C = 0;
    d[1] = 0.0f;
    sub_001AD9F0(d, ppos, o->pos);
    dist = sub_000F5F50(d);
    r = 1.0f / a50_frameUnits;
    t = r * 20.0f * (dist * 0.0064102565f) + r * 53.0f;
    o->scale70[2] = 0.3f;
    o->scale70[1] = 0.3f;
    o->scale70[0] = 0.3f;
    sub_001AD9F0(e, ppos, o->pos);
    if (sub_000F5F50(e) > 30.0f)
        rec->s10 = 1;
    else
        rec->s10 = 0;
    rec->s12 = 0;
    rec->s0E = 0;
    inv = 1.0f / t;
    rec->f18 = (o->pos[1] - (ppos[1] - 8.4500008f)) * inv;
    sub_000F5D40(rec->v30, d);
    rec->v30[3] = 0.0f;
    sub_000F5D40(o->pos, o->pos);
    d[1] = 0.0f;
    d[3] = 0.0f;
    sub_001AD7E0(d, d);
    sub_001ADB60(rec->v20, d, inv * dist);
    a = d[1] * 37.0f * 2.0f;
    b = d[2];
    rec->f1C = (18.5f - a * b * 0.5f) * 8.0f / (b * b);
    rec->v20[1] = 0.0f - a;
    rec->v20[3] = 0.0f;
}
