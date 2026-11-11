/* Area r1j, group 2: LZ bit-stream decoder 0x00031120.
   Names inferred. */
#include "r1j.h"

/* read one bit (LSB first) from the stream; after each 32 bits advance to
   the next word and, when a refill callback is set and the byte count has
   reached the limit, call it */
static __inline uint32_t r1j_GetBit(R1jBits *bs)
{
    uint32_t *w = bs->cur;
    uint32_t bit = bs->bit;
    uint32_t b = (*w >> bit) & 1;
    bs->bit = (bit + 1) & 0x1F;
    if (bs->bit == 0) {
        void (*fill)(R1jBits *) = bs->fill;
        bs->cur = w + 1;
        bs->bytes += 4;
        if (fill != 0 && bs->limit >= 0 && bs->bytes >= bs->limit)
            fill(bs);
    }
    return b;
}

/* 0x00031120: decode size bytes of LZ data from bit stream bs into dst.
   Each item starts with a flag bit: 1 = an 8-bit literal; 0 = a back
   reference whose distance is a fixed 10-bit field (mode 1) or a field
   of r1j_lzBits[n] bits after a unary prefix n, followed by a length
   coded the same way (unary prefix then field). The copy is a forward
   dword-then-byte copy from dst[pos - dist - 1]. Every 1000 items the
   thread yields (0x001AB850). */
void r1j_LzDecode(R1jBits *bs, char mode, uint8_t *dst, uint32_t size)
{
    uint32_t pos = 0;
    int tick = 0;
    uint32_t i, n, v, dist, len;
    if (size == 0)
        return;
    do {
        if (++tick >= 1000) {
            sub_001AB850();
            tick = 0;
        }
        if (r1j_GetBit(bs) == 0) {
            dist = 0;
            if (mode == 1) {
                for (i = 0; i < 10; i++)
                    dist |= r1j_GetBit(bs) << i;
            } else {
                n = 0;
                while (r1j_GetBit(bs) == 0)
                    n++;
                for (i = 0; i < r1j_lzBits[n]; i++)
                    dist |= r1j_GetBit(bs) << i;
            }
            n = 0;
            while (r1j_GetBit(bs) == 0)
                n++;
            len = 0;
            for (i = 0; i < r1j_lzBits[n]; i++)
                len |= r1j_GetBit(bs) << i;
            r1j_CopyFwd(dst + pos, dst + pos - dist - 1, len);
            pos += len;
        } else {
            dst[pos] = 0;
            for (i = 0; i < 8; i++) {
                v = r1j_GetBit(bs);
                dst[pos] |= (uint8_t)(v << i);
            }
            pos++;
        }
    } while (pos < size);
}
