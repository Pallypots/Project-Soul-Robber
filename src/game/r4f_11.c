/* Area r4f: pre-transformed screen quads at 0x001A5BD0-0x001A5F41 (r4f_11). Names inferred. */
#include "r4f.h"

/* 0x001A5BD0: under the render lock draw a pre-transformed quad on target mode 0xC with
   blend mode 2 and the depth-of-field shift constants. Returns 0. Stack arg (q).
   0x001D2490 and 0x001D4350 are fastcall (ECX EDX); the other XDK callees are stdcall. */
int r4f_DrawQuadT2(const R4fQuad *q)
{
    R4fTLVert v[4];
    uint32_t col;
    v[0].x = q->x0;
    v[1].x = q->x1;
    v[2].x = q->x0;
    v[3].x = q->x1;
    v[0].y = q->y0;
    v[1].y = q->y0;
    v[2].y = q->y1;
    v[3].y = q->y1;
    v[0].rhw = 1.0f;
    v[1].rhw = 1.0f;
    v[2].rhw = 1.0f;
    v[3].rhw = 1.0f;
    v[0].z = q->z;
    v[1].z = q->z;
    v[2].z = q->z;
    v[3].z = q->z;
    v[0].u = q->u0;
    v[0].v = q->v0;
    v[1].u = q->u1;
    v[1].v = q->v0;
    v[2].u = q->u0;
    v[2].v = q->v1;
    v[3].u = q->u1;
    v[3].v = q->v1;
    col = (uint32_t)R4F_FTOI(q->rgba[3]);
    col = col << 8 | (uint32_t)R4F_FTOI(q->rgba[0]);
    col = col << 8 | (uint32_t)R4F_FTOI(q->rgba[1]);
    col = col << 8 | (uint32_t)R4F_FTOI(q->rgba[2]);
    v[0].colour = col;
    v[1].colour = col;
    v[2].colour = col;
    v[3].colour = col;
    RtlEnterCriticalSection(g_renderLock);
    r4c_TargetSelect(0xC);
    sub_001A1D50(2);
    r4f_SetVSConsts1D2490(0xC, r4e_depth40AE88);
    a1a_g1E2148 |= 0x2000;
    a1a_g1E24C0 = 0;
    sub_001D4350(0x41D78, 0x10);
    r4f_rs1E2498 = 0x10;
    sub_001D4720(0);
    a1a_g1E2148 |= 0x1200;
    r4f_g1E24E8 = 0;
    sub_001D5AC0(6, 4, v, 0x1C);
    RtlLeaveCriticalSection(g_renderLock);
    return 0;
}

/* 0x001A5D90: like r4f_DrawQuadT2 with blend mode 6. Returns 0. Stack arg (q). */
int r4f_DrawQuad1A5D90(const R4fQuad *q)
{
    R4fTLVert v[4];
    uint32_t col;
    v[0].x = q->x0;
    v[1].x = q->x1;
    v[2].x = q->x0;
    v[3].x = q->x1;
    v[0].y = q->y0;
    v[1].y = q->y0;
    v[2].y = q->y1;
    v[3].y = q->y1;
    v[0].rhw = 1.0f;
    v[1].rhw = 1.0f;
    v[2].rhw = 1.0f;
    v[3].rhw = 1.0f;
    v[0].z = q->z;
    v[1].z = q->z;
    v[2].z = q->z;
    v[3].z = q->z;
    v[0].u = q->u0;
    v[0].v = q->v0;
    v[1].u = q->u1;
    v[1].v = q->v0;
    v[2].u = q->u0;
    v[2].v = q->v1;
    v[3].u = q->u1;
    v[3].v = q->v1;
    col = (uint32_t)R4F_FTOI(q->rgba[3]);
    col = col << 8 | (uint32_t)R4F_FTOI(q->rgba[0]);
    col = col << 8 | (uint32_t)R4F_FTOI(q->rgba[1]);
    col = col << 8 | (uint32_t)R4F_FTOI(q->rgba[2]);
    v[0].colour = col;
    v[1].colour = col;
    v[2].colour = col;
    v[3].colour = col;
    RtlEnterCriticalSection(g_renderLock);
    r4c_TargetSelect(0xC);
    sub_001A1D50(6);
    r4f_SetVSConsts1D2490(0xC, r4e_depth40AE88);
    a1a_g1E2148 |= 0x2000;
    a1a_g1E24C0 = 0;
    sub_001D4350(0x41D78, 0x10);
    r4f_rs1E2498 = 0x10;
    sub_001D4720(0);
    a1a_g1E2148 |= 0x1200;
    r4f_g1E24E8 = 0;
    sub_001D5AC0(6, 4, v, 0x1C);
    RtlLeaveCriticalSection(g_renderLock);
    return 0;
}
