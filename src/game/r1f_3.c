/* Area r1f, group 3: stage fade state machines 0x00028080..0x0002B950. Names inferred. */
#include "r1f.h"

/* 0x00029680: fade stage C out over 20 units, then pop its request queue. */
void r1f_FadeOutC(void)
{
    R1fFade *f = &r1_qt37DAA4;
    switch (f->state) {
    case 0:
        r1f_flags37DAA0 |= 1;
        f->t = 20.0f;
        f->state = 1;
        break;
    case 1:
        sub_000720A0(&f->t, 0);
        f->level = (uint8_t)(int)((20.0f - f->t) * 6.4f);
        if (f->t <= 0.0f) {
            f->q[0] = f->q[1];
            f->q[1] = f->q[2];
            f->q[2] = f->q[3];
            f->q[3] = f->q[4];
            f->q[4] = f->q[5];
            f->q[5] = f->q[6];
            f->q[6] = f->q[7];
            f->level = 0x80;
            f->q[7] = 0;
            f->state = 0;
        }
        break;
    }
}

/* 0x00029770: fade stage C in over 20 units, then pop its request queue. */
void r1f_FadeInC(void)
{
    R1fFade *f = &r1_qt37DAA4;
    switch (f->state) {
    case 0:
        f->t = 20.0f;
        f->state = 1;
        break;
    case 1:
        sub_000720A0(&f->t, 0);
        f->level = (uint8_t)(int)(f->t * 6.4f);
        if (f->t <= 0.0f) {
            r1f_flags37DAA0 &= ~1u;
            f->q[0] = f->q[1];
            f->q[1] = f->q[2];
            f->q[2] = f->q[3];
            f->q[3] = f->q[4];
            f->q[4] = f->q[5];
            f->q[5] = f->q[6];
            f->q[6] = f->q[7];
            f->level = 0;
            f->q[7] = 0;
            f->state = 0;
        }
        break;
    }
}

/* 0x00028630: open stage A's curtain (level 304 -> 0 along a sine) over 20
   units, then pop its request queue. */
void r1f_SeqAOpen(void)
{
    R1fSeqA *s = &r1f_seqA37C540;
    switch (s->state) {
    case 0:
        s->flags |= 1;
        s->t = 20.0f;
        s->level16 = 0x130;
        s->state = 1;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        s->level16 = (int16_t)(int)(304.0f - sub_001A3ED0((20.0f - s->t) * 4.5f * 0.017453292f) * 304.0f);
        if (s->t <= 0.0f) {
            s->q[0] = s->q[1];
            s->q[1] = s->q[2];
            s->q[2] = s->q[3];
            s->q[3] = s->q[4];
            s->q[4] = s->q[5];
            s->q[5] = s->q[6];
            s->q[6] = s->q[7];
            s->q[7] = 0;
            s->state = 0;
        }
        break;
    }
}

/* 0x00028740: close stage A's curtain over 20 units, then latch two player
   stats, reset the stage counters and pop the request queue. */
void r1f_SeqAClose(void)
{
    R1fSeqA *s = &r1f_seqA37C540;
    switch (s->state) {
    case 0:
        s->t = 20.0f;
        s->state = 1;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        s->level16 = (int16_t)(int)(304.0f - sub_001A3ED0(s->t * 4.5f * 0.017453292f) * 304.0f);
        if (s->t <= 0.0f) {
            s->w42 = 0;
            s->d30 = Stats_Get(&g_stats, 0);
            s->d34 = Stats_Get(&g_stats, 1);
            s->flags &= ~1u;
            s->q[0] = s->q[1];
            s->q[1] = s->q[2];
            s->q[2] = s->q[3];
            s->q[3] = s->q[4];
            s->q[4] = s->q[5];
            s->q[5] = s->q[6];
            s->q[6] = s->q[7];
            s->d38 = 0;
            s->w40 = 0;
            s->d3C = 0;
            s->q[7] = 0;
            s->state = 0;
            s->f44 = 120.0f;
        }
        break;
    }
}

