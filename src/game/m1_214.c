/* Area m1, file 214: revisits with size optimisation. Names inferred. */
#include <stdint.h>

typedef struct M1Pl214 { uint32_t flags0; uint8_t unk04[0x14]; } M1Pl214;
typedef struct M1PlS214 { uint32_t i0; } M1PlS214;
typedef struct M1PlE214 { uint8_t unk00[0x74]; M1PlS214 *st74; } M1PlE214;
extern M1Pl214 b16_pool18[5];
void sub_000ED780(void *o);

#pragma optimize("s", on)
/* 0x16BE00: finish a switch effect: if armed, flag (8) every live pool entry matching its polarity (flag-4 entries want it on, others want it off unless locked by 0x10); then clear its own flag 8 and remove it. */
void m1_SwitchFinish16BE00(void *o, M1PlE214 *e) {
    M1PlS214 *s = e->st74; uint32_t v = s->i0, bit, c;
    if (v & 2) {
        bit = (v >> 2) & 1;
#define M1_SW214(i) \
        c = b16_pool18[i].flags0; \
        if (c & 1) { \
            if (c & 4) { if (bit != 0) b16_pool18[i].flags0 = c | 8; } \
            else if (!(c & 0x10) && bit == 0) b16_pool18[i].flags0 = c | 8; \
        }
        M1_SW214(0) M1_SW214(1) M1_SW214(2) M1_SW214(3) M1_SW214(4)
#undef M1_SW214
    }
    s->i0 &= ~8u;
    sub_000ED780(o);
}
#pragma optimize("", on)
