/* Area rbk: Jack's aim rig (0x000D42F0..0x000D4C5F). Names inferred. */
#include "rbk.h"

/* 0x000D42F0: create Jack's aim rig (0x418 bytes, tag 0xB9). Sixteen joints of segment length
   1 hang along -z: positions and rest positions accumulate one segment each, speeds start
   at rest. A root record with eight child records (0x0001D160 / 0x0001D240) is attached
   and given count 0x10. No arguments; returns the rig. */
RbkRig *rbk_RigNew0D42F0(void)
{
    RbkRig *r = (RbkRig *)sub_00053AB0(0x418, 0, 0xB9);
    int i;

    r->a00 = 0;
    r->a04 = 0;
    r->cur08 = 0;
    r->next0C = 0;
    r->show14 = 0;
    r->step18 = 0;
    r->fade10 = 0.0f;
    r->time1C = 0.0f;
    r->size20 = 0.0f;
    r->p24[4] = 1.0f;
    r->len44[0] = 1.0f;
    r->vel184[0].x = 0.0f;
    r->vel184[0].y = 0.0f;
    r->vel184[0].z = 0.0f;
    r->vel184[0].w = 1.0f;
    r->pos84[0].x = 0.0f;
    r->pos84[0].y = 0.0f;
    r->pos84[0].z = -1.0f;
    r->pos84[0].w = 1.0f;
    for (i = 0; i < 15; i++) {
        r->len44[i + 1] = r->p24[4];
        r->vel184[i + 1].x = 0.0f;
        r->vel184[i + 1].y = 0.0f;
        r->vel184[i + 1].z = 0.0f;
        r->vel184[i + 1].w = 1.0f;
        r->pos84[i + 1].x = 0.0f;
        r->pos84[i + 1].y = 0.0f;
        r->pos84[i + 1].z = 0.0f - r->p24[4];
        r->pos84[i + 1].w = 1.0f;
        rbj_VecAdd(&r->pos84[i + 1], &r->pos84[i], &r->pos84[i + 1]);
        r->pos84[i + 1].w = 1.0f;
        r->rest294[i + 1].x = 0.0f;
        r->rest294[i + 1].y = 0.0f;
        r->rest294[i + 1].z = 0.0f - r->p24[4];
        r->rest294[i + 1].w = 1.0f;
        rbj_VecAdd(&r->rest294[i + 1], &r->rest294[i], &r->rest294[i + 1]);
        r->rest294[i + 1].w = 1.0f;
    }
    r->p24[0] = 0.5f;
    r->p24[1] = 0.5f;
    r->p24[2] = 0.5f;
    r->p24[3] = 0.5f;
    r->p24[6] = 0.1f;
    r->p24[5] = 1.0f;
    r->p24[7] = 0.0f;
    r->f394 = 2.625f;
    r->f398 = 0.0f;
    r->v39C.x = 0.0f;
    r->v39C.y = 0.0f;
    r->v39C.z = 0.0f;
    r->v39C.w = 1.0f;
    r->a3AC = 0;
    r->root3B0 = r1_StateNew(0);
    for (i = 0; i < 8; i++)
        r1b_RecAddChild(r->root3B0, r1_StateNew(i));
    r->root3B0->n04 = 0x10;
    r->a3BC = 0;
    r->f3B8 = 0.0f;
    r->f3C0[0] = 0.0f;
    r->f3C0[1] = 0.0f;
    r->f3C0[2] = 0.0f;
    r->f3C0[3] = 0.0f;
    r->blendTime410 = 0.0f;
    r->blendT414 = 0.0f;
    return r;
}

/* 0x000D4630: lay the rig's joints along the model's bone chain. The world matrix of the
   root bone (product of the parent chain) is inverted, keeping the world position as its
   translation. Following the chain of kind-10 bones (at most 16): every joint gets the
   segment length and a rest speed; mode 0 stacks the joints one segment apart along -z
   from that position; mode 1 walks the bones' matrices, measuring each segment as the
   distance to the next kind-10 bone. Called with stack args (r mode). */
