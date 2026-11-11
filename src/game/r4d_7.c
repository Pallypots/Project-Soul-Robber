/* Area r4d: sound driver helpers around 0x001AA970-0x001AB3C5 (r4d_7). Names inferred. */
#include "r4d.h"

/* 0x001AA970: unless the driver is in mode 1 or 2, post a kind-1 message carrying x. Stack arg (x). */
void r4d_DrvSetFade(int x)
{
    R4dDrvMsg m;
    if (r4d_drvMode40E348 == 1 || r4d_drvMode40E348 == 2)
        return;
    r4d_g40E6A8 = 1;
    m.kind = 1;
    r4d_g40E350 = x;
    m.x = x;
    m.f08 = r4d_g40E310;
    m.f0C = 0;
    sub_002226F3(r4d_drv40C868, &m, r4d_g40E300);
}

/* 0x001AB050: mark driver voice j for stopping with value x and record y, except for the
   protected ids 0x5A and 0x24E..0x259. Stack args (x j y). */
void r4d_DrvVoiceStop(int x, int j, int y)
{
    R4dDrvVoice *v = &r4d_drvVoices40CF50[j];
    int id = v->id00;
    if ((id <= 0x24D || id >= 0x25A) && id != 0x5A) {
        v->b2A = 1;
        v->f10 = x;
        r4d_g40E6AA = 1;
        r4d_g40E6AC = y;
        r4d_g40E6B0 = 0;
    }
}

/* 0x001AB370: release every driver object of group g (g < 45). Stack args (unused g). */
void r4d_DrvReleaseGroup(int unused, int g)
{
    void **p;
    int k;
    (void)unused;
    if (g >= 45)
        return;
    for (k = r4d_drvFirst27B6AC[g]; k < r4d_drvEnd27B6D4[g]; k++) {
        p = &r4d_drvObjs40E518[k];
        if (*p) {
            sub_002227C8(*p);
            sub_00222790(*p);
        }
        sub_0022239E(r4d_drvDev40E690, 2, p);
    }
}
