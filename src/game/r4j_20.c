/* Area r4j: animation player tick (0x001AFD80). Names inferred. */
#include "r4j.h"

/* 0x001AFD80: per-frame update of an animation player. While blending
   (mode bit 1) count the wait ticks; when done, make the queued animation
   current and move every part's queued track and values into place (the
   loop-next bit becomes the loop bit), clearing the low six mode bits.
   Otherwise, once every playing part has finished (0x001AEE50 bit 1),
   start the queued animation if mode bit 0 (0x001AEBF0 mode 4), call the
   end callback and clear the parts' bit 1 (0x001AEF10). Unless frozen, the
   time advances by factor (0x001BBD80) * speed and is wrapped (when all
   playing parts loop) or clamped to [0, length]; blending kinds 0x10/0x20
   only advance. Stack arg (p). */
void r4j_AnimPlayerTick(R4jAnimPlayer *p)
{
    R4jAnimPart *pt;
    uint32_t mode = p->modeBC;
    uint32_t mask, f;
    void *next;
    int i;
    float t;

    if (mode & 2) {
        if (p->waitCC > p->tickD0) {
            p->tickD0++;
        } else {
            p->animC0 = p->nextC8;
            p->nextC8 = 0;
            p->waitCC = 0;
            p->tickD0 = 0;
            pt = p->parts;
            for (i = 0; i < p->count; i++, pt++) {
                f = pt->flagsB8;
                if (f & 4)
                    f = (f & ~4u) | 1;
                else
                    f &= ~1u;
                pt->flagsB8 = f;
                pt->curBC = pt->nextD4;
                pt->iC0 = pt->iD8;
                pt->iC4 = pt->iDC;
                pt->iC8 = pt->iE0;
                pt->iCC = pt->iE4;
                pt->nextD4 = 0;
                pt->iD8 = 0;
                pt->iE4 = 0;
                pt->fD0 = pt->fE8;
                pt->fE8 = 0.0f;
            }
            p->modeBC &= ~0x3Fu;
        }
    } else if (sub_001AEE50(p, 0) & 2) {
        if (mode & 1) {
            next = p->nextC8;
            p->animC0 = next;
            p->nextC8 = 0;
            sub_001AEBF0(p, next, 4);
            p->modeBC &= ~1u;
        }
        if (p->onEndD4 != 0)
            p->onEndD4(p);
        sub_001AEF10(p, 2);
    }
    if (p->flagsB8 & 2)
        return;
    mask = 0xFFFFFFFF;
    pt = p->parts;
    for (i = p->count; i > 0; i--, pt++)
        if (pt->curBC != 0)
            mask &= pt->flagsB8;
    mode = p->modeBC;
    if (mode & 2) {
        mode &= ~3u;
        if (mode == 0x10 || mode == 0x20)
            p->timeD8 = sub_001BBD80() * p->speedC4 + p->timeD8;
        return;
    }
    t = sub_001BBD80() * p->speedC4 + p->timeD8;
    p->timeD8 = t;
    if (!(p->lenDC > 0.0f))
        return;
    if (mask & 1) {
        if (t > p->lenDC) {
            do
                p->timeD8 = p->timeD8 - p->lenDC;
            while (p->timeD8 > p->lenDC);
        }
        if (0.0f > p->timeD8) {
            t = p->timeD8;
            do
                t = p->lenDC + t;
            while (0.0f > t);
            p->timeD8 = t;
        }
    } else if (t > p->lenDC) {
        p->timeD8 = p->lenDC;
    } else if (0.0f > t) {
        p->timeD8 = 0.0f;
    }
}