void rbk_RigFollow0D4630(RbkRig *r, int mode)
{
    RbjMat4 inv, world;
    RbjVec4 v;
    RbkRigBone *b;
    float len;
    float *plen;
    int i;

    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 0.0f;
    v.w = 1.0f;
    rbj_MatIdentity(&world);
    for (b = r->root3B0->bone20; b != 0; b = b->parent80)
        rbj_MatMul(&world, b, &world);
    sub_001B1F70(&inv, &world);
    sub_000F5D40(&inv.r[3], &world.r[3]);
    inv.r[3].w = 1.0f;
    switch (mode) {
    case 0:
        b = r->root3B0->bone20->next88;
        i = 0;
        if (b == 0)
            return;
        plen = r->len44;
        do {
            if (b->kind8C != 10 || i >= 16)
                return;
            *plen = r->p24[4];
            r->vel184[i].x = 0.0f;
            r->vel184[i].y = 0.0f;
            r->vel184[i].z = 0.0f;
            r->vel184[i].w = 1.0f;
            v.x = 0.0f;
            v.y = 0.0f;
            v.z = 0.0f - r->p24[4];
            v.w = 1.0f;
            rbj_VecTransform(&r->pos84[i], &inv, &v);
            r->pos84[i].w = 1.0f;
            sub_000F5D40(&inv.r[3], &r->pos84[i]);
            inv.r[3].w = 1.0f;
            b = b->next88;
            i++;
            plen++;
        } while (b != 0);
        break;
    case 1:
        b = r->root3B0->bone20->next88;
        i = 0;
        if (b == 0)
            return;
        do {
            if (b->kind8C != 10 || i >= 16)
                return;
            len = r->p24[4];
            r->len44[i] = len;
            rbj_MatMul(&inv, &inv, b);
            r->vel184[i].x = 0.0f;
            r->vel184[i].y = 0.0f;
            r->vel184[i].z = 0.0f;
            r->vel184[i].w = 1.0f;
            inv.r[3].w = 1.0f;
            if (b->next88 != 0 && b->next88->kind8C == 10) {
                rbj_VecTransform(&v, &inv, &b->next88->m.r[3]);
                rbj_VecSub(&v, &v, &inv.r[3]);
                v.w = 1.0f;
                len = sub_00082D70(&v);
            }
            v.x = 0.0f;
            v.y = 0.0f;
            v.z = 0.0f - len;
            v.w = 1.0f;
            rbj_VecTransform(&r->pos84[i], &inv, &v);
            r->pos84[i].w = 1.0f;
            b = b->next88;
            i++;
        } while (b != 0);
        break;
    }
}

/* 0x000D4940: blend the rig parameters. While a blend time is set, the blend clock advances
   one frame unit and each of the eight parameters becomes start * (1 - t) + end * t with
   both weights clamped to 0..1; when the clock passes the time the blend ends.
   regargs: r=EAX. */
void rbk_RigBlend0D4940(RbkRig *r)
{
    float t, inv, a, b;
    int i;

    if (!(r->blendTime410 > 0.0f))
        return;
    t = a50_frameUnits + r->blendT414;
    r->blendT414 = t;
    inv = 1.0f / r->blendTime410;
    a = (r->blendTime410 - t) * inv;
    b = inv * t;
    if (0.0f > a)
        a = 0.0f;
    else if (a > 1.0f)
        a = 1.0f;
    if (0.0f > b)
        b = 0.0f;
    else if (b > 1.0f)
        b = 1.0f;
    for (i = 0; i < 8; i++)
        r->p24[i] = r->to3F0[i] * b + r->from3D0[i] * a;
    if (r->blendT414 > r->blendTime410) {
        r->blendTime410 = 0.0f;
        r->blendT414 = 0.0f;
    }
}

/* 0x000D4C60: show the rig's current record and fade in the next one. Records of the root's
   list with a bone are shown (0x0001D470) when they are the current or (while switching) the
   next record, hidden (0x0001D4B0) otherwise. While switching, the current bone's axes are
   scaled by 1 / (1 + fade) and the next one's by fade / 8 (at most 1, doubled with Jack's
   mode bit 0x40 or flag 2 at +0xD60); after 8 frame units the next record becomes current.
   Otherwise the current bone gets unit axes (doubled likewise unless the record id is 0).
   regargs: r=EAX. */
