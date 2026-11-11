/* Area r4g: model ground snap callback at 0x00196B40 (r4g_7). Names inferred. */
#include "r4g.h"

/* 0x00196B40: model callback of the 0x00400390 effects: copy the owner's
   matrix, scale its three axes (by scale18, times scale14 unless hit tests
   5/10 and 5/20 fire), cast a ray from the owner's position 100 units up
   and snap the position (and the copy at +0x70) to the hit, then add the
   offset and rebuild the second matrix. Stack args (m p). */
void r4g_ModelSnapToGround(float *m, R4gSnapArg *p)
{
    R4gHitObj *o = p->obj10;
    float from[4], to[4];
    float s;
    void *h;
    R4gHit *hit;

    if (!o->mtx20)
        return;
    sub_001ADA40(m, o->mtx20);
    if (sub_000F5CD0(o, 5, 10) || sub_000F5CD0(o, 5, 20))
        s = p->scale18;
    else
        s = p->scale18 * p->scale14;
    sub_001ADB60(m, m, s);
    sub_001ADB60(m + 4, m + 4, s);
    sub_001ADB60(m + 8, m + 8, s);
    sub_000F5D40(from, o->mtx20 + 12);
    sub_000F5D40(to, from);
    to[1] = 100.0f;
    h = sub_00080970();
    sub_000824F0(a80_ctx42C8E4->p54, h, from, to, 0, 0);
    hit = sub_00080CB0(h, from, to);
    if (hit) {
        sub_000F5D40(m + 12, hit->pos40);
        sub_000F5D40(m + 28, hit->pos40);
    }
    m[12] += p->off1C[0];
    m[13] += p->off1C[1];
    m[14] += p->off1C[2];
    m[15] = m[15];
    sub_001ADA40(m + 16, m);
}

/* 0x00198080: spawn callback of the pop effect: take one of the four
   records at *0x00401830, set it up (0x00196E70), collision, callbacks and
   the hit callback 0x00197650, enter state 1 and set the spin rate and
   colour. Returns 0 when all records are busy. Stack args (o a); calls
   0x00196E70 with ESI=rec. */
int r4g_FxPopSpawn(R4gNode *o, R4gActor *a)
{
    R4gPopRec *rec;
    float c[4];
    int i;

    for (i = 0; i < 4; i++)
        if (!r4c_g401830[i].obj)
            break;
    if (i >= 4)
        return 0;
    rec = &r4c_g401830[i];
    rec->idx08 = i;
    rec->actor = a;
    rec->obj = o;
    a->work = rec;
    o->flagsC |= 1;
    o->flags10 |= 0x4C1;
    r4g_PopAim(rec);
    o->i124 = 1;
    sub_000F5D60(o, 0.3f, -22.0f, 9.5f, r4g_v27B1B0);
    sub_000F5DD0(o, 0.3f, 10.0f, r4g_v27B1C4);
    o->iF0 = 2;
    o->iF4 = 2;
    sub_000F5E30(o, 0.3f, r4g_v27B1D4, r4g_v27B1E4);
    o->i11C = 1;
    o->i120 = 2;
    a->f28 = 0.0f;
    a->f2C = -3.9f;
    a->p84 = r4g_d32C858;
    a->p88 = r4g_d32C864;
    a->fn78 = (void *)sub_00197D90;
    a->fn7C = (void *)sub_00197040;
    a->fn80 = (void *)sub_00197160;
    sub_0001C9E0(o, 0, sub_00197650);
    a->i24 = 0;
    sub_00189DA0(o, a, 1);
    c[0] = 0.0f;
    c[1] = 2.5f;
    c[2] = 0.0f;
    c[3] = 1.0f;
    sub_0001EEC0(o, 3.3333333f);
    sub_0001EF00(o, c);
    return 1;
}
