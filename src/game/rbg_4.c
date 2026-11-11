/* Area rbg: game functions in 0x000F0000..0x000FFFFF far from their callees (rbg_4). Names inferred. */
#include "rbg.h"

/* 0x000F1EF0: step the boss finish sequence of o: each step waits for the current animation
   (parts mask bit 2) before starting the next one. Step 1 applies the damage of the level
   (1..6), step 4 picks the ending by score (below 75000: anim 7, else anim 0).
   calls 0x000F0B10 with EDI=o, 0x000F0B70 with ESI=o, 0x000EF8A0/0x000EF8D0 with EAX=o,
   0x000EEF90 with ESI=o */
void rbg_FinishSeq0F1EF0(RbgRec150 *o, RbgSeq *s)
{
    int i;

    switch (s->step110) {
    case 0:
        rbg_GroupAnim0F3DA0(o, 0x15, 0, 0);
        s->step110 = 1;
        break;
    case 1:
        if (sub_001AEE90(o->anim30->node14, 0) & 2) {
            i = s->level104 - 1;
            if (i < 0)
                i = 0;
            else if (i > 5)
                i = 5;
            sub_000F3BF0(o, rbg_dmg278410[i], 9);
            rbg_GroupAnim0F3DA0(o, 0x16, 0, 0);
            s->step110 = 2;
            r2d_SwitchOn();
        }
        break;
    case 2:
        if (sub_001AEE90(o->anim30->node14, 0) & 2) {
            rbg_GroupAnim0F3DA0(o, 0x17, 0, 0);
            r2c_SetEffectD4(o, 0);
            r2c_SetSoundD8(o, 0x1BF, 1);
            s->step110 = 3;
        }
        break;
    case 3:
        if (sub_001AEE90(o->anim30->node14, 0) & 2) {
            rbg_GroupAnim0F3DA0(o, 0x18, 0, 0);
            r2_Comp5FreeD4(o);
            r2_Comp5ReleaseD8(o);
            s->step110 = 4;
        }
        break;
    case 4:
        if (sub_001AEE90(o->anim30->node14, 0) & 2) {
            r2d_SwitchOff();
            if (s->p64->score2F0 < 75000) {
                rbg_GroupAnim0F3DA0(o, 7, 0, 0);
                sub_000F0C80(o, s);
                s->step110 = 5;
            } else {
                rbg_GroupAnim0F3DA0(o, 0, 0, 0);
                s->step110 = 6;
            }
        }
        break;
    case 5:
        sub_000F0D80(o, s);
        if (sub_001AEE90(o->anim30->node14, 0) & 2) {
            s->f10C = 0.0f;
            rbg_GroupAnim0F3DA0(o, 2, 0, 0);
            r2_ActorCallComp5(o, 3);
            s->step110 = 6;
        }
        break;
    }
}