/* 0x00028890: stage A wait: count down f44 (120 when unset; -1 waits
   forever), then notify and pop the request queue.
   calls 0x000268D0 with EAX=q */
void r1f_SeqAWait(void)
{
    R1fSeqA *s = &r1f_seqA37C540;
    switch (s->state) {
    case 0:
        s->t = (s->f44 != 0.0f) ? s->f44 : 120.0f;
        s->level16 = 0;
        s->state = 1;
        break;
    case 1:
        if (s->t == -1.0f)
            return;
        sub_000720A0(&s->t, 0);
        if (s->t <= 0.0f) {
            sub_000243B0(0, 0);
            r1_QueuePop8(s->q);
            s->state = 0;
        }
        break;
    }
}

/* 0x00028EB0: fade stage B out (level 128 -> 0 along a sine) over 10 units,
   remembering player stat 3, then pop its request queue. */
void r1f_SeqBFadeOut(void)
{
    R1fSeqB *s = &r1f_seqB37D430;
    switch (s->state) {
    case 0:
        s->flags |= 1;
        s->level = 0x80;
        s->t = 10.0f;
        s->w46 = (uint16_t)Stats_Get(&g_stats, 3);
        s->f40 = 0.0f;
        s->state++;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        s->level = (int16_t)(int)(128.0f - sub_001A3ED0((10.0f - s->t) * 9.0f * 0.017453292f) * 128.0f);
        if (s->t <= 0.0f) {
            s->q[0] = s->q[1];
            s->q[1] = s->q[2];
            s->q[2] = s->q[3];
            s->q[3] = s->q[4];
            s->q[4] = s->q[5];
            s->q[5] = s->q[6];
            s->q[6] = s->q[7];
            s->q[7] = 0;
            s->state = 0;
        }
        break;
    }
}

/* 0x00028FE0: fade stage B back in over 10 units, then pop its request
   queue. */
void r1f_SeqBFadeIn(void)
{
    R1fSeqB *s = &r1f_seqB37D430;
    switch (s->state) {
    case 0:
        s->t = 10.0f;
        s->state = 1;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        s->level = (int16_t)(int)(128.0f - sub_001A3ED0(s->t * 9.0f * 0.017453292f) * 128.0f);
        if (s->t <= 0.0f) {
            s->flags &= ~1u;
            s->d30 = s->d34;
            s->q[0] = s->q[1];
            s->q[1] = s->q[2];
            s->q[2] = s->q[3];
            s->q[3] = s->q[4];
            s->q[4] = s->q[5];
            s->q[5] = s->q[6];
            s->q[6] = s->q[7];
            s->q[7] = 0;
            s->state = 0;
        }
        break;
    }
}

/* 0x000290F0: stage B selector: every 6 units step w46 to the next slot
   (0..3) whose player stat 8+slot is set; stop at the slot in stat 3. */
void r1f_SeqBCycle(void)
{
    R1fSeqB *s = &r1f_seqB37D430;
    float t;
    switch (s->state) {
    case 0:
        s->state = 1;
        s->t = 6.0f;
        /* fall through */
    case 1:
        sub_000720A0(&s->t, 0);
        t = s->t;
        s->f40 = (6.0f - t) * (1.0f / 6.0f);
        if (t <= 0.0f) {
            do {
                s->w46 = (s->w46 < 3) ? (uint16_t)(s->w46 + 1) : 0;
            } while (Stats_Get(&g_stats, s->w46 + 8) < 0);
            s->f40 = 0.0f;
            if (s->w46 == Stats_Get(&g_stats, 3)) {
                s->q[0] = s->q[1];
                s->q[1] = s->q[2];
                s->q[2] = s->q[3];
                s->q[3] = s->q[4];
                s->q[4] = s->q[5];
                s->q[5] = s->q[6];
                s->q[6] = s->q[7];
                s->q[7] = 0;
            } else {
                s->t += 6.0f;
            }
        }
        break;
    }
}

