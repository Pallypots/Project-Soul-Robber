/* Area r4h: effect held between Jack's joints (r4h_13). Names inferred. */
#include "r4h.h"

/* 0x00198B40: hold the effect between Jack's joints 0x26 and 0x27: set
   joint 2 of the effect to the blend point (0x0032C910 of the way) as an
   offset from its joint 1, scaled by 1/1.5 (0x0032C8CC) and turned back by
   the effect's yaw; enter state 4 once the timer reaches 0x0032C914.
   Stack args (o a). */
void r4h_FxJointHold(R4hJntObj *o, R4hJntAct *a)
{
    R4hJoint *ja = sub_0001D0F0(g_playerObj, 0x26);
    R4hJoint *jb = sub_0001D0F0(g_playerObj, 0x27);
    R4hJoint *j2 = sub_0001D0F0(o, 2);
    R4hJoint *j1 = sub_0001D0F0(o, 1);
    float *off;
    float v[4];
    float m[16];

    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 1.0f;
    sub_001ADCD0(v, ja->pos70, jb->pos70, r4h_lerp32C910);
    off = j2->off30;
    off[0] = v[0] - j1->pos70[0];
    off[1] = v[1] - j1->pos70[1];
    off[2] = v[2] - j1->pos70[2];
    off[3] = v[3];
    sub_001ADBA0(off, off, 1.0f / r4c_g32C8CC);
    sub_001AD940(m);
    sub_001AD8E0(m, m, 0.0f - o->rotY54);
    sub_001AD9B0(off, m, off);
    j2->off30[3] = 1.0f;
    if (a->t6C >= r4h_end32C914) {
        sub_00189DA0(o, a, 4);
        a->work->i04 = 0;
    }
}

/* 0x00197E40: step of a piece knocked off an object: while not held,
   play sound 0x1A7 once after 10 frames, remember the position, follow
   Jack in X/Z for the first 0.53 seconds, rise on its arc after 0.5
   seconds and move; then set the blink rate from the source's height
   (|y + 83| / 83 * 0.6 + 1) and run the two-frame blink. On landing pop
   the source (0x00196DB0, sound 0x1BD) and destroy it; vanish after 15
   seconds. Stack args (o a); calls 0x00196DB0 with EAX=kind ECX=source. */
void r4h_FxPopDrop(R4hPopObj *o, R4hPopAct *a)
{
    R4hPopRec *rec = a->work;
    float x;

    if (rec->held10 == 0) {
        if (rec->sound0C == 0 && a->t6C * a50_framesPerSecond >= 10.0f / r4c_frameUnits) {
            sub_000494D0(0x1A7, o->pos60, 1);
            rec->sound0C = 1;
        }
        sub_000F5D40(rec->last24, o->pos60);
        if (0.53f > a->t6C) {
            o->pos60[0] = ((R4hPopObj *)g_playerObj)->pos60[0];
            o->pos60[2] = ((R4hPopObj *)g_playerObj)->pos60[2];
        }
        if (a->t6C > 0.5f) {
            o->pos60[1] = rec->base38 + rec->h20;
            rec->h20 = rec->h20 + rec->vel1C;
            rec->vel1C = rec->acc18 + rec->vel1C;
        }
        sub_000F60C0(o, 1, 0);
        if (rec->held10 == 0)
            sub_000F6450(o, r4h_d32C848);
    }
    x = (-83.0f - (-83.0f - rec->src->pos60[1])) * -0.012048192f;
    if (0.0f > x)
        x = 0.0f - x;
    rec->rate08 = x * 0.6f + 1.0f;
    if (rec->blink0E == 1) {
        rec->blink0E = 2;
    } else if (rec->blink0E == 2) {
        rec->blink0E = 0;
        o->flagsC &= ~0x100u;
    }
    if (rec->held10 == 0) {
        if (o->flags128 & 0x18) {
            o->pos60[1] = -0.05f;
            sub_00196DB0(rec->kind04, rec->src);
            sub_000494D0(0x1BD, rec->src->pos60, 0);
            sub_000ED780(rec->src);
            return;
        }
        if (a->t6C > 15.0f) {
            sub_000ED780(o);
            return;
        }
    }
    sub_0001EEC0(o, rec->rate08);
}

/* 0x00193E50: place a new wave piece o at its source: same position
   (lowered by 13 times the source's Y scale) and scale, a random free
   lane r (0..6, bit r not set in used) giving a yaw of (r - 3) * 10
   degrees from the source, then the launch velocity from the lane
   profile (used & 1: tilt -15 degrees, 120 per second at 90 units per
   second, else tilt -30 degrees, 60 per second at 45). The record keeps
   the speed, the rise and the lane bit. Stack args (o src used). */
void r4h_FxWaveSpawn(R4hWaveObj *o, R4hWaveObj *src, uint32_t used)
{
    float prof[2][3];
    float v[4];
    float m[16];
    R4hWaveAct *act;
    R4hWaveRec *rec;
    int r;

    prof[0][0] = -0.52359879f;
    prof[0][1] = 60.0f;
    prof[0][2] = r4c_frameSeconds * 45.0f;
    prof[1][0] = -0.26179939f;
    prof[1][1] = 120.0f;
    prof[1][2] = r4c_frameSeconds * 90.0f;
    act = sub_0001D960(o, 7);
    if (!act)
        return;
    rec = act->work;
    sub_000F5D40(o->pos60, src->pos60);
    o->pos60[1] = o->pos60[1] - src->scale70[1] * 13.0f;
    sub_000F5D40(o->scale70, src->scale70);
    do {
        r = sub_001C7EE1() % 7;
    } while (used & (1u << r));
    o->rotY54 = (float)(r - 3) * 10.0f * 0.017453292f + src->rotY54;
    if (o->rotY54 > 3.1415927f)
        o->rotY54 = o->rotY54 - 6.2831855f;
    if (-3.1415927f > o->rotY54)
        o->rotY54 = o->rotY54 + 6.2831855f;
    sub_001AD940(m);
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 1.0f;
    sub_001AD8B0(m, m, prof[used & 1][0]);
    sub_001AD8E0(m, m, o->rotY54);
    v[2] = 0.0f - prof[used & 1][2];
    sub_001AD9B0(v, m, v);
    sub_000F5D40(o->vel80, v);
    sub_001AD940(m);
    sub_001AD8E0(m, m, 0.0f - o->rotY54);
    v[1] = 0.0f;
    sub_001AD9B0(v, m, v);
    rec->speed08 = prof[used & 1][1];
    rec->rise0C = 0.0f - v[2];
    rec->flags |= 4;
    rec->bit10 = 1u << r;
}
