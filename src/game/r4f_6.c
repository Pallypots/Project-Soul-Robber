/* Area r4f: normal model draw at 0x001A3080 (r4f_6). Names inferred. */
#include "r4f.h"

/* 0x001A3080: draw a normal model: blend mode from the object's blend block, transforms
   and shader constants, texture setup, then every vertex block of every group with its
   group's optional arrays; restore the default alpha states. Returns 0. Stack arg (o).
   XDK callees are stdcall, 0x001D24F0, 0x001D2490 and 0x001D4350 fastcall. */
int r4f_DrawNormalModel(R4fDrawObj *o)
{
    R4dMat m, view, world, proj;
    R4eVtxHdr *cur;
    R4fModelHdr *mdl;
    R4fMeshGrp *g;
    int i, j;
    r4f_PerfBegin1D60E0(0xFFFFFFFF, r4f_strDrawNormalModel27B5E4);
    sub_001A1D50(1);
    r4f_TexBind1A6820(r4f_TexLookup1B9650(o->tex0D8));
    sub_001D4350(0x41D78, 1);
    r4f_rs1E2498 = 1;
    r4c_TargetSelect(o->tex0D0 == 0 ? 3 : 2);
    if (o->blend0CC == r4f_blk42C860)
        sub_001D4720(0x900);
    else if (o->blend0CC != r4f_blk42C7E0 && o->blend0CC == r4f_blk42CA00)
        sub_001D4720(0x901);
    else
        sub_001D4720(0);
    sub_001D2E10(0, &view);
    sub_001D2E10(1, &world);
    sub_001D2E10(6, &proj);
    sub_001E522D(&m, &proj, &view);
    sub_001E522D(&m, &m, &world);
    r4e_SetVSConst1D24F0(0, &m);
    sub_001E522D(&m, &view, &world);
    r4e_SetVSConst1D24F0(8, &m);
    if (sub_001A7630()) {
        sub_001D4350(0x40358, 0x1000000);
        r4e_rs1E245C = 0x1000000;
    }
    r4f_SetVSConsts1D2490(0x19, o->vsc0DC);
    sub_001A69C0(o->tex0C0->fmtE0, o->tex0C0->fE4);
    sub_001A6C60(o->fEC);
    if (o->tex0C0->fmtE8 == 0x51001 && o->tex0C0->fEC == 0) {
        sub_001D4350(0x40300, 0);
        aac_g1E2440 = 0;
        sub_001D4350(0x4035C, 0);
        r4d_g1E2450 = 0;
    }
    mdl = o->model0BC;
    g = (R4fMeshGrp *)((uint8_t *)mdl + 0x30);
    for (i = 0; i < mdl->count00; i++) {
        cur = (R4eVtxHdr *)((uint8_t *)g + 0x60);
        for (j = 0; j < g->count00; j++)
            r4e_DrawVertexBlockOpt(&cur, g->flags04);
        g = (R4fMeshGrp *)cur;
    }
    sub_001D4350(0x40300, 1);
    aac_g1E2440 = 1;
    sub_001D55A0(1);
    sub_001D4350(0x4035C, 1);
    r4d_g1E2450 = 1;
    sub_001D5630(0);
    sub_001D4350(0x40358, 0x1010101);
    r4e_rs1E245C = 0x1010101;
    sub_001D4350(0x4035C, 1);
    r4d_g1E2450 = 1;
    r4f_PerfEnd1D60E0();
    return 0;
}
