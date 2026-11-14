/* Area m1, file 184: save slot scan and options defaults. Names inferred. */
#include <stdint.h>
#include <intrin.h>

extern uint8_t *m1_save3E3934;
int sub_001A9E60(int slot, void *hdr);

/* 0x54C00: probe the five save slots; state 0 = empty, 1 = valid save, 2 = damaged. Returns the empty count, or -1 when none is empty but some are valid. */
int m1_SaveScan054C00(void) {
    int i = 0, h = 0, off, valid = 0, empty = 0;
    int32_t *volatile sv; int32_t *st;
    __stosd((unsigned long *)(m1_save3E3934 + 0x122AB0), 0, 0xA0);
    sv = (int32_t *)(m1_save3E3934 + 0x122D30); st = sv;
    st[0] = 0; st[1] = 0; st[2] = 0; st[3] = 0; st[4] = 0;
    for (off = 0x122D30; off < 0x122D44; off += 4, i++, h += 0x80) {
        switch (sub_001A9E60(i, m1_save3E3934 + h + 0x122AB0)) {
        case 0: *(int32_t *)(m1_save3E3934 + off) = 0; empty++; break;
        case 1: *(int32_t *)(m1_save3E3934 + off) = 2; break;
        case 2: valid++; *(int32_t *)(m1_save3E3934 + off) = 1; break;
        }
    }
    if (empty == 0 && valid != 0) return -1;
    return empty;
}

typedef struct M1Opt184 {
    int32_t i0; volatile int16_t w4, w6, w8, wA, wC, wE; float f10, f14; volatile int16_t w18, w1A; float f1C;
    int32_t i20, i24, i28; uint8_t b2C; uint8_t unk2D[0x7FF]; int32_t i82C; uint8_t e830[0x9C]; uint8_t e8CC[0x9C];
} M1Opt184;
int  sub_00102FA0(void *p, ...);
void sub_00038030(void *e, int on);
void r1b_StepperSet(void *e, int a, int b, int c, int d);

/* 0x75F00: fill an options block with defaults (hangs on a null block) and reset its two steppers. */
void m1_OptDefaults075F00(M1Opt184 *o) {
    if (o == 0) for (;;) ;
    o->w4 = 0x40; o->w6 = 0x40;
    o->f10 = 1.0f; o->f14 = 1.0f;
    o->i0 = 0x81;
    o->w8 = 100; o->wA = 100; o->wC = 0; o->wE = 0;
    o->w18 = 0x1D; o->w1A = 0; o->f1C = -1.0f;
    o->i20 = 0; o->i24 = 0; o->i28 = 0; o->i82C = 0; o->b2C = 0;
    sub_00102FA0(o->e830);
    sub_00038030(o->e830, 0);
    r1b_StepperSet(o->e830, 0, 0, 0, 0);
    sub_00102FA0(o->e8CC);
    sub_00038030(o->e8CC, 1);
    r1b_StepperSet(o->e8CC, 1, 0, 0, 0);
}
