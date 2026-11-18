/* Area m1, file 218: small leftovers (peer slot prep, kind tables, cue-slot probe). Names inferred. */
#include "aac.h"

void OOG_STDCALL r4f_SlotPrepare1AD1B0(AacPeer *p, int snd);   /* 0x001AD1B0 thiscall, ECX=p */

/* 0x001AB1D0: prepare sound snd (16-bit) on player record b. */
void m1_PeerPrepare1AB1D0(short snd, int b)
{
    r4f_SlotPrepare1AD1B0(&aac_g40E604[b], snd);
}

/* 0x000F3140: kind 0 gives 2, kinds 1..0x21 give 1, anything else 0. */
int sub_000F3140(unsigned k)
{
    switch (k) {
    case 0: return 2;
    case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10:
    case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19: case 20:
    case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29: case 30:
    case 31: case 32: case 33: return 1;
    }
    return 0;
}

/* 0x000F30E0: pool count for kind k (2 -> 20, 8 -> 4, 12/13 and out of range -> 0, other kinds up to 0x21 -> 1). */
int m1_PoolCount0F30E0(unsigned k)
{
    switch (k) {
    case 0: case 1: case 3: case 4: case 5: case 6: case 7: case 9: case 10: case 11:
    case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
    case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32: case 33:
        return 1;
    case 2: return 0x14;
    case 8: return 4;
    }
    return 0;
}

typedef struct M1Sl218 { volatile int32_t on0; int32_t a4; volatile int32_t a8; uint8_t unkC[0x24]; } M1Sl218;
extern M1Sl218 m1_cueSlots401AF8[1];

/* 0x0019A7E0: probe the single cue slot (reads its value but always answers -1). */
int m1_CueProbe19A7E0(int i)
{
    volatile int k = i;
    if (k >= 0 && k < 1 && m1_cueSlots401AF8[k].on0) {
        int v = m1_cueSlots401AF8[k].a8;
        (void)v;
    }
    return -1;
}

typedef struct M1Ob218 { int32_t a0; int32_t a4; int32_t kind8; } M1Ob218;
/* sub_0001D0F0 comes from aac.h: void *(void *, int) */

/* 0x000A2050: slot count for object o by kind (hang if o is null); also stores 0x1D0F0(o, count) in *out when given. */
int m1_KindSlots0A2050(M1Ob218 *o, int *out)
{
    int r;
    if (!o) for (;;) ;
    switch (o->kind8) {
    case 7: case 0x39: r = 4; break;
    case 0x73: case 0x89: r = 2; break;
    case 0x30: case 0xF4: case 0xF8: r = 1; break;
    case 0xF6: r = 9; break;
    default: r = 0; break;
    }
    if (out) *out = (int)sub_0001D0F0(o, r);
    return r;
}

typedef struct M1Own218 { uint8_t unk00[0x120]; M1Ob218 *sub120; } M1Own218;

/* 0x000A21C0: slot count for the sub-object at o+0x120 by its kind; also stores 0x1D0F0(sub, count) in *out when given. */
int m1_SubKindSlots0A21C0(M1Own218 *o, int *out)
{
    M1Ob218 *p = o->sub120;
    int r;
    switch (p->kind8) {
    case 0x1B: case 0x1C: case 0x48: r = 3; break;
    case 0x26: r = 2; break;
    case 0x62: case 0x63: case 0x64: case 0x66: case 0x67: case 0x69: r = 5; break;
    case 0x38: case 0x65: case 0x68: r = 6; break;
    case 0x2C: case 0x2D: case 0x8B: r = 4; break;
    case 0x2E: case 0x2F: r = 10; break;
    default: r = 0; break;
    }
    if (out) *out = (int)sub_0001D0F0(p, r);
    return r;
}
