/* Area ae0 (0x000DB100-0x00100000): event-script opcode handlers and
 * nearby game helpers. Reference build OOGIE-XBOX-US-RETAIL. All names
 * inferred (Hypothesis). */
#ifndef AE0_H
#define AE0_H
#include "oogie.h"
#include <string.h>

/* Event-script interpreter context (same layout as area ad0's ScriptCtx):
 * handlers are entered with pc pointing at the operand bytes. */
typedef struct Ae0Script {
    uint8_t *start;          /* +0x00 */
    uint8_t *pc;             /* +0x04 operand pointer */
} Ae0Script;

/* Handler results (Hypothesis): 0x1000 jumped, 0x2000+n advance n operand
 * bytes, 0x3000 wait and re-run, 0x5000+n advance n bytes and yield. */
#define AE0_JUMPED       0x1000
#define AE0_NEXT(n)      (0x2000 + (n))
#define AE0_WAIT         0x3000
#define AE0_NEXTYIELD(n) (0x5000 + (n))

static __inline int16_t ae0_ReadS16(const uint8_t *p)
{
    int16_t v;
    memcpy(&v, p, sizeof v);
    return v;
}
#define AE0_U32(p) ((((uint32_t)(p)[3] << 8 | (p)[2]) << 8 | (p)[1]) << 8 | (p)[0])

extern uint8_t ae0_flags420010;   /* 0x00420010 */
extern uint8_t ae0_obj3E1270[];   /* 0x003E1270 */
extern void   *ae0_ptr3F6100;     /* 0x003F6100 */

void *sub_000DE170(int a, int b);
void  sub_000325A0(int on);
void  sub_000CF330(void *s, void *v, float f);
void  sub_000D1D00(void *s);
void  sub_0001D700(void *o);
void  sub_000BD4D0(void *s, int a);
void  sub_00019000(void *o, int a);
void  sub_0001AB00(void *o, int a, int b, int c, int d);
void  sub_00036C00(int a, int b, uint32_t c);
int   sub_00036D40(void);
void  sub_00036BC0(void);
void  sub_000F3B70(void *o, int a);
void  sub_00087450(void);
void  sub_000D9020(void);
void  sub_000DDF40(void);
void  sub_000DDEF0(int a, int b);
void  sub_000DDEE0(int a, uint32_t b);
void  sub_000DE530(int a);
void  sub_000DE9E0(int a);
void  sub_000DEA00(int a);
void  sub_000E6CE0(int a);
int   sub_000E5CF0(void);
void  sub_000E5D50(void);
int   sub_000E3370(void);
void  sub_000E4F70(void);
int   sub_000E3050(void);
int   sub_00087AF0(void);
void  sub_00087B00(void);
int   sub_00089040(void);
int   sub_00088150(void);
int   sub_00089010(int a);
void  sub_00087B60(int a);
void  sub_00087B90(void);
void  sub_00087BA0(void);
int   sub_00086290(void);
void  sub_00048590(void);
int   sub_00047950(void);
void  sub_000DFD40(int *a, int *b);
void  sub_000487F0(int a, int b, int c);
void  sub_000488F0(int a, int b);
int   sub_00048910(int a, int b);
void  sub_00048860(int a, int b, int c);
void  sub_00048940(int a, int b);
void  sub_000488C0(int a, int b, int c);
void  sub_000489A0(int a, int b);
int   sub_000489D0(int a, int b);
void  sub_00048110(int a);
void  sub_000481B0(int a);
void  sub_00048270(void);
int   sub_00047F40(void);
int   sub_00047EE0(void);
void  sub_00022750(int a);
int   sub_00022770(void);
void  sub_00174410(void *o);
int   sub_001729D0(void);
void  sub_00174470(int a);
void  sub_001744C0(void);
void  sub_00172A00(void *o, int a);
void  sub_000CEDF0(void *o);
void  sub_000CEDA0(void *o);

#endif
