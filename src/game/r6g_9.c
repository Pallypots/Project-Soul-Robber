/* Area r6g: menu page images (r6g_9). Names inferred. */
#include "r6g.h"

/* 0x00064CE0: decode the images of menu page `page` into the work block; pages
   1..3 flip the double-buffer half and decode the images of the selected item
   (r6g_menuItem42A018) into that half. */
void r6g_MenuLoadImages(int page)
{
    switch (page) {
    case 0:
        sub_00053ED0(r6g_menuImgs2DDB08.top[0], a60_work42C5E8 + 0x40080);
        sub_00053ED0(r6g_menuImgs2DDB08.top[1], a60_work42C5E8 + 0x50100);
        sub_00053ED0(r6g_menuImgs2DDB08.top[2], a60_work42C5E8 + 0x60180);
        sub_00053ED0(r6g_menuImgs2DDB08.top[3], a60_work42C5E8 + 0x80200);
        sub_00053ED0(r6g_menuImgs2DDB08.top[4], a60_work42C5E8 + 0x81200);
        break;
    case 1:
        r6g_menuBuf42A028 = 1 - r6g_menuBuf42A028;
        sub_00053ED0(r6g_menuImgs2DDB08.bg1[0], a60_work42C5E8 + 0x83200);
        sub_00053ED0(r6g_menuImgs2DDB08.bg1[1], a60_work42C5E8 + 0xA3280);
        sub_00053E20(r6g_menuImgs2DDB08.name1[r6g_menuItem42A018],
                     a60_work42C5E8 + r6g_menuBuf42A028 * 0x10080 + 0xA7300);
        sub_00053ED0(r6g_menuImgs2DDB08.pic1[r6g_menuItem42A018],
                     a60_work42C5E8 + r6g_menuBuf42A028 * 0x10080 + 0xC7400);
        sub_00053ED0(r6g_menuImgs2DDB08.fg1[0], a60_work42C5E8 + 0xE7500);
        sub_00053ED0(r6g_menuImgs2DDB08.fg1[1], a60_work42C5E8 + 0xEB500);
        break;
    case 2:
        r6g_menuBuf42A028 = 1 - r6g_menuBuf42A028;
        sub_00053ED0(r6g_menuImgs2DDB08.bg2, a60_work42C5E8 + 0x83200);
        sub_00053E20(r6g_menuImgs2DDB08.name2[r6g_menuItem42A018],
                     a60_work42C5E8 + r6g_menuBuf42A028 * 0x10080 + 0x93280);
        sub_00053ED0(r6g_menuImgs2DDB08.pic2[r6g_menuItem42A018],
                     a60_work42C5E8 + r6g_menuBuf42A028 * 0x10080 + 0xB3380);
        sub_00053ED0(r6g_menuImgs2DDB08.fg2[0], a60_work42C5E8 + 0xD3480);
        sub_00053ED0(r6g_menuImgs2DDB08.fg2[1], a60_work42C5E8 + 0xD4C80);
        break;
    case 3:
        r6g_menuBuf42A028 = 1 - r6g_menuBuf42A028;
        sub_00053ED0(r6g_menuImgs2DDB08.bg3, a60_work42C5E8 + 0x83200);
        sub_00053E20(r6g_menuImgs2DDB08.name3[r6g_menuItem42A018],
                     a60_work42C5E8 + r6g_menuBuf42A028 * 0x10080 + 0x93280);
        sub_00053ED0(r6g_menuImgs2DDB08.pic3[r6g_menuItem42A018],
                     a60_work42C5E8 + r6g_menuBuf42A028 * 0x10080 + 0xB3380);
        sub_00053ED0(r6g_menuImgs2DDB08.fg3[0], a60_work42C5E8 + 0xD3480);
        sub_00053ED0(r6g_menuImgs2DDB08.fg3[1], a60_work42C5E8 + 0xD4C80);
        break;
    }
}

/* 0x000646E0: build the textures and sprites of the menu page selected by
   r6g_b428F80[1] from the images decoded by 0x00064CE0 (sprites 1, 3 and 5 are
   copies of 0, 2 and 4); pages 1..3 first release sprite 2. */
