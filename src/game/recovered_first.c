/* First recovered game functions. State of each is in docs/functions/first.md.
 * Reference build: OOGIE-XBOX-US-RETAIL. Names are INFERRED, not original. */
#include "oogie_globals.h"

/* --- external functions, not yet recovered (called by original address) --- */
void Hud_Notify(int mode, int value);               /* 0x00025FD0, purpose not analysed */
void Frame_PrePresent(void);                         /* 0x001A7940, not analysed */
#ifdef _MSC_VER
#define OOG_STDCALL __stdcall
#define OOG_IMPORT __declspec(dllimport)
#else
#define OOG_STDCALL
#define OOG_IMPORT
#endif

/* Callee-pops (stdcall) for these four is VERIFIED from the original: no
 * `add esp` follows their calls. The two Rtl calls go through the kernel thunk
 * table (`call [0x25F8E0]`), i.e. a dllimport, as XDK headers declare them. */
int OOG_STDCALL D3DDevice_Swap(uint32_t flags);   /* 0x001D6D20, XDK D3D8 (library) */
OOG_IMPORT void OOG_STDCALL RtlEnterCriticalSection(void *cs);             /* kernel ordinal 277, thunk slot 0 */
OOG_IMPORT void OOG_STDCALL RtlLeaveCriticalSection(void *cs);             /* kernel ordinal 294, thunk slot 1 */
int OOG_STDCALL SwitchToThread(void);                          /* 0x001BD332, XAPI */
uint32_t OOG_STDCALL WaitForSingleObjectEx(void *h, uint32_t ms, int alertable); /* 0x001BD012, XAPI */

#define WAIT_TIMEOUT_      0x102u
#define WAIT_IO_COMPLETION_ 0xC0u

/* 0x00057E90, 6 bytes: is the background loading job still running? */
JobFunc Job_IsRunning(void)
{
    return g_job.func;
}

/* 0x000414A0, 68 bytes: add exclamation points to the chapter grade, kept in 0..999. */
void Grade_AddExclamations(int amount)
{
    g_chapterExclamations += amount;
    Hud_Notify(1, 0x78);
    if (g_chapterExclamations < 0)
        g_chapterExclamations = 0;
    else if (g_chapterExclamations > 999)
        g_chapterExclamations = 999;
}

/* 0x001A7BA0, 88 bytes: end-of-frame present under the render lock, then yield
 * until no other thread wants the CPU, waiting alertably on the present event. */
void Frame_Present(void)
{
    uint32_t r;

    Frame_PrePresent();
    RtlEnterCriticalSection(g_renderLock);
    D3DDevice_Swap(0);
    RtlLeaveCriticalSection(g_renderLock);

    while (SwitchToThread()) {
        r = WaitForSingleObjectEx(g_presentEvent, 0, 1);
        if (r != WAIT_TIMEOUT_ && r != WAIT_IO_COMPLETION_)
            break;
    }
}
