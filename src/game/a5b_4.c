/* Scene/sequence helpers (0x0005C2C0-0x0005D3FD), second pass.
 * Reference build OOGIE-XBOX-US-RETAIL. Names inferred. */
#include "a5b.h"

/* 0x0005C2C0: point obj->+0xC at its inline data and store obj in `owner`. */
void a5b_AttachInline(A5bPair *owner, uint8_t *obj)
{
    *(uint8_t **)(obj + 0xC) = obj + 0x10;
    a5b_PairSet(owner, obj);
}

/* 0x0005C8D0: walk obj->+0xC with callback 0x0005BC90. */
int a5b_WalkWith5BC90(uint8_t *obj)
{
    sub_0005A510(*(void **)(obj + 0xC), (void *)sub_0005BC90);
    return 0;
}

/* 0x0005CC50: self-link a node, clear its id and init the part at +0x20. */
void a5b_NodeInit(uint8_t *node)
{
    *(uint8_t **)(node + 0xC) = node;
    *(int32_t *)(node + 0x10) = -1;
    sub_0005CAF0(node + 0x20);
}

/* 0x0005CCD0: finish a sequence item (running 0x001997E0 first unless `quiet`). */
int a5b_SeqFinish(uint8_t *item, int quiet)
{
    if (item == 0)
        return 0;
    if (quiet == 0)
        sub_001997E0(*(int32_t *)(item + 0x10), *(int32_t *)(item + 0x14));
    return sub_0005C430(item);
}

/* 0x0005D010: run 0x0005CD00 with a record's own +4/+8 fields. */
int a5b_SeqStartRec(int32_t *rec)
{
    return sub_0005CD00(rec, rec[1], rec[2]);
}

/* 0x0005D3E0: thiscall; value at +0xC0 of the +0x20 child when its kind is 1 or 9. */
int __fastcall a5b_ChildValueC0(uint8_t *self)
{
    uint8_t *c = *(uint8_t **)(self + 0x20);
    int kind;
    if (c == 0)
        return 0;
    kind = *(int32_t *)(c + 0x8C);
    switch (kind) {
    case 1:
    case 9:
        return *(int32_t *)(c + 0xC0);
    }
    return 0;
}
