/* Area r1f, group 5: stage H 0x0002ABD0. Names inferred. */
#include "r1f.h"

/* 0x0002ABD0: stage H fade-in over 100 units: level and every pair's second
   value follow the timer, first values are held at 1; then pop the queue. */
void r1f_SeqHFadeIn(void)
{
    R1fStageH *s = &r1f_seqH37EDEC;
    int i;
    switch (s->state) {
    case 0:
        s->t = 100.0f;
        s->state = 1;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        s->level = (uint8_t)(int)(s->t * 0.01f * 128.0f);
        for (i = 0; i < 13; i++) {
            s->pair[i].a = 1.0f;
            s->pair[i].b = s->t * 0.01f;
        }
        if (s->t <= 0.0f) {
            s->q[0] = s->q[1];
            s->q[1] = s->q[2];
            s->q[2] = s->q[3];
            s->q[3] = s->q[4];
            s->q[4] = s->q[5];
            s->q[5] = s->q[6];
            s->q[6] = s->q[7];
            s->level = 0;
            s->q[7] = 0;
            s->state = 0;
        }
        break;
    }
}

