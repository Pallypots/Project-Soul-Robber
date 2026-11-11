/* Area r2, group 5: mixed helpers (0x000D7090..0x0012D3CD). Names inferred. */
#include "r2.h"

/* 0x000D9100: id of the table point nearest to pos (-1 for an empty table).
   regargs: t=EBX; pos is the stack arg */
int r2_NearestPoint(const R2PtTable *t, const float *pos)
{
    float d[4], best = 0.0f, l;
    int id = -1, i;
    for (i = 0; i < t->count; i++) {
        sub_001AD9F0(d, pos, t->pt400[i]);
        l = sub_001AD9D0(d, d);
        if (i == 0 || best > l) {
            best = l;
            id = t->id04[i];
        }
    }
    return id;
}

/* 0x000DDC60: script command: wait until the sound position (0x053F60, in ms) has
   passed the float in the message; then release it and clear 0x3EDD1C.
   Returns 0x3000 (keep waiting) or 0x2004 (done).  Stack arg msg. */
int r2_MsgCheckRange(R2Msg *msg)
{
    const uint8_t *d = msg->data04;
    union { uint32_t u; float f; } v;
    unsigned int pos;
    v.u = ((((uint32_t)d[3] << 8 | d[2]) << 8 | d[1]) << 8) | d[0];
    pos = (unsigned int)sub_00053F60();
    if (v.f > (float)pos * 0.001f)
        return 0x3000;
    a5b_SndRelease();
    af0_SetVar3EDD1C(0);
    return 0x2004;
}

/* 0x000EF810: keep the kind-5 component's +0x10C slot while 0x17F000 accepts it,
   otherwise pick a random accepted slot 0..5 (or -1).  regargs: obj=EAX */
int r2_PickRandomSlot(R2Actor *obj)
{
    R2Comp5B *c = (R2Comp5B *)sub_0001D960(obj, 5);
    int list[6], n, i;
    if (c->pick10C == -1)
        return -1;
    if (!sub_0017F000(c->pick10C)) {
        n = 0;
        for (i = 0; i < 6; i++)
            if (sub_0017F000(i))
                list[n++] = i;
        if (n) {
            c->pick10C = list[aab_Rand() % n];
            return c->pick10C;
        }
        c->pick10C = -1;
    }
    return c->pick10C;
}

/* 0x000EFD50: set a ballistic velocity for flight time t (seconds), height h and
   distance d.  regargs: obj=EAX; t h d are the stack args */
void r2_SetBallistic(R2Mover *obj, float t, float h, float d)
{
    float f = a50_framesPerSecond * t, inv;
    if (!obj)
        for (;;) ;
    obj->velF0[0] = d * -8.0f / (f * f);
    obj->velF0[1] = a50_frameSeconds * 0.0f;
    inv = 1.0f / f;
    obj->velF0[2] = inv * d * 4.0f;
    obj->velF0[3] = inv * h;
}

/* 0x000F4510: when the boss's +0x8C part has flag 2, derive its +0x120 speed from
   0x0F3C70, clamped to [1.48, 10]. */
void r2_BossClampSpeed(void)
{
    R2Boss *o = (R2Boss *)g_acb_bossMgr;
    void *p = o->link8C;
    float v;
    if (sub_000F3CB0(p) & 2) {
        sub_000F3CB0(p);
        v = sub_000F3C70(p) * 0.0017301039f * 10.0f;
        if (1.48f > v) {
            o->f120 = 1.48f;
            return;
        }
        if (v > 10.0f)
            v = 10.0f;
        o->f120 = v;
    }
}

/* 0x00102FC0: choose direction 1, 2 or 0 from the facing value 0x0F7720(a, player
   position) against +-0.6632 and clear the screen's +0x1A8 word.  Stack arg a. */
void r2_ScrPickDir(void *a)
{
    R2Scr *s = (R2Scr *)b10_scr;
    float f = sub_000F7720(a, r2_player->pos60);
    s->w1A8 = 0;
    if (f > 0.66322511f)
        sub_00101280(1);
    else if (-0.66322511f > f)
        sub_00101280(2);
    else
        sub_00101280(0);
}

