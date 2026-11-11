/* Area rfl, group 8: fade state machines (0x000E8220..0x000E90F2). Names inferred. */
#include "rfl.h"

/* 0x000E8220: two-step fade in of a screen element: set up, then count
   20 frames down while the alpha byte rises to 0x80.
   regargs: o=ESI */
void rfl_FadeInStep(RflFadeObj *o)
{
    switch (o->stateC) {
    case 0:
        o->t10 = 20.0f;
        o->f2C = -224.0f;
        o->f30 = -12.0f;
        o->f34 = 1.0f;
        o->i28 = 1;
        o->flags0 |= 1;
        o->rec38[0].v = 0;
        o->rec38[1].v = 0;
        o->rec38[2].v = 0;
        o->rec38[3].v = 0;
        o->rec38[4].v = 0;
        o->rec38[5].v = 0;
        o->rec38[6].v = 0;
        o->stateC++;
        break;
    case 1:
        sub_000720A0(&o->t10, 0);
        o->alpha14 = (uint8_t)(int)((20.0f - o->t10) * 0.05f * 128.0f);
        if (!(0.0f < o->t10)) {
            o->stateC = 0;
            o->alpha14 = 0x80;
            o->mode4 = 2;
        }
        break;
    }
}

/* 0x000E82E0: drop-in motion: over 40 frames +0x30 follows
   (1 - cos(angle)) * 140 - 12, ending at 128.
   regargs: o=ESI */
void rfl_DropInStep(RflFadeObj *o)
{
    switch (o->stateC) {
    case 0:
        o->t10 = 40.0f;
        o->stateC = 1;
        break;
    case 1:
        sub_000720A0(&o->t10, 0);
        o->f30 = (1.0f - sub_001A3EE0(sub_001A3F00((40.0f - o->t10) * 2.25f * 0.0174532924f + 3.14159274f,
                                                   6.28318548f) - 3.14159274f)) * 140.0f - 12.0f;
        if (!(0.0f < o->t10)) {
            o->f30 = 128.0f;
            o->mode4 = 3;
            o->stateC = 0;
        }
        break;
    }
}

/* 0x000E8F80: global caption fade in: 20 frames, then shift the queue at
   0x003F43E0 by one entry. */
void rfl_CaptionFadeIn(void)
{
    switch (rfl_caption.state14) {
    case 0:
        rfl_caption.flags0 |= 1;
        rfl_caption.t18 = 20.0f;
        rfl_caption.state14 = 1;
        break;
    case 1:
        sub_000720A0(&rfl_caption.t18, 0);
        rfl_caption.alpha1C = (uint8_t)(int)((20.0f - rfl_caption.t18) * 0.05f * 128.0f);
        if (!(0.0f < rfl_caption.t18)) {
            rfl_caption.alpha1C = 0x80;
            rfl_caption.q[0] = rfl_caption.q[1];
            rfl_caption.q[1] = rfl_caption.q[2];
            rfl_caption.q[2] = rfl_caption.q[3];
            rfl_caption.q[3] = 0;
            rfl_caption.state14 = 0;
        }
        break;
    }
}

/* 0x000E9040: global caption fade out: 20 frames, then clear the visible
   flag and shift the queue. */
void rfl_CaptionFadeOut(void)
{
    switch (rfl_caption.state14) {
    case 0:
        rfl_caption.t18 = 20.0f;
        rfl_caption.state14 = 1;
        break;
    case 1:
        sub_000720A0(&rfl_caption.t18, 0);
        rfl_caption.alpha1C = (uint8_t)(int)(rfl_caption.t18 * 0.05f * 128.0f);
        if (!(0.0f < rfl_caption.t18)) {
            rfl_caption.flags0 &= ~1u;
            rfl_caption.alpha1C = 0;
            rfl_caption.q[0] = rfl_caption.q[1];
            rfl_caption.q[1] = rfl_caption.q[2];
            rfl_caption.q[2] = rfl_caption.q[3];
            rfl_caption.q[3] = 0;
            rfl_caption.state14 = 0;
        }
        break;
    }
}

/* 0x000E9180: second caption block (0x003F47B4) fade in over 10 frames,
   then shift its queue by one entry. */
