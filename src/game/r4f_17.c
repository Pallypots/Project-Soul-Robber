/* Area r4f: track part fade step at 0x001AC8F0 (r4f_17). Names inferred. */
#include "r4f.h"

/* 0x001AC8F0: move each part's level one step (1/steps of the distance, at least 1)
   towards its target and apply it (applying the current level first when b18 asks for a
   refresh); with no step count the level jumps to the target. Stack arg (f). */
void r4f_TrackFadeStep(R4fTrackFade *f)
{
    R4fFadePart *p;
    uint32_t d;
    int i;
    for (i = 0; i < f->n14; i++) {
        p = &f->part1C[i];
        r4d_drvMode40E348 = f->mode04;
        if (f->b18 == 1)
            sub_001AC3E0(f->id00, i, p->cur, f->f08);
        if (p->target == p->cur)
            continue;
        if (f->steps0C == 0) {
            f->steps0C = 1;
            p->cur = p->target;
        } else if (p->target > p->cur) {
            d = (p->target - p->cur) / f->steps0C;
            if (!d)
                d = 1;
            p->cur += d;
        } else {
            d = (p->cur - p->target) / f->steps0C;
            if (!d)
                d = 1;
            if (p->target < p->cur)
                p->cur -= d;
        }
        sub_001AC3E0(f->id00, i, p->cur, f->f08);
    }
    f->b18 = 0;
}