/* 0x00109460: give o a random spin speed (+0xD0) and step (+0xC8).  Stack arg o. */
void r2_RandomSpin(R2Spin *o)
{
    float a = ((float)aab_Rand() * 3.0518509e-05f * 0.4f + 0.8f) * a50_framesPerSecond;
    float v = ((float)aab_Rand() * 3.0518509e-05f * 12.566371f + 37.699112f) * a50_frameSeconds;
    o->fD0 = v;
    o->fC8 = v / a * -1.0f;
}

/* 0x0010CAA0: when the player is in state 8, roll the kind-5 component's attack
   chance (table 0x31A094) and return attack 0xB (kinds 0/1) or 0xE (kinds 2/3), else 0.
   regargs: obj=EAX */
int r2_RollAttack(R2Actor *obj)
{
    R2Comp5B *c;
    int r = 0;
    if (!obj)
        for (;;) ;
    c = (R2Comp5B *)sub_0001D960(obj, 5);
    if (PlayerObj_GetState((PlayerObj *)&g_stats) == 8 &&
        r2_chance31A094[c->row150][c->col158] >= (float)aab_Rand() * 3.0518509e-05f) {
        switch (c->kind14C) {
        case 0:
        case 1:
            r = 0xB;
            break;
        case 2:
        case 3:
            r = 0xE;
            break;
        }
    }
    return r;
}

/* 0x0011A300: nudge the state's +0x14 value: up to 255 by 20 (flag 1, mode 0x10000)
   or 5, else down to 0 by 5 (mode 0x10000) or 20.  regargs: obj=EAX */
void r2_BodyAdjust14(R2Body *obj)
{
    float *v = &obj->st278->f14;
    uint32_t f = obj->flags20;
    if (f & 0x10000) {
        if (f & 1)
            b10_AddClampF(v, 20.0f, 255.0f);
        else
            b10_SubClampF(v, 5.0f, 0.0f);
    } else {
        if (f & 1)
            b10_AddClampF(v, 5.0f, 255.0f);
        else
            b10_SubClampF(v, 20.0f, 0.0f);
    }
}

/* 0x0011F480: save the +0x40 vector into +0x30 and set the motion values
   (+0x58 = -a, +0x54 = b, +0x50 = c, +0x5C = 1, +0x64 = d, +0x60 = d == 1).
   regargs: obj=EAX; a b c d are the stack args */
void r2_BodySetMotion(R2Body *obj, float a, float b, float c, float d)
{
    R2MotionSt *st = (R2MotionSt *)obj->st278;
    sub_000F5D40(st->v40, st->v30);
    st->f58 = 0.0f - a;
    st->f54 = b;
    st->f50 = c;
    st->f5C = 1.0f;
    st->f64 = d;
    st->f60 = (d == 1.0f) ? 1.0f : 0.0f;
}

/* 0x00120820: is the player out of self's reach (at least 200 away or 100 above or
   below)?  0 when obj's state flag 0x10000000 is set.  regargs: obj=EAX self=ESI */
int r2_PlayerOutOfReach(R2Body *obj, R2Body *self)
{
    if (obj->st278->flags04 & 0x10000000)
        return 0;
    if (a80_Get3ED238())
        return 1;
    if (sub_001B2770(self->pos60, r2_player->pos60) >= 200.0f)
        return 1;
    if (sub_001A3F30(self->y64 - ((R2Body *)r2_player)->y64) < 100.0f)
        return 0;
    return 1;
}

/* 0x0012D350: initialise the hook record at +0xA0 of b's state block (handler
   0x11F620, owners a and b, three identity matrices) and push it on a's owner list.
   regargs: a=EBX b=EDI */
void r2_HookInit(R2HookHost *a, R2HookBody *b)
{
    R2Owner *o = a->owner20;
    R2Hook *h = (R2Hook *)(b->st278 + 0xA0);
    sub_001B2150(h);
    h->fDC = 0.0f;
    h->fn04 = sub_0011F620;
    h->a10 = a;
    h->b14 = b;
    h->fE0 = a50_frameUnits * 0.008f;
    sub_001AD940(h->m18);
    sub_001AD940(h->m58);
    sub_001AD940(h->m98);
    sub_001B2160(o->listC4 + 0x180, h);
}
