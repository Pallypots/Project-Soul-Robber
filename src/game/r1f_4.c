/* Area r1f, group 4: stage fades D..G 0x000299F0..0x0002A6C0 (shared
   template: count 20 units down, drive a fade level, then pop the stage's
   request queue). Names inferred. */
#include "r1f.h"

/* 0x000299F0: fade stage D out over 20 units, then pop its request queue. */
void r1f_SeqDFadeOut(void)
{
    R1fStage *s = &r1f_seqD37DC24;
    switch (s->state) {
    case 0:
        s->flags |= 1;
        s->t = 20.0f;
        s->state = 1;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        s->level = (uint8_t)(int)((20.0f - s->t) * 6.4f);
        if (s->t <= 0.0f) {
            s->q[0] = s->q[1];
            s->q[1] = s->q[2];
            s->q[2] = s->q[3];
            s->q[3] = s->q[4];
            s->q[4] = s->q[5];
            s->q[5] = s->q[6];
            s->q[6] = s->q[7];
            s->level = 0x80;
            s->q[7] = 0;
            s->state = 0;
        }
        break;
    }
}

/* 0x00029AE0: fade stage D in over 20 units, then pop its request queue. */
void r1f_SeqDFadeIn(void)
{
    R1fStage *s = &r1f_seqD37DC24;
    switch (s->state) {
    case 0:
        s->t = 20.0f;
        s->state = 1;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        s->level = (uint8_t)(int)(s->t * 6.4f);
        if (s->t <= 0.0f) {
            s->flags &= ~1u;
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

/* 0x00029CE0: fade stage D's second layer in over 20 units, then pop the request queue. */
void r1f_SeqDFadeIn2(void)
{
    R1fStage *s = &r1f_seqD37DC24;
    switch (s->state) {
    case 0:
        s->t = 20.0f;
        s->state = 1;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        s->level2 = (uint8_t)(int)(s->t * 6.4f);
        if (s->t <= 0.0f) {
            s->flags &= ~1u;
            s->q[0] = s->q[1];
            s->q[1] = s->q[2];
            s->q[2] = s->q[3];
            s->q[3] = s->q[4];
            s->q[4] = s->q[5];
            s->q[5] = s->q[6];
            s->q[6] = s->q[7];
            s->level2 = 0;
            s->q[7] = 0;
            s->state = 0;
        }
        break;
    }
}

/* 0x0002A070: fade stage F out over 20 units, then pop its request queue. */
void r1f_SeqFFadeOut(void)
{
    R1fStage *s = &r1f_seqF37ED00;
    switch (s->state) {
    case 0:
        s->flags |= 1;
        s->t = 20.0f;
        s->state = 1;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        s->level = (uint8_t)(int)((20.0f - s->t) * 6.4f);
        if (s->t <= 0.0f) {
            s->q[0] = s->q[1];
            s->q[1] = s->q[2];
            s->q[2] = s->q[3];
            s->q[3] = s->q[4];
            s->q[4] = s->q[5];
            s->q[5] = s->q[6];
            s->q[6] = s->q[7];
            s->level = 0x80;
            s->q[7] = 0;
            s->state = 0;
        }
        break;
    }
}

/* 0x0002A160: fade stage F in over 20 units, then pop its request queue. */
void r1f_SeqFFadeIn(void)
{
    R1fStage *s = &r1f_seqF37ED00;
    switch (s->state) {
    case 0:
        s->t = 20.0f;
        s->state = 1;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        s->level = (uint8_t)(int)(s->t * 6.4f);
        if (s->t <= 0.0f) {
            s->flags &= ~1u;
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

/* 0x0002A6C0: fade stage G in over 20 units, then pop its request queue. */
void r1f_SeqGFadeIn(void)
{
    R1fStageG *s = &r1f_seqG37E090;
    switch (s->state) {
    case 0:
        s->t = 20.0f;
        s->state = 1;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        s->level = (uint8_t)(int)(s->t * 6.4f);
        if (s->t <= 0.0f) {
            s->flags &= ~1u;
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

/* 0x00029BC0: stage D flash: raise the second layer over 60 units, hold it
   for 180, then pop the request queue. */
void r1f_SeqDFlash(void)
{
    R1fStage *s = &r1f_seqD37DC24;
    switch (s->state) {
    case 0:
        s->state = 1;
        s->t = 60.0f;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        s->level2 = (uint8_t)(int)((60.0f - s->t) * (128.0f / 60.0f));
        if (s->t <= 0.0f) {
            s->state++;
            s->level2 = 0x80;
            s->t = 180.0f;
        }
        break;
    case 2:
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
            s->state = 0;
        }
        break;
    }
}

/* 0x00029DC0: close stage E's curtain (level 208 -> 0 along a sine) over 20
   units with sound 7 at both ends, then pop its request queue. */
void r1f_SeqECurtainOpen(void)
{
    R1fStage *s = &r1f_seqE37DCF8;
    switch (s->state) {
    case 0:
        s->flags |= 1;
        s->t = 20.0f;
        s->d34 = 0xD0;
        sub_00048AF0(7);
        s->state++;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        s->d34 = (int)(208.0f - sub_001A3ED0((20.0f - s->t) * 4.5f * 0.017453292f) * 208.0f);
        if (s->t <= 0.0f) {
            sub_00048AF0(7);
            s->q[0] = s->q[1];
            s->q[1] = s->q[2];
            s->q[2] = s->q[3];
            s->q[3] = s->q[4];
            s->q[4] = s->q[5];
            s->q[5] = s->q[6];
            s->q[6] = s->q[7];
            s->d34 = 0;
            s->q[7] = 0;
            s->state = 0;
        }
        break;
    }
}

/* 0x00029EF0: close stage E's curtain back over 20 units, then pop its
   request queue. */
void r1f_SeqECurtainClose(void)
{
    R1fStage *s = &r1f_seqE37DCF8;
    switch (s->state) {
    case 0:
        s->t = 20.0f;
        s->d34 = 0;
        s->state = 1;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        s->d34 = (int)(208.0f - sub_001A3ED0(s->t * 4.5f * 0.017453292f) * 208.0f);
        if (s->t <= 0.0f) {
            s->flags &= ~1u;
            s->q[0] = s->q[1];
            s->q[1] = s->q[2];
            s->q[2] = s->q[3];
            s->q[3] = s->q[4];
            s->q[4] = s->q[5];
            s->q[5] = s->q[6];
            s->q[6] = s->q[7];
            s->d34 = 0xD0;
            s->q[7] = 0;
            s->state = 0;
        }
        break;
    }
}

/* 0x0002A2C0: stage F: wait 10 units, then run f3C down by 0.01 per call
   and pop the request queue when it reaches 0. */
void r1f_SeqFDrain(void)
{
    R1fStage *s = &r1f_seqF37ED00;
    switch (s->state) {
    case 0:
        s->t = 10.0f;
        s->state = 1;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        if (s->t <= 0.0f)
            s->state++;
        break;
    case 2:
        s->f3C -= 0.01f;
        if (s->f3C <= 0.0f) {
            s->q[0] = s->q[1];
            s->q[1] = s->q[2];
            s->q[2] = s->q[3];
            s->q[3] = s->q[4];
            s->q[4] = s->q[5];
            s->q[5] = s->q[6];
            s->q[6] = s->q[7];
            s->f3C = 0.0f;
            s->q[7] = 0;
            s->state = 0;
        }
        break;
    }
}
/* 0x0002B140: fade stage I out over 20 units, then pop its request queue. */
void r1f_SeqIFadeOut(void)
{
    R1fStage2 *s = &r1f_seqI37F480;
    switch (s->state) {
    case 0:
        s->flags |= 1;
        s->t = 20.0f;
        s->state = 1;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        s->level = (uint8_t)(int)((20.0f - s->t) * 6.4f);
        if (s->t <= 0.0f) {
            s->q[0] = s->q[1];
            s->q[1] = s->q[2];
            s->q[2] = s->q[3];
            s->q[3] = s->q[4];
            s->q[4] = s->q[5];
            s->q[5] = s->q[6];
            s->q[6] = s->q[7];
            s->level = 0x80;
            s->q[7] = 0;
            s->state = 0;
        }
        break;
    }
}

/* 0x0002B230: fade stage I in over 20 units, then pop its request queue. */
void r1f_SeqIFadeIn(void)
{
    R1fStage2 *s = &r1f_seqI37F480;
    switch (s->state) {
    case 0:
        s->t = 20.0f;
        s->state = 1;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        s->level = (uint8_t)(int)(s->t * 6.4f);
        if (s->t <= 0.0f) {
            s->flags &= ~1u;
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

/* 0x0002B5A0: fade stage J out over 20 units, then pop its request queue. */
void r1f_SeqJFadeOut(void)
{
    R1fStage *s = &r1f_seqJ37FB3C;
    switch (s->state) {
    case 0:
        s->flags |= 1;
        s->t = 20.0f;
        s->state = 1;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        s->level = (uint8_t)(int)((20.0f - s->t) * 6.4f);
        if (s->t <= 0.0f) {
            s->q[0] = s->q[1];
            s->q[1] = s->q[2];
            s->q[2] = s->q[3];
            s->q[3] = s->q[4];
            s->q[4] = s->q[5];
            s->q[5] = s->q[6];
            s->q[6] = s->q[7];
            s->level = 0x80;
            s->q[7] = 0;
            s->state = 0;
        }
        break;
    }
}

/* 0x0002B690: fade stage J in over 20 units, then pop its request queue. */
void r1f_SeqJFadeIn(void)
{
    R1fStage *s = &r1f_seqJ37FB3C;
    switch (s->state) {
    case 0:
        s->t = 20.0f;
        s->state = 1;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        s->level = (uint8_t)(int)(s->t * 6.4f);
        if (s->t <= 0.0f) {
            s->flags &= ~1u;
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

/* 0x0002B770: stage J: wait 120 units, then pop its request queue. */
void r1f_SeqJWait(void)
{
    R1fStage *s = &r1f_seqJ37FB3C;
    switch (s->state) {
    case 0:
        s->t = 120.0f;
        s->state = 1;
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
            s->state = 0;
        }
        break;
    }
}

/* 0x0002B380: close a curtain (level 208 -> 0 along a sine) over 20 units,
   then pop its request queue.
   regargs: c=ESI */
void r1f_CurtainOpen(R1fCurtain *s)
{
    switch (s->state) {
    case 0:
        s->flags |= 1;
        s->t = 20.0f;
        s->level = 0xD0;
        s->state = 1;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        s->level = (int)(208.0f - sub_001A3ED0((20.0f - s->t) * 4.5f * 0.017453292f) * 208.0f);
        if (s->t <= 0.0f) {
            s->level = 0;
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

/* 0x0002B450: open a curtain back over 20 units, then pop its request
   queue.
   regargs: c=ESI */
void r1f_CurtainClose(R1fCurtain *s)
{
    switch (s->state) {
    case 0:
        s->t = 20.0f;
        s->level = 0;
        s->state = 1;
        break;
    case 1:
        sub_000720A0(&s->t, 0);
        s->level = (int)(208.0f - sub_001A3ED0(s->t * 4.5f * 0.017453292f) * 208.0f);
        if (s->t <= 0.0f) {
            s->level = 0xD0;
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
