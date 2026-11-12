/* Area m1, file 27: voice start (56 x 0xDC table at 0x00420F20). Names inferred. */
#include <stdint.h>

typedef struct M1VoiceS {
    uint8_t unk00[0xD0];
    int32_t paramD0;           /* +0xD0 */
    uint8_t unkD4[0xDC - 0xD4];
} M1VoiceS;
extern M1VoiceS m1_voices420F20S[56];  /* 0x00420F20 (start view) */
int  aab_FindA88B0(void *a, int b, const float *v);
void sub_000A8510(M1VoiceS *v, int a);  /* regargs: v=EDI a=EDX */

/* 0x000A93F0: finds a voice slot for (a, b, pos); stores param and starts it
 * with mode. Returns the slot index, or -1. */
int m1_VoiceStartA93F0(void *a, int mode, int param, int b, const float *pos)
{
    int s = aab_FindA88B0(a, b, pos);
    M1VoiceS *v;
    if (s < 0)
        return -1;
    v = &m1_voices420F20S[s];
    v->paramD0 = param;
    sub_000A8510(v, mode);
    return s;
}

