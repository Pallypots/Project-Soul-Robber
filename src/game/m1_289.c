/* Area m1, file 289: draw record pool. Names inferred. */
#include <stdint.h>

typedef struct M1Dr289 { uint8_t unk00[0x1E]; int16_t key1E; struct M1Dr289 *next20, *prev24; uint8_t unk28[0x28];
    int32_t f50; uint8_t f54[4]; } M1Dr289;                                   /* 0x58 */
typedef struct M1Pool289 { uint8_t unk00[8]; int32_t count8; M1Dr289 *head0C, *tail10, *free14; M1Dr289 *freeTail18; } M1Pool289;
typedef struct M1Src289 { uint8_t unk00[0x20]; void *cache20; } M1Src289;
extern M1Pool289 *m1_drawPool40F390;
extern M1Dr289 *m1_drawRecs40F750;
int32_t sub_001B9B90(void **cache, int32_t key);              /* regargs: cache=ECX key=ESI */
void sub_001A6540(M1Src289 *s, uint8_t *out);
void m1_DrawInit1B9460(M1Dr289 *d, M1Src289 *s);              /* regargs: d=EAX s=ECX */
int32_t sub_001BB650(void);
void sub_001B9EC0(M1Src289 *s, int32_t v);

/* 0x001BA6E0: get the texture record for (key, s): reuse a cached one if s has it, else take a record from the
   free list (or fail with -1), tag it with key, append it to the active list, initialise it from s and count it.
   Returns the record's index. */
int32_t m1_DrawAlloc1BA6E0(int32_t key, M1Src289 *s)
{
    M1Dr289 *e, *n;
    M1Pool289 *p;
    int32_t r, idx;
    if (s->cache20) {
        r = sub_001B9B90(&s->cache20, key);
        if (r != -1) return r;
    }
    e = m1_drawPool40F390->free14;
    if (!e) return -1;
    idx = (int32_t)(e - m1_drawRecs40F750);
    e->key1E = (int16_t)key;
    e->f50 = 0;
    sub_001A6540(s, e->f54);
    p = m1_drawPool40F390;
    n = p->free14->next20;
    p->free14 = n;
    if (n)
        n->prev24 = 0;
    else
        p->freeTail18 = 0;
    if (p->tail10) {
        e->next20 = 0;
        e->prev24 = p->tail10;
        p->tail10->next20 = e;
        p->tail10 = e;
    } else {
        p->tail10 = e;
        p->head0C = e;
        e->next20 = 0;
        e->prev24 = 0;
    }
    m1_DrawInit1B9460(e, s);
    sub_001B9EC0(s, sub_001BB650());
    m1_drawPool40F390->count8++;
    return idx;
}
