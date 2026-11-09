/* Area a1a, group 2: misc state, item lists, hook table. Names inferred. */
#include "a1a.h"

/* 0x001A1A70: clear two words. */
void a1a_Clear_1A1A70(void) { a1a_g4046CC = 0; a1a_g4046D0 = 0; }

/* 0x001A1A80: allocate and set up object 0x5F. */
void a1a_Init_1A1A80(void)
{
    sub_00053710(1);
    a1a_g4046BC = sub_0004F680(0x5F);
    a1a_g4046CC = sub_00053AB0(a1a_g4046BC, 0, 0x4B);
    sub_000512D0(0x5F, a1a_g4046CC);
    sub_00053740();
    a1a_g4046D0 = 0;
}

/* 0x001A1CD0: get word 0x4046D0. */
int a1a_Get4046D0(void) { return a1a_g4046D0; }

/* 0x001A1F90: library call bracketed by lock/unlock. */
void a1a_Locked_1A1F90(A1aTriple *t)
{
    sub_001A5300();
    sub_001D3D80(t->a, t->b, t->c);
    sub_001A52F0();
}

/* 0x001A1FB0: library call with the addresses of the three words. */
void a1a_Call_1A1FB0(A1aTriple *t)
{
    sub_001D2F40(t, &t->b, t->c);
}

/* 0x001A1FD0: clear the 0x90-byte record table and return record i. */
A1aRec90 *a1a_ResetRecs(int i)
{
    int n;
    int32_t *p = (int32_t *)a1a_rec404770;
    for (n = 0; n < 0x168; n++) p[n] = 0;
    return &a1a_rec404770[i];
}

/* 0x001A1FF0: clear flag when one of the first three records is passed. */
void a1a_RecCheck(A1aRec90 *r)
{
    if (r == &a1a_rec404770[0] || r == &a1a_rec404770[1] || r == &a1a_rec404770[2])
        a1a_g40AD10 = 0;
}

/* 0x001A2080: call every installed hook with 0 and count the frame. */
void a1a_RunHooks(void)
{
    int i;
    for (i = 0; i < 9; i++)
        if (a1a_hooks40AD1C[i]) a1a_hooks40AD1C[i](0);
    a1a_g40AD44++;
}

/* 0x001A20B0: remove hook slot i. */
void a1a_RemoveHook(int i)
{
    if (a1a_hooks40AD1C[i]) {
        a1a_hooks40AD1C[i] = 0;
        a1a_g40AD40--;
    }
}

/* 0x001A20E0: install a hook in the first free slot; returns slot or 0. */
int a1a_AddHook(A1aHook h, int unused)
{
    int i;
    if (a1a_g40AD40 > 7)
        return 0;
    {
        for (i = 0; i < 8; i++) {
            if (a1a_hooks40AD1C[i] == 0) {
                a1a_hooks40AD1C[i] = h;
                a1a_g40AD40++;
                return i;
            }
        }
    }
    return 0;
}

/* 0x001A2120: swap the special ninth hook slot, returning the old one. */
A1aHook a1a_SwapHook8(A1aHook v) { A1aHook o = a1a_hooks40AD1C[8]; a1a_hooks40AD1C[8] = v; return o; }

/* 0x001A37E0: state is mode 1 (thiscall). */
int a1a_IsMode1(A1aState *s) { return s->mode == 1; }
/* 0x001A37F0: handle valid (thiscall). */
int a1a_HasHandle(A1aState *s) { return s->handle != -1; }

/* 0x001A3800: set state mode from (a, b). */
void OOG_STDCALL a1a_SetMode(int a, int b, A1aStateOwner *o)
{
    A1aState *s = o->st;
    if (a == 0) {
        s->mode = 1;
        s->p38 = b;
    } else {
        s->mode = 2;
        s->p34 = a;
        s->p38 = 0;
    }
}
