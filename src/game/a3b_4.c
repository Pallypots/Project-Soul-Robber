/* Area a3b, group 4: helpers near 0x00036260. Names inferred. */
#include "a3b.h"

/* 0x00036260: apply to every node of a pool chain. */
void a3b_PoolApplyF(A3bPNode *n)
{
    for (; n; n = n->next)
        sub_00034F90(n);
}

/* 0x00036290: walk the chain at +0x10 when the owner matches. */
int a3b_CbApplyIfOwner(A3bObj *o, int owner)
{
    if (owner && o->f24 == owner) sub_00036260((char *)o + 0x10);
    return 0;
}

/* 0x00036750: forward with the field at +0x130. */
void *a3b_Fwd130(char *p, int a) { return sub_00035DD0(p, *(void **)(p + 0x130), a, 0); }

/* 0x00036770: forward with mode 4. */
void a3b_FwdMode4(void *p, void *a, int b) { sub_00035DD0(p, a, b, 4); }

/* 0x00036790: forward the range fields. */
void a3b_RangeFwdA(A3bRange *r) { sub_00035FD0(r, r->f04, r->f08); }

/* 0x00036A70: forward the range fields. */
void a3b_RangeFwdB(A3bRange *r) { sub_000368F0(r, r->f04, r->f08); }

/* 0x00036B10: drop a held reference. */
void a3b_HandleRelease(A3bHandle *h)
{
    if (h->flags & 1) {
        h->flags = 0;
        h->ref->refs--;
    }
}

/* 0x00036D40: flag bit 0. */
int a3b_Flag3DA098Bit0(void) { return (int8_t)a3b_g3DA098 & 1; }

/* 0x00036D50: read flags. */
int a3b_GetFlags3DA098(void) { return a3b_g3DA098; }

/* 0x00036D60: address of the object at 0x003DA0A4. */
void *a3b_GetObj3DA0A4(void) { return a3b_obj3DA0A4; }

/* 0x00036FD0: set value unless locked by flag bit 0. */
void a3b_SetF3DA0B0(float v)
{
    if (!(a3b_g3DA098 & 1)) a3b_f3DA0B0 = v;
}

/* 0x00036FF0: read value. */
float a3b_GetF3DA0B0(void) { return a3b_f3DA0B0; }

/* 0x00037550: forward with two zero arguments. */
void *a3b_Fwd373A0(const void *a, void *buf) { return sub_000373A0(a, 0, 0, buf); }

/* 0x00037570: forward with zero arguments. */
void *a3b_Fwd373A0Z(const void *a, int align) { return sub_000373A0(a, 0, 0, 0); }

/* 0x00037780: address of the object at 0x0042CB20. */
void *a3b_GetObj42CB20(void) { return a3b_obj42CB20; }