/* 0x00029230: start stage B's stepper and wait 180 units, then take d38 as
   the new d34 and pop the request queue. */
void r1f_SeqBStepWait(void)
{
    R1fSeqB *s = &r1f_seqB37D430;
    switch (s->state) {
    case 0:
        sub_00014E30(r1f_stepper37D51C, 2, 0, 0, 0);
        s->t = 180.0f;
        s->state++;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        if (s->t <= 0.0f) {
            s->q[0] = s->q[1];
            s->q[1] = s->q[2];
            s->q[2] = s->q[3];
            s->q[3] = s->q[4];
            s->q[4] = s->q[5];
            s->q[5] = s->q[6];
            s->q[6] = s->q[7];
            s->q[7] = 0;
            s->d34 = s->d38;
            s->state = 0;
        }
        break;
    }
}

/* 0x00029310: stage B zoom: grow the scale over 10 units, hold 60, wait 60,
   then shrink back over 60 units and pop the request queue.
   calls 0x000268D0 with EAX=q */
void r1f_SeqBZoom(void)
{
    R1fSeqB *s = &r1f_seqB37D430;
    float t, a, x;
    switch (s->state) {
    case 0:
        s->t = 10.0f;
        s->state = 1;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        t = s->t;
        a = 10.0f - t;
        x = a * 0.08f + 1.0f;
        r1f_scaleY37D8E4 = a * 0.04f + 1.0f;
        r1f_scaleX37D8E0 = x;
        r1f_scaleX37D94C = x;
        if (t <= 0.0f) {
            s->t = 60.0f;
            s->state++;
        }
        break;
    case 2:
        sub_000720A0(&s->t, 0);
        if (s->t <= 0.0f) {
            s->t = 60.0f;
            s->state++;
        }
        break;
    case 3:
        sub_000720A0(&s->t, 0);
        t = s->t;
        x = t * (0.8f / 60.0f) + 1.0f;
        r1f_scaleX37D8E0 = x;
        r1f_scaleX37D94C = x;
        r1f_scaleY37D8E4 = t * (0.4f / 60.0f) + 1.0f;
        if (t <= 0.0f) {
            r1_QueuePop8(s->q);
            s->state = 0;
        }
        break;
    }
}

/* 0x00029470: close stage B's curtain (level 256 -> 0 along a sine) over 20
   units, then pop its request queue. */
void r1f_SeqBCurtainOpen(void)
{
    R1fSeqB *s = &r1f_seqB37D430;
    switch (s->state) {
    case 0:
        s->flags |= 1;
        s->level = 0x100;
        s->t = 20.0f;
        s->state = 1;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        s->level = (int16_t)(int)(256.0f - sub_001A3ED0((20.0f - s->t) * 4.5f * 0.017453292f) * 256.0f);
        if (s->t <= 0.0f) {
            s->q[0] = s->q[1];
            s->q[1] = s->q[2];
            s->q[2] = s->q[3];
            s->q[3] = s->q[4];
            s->q[4] = s->q[5];
            s->q[5] = s->q[6];
            s->q[6] = s->q[7];
            s->q[7] = 0;
            s->state = 0;
        }
        break;
    }
}

/* 0x00029580: close stage B's curtain back over 20 units, then pop its
   request queue. */
void r1f_SeqBCurtainClose(void)
{
    R1fSeqB *s = &r1f_seqB37D430;
    switch (s->state) {
    case 0:
        s->t = 20.0f;
        s->state = 1;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        s->level = (int16_t)(int)(256.0f - sub_001A3ED0(s->t * 4.5f * 0.017453292f) * 256.0f);
        if (s->t <= 0.0f) {
            s->flags &= ~1u;
            s->q[0] = s->q[1];
            s->q[1] = s->q[2];
            s->q[2] = s->q[3];
            s->q[3] = s->q[4];
            s->q[4] = s->q[5];
            s->q[5] = s->q[6];
            s->q[6] = s->q[7];
            s->q[7] = 0;
            s->state = 0;
        }
        break;
    }
}
