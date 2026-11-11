/* Area r1, group 13: callers of the queue, resource and packet helpers 0x00029850..0x00058960. Names inferred. */
#include "r1.h"

/* 0x00029850: run queue timer 0x0037DAA4 (a running time of -1 waits forever).
   calls 0x000268D0 with EAX=q */
void r1_QTimerA(void)
{
    R1QTimer *t = &r1_qt37DAA4;
    switch (t->state) {
    case 0:
        t->t = t->reload;
        t->state = 1;
        break;
    case 1:
        if (t->t == -1.0f) return;
        sub_000720A0(&t->t, 0);
        if (t->t <= 0.0f) {
            r1_QueuePop8(t->q);
            t->state = 0;
        }
        break;
    }
}

/* 0x0002A000: run queue timer 0x0037DCFC (a running time of -1 waits forever).
   calls 0x000268D0 with EAX=q */
void r1_QTimerB(void)
{
    R1QTimer *t = &r1_qt37DCFC;
    switch (t->state) {
    case 0:
        t->t = t->reload;
        t->state = 1;
        break;
    case 1:
        if (t->t == -1.0f) return;
        sub_000720A0(&t->t, 0);
        if (t->t <= 0.0f) {
            r1_QueuePop8(t->q);
            t->state = 0;
        }
        break;
    }
}

/* 0x0002B310: run queue timer 0x0037F484 (a reload time of -1 waits forever).
   calls 0x000268D0 with EAX=q */
void r1_QTimerC(void)
{
    R1QTimer *t = &r1_qt37F484;
    switch (t->state) {
    case 0:
        t->t = t->reload;
        t->state = 1;
        break;
    case 1:
        if (t->reload == -1.0f) return;
        sub_000720A0(&t->t, 0);
        if (t->t <= 0.0f) {
            r1_QueuePop8(t->q);
            t->state = 0;
        }
        break;
    }
}

/* 0x00038F10: write a framed packet of the queued quads; returns the end of the buffer.
   calls 0x00038AD0 with ECX=p+4 ESI=0x003DA320 */
uint32_t *r1_PacketBuild(uint32_t *p)
{
    uint32_t *hdr, *end, n;
    p[0] = 0x10000000;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0x11000000;
    hdr = p + 4;
    end = sub_00038AD0(hdr + 4, r1_pk3DA320);
    n = ((uint32_t)((uint8_t *)end - (uint8_t *)hdr) >> 4) - 1;
    hdr[1] = 0;
    hdr[2] = 0;
    hdr[0] = n | 0x10000000;
    hdr[3] = n | 0x50000000;
    end[1] = 0;
    end[2] = 0;
    end[3] = 0;
    end[0] = 0x60000000;
    return end;
}

/* 0x00058960: stop resource id when it is idle and owned elsewhere; 0 on success, -1 otherwise.
   calls 0x00058220 with EAX=r */
int r1_ResStop(int id)
{
    R1Res *r = sub_00057F80(id);
    if (r == 0 || r->a == sub_001AD560() || r->state != 0) return -1;
    if (sub_001AD440(r->a) == -1) return -1;
    if (sub_001AA310(r->b) == -1) return -1;
    r->state = 3;
    r->a = -1;
    r->b = -1;
    if (r1_g3E3F90 == -1) r1_ResRelease(r);
    return 0;
}
