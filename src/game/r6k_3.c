/* Area r6k: demo task list loader (r6k_3). Names inferred. */
#include "r6k.h"

/* 0x0008B9E0: build a task list from serialized records. Each record starts
   with the header R6kRec; its stored size comes from the kind's descriptor
   table (a8b_descGetters[kind]()[sub].size). Kind 6 sub 1 records are
   skipped. For the others a task is created (0x0008B980); mode 0x64 copies
   the record into the task's work block and for kind 8 sub 1 moves bits
   24..27 of +0x10 down from bits 28..31 (top byte cleared first); mode 0x65
   only copies. A link index at +0x08 (cleared) is resolved against `parent`
   (0x0007F390) and attached (0x0008B3B0). Each task is inserted after the
   previous one (0x0007F3F0). The list ends at kind -1; *out then gets the
   first task (0x0007F330). Returns the bytes used (+0x10 for the end
   record), or -1 on bad arguments, a failed task, or an overrun (then the
   tasks are freed and *out is cleared). */
int r6k_TaskListLoad(R6kTask **out, const uint8_t *data, int size, void *parent, int mode)
{
    int result = 0;
    int used = 0;
    const uint8_t *cur;
    const R6kRec *rec;
    R6kTask *task, *r;
    R6kRec *w;
    int len, link;

    if (out == 0)
        return -1;
    if (data == 0 || size <= 0)
        return -1;
    *out = 0;
    cur = data;
    rec = (const R6kRec *)cur;
    while (rec->kind != -1) {
        len = a8b_descGetters[rec->kind]()[rec->sub].size;
        if (rec->kind == 6 && rec->sub == 1) {
            cur += len;
            used += len;
        } else {
            task = sub_0008B980(rec->kind, rec->sub);
            if (task == 0) {
                result = -1;
                break;
            }
            w = task->work;
            switch (mode) {
            case 0x64:
                sub_0007F210(w, rec, len);
                if (w->kind == 8 && w->sub == 1) {
                    uint32_t hi = w->bits.u >> 4;
                    w->bits.b[3] = 0;
                    w->bits.u |= hi & 0x0F000000;
                }
                break;
            case 0x65:
                sub_0007F210(w, rec, len);
                break;
            }
            cur += len;
            used += len;
            link = w->link;
            w->link = 0;
            if (link >= 0)
                a8b_SetLink(w, a6b_Node_Nth(parent, link));
            r = (R6kTask *)sub_0007F3F0(*out, task);
            if (r == 0) {
                result = -1;
                break;
            }
            *out = r;
        }
        rec = (const R6kRec *)cur;
    }
    used += 0x10;
    *out = a6b_Node_First(*out);
    if ((unsigned int)used > (unsigned int)size)
        result = -1;
    if (result != 0) {
        r6f_TaskFreeChain(*out);
        *out = 0;
        return result;
    }
    return used;
}
