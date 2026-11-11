/* Area r6d: memory/string helpers and scene tree walk around 0x0007F1E0-0x00084EB8 (r6d_15). Names inferred. */
#include "r6d.h"

/* 0x0007F1E0: fill n bytes with v; returns 0. */
int r6d_MemFill(void *p, int v, unsigned n)
{
#if defined(_M_IX86)
    uint32_t w = (uint8_t)v;
    w |= w << 8;
    w |= w << 16;
    __stosd((unsigned long *)p, w, n >> 2);
    __stosb((unsigned char *)p + (n - (n & 3)), (unsigned char)v, n & 3);
#else
    memset(p, v, n);
#endif
    return 0;
}

/* 0x0007F210: copy n bytes; returns 0. */
int r6d_MemCopy(void *dst, const void *src, unsigned n)
{
#if defined(_M_IX86)
    __movsd((unsigned long *)dst, (const unsigned long *)src, n >> 2);
    __movsb((unsigned char *)dst + (n - (n & 3)), (const unsigned char *)src + (n - (n & 3)), n & 3);
#else
    memcpy(dst, src, n);
#endif
    return 0;
}

/* 0x0007F560: compare two strings four bytes at a time (NULL sorts first). */
int r6d_StrCompare(const char *a, const char *b)
{
    int r = 0;
    int n;
    const char *e;
    if (!a)
        return -1;
    if (!b)
        return 1;
    if (a == b)
        return 0;
    e = a;
    if (*e)
        while (e[1])
            e++;
    n = (int)(e - a) + 1;
    while (n >= 4) {
        if (*(const int32_t *)a != *(const int32_t *)b) {
            r = *(const int32_t *)a - *(const int32_t *)b;
            if (r)
                return r;
            break;
        }
        n -= 4;
        a += 4;
        b += 4;
    }
    while (n) {
        if (*a != *b)
            return (uint8_t)*a - (uint8_t)*b;
        a++;
        b++;
        n--;
    }
    return r;
}

/* 0x00082140: collect the visible items of a scene box tree into the draw list (max 256). */
void r6d_TreeCollect(R6dTree *t)
{
    R6dTreeItem *it;
    for (;;) {
        if (r6c_BoxBehind(&t->boxMax, &t->boxMin, &r6c_vec3EC9E8, &r6c_vec3EC864)) {
            for (it = t->items; it; it = it->next) {
                uint8_t *base;
                uint8_t *e;
                if ((unsigned)r6c_n3ECA20 >= 0x100)
                    break;
                if (it->owner->flags & 1)
                    continue;
                base = it->owner->parts;
                e = base + *(int32_t *)(base + it->index * 0x50 + 0x28);
                if (r6c_BoxBehind((const R6cVec4 *)(e + 0x20), (const R6cVec4 *)(e + 0x10),
                                  &r6c_vec3EC9E8, &r6c_vec3EC864))
                    r6c_out3ECA78[r6c_n3ECA20++] = it;
            }
            if (t->left)
                r6d_TreeCollect(t->left);
        }
        if (!t->right)
            return;
        t = t->right;
    }
}

/* 0x00084E70: remember a table and allocate a zeroed 8-byte slot per entry for it. */
void r6d_SlotsAlloc(R6dCountTable *t)
{
    uint8_t *p;
    unsigned n;
    a80_g3ED1B0 = t;
    if (t) {
        p = (uint8_t *)a50_Alloc(3, t->count * 8, 0, 0);
        n = ((R6dCountTable *)a80_g3ED1B0)->count * 8;
        a8c_g3ECCA8 = p;
#if defined(_M_IX86)
        __stosd((unsigned long *)p, 0, n >> 2);
        __stosb(p + (n - (n & 3)), 0, n & 3);
#else
        memset(p, 0, n);
#endif
    }
}