void rbk_RigScale0D4C60(RbkRig *r)
{
    RbjMat4 m;
    RbkRigRoot *rec, *cur, *nxt;
    float k, s;
    int i;

    m.r[0].x = 0.0f;
    m.r[0].y = 0.0f;
    m.r[0].z = 0.0f;
    m.r[0].w = 1.0f;
    for (i = 1; i < 4; i++) {
        m.r[i].x = 0.0f;
        m.r[i].y = 0.0f;
        m.r[i].z = 0.0f;
        m.r[i].w = 0.0f;
    }
    nxt = 0;
    cur = 0;
    for (rec = r->root3B0->next3C; rec != 0; rec = rec->next3C) {
        if (rec->bone20 == 0)
            continue;
        if (rec->id00 == r->cur08) {
            r1_ChildShow(r->root3B0, rec->id00);
            cur = rec;
        } else if (r->cur08 != r->next0C && rec->id00 == r->next0C) {
            r1_ChildShow(r->root3B0, rec->id00);
            nxt = rec;
        } else {
            r1_ChildHide(r->root3B0, rec->id00);
        }
    }
    if (r->cur08 != r->next0C) {
        k = r->fade10 + 1.0f;
        s = 1.0f / k;
        k = k * 0.125f;
        if (k > 1.0f)
            k = 1.0f;
        if ((RBK_JACK->modeEC & 0x40) || (RBK_JACK->flagsD60 & 2))
            k = k * 2.0f;
        rbj_MatIdentity(&m);
        rbj_VecScale4(&m.r[0], &m.r[0], s);
        rbj_VecScale4(&m.r[1], &m.r[1], s);
        rbj_VecScale4(&m.r[2], &m.r[2], s);
        sub_000F5D40(&cur->bone20->m.r[0], &m.r[0]);
        sub_000F5D40(&cur->bone20->m.r[1], &m.r[1]);
        sub_000F5D40(&cur->bone20->m.r[2], &m.r[2]);
        rbj_MatIdentity(&m);
        rbj_VecScale4(&m.r[0], &m.r[0], k);
        rbj_VecScale4(&m.r[1], &m.r[1], k);
        rbj_VecScale4(&m.r[2], &m.r[2], k);
        sub_000F5D40(&nxt->bone20->m.r[0], &m.r[0]);
        sub_000F5D40(&nxt->bone20->m.r[1], &m.r[1]);
        sub_000F5D40(&nxt->bone20->m.r[2], &m.r[2]);
        r->fade10 = r->fade10 + a50_frameUnits;
        if (r->fade10 >= 8.0f) {
            r->cur08 = r->next0C;
            r->fade10 = 0.0f;
        }
        return;
    }
    if (r->cur08 != 0 && ((RBK_JACK->modeEC & 0x40) || (RBK_JACK->flagsD60 & 2)))
        s = 2.0f;
    else
        s = 1.0f;
    rbj_MatIdentity(&m);
    rbj_VecScale4(&m.r[0], &m.r[0], s);
    rbj_VecScale4(&m.r[1], &m.r[1], s);
    rbj_VecScale4(&m.r[2], &m.r[2], s);
    sub_000F5D40(&cur->bone20->m.r[0], &m.r[0]);
    sub_000F5D40(&cur->bone20->m.r[1], &m.r[1]);
    sub_000F5D40(&cur->bone20->m.r[2], &m.r[2]);
}

/* 0x000D5050: place one rig segment. p1 moves onto p0 and p2 goes len away from it along
   the direction p1 -> p0 (the old p1). With t below 1 both are then pulled towards the
   segment that points from p0 away from target (VecLerp4 with t, p1 towards p0).
   regargs: p0=EAX p1=ESI p2=EDI, target/len/t on the stack (ESI is not preserved by the
   original). */
