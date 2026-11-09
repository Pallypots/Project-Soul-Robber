/* Job helpers (0x00057660-0x0005818D). Reference build OOGIE-XBOX-US-RETAIL.
 * Names inferred. */
#include "a50.h"

/* 0x00057660: address of byte `off` of range `i`, -1 if out of bounds. */
int a50_RangeAddr(uint32_t i, uint32_t off)
{
    if (i < 13 && a50_ranges[i].size > off)
        return a50_ranges[i].base + off;
    return -1;
}

/* 0x00057EA0: true on the background job's thread. */
int Job_OnJobThread(void)
{
    return g_job.thread == sub_001AD560();
}

/* 0x00057EC0: true on the loader thread. */
int a50_OnLoaderThread(void)
{
    return a50_loaderThread == sub_001AD560();
}

/* 0x00057EE0: call the job poll hook, -1 if none. */
int a50_JobPoll(void)
{
    if (a50_jobPoll)
        return a50_jobPoll();
    return -1;
}

/* 0x00057EF0: does the object's descriptor (+0x0C) have id (+0x14) `id`. */
int a50_ObjIdIs(uint8_t *obj, int id)
{
    return *(int32_t *)(*(uint8_t **)(obj + 0xC) + 0x14) == id;
}

/* 0x00057F10: does the object's descriptor have kind (+0x30) `kind`. */
int a50_ObjKindIs(uint8_t *obj, int kind)
{
    return *(int32_t *)(*(uint8_t **)(obj + 0xC) + 0x30) == kind;
}

/* 0x00058170: wait for a free request slot, clear it, then kick the loader. */
void a50_KickLoader(void)
{
    int *p;
    while ((p = sub_00057F30()) == 0) ;
    *p = 0;
    sub_00102FA0(0);
    sub_001AD540();
}
