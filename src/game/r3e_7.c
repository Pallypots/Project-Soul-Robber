/* Area r3e: game functions in 0x00140000..0x0015FFFF kept apart from their callees (r3e_7). Names inferred. */
#include "r3e.h"

/* 0x00154C80: wait for the node's time (frame of act's +0x5C clock when node->f18 is 0, else
   animation time node->f10), then run 0x00147780 with mode node->f14, mark the node request done
   and free it. calls 0x00147780 with EAX=act (obj and mode on the stack). */
void r3e_Wait154C80(R3eObj *obj, R3eObj *act, R3eNode *node)
{
    int hit;

    if (node->f18 == 0.0f)
        hit = r3e_InFrame145730(act->f5C, (unsigned int)node->f10);
    else
        hit = sub_00145780(obj, node->f10);
    if (hit) {
        sub_00147780(act, obj, R3E_FTOI(node->f14));
        if (node->i00 != 0)
            node->i00 = 1;
        sub_00113370(act, node);
    }
}
