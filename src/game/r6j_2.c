/* Area r6j: shop list page draw (r6j_2). Names inferred. */
#include "r6j.h"

#define SPR_ROW   (&r6j_shopSpr3E6114[0])
#define SPR_UP    (&r6j_shopSpr3E6114[1])
#define SPR_DOWN  (&r6j_shopSpr3E6114[2])
#define SPR_TAG   (&r6j_shopSpr3E6114[3])
#define SPR_NAME  (&r6j_shopSpr3E6114[4])
#define SPR_HELP  (&r6j_shopSpr3E6114[5])

/* 0x00060BF0: draw the shop list page into the command buffer `cmd`:
   the scroll arrows (up when the list top is past 0, down when more items
   follow), three rows of item name, price tag and price (the cursor row
   bright, others dim; item 0x1C costs half while stat 0x29 is 0; prices
   shown at 60 percent while 0x00413178 is clear), then six help labels
   whose x position depends on the video mode. Returns the advanced
   command pointer. regargs: cmd=EAX. */
void *r6j_ShopListDraw(void *cmd)
{
    int i;
    uint32_t alpha;
    uint32_t col;
    int item;
    int price;
    void *p;
    float x;

    sub_000150B0(SPR_UP, 4);
    if (a60_w3E60FA > 0) {
        SPR_UP->x = -236.0f;
        SPR_UP->y = -110.0f;
        SPR_UP->color = ((uint32_t)r6i_alpha3E60FC << 24) + 0x808080;
        cmd = sub_00017C00(cmd, SPR_UP);
    }
    sub_000150B0(SPR_DOWN, 5);
    if (a60_w3E60FA + 2 < r6h_menuCount3E6112 - 1) {
        SPR_DOWN->x = -236.0f;
        SPR_DOWN->y = 80.0f;
        SPR_DOWN->color = ((uint32_t)r6i_alpha3E60FC << 24) + 0x808080;
        cmd = sub_00017C00(cmd, SPR_DOWN);
    }
    sub_00014E80(SPR_UP);
    sub_00014E80(SPR_DOWN);

    for (i = 0; i < 3; i++) {
        if (a60_w3E60FA + i >= r6h_menuCount3E6112)
            break;
        alpha = (uint32_t)r6i_alpha3E60FC << 24;
        col = (a60_w3E60F8 != i ? 0x404040 : 0x808080) + alpha;
        SPR_ROW->x = -90.0f;
        SPR_ROW->y = r6j_rowY2DDAF4[i];
        SPR_ROW->color = col;
        sub_000150B0(SPR_ROW, (a60_w3E60FA + i) % 3 + 1);
        p = sub_00017C00(cmd, SPR_ROW);

        item = r6h_menuItems3E6104[a60_w3E60FA + i];
        SPR_NAME->x = SPR_ROW->x - 93.0f;
        SPR_NAME->y = SPR_ROW->y - 1.0f;
        SPR_NAME->color = col;
        sub_000150B0(SPR_NAME, item);
        p = sub_00017C00(p, SPR_NAME);

        SPR_TAG->x = SPR_ROW->x;
        SPR_TAG->y = SPR_ROW->y;
        SPR_TAG->color = (a60_w3E60F8 != i ? 0x262B2B : 0x3B6F86) + ((uint32_t)r6i_alpha3E60FC << 24);
        sub_000150B0(SPR_TAG, r6j_itemTag2DD9EC[item]);
        p = sub_00017C00(p, SPR_TAG);

        if (item == 0x1C) {
            price = r6d_prices[0x1C];
            if (Stats_Get(&g_stats, 0x29) == 0)
                price /= 2;
        } else {
            price = r6d_prices[item];
        }
        if (r6i_g413178 == 0)
            price = price * 60 / 100;
        cmd = sub_0002B950(p, SPR_ROW->x + 88.0f, SPR_ROW->y + 12.0f,
                           (a60_w3E60F8 != i ? 0x161B1B : 0x23576E) + ((uint32_t)r6i_alpha3E60FC << 24),
                           price);
    }

    x = SPR_HELP->x;
    switch (sub_000529F0()) {
    case 0: x = 35.0f; break;
    case 1:
    case 2: x = -16.0f; break;
    case 3: x = -66.0f; break;
    case 4: x = -37.0f; break;
    case 5: x = -46.0f; break;
    case 6: x = -70.0f; break;
    }
    SPR_HELP->x = x;
    SPR_HELP->y = 196.0f;
    SPR_HELP->color = ((uint32_t)r6i_alpha3E60FC << 24) + 0x808080;
    sub_000150B0(SPR_HELP, 3);
    cmd = r1d_TrackApplyD(cmd, SPR_HELP);

    x = SPR_HELP->x;
    switch (sub_000529F0()) {
    case 0: x = 114.0f; break;
    case 1:
    case 2: x = 59.0f; break;
    case 3: x = 9.0f; break;
    case 4: x = 38.0f; break;
    case 5: x = 29.0f; break;
    case 6: x = 5.0f; break;
    }
    SPR_HELP->x = x;
    sub_000150B0(SPR_HELP, 8);
    cmd = r1d_TrackApplyD(cmd, SPR_HELP);

    x = SPR_HELP->x;
    switch (sub_000529F0()) {
    case 0: x = 114.0f; break;
    case 1:
    case 2: x = 101.0f; break;
    case 3: x = 44.0f; break;
    case 4: x = 73.0f; break;
    case 5: x = 78.0f; break;
    case 6: x = 55.0f; break;
    }
    SPR_HELP->x = x;
    SPR_HELP->y = 196.0f;
    SPR_HELP->color = ((uint32_t)r6i_alpha3E60FC << 24) + 0x808080;
    sub_000150B0(SPR_HELP, 1);
    cmd = r1d_TrackApplyD(cmd, SPR_HELP);

    x = SPR_HELP->x;
    switch (sub_000529F0()) {
    case 0: x = 193.0f; break;
    case 1:
    case 2: x = 176.0f; break;
    case 3: x = 119.0f; break;
    case 4: x = 148.0f; break;
    case 5: x = 153.0f; break;
    case 6: x = 130.0f; break;
    }
    SPR_HELP->x = x;
    sub_000150B0(SPR_HELP, 11);
    cmd = r1d_TrackApplyD(cmd, SPR_HELP);

    x = SPR_HELP->x;
    switch (sub_000529F0()) {
    case 0:
    case 5: x = 188.0f; break;
    case 1:
    case 2: x = 178.0f; break;
    case 3: x = 163.0f; break;
    case 4: x = 180.0f; break;
    case 6: x = 176.0f; break;
    }
    SPR_HELP->x = x;
    SPR_HELP->y = 196.0f;
    SPR_HELP->color = ((uint32_t)r6i_alpha3E60FC << 24) + 0x808080;
    sub_000150B0(SPR_HELP, 0);
    cmd = r1d_TrackApplyD(cmd, SPR_HELP);

    x = SPR_HELP->x;
    switch (sub_000529F0()) {
    case 0: x = 267.0f; break;
    case 1:
    case 2: x = 253.0f; break;
    case 3: x = 238.0f; break;
    case 4: x = 255.0f; break;
    case 5: x = 263.0f; break;
    case 6: x = 251.0f; break;
    }
    SPR_HELP->x = x;
    sub_000150B0(SPR_HELP, 9);
    return r1d_TrackApplyD(cmd, SPR_HELP);
}
