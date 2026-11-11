/* Area r4f: projection and fog setup at 0x001A6D70-0x001A7229 (r4f_10). Names inferred. */
#include "r4f.h"

/* 0x001A6D70: build the perspective projection from the lens (field of view from
   atan(240/d/w) scaled by 1.15, aspect 1.2698), load it as the projection transform
   and copy it to out. Stack args (out l). D3DX and XDK callees are stdcall. */
void r4f_SetProjection(float *out, const R4fLens *l)
{
    R4dMat m;
    float k = 240.0f / l->d08;
    float fov;
    r4f_Atan1A3EB0(k / l->w00);
    fov = r4f_Atan1A3EB0(k / l->w00) * 1.15f;
    r4f_PerspFovLH1E4E86(&m, fov, 1.3333334f, r4e_g361AE0, l->far20);
    r4f_PerspFovLH1E4E86(&m, fov, 1.2698413f, r4e_g361AE0, l->far20);
    RtlEnterCriticalSection(g_renderLock);
    r4f_SetTransform1D2CF0(1, &m);
    RtlLeaveCriticalSection(g_renderLock);
    r4f_MatCopy1ADA40(out, &m);
}

/* 0x001A7100: under the render lock set the fog colour (ARGB to ABGR), the fog start
   and end, and the vertex shader fog constants. Stack arg (f). 0x001D2490 is fastcall
   (ECX EDX); the other XDK callees are stdcall. */
void r4f_SetFogRange(const R4fFog *f)
{
    float c[4];
    uint32_t col;
    RtlEnterCriticalSection(g_renderLock);
    a1a_g1E2148 |= 0x2000;
    a1a_g1E24C0 = 1;
    col = f->colour10;
    c[0] = 0.0f;
    c[1] = 0.0f;
    c[2] = 0.0f;
    c[3] = 0.0f;
    r4f_SetFogColour1D46D0(((col >> 16) & 0xFF) | ((col & 0xFF) << 16) | (col & 0xFF00FF00));
    a1a_g1E2148 |= 0x2000;
    r4f_g1E24C4 = 0;
    r4f_g1E24C8 = f->end0C;
    a1a_g1E2148 |= 0x2000;
    r4f_g1E24CC = f->start08;
    a1a_g1E2148 |= 0x2000;
    c[0] = -1.0f / (f->end0C - f->start08);
    c[1] = (1.0f - (f->end0C + f->start08) * c[0]) * 0.5f;
    c[2] = 1.0f / (f->far04 - f->near00);
    r4f_SetVSConsts1D2490(0x14, c);
    RtlLeaveCriticalSection(g_renderLock);
}

/* 0x001A7490: under the render lock draw the saved screen texture 0x0040AE68 over the
   whole 640x480 screen (offset by the depth-of-field shift), half transparent, with
   clamped addressing and alpha test off; then restore the stage-0 texture and states.
   No inputs. 0x001D4350 is fastcall (ECX EDX); the other XDK callees are stdcall. */
void r4f_DrawScreenCopy(void)
{
    R4fQuad q;
    void *old;
    RtlEnterCriticalSection(g_renderLock);
    old = r4f_GetTexture1D3A80(0);
    r4f_SetTexture1D3AB0(0, r4d_g40AE68);
    r4f_tss1E2150 = 3;
    r4f_tss1E2154 = 3;
    a1a_g1E2148 |= 1;
    r4f_tss1E2160 = 1;
    r4f_tss1E215C = 1;
    sub_001D4350(0x40304, 0);
    aac_g1E243C = 0;
    sub_001D55A0(0);
    q.rgba[0] = 255.0f;
    q.rgba[1] = 255.0f;
    q.rgba[2] = 255.0f;
    q.rgba[3] = 128.0f;
    q.x0 = 0.0f - r4e_depth40AE88[0];
    q.y0 = 0.0f - r4e_depth40AE88[1];
    q.z = 10000.0f;
    q.u0 = 0.0f;
    q.v0 = 0.0f;
    q.x1 = 640.0f - r4e_depth40AE88[0];
    q.y1 = 480.0f - r4e_depth40AE88[1];
    q.u1 = 640.0f;
    q.v1 = 480.0f;
    r4f_DrawQuad1A5D90(&q);
    r4f_SetTexture1D3AB0(0, old);
    if (old)
        r4e_Release1D5F50(old);
    r4f_tss1E2160 = 2;
    r4f_tss1E215C = 2;
    r4f_tss1E2150 = 1;
    a1a_g1E2148 |= 1;
    r4f_tss1E2154 = 1;
    sub_001D4350(0x40304, 1);
    aac_g1E243C = 1;
    sub_001D55A0(1);
    RtlLeaveCriticalSection(g_renderLock);
}
