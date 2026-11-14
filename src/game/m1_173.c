/* Area m1, file 173: sound channel resets (revisited). Names inferred. */
#include <stdint.h>

extern uint32_t *m1_chFlags2DF660[2];
extern uint32_t *m1_chVol2DF650[2];
extern int32_t m1_chA3E69C0[2];
extern int32_t m1_chB3E69D8[2];
extern int32_t m1_chId3E69A8[2];

#pragma optimize("s", on)
/* 0x77190: reset both stream channels (clear the playing bit, zero the volume, forget the id). */
void m1_ChReset077190(void) {
    int o;
    for (o = 0; o < 8; o += 4) {
        uint32_t *f = *(uint32_t **)((uint8_t *)m1_chFlags2DF660 + o);
        *(int32_t *)((uint8_t *)m1_chA3E69C0 + o) = 0;
        *(int32_t *)((uint8_t *)m1_chB3E69D8 + o) = 0;
        *f &= ~0x80u;
        *(volatile uint32_t *)*(uint32_t **)((uint8_t *)m1_chVol2DF650 + o) &= 0xFFFF0000;
        *(int32_t *)((uint8_t *)m1_chId3E69A8 + o) = -1;
    }
}
#pragma optimize("", on)

typedef struct M1Rg173 { int32_t n0; int32_t a4; int32_t a8; int32_t aC; int32_t *buf10; } M1Rg173;

/* 0xBC5F0: clear a ring buffer; 1 if it is too small (< 3 entries), 2 if it has no storage. */
int m1_RingClear0BC5F0(M1Rg173 *r) {
    int i; volatile int k;
    if (r->n0 < 3) return 1;
    if (r->buf10 == 0) return 2;
    r->a4 = 0; r->a8 = 0; r->aC = 0;
    k = r->n0;
    if (k > 0)
        for (i = 0; i < r->n0; i++) r->buf10[i] = 0;
    return 0;
}

typedef struct M1Fl173 { uint8_t unk00[0xC]; int32_t sizeC; uint8_t rest[0x10]; } M1Fl173;
extern M1Fl173 m1_streams2C8900[0x21E];

/* 0x4F680: size of data file i rounded up to 16 bytes (0 for the impossible out-of-range case). */
int m1_FileSize04F680(int i) {
    volatile int k = i;
    if (k < 0 && k >= 0x21E) return 0;
    return (m1_streams2C8900[i].sizeC + 15) & ~15;
}

typedef struct M1Slot173 { void *data; void *ent; uint8_t pad[8]; } M1Slot173;
typedef struct M1Bind173 { void *bank0; M1Slot173 *slots4; uint8_t *mem8; } M1Bind173;
typedef struct M1Bank173 { uint8_t unk00[8]; int32_t n8; uint8_t unk0C[0x14]; } M1Bank173;
int m1_BankCheck1AE950(M1Bank173 *k);

/* 0x1B8800: bind a sound bank to a memory block: one slot per entry, data pointer only for entries that have data. */
uint8_t *m1_BankBind1B8800(M1Bind173 *b, uint8_t *mem, M1Bank173 *k) {
    uint8_t *data, *e; int i; volatile int vi;
    if (m1_BankCheck1AE950(k) == 0) return 0;
    b->mem8 = mem;
    b->slots4 = (M1Slot173 *)mem;
    data = mem + k->n8 * 16;
    b->bank0 = k;
    e = (uint8_t *)k + 0x20;
    for (i = 0; i < k->n8; i++, e += 0x50) {
        int off; vi = i * 0x10; off = vi;
        *(void **)((uint8_t *)b->slots4 + off + 4) = e;
        if (*(int32_t *)(e + 8) == 0) *(void *volatile *)((uint8_t *)b->slots4 + off) = 0;
        else *(void *volatile *)((uint8_t *)b->slots4 + off) = data;
    }
    return data;
}
