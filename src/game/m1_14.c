/* Area m1, file 14: small helpers. Names inferred. */
#include <stdint.h>

typedef struct M1TextArg {
    int32_t f00;
    const char *text04;        /* +0x04 */
} M1TextArg;
int sub_0005BBB0(int a);

/* 0x000DD880: 0x5BBB0(0) when the text is non-empty, else 0x5BBB0(-1); returns 0x2001. */
int m1_TextSelectDD880(M1TextArg *a)
{
    if (*a->text04 != 0) {
        sub_0005BBB0(0);
        return 0x2001;
    }
    sub_0005BBB0(-1);
    return 0x2001;
}

typedef struct M1Slot8C {
    int32_t f00;
    int32_t total04;           /* +0x04 */
    uint8_t unk08[0x8C - 8];
} M1Slot8C;
typedef struct M1SlotOwner {
    uint8_t  unk000[0x200];
    M1Slot8C slots[1];         /* +0x200, stride 0x8C */
} M1SlotOwner;
int sub_000CD180(M1SlotOwner *o, int i);

/* 0x000CD830: adds the amount computed by 0xCD180 to slot i's running total. */
void m1_AddSlotTotalCD830(M1SlotOwner *o, int i)
{
    M1Slot8C *s = &o->slots[i];
    s->total04 += sub_000CD180(o, i);
}
