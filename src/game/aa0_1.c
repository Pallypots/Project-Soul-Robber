/* Area aa0, group 1: slot table and small state helpers (0x000A3000..0x000AA300). Names inferred. */
#include "aa0.h"

/* 0x000A3280: zero +0x54 and store v at +0x58. */
void aa0_SetPair54(Aa0Pair54 *o, float v) { o->f54 = 0.0f; o->f58 = v; }

/* 0x000A41D0: change the state at +0x3C, resetting its timer on change. */
void aa0_SetStateB(Aa0StateB *o, int s) { if (o->state != s) { o->state = s; o->timer = 0; } }

/* 0x000A4290: address of slot i. */
Aa0Slot *aa0_GetSlot(int i) { return &aa0_slots[i]; }

/* 0x000A42A0: the object attached to slot i. */
void *aa0_GetSlotObj(int i) { return aa0_slots[i].obj120; }

/* 0x000A4480: set slot i's value at +0x124. */
void aa0_SetSlotVal(int i, int v) { aa0_slots[i].val124 = v; }

/* 0x000A44A0: copy a 4-float vector into slot i. */
void aa0_SetSlotVec(int i, const float *v) { aa0_Vec4Copy(aa0_slots[i].vecB0, v); }

/* 0x000A7920: change the state at +0x1C, resetting its timer on change. */
void aa0_SetStateA(Aa0StateA *o, int s) { if (o->state != s) { o->state = s; o->timer = 0; } }

/* 0x000A7940: copy a 4-float vector to +0x40 of an object. */
void aa0_SetVec40(uint8_t *o, const float *v) { aa0_Vec4Copy(o + 0x40, v); }

/* 0x000A86A0: clear the 0x00420EF8 flags and timer. */
void aa0_Reset420EF8(void) { aa0_flags420EF8 = 0; aa0_float420EFC = 0.0f; }

/* 0x000A86C0: set bit 0 of 0x00420EF8. */
void aa0_Set420EF8(void) { aa0_flags420EF8 |= 1; }

/* 0x000A9960: mark an object done (bit 30). */
void aa0_MarkDone(uint32_t *flags) { *flags |= 0x40000000; }

/* 0x000A9C40: mark done then request one unit from 0x000E5B70. */
int aa0_MarkDoneAndStep(uint32_t *flags) { *flags |= 0x40000000; return sub_000E5B70(1); }

/* 0x000A9D80: bit 0 of record i's flag byte. */
int aa0_Rec16Flag(int i) { return aa0_rec16Table[i].flag & 1; }

/* 0x000A9DA0: address of record i's flag byte. */
int8_t *aa0_Rec16FlagPtr(int i) { return &aa0_rec16Table[i].flag; }

/* 0x000A9FE0: set bit 0 of 0x003ED764 and clear 0x003ED74C. */
void aa0_Mark3ED764(void) { aa0_flags3ED764 |= 1; aa0_word3ED74C = 0; }

/* 0x000AA2E0: forward to 0x0005EB10 when enabled. */
void aa0_Forward5EB10(int v) { if (aa0_enabled413142) sub_0005EB10(0, v); }
