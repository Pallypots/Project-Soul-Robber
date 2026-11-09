#ifndef AF0_H
#define AF0_H
#include "oogie.h"

/* Event-script interpreter context passed to the opcode handlers at
 * 0x000DC180..0x000DC700. Handlers return a status word: 0x1000 = branch
 * taken (pc already moved), 0x2000 | n = done, skip n operand bytes
 * (Hypothesis), 0x3000 = wait and retry next frame (Hypothesis). */
typedef struct Af0Script {
    int32_t  unk00;
    uint8_t *pc;            /* +0x04 operand pointer */
} Af0Script;

/* Signed little-endian 16-bit operand. */
#define AF0_RD16(p) ((int16_t)((p)[1] << 8) | (p)[0])

/* Script variables (0x003EDCBC..) */
extern int32_t af0_var3EDCBC, af0_var3EDCC0, af0_var3EDCC4, af0_var3EDCC8;
extern int32_t af0_vars3EDCD4[];
extern int32_t af0_var3EDCE8, af0_var3EDCEC, af0_var3EDCF0, af0_var3EDCF8, af0_var3EDCFC;
extern int32_t af0_var3EDD18, af0_var3EDD1C;
extern int32_t af0_var3EE6A8, af0_var3EE6AC, af0_var3EE6C0;
extern int32_t af0_var3F0734, af0_var3F0738, af0_var3F073C;

int  af0_GetVar3EDCBC(void);            /* 0x000DDE60 */
void af0_SetVar3EDCBC(int v);           /* 0x000DDE70 */
int  af0_GetVar3EDCC0(void);            /* 0x000DDE80 */
void af0_SetVar3EDCC0(int v);           /* 0x000DDE90 */
int  af0_GetVar3EDCC4(void);            /* 0x000DDEA0 */
void af0_SetVar3EDCC4(int v);           /* 0x000DDEB0 */
int  af0_GetVar3EDCC8(void);            /* 0x000DDEC0 */
void af0_SetVar3EDCC8(int v);           /* 0x000DDED0 */
void af0_SetVarSlot(int i, int v);      /* 0x000DDEE0 */
int  af0_GetVar3EDCE8(void);            /* 0x000DE490 */
void af0_SetVar3EDCE8(int v);           /* 0x000DE4A0 */
int  af0_GetVar3EDCEC(void);            /* 0x000DE4B0 */
void af0_ClearVar3EDCEC(void);          /* 0x000DE4C0 */
int  af0_GetVar3EE6AC(void);            /* 0x000DFDF0 */

void sub_000DE400(int v);
void sub_000DFC90(void);
void sub_000E03E0(int v);
void sub_00172A30(int v);
void sub_000D7480(int v);
int  sub_000D74D0(void);
void sub_000D7100(int v);
int  sub_000D71E0(void);
int  sub_000D8750(void);
void sub_0003FC10(int32_t *p);
#endif
