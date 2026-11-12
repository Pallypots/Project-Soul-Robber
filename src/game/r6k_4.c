/* Area r6k: new game reset (r6k_4). Names inferred. */
#include "r6k.h"

/* 0x00077EF0: reset the save data for a new game. Every per-chapter grading
   record gets time -1.0 and -1 in all other fields (never played); the
   chapter globals 0x00413164/0x00413168 become 1 and 0x0041316C..0x00413174
   0; the event flag words 0x004133F0..0x00413430 and the float 0x0041317C
   are cleared. Then the play time is reset (0x0019C1E0), the sound settings
   are set up (0x00049AA0(0x10), 0x00049B00(3), 0x00049A40(0, 0..4)), the
   event bits are reset (0x000D9BF0) and event flags 0x330, 0x338, 0x33A,
   0x33C, 0x350 and 0x35A are set. */
void r6k_NewGameReset(void)
{
    GradeBlock *r;

    r = g_chapterRecords;
    do {
        r->time = -1.0f;
        r->bestCombo = -1;
        r->damage = -1;
        r->exclaim = -1;
        r->rank[0] = -1;
        r->rank[1] = -1;
        r->rank[2] = -1;
        r->rank[3] = -1;
        r->grade = -1;
        r++;
    } while ((intptr_t)r < (intptr_t)(g_chapterRecords + 25));
    a9b_g413164 = 1;
    a9b_g413168 = 1;
    a30_g41316C = 0;
    a30_g413170 = 0;
    a19_g413174 = 0;
    g_eventFlagBits[0] = 0;
    g_eventFlagBits[1] = 0;
    g_eventFlagBits[2] = 0;
    r6k_f41317C = 0.0f;
    g_eventFlagBits[3] = 0;
    g_eventFlagBits[4] = 0;
    g_eventFlagBits[5] = 0;
    g_eventFlagBits[6] = 0;
    g_eventFlagBits[7] = 0;
    g_eventFlagBits[8] = 0;
    g_eventFlagBits[9] = 0;
    g_eventFlagBits[10] = 0;
    g_eventFlagBits[11] = 0;
    g_eventFlagBits[12] = 0;
    g_eventFlagBits[13] = 0;
    g_eventFlagBits[14] = 0;
    g_eventFlagBits[15] = 0;
    g_eventFlagBits[16] = 0;
    Clock_ResetPlayTime();
    sub_00049AA0(0x10);
    sub_00049B00(3);
    sub_00049A40(0, 0);
    sub_00049A40(0, 1);
    sub_00049A40(0, 2);
    sub_00049A40(0, 3);
    sub_00049A40(0, 4);
    r2b_ResetBits();
    sub_000D9AB0(0x330);
    sub_000D9AB0(0x338);
    sub_000D9AB0(0x33A);
    sub_000D9AB0(0x33C);
    sub_000D9AB0(0x350);
    sub_000D9AB0(0x35A);
}

