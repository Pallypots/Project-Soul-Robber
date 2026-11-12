/* Area r1k, group 11: title background and stars 0x00041520.
   Names inferred. */
#include "r1k.h"

/* 0x00041520: draw the title background (a full-screen 512x448 quad,
   skipped in mode 2) and then move and draw every background star of
   the current stage's star parameters (stage 0x1B in mode 2) like the
   loading-screen field; a star whose life runs out respawns. Returns the
   advanced command pointer. */
void *r1k_TitleStarsDraw(void *cmd)
{
    R1kQuad q;
    int kind, i;
    float v;
    if (a30_g3DF9B8 != 2) {
        q.col[0] = 0x80808080;
        q.col[1] = 0x80808080;
        q.col[2] = 0x80808080;
        q.col[3] = 0x80808080;
        q.tex = rtc_tex3DF9C0;
        q.z = 0;
        q.x = 0.0f;
        q.w = 512.0f;
        q.y = 0.0f;
        q.h = 448.0f;
        q.u0 = 0.0f;
        q.v0 = 0.0f;
        q.u1 = 512.0f;
        q.v1 = 448.0f;
        cmd = sub_00072420(cmd, &q);
    }
    kind = a30_g3DF9BC;
    if (a30_g3DF9B8 == 2)
        kind = 0x1B;
    R1K_TSPR()->mode = r1k_starDefs2C58E0[kind].mode;
    for (i = 0; i < r1k_starDefs2C58E0[kind].count; i++) {
        R1K_TSPR()->x = R1K_STAR(i)->x = R1K_STAR(i)->vx + R1K_STAR(i)->x;
        R1K_TSPR()->y = R1K_STAR(i)->y = R1K_STAR(i)->vy + R1K_STAR(i)->y;
        v = (480.0f - R1K_STAR(i)->life) / r1k_starDefs2C58E0[kind].life
            * r1k_starDefs2C58E0[kind].grow + 1.0f;
        R1K_TSPR()->sx = v;
        R1K_TSPR()->sy = v;
        R1K_TSPR()->color = ((uint32_t)(int)(sub_001A3ED0(180.0f / r1k_starDefs2C58E0[kind].life
                                 * R1K_STAR(i)->life * 0.017453292f)
                             * r1k_starDefs2C58E0[kind].alpha) << 24)
                            | r1k_starDefs2C58E0[kind].color;
        cmd = sub_00017C00(cmd, R1K_TSPR());
        a60_StepByFrame(&R1K_STAR(i)->life, 0);
        if (0.0f >= R1K_STAR(i)->life)
            r1k_StarSpawn(i);
    }
    return cmd;
}
