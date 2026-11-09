/* Area a6b, group 2: 0x0007E120..0x0007F4EA callers of group 1. Names inferred. */
#include "a6b.h"

/* 0x0007E120: free the ten tracks of a set. */
int a6b_TrackSet_Free(A6bTrackSet *s)
{
    int i;
    if (s != 0)
        for (i = 0; i < 10; i++)
            a6b_Track_Free(&s->tracks[i]);
    return 0;
}

/* 0x0007E150: load the ten tracks of a set from consecutive data. */
float *a6b_TrackSet_Load(A6bTrackSet *s, float *data)
{
    int i;
    if (s == 0)
        return 0;
    for (i = 0; i < 10; i++) {
        data = a6b_Track_Load(&s->tracks[i], data);
        if (data == 0)
            return 0;
    }
    return data;
}

/* 0x0007EC20: unlink a node and release it. */
int a6b_Node_Release(A6bNode *n)
{
    if (n != 0) {
        a6b_Node_Unlink(n);
        sub_0007EAD0(n);
    }
    return 0;
}

/* 0x0007F4C0: allocate from the heap registered for a kind. */
void *a6b_AllocAt(int kind, int align, int size, int line, const char *file)
{
    return a6b_HeapAlloc(a6b_GetHeap(kind), align, size, line, file);
}
