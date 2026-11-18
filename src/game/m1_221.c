/* Area m1, file 221: online-session wrappers on a peer record (thiscall, written as __fastcall with an unused EDX). Names inferred. */
#include <stdint.h>

typedef struct M1Peer { uint8_t unk00[0x58]; void *h58; } M1Peer;
int __fastcall sub_001ACF00(M1Peer *p);                       /* p=ECX: is the peer connected */
int __stdcall sub_002226C0(void *h, int a, int *out);
int __stdcall sub_002226F3(void *h, int a, int *out);
int __stdcall sub_00222726(void *h, int a, int b, int c);
int __stdcall sub_0022275D(void *h, int a, int b);

#define M1_E_FAIL ((int)0x80004005)

/* 0x001AA5D0: query 0x2226C0 on the peer's session handle; E_FAIL with *out = 0 when not connected. */
int __fastcall m1_PeerQuery1AA5D0(M1Peer *p, int unusedEdx, int a, int *out)
{
    if (!sub_001ACF00(p)) { *out = 0; return M1_E_FAIL; }
    return sub_002226C0(p->h58, a, out);
}

/* 0x001AA610: same, through 0x2226F3. */
int __fastcall m1_PeerQuery1AA610(M1Peer *p, int unusedEdx, int a, int *out)
{
    if (!sub_001ACF00(p)) { *out = 0; return M1_E_FAIL; }
    return sub_002226F3(p->h58, a, out);
}

/* 0x001AA650: forward (a, b, c) to 0x222726 on the session handle; E_FAIL when not connected. */
int __fastcall m1_PeerCall1AA650(M1Peer *p, int unusedEdx, int a, int b, int c)
{
    if (!sub_001ACF00(p)) return M1_E_FAIL;
    return sub_00222726(p->h58, a, b, c);
}

/* 0x001AA690: forward (a, b) to 0x22275D on the session handle; E_FAIL when not connected. */
int __fastcall m1_PeerCall1AA690(M1Peer *p, int unusedEdx, int a, int b)
{
    if (!sub_001ACF00(p)) return M1_E_FAIL;
    return sub_0022275D(p->h58, a, b);
}
