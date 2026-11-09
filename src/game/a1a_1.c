/* Area a1a, group 1: resource-group wrappers and job messages. Names inferred. */
#include "a1a.h"

/* 0x001A0640: shut down subsystem and clear two state words. */
void a1a_Shutdown_1A0640(void)
{
    sub_001A0320();
    sub_00102FA0();
    a1a_g403960 = 0;
    a1a_g403964 = 0;
}

/* 0x001A0C80: find the record with this id (or the terminator). */
A1aIdRec *a1a_FindId(int id)
{
    int i = 0;
    A1aIdRec *r = a1a_idTable;
    if (r->id != -1) {
        while (r->id != id) {
            r++;
            i++;
            if (r->id == -1)
                break;
        }
    }
    return &a1a_idTable[i];
}

/* 0x001A0CC0: get word 0x4044A4. */
int a1a_Get4044A4(void) { return a1a_g4044A4; }
/* 0x001A0CD0: current 16-byte slot. */
void *a1a_CurSlot(void) { return a1a_g404420 + a1a_g4044A0 * 16; }
/* 0x001A0CE0: current slot index. */
int a1a_Get4044A0(void) { return a1a_g4044A0; }

/* 0x001A0CF0: post a kind-2 message (spins for a free node). */
void a1a_Post2(int a, int b)
{
    A1aJobNode *n;
    A1aJobMsg *m;
    do n = sub_0003DC70(a1a_jobQueue404410); while (n == 0);
    m = n->msg;
    m->a = a;
    m->kind = 2;
    m->b = b;
    sub_0003D880(a1a_jobQueue4044A8, n);
}

/* 0x001A0D30: post a kind-0 message. */
void a1a_Post0(int a, int b)
{
    A1aJobNode *n;
    A1aJobMsg *m;
    do n = sub_0003DC70(a1a_jobQueue404410); while (n == 0);
    m = n->msg;
    m->a = a;
    m->kind = 0;
    m->b = b;
    sub_0003D880(a1a_jobQueue4044A8, n);
}

/* 0x001A0D70: post a kind-1 message with no payload. */
void a1a_Post1(void)
{
    A1aJobNode *n;
    A1aJobMsg *m;
    do n = sub_0003DC70(a1a_jobQueue404410); while (n == 0);
    m = n->msg;
    m->kind = 1;
    m->a = -1;
    m->b = 0;
    sub_0003D880(a1a_jobQueue4044A8, n);
}

/* 0x001A1030: add an entry to a resource group. */
int a1a_GroupAdd(A1aGroup *g, int a, int b, int c, int d, int e)
{
    return sub_00058B00(b, c, d, e, g, g->id, a);
}

/* 0x001A1060: look up key and release its handle (-1 if absent). */
int a1a_GroupReleaseOne(A1aGroup *g, int key)
{
    A1aRes *r = sub_00057FC0(g->id, key);
    if (r == 0)
        return -1;
    return sub_000588D0(r->handle);
}

/* 0x001A1090: look up key and stop its handle. */
void a1a_GroupStopOne(A1aGroup *g, int key)
{
    A1aRes *r = sub_00057FC0(g->id, key);
    if (r != 0)
        sub_000581E0(r->handle);
}

/* 0x001A10C0: look up key and free its handle. */
void a1a_GroupFreeOne(A1aGroup *g, int key)
{
    A1aRes *r = sub_00057FC0(g->id, key);
    if (r != 0)
        sub_00058960(r->handle);
}

/* 0x001A10F0: release every handle in the group. */
int a1a_GroupReleaseAll(A1aGroup *g)
{
    A1aRes *r;
    for (r = sub_00058020(g->id); r != 0; r = sub_00058060(r, g->id))
        sub_000588D0(r->handle);
    return 0;
}

/* 0x001A1130: stop and free every handle in the group. */
void a1a_GroupFreeAll(A1aGroup *g)
{
    A1aRes *r;
    for (r = sub_00058020(g->id); r != 0; r = sub_00058060(r, g->id)) {
        sub_000581E0(r->handle);
        sub_00058960(r->handle);
    }
}

/* 0x001A1170: apply 0x58130 to every handle in the group. */
int a1a_GroupPauseAll(A1aGroup *g)
{
    A1aRes *r;
    for (r = sub_00058020(g->id); r != 0; r = sub_00058060(r, g->id))
        sub_00058130(r->handle);
    return 0;
}

/* 0x001A11B0: apply 0x58910 to every handle in the group. */
int a1a_GroupResumeAll(A1aGroup *g)
{
    A1aRes *r;
    for (r = sub_00058020(g->id); r != 0; r = sub_00058060(r, g->id))
        sub_00058910(r->handle);
    return 0;
}
