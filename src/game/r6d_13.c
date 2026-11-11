/* Area r6d: string and character loading helpers around 0x0007D4A0-0x0007E9A2 (r6d_13). Names inferred. */
#include "r6d.h"

/* 0x0007D4A0: copy at most max bytes of src (without its terminator) to dst;
   returns dst advanced past the copied bytes.
   regargs: max=EAX src=EBX */
char *r6d_CopyN(char *dst, unsigned max, const char *src)
{
    unsigned len = (unsigned)strlen(src);
    unsigned n = len < max ? len : max;
    sub_001C7DB0(dst, src, n);
    return dst + (n < len ? n : len);
}

/* 0x0007E910: load a character resource into an object and make sure its effect list exists.
   calls 0x0007E680 with EDI=table; 0x0007E720 with EBX=o->chr */
void r6d_CharLoad(int a, int b, int c, R6dCharObj *o)
{
    void *h = sub_0008FDC0(a, b, c);
    void *res = r6b_FwdHolderData(&h);
    R6dChar *chr;
    r6b_ResLoad(res);
    r6d_TableFirstFree(r6b_ResLoaded(res), (void **)&o->chr);
    sub_0007E720(r6b_ResTableEntry(res), o->chr);
    chr = o->chr;
    if (!chr->effects) {
        chr->effects = a6b_AllocAt(1, 4, 0x10, 0x263, a6b_srcYCharacter);
        sub_0003D860(chr->effects);
    }
}
