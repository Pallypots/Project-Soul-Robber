/* Area r6h: demo player state step, demo_player.c area (r6h_10). Names inferred. */
#include "r6h.h"

/* 0x0008CE10: run one step of the demo player p. State 0 starts the demo;
   state 1 loads all twelve tracks (repeating passes until every track reports
   ready, with loaders 4 and 5 in mode 5), rebuilds the key and event lists and
   binds them; state 2 prepares the events; state 3 waits for the demo to be
   ready and starts it; state 4 marks the player done and returns to state 0.
   The replaced lists are released at the end. Returns 0 or the error of a
   failed list step. */
int r6h_DemoPlayerStep(R6hDemoPlayer *p)
{
    int result = 0;
    void *keys = 0;
    void *events = 0;
    int r;

    switch (p->state) {
    case 0:
        sub_000893C0(p->demo);
        p->state = 1;
        break;
    case 1: {
        int pass, bad, i;
        sub_0008BCF0(4, 5);
        sub_0008BCF0(5, 5);
        for (pass = 0;; pass++) {
            bad = 0;
            for (i = 0; i < 12; i++) {
                if (!sub_000898C0(p->demo, r6h_demoTracks2700E0[i], pass))
                    bad |= 1;
            }
            if (!bad)
                break;
        }
        sub_0008BCF0(4, 1);
        sub_0008BCF0(5, 1);
        keys = p->demo->keys;
        p->demo->keys = 0;
        r = sub_0008B480(&p->demo->keys, keys);
        if (r) {
            result = r;
            break;
        }
        events = p->demo->events;
        p->demo->events = 0;
        r = sub_0008C9B0(&p->demo->events, events);
        if (r) {
            result = r;
            break;
        }
        sub_0008B680(p->demo->keys, p->demo->events, events);
        sub_000894E0(p->demo);
        p->state = 2;
        break;
    }
    case 2:
        r = sub_0008BFD0(p->demo->events, p->demo);
        if (r) {
            result = r;
            break;
        }
        p->state = 3;
        break;
    case 3:
        if (sub_000896E0(p->demo)) {
            sub_000899C0(p->demo);
            sub_000896C0(p->demo, 0x1FF00);
            p->state = 4;
        }
        break;
    case 4:
        p->done = 3;
        p->state = 0;
        break;
    }
    sub_0008B400(keys);
    sub_0008BF70(events);
    return result;
}
