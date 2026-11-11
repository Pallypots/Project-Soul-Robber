/* Area a80, group 2: handle wrappers and module state globals. Names inferred. */
#include "a80.h"

/* 0x00084C30: query a handle, -1 for null. */
int a80_HandleQuery(void *h) { if (h == 0) return -1; return sub_001BA7C0(h); }
/* 0x00084EC0: get word 0x3ED1B0. */
void *a80_Get3ED1B0(void) { return a80_g3ED1B0; }
/* 0x000852E0: clear three state words. */
void a80_Clear3ED1C4(void) { a80_g3ED1CC = 0; a80_g3ED1C8 = 0; a80_g3ED1C4 = 0; }
/* 0x00085360: set word 0x3ED1CC. */
void a80_Set3ED1CC(int32_t v) { a80_g3ED1CC = v; }
/* 0x00085370: get word 0x3ED1CC. */
int32_t a80_Get3ED1CC(void) { return a80_g3ED1CC; }
/* 0x00085380: clear word 0x3ED1CC. */
void a80_Zero3ED1CC(void) { a80_g3ED1CC = 0; }
/* 0x00085BF0: clear two state words. */
void a80_Clear3ED1D0(void) { a80_g3ED1D4 = 0; a80_g3ED1D0 = 0; }
/* 0x00085DA0: get word 0x3ED1D4. */
void *a80_Get3ED1D4(void) { return a80_g3ED1D4; }
/* 0x00086200: set word 0x3ED208. */
void a80_Set3ED208(void *v) { a80_g3ED208 = v; }
/* 0x00086210: get word 0x3ED208. */
void *a80_Get3ED208(void) { return a80_g3ED208; }
/* 0x00086220: clear word 0x3ED208. */
void a80_Zero3ED208(void) { a80_g3ED208 = 0; }
/* 0x00086230: dispatch through handler table 0x2E03B4. */
int a80_Dispatch2E03B4(int a, int b, int idx) { return a80_fnTab2E03B4[idx](a, b); }
/* 0x00086290: get word 0x3ED204. */
int32_t a80_Get3ED204(void) { return a80_g3ED204; }
/* 0x00086EC0: set word 0x3ED210. */
void a80_Set3ED210(int32_t v) { a80_g3ED210 = v; }
/* 0x00086ED0: get word 0x3ED210. */
int32_t a80_Get3ED210(void) { return a80_g3ED210; }
/* 0x00086EE0: clear word 0x3ED210. */
void a80_Zero3ED210(void) { a80_g3ED210 = 0; }
/* 0x00086F90: clear two state words. */
void a80_Clear3ED214(void) { a80_g3ED214 = 0; a80_g3ED218 = 0; }
/* 0x00087000: set word 0x3ED214. */
void a80_Set3ED214(int32_t v) { a80_g3ED214 = v; }
/* 0x00087010: get word 0x3ED214. */
int32_t a80_Get3ED214(void) { return a80_g3ED214; }
/* 0x00087020: clear word 0x3ED214. */
void a80_Zero3ED214(void) { a80_g3ED214 = 0; }
/* 0x00087440: clear word 0x3ED248. */
void a80_Zero3ED248(void) { a80_g3ED248 = 0; }
/* 0x000874B0: pause: from state 2 or 3, remember it and enter state 1. */
void a80_StatePause(void)
{
    int32_t s = a80_state3ED21C;
    if (s == 2 || s == 3) {
        a80_saved3ED220 = s;
        a80_state3ED21C = 1;
    }
}
/* 0x000874D0: resume the remembered state if paused. */
void a80_StateResume(void) { if (a80_state3ED21C == 1) a80_state3ED21C = a80_saved3ED220; }
/* 0x000874F0: first word of the current entry, -1 if none. */
int32_t a80_CurEntryId(void) { if (a80_ptr3ED240 == 0) return -1; return *a80_ptr3ED240; }
/* 0x00087500: get word 0x3ED238. */
int32_t a80_Get3ED238(void) { return a80_g3ED238; }
/* 0x00087510: set word 0x3ED238 to 1. */
void a80_Set3ED238(void) { a80_g3ED238 = 1; }
/* 0x00087520: set word 0x3ED23C. */
void a80_Set3ED23C(int32_t v) { a80_g3ED23C = v; }
/* 0x00087530: dispatch through handler table 0x2E0408. */
int a80_Dispatch2E0408(int idx, int a, int b) { return a80_fnTab2E0408[idx](a, b); }
