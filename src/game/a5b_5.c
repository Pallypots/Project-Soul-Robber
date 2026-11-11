/* Background job lookup and control (0x00057E60-0x000592D2), second pass.
 * Reference build OOGIE-XBOX-US-RETAIL. Names inferred. Each job record
 * sits 0x10 bytes into its list descriptor (descriptor +0x14 = job thread). */
#include "a5b.h"

/* 0x00057E60: finish a job: close its handle, run its completion callback,
 * mark it idle. */
void a5b_JobFinish(BackgroundJob *job)
{
    sub_001AA460(*(int32_t *)job->unk08);
    if (job->func != 0)
        job->func(job->arg);
    job->state = 0;
}

/* 0x00057F30: the job record of the calling thread (main job or pool). */
BackgroundJob *a5b_JobCurrent(void)
{
    void *self = sub_001AD560();
    int i;
    uint8_t *node;
    if (g_job.thread == self)
        return &g_job;
    for (i = 0; i < 6; i++) {
        node = (uint8_t *)sub_0003DBC0(a5b_jobLists[i], a50_ObjIdIs, self);
        if (node != 0)
            return (BackgroundJob *)(*(uint8_t **)(node + 0xC) + 0x10);
    }
    return 0;
}

/* 0x00057F80: the pooled job record running on thread `id` (NULL if none). */
BackgroundJob *a5b_JobById(int id)
{
    int i;
    uint8_t *node;
    if (id == -1)
        return 0;
    for (i = 0; i < 6; i++) {
        node = (uint8_t *)sub_0003DBC0(a5b_jobLists[i], a50_ObjIdIs, (void *)(intptr_t)id);
        if (node != 0)
            return (BackgroundJob *)(*(uint8_t **)(node + 0xC) + 0x10);
    }
    return 0;
}

/* 0x00058020: the pooled job record of kind `kind` (NULL if none). */
BackgroundJob *a5b_JobByKind(int kind)
{
    int i;
    uint8_t *node;
    for (i = 0; i < 6; i++) {
        node = (uint8_t *)sub_0003DBC0(a5b_jobLists[i], a50_ObjKindIs, (void *)(intptr_t)kind);
        if (node != 0)
            return (BackgroundJob *)(*(uint8_t **)(node + 0xC) + 0x10);
    }
    return 0;
}

/* 0x00058130: ask job `id` (not the caller's own) to suspend: state 2. */
int a5b_JobRequestSuspend(int id)
{
    BackgroundJob *j = a5b_JobById(id);
    if (j == 0 || j->thread == (void *)-1 || j->thread == sub_001AD560()
        || j->state == 0 || j->state == 3)
        return -1;
    j->state = 2;
    return 0;
}

/* 0x000581E0: stop job `id` (not the caller's own) and release its thread. */
int a5b_JobStop(int id)
{
    BackgroundJob *j = a5b_JobById(id);
    if (j == 0 || j->thread == (void *)-1 || j->thread == sub_001AD560())
        return -1;
    j->state = 0;
    sub_001AD440(j->thread);
    return 0;
}

/* 0x000588D0: resume suspended job `id`: state 1 and requeue it. */
int a5b_JobResume(int id)
{
    BackgroundJob *j = a5b_JobById(id);
    if (j == 0 || j->thread == sub_001AD560() || j->state != 2)
        return -1;
    j->state = 1;
    sub_0003D910((uint8_t *)j - 0x10);
    return 0;
}

/* 0x000592C0: run 0x001A1130 then 0x00058B40 on the same argument. */
int a5b_Run58B40(void *a)
{
    sub_001A1130(a);
    return sub_00058B40(a);
}
