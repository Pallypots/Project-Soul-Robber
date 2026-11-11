/* Area r1j, group 8: job buckets 0x00058780.
   Names inferred. */
#include "r1j.h"

/* job record of a bucket node: the job sits 0x10 bytes into the node */
#define R1J_NODE_JOB(n) ((R1jJob *)((char *)(n)->data + 0x10))
#define R1J_JOB_NODE(j) ((void *)((char *)(j) - 0x10))

/* 0x00058780: kill every job: for each job of the six buckets (the
   bucket being walked is published in r1j_jobBucketCur) stop its thread
   when some job with that thread is still running (state not 0 or 3),
   close its handle, free its memory, reset it and move its node to the
   free list. Then stop the main job's thread and close its handle, and
   reset the main job. */
void r1j_JobsKillAll(void)
{
    int i, key;
    R1jJobNode *n, *next, *f;
    R1jJob *j, *fj;
    R1jJobBucket *b;
    for (i = 0; i < 6; i++) {
        r1j_jobBucketCur = i;
        for (n = r1j_jobBuckets[i].first; n != 0; n = next) {
            j = R1J_NODE_JOB(n);
            key = j->thread;
            next = n->next;
            if (key != -1) {
                for (b = r1j_jobBuckets; (intptr_t)b < (intptr_t)(r1j_jobBuckets + 6); b++) {
                    f = sub_0003DBC0(b, (void *)sub_00057EF0, (void *)(intptr_t)key);
                    if (f != 0) {
                        fj = R1J_NODE_JOB(f);
                        if (fj != 0 && fj->state != 0 && fj->state != 3)
                            sub_001AD440(j->thread);
                        break;
                    }
                }
            }
            sub_001AA310(j->handle);
            sub_00053880(j->mem);
            j->mem = 0;
            j->thread = -1;
            j->handle = -1;
            sub_0003D8C0(R1J_JOB_NODE(j));
            sub_0003D880(r1j_jobFree3E3F54, R1J_JOB_NODE(j));
        }
    }
    if (r1j_mainJob3E3F64.thread != -1) {
        sub_001AD440(r1j_mainJob3E3F64.thread);
        if (r1j_mainJob3E3F64.handle != -1)
            sub_001AA310(r1j_mainJob3E3F64.handle);
    }
    r1j_mainJob3E3F64.state = 0;
    r1j_mainJob3E3F64.thread = -1;
    r1j_mainJob3E3F64.handle = -1;
    r1j_mainJob3E3F64.mem = 0;
    r1j_mainJob3E3F64.d14 = 0;
    r1j_mainJob3E3F64.done = 0;
    r1j_mainJob3E3F64.arg = 0;
}
