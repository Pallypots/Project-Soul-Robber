/* Area a60, group 1: 0x00060000..0x00062FFF. Names inferred. */
#include "a60.h"

/* 0x00060980: create the resource at base + 0x49300. */
void a60_InitRes60980(void)
{
    a60_res3E64BC = sub_00084C00(a60_base3E60C8 + 0x49300, 0);
}

/* 0x00060BD0: -1 unless mode is 100, else whether the state is nonzero. */
int a60_IsActive(void)
{
    if (a60_mode3E64C0 != 100)
        return -1;
    return a60_state3E60D4 != 0;
}

/* 0x00062050: carve six consecutive slices of n ints from base. */
void a60_SetSlices(A60Slices *s, int32_t *base, int n)
{
    s->s[0] = base; base += n;
    s->s[1] = base; base += n;
    s->s[2] = base; base += n;
    s->s[3] = base; base += n;
    s->s[4] = base;
    s->s[5] = base + n;
}

/* 0x00060B70: open the menu in state 1 with value v. */
void a60_MenuOpen(int v)
{
    a60_v3E60F4 = v;
    a60_state3E60D4 = 1;
    a60_v3E60D8 = 0;
    a60_v3E60DC = 0;
    a60_v3E60E0 = 0;
    sub_00075F00(a60_menu3E60CC);
    sub_0003FAB0(a60_menu3E60CC->anim968, a60_menu3E60CC);
    sub_000603C0(v);
    a60_w3E60F8 = 0;
    a60_w3E60FA = 0;
}

/* 0x00062160: read two option flags and reset the screen's handles. */
void a60_ScreenInit62160(void)
{
    a60_b42A026 = 1;
    if (sub_000D9A70(0xF5)) a60_b42A026 |= 2;
    if (sub_000D9A70(0xF4)) a60_b42A026 |= 4;
    if ((a60_flags413428 & 0x83) != 0x83)
        a60_flags413428 |= 0x83;
    a60_hB3E64D0[0] = a60_hD3E64EC[0] = a60_hC3E64E0[0] = a60_hA3E64C4[0] = -1;
    a60_hB3E64D0[1] = a60_hD3E64EC[1] = a60_hC3E64E0[1] = a60_hA3E64C4[1] = -1;
    a60_hB3E64D0[2] = a60_hD3E64EC[2] = a60_hC3E64E0[2] = a60_hA3E64C4[2] = -1;
    a60_h3E64DC = -1;
}

/* 0x00062200: release the screen's handles. */
void a60_ScreenRelease62200(void)
{
    int i;
    for (i = 0; i < 3; i++) {
        if (a60_hA3E64C4[i] != -1) { sub_001B9FC0(a60_hA3E64C4[i]); a60_hA3E64C4[i] = -1; }
        if (a60_hC3E64E0[i] != -1) { sub_001B9FC0(a60_hC3E64E0[i]); a60_hC3E64E0[i] = -1; }
        if (a60_hD3E64EC[i] != -1) { sub_001B9FC0(a60_hD3E64EC[i]); a60_hD3E64EC[i] = -1; }
        if (a60_hB3E64D0[i] != -1) { sub_001B9FC0(a60_hB3E64D0[i]); a60_hB3E64D0[i] = -1; }
    }
    if (a60_h3E64DC != -1) { sub_001B9FC0(a60_h3E64DC); a60_h3E64DC = -1; }
}
