/* Area r1j, group 15: menu screen texture release 0x00049870.
   Names inferred. */
#include "r1j.h"

/* release texture handle *h when it holds one */
#define R1J_TEX_FREE(h) do { \
    if (*(h) != -1) { \
        sub_001B9FC0(*(h)); \
        *(h) = -1; \
    } \
} while (0)

/* release every handle of the table [a, end) */
#define R1J_TEX_FREE_ALL(a, n) do { \
    int32_t *h_; \
    for (h_ = (a); (intptr_t)h_ < (intptr_t)((a) + (n)); h_++) \
        R1J_TEX_FREE(h_); \
} while (0)

/* 0x00049870: tear down the menu screen: release the common textures and
   those of the current page kind (r1j_menuKind 0..4), free the page
   buffer, run commands 0xBB, 0xA0 + video mode and 0xBA (0x0004F5D0),
   yield and restore (0x001A1B90, tail call). */
void r1j_MenuTexRelease(void)
{
    int i;
    r1j_menuCount3E059C = 0;
    R1J_TEX_FREE_ALL(r1j_menuTexA3E0590, 2);
    switch (r1j_menuKind) {
    case 0:
        R1J_TEX_FREE_ALL(r1j_menuTexB3E05D0, 3);
        R1J_TEX_FREE_ALL(r1j_menuTexC3E05B4, 2);
        break;
    case 1:
        R1J_TEX_FREE_ALL(r1j_menuTexD3E0580, 3);
        R1J_TEX_FREE_ALL(r1j_menuTexC3E05B4, 2);
        break;
    case 2:
        R1J_TEX_FREE_ALL(r1j_menuTexE3E0544, 13);
        break;
    case 3:
        for (i = 0; i < 2; i++) {
            R1J_TEX_FREE(&r1j_menuTexF3E05C8[i]);
            R1J_TEX_FREE(&r1j_menuTexG3E05C0[i]);
            R1J_TEX_FREE(&r1j_menuTexC3E05B4[i]);
        }
        break;
    case 4:
        R1J_TEX_FREE_ALL(r1j_menuTexH3E05A0, 5);
        break;
    }
    sub_00053880(r1j_menuBuf3E058C);
    sub_0004F5D0(0xBB);
    sub_0004F5D0(sub_000529F0() + 0xA0);
    sub_0004F5D0(0xBA);
    sub_001AB850();
    sub_001A1B90();
}
