/* Area r3e: state choosers near 0x00131310 (r3e_2). Names inferred.
   All of them pass obj in EBX and act in EDI on to 0x0012DC90 and 0x00131310. */
#include "r3e.h"

/* 0x00132250: steps 1 and 3 lead to states 0xF and 0x11; otherwise a random roll picks state 6
   or 0x13, favouring 0x13 while health is below half.
   regargs: obj=EBX act=EDI (stack args passed through); calls 0x0012DC90 with EAX=table EBX=obj
   EDI=act and 0x00131310 with EBX=obj EDI=act. */
void r3e_Roll132250(R3eObj *obj, R3eObj *act)
{
    if (sub_0012DC90(1, obj, act)) {
        r3_SetStateA(obj, act, 0xF);
        return;
    }
    if (sub_0012DC90(3, obj, act)) {
        r3_SetStateA(obj, act, 0x11);
        return;
    }
    if (act->f274 >= act->f270 * 0.5f) {
        if (sub_001C7EE1() % 100 < 40) {
            r3_SetStateA(obj, act, 6);
            return;
        }
    } else if (sub_001C7EE1() % 100 >= 75) {
        r3_SetStateA(obj, act, 6);
        return;
    }
    r3_SetStateA(obj, act, 0x13);
}
