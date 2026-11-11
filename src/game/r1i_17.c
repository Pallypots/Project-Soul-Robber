/* Area r1i, group 17: HUD orbiting sprites 0x00022E70. Names inferred. */
#include "r1i.h"

/* 0x00022E70: when shown, draw the HUD centre sprite at the HUD position
   (x less the offset, y plus a sixth of it), then the three orbit sprites
   at the centre moved by the sine/cosine of the spinning angle (advancing
   their key sequences), then the top sprite at the centre. The angle is
   recomputed from the spin value for each of the two terms.
   regargs: p=EAX; returns the packet position */
uint32_t *r1i_HudOrbitDraw(uint32_t *p)
{
    float x, y, ox, oy;
    int i;
    R1iSprite *s;
    if (!(r1i_hudFlags37DCF8 & 1))
        return p;
    x = (float)(r1i_hudX37DCF4 - r1i_hudOfs37DD2C);
    y = (float)(r1i_hudOfs37DD2C / 6 + r1i_hudY37DCF6);
    ox = sub_001A3EE0(sub_001A3F00(r1i_hudSpin37DD20 * a50_frameUnits * r1i_kNeg3_2602C0
                                   * 0.017453292f + 3.1415927f, 6.2831855f) - 3.1415927f);
    oy = sub_001A3ED0(sub_001A3F00(r1i_hudSpin37DD20 * a50_frameUnits * r1i_kNeg3_2602C0
                                   * 0.017453292f + 3.1415927f, 6.2831855f) - 3.1415927f);
    r1i_hudSpr37DD30[0].x = x;
    r1i_hudSpr37DD30[0].y = y;
    p = r1i_SprDraw17C00(p, &r1i_hudSpr37DD30[0]);
    ox = ox + x;
    oy = oy + y;
    for (i = 1; i < 4; i++) {
        s = &r1i_hudSpr37DD30[i];
        s->x = ox;
        s->y = oy;
        p = r1i_SprDraw17C00(p, s);
        r1i_SeqPlayUpdate(s);
    }
    r1i_hudSpr37DD30[4].x = x;
    r1i_hudSpr37DD30[4].y = y;
    return r1i_SprDraw17C00(p, &r1i_hudSpr37DD30[4]);
}