void rbk_RigSegment0D5050(const RbjVec4 *p0, RbjVec4 *p1, RbjVec4 *p2, const RbjVec4 *target, float len, float t)
{
    RbjVec4 d, a, b;

    d.x = 0.0f;
    d.y = 0.0f;
    d.z = 0.0f;
    d.w = 1.0f;
    a.x = 0.0f;
    a.y = 0.0f;
    a.z = 0.0f;
    a.w = 1.0f;
    b.x = 0.0f;
    b.y = 0.0f;
    b.z = 0.0f;
    b.w = 1.0f;
    rbj_VecSub(&d, p0, p1);
    rbj_VecNormalize(&d, &d);
    rbj_VecScale4(&d, &d, len);
    sub_000F5D40(p1, p0);
    p1->w = 1.0f;
    rbj_VecAdd(p2, p1, &d);
    p2->w = 1.0f;
    if (1.0f > t) {
        sub_000F5D40(&a, p0);
        a.w = 1.0f;
        rbj_VecSub(&d, &a, target);
        rbj_VecNormalize(&d, &d);
        rbj_VecScale4(&d, &d, len);
        rbj_VecAdd(&b, &a, &d);
        b.w = 1.0f;
        r4e_VecLerp4(p1, p1, &a, t);
        p1->w = 1.0f;
        r4e_VecLerp4(p2, p2, &b, t);
        p2->w = 1.0f;
    }
}

/* 0x000D5200: grow or shrink the rig's root bone. Show mode 1 (appear): the root record is
   shown, the light set rewound and flag bit 0 of 0x00418B40 cleared, then the size grows by
   1/16 per frame unit up to 1. Show mode 2 (vanish): size 1, light set rewound, then the
   size falls as 1 / (1 + 0.2 t) until t reaches 32, when the record is hidden, bit 0 set
   and the size becomes 0. Otherwise the size is 1. The bone's three axes are scaled by the
   size. Called with stack arg (r). */
void rbk_RigShow0D5200(RbkRig *r)
{
    RbkRigBone *bone = r->root3B0->bone20;
    RbjMat4 m;
    float t;

    switch (r->show14) {
    case 1:
        switch (r->step18) {
        case 0:
            r1_NodeShow(r->root3B0);
            r4b_NodePRewind(rbk_g418A80);
            rbk_g418B40 &= ~1u;
            r->step18++;
            r->size20 = 0.0f;
            break;
        case 1:
            r->time1C = r->time1C + a50_frameUnits;
            r->size20 = r->time1C * 0.0625f;
            if (r->time1C >= 16.0f) {
                r->show14 = 0;
                r->step18 = 0;
                r->time1C = 0.0f;
                r->size20 = 1.0f;
            }
            break;
        }
        break;
    case 2:
        switch (r->step18) {
        case 0:
            r->size20 = 1.0f;
            r4b_NodePRewind(rbk_g418A80);
            r->step18++;
            break;
        case 1:
            t = r->time1C + a50_frameUnits;
            r->time1C = t;
            r->size20 = 1.0f / (t * 0.2f + 1.0f);
            if (r->time1C >= 32.0f) {
                r1_NodeHide(r->root3B0);
                rbk_g418B40 |= 1;
                r->show14 = 0;
                r->step18 = 0;
                r->time1C = 0.0f;
                r->size20 = 0.0f;
            }
            break;
        }
        break;
    default:
        r->size20 = 1.0f;
        break;
    }
    rbj_MatIdentity(&m);
    rbj_MatCopy(&m, &bone->m);
    rbj_VecScale4(&m.r[0], &m.r[0], r->size20);
    rbj_VecScale4(&m.r[1], &m.r[1], r->size20);
    rbj_VecScale4(&m.r[2], &m.r[2], r->size20);
    rbj_MatCopy(&bone->m, &m);
}

/* 0x000D53B0: test the rig segment k for a hook target. The segment runs from Jack's feet
   (15 below the model position) past rig rest point k by the reach (0x000CA300). The boxes
   of the used, hookable entity slots whose object is solid and of kind 1 are tested
   (0x0001B4D0 / 0x0001BAD0); without a hit -1 is returned. With a hit the rest point
   becomes the hit point, except for k = 15: then the last rest point is set one reach
   before the hit and, if that sphere touches something (0x0001B9E0, second result in
   hit2), pulled back once more; every 8th frame an effect (0x30) and sound set 8 play.
   Returns 1 on a hit. Called with stack args (j r k hit hit2). */
