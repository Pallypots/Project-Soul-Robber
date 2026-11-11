/* Area r6g: pause page images (r6g_10). Names inferred. */
#include "r6g.h"

#define R6G_IMG(i) r6g_pauseImgs2DF168[i]

/* 0x0006E6B0: decode the images of pause page `page` (0..5) into the work block
   (0x00053E20 for the images loaded by name, 0x00053ED0 for the others). */
void r6g_PauseLoadImages(int page)
{
    switch (page) {
    case 0:
        sub_00053E20(R6G_IMG(0), a60_work42C5E8);
        sub_00053E20(R6G_IMG(1), a60_work42C5E8 + 0x40080);
        sub_00053ED0(R6G_IMG(2), a60_work42C5E8 + 0x40900);
        sub_00053ED0(R6G_IMG(3), a60_work42C5E8 + 0x50980);
        sub_00053ED0(R6G_IMG(4), a60_work42C5E8 + 0x60A00);
        sub_00053ED0(R6G_IMG(5), a60_work42C5E8 + 0x63A00);
        break;
    case 1:
        sub_00053ED0(R6G_IMG(22), a60_work42C5E8 + 0x65A00);
        sub_00053ED0(R6G_IMG(23), a60_work42C5E8 + 0x75A80);
        sub_00053ED0(R6G_IMG(24), a60_work42C5E8 + 0x85B00);
        sub_00053ED0(R6G_IMG(25), a60_work42C5E8 + 0x89B80);
        sub_00053ED0(R6G_IMG(26), a60_work42C5E8 + 0x8DC00);
        sub_00053ED0(R6G_IMG(27), a60_work42C5E8 + 0x90400);
        break;
    case 2:
        sub_00053ED0(R6G_IMG(6), a60_work42C5E8 + 0x65A00);
        sub_00053E20(R6G_IMG(7), a60_work42C5E8 + 0x85A80);
        sub_00053ED0(R6G_IMG(8), a60_work42C5E8 + 0x95B00);
        sub_00053ED0(R6G_IMG(15), a60_work42C5E8 + 0xB5B80);
        break;
    case 3:
        sub_00053ED0(R6G_IMG(16), a60_work42C5E8 + 0x65A00);
        sub_00053ED0(R6G_IMG(17), a60_work42C5E8 + 0x75A80);
        sub_00053E20(R6G_IMG(18), a60_work42C5E8 + 0x85B00);
        sub_00053ED0(R6G_IMG(19), a60_work42C5E8 + 0xA5B80);
        sub_00053ED0(R6G_IMG(20), a60_work42C5E8 + 0xA8380);
        sub_00053ED0(R6G_IMG(21), a60_work42C5E8 + 0xA8B80);
        break;
    case 4:
        sub_00053E20(R6G_IMG(28), a60_work42C5E8 + 0x65A00);
        sub_00053ED0(R6G_IMG(29), a60_work42C5E8 + 0x66A80);
        sub_00053ED0(R6G_IMG(30), a60_work42C5E8 + 0xA6B00);
        break;
    case 5:
        sub_00053ED0(R6G_IMG(31), a60_work42C5E8 + 0x65A00);
        break;
    }
}
