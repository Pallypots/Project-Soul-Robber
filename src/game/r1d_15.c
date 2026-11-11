/* Area r1d, group 15: picture set-up and packet tags 0x00037F10..0x00038D30. Names inferred. */
#include "r1d.h"

/* 0x00037F10: load the (up to two) font pictures and the frame picture,
   relocate the frame animation bank and reset the text state. Returns 0. */
int r1d_PicInit(void)
{
    int i;
    a3c_g2C4460 = 0;
    r1d_tex3DA2EC[0] = -1;
    r1d_src3DA300[0] = 0;
    r1d_tex3DA2EC[1] = -1;
    r1d_src3DA300[1] = 0;
    r1d_tex3DA2EC[2] = -1;
    r1d_src3DA300[2] = 0;
    r1d_tex3DA2EC[3] = -1;
    r1d_src3DA300[3] = 0;
    for (i = 0; i < 2; i++) {
        r1d_src3DA300[i] = r1d_srcTbl2C3800[i];
        if (r1d_src3DA300[i] == 0) break;
        r1d_tex3DA2EC[i] = sub_00084C00(r1d_src3DA300[i], 0);
    }
    a3c_g3DA2FC = sub_00084C00(r1d_blob2C3810, 0);
    r1d_AnimBankFixup((R1dAnimBank *)a3c_obj2C4090);
    r1d_g3DA318 = 0;
    a3c_busy3DA310 = 0;
    a3c_g2C4464 = -1;
    r1c_paged3DA314 = a60_table266AD8;
    return 0;
}

/* 0x00038D30: close the packet under construction: write its DMA and
   GIF tags and the end tag. */
void r1d_PktClose(void)
{
    uint32_t *end = r1d_pkEnd3DA324;
    r1_pk3DA320[0] = (((uint32_t)((char *)end - (char *)r1_pk3DA320) >> 4) - 1) | 0x10000000;
    r1_pk3DA320[1] = 0;
    r1_pk3DA320[2] = 0;
    r1_pk3DA320[3] = (((uint32_t)((char *)end - (char *)r1_pk3DA320) >> 4) - 1) | 0x50000000;
    end[0] = 0x60000000;
    end[1] = 0;
    end[2] = 0;
    end[3] = 0;
}
