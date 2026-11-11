/* Area r6c: callers of the encoded text helpers (r6c_2). Names inferred. */
#include "r6c.h"

/* 0x00076430: character code of visible character n (clamped); two-byte codes are big-endian. */
uint16_t r6c_TextCharAt(const uint8_t *s, unsigned n)
{
    const uint8_t *p;
    if (!s)
        for (;;) ;
    if (n > (unsigned)r6c_TextCount(s))
        n = r6c_TextCount(s);
    p = s + r6c_TextIndex(s, n);
    if ((uint16_t)p[0] < r6c_textFont->singleCount)
        return p[0];
    return (uint16_t)((p[0] << 8) | p[1]);
}
