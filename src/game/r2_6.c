/* Area r2, group 6: mixed helpers (0x000E48C0..0x0011B0CF). Names inferred. */
#include "r2.h"

/* 0x000E48C0: advance the sequence's animation step and play the player animation
   from table 0x317758 (column by mode 0x3F0A7C); a negative entry ends the sequence.
   regargs: q=ESI */
void r2_SeqStep(R2Seq *q)
{
    int n, id;
    if (q->on510 && PlayerObj_TimerDone(&g_stats)) {
        n = ++q->step514;
        if (g_acb_3F0A7C == 4)
            id = r2_anim317758[q->row][n][0];
        else
            id = r2_anim317758[q->row][n][1];
        if (id < 0) {
            q->on510 = 0;
            q->step514 = 0;
        } else if (r2_player->part30->i08 != id) {
            PlayerObj_SetAnim(&g_stats, id);
        }
    }
}

/* 0x000E8080: run value v through the two optional fades (0x3F49E0 with 3 steps,
   0x3F4A7C with 0x3F49DC steps).  regargs: v=EAX; returns EAX */
int r2_ApplyFades(int v)
{
    if (aec_3F49D0) {
        r2_fade3F49E0[0] = 0.0f;
        r2_fade3F49E0[1] = 0.0f;
        sub_000150B0(r2_fade3F49E0, 3);
        v = sub_00017C00(v, r2_fade3F49E0);
        sub_00014E80(r2_fade3F49E0);
    }
    if (aec_3F49D4) {
        r2_fade3F4A7C[0] = 0.0f;
        r2_fade3F4A7C[1] = 0.0f;
        sub_000150B0(r2_fade3F4A7C, r2_g3F49DC);
        v = sub_00017C00(v, r2_fade3F4A7C);
        sub_00014E80(r2_fade3F4A7C);
    }
    return v;
}

/* 0x000E8D00: take a free slot of 0x3F4D10, initialise it with (a, b) and a random
   angle; returns its index or -1.  Stack args a b. */
int r2_SlotAlloc(int a, int b)
{
    R2Slot *s;
    int i = 0;
    for (s = r2_slots3F4D10; s < r2_slots3F4D10 + 16; s++, i++) {
        if (!(s->flags & 1)) {
            s = &r2_slots3F4D10[i];
            s->flags |= 1;
            sub_00014E30(s->obj04, 3, a, b, 0);
            s->f24 = 1.0f;
            s->f20 = 1.0f;
            s->f18 = (float)(aab_Rand() % 360);
            return i;
        }
    }
    return -1;
}

/* 0x000F43E0: unless busy (+0x108 = 2/3), set the boss direction flag from the
   facing value toward the player (outside +-2.3038 rad -> 1, else 0). */
void r2_BossPickDir(void)
{
    R2Boss2 *o = (R2Boss2 *)g_acb_bossMgr;
    void *p = o->link8C;
    int *d;
    float f;
    if (o->i104 != 2 && o->i100 == 1) {
        d = &o->dir108;
        if (*d == 2 || *d == 3)
            return;
        f = sub_000F7720(p, r2_player->pos60);
        if (f > 2.3038347f || -2.3038347f > f)
            *d = 1;
        else
            *d = 0;
        return;
    }
    o->dir108 = 0;
}

/* 0x000FE9E0: turn obj toward the player (4.5 degrees per frame unit); the first
   time arg's +0x68 exceeds 0.15 show the minion's +0x94 object, afterwards send
   event 0x1E when 0x0F5D00 reports done.  Stack args obj arg. */
void r2_MinionTurn(R2Actor *obj, R2Arg68 *arg)
{
    R2Minion *m = (R2Minion *)afc_minion;
    sub_000F7C40(obj, r2_player, a50_frameUnits * 0.07853982f);
    if (!m->i9C) {
        if (arg->f68 > 0.15f) {
            sub_0001D610(m->obj94);
            m->i9C = 1;
        }
    } else if (sub_000F5D00(obj)) {
        sub_000F3D10(obj, arg, 0x1E);
    }
}

/* 0x00102E80: pull obj's position back to within 130 units (XZ) of 0x3194C8.
   regargs: obj=EAX */
void r2_ClampToCenter(R2Actor *obj)
{
    float *pos = obj->pos60;
    float d[4], len;
    sub_001AD9F0(d, pos, r2_center3194C8);
    len = afc_VecLengthXZ(d);
    if (len > 130.0f) {
        sub_001AD9F0(d, pos, r2_center3194C8);
        sub_001AD7E0(d, d);
        sub_001ADB60(d, d, len - 130.0f);
        sub_001AD9F0(pos, pos, d);
    }
}

/* 0x00103640: as 0x102FC0 with +-0.6981 limits; also clears +0x1AC and records the
   side in +0x1CC (or sets +0x1A8 when centred).  Stack arg a. */
void r2_ScrPickDirB(void *a)
{
    R2Scr2 *s = (R2Scr2 *)b10_scr;
    float f = sub_000F7720(a, r2_player->pos60);
    s->f1AC = 0.0f;
    s->w1A8 = 0;
    if (f > 0.69813174f) {
        sub_00101280(1);
        s->i1CC = 0;
    } else if (-0.69813174f > f) {
        sub_00101280(2);
        s->i1CC = 1;
    } else {
        sub_00101280(0);
        s->w1A8 = 1;
    }
}

/* 0x00113F10: is pt within 130 units of self, -50..20 above it and within
   +-1.2217 rad of its facing?  On success store distance and angle.
   regargs: self=EDI pt=ESI; dist ang are the stack args */
int r2_PointInView(R2Body *self, const float *pt, float *dist, float *ang)
{
    float d, dy, a;
    d = r4_Distance(self->pos60, pt);
    if (d > 130.0f)
        return 0;
    dy = pt[1] - self->y64;
    if (-50.0f > dy || dy > 20.0f)
        return 0;
    a = sub_00113290(self, pt);
    if (-1.2217305f > a || a > 1.2217305f)
        return 0;
    *dist = d;
    *ang = a;
    return 1;
}

/* 0x0011B040: may self attack: other not flagged, player distance within
   [rec0, rec1], facing angle below rec2 and a 1-in-rec3 random roll.  Stack args. */
int r2_InAttackCone(R2Actor *self, R2Body *other, const float *rec)
{
    float d = sub_001B2770(self->pos60, r2_player->pos60);
    float a = sub_001A3F30(sub_00113200(self, r2_player->pos60));
    if (!(other->flags20 & 1) && d >= rec[0] && rec[1] >= d && rec[2] > a &&
        aab_Rand() % (int)rec[3] < 1)
        return 1;
    return 0;
}
