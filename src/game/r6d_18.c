/* Area r6d: streaming job state machines around 0x000869C0-0x00086E56 (r6d_18). Names inferred.
   Each function is resumed every frame with its state word; it runs the work directly
   when already on the job thread, otherwise queues it as background jobs and returns 1
   while a job is still running. */
#include "r6d.h"

/* 0x000869C0: find the first stream set entry whose event flag is set and load it. */
int r6d_StreamLoadStep(void)
{
    R6dStreamSet *set = a80_g3ED208;
    R6dStreamEntry *e;
    int i;
    if (!set)
        return 0;
    switch (a8c_g3ED1F0) {
    case 0:
        a8c_g3ED1E8 = 0;
        a8c_g3ED1F4 = 0;
        e = set->entries;
        for (i = 0; i < set->count; i++) {
            if (sub_000D9A70(e->event)) {
                a8c_g3ED1F4 = e;
                break;
            }
            e = (R6dStreamEntry *)((uint8_t *)e + e->n * 8 + 8);
        }
        if (!a8c_g3ED1F4 || !a8c_g3ED1F4->n)
            return 0;
        sub_000865F0();
        a8c_g3ED1F0 = 10;
    case 10:
        if (Job_OnJobThread()) {
            sub_000862A0(a8c_g3ED1F4);
            r6d_StreamsStop(0);
            a8c_g3ED1F0 = 0;
            return 0;
        }
        a8c_g3ED1F0 = 20;
    case 20:
        if (Job_IsRunning())
            return 1;
        sub_00058540((void (*)(void))sub_000862A0, a8c_g3ED1F4);
        a8c_g3ED1F0 = 30;
    case 30:
        if (Job_IsRunning())
            return 1;
        sub_00058540((void (*)(void))r6d_StreamsStop, 0);
        a8c_g3ED1F0 = 40;
    case 40:
        if (Job_IsRunning())
            return 1;
        a8c_g3ED1F0 = 0;
        return 0;
    }
    return 1;
}

/* 0x00086B30: release the current stream set entry. */
int r6d_StreamFreeStep(void)
{
    if (!a8c_g3ED1F4)
        return 0;
    switch (a8c_g3ED1D8) {
    case 0:
        sub_000CE8F0();
        if (Job_OnJobThread()) {
            sub_00086460(a8c_g3ED1F4);
            sub_00086850(0);
            break;
        }
        a8c_g3ED1D8 = 10;
    case 10:
        if (Job_IsRunning())
            return 1;
        sub_00058540((void (*)(void))sub_00086460, a8c_g3ED1F4);
        a8c_g3ED1D8 = 20;
    case 20:
        if (Job_IsRunning())
            return 1;
        sub_00058540((void (*)(void))sub_00086850, 0);
        a8c_g3ED1D8 = 30;
    case 30:
        if (Job_IsRunning())
            return 1;
        break;
    default:
        return 1;
    }
    a8c_g3ED1F4 = 0;
    a8c_g3ED1D8 = 0;
    return 0;
}

/* 0x00086CE0: start playing stream (a, b) on the third voice. */
int r6d_StreamPlay(int a, int b)
{
    switch (a8c_g3ED1E8) {
    case 0:
        if (a8c_handles3ED1DC[2] == -1)
            return 0;
        if (Job_OnJobThread()) {
            r6c_strA3ED1F8 = a;
            r6c_strB3ED1FC = b;
            r6c_strH3ED200 = a8c_handles3ED1DC[2];
            r6c_StreamPlayWait(0);
            return 0;
        }
        if (Job_IsRunning())
            return 1;
        r6c_strA3ED1F8 = a;
        r6c_strB3ED1FC = b;
        r6c_strH3ED200 = a8c_handles3ED1DC[2];
        sub_00058540((void (*)(void))r6c_StreamPlayWait, 0);
        a8c_g3ED1E8 = 10;
    case 10:
        if (Job_IsRunning())
            return 1;
        a8c_g3ED1E8 = 0;
        return 0;
    }
    return 1;
}

/* 0x00086DA0: switch the third voice to stream (a, b). */
int r6d_StreamSwitch(int a, int b)
{
    switch (a8c_g3ED1E8) {
    case 0:
        if (a8c_handles3ED1DC[2] == -1)
            return 0;
        if (Job_OnJobThread()) {
            r6c_strA3ED1F8 = a;
            r6c_strB3ED1FC = b;
            r6c_strH3ED200 = a8c_handles3ED1DC[2];
            r6c_StreamSwitchWait(0);
            return 0;
        }
        if (Job_IsRunning())
            return 1;
        r6c_strA3ED1F8 = a;
        r6c_strB3ED1FC = b;
        r6c_strH3ED200 = a8c_handles3ED1DC[2];
        sub_00058540((void (*)(void))r6c_StreamSwitchWait, 0);
        a8c_g3ED1E8 = 10;
    case 10:
        if (Job_IsRunning())
            return 1;
        a8c_g3ED1E8 = 0;
        return 0;
    }
    return 1;
}
