/* Area r4e: immediate-mode draws at 0x001A2D80 and 0x001A36A0 (r4e_8). Names inferred. */
#include "r4e.h"

/* 0x001A2D80: draw count user-pointer primitives (type 6, 0x30-byte vertices) with
   the current world/view/projection loaded into the vertex-shader constants 0 and 8.
   Stack args (verts count); returns 0. */
int r4e_DrawPrimsUP(const void *verts, int count)
{
    R4dMat r, view, world, proj;
    if (!(r4e_g40AD48 & 1))
        r4e_g40AD48 |= 1;
    r4c_TargetSelect(0xB);
    sub_001A1D50(2);
    sub_001D4720(0);
    sub_001D2E10(0, &world);
    sub_001D2E10(1, &view);
    sub_001D2E10(6, &proj);
    sub_001E522D(&r, &proj, &world);
    sub_001E522D(&r, &r, &view);
    r4e_SetVSConst1D24F0(0, &r);
    sub_001E522D(&r, &world, &view);
    r4e_SetVSConst1D24F0(8, &r);
    sub_001D4350(0x40358, 0x10101);
    r4e_rs1E245C = 0x10101;
    r4e_streams40AFF8[0].addr04 = (uint32_t)(uintptr_t)verts & 0x0FFFFFFF; /* XBOX32: vertex stream physical address (32-bit GPU word) */
    sub_001D26C0(0, &r4e_streams40AFF8[0], 0x30);
    sub_001D5AC0(6, count, verts, 0x30);
    sub_001D4350(0x40358, 0x1010101);
    r4e_rs1E245C = 0x1010101;
    return 0;
}

/* 0x001A36A0: as r4e_DrawPrimsUP for count quads (type 8, four 0x80-byte vertices
   each) in target mode 0. Stack args (verts count); returns 0. */
int r4e_DrawQuadsUP(const void *verts, int count)
{
    R4dMat r, view, world, proj;
    if (!(r4e_g40AD4C & 1))
        r4e_g40AD4C |= 1;
    r4c_TargetSelect(0);
    sub_001A1D50(2);
    sub_001D4720(0);
    sub_001D2E10(0, &world);
    sub_001D2E10(1, &view);
    sub_001D2E10(6, &proj);
    sub_001E522D(&r, &proj, &world);
    sub_001E522D(&r, &r, &view);
    r4e_SetVSConst1D24F0(0, &r);
    sub_001E522D(&r, &world, &view);
    r4e_SetVSConst1D24F0(8, &r);
    sub_001D4350(0x40358, 0x10101);
    r4e_rs1E245C = 0x10101;
    r4e_streams40AFF8[0].addr04 = (uint32_t)(uintptr_t)verts & 0x0FFFFFFF; /* XBOX32: vertex stream physical address (32-bit GPU word) */
    sub_001D26C0(0, &r4e_streams40AFF8[0], 0x80);
    sub_001D5AC0(8, count * 4, verts, 0x80);
    sub_001D4350(0x40358, 0x1010101);
    r4e_rs1E245C = 0x1010101;
    return 0;
}
