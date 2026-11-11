/* Area r1i, group 4: sprite track steps 0x000181B0 and 0x00018340.
   Names inferred. */
#include "r1i.h"

/* 0x000181B0: run the current track command on item t->idx: read the key
   record that follows it (kind 0 fixed values, kind 1 interpolated by
   0x00017F70), and once the track time reaches the command's start time
   set the sprite up on first use, place it at the track origin plus the
   key values, draw it with 0x00017AE0 and advance its key sequence; mark
   the item finished when the sequence is done. Always marks the item seen
   and moves to the next item. regargs: t=EDI; calls 0x00017F70 with EAX=t */
void r1i_TrackStepA(R1iTrack *t)
{
    R1iTrkCmd *c = (R1iTrkCmd *)t->cur;
    R1iTrkItem *it = &t->items[t->idx];
    R1iTrkFix *k = (R1iTrkFix *)(c + 1);
    uint32_t f;
    t->cur = (uint8_t *)k;
    switch (k->kind) {
    case 0:
        t->cur = (uint8_t *)(k + 1);
        r1i_trkVal42CE60.x = (float)k->x;
        r1i_trkVal42CE60.y = (float)k->y;
        r1i_trkVal42CE60.z = (float)k->z;
        r1i_trkVal42CE60.sx = 1.0f;
        r1i_trkVal42CE60.sy = 1.0f;
        r1i_trkVal42CE60.rot = 0.0f;
        r1i_trkVal42CE60.col = 0x80808080;
        break;
    case 1:
        r1i_TrackLerp(t);
        break;
    }
    f = it->flags;
    if (!(f & 8) && t->time >= (float)c->start) {
        if (!(f & 4)) {
            it->flags = f | 4;
            sub_00014D00(&it->spr, t->data[c->data], t->tex[c->tex]);
            sub_00014E30(&it->spr, c->anim, 0, 0, 0);
        }
        it->spr.x = (float)t->x + r1i_trkVal42CE60.x;
        it->spr.y = (float)t->y + r1i_trkVal42CE60.y;
        it->spr.z = (int)((float)t->z + r1i_trkVal42CE60.z);
        it->spr.sx = r1i_trkVal42CE60.sx;
        it->spr.sy = r1i_trkVal42CE60.sy;
        it->spr.rot = r1i_trkVal42CE60.rot;
        it->spr.color = r1i_trkVal42CE60.col;
        a1b_val37B558 = sub_00017AE0(a1b_val37B558, &it->spr);
        r1i_SeqPlayUpdate(&it->spr);
        if (it->spr.flags & 1)
            it->flags |= 8;
    }
    it->flags |= 2;
    t->idx++;
}

/* 0x00018340: as 0x000181B0, drawing with 0x00017C00.
   regargs: t=EDI; calls 0x00017F70 with EAX=t */
void r1i_TrackStepC(R1iTrack *t)
{
    R1iTrkCmd *c = (R1iTrkCmd *)t->cur;
    R1iTrkItem *it = &t->items[t->idx];
    R1iTrkFix *k = (R1iTrkFix *)(c + 1);
    uint32_t f;
    t->cur = (uint8_t *)k;
    switch (k->kind) {
    case 0:
        t->cur = (uint8_t *)(k + 1);
        r1i_trkVal42CE60.x = (float)k->x;
        r1i_trkVal42CE60.y = (float)k->y;
        r1i_trkVal42CE60.z = (float)k->z;
        r1i_trkVal42CE60.sx = 1.0f;
        r1i_trkVal42CE60.sy = 1.0f;
        r1i_trkVal42CE60.rot = 0.0f;
        r1i_trkVal42CE60.col = 0x80808080;
        break;
    case 1:
        r1i_TrackLerp(t);
        break;
    }
    f = it->flags;
    if (!(f & 8) && t->time >= (float)c->start) {
        if (!(f & 4)) {
            it->flags = f | 4;
            sub_00014D00(&it->spr, t->data[c->data], t->tex[c->tex]);
            sub_00014E30(&it->spr, c->anim, 0, 0, 0);
        }
        it->spr.x = (float)t->x + r1i_trkVal42CE60.x;
        it->spr.y = (float)t->y + r1i_trkVal42CE60.y;
        it->spr.z = (int)((float)t->z + r1i_trkVal42CE60.z);
        it->spr.sx = r1i_trkVal42CE60.sx;
        it->spr.sy = r1i_trkVal42CE60.sy;
        it->spr.rot = r1i_trkVal42CE60.rot;
        it->spr.color = r1i_trkVal42CE60.col;
        a1b_val37B558 = sub_00017C00(a1b_val37B558, &it->spr);
        r1i_SeqPlayUpdate(&it->spr);
        if (it->spr.flags & 1)
            it->flags |= 8;
    }
    it->flags |= 2;
    t->idx++;
}
