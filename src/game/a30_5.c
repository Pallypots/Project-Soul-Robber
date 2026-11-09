/* Area a30, group 5: record tables and state dispatch 0x0004EC40..0x0004F7F0. Names inferred. */
#include "a30.h"

/* 0x0004EC40: flip double-buffer index and pass the new buffer on. */
void a30_FlipBuffer(void)
{
    a30_bufIndex ^= 1;
    sub_001B3300(&a30_buf12[a30_bufIndex]);
}
/* 0x0004ECC0..0x0004ECF0: record field getters. */
int a30_RecF00(int i) { return a30_rec4C[i].f00; }
int a30_RecFlags(int i) { return a30_rec4C[i].flags; }
int a30_RecF0C(int i) { return a30_rec4C[i].f0C; }
int a30_RecF10(int i) { return a30_rec4C[i].f10; }
/* 0x0004ED00..0x0004ED40: fields, 0 when flags 0xF000 set. */
int a30_RecF1C(int i) { if (a30_rec4C[i].flags & 0xF000) return 0; return a30_rec4C[i].f1C; }
int a30_RecF20(int i) { if (a30_rec4C[i].flags & 0xF000) return 0; return a30_rec4C[i].f20; }
int a30_RecF24(int i) { if (a30_rec4C[i].flags & 0xF000) return 0; return a30_rec4C[i].f24; }
/* 0x0004ED60: set byte pair 0 or 1; -1 if index too large. */
int a30_SetBytePair(int i, uint8_t a, uint8_t b)
{
    if (i > 1) return -1;
    a30_bytePairs[i].a = a;
    a30_bytePairs[i].b = b;
    return 0;
}
/* 0x0004F4D0: nonzero state? */
int a30_StateActive(void) { return a30_g3E0DB4 != 0; }
/* 0x0004F6D0: slot word +0x1C, 0 when out of range. */
int a30_SlotF1C(int i) { if (i >= 0 && i < A30_SLOT_COUNT) return a30_slots[i].f1C; return 0; }
/* 0x0004F6F0: read value. */
int a30_Get3E0DC8(void) { return a30_g3E0DC8; }
/* 0x0004F700: select current slot if in range. */
void a30_SelectSlot(int i) { if (i >= 0 && i < A30_SLOT_COUNT) a30_curSlot = &a30_slots[i]; }
/* 0x0004F720: clear current slot. */
void a30_ClearCurSlot(void) { a30_curSlot = 0; }
/* 0x0004F730: store boolean. */
void a30_SetFlag3E0DD0(uint8_t v) { a30_g3E0DD0 = v != 0; }
/* 0x0004F740: clear stream state. */
void a30_ClearStreamState(void) { a50_streamState = 0; }