int rbk_RigHook0D53B0(RbkJack *j, RbkRig *r, int k, RbjVec4 *hit, RbjVec4 *hit2)
{
    RbjVec4 feet, end, dir;
    RbkBox box;
    RbkSlot *s;
    RbjVec4 *rest, *last;
    float reach, rad;

    feet.x = 0.0f;
    feet.y = 0.0f;
    feet.z = 0.0f;
    feet.w = 1.0f;
    end.x = 0.0f;
    end.y = 0.0f;
    end.z = 0.0f;
    end.w = 1.0f;
    dir.x = 0.0f;
    dir.y = 0.0f;
    dir.z = 0.0f;
    dir.w = 1.0f;
    rad = sub_000CA300(j);
    reach = rad;
    sub_000F5D40(&feet, &j->modelFD8->pos60);
    feet.y = feet.y - 15.0f;
    rest = &r->rest294[k];
    sub_000F5D40(&end, rest);
    rbj_VecSub(&dir, &end, &feet);
    rbj_VecNormalize(&dir, &dir);
    rbj_VecScale4(&dir, &dir, reach);
    rbj_VecAdd(&end, &end, &dir);
    for (s = g_ac0_entities; (intptr_t)s < (intptr_t)(g_ac0_entities + 32); s++) {
        if ((s->flags00 & 1) && (s->flags00 & 0x10000000)
            && (s->obj120->flags0C & 0x20) && s->obj120->kindD0 == 1) {
            r1i_BoxBuild(s->obj120, &box);
            if (sub_0001BAD0(&box, &feet, &end, hit) != 0)
                goto found;
        }
    }
    return -1;
found:
    if (k != 15) {
        sub_000F5D40(rest, hit);
        return 1;
    }
    rbj_VecSub(&dir, &feet, hit);
    rbj_VecNormalize(&dir, &dir);
    rbj_VecScale4(&dir, &dir, reach);
    last = &r->rest294[15];
    rbj_VecAdd(last, hit, &dir);
    if (sub_0001B9E0(&rad, last, reach, hit, hit2) != 0) {   /* may update rad; reach keeps the value */
        rbj_VecSub(&dir, &feet, hit);
        rbj_VecNormalize(&dir, &dir);
        rbj_VecScale4(&dir, &dir, reach);
        rbj_VecAdd(last, last, &dir);
    }
    if ((rbk_frames42C918 & 7) == 0) {
        rbk_JackFx0D0060(j, 0x30, last);
        sub_000AA2E0(8);
    }
    return 1;
}

/* 0x000D56C0: set the rig parameters; a negative argument leaves its parameter alone. The
   segment length and parameters 1, 3, 5, 6, 7 are per frame unit (the segment length is
   copied to all 16 joints). Parameters 0 and 2 are fractions clamped to 1 and corrected for
   frame units above 1 (p0: ((2 - x) x + x) / 2 - x, p2: (x x + x) / 2 - x, times
   (1 - fu) (fu - 1) for p2 and (fu - 1) for p0, added to x).
   Called with stack args (r seg p5 p6 p7 p0 p1 p2 p3). */
