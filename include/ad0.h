/* Area ad0 (0x000D0000-0x000E0000): event-script opcode handlers.
 * Reference build OOGIE-XBOX-US-RETAIL. Names inferred (Hypothesis). */
#ifndef AD0_H
#define AD0_H
#include "oogie.h"
#include <string.h>

/* Event-script interpreter context passed to every opcode handler. The
 * handler is entered with pc pointing at the operand bytes (after the
 * opcode). Operands are little-endian and unaligned. */
typedef struct ScriptCtx {
    uint8_t *start;          /* +0x00 script start (restart target) */
    uint8_t *pc;             /* +0x04 operand pointer */
    int32_t  unk08;          /* +0x08 */
    int32_t  depth;          /* +0x0C call-stack depth */
    uint8_t *stack[16];      /* +0x10 return addresses */
    float    wait;           /* +0x50 wait timer */
    uint16_t flags;          /* +0x54 script flag bits */
} ScriptCtx;

/* Handler results (Hypothesis from usage):
 * 0x1000 pc already moved (jump), 0x2000+n advance n operand bytes,
 * 0x3000 yield and re-run this opcode, 0x4000 restart, 0x5000+n advance
 * n bytes and yield. */
/* Operand readers (little-endian, unaligned). */
#define OP_S16(p) ad0_ReadS16(p)
static __inline int16_t ad0_ReadS16(const uint8_t *p)
{
    int16_t v;
    memcpy(&v, p, sizeof v);
    return v;
}
#define OP_U32(p) ((((uint32_t)(p)[3] << 8 | (p)[2]) << 8 | (p)[1]) << 8 | (p)[0])

#define SCR_JUMPED      0x1000
#define SCR_NEXT(n)     (0x2000 + (n))
#define SCR_WAIT        0x3000
#define SCR_RESTART     0x4000
#define SCR_NEXTYIELD(n) (0x5000 + (n))

extern uint8_t  g_ad0_scriptVars[0x80];   /* 0x003EDC38, 128-byte save block */
extern int32_t  g_ad0_42CAE0;             /* 0x0042CAE0 */
extern float    g_ad0_waitScale;          /* 0x0042C964 */
extern int32_t  g_ad0_3FD7BC;             /* 0x003FD7BC */
extern int32_t  g_ad0_41316C, g_ad0_413170;

int  sub_000DFD00(void);
void sub_000DFD10(int a);
void sub_0003DD00(void);
void sub_0019D7A0(int a, int b);
void sub_000DFD30(int a);
int  sub_000DDE80(void);
int  sub_000DFDF0(void);
void sub_00032140(int a, int b, int c);
void sub_000A9D40(int a);
int  sub_000A9D80(int a);
int  sub_000D1E10(PlayerStats *s, int index, int delta);
void sub_000408B0(int a);
void sub_000408C0(int a);
void sub_001A0D30(int a, int b);
void sub_000DE330(int a);
int  sub_000EDA50(void);
int  sub_000EDA90(void);
void sub_00060B70(int a);
int  sub_00060BD0(void);
int  sub_0005F860(void);
void sub_000E00D0(void);
void sub_00038070(int a);
int  sub_00086B30(void);
int  sub_00087570(int a, int b);
void sub_000EE0C0(void);
void sub_00047BF0(int a);
void sub_00054160(int a);
void sub_00054170(int a);
void sub_0019E850(void);
void sub_0019D450(int a);
int  sub_000DEA40(void);
#endif
