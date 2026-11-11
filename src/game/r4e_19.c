/* Area r4e: node initialisers at 0x001B2FE0 and 0x001B3450 (r4e_19). Names inferred. */
#include "r4e.h"

/* 0x001B2FE0: initialise a kind 1 node: cleared state, colour 128,128,128,128 and
   the 0x44 / 0x5000D parameters. Stack arg (n); returns n. */
R4eNode1 *r4e_Node1Init(R4eNode1 *n)
{
    n->kind8C = 1;
    r4e_SubNodeBase(n);
    n->iB0 = 0;
    n->iB4 = 0;
    n->iB8 = 0;
    n->iBC = 0;
    n->iC0 = 0;
    n->iC4 = 0;
    n->iC8 = 0;
    n->iE4 = 0;
    n->iEC = 0;
    n->colCC[0] = 128.0f;
    n->colCC[1] = 128.0f;
    n->colCC[2] = 128.0f;
    n->colCC[3] = 128.0f;
    n->iE0 = 0x44;
    n->iE8 = 0x5000D;
    return n;
}

/* 0x001B3450: initialise a kind 14 node with unit factors. Stack arg (n). */
void r4e_Node14Init(R4eNode14 *n)
{
    n->kind8C = 0xE;
    r4e_SubNodeBase(n);
    n->fD0 = 1.0f;
    n->fBC = 1.0f;
    n->fC0 = 1.0f;
    n->fC4 = 1.0f;
    n->fC8 = 1.0f;
    n->fD4 = 1.0f;
    n->iB8 = 0x191;
    n->iCC = 0;
    n->fD8 = 0.0f;
}
