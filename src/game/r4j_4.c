/* Area r4j: texture bind (0x001A6820). Names inferred. */
#include "r4j.h"

/* 0x001A6820: bind a texture entry to stage 0 unless it has no device
   texture or is already bound: under the render lock set the texture,
   linear filtering, mip bias -1, the default alpha test/blend states and the
   U/V address modes from bits 0-1 / 2-3 of wrap48 (1 or 2 = clamp (3),
   0 or 3 = wrap (1)). Stack arg (e). 0x001D4350 is fastcall (ECX EDX). */
void r4j_TexBind(R4jTexBind *e)
{
    void *tex = e->tex54;

    if (tex == 0 || r4j_curTex40B0E8 == e)
        return;
    r4j_curTex40B0E8 = e;
    RtlEnterCriticalSection(g_renderLock);
    r4f_SetTexture1D3AB0(0, tex);
    a1a_g1E2148 |= 1;
    r4f_tss1E2160 = 2;
    r4f_tss1E215C = 2;
    (void)*(R4jTexHdr *volatile *)&e->hdr14;   /* the original loads hdr14 here and never uses it */
    a1a_g1E2148 |= 1;
    r4j_tss1E2164 = 2;
    r4j_tss1E2188 = 2;
    a1a_g1E2148 |= 0x801;
    r4j_tss1E2168 = -1.0f;
    r4j_tss1E2180 = 4;
    r4j_tss1E218C = 0;
    sub_001D4350(0x40300, 1);
    aac_g1E2440 = 1;
    sub_001D4350(0x4033C, 0x204);
    r4j_rs1E2438 = 0x204;
    sub_001D4350(0x40340, 0);
    aac_g1E2444 = 0;
    sub_001D4350(0x40304, 1);
    aac_g1E243C = 1;
    sub_001D4350(0x40350, 0x8006);
    r4f_rs1E2478 = 0x8006;
    switch (e->wrap48 & 3) {
    case 1:
    case 2:
        r4f_tss1E2150 = 3;
        a1a_g1E2148 |= 1;
        break;
    case 0:
    case 3:
        r4f_tss1E2150 = 1;
        a1a_g1E2148 |= 1;
        break;
    }
    switch ((e->wrap48 >> 2) & 3) {
    case 1:
    case 2:
        r4f_tss1E2154 = 3;
        a1a_g1E2148 |= 1;
        break;
    case 0:
    case 3:
        r4f_tss1E2154 = 1;
        a1a_g1E2148 |= 1;
        break;
    }
    RtlLeaveCriticalSection(g_renderLock);
}
