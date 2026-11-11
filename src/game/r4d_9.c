/* Area r4d: timer, pad and save-data helpers around 0x001A8680-0x001A9E50 (r4d_9). Names inferred. */
#include "r4d.h"

/* 0x001A8680: add the time since the last call to the running total (while the timer is on) and
   return the total in milliseconds (64-bit result in EDX:EAX). No inputs. */
int64_t r4d_TimerElapsedMs(void)
{
    int64_t now;
    if (r4d_timerOn40B87C == 1) {
        sub_001BD59E(&r4d_timerFreq40B858);
        sub_001BD58D(&now);
        r4d_timerLen40B850 += now - r4d_timerStart40B848;
        r4d_timerStart40B848 = now;
    }
    return r4d_timerLen40B850 * 1000 / r4d_timerFreq40B858;
}

/* 0x001A90B0: set the rumble motors of the selected pad (a=0: current, else the other one).
   Stack args (a right left). */
void r4d_PadRumble(int a, int right, int left)
{
    R4dPad *p;
    int idx;
    if (a) {
        idx = r4d_padSel3650C8 != 1;
    } else {
        idx = r4d_padSel3650C8;
        if (idx < 0)
            return;
    }
    p = &r4d_padRecs40B9A4[idx];
    if (!p->hD0 || p->rumble70 == 0x3E5)
        return;
    p->motorL = (uint16_t)((uint8_t)left * 0xFF);
    p->motorR = (uint8_t)right ? 0xFFFF : 0;
    sub_002593D8(p->hD0, &p->rumble70);
}

/* 0x001A9D80: read and verify a save slot: 0 good, 1 read failed, 2 bad, or the loader's code. Stack arg (slot). */
int r4d_SaveCheck(int slot)
{
    R4dSaveSlot *s = &r4d_saveSlots3650E0[slot];
    uint32_t *p, saved;
    int size, r;
    if (sub_001A9A90(s, &size))
        return 1;
    if (size != r4d_saveLen40C028 + r4d_saveLen40BF20 + 0x14)
        return 2;
    r = sub_001A9910(s, r4d_saveBuf40BF24);
    if (r)
        return (r != 1) + 1;
    if (sub_001A9B90(r4d_saveBuf40BF24, r4d_saveLen40C028 + r4d_saveLen40BF20,
                     r4d_saveBuf40BF24 + r4d_saveLen40C028 + r4d_saveLen40BF20))
        return 2;
    p = (uint32_t *)(r4d_saveBuf40BF24 + r4d_saveLen40C028 + r4d_saveLen40BF20 - 4);
    saved = *p;
    *p = 0;
    return saved == (uint32_t)sub_001A9C00(r4d_saveBuf40BF24, r4d_saveLen40C028 + r4d_saveLen40BF20) ? 0 : 2;
}