void r6g_MenuBuildSprites(void)
{
    sub_001B9720();
    switch (r6g_b428F80[1]) {
    case 0:
        a60_hA3E64C4[0] = sub_00084C00(a60_work42C5E8 + 0x40080, 0);
        a60_hA3E64C4[1] = sub_00084C00(a60_work42C5E8 + 0x50100, 0);
        a60_hA3E64C4[2] = sub_00084C00(a60_work42C5E8 + 0x60180, 0);
        sub_00014DA0(a60_work42C5E8 + 0x80200);
        sub_00014D00(&r6g_menuSpr42A3D4[0], a60_work42C5E8 + 0x80200, a60_hA3E64C4[0]);
        r6g_menuSpr42A3D4[0].tex[0] = a60_hA3E64C4[2];
        sub_00014E30(&r6g_menuSpr42A3D4[0], 0, 0, 0, 0);
        r6g_menuSpr42A3D4[1] = r6g_menuSpr42A3D4[0];
        sub_00014DA0(a60_work42C5E8 + 0x81200);
        sub_00014D00(&r6g_menuSpr42A3D4[2], a60_work42C5E8 + 0x81200, a60_hA3E64C4[1]);
        sub_00014E30(&r6g_menuSpr42A3D4[2], 0, 0, 0, 0);
        r6g_menuSpr42A3D4[3] = r6g_menuSpr42A3D4[2];
        return;
    case 1:
        sub_00015070(&r6g_menuSpr42A3D4[2]);
        a60_hB3E64D0[0] = sub_00084C00(a60_work42C5E8 + 0x83200, 0);
        a60_hB3E64D0[1] = sub_00084C00(a60_work42C5E8 + r6g_menuBuf42A028 * 0x10080 + 0xA7300, 0);
        a60_hB3E64D0[2] = sub_00084C00(a60_work42C5E8 + r6g_menuBuf42A028 * 0x10080 + 0xC7400, 0);
        a60_h3E64DC = sub_00084C00(a60_work42C5E8 + 0xA3280, 0);
        sub_00014DA0(a60_work42C5E8 + 0xE7500);
        sub_00014DA0(a60_work42C5E8 + 0xEB500);
        sub_00014D00(&r6g_menuSpr42A3D4[4], a60_work42C5E8 + 0xE7500, a60_hB3E64D0[0]);
        r6g_menuSpr42A3D4[4].tex[0] = a60_h3E64DC;
        sub_00014E30(&r6g_menuSpr42A3D4[4], 0, 0, 0, 0);
        r6g_menuSpr42A3D4[5] = r6g_menuSpr42A3D4[4];
        sub_00014D00(&r6g_menuSpr42A3D4[6], a60_work42C5E8 + 0xEB500, a60_hB3E64D0[1]);
        r6g_menuSpr42A3D4[6].tex[0] = a60_hB3E64D0[2];
        break;
    case 2:
        sub_00015070(&r6g_menuSpr42A3D4[2]);
        a60_hD3E64EC[0] = sub_00084C00(a60_work42C5E8 + 0x83200, 0);
        a60_hD3E64EC[1] = sub_00084C00(a60_work42C5E8 + r6g_menuBuf42A028 * 0x10080 + 0x93280, 0);
        a60_hD3E64EC[2] = sub_00084C00(a60_work42C5E8 + r6g_menuBuf42A028 * 0x10080 + 0xB3380, 0);
        sub_00014DA0(a60_work42C5E8 + 0xD3480);
        sub_00014DA0(a60_work42C5E8 + 0xD4C80);
        sub_00014D00(&r6g_menuSpr42A3D4[4], a60_work42C5E8 + 0xD3480, a60_hD3E64EC[0]);
        sub_00014E30(&r6g_menuSpr42A3D4[4], 0, 0, 0, 0);
        r6g_menuSpr42A3D4[5] = r6g_menuSpr42A3D4[4];
        sub_00014D00(&r6g_menuSpr42A3D4[6], a60_work42C5E8 + 0xD4C80, a60_hD3E64EC[1]);
        r6g_menuSpr42A3D4[6].tex[0] = a60_hD3E64EC[2];
        break;
    case 3:
        sub_00015070(&r6g_menuSpr42A3D4[2]);
        a60_hC3E64E0[0] = sub_00084C00(a60_work42C5E8 + 0x83200, 0);
        a60_hC3E64E0[1] = sub_00084C00(a60_work42C5E8 + r6g_menuBuf42A028 * 0x10080 + 0x93280, 0);
        a60_hC3E64E0[2] = sub_00084C00(a60_work42C5E8 + r6g_menuBuf42A028 * 0x10080 + 0xB3380, 0);
        sub_00014DA0(a60_work42C5E8 + 0xD3480);
        sub_00014DA0(a60_work42C5E8 + 0xD4C80);
        sub_00014D00(&r6g_menuSpr42A3D4[4], a60_work42C5E8 + 0xD3480, a60_hC3E64E0[0]);
        sub_00014E30(&r6g_menuSpr42A3D4[4], 0, 0, 0, 0);
        r6g_menuSpr42A3D4[5] = r6g_menuSpr42A3D4[4];
        sub_00014D00(&r6g_menuSpr42A3D4[6], a60_work42C5E8 + 0xD4C80, a60_hC3E64E0[1]);
        r6g_menuSpr42A3D4[6].tex[0] = a60_hC3E64E0[2];
        break;
    default:
        return;
    }
    sub_00014E30(&r6g_menuSpr42A3D4[6], 0, 0, 0, 0);
}
