/* Area r4f: driver voice status query at 0x001AB0D0 (r4f_13). Names inferred. */
#include "r4f.h"

/* 0x001AB0D0: query a voice status with each of the four query kinds in turn; 0 on the
   first success, E_FAIL if none answers. Stack args (q out). XACT callee is stdcall. */
int r4f_DrvStatus1AB0D0(const R4fDrvQuery *q, void *out)
{
    R4fDrvQuery t = *q;
    unsigned int i;
    for (i = 0; i < 4; i++) {
        t.kind00 = (uint16_t)r4f_queryKinds27B7E0[i];
        if (!sub_00222573(r4d_drvDev40E690, &t, out))
            return 0;
    }
    return 0x80004005;
}


/* 0x001AC2E0: start group g's sound snd once its driver slot is ready: release the group's
   old voices and, for groups 5 and 6 except sounds 0x56, 0x57 and 0x5E..0x65, prime the
   sound. Returns 1, or 0 (after 0x001AD150) when the slot is not ready. Stack args (snd g)
   with snd a 16-bit value. Calls 0x001ACF00 and 0x001AD150 with ECX=slot. */
int r4f_DrvStart(int snd, int g)
{
    int k = g - 1;
    short s16 = (short)snd;
    R4eDrvSlot *s = &r4f_slots40E6B8[k];
    if (!sub_001ACF00(s)) {
        sub_001AD150(s);
        return 0;
    }
    r4d_DrvReleaseGroup(s16, k);
    if ((g == 5 || g == 6) && !(s16 >= 0x5E && s16 <= 0x65) && s16 != 0x56 && s16 != 0x57)
        sub_002224DD(r4d_drvDev40E690, &r4f_snd365780[s16], 0);
    return 1;
}

