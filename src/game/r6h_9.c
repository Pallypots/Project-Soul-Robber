/* Area r6h: status screen texture release (r6h_9). Names inferred. */
#include "r6h.h"

/* Release texture handle *h when it is loaded and mark it unused (-1). */
#define R6H_FREE_TEX(h) do { if ((h) != -1) { sub_001B9FC0(h); (h) = -1; } } while (0)

/* 0x00064B50: reset the texture heap and release the textures of the current
   status screen sub-page (sub-page 0 keeps its textures when the next page
   byte is 2). */
void r6h_StatusFreeTextures(void)
{
    sub_001B9720();
    switch (r6g_b428F80[1]) {
    case 0:
        if (r6g_b428F80[4] == 2)
            break;
        R6H_FREE_TEX(a60_hA3E64C4[0]);
        R6H_FREE_TEX(a60_hA3E64C4[1]);
        R6H_FREE_TEX(a60_hA3E64C4[2]);
        break;
    case 1:
        R6H_FREE_TEX(a60_hB3E64D0[0]);
        R6H_FREE_TEX(a60_hB3E64D0[1]);
        R6H_FREE_TEX(a60_hB3E64D0[2]);
        R6H_FREE_TEX(a60_h3E64DC);
        break;
    case 2:
        R6H_FREE_TEX(a60_hD3E64EC[0]);
        R6H_FREE_TEX(a60_hD3E64EC[1]);
        R6H_FREE_TEX(a60_hD3E64EC[2]);
        break;
    case 3:
        R6H_FREE_TEX(a60_hC3E64E0[0]);
        R6H_FREE_TEX(a60_hC3E64E0[1]);
        R6H_FREE_TEX(a60_hC3E64E0[2]);
        break;
    }
}
