/* Area r6d: box corners, texture headers and sound slots around 0x00082D90-0x00086152 (r6d_16). Names inferred. */
#include "r6d.h"

/* 0x00082D90: write the eight corners of the box lo..hi (fourth component kept per corner). */
void r6d_BoxCorners(R6dIVec4 *out, const R6dIVec4 *lo, const R6dIVec4 *hi)
{
    sub_000F5D40(&out[0], lo);
    out[1].v[1] = lo->v[1];
    out[1].v[2] = lo->v[2];
    out[1].v[3] = lo->v[3];
    out[1].v[0] = hi->v[0];
    out[2].v[0] = lo->v[0];
    out[2].v[2] = lo->v[2];
    out[2].v[3] = lo->v[3];
    out[2].v[1] = hi->v[1];
    out[3].v[0] = lo->v[0];
    out[3].v[1] = lo->v[1];
    out[3].v[3] = lo->v[3];
    out[3].v[2] = hi->v[2];
    sub_000F5D40(&out[4], hi);
    out[5].v[1] = hi->v[1];
    out[5].v[2] = hi->v[2];
    out[5].v[3] = hi->v[3];
    out[5].v[0] = lo->v[0];
    out[6].v[0] = hi->v[0];
    out[6].v[2] = hi->v[2];
    out[6].v[3] = hi->v[3];
    out[6].v[1] = lo->v[1];
    out[7].v[0] = hi->v[0];
    out[7].v[1] = hi->v[1];
    out[7].v[3] = hi->v[3];
    out[7].v[2] = lo->v[2];
}

/* Bit count of the highest set bit of v (log2), capped at 32. */
static int r6d_Log2(unsigned v)
{
    int n = 0;
    while ((v >>= 1) != 0)
        if (++n >= 32)
            break;
    return n;
}

/* 0x00084B40: initialise a "P2IG" texture header with a name of up to 8 characters and
   the log2 of its width and height. */
void r6d_TexHeaderInit(R6dTexHeader *h, const char *name, unsigned w, unsigned ht)
{
    int i;
    h->unkC = 1;
    h->unkE = 1;
    h->name[0] = 0;
    h->name[1] = 0;
    h->magic = 0x47493250;
    h->version = 0x60;
    h->f18 = 0;
    h->f1C = 0;
    for (i = 0; i < 8 && name[i]; i++)
        ((char *)h->name)[i] = name[i];
    h->log2W = (int16_t)r6d_Log2(w);
    h->log2H = (int16_t)r6d_Log2(ht);
    h->b24 = 0;
    h->b25 = 0;
    for (i = 0; i < 16; i++)
        h->f40[i] = 0;
}

/* 0x00086090: update a playing sound: when it ends, stop the sounds sharing its group;
   stop it early once its event flag is set. */
void r6d_SoundUpdate(R6dSound *s)
{
    R6dSoundDef *d = s->def;
    int key;
    int i;
    if (s->handle == -1)
        return;
    if (sub_000A79B0(s->handle) == -1) {
        s->handle = -1;
        s->state = 2;
        if (d->kind == 2) {
            key = d->group;
            for (i = 0; i < ((R6dCountTable *)a80_g3ED1D4)->count; i++) {
                R6dSound *o = &((R6dSound *)a80_g3ED1D0)[i];
                if (o->def->group == key && o->handle != -1) {
                    sub_000A7950(o->handle);
                    o->handle = -1;
                    o->state = 2;
                }
            }
        }
    }
    if (d->mode <= 1 && sub_000D9A70(d->event)) {
        sub_000A7950(s->handle);
        s->handle = -1;
        s->state = 2;
    }
}
