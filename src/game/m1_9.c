/* Area m1, file 9: scene render-buffer setup. Names inferred. */
#include "m1i.h"

/* 0x000C6920: create two render buffers (0x1F210(0xC,1) and 0x22260(3,1,0x10,0x10)),
 * keep each buffer and its data pointer, and attach the second to the scene root (0xD). */
void m1_SetupBufsC6920(void)
{
    R1cScene *sc = r1c_scene42C8E4;
    R1cRBuf *b;
    b = sub_0001F210(0xC, 1);
    m1_rbA41CEB8 = b;
    m1_rbAData41CEBC = b->data;
    sub_0001DA40(b);
    b = sub_00022260(3, 1, 0x10, 0x10);
    m1_rbB41CEB0 = b;
    m1_rbBData41D008 = b->data;
    sub_0001CFF0(sc->root, b, 0xD);
}

/* 0x000C7B00: same shape: buffer 0x1F210(1,0) loaded with chkaz00_pk.txt, and buffer
 * 0x22260(4,0,8,0) attached to the scene root (1). */
void m1_SetupBufsC7B00(void)
{
    R1cScene *sc = r1c_scene42C8E4;
    R1cRBuf *b;
    b = sub_0001F210(1, 0);
    m1_rbC41CFF8 = b;
    m1_rbCData41CFFC = b->data;
    sub_0001DA40(b);
    sub_00022630(m1_rbCData41CFFC, m1_strChkaz2770A8);
    b = sub_00022260(4, 0, 8, 0);
    m1_rbD41D000 = b;
    m1_rbDData41E290 = b->data;
    sub_0001CFF0(sc->root, b, 1);
}

/* 0x000C72C0: buffer 0x1F210(2,0) loaded with two model lists (the second into the
 * block at data+0x150), and 0x22260(0x14,0,8,0) attached to the scene root (1). */
void m1_SetupBufsC72C0(void)
{
    R1cScene *sc = r1c_scene42C8E4;
    R1cRBuf *b;
    b = sub_0001F210(2, 0);
    m1_rbE41D004 = b;
    m1_rbEData41CEB4 = b->data;
    sub_0001DA40(b);
    sub_00022630(m1_rbEData41CEB4, m1_strPk277078);
    sub_00022630(m1_rbEData41CEB4 + 0x150, m1_strPk277050);
    b = sub_00022260(0x14, 0, 8, 0);
    m1_rbF41E294 = b;
    m1_rbFData41E298 = b->data;
    sub_0001CFF0(sc->root, b, 1);
}
