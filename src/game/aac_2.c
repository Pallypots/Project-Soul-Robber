/* Area aac, group 2: network/session wrappers and per-slot tables (0x1AA590-0x1ABC00). Names inferred. */
#include "aac.h"

/* 0x001AA590: pack (d, b, c, 0) into a block and pass it with a and e to 0x2226F3. */
int OOG_STDCALL aac_SendBlock(int a, int b, int c, int d, int e)
{
    AacBlock4 blk;
    blk.a = d;
    blk.b = b;
    blk.c = c;
    blk.d = 0;
    return sub_002226F3(a, &blk, e);
}

/* 0x001AA7C0: in mode 0, close the pending session 0x40E698 and flush. */
void aac_ClosePending(void)
{
    uint8_t buf[0x58];
    if (aac_g40E348 == 0 && aac_g40E698 != 0) {
        sub_002224A2(aac_g40E690, aac_g40E698);
        sub_00223F9C();
        sub_002225ED(aac_g40E690, buf);
        aac_g40E698 = 0;
    }
}

/* 0x001AB0A0: slot is active; an unused slot (id -1) has its flag cleared. */
int aac_SlotActive(int i)
{
    AacSlot70 *s = &aac_g40CF50[i];
    if (s->id == -1) {
        s->active = 0;
        return 0;
    }
    return s->active != 0;
}

/* 0x001AB1F0: query 0x1ACF10 on player record b (a unused). */
int aac_PeerQuery1(int unused, int b)
{
    (void)unused;
    return sub_001ACF10(&aac_g40E604[b]);
}

/* 0x001AB280: query 0x1ACF20 on player record b (a unused). */
int aac_PeerQuery2(int unused, int b)
{
    (void)unused;
    return sub_001ACF20(&aac_g40E604[b]);
}

/* 0x001AB4A0: set mode and store the value in the slot for that mode. */
void aac_SetModeValue(int v, int mode)
{
    aac_g40E348 = mode;
    if (mode == 0)
        aac_g365158 = v;
    else if (mode == 1)
        aac_g36515C = v;
    else
        aac_g365160 = v;
}

/* 0x001AB5F0: forward a to the handle in slot b of 0x40E518, if any. */
void aac_SlotForward(int a, int b)
{
    void *h = aac_g40E518[b];
    if (h)
        sub_002227C3(h, a);
}

/* 0x001AB610: map the library's state 0 to 1 and 2 to 2, else 0. */
int aac_MapState(void)
{
    switch ((uint16_t)sub_001BEE51()) {
    case 0: return 1;
    case 2: return 2;
    }
    return 0;
}

/* 0x001AB810: store a weight and a 3-double vector in slot i. */
void aac_SetSlotVec(const AacDVec3 *v, float w, int i)
{
    aac_g365170[i] = w;
    aac_g365228[i].x = v->x;
    aac_g365228[i].y = v->y;
    aac_g365228[i].z = v->z;
}

/* 0x001AB860: library query on handle 0x40E690 returned 0. */
int aac_Query40E690Zero(void) { return sub_002225B2(aac_g40E690, 0) == 0; }

/* 0x001ABC00: run 0x1AB4E0 with code 0x2C. */
void aac_Run2C(int a) { sub_001AB4E0(0x2C, a); }
