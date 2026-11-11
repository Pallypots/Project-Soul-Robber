/* Area adc (0x000D0000-0x000E0000, third pass): event-script opcode
 * handlers. Reference build OOGIE-XBOX-US-RETAIL. Names inferred
 * (Hypothesis). Reuses ScriptCtx and the operand readers from ad0.h. */
#ifndef ADC_H
#define ADC_H
#include "oogie.h"
#include "shared_decls.h"
#include "ad0.h"

/* Little-endian unaligned 32-bit float operand. */
static __inline float adc_ReadF32(const uint8_t *p)
{
    uint32_t u = OP_U32(p);
    float f;
    memcpy(&f, &u, sizeof f);
    return f;
}

/* Signed 16-bit operand assembled from two bytes. */
#define ADC_S16(p) ((int16_t)((p)[1] << 8 | (p)[0]))

extern uint8_t *adc_ctx42C8E4;      /* 0x0042C8E4 */
extern uint8_t  adc_enabled413142;  /* 0x00413142 */

int  sub_000D71E0(void);
void a80_Set3ED238(void);
void a80_Set3ED23C(int v);
int  sub_000D9A70(int id);
void sub_000DE970(void);
void sub_000D9B30(int id);
void sub_000DE6D0(int a, int b, int c);
void sub_0002E410(void);
void sub_000A96D0(void);
int  af0_GetVar3EDCF8(void);
void af0_SetVar3EDCF8(int v);
void af0_SetVar3EDCFC(int v);
int  af0_GetVar3EDCFC(void);
void sub_0002C790(void);
void sub_000A86A0(void);
int  sub_0002CC20(void);
int sub_000DE8E0(int a);
int  sub_00037FE0(void);
void sub_0019C5E0(int a);
void sub_0019C5F0(uint32_t a, uint32_t b, uint32_t c);
void sub_000A86C0(void);
void sub_000DFCC0(int a);
void sub_00026280(int a, int b);
void af0_Release3EE6A8(void);
void sub_00019350(int a, uint32_t b);
void sub_000AA490(int a);
void sub_00048160(int a);
void sub_00048200(int a);
void sub_0005CA80(void);
int a5b_Swap2DD4D8(int a);
void sub_00036FD0(float a);
void sub_00049AA0(int a);
void sub_0019B9E0(void);
void sub_0019B9F0(void);
void sub_00169730(void);
void sub_00169790(void);
extern int32_t  adc_413178;         /* 0x00413178, operand table index */
int  sub_00087AF0(void);
int  sub_00032450(int a);
int  sub_00049B70(void);
void sub_0019E900(int a);
int  sub_00047F60(void);
int  sub_000E03C0(void);
void sub_000DF830(void);
int  sub_000DF8E0(void);
void sub_000A9D00(void);
void a5b_SndStart(int a);
void a5b_SndBegin(void);
void af0_SetVar3EDD1C(int v);
int  sub_0019BE60(int a);
void sub_000264C0(void);
void sub_0003AEB0(int a, int b);

/* Script variable block reset by adc_ResetScriptVars (0x003EDCBC..). */
extern int32_t af0_var3EDCBC, af0_var3EDCC0, af0_var3EDCC4, af0_var3EDCC8;
extern int32_t af0_var3EDCE8, af0_var3EDCF0, af0_var3EDCF8, af0_var3EDCFC;
extern int32_t af0_var3EDD18;
extern int32_t adc_var3EDCCC, adc_var3EDCD0;   /* pair, -2 = locked */
extern int32_t adc_var3EDCF4;
extern int32_t adc_var3EDD00, adc_var3EDD04, adc_var3EDD08, adc_var3EDD0C, adc_var3EDD10;
extern float   adc_var3EDD14;
extern int32_t adc_30D6B8, adc_30D6BC;

typedef struct AdcNode { int32_t unk00; int32_t a; int32_t b; } AdcNode;
AdcNode *sub_000EDB10(int a);
AdcNode *sub_000EDB90(void);
int   aab_Rand(void);
void  sub_000DFD40(int *a, int *b);
void sub_000243B0(int a, int b);
void sub_000251B0(int a, int b);
void sub_000252A0(int a, int b);
void sub_000253D0(int a, int b);
void sub_00025C10(int a, int b);
void sub_00025D50(int a, int b);
void sub_00025F50(int a, int b);   /* callers push 2 args; callee reads only a */
void sub_00025F90(int a, int b);   /* callers push 2 args; callee reads only a */
void aab_Sound260C0(int a, int b, int c);
int a12_Level_37C544(void);
int a12_Level_37D434(void);
int a12_Level_37DAA4(void);
int a12_Level_37DC28(void);
int a12_Level_37DCFC(void);
int a12_Level_37ED04(void);
int a12_Level_37E094(void);
int a12_Level_37EECC(void);
int a12_FlagBit0(void);
int a12_FlagBit1(void);
int a12_AnyBit1(void);

/* Script thread table at 0x003EF034: 64 records of 0x5C bytes; the head
 * matches ScriptCtx. */
typedef struct AdcThread {
    uint8_t *start;          /* +0x00 */
    uint8_t *pc;             /* +0x04 */
    int16_t  id;             /* +0x08 */
    int16_t  pad0A;
    int32_t  depth;          /* +0x0C */
    uint8_t *stack[16];      /* +0x10 */
    float    wait;           /* +0x50 */
    uint16_t flags;          /* +0x54 bit 0: suspended (Hypothesis) */
    uint16_t pad56;
    int32_t  unk58;          /* +0x58 */
} AdcThread;
extern int32_t   adc_threadCount;     /* 0x003EF030 */
extern AdcThread adc_threads[64];     /* 0x003EF034 */
extern int32_t  *adc_scriptTable;     /* 0x00417864, self-relative offsets, -1 ends */
extern void     *adc_3EE6B0;          /* 0x003EE6B0 */
extern int32_t   af0_var3EE6A8, af0_var3F0734, af0_var3F0738, af0_var3F073C, af0_var3EDD1C;

void adc_ClearChannels(void);
void a60_PostCommand(int a, int b);
void sub_000325A0(int a);
void *adc_StatD0030(PlayerStats *s, int v);   /* PlayerObj_D0030 */
int  sub_000E03D0(void);
int a5b_SndPause(void);
void a5b_SndRelease(void);
void sub_000D7590(void);
void sub_0003FC10(void *q);
void sub_0003FC40(void *q);
void a60_FlagBit8(void *o, int v);
void a60_FlagBit1(void *o, int v);
#endif
