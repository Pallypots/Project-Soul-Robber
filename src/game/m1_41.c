/* Area m1, file 41: model part visibility (kept apart so cl does not inline it). Names inferred. */
#include <stdint.h>

typedef struct M1Mdl8 {
    uint8_t unk00[4];
    int32_t kind04;            /* +0x04 */
    int32_t sub08;             /* +0x08 */
} M1Mdl8;

void sub_0001D4B0(M1Mdl8 *m, int part);   /* hide part */
void sub_0001D470(M1Mdl8 *m, int part);   /* show part */
int  sub_00172950(M1Mdl8 *m);

/* 0x000CE4C0: for a kind-6 / sub-model-1 model, hides parts 8..10 and 0..7, then
 * shows parts 8, 1, 10, 7 (or 9, 3, 5 when 0x172950 reports the alternate look).
 * regargs: m=ESI */
void m1_PartsLookCE4C0(M1Mdl8 *m)
{
    if (m == 0 || m->kind04 != 6 || m->sub08 != 1)
        return;
    sub_0001D4B0(m, 8);
    sub_0001D4B0(m, 9);
    sub_0001D4B0(m, 10);
    sub_0001D4B0(m, 0);
    sub_0001D4B0(m, 1);
    sub_0001D4B0(m, 2);
    sub_0001D4B0(m, 3);
    sub_0001D4B0(m, 4);
    sub_0001D4B0(m, 5);
    sub_0001D4B0(m, 6);
    sub_0001D4B0(m, 7);
    if (sub_00172950(m) == 0) {
        sub_0001D470(m, 8);
        sub_0001D470(m, 1);
        sub_0001D470(m, 10);
        sub_0001D470(m, 7);
        return;
    }
    sub_0001D470(m, 9);
    sub_0001D470(m, 3);
    sub_0001D470(m, 5);
}
