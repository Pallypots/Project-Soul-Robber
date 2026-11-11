/* Area fix: callers recovered after the callee signatures in r3c.h were
 * corrected. Reference build OOGIE-XBOX-US-RETAIL. All names inferred. */
#include "fix.h"

/* 0x0017C460: when none of the six records at 0x003FDC70 holds an object and the
 * game mode is 1, spawn effect 0x16 for slots 0..5 and store v in each spawned
 * object's component-6 work block (+0x0C). */
void fix_SpawnLinks17C460(int v)
{
    int i;

    for (i = 0; i < 6; i++)
        if (r3c_recs3FDC70[i].obj != 0)
            return;
    if (sub_000E0770()->i324 != 1)
        return;
    for (i = 0; i < 6; i++) {
        FixObj *o = sub_000ED630(4, 0x16, 0, 0, i);
        if (o != 0) {
            FixObj *c = sub_0001D960(o, 6);
            if (c != 0 && c->work278 != 0)
                c->work278->i0C = v;
        }
    }
}

/* 0x0018E740: start obj's component 7 (0x0018E270 with k = 0, mode 2 or 3 by
 * c's bit 0) and set its direction to dir scaled to 70. */
void fix_Launch18E740(FixObj *obj, const float *dir)
{
    FixObj *c = sub_0001D960(obj, 7);
    FixBlk74 *b;

    if (c == 0)
        for (;;)
            ;
    b = c->p74;
    sub_0018E270(obj, c, 0);
    obj->flags0C |= 0x40;
    obj->i124 = 1;
    sub_00189DA0(obj, c, (c->b20 & 1) ? 3 : 2);
    sub_001AD7E0(b->v0C, dir);
    sub_001ADB60(b->v0C, b->v0C, 70.0f);
}

/* 0x00146F50: mirror obj's position through the centre point of act's work block;
 * when 0x00145940 accepts c's range there, apply c's value through 0x001459D0. */
void fix_Mirror146F50(FixObj *obj, FixObj *act, const FixRange *c)
{
    float v[4];

    sub_001AD9F0(v, obj->pos60, act->work278->v78);
    sub_001ADAF0(v, v, obj->pos60);
    if (sub_00145940(obj, v[0], v[2], c->lo, c->hi))
        sub_001459D0(obj, v[0], v[2], c->val);
}

/* 0x0012DA00: when 0x00145940 accepts c's range at the work block's point
 * (+0x144, +0x14C), apply c's value through 0x001459D0. */
void fix_Apply12DA00(void *obj, FixObj *act, const FixRange *c)
{
    FixWork *w = act->work278;

    if (sub_00145940(obj, w->f144, w->f14C, c->lo, c->hi))
        sub_001459D0(obj, w->f144, w->f14C, c->val);
}

/* 0x00146FD0: step obj around the work block's centre: the flat direction from
 * the centre, scaled to radius c->lo and turned 5 degrees (sign by work bit 0),
 * gives the target passed to 0x001459D0 with value c->hi. */
void fix_Orbit146FD0(FixObj *obj, FixObj *act, const FixRange *c)
{
    FixWork *w = act->work278;
    float d[4], r[4];

    sub_001AD9F0(d, obj->pos60, w->v78);
    d[1] = 0.0f;
    sub_001AD7E0(d, d);
    sub_001ADBA0(d, d, c->lo);
    if (w->b50 & 1)
        sub_00145C50(r, d, 0.0872664675f);
    else
        sub_00145C50(r, d, -0.0872664675f);
    sub_001ADAF0(d, r, w->v78);
    sub_001459D0(obj, d[0], d[2], c->hi);
}

/* 0x001860B0: turn obj towards part 0x27 of the player model and store the
 * distance, height difference and per-frame rates in act's work block. */
void fix_Face1860B0(FixObj *obj, FixObj *act)
{
    FixWork *w = act->work278;
    float m[16];

    sub_00145F40(g_playerObj, 0x27, m);
    sub_001459D0(obj, m[12], m[14], 3.14159274f);
    w->f88 = w->f8C = sub_001B2770(obj->pos60, &m[12]);
    w->f90 = a50_frameSeconds * 10000.0f;
    w->f94 = w->f98 = m[13] - obj->pos60[1];
    w->f9C = a50_frameSeconds * 10000.0f;
}

/* 0x000EBA00: spawn effect 0xA (type 5) at the player model's position. */
void fix_SpawnAtPlayerEBA00(void)
{
    float rot[4], pos[4];

    rot[0] = 0.0f; rot[1] = 0.0f; rot[2] = 0.0f; rot[3] = 0.0f;
    sub_000F5D40(pos, (float *)((uint8_t *)g_playerObj + 0x60));
    sub_000ED630(5, 0xA, pos, rot, 0);
}

/* 0x000EBA50: spawn effect 0x11 (type 5) at the point +0x34F0 of the record
 * reached from 0x000E23F0(3, 0) -> +0x20 -> +0xC4. */
void fix_SpawnAtEBA50(void)
{
    float rot[4], pos[4];
    uint8_t *o;

    rot[0] = 0.0f; rot[1] = 0.0f; rot[2] = 0.0f; rot[3] = 0.0f;
    o = *(uint8_t **)((uint8_t *)sub_000E23F0(3, 0) + 0x20);
    sub_000F5D40(pos, (float *)(*(uint8_t **)(o + 0xC4) + 0x34F0));
    sub_000ED630(5, 0x11, pos, rot, 0);
}
