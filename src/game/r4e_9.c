/* Area r4e: D3D wrappers around 0x001A5480-0x001A70F8 (r4e_9). Names inferred. */
#include "r4e.h"

/* 0x001A5480: set the scissor/viewport rectangle from the screen offsets
   (0x0019BA20, 0x0019BA30), clamped to 640x480. No inputs. */
void r4e_SetSafeViewport(void)
{
    int x = sub_0019BA20();
    int y = sub_0019BA30();
    r4e_viewport361AE4.x0 = x;
    if (x < 0)
        r4e_viewport361AE4.x0 = 0;
    r4e_viewport361AE4.y0 = y + 0x10;
    if (y + 0x10 < 0)
        r4e_viewport361AE4.y0 = 0;
    r4e_viewport361AE4.x1 = x + 0x280;
    if (x + 0x280 > 0x280)
        r4e_viewport361AE4.x1 = 0x280;
    r4e_viewport361AE4.y1 = y + 0x1D0;
    if (y + 0x1D0 > 0x1E0)
        r4e_viewport361AE4.y1 = 0x1E0;
    r4e_SetScissor1D3D80(1, 0, &r4e_viewport361AE4);
}

/* 0x001A6E80: under the render lock, set render state 0x4035C to on (1) or off (0)
   and cache it. Stack arg (on). */
void r4e_SetRenderState4035C(int on)
{
    RtlEnterCriticalSection(g_renderLock);
    if (on) {
        sub_001D4350(0x4035C, 1);
        r4d_g1E2450 = 1;
        RtlLeaveCriticalSection(g_renderLock);
        return;
    }
    sub_001D4350(0x4035C, 0);
    r4d_g1E2450 = 0;
    RtlLeaveCriticalSection(g_renderLock);
}

/* 0x001A6F90: build texture headers over the back buffer and the depth buffer so
   they can be sampled. No inputs. */
void r4e_WrapFrameBuffers(void)
{
    R4dSurfDesc d, dz;
    R4eSurf *s;
    s = r4e_GetBackBuffer1D3490(0);
    r4e_GetDesc1D7D50(s, &d);
    sub_002039CA(d.f[5], d.f[6], 1, 0, d.f[0], 0, &r4e_backTex40AE98, s->res04, d.f[5] * 4);
    r4e_backTex40AE98.data10 = s->data10;
    r4e_Release1D5F50(s);
    s = sub_001D3810();
    r4e_GetDesc1D7D50(s, &dz);
    sub_002039CA(dz.f[5], dz.f[6], 1, 0, dz.f[0], 0, &r4e_depthTex40AED4, s->res04, dz.f[5] * 4);
    r4e_depthTex40AED4.data10 = s->data10;
    r4e_Release1D5F50(s);
}

/* 0x001A7040: texture header over the current back buffer (index -1). No inputs. */
R4eTexHdr *r4e_WrapBackBuffer(void)
{
    R4dSurfDesc d;
    R4eSurf *s = r4e_GetBackBuffer1D3490(-1);
    r4e_GetDesc1D7D50(s, &d);
    sub_002039CA(d.f[5], d.f[6], 1, 0, d.f[0], 0, &r4e_backTex40AE98, s->res04, d.f[5] * 4);
    r4e_backTex40AE98.data10 = s->data10;
    r4e_Release1D5F50(s);
    return &r4e_backTex40AE98;
}

/* 0x001A70A0: texture header over the depth buffer. No inputs. */
R4eTexHdr *r4e_WrapDepthBuffer(void)
{
    R4dSurfDesc d;
    R4eSurf *s = sub_001D3810();
    r4e_GetDesc1D7D50(s, &d);
    sub_002039CA(d.f[5], d.f[6], 1, 0, d.f[0], 0, &r4e_depthTex40AED4, s->res04, d.f[5] * 4);
    r4e_depthTex40AED4.data10 = s->data10;
    r4e_Release1D5F50(s);
    return &r4e_depthTex40AED4;
}

/* 0x001A7640: under the render lock, store and apply the depth range (a, b).
   Stack args (a b), floats. */
void r4e_SetDepthRange(float a, float b)
{
    RtlEnterCriticalSection(g_renderLock);
    r4e_depth40AE88[0] = a;
    r4e_depth40AE88[1] = b;
    r4e_depth40AE88[2] = 0.0f;
    r4e_depth40AE88[3] = 0.0f;
    sub_001D4080(a, b);
    RtlLeaveCriticalSection(g_renderLock);
}
