/* Area r6i: title letter animation (r6i_10). Names inferred. */
#include "r6i.h"

/* 0x0006C3F0: move the five title letters from key pose 0x0042C5E0 to key
   pose 0x0042C5E4 along a cubic Bezier (0x00071FE0) with an eased 0..1
   parameter over 110 frames, interpolating their scales linearly. Mode 1
   uses the control points of the "to" key in order, mode 2 those of the
   "from" key reversed; the mode ends when the timer runs out. */
void r6i_TitleLettersAnim(void)
{
    R6iVec2 pts[4];
    float t;
    int i;

    switch (r6e_g42C5D8) {
    case 2:
        t = (sub_001A3ED0(((1.0f - r6e_f42C5DC * (1.0f / 110.0f)) * 180.0f + 270.0f)
                          * 0.017453292f) + 1.0f) * 0.5f;
        for (i = 0; i < 5; i++) {
            pts[0] = r6i_keys42C600[r6e_g42C5E0][i].pos;
            pts[1] = r6i_ctl42C700[r6e_g42C5E0 - 1][i].b;
            pts[2] = r6i_ctl42C700[r6e_g42C5E0 - 1][i].a;
            pts[3] = r6i_keys42C600[r6e_g42C5E4][i].pos;
            sub_00071FE0(pts, t, &r6h_titlePos42C588[i]);
            r6h_titleScl42C5B0[i].x = (r6i_keys42C600[r6e_g42C5E4][i].scl.x
                                       - r6i_keys42C600[r6e_g42C5E0][i].scl.x) * t
                                      + r6i_keys42C600[r6e_g42C5E0][i].scl.x;
            r6h_titleScl42C5B0[i].y = (r6i_keys42C600[r6e_g42C5E4][i].scl.y
                                       - r6i_keys42C600[r6e_g42C5E0][i].scl.y) * t
                                      + r6i_keys42C600[r6e_g42C5E0][i].scl.y;
        }
        break;
    case 1:
        t = (sub_001A3ED0(((1.0f - r6e_f42C5DC * (1.0f / 110.0f)) * 180.0f + 270.0f)
                          * 0.017453292f) + 1.0f) * 0.5f;
        for (i = 0; i < 5; i++) {
            pts[0] = r6i_keys42C600[r6e_g42C5E0][i].pos;
            pts[1] = r6i_ctl42C700[r6e_g42C5E4 - 1][i].a;
            pts[2] = r6i_ctl42C700[r6e_g42C5E4 - 1][i].b;
            pts[3] = r6i_keys42C600[r6e_g42C5E4][i].pos;
            sub_00071FE0(pts, t, &r6h_titlePos42C588[i]);
            r6h_titleScl42C5B0[i].x = (r6i_keys42C600[r6e_g42C5E4][i].scl.x
                                       - r6i_keys42C600[r6e_g42C5E0][i].scl.x) * t
                                      + r6i_keys42C600[r6e_g42C5E0][i].scl.x;
            r6h_titleScl42C5B0[i].y = (r6i_keys42C600[r6e_g42C5E4][i].scl.y
                                       - r6i_keys42C600[r6e_g42C5E0][i].scl.y) * t
                                      + r6i_keys42C600[r6e_g42C5E0][i].scl.y;
        }
        break;
    default:
        return;
    }
    if (r6e_f42C5DC <= 0.0f)
        r6e_g42C5D8 = 0;
    a60_StepByFrame(&r6e_f42C5DC, 0);
}
