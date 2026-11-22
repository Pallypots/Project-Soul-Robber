/* Area r4b: sound voice set allocation (r4b_13). Names inferred. */
#include "r4b.h"

/* 0x001BC1F0: clear and allocate the enabled voices (format 0x13) of every entry of s;
   on the first failure free the whole set and return 0. Stack args (a s). */
int r4b_VoiceSetAlloc(int a, R4bVoiceSet *s)
{
    int i;
    /* walk pointers biased like the original: hs at hnd[i][0].size, eb at bufs[i].buf[1] */
    int32_t *hs = &s->hnd[0][0].size;
    int32_t *eb = (int32_t *)&s->bufs[0].buf[1];
    for (i = 0; i < s->count; i++, hs += 12, eb += 8) {
        eb[-1] = 0;
        eb[1] = 0;
        eb[0] = 0;
        eb[2] = 0;
        if (hs[-2] && !r4b_VoiceAlloc(s->a44, s->a48, 0x13, (void **)&eb[-1], (void **)&hs[-1], &hs[0], &eb[3]))
            goto fail;
        if (hs[1] && !r4b_VoiceAlloc(s->a4C, s->a50, 0x13, (void **)&eb[0], (void **)&hs[2], &hs[3], &eb[4]))
            goto fail;
        if (hs[4] && !r4b_VoiceAlloc(s->a4C, s->a50, 0x13, (void **)&eb[1], (void **)&hs[5], &hs[6], &eb[5]))
            goto fail;
        if (hs[7] && !r4b_VoiceAlloc(s->a44, s->a48, 0x13, (void **)&eb[2], (void **)&hs[8], &hs[9], &eb[6]))
            goto fail;
    }
    return 1;
fail:
    r4b_VoiceSetFree(a, s);
    return 0;
}
