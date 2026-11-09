/* Area a1b, group 2: animation-state helpers near 0x00015070. Names inferred. */
#include "a1b.h"

/* 0x00015070: step the object with flags forced until bit 7 is set, then restore flags. */
void a1b_RunToEnd(A1bStepper *s)
{
    uint32_t saved = s->flags24;
    s->flags24 = (saved & 0xFFFFFF76) | 6;
    do {
        s->t10 = 0.0f;
        sub_00014E80(s);
    } while ((int8_t)s->flags24 >= 0);
    s->flags24 = saved;
}

/* 0x000150B0: switch to animation idx, resetting time. */
void a1b_SetAnim(A1bAnimState *a, int idx)
{
    if (a->cur != idx) {
        a->cur = idx;
        a->time = 0;
        a->length = a->set->entries[idx]->length;
        a->r28 = 0;
    }
}
