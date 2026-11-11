/* Area r1d, group 2: packet senders and animation track helpers 0x00013B70..0x000187E0. Names inferred. */
#include "r1d.h"

/* 0x00013B70: flip to the other packet buffer, emit a nine-value command
   into it and submit it. */
void r1d_PktSend9(int a, int b, int c, int d, int e, int f, int g, int h, int i)
{
    R1dPkt *p;
    r1b_pktIdx37B4A0 ^= 1;
    r1b_PktOp(&r1b_pkts37B4AC[r1b_pktIdx37B4A0]);
    p = &r1b_pkts37B4AC[r1b_pktIdx37B4A0];
    r1b_PktOp(p, a, b, c, d, e, f, g, h, i);
    if (!r1b_dma37B390)
        r1b_PktOp(p, 0, 0, 0);
    sub_000AD090(p);
    r1b_PktSubmit();
}

/* 0x000141B0: write a rectangle's colour and two corner registers into a
   fresh packet (0x000138F0) and submit it; returns r->result.
   regargs: r=ESI */
int r1d_RectSend(R1dRect *r)
{
    uint64_t *q = sub_000138F0();
    q[1] = ((((int64_t)(r->a | 0x100) << 8 | (int64_t)r->b) << 8 | (int64_t)r->g) << 8)
           | (int64_t)r->r;
    q[2] = (((uint64_t)r->z << 16 | (int64_t)r->y) << 16) | (int64_t)r->x;
    q[3] = (((uint64_t)r->z << 16 | (int64_t)(r->h / 2 + r->y)) << 16)
           | (int64_t)(r->w + r->x);
    r1b_PktSubmit();
    return r->result;
}

/* 0x00017AE0: apply the current key's element list of a track, last
   element first, with 0x00015150. Returns a.
   calls 0x00015150 with EAX=elem stack=(a, t) */
int r1d_TrackApplyA(int a, R1dTrack *t)
{
    R1dAnimBank *b;
    int32_t *list;
    char *elems;
    int n;
    if (!(t->flags & 1)) {
        b = t->bank;
        elems = b->elems;
        list = b->lists[(int)b->keys[t->key][t->frame - t->base].list];
        r1d_g37B554 = -1;
        if (list != 0) {
            n = 0;
            while (list[n] != -1) n++;
            n--;
            for (t->left = n; n >= 0; n--) {
                sub_00015150(elems + list[n] * 0x54, a, t);
                t->left--;
            }
        }
        t->left = 0;
    }
    return a;
}

/* 0x00017B70: as 0x00017AE0 with 0x00015E10.
   calls 0x00015E10 with EAX=elem stack=(a, t) */
int r1d_TrackApplyB(int a, R1dTrack *t)
{
    R1dAnimBank *b;
    int32_t *list;
    char *elems;
    int n;
    if (!(t->flags & 1)) {
        b = t->bank;
        elems = b->elems;
        list = b->lists[(int)b->keys[t->key][t->frame - t->base].list];
        r1d_g37B554 = -1;
        if (list != 0) {
            n = 0;
            while (list[n] != -1) n++;
            n--;
            for (t->left = n; n >= 0; n--) {
                sub_00015E10(elems + list[n] * 0x54, a, t);
                t->left--;
            }
        }
        t->left = 0;
    }
    return a;
}

/* 0x00017C00: as 0x00017AE0 with 0x00016B80.
   calls 0x00016B80 with EAX=elem stack=(a, t) */
int r1d_TrackApplyC(int a, R1dTrack *t)
{
    R1dAnimBank *b;
    int32_t *list;
    char *elems;
    int n;
    if (!(t->flags & 1)) {
        b = t->bank;
        elems = b->elems;
        list = b->lists[(int)b->keys[t->key][t->frame - t->base].list];
        r1d_g37B554 = -1;
        if (list != 0) {
            n = 0;
            while (list[n] != -1) n++;
            n--;
            for (t->left = n; n >= 0; n--) {
                sub_00016B80(elems + list[n] * 0x54, a, t);
                t->left--;
            }
        }
        t->left = 0;
    }
    return a;
}

/* 0x00017C90: as 0x00017AE0 with 0x00017650.
   calls 0x00017650 with ESI=t EDI=elem stack=(a) */
int r1d_TrackApplyD(int a, R1dTrack *t)
{
    R1dAnimBank *b;
    int32_t *list;
    char *elems;
    int n;
    if (!(t->flags & 1)) {
        b = t->bank;
        list = b->lists[(int)b->keys[t->key][t->frame - t->base].list];
        elems = b->elems;
        r1d_g37B554 = -1;
        if (list != 0) {
            n = 0;
            while (list[n] != -1) n++;
            n--;
            for (t->left = n; n >= 0; n--) {
                sub_00017650(t, elems + list[n] * 0x54, a);
                t->left--;
            }
        }
        t->left = 0;
    }
    return a;
}

/* 0x00018580: set or clear the menu flags for line i, then print message
   `id` of the line's table into the text block. */
void r1d_MenuLine(int i, int id, int a, int b, float c)
{
    switch (i) {
    case 0: case 1: case 2: case 3:
    case 17: case 18: case 19:
        a60_FlagsSet(r1b_menu37B580, 0x80);
        break;
    default:
        a60_FlagsClear(r1b_menu37B580, 0x80);
        break;
    }
    sub_0003FCB0(a1b_obj37B560, sub_0003FA70(a1b_slots37BEE8[i], id), a, b, c);
}

/* 0x000187E0: reset dst (0x000195F0) and copy src's settings into it.
   regargs: src=stack dst=EBX */
void r1d_SetCopy(R1dSet *src, R1dSet *dst)
{
    int i;
    sub_000195F0(dst);
    dst->d04 = src->d00;
    dst->d08 = src->d04;
    dst->blk = src->blk;
    for (i = 0; i < 2; i++)
        sub_000F5D40(&dst->v[i], &src->v[i]);
    dst->d558 = -1;
}
