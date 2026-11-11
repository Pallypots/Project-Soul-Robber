/* Area r1, group 8: file, table, HUD and vector helpers 0x0004FBF0..0x0005BAC0. Names inferred. */
#include "r1.h"

/* 0x0004FBF0: read n bytes at the file position into buf and advance it.
   regargs: f=ESI n=EDI; buf is the stack argument */
int r1_FileRead(R1File *f, void *buf, int n)
{
    int st;
    sub_001A8490(f->h, f->pos, 0);
    while (sub_001A8500(f->h, 1, &st)) ;
    sub_00102FA0(0);
    sub_001A8410(f->h, buf, n);
    f->pos += n;
    return n;
}

/* 0x00053230: find a used record after prev (or from the start) matching a and b (-1 = any b).
   The original re-tests the same record on every pass of its loop.
   regargs: prev=EAX; calls 0x00052EC0 with EAX=&a EDX=a EBX=&b stack=b */
R1Ent20 *r1_EntFind(R1Ent20 *prev, int a, int b)
{
    R1Ent20 *p;
    int i;
    p = prev ? prev + 1 : r1_ents3E2550;
    sub_00052EC0(&a, a, &b, b);
    for (i = p - r1_ents3E2550; i < 17; i++)
        if (p->used && p->a == a && (b == -1 || p->b == b)) return p;
    return 0;
}

/* 0x00058220: release a resource and return its node to the free list.
   regargs: r=EAX */
void r1_ResRelease(R1Res *r)
{
    R1ResNode *n;
    sub_00053880(r->h);
    r->h = 0;
    r->a = -1;
    r->b = -1;
    n = (R1ResNode *)((uint8_t *)r - 0x10);
    sub_0003D8C0(n);
    sub_0003D880(r1_resFree3E3F54, n);
}

/* 0x0005BAC0: dot of the direction from a reference point (mode 0 camera, 1 model) to p, divided by scale.
   regargs: mode=EAX; p and scale are the stack arguments */
float r1_DirDot(int mode, const float *p, float scale)
{
    float ref[4], d[4], n[4];
    switch (mode) {
    case 0: sub_000F5D40(ref, r1_ctx42C8E4->pos); break;
    case 1: sub_000F5D40(ref, r1_model420E98->pos); break;
    }
    sub_001AD9F0(d, p, ref);
    sub_001AD7E0(n, d);
    return sub_001AD9D0(d, n) / scale;
}

/* 0x0004FB50: read n bytes at the file position into buf, yielding while busy before and after.
   regargs: f=ESI n=EBX; buf is the stack argument */
int r1_FileReadWait(R1File *f, void *buf, int n)
{
    int st;
    sub_001A8490(f->h, f->pos, 0);
    while (sub_001A8500(f->h, 1, &st)) sub_001AB850();
    sub_00102FA0(0);
    sub_001A8410(f->h, buf, n);
    while (sub_001A8500(f->h, 1, &st)) sub_001AB850();
    f->pos += n;
    return n;
}
