/* Area r6, group 4: object list refresh (0x0007A980..0x0007B060). Names inferred. */
#include "r6.h"

/* 0x0007A980: for every node of obj's list (+0x204 -> +4), copy obj's +0x184 transform
   into the item's +0x20 target (+0x30) via 0x1ADB40 and set its +0x3C to 1.0.
   regargs: obj=EBX */
void r6_ObjRefreshList(R6ListOwner *obj)
{
    R6ListNode *n;
    for (n = obj->list204->first04; n; n = n->next) {
        R6ListItem *it = n->item0C;
        if (it && it->target20) {
            r6_Mat1ADB40(it->target20->mat30, obj->mat184);
            it->target20->f3C = 1.0f;
        }
    }
}

