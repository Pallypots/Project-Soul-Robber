/* Area m1, file 24: channel table sweeps (10 x 0x48 at 0x0042CB20). Names inferred. */
#include <stdint.h>

typedef struct M1Chan48 {
    uint8_t unk00[0x20];
    int32_t kind20;            /* +0x20, 0 ends the table */
    int32_t handle24;          /* +0x24 */
    uint8_t unk28[0x44 - 0x28];
    uint32_t flags44;          /* +0x44 bit 0 = paused */

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

M1Chan48 *sub_00037780(void);
void sub_001B9650(int h);
void sub_001B9FC0(int h);
void sub_00037AE0(void);
extern int32_t m1_chanG3DA2D8[5];   /* 0x003DA2D8 */

/* 0x00037BC0: stops every kind-1 channel's handle and unpauses it, clears the five
 * channel globals, runs 0x37AE0 and clears them again. */
void m1_ChanShutdown37BC0(void)
{
    M1Chan48 *c = sub_00037780();
    int i;
    for (i = 10; i != 0; i--, c++) {
        if (c->kind20 == 1) {
            if (c->handle24 > -1) {
                sub_001B9650(c->handle24);
                sub_001B9FC0(c->handle24);
            }
            c->flags44 &= ~1u;
        }
    }
    for (i = 0; i < 5; i++) {
        if (m1_chanG3DA2D8[i] != 0)
            m1_chanG3DA2D8[i] = 0;
    }
    sub_00037AE0();
    for (i = 0; i < 5; i++)
        m1_chanG3DA2D8[i] = 0;
}
