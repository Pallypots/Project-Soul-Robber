/* Area m1, file 24: channel table sweeps (10 x 0x48 at 0x0042CB20). Names inferred. */
#include <stdint.h>

typedef struct M1Chan48 {
    uint8_t unk00[0x20];
    int32_t kind20;            /* +0x20, 0 ends the table */
    uint8_t unk24[0x44 - 0x24];
    uint8_t flags44;           /* +0x44 bit 0 = paused */
    uint8_t unk45[0x48 - 0x45];
} M1Chan48;
extern M1Chan48 m1_chans42CB20[10];  /* 0x0042CB20 */
void sub_00037830(M1Chan48 *c);          /* regargs: c=EAX */

/* 0x00037AF0: updates every active kind-1 channel (stops at the first empty one). */
void m1_ChanUpdate37AF0(void)
{
    int i;
    M1Chan48 *c = m1_chans42CB20;
    for (i = 0; i < 10; i++, c++) {
        if (c->kind20 == 0)
            return;
        if (!(c->flags44 & 1) && c->kind20 == 1)
            sub_00037830(c);
    }
}


void sub_00037910(M1Chan48 *c, int a);   /* regargs: c=ESI */
void sub_00037790(M1Chan48 *c, int a);   /* regargs: c=ESI */

/* 0x00037B20: passes a to every active channel: kind 1 -> 0x37910, kind 2 -> 0x37790. */
void m1_ChanApply37B20(int a)
{
    int i;
    M1Chan48 *c = m1_chans42CB20;
    for (i = 0; i < 10; i++, c++) {
        if (c->kind20 == 0)
            return;
        if (!(c->flags44 & 1)) {
            switch (c->kind20) {
            case 1:
                sub_00037910(c, a);
                break;
            case 2:
                sub_00037790(c, a);
                break;
            }
        }
    }
}
