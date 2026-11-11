/* Area r1h, group 12: 2D animation set loader 0x00059020. Names inferred. */
#include "r1h.h"

/* 0x00059020: create the textures and animation records of one 2D set
   from the loaded data file r1h_pak3E474C. Kind 0 builds record 0 and
   copies it to records 1 and 2; kind 1 rebuilds record 3, copies it to
   record 4 and selects the language entry; kind 2 rebuilds record 5.
   Old textures are released first. regargs: kind=EAX. */
void r1h_AnimSetLoad(int kind)
{
    switch (kind) {
    case 0:
        r1h_tex3E4B30[0] = sub_00084C00(r1h_pak3E474C, 0);
        r1h_tex3E4B30[1] = sub_00084C00(r1h_pak3E474C + 0x10100, 0);
        sub_00014DA0(r1h_pak3E474C + 0x18580);
        sub_00014D00(&r1h_anim3E4774[0], r1h_pak3E474C + 0x18580, r1h_tex3E4B30[0]);
        r1h_anim3E4774[0].tex[0] = r1h_tex3E4B30[1];
        sub_00014E30(&r1h_anim3E4774[0], 0, 0, 0, 0);
        r1h_anim3E4774[0].flags |= 4;
        r1h_anim3E4774[1] = r1h_anim3E4774[0];
        r1h_anim3E4774[2] = r1h_anim3E4774[0];
        break;
    case 1:
        if (r1h_tex3E4B20[0] != -1) {
            sub_001B9FC0(r1h_tex3E4B20[0]);
            r1h_tex3E4B20[0] = -1;
        }
        if (r1h_tex3E4B20[1] != -1) {
            sub_001B9FC0(r1h_tex3E4B20[1]);
            r1h_tex3E4B20[1] = -1;
        }
        r1h_tex3E4B20[0] = sub_00084C00(r1h_pak3E474C + 0x21580, 0);
        r1h_tex3E4B20[1] = sub_00084C00(r1h_pak3E474C + 0x31680, 0);
        sub_00014DA0(r1h_pak3E474C + 0x51780);
        sub_00014D00(&r1h_anim3E4774[3], r1h_pak3E474C + 0x51780, r1h_tex3E4B20[0]);
        r1h_anim3E4774[3].tex[0] = r1h_tex3E4B20[1];
        sub_00014E30(&r1h_anim3E4774[3], 0, 0, 0, 0);
        r1h_anim3E4774[4] = r1h_anim3E4774[3];
        r1h_g3E4764 = 0;
        r1h_lang413145 = r1h_langTbl2DD1C8[r1h_lang3E4760].v;
        sub_00052A00(r1h_lang413145);
        break;
    case 2:
        if (r1h_tex3E4740[0] != -1) {
            sub_001B9FC0(r1h_tex3E4740[0]);
            r1h_tex3E4740[0] = -1;
        }
        if (r1h_tex3E4740[1] != -1) {
            sub_001B9FC0(r1h_tex3E4740[1]);
            r1h_tex3E4740[1] = -1;
        }
        if (r1h_tex3E4740[2] != -1) {
            sub_001B9FC0(r1h_tex3E4740[2]);
            r1h_tex3E4740[2] = -1;
        }
        r1h_tex3E4740[0] = sub_00084C00(r1h_pak3E474C + 0x53780, 0);
        r1h_tex3E4740[1] = sub_00084C00(r1h_pak3E474C + 0x9BD00, 0);
        r1h_tex3E4740[2] = sub_00084C00(r1h_pak3E474C + 0x5B880, 0);
        sub_00014DA0(r1h_pak3E474C + 0xA3E00);
        sub_00014D00(&r1h_anim3E4774[5], r1h_pak3E474C + 0xA3E00, r1h_tex3E4740[1]);
        r1h_anim3E4774[5].tex[0] = r1h_tex3E4740[0];
        sub_00014E30(&r1h_anim3E4774[5], 0, 0, 0, 0);
        break;
    }
}
