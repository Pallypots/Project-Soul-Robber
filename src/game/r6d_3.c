/* Area r6d: shop menu helpers around 0x00060900-0x00061C30 (r6d_3). Names inferred. */
#include "r6d.h"

/* 0x00060900: show a new message in the menu text box. */
void r6d_MenuShowText(int id)
{
    sub_00018620(a60_menu3E60CC->anim968, r6d_menuAnim2DDB00);
    a60_TextClear(a60_menu3E60CC->text970);
    sub_0003FCB0(a60_menu3E60CC->anim968, sub_0003FA70(a60_menu3E60CC->anim988, id, 0, 0, -1.0f));
    a60_FlagsClear(a60_menu3E60CC->text970, 0x80);
}

/* 0x000609A0: give the player one bought shop item.
   regargs: id=AX (zero-extended) */
void r6d_ShopGive(uint16_t id)
{
    switch (id) {
    case 1:
        sub_000D1E10(&g_stats, id + 13, 1);
        sub_000D9AB0(0x37F);
        break;
    case 3:
        sub_000D1E10(&g_stats, id + 13, 1);
        break;
    case 28:
        sub_000D1E10(&g_stats, id + 13, 1);
        sub_00023D80(4, 0);
        sub_000D1E10(&g_stats, 0, 2);
        break;
    case 47:
        sub_000D1E10(&g_stats, id + 13, 1);
        sub_000D9AB0(0x0D);
        break;
    case 23:
        sub_000D1E10(&g_stats, id + 13, 10);
        break;
    case 5: case 6: case 7:
        sub_000D1E10(&g_stats, 4, 1);
        break;
    case 8: case 9: case 10:
        sub_000D1E10(&g_stats, 6, 1);
        break;
    case 11: case 12: case 13:
        sub_000D1E10(&g_stats, 8, 1);
        break;
    case 14: case 15: case 16:
        sub_000D1E10(&g_stats, 9, 1);
        break;
    case 17: case 18: case 19:
        sub_000D1E10(&g_stats, 10, 1);
        break;
    case 20: case 21: case 22:
        sub_000D1E10(&g_stats, 11, 1);
        break;
    }
}

/* 0x00061500: why an item cannot be bought: 1 = too expensive, 2 = not for sale
   or already full, 0 = can buy.
   regargs: id=SI (zero-extended) */
int r6d_ShopCheck(uint16_t id)
{
    int money = Stats_Get(&g_stats, 0x0C);
    int have;
    int r;
    if (r6d_ItemPrice(id) > money)
        return 1;
    have = Stats_Get(&g_stats, id + 13);
    r = 2;
    switch (id) {
    case 1:
        if (!sub_000D9A70(0x37F))
            return 0;
        break;
    case 28:
        if (have < Stats_GetMax(id) && Stats_Get(&g_stats, 0) < 30)
            r = 0;
        break;
    case 3: case 23: case 47:
        if (have < Stats_GetMax(id))
            r = 0;
        break;
    case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13:
    case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22:
        r = 0;
        break;
    }
    return r;
}

/* 0x00061B70: translate a menu value for the current shop page and show it.
   calls 0x00060BF0 with EAX=v */
int r6d_MenuPageValue(int v)
{
    if (a60_mode3E64C0 != 100)
        return v;
    switch (a60_state3E60D4) {
    case 2:
        v = sub_00060BF0(v);
        break;
    case 3:
        v = sub_0005FFB0(v);
        break;
    default:
        return v;
    }
    return sub_0003FBD0(v, a60_menu3E60CC->anim968);
}

/* 0x00061BC0: run the current shop page and update the menu animation. */
void r6d_MenuUpdate(void)
{
    switch (a60_state3E60D4) {
    case 1:
        sub_000601E0();
        break;
    case 2:
        sub_000615F0();
        break;
    case 3:
        sub_00061290();
        break;
    case 4:
        sub_00060300();
        break;
    default:
        return;
    }
    sub_0003FCE0(a60_menu3E60CC->anim968);
}
