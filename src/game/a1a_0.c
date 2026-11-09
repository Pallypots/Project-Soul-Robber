/* Area a1a, group 0: resource registration (kept apart from the group helpers). Names inferred. */
#include "a1a.h"

/* 0x001A0930: register a 0x100 resource with handler 0x1A0830 and release it. */
void a1a_Register_1A0930(A1aGroup *g)
{
    a1a_g40396C = 1;
    a1a_GroupAdd(g, 0x100, 0, (int)sub_001A0830, 4, 0x2000);
    a1a_GroupReleaseOne(g, 0x100);
}

/* 0x001A0C40: register two handlers and release the whole group. */
void a1a_Register_1A0C40(A1aGroup *g)
{
    a1a_GroupAdd(g, 0, 1, (int)sub_001A0B80, 8, 0x20000);
    a1a_GroupAdd(g, -1, 4, (int)sub_001A0BD0, 8, 0x20000);
    a1a_GroupReleaseAll(g);
}
