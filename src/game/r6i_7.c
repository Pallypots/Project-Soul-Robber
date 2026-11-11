/* Area r6i: title texture release (r6i_7). Names inferred. */
#include "r6i.h"

/* 0x0006E490: reset the two title scales to 1.0 and release the textures
   loaded for the current title phase (phase byte 0x00428F81): phase 0 the
   background and handles 0..2 (kept when the queued page is 4), phase 1
   handles 3..6, phase 2 7..9, phase 3 10..12, phase 4 13..14, phase 5 15. */
void r6i_TitleReleaseTextures(void)
{
    r6i_f42906C = 1.0f;
    r6i_f429070 = 1.0f;

    switch (r6g_b428F80[1]) {
    case 0:
        if (r6g_b428F80[4] == 4)
            break;
        R6I_RELEASE_TEX(a60_h42C6F0)
        R6I_RELEASE_TEX(a60_h3E68B8[0])
        R6I_RELEASE_TEX(a60_h3E68B8[1])
        R6I_RELEASE_TEX(a60_h3E68B8[2])
        break;
    case 1:
        R6I_RELEASE_TEX(a60_h3E68B8[3])
        R6I_RELEASE_TEX(a60_h3E68B8[4])
        R6I_RELEASE_TEX(a60_h3E68B8[5])
        R6I_RELEASE_TEX(a60_h3E68B8[6])
        break;
    case 2:
        R6I_RELEASE_TEX(a60_h3E68B8[7])
        R6I_RELEASE_TEX(a60_h3E68B8[8])
        R6I_RELEASE_TEX(a60_h3E68B8[9])
        break;
    case 3:
        R6I_RELEASE_TEX(a60_h3E68B8[10])
        R6I_RELEASE_TEX(a60_h3E68B8[11])
        R6I_RELEASE_TEX(a60_h3E68B8[12])
        break;
    case 4:
        R6I_RELEASE_TEX(a60_h3E68B8[13])
        R6I_RELEASE_TEX(a60_h3E68B8[14])
        break;
    case 5:
        R6I_RELEASE_TEX(a60_h3E68B8[15])
        break;
    }
}
