/* Area r3b: small helpers and dispatchers in 0x00130000..0x0014FFFF (r3b_1). Names inferred. */
#include "r3b.h"

/* 0x001356C0: release p through 0x000ED780. */
void r3b_Release1356C0(void *p)
{
    sub_000ED780(p);
}

/* 0x00139B10: call dispatcher idx of table 0x0031CDFC with (a, b, its record).
   regargs: idx=EAX b=EDX a=stack. */
int r3b_Dispatch139B10(int idx, void *b, void *a)
{
    return r3b_disp31CDFC[idx](a, b, &r3b_recs279728[idx]);
}

/* 0x0013B950: forward to 0x0013A4A0. */
int r3b_Fwd13B950(void *obj, void *act)
{
    return sub_0013A4A0(obj, act);
}

/* 0x0013BA10: enter state 0x48 and run its setup. */
void r3b_Enter13BA10(void *obj, void *act)
{
    sub_00113090(obj, act, 0x48);
    sub_0013A840(obj, act);
}

/* 0x00140040: call dispatcher idx of table 0x0031D0B8 with (a, b, its record).
   regargs: idx=EAX b=EDX a=stack. */
int r3b_Dispatch140040(int idx, void *b, void *a)
{
    return r3b_disp31D0B8[idx](a, b, &r3b_recs2797C8[idx]);
}

/* 0x00143740: call dispatcher idx of table 0x0031DBBC with (a, b, its record).
   regargs: idx=EAX b=EDX a=stack. */
int r3b_Dispatch143740(int idx, void *b, void *a)
{
    return r3b_disp31DBBC[idx](a, b, &r3b_recs279848[idx]);
}

/* 0x00145A40: forward to 0x001A8830. */
int r3b_Fwd145A40(void *a, void *b)
{
    return sub_001A8830(a, b);
}
