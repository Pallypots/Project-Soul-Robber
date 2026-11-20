/* Area m1, file 267: bounds and scans. Names inferred. */
#include <stdint.h>

typedef int (*M1Filt267)(int a, int b);
typedef struct M1Ent267 { uint8_t unk00[4]; int32_t x4; int32_t x8; uint8_t bC; } M1Ent267;
typedef struct M1Nd2_267 { struct M1Nd2_267 *next0; uint8_t unk04[8]; M1Ent267 *xC; } M1Nd2_267;
typedef struct M1Lk267 { uint8_t unk00[0x24]; int (*ready24)(M1Ent267 *e); } M1Lk267;
extern M1Filt267 m1_filtTbl3189C0[3];
extern M1Filt267 m1_filtFn3189CC;
extern M1Nd2_267 *m1_filtList3F5DC4;
extern M1Nd2_267 *m1_filtNext3F60E4;
void sub_00033B30(M1Ent267 *e);
M1Lk267 *sub_0001D960(M1Ent267 *e, int32_t kind);
void sub_000ED380(M1Ent267 *e);                              /* regargs: e=EAX */
void sub_0001EB80(M1Ent267 *e);
void sub_000362B0(M1Ent267 *e);
void sub_0001D190(M1Ent267 *e);
void sub_0001B3F0(M1Ent267 *e);

/* 0x000EE0C0: for every entity passing filter 0: update it, and if it is active and its kind-13 link says it
   is ready, retire it (clear its active bit and free its parts). */
void m1_RetireReadyEE0C0(void)
{
    M1Nd2_267 *n;
    M1Ent267 *e;
    M1Lk267 *l;
    *(M1Filt267 volatile *)&m1_filtFn3189CC = m1_filtTbl3189C0[0];
    for (n = m1_filtList3F5DC4; n; n = n->next0)
        if (m1_filtFn3189CC(n->xC->x4, n->xC->x8)) break;
    if (!n) {
        m1_filtNext3F60E4 = 0;
        return;
    }
    m1_filtNext3F60E4 = n->next0;
    e = n->xC;
    while (e) {
        sub_00033B30(e);
        if (e->bC & 1) {
            l = sub_0001D960(e, 0xD);
            if (l && l->ready24(e)) {
                sub_000ED380(e);
                *(uint32_t *)&e->bC &= ~1u;
                sub_0001EB80(e);
                sub_000362B0(e);
                sub_0001D190(e);
                sub_0001B3F0(e);
            }
        }
        for (n = m1_filtNext3F60E4; n; n = n->next0)
            if (m1_filtFn3189CC(n->xC->x4, n->xC->x8)) break;
        if (!n) {
            m1_filtNext3F60E4 = n;
            return;
        }
        m1_filtNext3F60E4 = n->next0;
        e = n->xC;
    }
}
