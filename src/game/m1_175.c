/* Area m1, file 175: talk sequence (revisited). Names inferred. */
#include <stdint.h>

extern int32_t m1_talk3EDBB0;
extern int32_t m1_talkN3EDBB8;
extern uint8_t m1_stats41FEC0[];
void sub_000D7590(void);
void sub_000D9AB0(int id);
int  sub_000CF790(void *s, int k);

/* 0xD8750: pick the next line of a talk sequence by step count (odd/even stat 12 picks the variant). */
int m1_TalkStep0D8750(void) {
    int n; volatile int r;
    if (m1_talk3EDBB0 == 0) {
        if (m1_talkN3EDBB8 > 5) return 1;
        sub_000D7590();
        return 0;
    }
    n = m1_talkN3EDBB8;
    if (n <= 3) { sub_000D9AB0(0x38D); return 0; }
    if (n <= 6) {
        sub_000D9AB0(0x38D);
        r = sub_000CF790(m1_stats41FEC0, 0xC) % 2;
        switch (r) { case 0: sub_000D9AB0(0x390); return 0; }
        sub_000D9AB0(0x3A0); return 0;
    }
    if (n <= 9) {
        sub_000D9AB0(0x38E);
        r = sub_000CF790(m1_stats41FEC0, 0xC) % 2;
        switch (r) { default: sub_000D9AB0(0x3A0); return 0; case 0: break; }
        sub_000D9AB0(0x390); return 0;
    }
    if (n != 10) return 0;
    sub_000D9AB0(0x38F);
    return 1;
}

typedef struct M1Bits175 { uint16_t id; uint16_t bits[6]; } M1Bits175;
extern M1Bits175 m1_flagSets300FC8[];
extern uint8_t m1_flagBits300FCA[];
void sub_000D9B30(int id);

/* 0xDE400: set or clear flags 0x1A0..0x1FF from the bit set with this id. */
void m1_FlagSetApply0DE400(int id) {
    uint16_t *bits; int i; M1Bits175 *e; volatile unsigned d = 16;
    for (i = 0, e = m1_flagSets300FC8; e->id != 0xFFFF; e++, i++)
        if (e->id == id) { bits = (uint16_t *)(m1_flagBits300FCA + i * 0xE); break; }
    for (i = 0; i < 0x60; i++) {
        unsigned q = (unsigned)i / d, r = (unsigned)i % d;
        if (bits[q] & (1 << r)) sub_000D9AB0(i + 0x1A0);
        else sub_000D9B30(i + 0x1A0);
    }
}

extern uint16_t m1_flagsAll2C4BB0[];

/* 0x409E0: load the saved flag bitmap for room n (1..24; hangs otherwise): set flags it has that are not set yet. */
void m1_RoomFlags0409E0(int n) {
    uint16_t *row = (uint16_t *)((uint8_t *)m1_flagsAll2C4BB0 + n * 0x80); volatile int k = n;
    int i; volatile unsigned d = 16;
    if (k < 1 || k > 0x18) for (;;) ;
    for (i = 0; i < 0x400; i++) {
        unsigned q = (unsigned)i / d, b = 1u << ((unsigned)i % d);
        if (m1_flagsAll2C4BB0[q] & b) continue;
        if (row[q] & b) sub_000D9AB0(i); else sub_000D9B30(i);
    }
}

typedef struct M1Deck175 { uint8_t unk00[0x1AC]; float t1AC; uint8_t unk1B0[0x240 - 0x1B0]; int32_t cards[18]; int32_t keep[4]; int32_t n298; } M1Deck175;
extern M1Deck175 *m1_scr3F6130;
int sub_001C7EE1(void);

#pragma optimize("s", on)
/* 0x104070: shuffle the 18-card deck (two of each 0..8), keeping a snapshot of the first four halfway through. */
void m1_DeckShuffle104070(void) {
    M1Deck175 *d = m1_scr3F6130; int32_t *c, *k; int i, n, a, b, t;
    { int32_t *volatile cp = d->cards, *volatile kp = d->keep; c = cp; k = kp; }
    d->t1AC = 0.0f;
    for (i = 0; i < 18; ) { t = (unsigned)i % 9; i++; c[i - 1] = t; }
    for (n = 0; n < 100; n++) {
        if (n == 50) { k[0] = c[0]; k[1] = c[1]; k[2] = c[2]; k[3] = c[3]; }
        a = sub_001C7EE1() % 18;
        b = sub_001C7EE1() % 18;
        t = c[a]; c[a] = c[b]; c[b] = t;
    }
    d->n298 = 0;
}
#pragma optimize("", on)
