/* Area m2, file 2: packet builders. Names inferred. */
#include <stdint.h>

typedef struct M2Q2 { uint32_t w[4]; } M2Q2;
typedef struct M2Pkt2 { int32_t *cur; uint8_t unk4[0xC]; } M2Pkt2;
extern int r1b_pktIdx37B4A0;
extern M2Pkt2 r1b_pkts37B4AC[2];
extern int r1b_dma37B390;
extern M2Q2 r1j_gifTag280400[8];
void r1b_PktOp();
void a8c_Release102FA0();
void m1_Stub102FA0();
void r6b_ReturnZero();

/* Packet builders: flip to the other packet buffer, open it (two names for the same debug stub so cl keeps both branch calls), add GIF tag T, write header H with fields 1, N-2 and N-1 cleared, reserve N words and close it. Return the packet cursor. */
#define M2_PKT(NAME, T, H, N) \
int32_t *NAME(void) { \
    M2Pkt2 *p; int32_t *c; \
    r1b_pktIdx37B4A0 ^= 1; \
    p = &r1b_pkts37B4AC[r1b_pktIdx37B4A0]; \
    r1b_PktOp(p); \
    if (r1b_dma37B390) a8c_Release102FA0(p, 0, 0, 0); \
    else m1_Stub102FA0(p, 0, 0, 0); \
    r1b_PktOp(p, r1j_gifTag280400[T]); \
    c = p->cur; \
    c[0] = H; c[1] = 0; c[(N) - 2] = 0; c[(N) - 1] = 0; \
    r6b_ReturnZero(p, N); \
    r1b_PktOp(p); \
    r6b_ReturnZero(p); \
    return c; \
}
M2_PKT(m2_PktTag134E0, 1, 0x154, 0x18)
M2_PKT(m2_PktTag13590, 2, 0x156, 0x10)
M2_PKT(m2_PktTag13640, 4, 0x4b, 0x10)
M2_PKT(m2_PktTag136F0, 5, 0x4d, 0x1c)
M2_PKT(m2_PktTag137A0, 6, 0x4a, 4)

/* 0x13850: same as the builders above with GIF tag 7 and 4 words, but no header is written. */
int32_t *m2_PktTag13850(void) {
    M2Pkt2 *p; int32_t *c;
    r1b_pktIdx37B4A0 ^= 1;
    p = &r1b_pkts37B4AC[r1b_pktIdx37B4A0];
    r1b_PktOp(p);
    if (r1b_dma37B390) a8c_Release102FA0(p, 0, 0, 0);
    else m1_Stub102FA0(p, 0, 0, 0);
    r1b_PktOp(p, r1j_gifTag280400[7]);
    c = p->cur;
    r6b_ReturnZero(p, 4);
    r1b_PktOp(p);
    r6b_ReturnZero(p);
    return c;
}
