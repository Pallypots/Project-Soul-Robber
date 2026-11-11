/* Area r1h, group 4: screen-filter packet builders 0x00039920. Names inferred. */
#include "r1h.h"

/* sub_00012300 takes its two 64-bit operands as (low, high) 32-bit pairs. */
#define R1H_LO(q) ((int)(uint32_t)(q))
#define R1H_HI(q) ((int)(uint32_t)((q) >> 32))

/* 0x00039920: append the blended screen-filter pass of channel ch to the
   GS packet p: frame and texture registers, every sprite pair of the
   channel, the full-screen scissor, then the final blend sprite in the
   channel's blend mode; ends with 0x000396E0. Returns the new packet end. */
uint32_t *r1h_FiltDrawBlend(uint32_t *p, int ch)
{
    R1hChan *c = &r1e_chan3DA4A8[ch];
    R1hFilt *f = &r1h_filt3DA500[ch];
    R1hFrame *fr;
    uint32_t v;
    uint64_t q;
    int i;
    sub_001A4D70(ch);
    fr = sub_001BB230();
    v = sub_001BB240(fr->c, fr->a, fr->b);
    q = v | ((uint64_t)(fr->c | 0x100) << 24);
    p = sub_00012300(p, 0x4E, 0, R1H_LO(q), R1H_HI(q));
    p = sub_00012300(p, 0x3B, 0, 0x00008080, 0x00000040);
    p = sub_00012300(p, 0x40, 0, 0x00800000, 0x00800000);
    q = ((((R1hTex *)sub_001B9650(f->tex))->q28 >> 5) & 0x1FF) | 0x20000
        | 0xFF00000000000000ULL;
    p = sub_00012300(p, 0x4C, 0, R1H_LO(q), R1H_HI(q));
    q = ((uint64_t)r1h_zbuf3DCDA0 << 32) | 0x7000;
    p = sub_00012300(p, 0x18, 0, R1H_LO(q), R1H_HI(q));
    for (i = 0; i < c->count; i++) {
        p = sub_00012300(p, 0x3F, 0, 0, 0);
        p = sub_00012360(p, &f->spr[i]);
        p = sub_00012300(p, 0x3F, 0, 0, 0);
        p = sub_00012360(p, &f->spr[i + 8]);
    }
    q = (((uint64_t)(uint32_t)(a3c_h3DCE5C - 1) << 32)
         | (uint32_t)(a3c_w3DCE58 - 1)) << 16;
    p = sub_00012300(p, 0x40, 0, R1H_LO(q), R1H_HI(q));
    p = sub_00012300(p, 0x3F, 0, 0, 0);
    p = sub_00012300(p, 0x42, 0, 0x48, 0);
    q = ((((R1hTex *)sub_001B9650(-1))->q28 >> 5) & 0x1FF)
        | ((uint64_t)(a3c_w3DCE58 >> 6) << 16);
    p = sub_00012300(p, 0x4C, 0, R1H_LO(q), R1H_HI(q));
    q = ((uint64_t)r1h_zbuf3DCDA0 << 32) | 0x7000;
    p = sub_00012300(p, 0x18, 0, R1H_LO(q), R1H_HI(q));
    switch (f->mode) {
    case 0:
        f->s1280.ent[0].lo = 0x48;
        f->s1280.ent[0].hi = 0;
        break;
    case 1:
        f->s1280.ent[0].lo = 0x42;
        f->s1280.ent[0].hi = 0;
        break;
    case 2:
        f->s1280.ent[0].lo = 0x44;
        f->s1280.ent[0].hi = 0;
        break;
    }
    f->s1280.a = c->alpha;
    p = sub_00012360(p, &f->s1280);
    return sub_000396E0(p);
}
