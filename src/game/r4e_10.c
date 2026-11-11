/* Area r4e: render init at 0x001A7750 (r4e_10). Names inferred. */
#include "r4e.h"

/* 0x001A7750: one-time render setup: lock and present event, frame callbacks, render
   targets, a 1x1 white texture, frame-buffer texture headers, a 640x480 texture and
   the vertex stream descriptors. No inputs; returns 0. */
int r4e_RenderInit(void)
{
    R4eLockedRect lr;
    R4eStreamDesc *s;
    if (!g_renderLock)
        g_renderLock = r4d_AllocPersist();
    if (!g_presentEvent)
        g_presentEvent = sub_001BCE98(0, 0, 0, 0);
    sub_001D2EB0(sub_001A53A0);
    sub_001D7310(sub_001A53B0);
    r4e_RenderTargetsInit();
    sub_001A1CE0();
    r4d_g40B0E8 = 0;
    r4e_g40AECC = sub_001D60F0(1, 1, 1, 1, 0, 6, 3);
    if (r4e_g40AECC) {
        sub_001D6210(r4e_g40AECC, 0, &lr, 0, 0);
        lr.bits[0] = 0xFF;
        lr.bits[1] = 0xFF;
        lr.bits[2] = 0xFF;
        lr.bits[3] = 0xFF;
    }
    r4e_WrapFrameBuffers();
    r4d_g40AE68 = sub_001D60F0(0x280, 0x1E0, 1, 1, 0, 0x12, 3);
    if (!r4e_g40B0F0) {
        for (s = r4e_streams40AFF8; s < r4e_streams40AFF8 + 16; s++)
            sub_002039F4(0, 0, 0, 0, s, 0);
        r4e_g40B0F0 = 1;
    }
    sub_001A72C0();
    r4e_g361AE0 = 2.0f;
    r4e_SetDepthRange(0.0f, 0.0f);
    return 0;
}
