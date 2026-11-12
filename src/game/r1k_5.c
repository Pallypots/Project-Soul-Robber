/* Area r1k, group 5: HUD life gauge loss 0x00028B10.
   Names inferred. */
#include "r1k.h"

/* 0x00028B10: step the life-loss animation of HUD sequence A. State 0
   sets a 10-unit timer and, while points are pending, picks state 1
   (shrink a whole gauge pip: more than one point pending or an even
   health) or state 2 (half pip); with nothing pending the request queue
   shifts by one entry. State 1 shrinks the current pip with the timer and
   at zero restores it and removes one or two points; state 2 waits for
   the timer and removes one point. */
void r1k_LifeLoseStep(void)
{
    R1kSeqA *s = &r1j_seqA37C4FC;
    R1kSprite *g;
    switch (s->state) {
    case 0:
        s->timer = 10.0f;
        if (s->pending > 0) {
            if (s->pending > 1)
                s->state = 1;
            else
                s->state = (s->health & 1) ? 1 : 2;
            return;
        }
        s->queue[0] = s->queue[1];
        s->queue[1] = s->queue[2];
        s->queue[2] = s->queue[3];
        s->queue[3] = s->queue[4];
        s->queue[4] = s->queue[5];
        s->queue[5] = s->queue[6];
        s->queue[6] = s->queue[7];
        s->queue[7] = 0;
        s->state = 0;
        return;
    case 1:
        a60_StepByFrame(&s->timer, 0);
        g = &s->pip[(s->health + 1) / 2 - 1];
        g->sy = g->sx = s->timer * 0.1f;
        if (!(0.0f >= s->timer))
            return;
        g->sy = g->sx = 1.0f;
        s->state = 0;
        if (s->health & 1)
            goto lose_one;
        s->pending -= 2;
        s->health -= 2;
        return;
    case 2:
        a60_StepByFrame(&s->timer, 0);
        if (!(0.0f >= s->timer))
            return;
        s->state = 0;
    lose_one:
        s->pending--;
        s->health--;
        return;
    }
}

/* 0x00028930: step the life-gain animation of HUD sequence A. State 0
   sets a 10-unit timer; with an even health it adds two pending points
   (or one) and starts growing the new pip from zero with a random
   wobble (state 1), with an odd health it adds one point (state 2);
   with nothing pending the request queue pops. Whenever the current
   request is 4 the pip's flash track restarts, its bit is set in w84 and
   sound 0x5D plays. State 1 grows the pip with the timer and at zero
   sets it to full size; state 2 only waits for the timer. */
void r1k_LifeGainStep(void)
{
    R1kSeqA *s = &r1j_seqA37C4FC;
    R1kSprite *g;
    int h, m;
    switch (s->state) {
    case 0:
        s->timer = 10.0f;
        if (!(s->health & 1)) {
            if (s->pending >= 2) {
                s->pending -= 2;
                h = s->health + 2;
            } else if (s->pending >= 1) {
                s->pending--;
                h = s->health + 1;
            } else {
                goto pop;
            }
            s->health = h;
            g = &s->pip[(h + 1) / 2 - 1];
            g->sy = g->sx = 0.0f;
            g->f14 = (float)(sub_001C7EE1() % 40 - 20);
            s->state = 1;
        } else {
            if (s->pending < 1)
                goto pop;
            s->pending--;
            s->health++;
            s->state = 2;
        }
        goto flash;
    pop:
        r1_QueuePop8(s->queue);
        s->state = 0;
    flash:
        if (s->queue[0] == 4) {
            m = (s->health + 1) / 2 - 1;
            r1b_TrackReset(&s->track[m]);
            s->w84 |= (uint16_t)(1 << m);
            sub_00048AF0(0x5D);
        }
        return;
    case 1:
        a60_StepByFrame(&s->timer, 0);
        g = &s->pip[(s->health + 1) / 2 - 1];
        g->sy = g->sx = (10.0f - s->timer) * 0.1f;
        if (!(0.0f >= s->timer))
            return;
        g->sy = g->sx = 1.0f;
        s->state = 0;
        return;
    case 2:
        a60_StepByFrame(&s->timer, 0);
        if (!(0.0f >= s->timer))
            return;
        s->state = 0;
        return;
    }
}
