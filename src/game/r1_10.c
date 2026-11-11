/* Area r1, group 10: key-table sound wrappers 0x000487F0..0x000489D0. Names inferred.
   Each calls 0x00048470 (EBX=a EDI=b stack=k) or 0x000484B0 (EBX=a EDI=b). */
#include "r1.h"

/* 0x000487F0: start the sound of key (a,b,k) when present. calls 0x00048470 with EBX=a EDI=b stack=k */
void r1_KeyPlayA(int a, int b, int k)
{
    int v = r1_KeyWord(a, b, k);
    if (v != -1) sub_0019B5C0(v);
}
/* 0x00048820: state of the sound of key (a,b,k); 2 when absent. calls 0x00048470 with EBX=a EDI=b stack=k */
int r1_KeyStateW(int a, int b, int k)
{
    int v = r1_KeyWord(a, b, k), r;
    if (v != -1 && (r = sub_00199CA0(v)) != 2) return r;
    return 2;
}
/* 0x00048860: stop the sound of key (a,b,k) when present. calls 0x00048470 with EBX=a EDI=b stack=k */
void r1_KeyStopW(int a, int b, int k)
{
    int v = r1_KeyWord(a, b, k);
    if (v != -1) sub_00199EB0(v);
}
/* 0x00048890: query the sound of key (a,b,k); 0 when absent. calls 0x00048470 with EBX=a EDI=b stack=k */
int r1_KeyQueryW(int a, int b, int k)
{
    int v = r1_KeyWord(a, b, k);
    if (v == -1) return 0;
    return sub_00199F70(v);
}
/* 0x000488C0: release the sound of key (a,b,k) when present. calls 0x00048470 with EBX=a EDI=b stack=k */
void r1_KeyReleaseW(int a, int b, int k)
{
    int v = r1_KeyWord(a, b, k);
    if (v != -1) sub_0019B5F0(v);
}
/* 0x000488F0: pass the dword of key (a,b) to 0x00047A80. calls 0x000484B0 with EBX=a EDI=b */
int r1_KeyApplyD(int a, int b)
{
    return sub_00047A80(r1_KeyDword(a, b));
}
/* 0x00048910: state of channel key (a,b) when in 3..23, else 2. calls 0x000484B0 with EBX=a EDI=b */
int r1_KeyStateD(int a, int b)
{
    int v = r1_KeyDword(a, b);
    if (v >= 3 && v < 24) return sub_00199CA0(v);
    return 2;
}
/* 0x00048940: stop channel key (a,b) when in 3..23. calls 0x000484B0 with EBX=a EDI=b */
void r1_KeyStopD(int a, int b)
{
    int v = r1_KeyDword(a, b);
    if (v >= 3 && v < 24) sub_00199EB0(v);
}
/* 0x00048970: query channel key (a,b) when in 3..23, else 0. calls 0x000484B0 with EBX=a EDI=b */
int r1_KeyQueryD(int a, int b)
{
    int v = r1_KeyDword(a, b);
    if (v >= 3 && v < 24) return sub_00199F70(v);
    return 0;
}
/* 0x000489A0: release channel key (a,b) when in 3..23. calls 0x000484B0 with EBX=a EDI=b */
void r1_KeyReleaseD(int a, int b)
{
    int v = r1_KeyDword(a, b);
    if (v >= 3 && v < 24) sub_0019B5F0(v);
}
/* 0x000489D0: second query of channel key (a,b) when in 3..23, else 0. calls 0x000484B0 with EBX=a EDI=b */
int r1_KeyQuery2D(int a, int b)
{
    int v = r1_KeyDword(a, b);
    if (v >= 3 && v < 24) return sub_0019B620(v);
    return 0;
}
