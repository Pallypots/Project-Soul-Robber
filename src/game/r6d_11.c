/* Area r6d: string drawing at 0x00079590 (r6d_11). Names inferred. */
#include "r6d.h"

/* 0x00079590: draw an encoded string glyph by glyph from x, returning the new draw context.
   regargs: x=EAX ctx=ECX; the original pushes an unused third argument 0 to 0x00076430 */
void *r6d_DrawString(int x, void *ctx, int y, int colour, const uint8_t *s)
{
    int n = r6c_TextCount(s);
    int i;
    for (i = 0; i < n; i++) {
        R6dGlyphSize sz;
        ctx = sub_000380A0(ctx, x, y, 0, &sz, colour, 1.0f, 1.0f, r6c_TextCharAt(s, i));
        x += sz.w;
    }
    return ctx;
}
