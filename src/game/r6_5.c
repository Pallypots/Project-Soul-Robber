/* Area r6, group 5: stack wrapper kept apart from its callee so it is not inlined. Names inferred. */
#include "r6.h"

/* 0x0007B060: stack wrapper; calls 0x0007A980 with EBX=obj. */
void r6_ObjRefreshListW(R6ListOwner *obj) { r6_ObjRefreshList(obj); }

