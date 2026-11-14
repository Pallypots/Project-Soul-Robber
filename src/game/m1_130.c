/* Area m1, file 130: small helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Seq130 { uint32_t flags00; int32_t step04; int32_t n08; } M1Seq130;
int  sub_000D9A70(int id);
void sub_000A4410(int a, int b);
void sub_000A2D40(int a, int b);
void sub_000A2D10(int a, int b);

/* 0x000B6F60: scripted sequence: mode 0 clears it, mode 1 starts it (flag 1, step 10), mode 3
 * jumps to step 0x14; each call counts; step 10 ends early on event 0xF3, otherwise plays cue
 * (0xA, 0) and shows sprite 0xA/0x20 in style 0xA2D40 (event 0x10E) or 0xA2D10; step 0x14 ends
 * it (returns 0). */
int m1_Seq0B6F60(int mode, M1Seq130 *s)
{
    if (mode == 0) {
        s->flags00 = 0;
        s->step04 = 0;
        s->n08 = 0;
        return 1;
    }
    if (mode == 1) {
        s->n08 = 0;
        s->flags00 |= 1;
        s->step04 = 10;
        return 1;
    }
    if (mode == 3) {
        s->flags00 = 0;
        s->step04 = 0x14;
    }
    s->n08++;
    if (s->step04 == 10) {
        if (sub_000D9A70(0xF3)) {
            s->step04 = 0x14;
            return 1;
        }
        sub_000A4410(0xA, 0);
        if (sub_000D9A70(0x10E))
            sub_000A2D40(0xA, 0x20);
        else
            sub_000A2D10(0xA, 0x20);
        return 1;
    }
    if (s->step04 == 0x14) {
        s->flags00 = 0;
        s->step04 = 0;
        return 0;
    }
    return 1;
}

typedef struct M1Cue130 { int32_t k0, k4, ev08, cue0C, ev10, cue14, cue18; } M1Cue130;
extern M1Cue130 m1_cuesA30C288[];
extern M1Cue130 m1_cuesB30CC98[];
void sub_000DFD40(int *a, int *b);
void sub_00049B00(int cue);
void sub_00048A00(int cue, int ms);

/* 0x000DE330: play the music cue for the current location: find the (area, room) entry from
 * 0xDFD40 in table B (alt) or A, then pick its first cue when event +0x08 is set (0x400 =
 * always), else its second or third by event +0x10; start it with a 1000 ms fade. */
void m1_MusicCue0DE330(int alt)
{
    int room, area;
    M1Cue130 *tbl;
    M1Cue130 *e;
    int i, c;
    sub_000DFD40(&area, &room);
    tbl = m1_cuesA30C288;
    if (alt)
        tbl = m1_cuesB30CC98;
    i = 0;
    for (e = tbl; e->k0 != -1; e++, i++)
        if (e->k0 == area && e->k4 == room)
            break;
    e = &tbl[i];
    if (e->k0 == -1)
        return;
    if (e->ev08 == -1)
        return;
    if (e->ev08 == 0x400 || sub_000D9A70(e->ev08)) {
        c = e->cue0C;
    } else {
        if (e->ev10 == -1)
            return;
        if (e->ev10 == 0x400 || sub_000D9A70(e->ev10))
            c = e->cue14;
        else
            c = e->cue18;
    }
    if (c == -1)
        return;
    sub_00049B00(c);
    sub_00048A00(c, 0x3E8);
}
