/* Area r1, group 9: hold detector 0x0004EEE0. Names inferred. */
#include "r1.h"

/* 0x0004EEE0: hold detector i: after 30 matching frames (then every 6) out takes b, otherwise src.
   regargs: i=EAX a=ESI b=EDX */
int r1_HoldStep(int i, int a, int b)
{
    R1Hold *h = &r1_holds[i];
    switch (h->state) {
    case 0:
        h->state = 1;
        h->cnt = 30;
        /* fall through */
    case 1:
    case 2:
        if (a == b) {
            if (--h->cnt < 0) {
                h->state = 2;
                h->cnt = 6;
                h->out = b;
                return 0;
            }
            h->out = h->src;
            return 0;
        }
        h->state = 0;
        h->out = h->src;
        return 0;
    }
    return 0;
}

/* 0x0004EF60: second hold detector of record i (same rules as 0x0004EEE0).
   regargs: i=EAX a=ESI b=EDX */
int r1_HoldStep2(int i, int a, int b)
{
    R1Hold *h = &r1_holds[i];
    switch (h->state2) {
    case 0:
        h->state2 = 1;
        h->cnt2 = 30;
        /* fall through */
    case 1:
    case 2:
        if (a == b) {
            if (--h->cnt2 < 0) {
                h->state2 = 2;
                h->cnt2 = 6;
                h->out2 = b;
                return 0;
            }
            h->out2 = h->src2;
            return 0;
        }
        h->state2 = 0;
        h->out2 = h->src2;
        return 0;
    }
    return 0;
}
