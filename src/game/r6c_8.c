/* Area r6c: scene tree reference drops (r6c_8). Names inferred. */
#include "r6c.h"

/* 0x0007EB40: drop one reference; at zero release the children and the node itself.
   calls 0x0007E6C0 with EAX=n->parts */
int r6c_TreeUnref(R6cTNode *n)
{
    if (n && --n->refs == 0) {
        sub_0007F2B0(n);
        r6c_TreeRelease(sub_0007F320(n));
        r6c_NodeRelease(n->parts);
        sub_0007F2B0(n);
        r6c_TreeFreeAll(n);
    }
    return 0;
}

/* 0x0007EB80: create a 0x60-byte tree node for (a, b, c); NULL when the resource is missing.
   calls 0x0007E6C0 with EAX=n->parts */
R6cTNode *r6c_TreeCreate(int a, int b, int c)
{
    R6cTNode *n;
    void *r;
    a6b_SetHeap(4, a6b_GetHeap(6));
    a6b_SetHeap(5, a6b_GetHeap(6));
    n = (R6cTNode *)a6b_Block_Init(0, 0x60, 0x15F, a6b_srcYCharacter);
    if (!n)
        return 0;
    n->refs = 1;
    r = sub_0008FE10(a, b, c);
    if (r) {
        sub_0008F9B0(r);
        return n;
    }
    if (--n->refs == 0) {
        sub_0007F2B0(n);
        r6c_TreeRelease(sub_0007F320(n));
        r6c_NodeRelease(n->parts);
        sub_0007F2B0(n);
        r6c_TreeFreeAll(n);
    }
    return 0;
}
