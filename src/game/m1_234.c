/* Area m1, file 234: actor state sequences (register-argument callers per docs/verification.md). Names inferred. */
#include <stdint.h>

typedef struct M1E234 { uint8_t unk00[0xC]; uint32_t flagsC; } M1E234;
typedef struct M1O234 { uint8_t unk00[0x30]; void *mdl30; } M1O234;
typedef struct M1S234 { uint8_t unk00[0x58]; int32_t st58; uint8_t unk5C[0x278 - 0x5C]; M1E234 *ext278; } M1S234;
int32_t sub_000833E0(void *m);
int32_t b4c_Enter1456E0(M1O234 *o, M1S234 *s, int32_t a, int32_t b);
void sub_0001D4E0(M1O234 *o);
void r3_SetStateA(M1O234 *obj, M1S234 *act, int state);    /* regargs: obj=EBX act=EDI state=stack */
void r3_SetStateA2(M1O234 *obj, M1S234 *act, int state);   /* same function (alias stops cl merging calls) */
void r3_SetStateA3(M1O234 *obj, M1S234 *act, int state);   /* same function (alias stops cl merging calls) */

/* 0x00132AF0: four-step sequence: wait for the clip, enter state 0x15 (nudge the model if it took), wait again,
   then state 1 (flags 1+0x200), 3 (flag 1) or 5 (calls 0x131310 with obj=EBX act=EDI). */
void m1_Seq132AF0(M1O234 *o, M1S234 *s)
{
    M1E234 *e = s->ext278;
    switch (s->st58) {
    case 0:
        if (!sub_000833E0(o->mdl30))
            return;
        s->st58++;
    case 1:
        if (b4c_Enter1456E0(o, s, 0x15, 0) == 1)
            sub_0001D4E0(o);
        s->st58++;
        return;
    case 2:
        if (!sub_000833E0(o->mdl30))
            return;
        s->st58++;
    case 3:
        if (e->flagsC & 1) {
            if (e->flagsC & 0x200) {
                r3_SetStateA(o, s, 1);
                return;
            }
            r3_SetStateA2(o, s, 3);
            return;
        }
        r3_SetStateA3(o, s, 5);
        return;
    }
}

typedef struct M1Hb234 { int32_t used0; void *heap4; } M1Hb234;
typedef struct M1Heap234 { int32_t linear0; uint8_t *cur4; uint8_t *end8; uint8_t unk0C[0x24]; int32_t lock30; } M1Heap234;
void sub_001AA460(int32_t lock);
int32_t sub_001AA520(int32_t lock);
void *r1_HeapFindFit(M1Heap234 *h, int size);                 /* regargs: h=ECX size=EDX */
uint8_t *r1g_BlkTake(int low, void *b, uint32_t size);         /* regargs: low=EAX b=ECX size=EBX */

/* 0x00047390: allocate size bytes: linear heaps bump cur4 (64-byte aligned, 0x40 header, fails at end8); others take
   the lock, find the best block and carve it (calls 0x47080 with h=ECX size=EDX, 0x47240 with low=EAX b=ECX size=EBX). */
void *m1_HeapAlloc047390(M1Heap234 *h, uint32_t size)
{
    void *b;
    uint8_t *p;
    if (h->linear0) {
        M1Hb234 *hdr = (M1Hb234 *)h->cur4;
        uint8_t *end = h->end8;
        uint8_t *a = (uint8_t *)(((uintptr_t)hdr + 0x7F) & ~0x3Fu);
        uint8_t *n = (uint8_t *)(((uintptr_t)a + size + 0x3F) & ~0x3Fu);
        if (end <= n)
            return 0;
        h->cur4 = n;
        hdr->heap4 = h;
        hdr->used0 = 1;
        *(int32_t *)(a - 4) = 1;
        return a;
    }
    if (h->lock30 != -1)
        sub_001AA460(h->lock30);
    b = r1_HeapFindFit(h, size);
    if (!b) {
        if (h->lock30 != -1)
            while (sub_001AA520(h->lock30) == -1)
                ;
        return 0;
    }
    p = r1g_BlkTake(1, b, size);
    if (h->lock30 != -1)
        while (sub_001AA520(h->lock30) == -1)
            ;
    return p + 0x40;
}

typedef struct M1Sc234 { uint8_t unk00[0x130]; int32_t res130; } M1Sc234;
typedef struct M1Fo234 { uint8_t unk00[0x60]; uint8_t pos60[0x10]; } M1Fo234;
extern M1Sc234 *ae0_ptr3F6100;
void *sub_00035DD0b(M1Fo234 *o, int32_t res, int32_t a, int32_t b);   /* aliases of the same functions keep */
void sub_00033880b(void *h, float *out);                              /* cl from merging the two branches */
void sub_00034E00b(void *h, const void *pos, float *v, const float *col);
void *sub_00035DD0(M1Fo234 *o, int32_t res, int32_t a, int32_t b);
void sub_00033880(void *h, float *out);
void sub_00034E00(void *h, const void *pos, float *v, const float *col);
void *sub_000ED630(int32_t a, int32_t b, void *pos, int32_t c, int32_t d);

/* 0x00196DB0: green effect 2/3 (k < 4) or 3/3 at o, then effect 5/0x1E at o with flag k >= 4
   (regargs: k=EAX o=ECX). */
void m1_GreenFx196DB0(int32_t k, M1Fo234 *o)
{
    float col[4];
    float a[8];
    float b[8];
    void *h;
    col[0] = 0.0f;
    col[1] = 1.0f;
    col[2] = 0.0f;
    col[3] = 1.0f;
    if (k < 4) {
        h = sub_00035DD0(o, ae0_ptr3F6100->res130, 2, 3);
        sub_00033880(h, a);
        sub_00034E00(h, o->pos60, b, col);
        sub_000ED630(5, 0x1E, o->pos60, 0, 0);
        return;
    }
    h = sub_00035DD0b(o, ae0_ptr3F6100->res130, 3, 3);
    sub_00033880b(h, a);
    sub_00034E00b(h, o->pos60, b, col);
    sub_000ED630(5, 0x1E, o->pos60, 0, 1);
}

