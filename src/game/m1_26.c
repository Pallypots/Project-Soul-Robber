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

typedef struct M1Ent54U {
    uint32_t flags00;          /* +0x00 bit 0 in use, bit 1 hold */
    uint8_t  unk04[4];
    int32_t  key08;            /* +0x08 */
    int32_t  step0C;           /* +0x0C */
    uint8_t  unk10[0x50 - 0x10];
    M1Mdl8  *mdl50;            /* +0x50 */
} M1Ent54U;
extern M1Ent54U m1_ents41C7C0U[16];  /* 0x0041C7C0 (same table, update view) */
void sub_000CE680(M1Ent54U *e);  /* regargs: e=ESI */
void sub_000CE750(M1Ent54U *e);  /* regargs: e=EDI */
void sub_000CE020(M1Ent54U *e);  /* regargs: e=EAX */
void sub_000CE1C0(M1Ent54U *e);  /* regargs: e=ESI */

/* 0x000CF000: per-frame update of every in-use entry: held entries reset their
 * step; entries on a kind-6/1 model use 0xCE680/0xCE750, others 0xCE020/0xCE1C0
 * (first of each pair when key is 0). */
void m1_UpdateEntriesCF000(void)
{
    int i;
    for (i = 0; i < 16; i++) {
        M1Ent54U *e = &m1_ents41C7C0U[i];
        if (!(e->flags00 & 1))
            continue;
        if (e->flags00 & 2) {
            e->step0C = 0;
            continue;
        }
        if (e->mdl50->kind04 == 6 && e->mdl50->sub08 == 1) {
            if (e->key08 == 0)
                sub_000CE680(e);
            else
                sub_000CE750(e);
        } else if (e->key08 == 0)
            sub_000CE020(e);
        else
            sub_000CE1C0(e);
    }
}
