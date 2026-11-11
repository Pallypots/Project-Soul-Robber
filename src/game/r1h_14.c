/* Area r1h, group 14: effman.c pool file loader 0x000358C0. Uses the pool
   types of area r1g. Names inferred. */
#include "r1g.h"

void r1h_EfsLoad(R1gPool *p, const R1gEfsFile *f);

/* 0x000358C0: load effect slot pool p from an "EFS" file f. Kind 1 holds
   the header and up to 16 fixed table entries, kinds 2 and 3 a packed
   pool image (0x000357E0). For kinds 1 and 2 the high half of every
   entry's +0x34 word is then set. Other files are ignored. */
void r1h_EfsLoad(R1gPool *p, const R1gEfsFile *f)
{
    int i, k;
    if (f->magic != 0x534645)
        return;
    if (f->kind == 1) {
        R1gPoolE14 *slots = p->tbl14;
        p->hdr = f->hdr;
        p->hdr.slots = slots;
        sub_00035320(p, p->hdr.cap);
        for (i = 0; i < p->hdr.cap; i++) {
            k = r1g_PoolAlloc(p);
            p->tbl14[k] = f->e14[i];
            p->tbl60[k] = f->e60[i];
            p->tbl14[k].data = &p->tbl60[k];
        }
    } else if (f->kind == 2) {
        r1g_PoolLoad((const R1gPoolBlob *)&f->hdr, p);
    } else if (f->kind == 3) {
        r1g_PoolLoad((const R1gPoolBlob *)&f->hdr, p);
        return;                 /* kind 3 keeps the +0x34 words as loaded */
    } else {
        return;
    }
    if (f->kind <= 2) {
        for (i = 0; i < p->hdr.cap; i++)
            p->tbl60[i].d34 |= 0xFFFF0000;
    }
}
