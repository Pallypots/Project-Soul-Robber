/* Area m1, file 28: sound entry lookup (17 x 0x14 at 0x003E2550). Names inferred. */
#include <stdint.h>

typedef struct M1Snd14 {
    int32_t f00;
    int32_t bank04;            /* +0x04 */
    int32_t cue08;             /* +0x08 */
    void   *data0C;            /* +0x0C, 0 = empty */
    int32_t f10;
} M1Snd14;
extern M1Snd14 m1_snds3E2550[17];  /* 0x003E2550 */
void sub_00052EC0(int *outA, int a, int *outB, int b);  /* regargs: outA=EAX a=EDX outB=EBX */

/* 0x000531C0: normalises (bank, cue) through 0x52EC0 and returns the loaded entry
 * for them (cue -1 matches any), or 0. */
M1Snd14 *m1_FindSound531C0(int bank, int cue)
{
    int i;
    sub_00052EC0(&bank, bank, &cue, cue);
    for (i = 0; i < 17; i++) {
        if (m1_snds3E2550[i].data0C != 0 && m1_snds3E2550[i].bank04 == bank &&
            (cue == -1 || m1_snds3E2550[i].cue08 == cue))
            return &m1_snds3E2550[i];
    }
    return 0;
}

