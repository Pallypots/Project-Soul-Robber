/* Area m1, file 26: lookups in the 16 x 0x54 table at 0x0041C7C0. Names inferred. */
#include <stdint.h>

typedef struct M1Mdl8 {
    uint8_t unk00[4];
    int32_t kind04;            /* +0x04 */
    int32_t sub08;             /* +0x08 */
} M1Mdl8;
typedef struct M1Ent54 {
    uint8_t flags00;           /* +0x00 bit 0 in use */
    uint8_t unk01[7];
    int32_t key08;             /* +0x08 */
    uint8_t unk0C[0x50 - 0xC];
    M1Mdl8 *mdl50;             /* +0x50 */
} M1Ent54;
extern M1Ent54 m1_ents41C7C0[16];  /* 0x0041C7C0 */
M1Mdl8 *sub_0001D290(M1Mdl8 *m, int i);

/* 0x000CDAB0: index of the in-use entry for (model, key), or -1. A kind-6 model
 * with no sub-model is first resolved through 0x1D290.
 * regargs: m=EAX key=ESI */
int m1_FindEntryCDAB0(M1Mdl8 *m, int key)
{
    int i;
    if (m->kind04 == 6 && m->sub08 == 0)
        m = sub_0001D290(m, 0);
    for (i = 0; i < 16; i++) {
        if ((m1_ents41C7C0[i].flags00 & 1) && m1_ents41C7C0[i].mdl50 == m && m1_ents41C7C0[i].key08 == key)
            return i;
    }
    return -1;
}
