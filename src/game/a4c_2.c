/* Area a4c, group 2: resource-loader state machine 0x0004F490..0x0004F7F0. Names inferred. */
#include "a4c.h"

/* 0x0004F490: reset the loader state. */
void a4c_LoaderReset(void)
{
    a4c_g3E0DB0 = 0;
    a30_g3E0DB4 = 0;
    a50_streamState = 0;
    a4c_g3E0DC0 = 0;
    a4c_g3E0DC4 = 0;
    a4c_g3E0DCC = 0;
    a30_g3E0DD0 = 0;
    a30_curSlot = 0;
}
/* 0x0004F4C0: run the handler for the current loader step. */
void a4c_LoaderStep(void)
{
    a4c_fnTbl2C8890[a30_g3E0DB4]();
}
/* 0x0004F660: clear the two link fields of every resource slot. */
void a4c_SlotsClearLinks(void)
{
    int i;
    for (i = 0; i < A30_SLOT_COUNT; i++) { a30_slots[i].f18 = 0; a30_slots[i].f1C = 0; }
}
/* 0x0004F750..0x0004F7F0: run a mode-specific handler; a zero result ends the step. */
void a4c_LoaderOpA(void) { int r = a4c_fnTbl2C88AC[a4c_g3E0DB0](); if (r == 0) a30_g3E0DB4 = r; }
void a4c_LoaderOpB(void) { int r = a4c_fnTbl2C88B4[a4c_g3E0DB0](); if (r == 0) a30_g3E0DB4 = r; }
void a4c_LoaderOpC(void) { int r = a4c_fnTbl2C88BC[a4c_g3E0DB0](); if (r == 0) a30_g3E0DB4 = r; }
void a4c_LoaderOpD(void) { int r = a4c_fnTbl2C88C4[a4c_g3E0DB0](); if (r == 0) a30_g3E0DB4 = r; }
void a4c_LoaderOpE(void) { int r = a4c_fnTbl2C88CC[a4c_g3E0DB0](); if (r == 0) a30_g3E0DB4 = r; }
void a4c_LoaderOpF(void) { int r = a4c_fnTbl2C88D4[a4c_g3E0DB0](); if (r == 0) a30_g3E0DB4 = r; }
/* 0x0004F540: start the loader in the given mode. */
void a4c_LoaderStart(int mode)
{
    a4c_g3E0DB0 = mode;
    a4c_g3E0DBC = -1;
    a4c_g3E0DC0 = 0;
    a4c_g3E0DC4 = 0;
    a30_g3E0DC8 = 0;
    a50_streamState = 0;
    a4c_g3E0DCC = 0;
    a30_g3E0DD0 = 0;
    a30_g3E0DB4 = 1;
}
/* 0x0004F580: queue a request (a,b) when the loader is idle; -1 when busy. */
int a4c_LoaderRequest(int a, int b)
{
    if (a30_g3E0DB4 != 0) return -1;
    a30_g3E0DC8 = 0;
    a50_streamState = 0;
    a4c_g3E0DCC = 0;
    a30_g3E0DD0 = 0;
    a4c_g3E0DBC = -1;
    a4c_g3E0DC0 = a;
    a4c_g3E0DC4 = b;
    a30_g3E0DB4 = 5;
    return 0;
}
/* 0x0004F5D0: free the resource held by slot i; 1 when nothing to free. */
int a4c_SlotFree(int i)
{
    if (i < 0 || i >= A30_SLOT_COUNT || a30_slots[i].f18 == 0) return 1;
    sub_00053880(a30_slots[i].f18);
    a30_slots[i].f18 = 0;
    a30_slots[i].f1C = 0;
    return 0;
}
/* 0x0004F620: forget the resource of slot i without freeing it; 1 when empty. */
int a4c_SlotForget(int i)
{
    if (i < 0 || i >= A30_SLOT_COUNT || a30_slots[i].f18 == 0) return 1;
    a30_slots[i].f18 = 0;
    a30_slots[i].f1C = 0;
    return 0;
}