void rfl_Caption2FadeIn(void)
{
    switch (rfl_caption2.state14) {
    case 0:
        rfl_caption2.flags0 |= 1;
        rfl_caption2.t18 = 10.0f;
        rfl_caption2.state14 = 1;
        break;
    case 1:
        sub_000720A0(&rfl_caption2.t18, 0);
        rfl_caption2.alpha1C = (uint8_t)(int)((10.0f - rfl_caption2.t18) * 0.1f * 128.0f);
        if (!(0.0f < rfl_caption2.t18)) {
            rfl_caption2.alpha1C = 0x80;
            rfl_caption2.q[0] = rfl_caption2.q[1];
            rfl_caption2.q[1] = rfl_caption2.q[2];
            rfl_caption2.q[2] = rfl_caption2.q[3];
            rfl_caption2.q[3] = 0;
            rfl_caption2.state14 = 0;
        }
        break;
    }
}

/* 0x000E9240: second caption block fade out over 10 frames. */
void rfl_Caption2FadeOut(void)
{
    switch (rfl_caption2.state14) {
    case 0:
        rfl_caption2.t18 = 10.0f;
        rfl_caption2.state14 = 1;
        break;
    case 1:
        sub_000720A0(&rfl_caption2.t18, 0);
        rfl_caption2.alpha1C = (uint8_t)(int)(rfl_caption2.t18 * 0.1f * 128.0f);
        if (!(0.0f < rfl_caption2.t18)) {
            rfl_caption2.flags0 &= ~1u;
            rfl_caption2.alpha1C = 0;
            rfl_caption2.q[0] = rfl_caption2.q[1];
            rfl_caption2.q[1] = rfl_caption2.q[2];
            rfl_caption2.q[2] = rfl_caption2.q[3];
            rfl_caption2.q[3] = 0;
            rfl_caption2.state14 = 0;
        }
        break;
    }
}

/* 0x000E95F0: third caption block (0x003F4870) fade out over 20 frames. */
void rfl_Caption3FadeOut(void)
{
    switch (rfl_caption3.state14) {
    case 0:
        rfl_caption3.t18 = 20.0f;
        rfl_caption3.state14 = 1;
        break;
    case 1:
        sub_000720A0(&rfl_caption3.t18, 0);
        rfl_caption3.alpha1C = (uint8_t)(int)(rfl_caption3.t18 * 0.05f * 128.0f);
        if (!(0.0f < rfl_caption3.t18)) {
            rfl_caption3.flags0 &= ~1u;
            rfl_caption3.alpha1C = 0;
            rfl_caption3.q[0] = rfl_caption3.q[1];
            rfl_caption3.q[1] = rfl_caption3.q[2];
            rfl_caption3.q[2] = rfl_caption3.q[3];
            rfl_caption3.q[3] = 0;
            rfl_caption3.state14 = 0;
        }
        break;
    }
}

/* 0x000E96B0: fourth caption block (0x003F4B18) fade in over 20 frames. */
void rfl_Caption4FadeIn(void)
{
    switch (rfl_caption4.state14) {
    case 0:
        rfl_caption4.flags0 |= 1;
        rfl_caption4.t18 = 20.0f;
        rfl_caption4.state14 = 1;
        break;
    case 1:
        sub_000720A0(&rfl_caption4.t18, 0);
        rfl_caption4.alpha1C = (uint8_t)(int)((20.0f - rfl_caption4.t18) * 0.05f * 128.0f);
        if (!(0.0f < rfl_caption4.t18)) {
            rfl_caption4.alpha1C = 0x80;
            rfl_caption4.q[0] = rfl_caption4.q[1];
            rfl_caption4.q[1] = rfl_caption4.q[2];
            rfl_caption4.q[2] = rfl_caption4.q[3];
            rfl_caption4.q[3] = 0;
            rfl_caption4.state14 = 0;
        }
        break;
    }
}

/* 0x000E9770: fourth caption block fade out over 20 frames. */
void rfl_Caption4FadeOut(void)
{
    switch (rfl_caption4.state14) {
    case 0:
        rfl_caption4.t18 = 20.0f;
        rfl_caption4.state14 = 1;
        break;
    case 1:
        sub_000720A0(&rfl_caption4.t18, 0);
        rfl_caption4.alpha1C = (uint8_t)(int)(rfl_caption4.t18 * 0.05f * 128.0f);
        if (!(0.0f < rfl_caption4.t18)) {
            rfl_caption4.flags0 &= ~1u;
            rfl_caption4.alpha1C = 0;
            rfl_caption4.q[0] = rfl_caption4.q[1];
            rfl_caption4.q[1] = rfl_caption4.q[2];
            rfl_caption4.q[2] = rfl_caption4.q[3];
            rfl_caption4.q[3] = 0;
            rfl_caption4.state14 = 0;
        }
        break;
    }
}
