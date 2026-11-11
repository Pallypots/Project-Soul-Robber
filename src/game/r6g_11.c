/* Area r6g: chapter screen sprites (r6g_11). Names inferred. */
#include "r6g.h"

#define R6G_CSPR(i) (&r6g_chapSpr42A830[i])

/* 0x00074160: build the textures and sprites of the chapter screen page
   selected by r6g_b428F80[1] (0..2); page 1 makes one texture per entry of the
   current chapter (count per video mode in r6d_counts2DF390). */
void r6g_ChapterBuildSprites(void)
{
    int i, idx;

    sub_001B9720();
    switch (r6g_b428F80[1]) {
    case 0:
        a60_h3E694C[0] = sub_00084C00(a60_work42C5E8 + 0x40080, 0);
        r6d_h3E6954 = sub_00084C00(a60_work42C5E8 + 0x80100, 0);
        sub_00014DA0(a60_work42C5E8 + 0x81180);
        sub_00014DA0(a60_work42C5E8 + 0x81280);
        sub_00014DA0(a60_work42C5E8 + 0x83280);
        sub_00014DA0(a60_work42C5E8 + 0x88280);
        sub_00014D00(R6G_CSPR(0), a60_work42C5E8 + 0x81180, a60_h3E694C[0]);
        sub_00014E30(R6G_CSPR(0), 0, 0.0f, 0.0f, 0);
        sub_00014D00(R6G_CSPR(1), a60_work42C5E8 + 0x83280, a60_h3E694C[0]);
        R6G_CSPR(1)->tex[0] = r6d_h3E6954;
        sub_00014E30(R6G_CSPR(1), 0, 0.0f, 0.0f, 0);
        *R6G_CSPR(2) = *R6G_CSPR(1);
        *R6G_CSPR(6) = *R6G_CSPR(1);
        *R6G_CSPR(5) = *R6G_CSPR(1);
        sub_00014D00(R6G_CSPR(3), a60_work42C5E8 + 0x88280, a60_h3E694C[0]);
        sub_00014E30(R6G_CSPR(3), 0, 0.0f, 0.0f, 0);
        sub_00014D00(R6G_CSPR(4), a60_work42C5E8 + 0x81280, a60_h3E694C[0]);
        sub_00014E30(R6G_CSPR(4), 0, 0.0f, 0.0f, 0);
        break;
    case 1:
        idx = r6d_g42A818 + r6d_g42A824;
        a60_h3E694C[1] = sub_00084C00(a60_work42C5E8 + 0x88680, 0);
        for (i = 0; i < r6d_counts2DF390[sub_000529F0()][idx]; i++)
            a60_h3E6940[i] = sub_00084C00(a60_work42C5E8 + i * 0x20080 + 0x98700, 0);
        R6G_CSPR(0)->base = a60_h3E694C[1];
        R6G_CSPR(3)->base = a60_h3E6940[0];
        break;
    case 2:
        a60_h3E6940[0] = sub_00084C00(a60_work42C5E8 + 0x88680, 0);
        a60_h3E6940[1] = sub_00084C00(a60_work42C5E8 + 0x98700, 0);
        a60_h3E6940[2] = sub_00084C00(a60_work42C5E8 + 0xB8780, 0);
        R6G_CSPR(4)->base = a60_h3E6940[1];
        R6G_CSPR(4)->tex[0] = a60_h3E6940[2];
        R6G_CSPR(4)->tex[1] = a60_h3E6940[0];
        break;
    }
}
