/* Area m1, file 129: small helpers. Names inferred. */
#include <stdint.h>

extern int32_t m1_vol3DFED0;
extern int32_t m1_track3DFECC;
extern int32_t m1_mode3DFEC0;
void sub_00199800(int v);
void sub_00199830(int v);
int  sub_00199880(int ch);
int  sub_00199AE0(int ch);
void sub_00199A90(int ch, int v);
int  sub_0019A810(int t);
int  sub_0019A930(int t);
int  sub_0019ADE0(int m);
int  sub_0019ACE0(int t, int i);
void sub_0019AC20(int t, int i, int v);

/* 0x00048620: set the music volume (capped at 0x3FFF): apply it, refresh the 16 channels, and
 * re-apply every part of the current track by mode. */
void m1_MusicVolume048620(int n)
{
    int i, k, r;
    if (n > 0x3FFF)
        n = 0x3FFF;
    m1_vol3DFED0 = n;
    sub_00199800(n);
    sub_00199830(m1_vol3DFED0);
    for (i = 0; i < 0x10; i++)
        if (sub_00199880(i))
            sub_00199A90(i, sub_00199AE0(i));
    if (m1_track3DFECC < 0)
        return;
    if (m1_mode3DFEC0 < 2)
        r = sub_00199880(m1_track3DFECC);
    else if (m1_mode3DFEC0 < 3)
        r = sub_0019A810(m1_track3DFECC);
    else
        r = sub_0019A930(m1_track3DFECC);
    if (r <= 0)
        return;
    k = sub_0019ADE0(m1_mode3DFEC0 - 3);
    for (i = 0; i < k; i++)
        sub_0019AC20(m1_track3DFECC, i, sub_0019ACE0(m1_track3DFECC, i));
}
