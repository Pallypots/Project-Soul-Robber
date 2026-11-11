/* Area r6f: task node lists around 0x0008C4D0-0x0008CCE3 (r6f_2). Names inferred. */
#include "r6f.h"

/* 0x0008C5F0: bubble-sort a sibling chain by type, then by target, between two
   sentinel nodes; returns the new first node. */
R6fTask *r6f_TaskSortList(R6fTask *list)
{
    R6fDNode tail, head;
    R6fTask *t, *nx;
    if (!list)
        return 0;
    head.next = &list->hdr;
    head.prev = (R6fDNode *)sub_0007F310(list);
    list->hdr.prev = &head;
    tail.prev = (R6fDNode *)sub_0007F350(list);
    tail.next = (R6fDNode *)sub_0007F300(tail.prev);
    tail.prev->next = &tail;
    t = list;
    while (&t->hdr != tail.prev) {
        do {
            nx = (R6fTask *)sub_0007F300(t);
            if (t->f18.s.type > nx->f18.s.type)
                sub_0008C2C0(&t->hdr, &nx->hdr);
            else if (t->f18.s.type == nx->f18.s.type && t->workId > nx->workId)
                sub_0008C2C0(&t->hdr, &nx->hdr);
            else
                t = nx;
        } while (&t->hdr != tail.prev);
        sub_0008C2C0(tail.prev, &tail);
        t = (R6fTask *)head.next;
    }
    if (head.prev)
        head.prev->next = &t->hdr;
    if (t)
        t->hdr.prev = head.prev;
    if (tail.prev)
        tail.prev->next = tail.next;
    if (tail.next)
        tail.next->prev = tail.prev;
    return t;
}

/* 0x0008C6E0: create a task node of a type (heap 5) for a work block and run
   the type's init handler; NULL on failure. */
R6fTask *r6f_TaskNew(int type, void *work)
{
    R6fOps *ops = R6F_OPS(type);
    R6fTask *t;
    sub_0007F4A0(4, sub_0008BCD0(sub_0008BD00(5)));
    t = (R6fTask *)sub_0007F240(0, ops->size, 0xA2, r6f_srcFile270024);
    if (!t)
        return 0;
    t->f18.s.type = (int8_t)type;
    t->work = (R6eWork *)work;
    t->unk22 = 0;
    t->refs = 0;
    if (ops->init && ops->init(t, 0)) {
        sub_0007F2B0(t);
        sub_0008BF70(t);
        return 0;
    }
    return t;
}

/* 0x0008C940: copy a task node (new node of the same type and work, copy handler). */
int r6f_TaskCopyNode(R6fTask **out, R6fTask *src)
{
    R6fOps *ops = R6F_OPS(src->f18.s.type);
    R6fTask *t;
    int r;
    *out = sub_0008C6E0(src->f18.s.type, src->work);
    if (!*out)
        return -1;
    r = ops->copy(*out, src);
    if (r) {
        t = *out;
        sub_0007F2B0(t);
        sub_0008BF70(t);
        *out = 0;
        return r;
    }
    (*out)->refs = 0;
    return 0;
}

/* 0x0008CC50: run the step handler of the first entry's task; on a result pop
   the entry, else drop it when its task has finished (flag 2). */
int r6f_RefListStep(R6fRef **list, int arg)
{
    R6fRef *e;
    R6fOps *ops;
    int r;
    if (!list)
        return -1;
    e = *list;
    if (!e)
        return 0;
    ops = (R6fOps *)sub_0008BF50(e->task->f18.s.type);
    if (ops->step) {
        r = ops->step(e->task, arg);
        if (r) {
            sub_0008BF60(e->task->f18.s.type);
            *list = (R6fRef *)sub_0007F300(*list);
            sub_0008CC30(e);
            return r;
        }
    }
    if (e->task->f18.u & 2) {
        *list = (R6fRef *)sub_0007F300(*list);
        sub_0007F2B0(e);
        sub_0008CB90(e);
    }
    return 0;
}
