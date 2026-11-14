/* Area m1, file 179: sound timing helpers. Names inferred. */
#include <stdint.h>

extern int a5b_sndChannel;
extern uint32_t a5b_sndCount;
extern uint16_t a5b_sndLevel;
uint32_t r4d_TimerElapsedMs(void);
void a60_ChannelSetLevel(int ch, uint16_t v);
void r4d_TimerStartMs(int ms);

#pragma optimize("s", on)
/* 0x53F70: restart the sound timer at ms; converts ms to a 576-per-ms sample count (16.16 split) and returns the old elapsed time. */
uint32_t m1_SndTimerSet053F70(uint32_t ms) {
    uint32_t r = r4d_TimerElapsedMs();
    uint64_t v = (uint64_t)ms * 576000u / 1000u;
    a5b_sndCount = (uint32_t)(v >> 16);
    a5b_sndLevel = (uint16_t)v;
    a60_ChannelSetLevel(a5b_sndChannel, (uint16_t)v);
    r4d_TimerStartMs(ms);
    return r;
}
#pragma optimize("", on)
