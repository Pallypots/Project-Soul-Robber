/* Background job and frame present. Reference build OOGIE-XBOX-US-RETAIL.
 * Names inferred. Records: docs/functions/system.md */
#include "oogie.h"

/* 0x00057E90 */
JobFunc Job_IsRunning(void)
{
    return g_job.func;
}

/* 0x001A7BA0: present the frame under the render lock, then yield while other
 * threads want the CPU, waiting alertably on the present event. */
void Frame_Present(void)
{
    uint32_t r;

    sub_001A7940();
    RtlEnterCriticalSection(g_renderLock);
    D3DDevice_Swap(0);
    RtlLeaveCriticalSection(g_renderLock);
    while (SwitchToThread()) {
        r = WaitForSingleObjectEx(g_presentEvent, 0, 1);
        if (r != 0x102 && r != 0xC0)
            break;
    }
}
