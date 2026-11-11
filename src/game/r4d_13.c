/* Area r4d: D3D surface helpers around 0x001A5310-0x001A748F (r4d_13). Names inferred. */
#include "r4d.h"

/* 0x001A5310: clear target, depth and stencil to the current background colour (red and blue
   swapped from the stored value). No inputs. */
void r4d_ClearToBackColour(void)
{
    uint32_t c;
    RtlEnterCriticalSection(g_renderLock);
    c = sub_0003DDE0(0);
    sub_001D6ED0(0, 0, 0xF3, ((c >> 16) & 0xFF) | ((c & 0xFF) << 16) | (c & 0xFF00FF00u), 1.0f, 0);
    r4d_g40B0E8 = 0;
    RtlLeaveCriticalSection(g_renderLock);
}

/* 0x001A5400: clear and present three times so every swap-chain buffer is black. No inputs. */
void r4d_ClearAllBuffers(void)
{
    RtlEnterCriticalSection(g_renderLock);
    sub_001D6ED0(0, 0, 0xF0, 0, 1.0f, 0);
    D3DDevice_Swap(0);
    sub_001D6ED0(0, 0, 0xF0, 0, 1.0f, 0);
    D3DDevice_Swap(0);
    sub_001D6ED0(0, 0, 0xF3, 0, 1.0f, 0);
    D3DDevice_Swap(0);
    RtlLeaveCriticalSection(g_renderLock);
}

/* 0x001A5500: copy the two swap-chain buffers into the current back buffer. No inputs. */
void r4d_CopyBackBuffers(void)
{
    void *back, *s;
    int i;
    RtlEnterCriticalSection(g_renderLock);
    back = sub_001D3490(-1);
    for (i = 0; i < 2; i++) {
        s = sub_001D3490(i);
        sub_001D34E0(back, 0, 0, s, 0);
        sub_001D5F50(s);
    }
    sub_001D5F50(back);
    RtlLeaveCriticalSection(g_renderLock);
}

/* 0x001A7430: copy level 0 of the texture at 0x0040AE68 into the back buffer; 0 or -1. No inputs. */
int r4d_CopyToBackBuffer(void)
{
    R4dSurfDesc src, dst;
    void *t, *back;
    t = sub_001D61C0(r4d_g40AE68, 0);
    if (!t)
        return -1;
    sub_001D7D50(t, &src);
    back = sub_001D3490(-1);
    sub_001D7D50(back, &dst);
    sub_001D34E0(back, 0, 0, t, 0);
    sub_001D5F50(back);
    sub_001D5F50(t);
    return 0;
}
