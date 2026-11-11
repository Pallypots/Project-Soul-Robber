/* Area r6h: title screen particles, respawn (r6h_2). Names inferred. */
#include "r6h.h"

/* 0x0006C270: respawn particle idx of the given kind: pick a random position
   on the 512x448 screen outside the central box (+-100, or +-50 when alt is
   set), then random speeds in both axes (random sign, scaled by 1/256, the
   vertical one by another quarter) and reset its lifetime from the kind record.
   regargs: idx=EAX alt=ECX kind=EDX. */
void r6h_FxRespawn(int idx, int alt, int kind)
{
    R6hFx *p = &r6h_fx3E6628[idx];
    float xmin, xmax, ymin, ymax;
    float sign;

    if (!alt) {
        xmin = -100.0f;
        ymin = -100.0f;
        xmax = 100.0f;
        ymax = 100.0f;
    } else {
        xmin = -50.0f;
        ymin = -50.0f;
        xmax = 50.0f;
        ymax = 50.0f;
    }
    do {
        p->x = (float)(sub_001C7EE1() % 512 - 256);
        p->y = (float)(sub_001C7EE1() % 448 - 224);
    } while (p->x >= xmin && xmax >= p->x && p->y >= ymin && ymax >= p->y);

    sign = (sub_001C7EE1() & 1) ? -1.0f : 1.0f;
    p->vx = (float)(sub_001C7EE1() % r6h_fxKinds2DF0C8[kind].range) * 0.00390625f * sign;
    sign = (sub_001C7EE1() & 1) ? -1.0f : 1.0f;
    p->vy = (float)(sub_001C7EE1() % r6h_fxKinds2DF0C8[kind].range) * 0.00390625f * sign * 0.25f;
    p->life = r6h_fxKinds2DF0C8[kind].life;
}
