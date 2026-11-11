/* Area r6h: demo (cutscene) object creation, demo.c (r6h_4). Names inferred. */
#include <string.h>
#include "r6h.h"

/* 0x00089C10: create a demo object for demo id with the given kind key:
   allocate the 0x50-byte object and its 0x184-byte work block from heap 1
   (source line tags 0xDF/0xE1 of demo.c), clear the object, look the key up
   in the flag table (default 0x3F4), copy the scene view, set up the key
   arrays, the slot holder and the sound tag, mark all 256 channel bytes
   active, register the demo and reset the spawners. */
R6hDemo *r6h_DemoCreate(int id, int key)
{
    R6hDemo *d;
    R6hDemoWk *w;
    uint32_t flags;
    int i, j;

    d = sub_0008BD80(sub_0008BD00(1), 4, 0x50, 0xDF, r6h_demoFile26FAFC);
    w = sub_0008BD80(sub_0008BD00(1), 4, 0x184, 0xE1, r6h_demoFile26FAFC);
    sub_0007F1E0(d, 0, 0x50);
    d->wk = w;
    d->state = 0;
    d->id = id;
    d->t8 = 0.0f;
    d->t10 = 0.0f;
    d->tC = 0.0f;
    d->list = sub_0008FB60();
    for (i = 0; i < 8; i++) {
        if (r6h_demoFlags26FA30[i].key == key) {
            flags = r6h_demoFlags26FA30[i].val;
            goto found;
        }
    }
    flags = 0x3F4;
found:
    d->wk->flags = flags | 2;
    if (!r4c_opt413140)
        d->wk->flags |= 0x400;
    d->wk->view = *sub_0007AB00(a80_ctx42C8E4);
    d->wk->w1C = 0;
    d->wk->w20 = 0;
    sub_00090020(d->wk->keys);
    sub_0008FEE0(d->wk->holder);
    sub_0008FF30(d->wk->holder, sub_00037780());
    sub_0008FF60(d->wk->holder, sub_000390A0());
    memcpy(d->wk->tag, r6h_demoTag26FB40, 5);
    for (i = 0; i < 0x100; i += 0x40)
        for (j = 0; j < 0x40; j++)
            d->wk->b7C[0][i + j] = 1;
    sub_00037BB0(4, d->wk->tag);
    sub_00089880(d);
    sub_00033390();
    sub_00035B20(sub_0007AAB0(a80_ctx42C8E4));
    d->state = 1;
    return d;
}
