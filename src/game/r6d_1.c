/* Area r6d: text boxes and sound channels around 0x000760C0-0x00077220 (r6d_1). Names inferred. */
#include "r6d.h"

/* 0x00076700: append an encoded string to the text box; hangs if it is too long. */
void r6d_TextAppend(R6cText *t, const uint8_t *s)
{
    int n = r6c_TextLen(s);
    if (n > 0x800)
        for (;;) ;
#if defined(_M_IX86)
    __movsd((unsigned long *)(t->buf + t->len), (const unsigned long *)s, (unsigned)n >> 2);
    __movsb(t->buf + t->len + (n - (n & 3)), s + (n - (n & 3)), n & 3);
#else
    memcpy(t->buf + t->len, s, n);
#endif
    t->len += n;
    t->buf[t->len] = 0;
    t->pageChars = r6c_TextPageChars(t);
}

/* 0x000770B0: draw a text box with its optional frame passes.
   calls 0x00076E30 with EAX=t ESI=0x80 EBX=ctx; 0x00076FA0 with EAX=t ESI=0x80; 0x000768D0 with EDI=t */
void *r6d_TextDraw(void *ctx, R6cText *t)
{
    r6c_TextReset(t);
    if (t) {
        if (t->u00.flags0 < 0)
            sub_00076E30(t, 0x80, ctx, 2);
        if (t->u00.flags & 0x100)
            sub_00076FA0(t, 0x80, ctx, 2);
    }
    return sub_000768D0(t, ctx, (void *)sub_000385B0, 7);
}