void rbk_RigParams0D56C0(RbkRig *r, float seg, float p5, float p6, float p7, float p0, float p1, float p2, float p3)
{
    float fu;
    int i;

    if (seg >= 0.0f) {
        r->p24[4] = a50_frameUnits * seg;
        for (i = 0; i < 16; i++)
            r->len44[i] = r->p24[4];
    }
    if (p5 >= 0.0f)
        r->p24[5] = a50_frameUnits * p5;
    if (p6 >= 0.0f)
        r->p24[6] = a50_frameUnits * p6;
    if (p7 >= 0.0f)
        r->p24[7] = a50_frameUnits * p7;
    if (p0 >= 0.0f) {
        if (p0 > 1.0f)
            p0 = 1.0f;
        fu = a50_frameUnits;
        if (fu > 1.0f)
            p0 = (((2.0f - p0) * p0 + p0) * 0.5f - p0) * (fu - 1.0f) + p0;
        r->p24[0] = p0;
    }
    if (p1 >= 0.0f)
        r->p24[1] = a50_frameUnits * p1;
    if (p2 >= 0.0f) {
        if (p2 > 1.0f)
            p2 = 1.0f;
        fu = a50_frameUnits;
        if (fu > 1.0f)
            p2 = ((p2 * p2 + p2) * 0.5f - p2) * (1.0f - fu) * (fu - 1.0f) + p2;
        r->p24[2] = p2;
    }
    if (p3 >= 0.0f)
        r->p24[3] = a50_frameUnits * p3;
}

/* 0x000D58F0: let rig rest point k reach out from Jack's feet. Entities are tried first
   (0x000D53B0; a hit ends here). Otherwise the segment from the feet (15 below Jack's
   position) through the rest point, extended by the reach, is probed against the world:
   with a hit the rest point moves to it (k != 15); for k = 15 the last rest point is set one
   reach out along the hit normal, a sphere of that reach is pushed out of the world
   (0x000822D0 / 0x00080CF0) once more, and every 8th frame an effect (0x30) and sound set
   8 play. Called with stack args (r world mask unused k); the fourth is never read. */
void rbk_RigReach0D58F0(RbkRig *r, void *world, int mask, int unused, int k)
{
    RbjVec4 feet, end, hit, hit2, dir;
    RbjVec4 *rest, *last;
    RbkWorldHit *h;
    float reach;
    int set;

    feet.x = 0.0f;
    feet.y = 0.0f;
    feet.z = 0.0f;
    feet.w = 1.0f;
    end.x = 0.0f;
    end.y = 0.0f;
    end.z = 0.0f;
    end.w = 1.0f;
    hit.x = 0.0f;
    hit.y = 0.0f;
    hit.z = 0.0f;
    hit.w = 1.0f;
    hit2.x = 0.0f;
    hit2.y = 0.0f;
    hit2.z = 0.0f;
    hit2.w = 1.0f;
    dir.x = 0.0f;
    dir.y = 0.0f;
    dir.z = 0.0f;
    dir.w = 1.0f;
    reach = sub_000CA300(RBK_JACK);
    if (rbk_RigHook0D53B0(RBK_JACK, r, k, &hit, &hit2) > 0)
        return;
    sub_000F5D40(&feet, (const RbjVec4 *)((uint8_t *)g_playerObj + 0x60));
    feet.y = feet.y - 15.0f;
    rest = &r->rest294[k];
    sub_000F5D40(&end, rest);
    rbj_VecSub(&dir, &end, &feet);
    rbj_VecNormalize(&dir, &dir);
    rbj_VecScale4(&dir, &dir, reach);
    rbj_VecAdd(&end, &end, &dir);
    set = sub_00080970();
    sub_000824F0(world, set, &feet, &end, mask, 0);
    h = sub_00080CB0(set, &feet, &end);
    if (h == 0)
        return;
    if (k != 15) {
        sub_000F5D40(rest, &h->point40);
        return;
    }
    sub_000F5D40(&dir, &h->normal30);
    rbj_VecNormalize(&dir, &dir);
    rbj_VecScale4(&dir, &dir, reach);
    last = &r->rest294[15];
    rbj_VecAdd(last, &h->point40, &dir);
    set = sub_00080970();
    sub_000822D0(world, set, last, reach, mask, 0);
    h = sub_00080CF0(set, last);
    if (h != 0) {
        sub_000F5D40(&dir, &h->normal30);
        rbj_VecNormalize(&dir, &dir);
        rbj_VecScale4(&dir, &dir, reach);
        rbj_VecAdd(last, &h->point40, &dir);
    }
    if ((rbk_frames42C918 & 7) == 0) {
        rbk_JackFx0D0060(RBK_JACK, 0x30, last);
        sub_000AA2E0(8);
    }
}
