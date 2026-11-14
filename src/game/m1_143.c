/* Area m1, file 143: script opcode helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Vm143 { uint8_t unk00[4]; uint8_t *pc4; } M1Vm143;
extern uint32_t *m1_padMasks2C4AE8;
extern uint32_t m1_btnMask300F88[];
int sub_0019BE60(int f);
uint32_t m1_PadHeld04ECD0(int pad);
uint32_t m1_PadHit04ECE0(int pad);

#define M1_PADMASK143(m, k) switch (k) { case 5: m = m1_padMasks2C4AE8[1]; break; case 7: m = m1_padMasks2C4AE8[0]; break; default: m = m1_btnMask300F88[k]; }
typedef union M1Hi143 { int16_t s; uint8_t b[2]; } M1Hi143;
#define M1_JUMP143(c, p) do { M1Hi143 u_; u_.s = 0; u_.b[1] = (p)[4]; (c)->pc4 = (p) + 3 + (u_.s | (p)[3]); } while (0)

/* Script op: branch when a pad button test (held/hit) is (not) met. */
#define M1_PADOP143(name, fn) \
int name(M1Vm143 *c) { \
    uint8_t *p = c->pc4; int pad = p[0], k = p[1]; uint32_t m; \
    if (p[2] != 0) { \
        M1_PADMASK143(m, k) \
        if ((m & fn(pad)) && sub_0019BE60(0x4001) == 0) { M1_JUMP143(c, c->pc4); return 0x1000; } \
        return 0x2005; \
    } \
    M1_PADMASK143(m, k) \
    if ((m & fn(pad)) && sub_0019BE60(0x4001) == 0) return 0x2005; \
    M1_JUMP143(c, c->pc4); return 0x1000; \
}

/* 0xDA120 / 0xDA210: held and newly-pressed variants. */
M1_PADOP143(m1_OpPadHeld0DA120, m1_PadHeld04ECD0)
M1_PADOP143(m1_OpPadHit0DA210, m1_PadHit04ECE0)

typedef struct M1Obj143 { uint8_t unk00[0x60]; float v60[4]; } M1Obj143;
typedef union M1F143 { uint32_t u; float f; } M1F143;
M1Obj143 *m1_ObjFind0DE170(int a, int b);
int m1_FlagGet0603C0(int id);

/* Read a little-endian float from four script bytes. */
#define M1_RDF143(d, p) do { M1Hi143 h_; h_.b[0] = (p)[2]; h_.b[1] = (p)[3]; \
    (d).u = (((uint32_t)(uint16_t)h_.s << 8 | (p)[1]) << 8) | (p)[0]; } while (0)

/* 0xDAD00: script op, place an object at a position given in the script. */
int m1_OpPlace0DAD00(M1Vm143 *c) {
    M1Obj143 *o = m1_ObjFind0DE170(c->pc4[0], c->pc4[1]);
    if (o != 0) {
        uint8_t *p = c->pc4; M1F143 x, y, z;
        M1_RDF143(x, p + 2); M1_RDF143(y, p + 6); M1_RDF143(z, p + 10);
        o->v60[0] = x.f; o->v60[1] = y.f; o->v60[2] = z.f; o->v60[3] = 1.0f;
    }
    return 0x200E;
}

/* 0xDADF0: script op, compare a flag with a constant and branch. */
int m1_OpFlagCmp0DADF0(M1Vm143 *c) {
    uint8_t *p = c->pc4; int k = p[1];
    switch (p[0]) {
    case 0: if (m1_FlagGet0603C0(p[2]) != k) return 0x2005; break;
    case 1: if (m1_FlagGet0603C0(p[2]) == k) return 0x2005; break;
    case 2: if (m1_FlagGet0603C0(p[2]) < k) return 0x2005; break;
    case 3: if (m1_FlagGet0603C0(p[2]) > k) return 0x2005; break;
    case 4: if (m1_FlagGet0603C0(p[2]) <= k) return 0x2005; break;
    case 5: if (m1_FlagGet0603C0(p[2]) >= k) return 0x2005; break;
    default: return 0x2005;
    }
    M1_JUMP143(c, c->pc4);
    return 0x1000;
}

extern void *m1_eventBms417868;
extern void *m1_talkBms41786C;
extern void *m1_shopBms417874;
extern uint8_t m1_opt413140;
void m1_MsgOpen0DFD60(void *bank, int id, int flags);
void m1_MsgMode0DFEB0(int m);
int  sub_000D9A70(int id);

/* 0xDA300: script op, open a message from one of the text banks. */
int m1_OpMessage0DA300(M1Vm143 *c) {
    uint8_t *p = c->pc4; int kind = p[0], id, f; void *bank; M1Hi143 h;
    h.s = 0; h.b[1] = p[2]; id = h.s | p[1];
    if (kind == 1) { bank = m1_eventBms417868; f = 0x43; }
    else if (kind == 2) { bank = m1_talkBms41786C; f = 0x43; }
    else if (kind == 3) { bank = m1_shopBms417874; f = 0x43; }
    else if (kind == 4) { bank = m1_eventBms417868; f = 0x63; }
    else if (kind == 5) { bank = m1_shopBms417874; f = 0x11; }
    else { bank = m1_eventBms417868; f = 1; }
    m1_MsgOpen0DFD60(bank, id, f);
    if (sub_000D9A70(0xA1) != 0 && m1_opt413140 == 0) { m1_MsgMode0DFEB0(0); return 0x2003; }
    m1_MsgMode0DFEB0(1);
    return 0x2003;
}
