/* Area r4j: world model draw (0x001A2EB0). Names inferred. */
#include "r4j.h"

/* 0x001A2EB0: draw a world (level) model: render target 1, texture
   wrap/alpha states, the combined projection*view*world matrix into shader
   constants 0..3, then the alpha mode picked from the texture block's
   format (0x5040D: alpha test on with reference 0x80; 0x51001: blending
   off; otherwise blending on, reference 0), then every vertex block of
   every group. Returns 0. Stack arg (o). XDK callees are stdcall except
   0x001D24F0 and 0x001D4350 which are fastcall (ECX EDX). */
int r4j_DrawWorldModel(R4fDrawObj *o)
{
    R4dMat m, view, world, proj;
    R4jVtxCursor c;
    uint32_t fmt;
    int32_t e4;
    R4fModelHdr *mdl;
    R4fMeshGrp *g;
    int i, j;

    r4f_PerfBegin1D60E0(0xFFFF8080, r4j_strDrawWorldModel27B5D4);
    r4c_TargetSelect(1);
    sub_001A1D50(1);
    sub_001D4350(0x41D78, 1);
    r4f_rs1E2498 = 1;
    sub_001D4350(0x40304, 1);
    aac_g1E243C = 1;
    sub_001D4720(0);
    sub_001D2E10(0, &view);
    sub_001D2E10(1, &world);
    sub_001D2E10(6, &proj);
    sub_001E522D(&m, &proj, &view);
    sub_001E522D(&m, &m, &world);
    r4e_SetVSConst1D24F0(0, &m);
    sub_001D4350(0x41D78, 1);
    r4f_rs1E2498 = 1;
    sub_001A6C60(o->fE4);
    fmt = o->tex0C0->fmtE0;
    e4 = o->tex0C0->fE4;
    /* alpha mode by texture format; a set fE4 always takes the default */
    switch (e4 != 0 ? 0 : fmt) {
    case 0x5040D:
        sub_001A6F10(1);
        r4e_SetRenderState4035C(1);
        sub_001A6F50(0x80);
        break;
    case 0x51001:
        r4e_SetRenderState4035C(0);
        break;
    default:
        r4e_SetRenderState4035C(1);
        sub_001A6F50(0);
        break;
    }
    mdl = o->model0BC;
    g = (R4fMeshGrp *)((uint8_t *)mdl + 0x30);
    r4f_TexBind1A6820(r4f_TexLookup1B9650(o->tex0D0));
    for (i = 0; i < mdl->count00; i++) {
        c.cur = (R4eVtxHdr *)((uint8_t *)g + 0x60);
        c.flags = &g->flags04;
        for (j = 0; j < g->count00; j++)
            r4e_DrawVertexBlock(&c.cur);
        g = (R4fMeshGrp *)c.cur;
    }
    sub_001A1D50(0);
    sub_001A6E40(1);
    r4f_PerfEnd1D60E0();
    return 0;
}
