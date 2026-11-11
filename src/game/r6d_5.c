/* Area r6d: pause/status screen helpers around 0x00065AE0-0x00065ED8 (r6d_5). Names inferred. */
#include "r6d.h"

/* 0x00065AE0: select a texture set (ids 0x38.. with 0x3D folded) and load its images
   into the work block. */
void r6d_LoadTexSet(int id)
{
    int n = id - 0x38;
    int i;
    if ((unsigned)n > 4)
        n--;
    r6d_texSet3E6538 = n;
    for (i = 0; i < 4; i++)
        if (r6d_texSets[n].big[i])
            sub_00053ED0(*r6d_texSets[n].big[i], a60_work42C5E8 + 0x40080 + i * 0x20080);
    for (i = 0; i < 3; i++)
        if (r6d_texSets[n].small[i])
            sub_00053ED0(*r6d_texSets[n].small[i], a60_work42C5E8 + 0xC0280 + i * 0x2800);
}

/* 0x00065DB0: icon index for entry k of the current status page.
   regargs: k=EDX */
int r6d_StatusIcon(int k)
{
    int m;
    switch (a60_phase428F81) {
    case 0:
        if (k == 12 || k == 13)
            return 3;
        if (k == 14)
            return 0x1D;
        k = r6d_iconSlot26DC68[k];
        if (k == -1)
            return 0;
        return r6d_icons42970C[k];
    case 1:
        if (k == 0) {
            m = r6d_g428F8C;
            if (m == 12 || m == 13)
                return 3;
            if (m == 14)
                return 0x1D;
            return r6d_icons42970C[r6d_iconSlot26DC68[m]];
        }
        return r6d_iconRows429718[r6d_g429708][r6d_g428F90];
    case 4:
        if (k == 0x13)
            return 0;
        return r6d_iconRows429718[r6d_g429708][k];
    }
    return 0;
}

/* 0x00065E50: show message `id` in status text box i (box 1 also clears flag 0x80).
   regargs: i=ESI */
void r6d_StatusShowText(int i, int id)
{
    sub_00018620(R6D_WORK->anim, r6d_statusAnims2DE3CC[i]);
    a60_TextClear(R6D_WORK->text);
    sub_0003FCB0(R6D_WORK->anim, sub_0003FA70(R6D_WORK->msgTables[i], id), 0, 0, -1.0f);
    if (i == 1)
        a60_FlagsClear(R6D_WORK->text, 0x80);
}
