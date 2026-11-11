/* Area r4b: movie playback helpers around 0x001A7DC0-0x001A820A (r4b_11). Names inferred. */
#include "r4b.h"

/* 0x001A7DC0: advance the playing movie; returns 1 while a frame was produced. No inputs. */
int r4b_MovieUpdate(void)
{
    R4bBink *b;
    if (!a1a_b40B144)
        return 0;
    b = a1a_g40B148;
    if (b) {
        sub_0022E730(b);
        if (a1a_g40B148->frameNum == a1a_g40B148->frames && !sub_0019FFC0())
            return 0;
        sub_001BC6D0(&a1a_g40B150);
        sub_0022E980(a1a_g40B148);
        return 1;
    }
    r4b_VoiceSetFree(a1a_g40F124, &a1a_g40B150);
    a1a_b40B144 = 0;
    return 0;
}

/* 0x001A7E30: draw the movie frame full screen unless in mode 0x16; returns 0. No inputs. */
int r4b_MovieDraw(void)
{
    if (r4b_g40B140 != 0x16 && a1a_b40B144 && a1a_g40B148) {
        void *rt = sub_001D3A80(0);
        sub_001BC6C0();
        sub_001BC320(a1a_g40F124, &a1a_g40B150, a1a_g40B148->width, a1a_g40B148->height,
                     0, 0, 1.0f, 1.0f, r4b_g40B104 * (1.0f / 255.0f));
        sub_001D4350(0x40304, 1);
        aac_g1E243C = 1;
        sub_001D3AB0(0, rt);
        if (rt)
            sub_001D5F50(rt);
    }
    return 0;
}

/* 0x001A7EE0: draw the movie frame only in mode 0x16. No inputs. */
void r4b_MovieDrawMode16(void)
{
    if (r4b_g40B140 == 0x16 && a1a_b40B144 && a1a_g40B148) {
        void *rt = sub_001D3A80(0);
        sub_001BC6C0();
        sub_001BC320(a1a_g40F124, &a1a_g40B150, a1a_g40B148->width, a1a_g40B148->height,
                     0, 0, 1.0f, 1.0f, r4b_g40B104 * (1.0f / 255.0f));
        sub_001D4350(0x40304, 1);
        aac_g1E243C = 1;
        sub_001D3AB0(0, rt);
        if (rt)
            sub_001D5F50(rt);
    }
}

/* 0x001A8020: set the movie colour factors from 0..n levels (2n-1, negative gives 0). Stack args. */
void r4b_MovieSetColor(int r, int g, int b, int a)
{
    int k;
    r4b_g40B0FC = 255.0f;
    r4b_g40B100 = 255.0f;
    k = r * 2 - 1;
    if (k < 0) {
        r4b_g40B0F8 = 0.0f;
        return;
    }
    r4b_g40B0F8 = (float)k;
    k = g * 2 - 1;
    if (k < 0) {
        r4b_g40B0FC = 0.0f;
        return;
    }
    r4b_g40B0FC = (float)k;
    k = b * 2 - 1;
    if (k < 0) {
        r4b_g40B100 = 0.0f;
        return;
    }
    r4b_g40B100 = (float)k;
    k = a * 2 - 1;
    r4b_g40B104 = k < 0 ? 0.0f : (float)k;
}

/* 0x001A80D0: set the movie volume (0 mutes) on the four Bink tracks at 70 percent. Stack args. */
void r4b_MovieSetVolume(int vol)
{
    R4bBink *b = a1a_g40B148;
    int32_t chans[2];
    int32_t vols[2];
    int v;
    if (vol == 0 && b) {
        sub_0022E840(b, 0);
        return;
    }
    v = vol * 7 / 10;
    chans[0] = 0;
    chans[1] = 1;
    vols[0] = v;
    vols[1] = v;
    sub_0022E7E0(b, 0, chans, vols, 2);
    chans[0] = 2;
    vols[0] = v;
    sub_0022E7E0(a1a_g40B148, 1, chans, vols, 1);
    chans[0] = 3;
    vols[0] = v;
    sub_0022E7E0(a1a_g40B148, 2, chans, vols, 1);
    chans[0] = 4;
    chans[1] = 5;
    vols[0] = v;
    vols[1] = v;
    sub_0022E7E0(a1a_g40B148, 3, chans, vols, 2);
}

/* 0x001A81C0: turn "dev:path/x" into "d:\path\x" (nothing if src has no ':'). Stack args (dst src). */
void r4b_MakeDvdPath(char *dst, const char *src)
{
    char c;
    while (*src) {
        if (*src++ == ':') {
            *dst++ = 'd';
            *dst++ = ':';
            *dst++ = '\\';
            for (c = *src; c; c = *++src)
                *dst++ = (c == '/') ? '\\' : c;
            *dst = 0;
            return;
        }
    }
}
