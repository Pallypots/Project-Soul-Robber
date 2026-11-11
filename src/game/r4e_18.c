/* Area r4e: node init at 0x001AE970 (r4e_18). Names inferred. */
#include "r4e.h"

/* 0x001AE970: initialise a node as kind 7 with unit scale and cleared state.
   Stack arg (n); returns n. */
R4eNode *r4e_NodeInit(R4eNode *n)
{
    n->kind8C = 7;
    sub_001B25B0(n);
    n->flags90 |= 0x140;
    n->scaleC4 = 1.0f;
    n->iB0 = 0;
    n->iB4 = 0;
    n->iB8 = 0;
    n->iBC = 0;
    n->iC0 = 0;
    n->iC8 = 0;
    n->iCC = 0;
    n->iD0 = 0;
    n->iD4 = 0;
    n->fD8 = 0.0f;
    n->fDC = 0.0f;
    return n;
}
