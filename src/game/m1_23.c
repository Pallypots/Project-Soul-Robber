/* Area m1, file 23: unrolled flag sweeps (the original unrolls these loops). Names inferred. */
#include <stdint.h>

typedef struct M1Flag20 {
    uint32_t flags00;          /* +0x00 bit 0 on, 0x1000 locked */
    uint8_t  unk04[0x20 - 4];
} M1Flag20;
extern M1Flag20 m1_flags3F8A18[16];  /* 0x003F8A18 */

#define M1_MARK(e, bit) if (((e).flags00 & 1) && !((e).flags00 & 0x1000)) (e).flags00 |= (bit)

/* 0x00169730: marks (0x10) every entry that is on and not locked. */
void m1_MarkOn169730(void)
{
    int i;
    for (i = 0; i < 16; i += 4) {   /* the original is unrolled by four */
        M1_MARK(m1_flags3F8A18[i], 0x10);
        M1_MARK(m1_flags3F8A18[i + 1], 0x10);
        M1_MARK(m1_flags3F8A18[i + 2], 0x10);
        M1_MARK(m1_flags3F8A18[i + 3], 0x10);
    }
}

/* 0x00169790: same sweep, setting 0x400. */
void m1_MarkOn169790(void)
{
    int i;
    for (i = 0; i < 16; i += 4) {
        M1_MARK(m1_flags3F8A18[i], 0x400);
        M1_MARK(m1_flags3F8A18[i + 1], 0x400);
        M1_MARK(m1_flags3F8A18[i + 2], 0x400);
        M1_MARK(m1_flags3F8A18[i + 3], 0x400);
    }
}

typedef struct M1Ent68 {
    uint32_t flags00;          /* +0x00 bit 0 in use, 0x10000000 armed, 0x20000000 fired */
    uint8_t  unk04[0x64 - 4];
    int32_t  owner64;          /* +0x64 */
} M1Ent68;
extern M1Ent68 m1_ents41CEC0[3];  /* 0x0041CEC0 */
#define M1_FIRE(e) if (((e).flags00 & 1) && ((e).flags00 & 0x10000000) && (e).owner64 == owner) \
    (e).flags00 = ((e).flags00 & ~0x10000000u) | 0x20000000
/* 0x000C6CD0: armed in-use entries of owner become fired (three entries, unrolled). */
void m1_FireOwnedC6CD0(int owner)
{
    M1_FIRE(m1_ents41CEC0[0]);
    M1_FIRE(m1_ents41CEC0[1]);
    M1_FIRE(m1_ents41CEC0[2]);
}

typedef struct M1Aim {
    uint8_t unk000[0x178];
    int32_t tgt178[3];         /* +0x178 entry indexes, -1 = none */
    int32_t cur184;            /* +0x184 current slot, -1 = none */
} M1Aim;
#define M1_CHECKTGT(k) if (a->tgt178[k] >= 0) { uint32_t f_ = m1_ents41CEC0[a->tgt178[k]].flags00; \
    if (!(f_ & 1) || !(f_ & 0x20000000)) a->tgt178[k] = -1; }

/* 0x000C6B90: drops target slots whose entry is no longer in use and fired, then
 * advances the current slot to the next valid one (or -1 after three tries). */
void m1_ValidateAimC6B90(M1Aim *a)
{
    int n;
    M1_CHECKTGT(0)
    M1_CHECKTGT(1)
    M1_CHECKTGT(2)
    if (a->cur184 < 0)
        return;
    for (n = 0; n < 3; n++) {
        if (a->tgt178[a->cur184] >= 0)
            return;
        a->cur184++;
        if (a->cur184 >= 3)
            a->cur184 = 0;
    }
    a->cur184 = -1;
}
