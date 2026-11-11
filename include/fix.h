#ifndef FIX_H
#define FIX_H
#include <stdint.h>
/* Area fix: callers that were blocked by wrong callee signatures in r3c.h
   (0x000ED630 result, 0x0018E270 register arguments, 0x00145940/0x001459D0
   float arguments). All names inferred. Register mappings are in the comments
   and in config/function_states_fix.csv. */

/* Work blocks hung off an actor at +0x278 (different actor kinds, only touched fields). */
typedef struct FixWork {
    uint8_t  unk00[0x0C];
    int32_t  i0C;            /* +0x0C */
    uint8_t  unk10[0x50 - 0x10];
    uint8_t  b50;            /* +0x50 bit 0: turn direction */
    uint8_t  unk51[0x78 - 0x51];
    float    v78[4];         /* +0x78 centre point */
    float    f88, f8C, f90, f94, f98, f9C; /* +0x88..+0x9C */
    uint8_t  unkA0[0x144 - 0xA0];
    float    f144;           /* +0x144 x */
    float    f148;
    float    f14C;           /* +0x14C z */
} FixWork;

typedef struct FixBlk74 {
    uint8_t  unk00[0x0C];
    float    v0C[4];         /* +0x0C direction */
} FixBlk74;

/* Object / actor / component (shared header layout). */
typedef struct FixObj {
    uint8_t  unk000[0x0C];
    uint32_t flags0C;        /* +0x00C */
    uint8_t  unk010[0x20 - 0x10];
    uint8_t  b20;            /* +0x020 */
    uint8_t  unk021[0x60 - 0x21];
    float    pos60[4];       /* +0x060 position */
    uint8_t  unk070[0x74 - 0x70];
    FixBlk74 *p74;           /* +0x074 */
    uint8_t  unk078[0x124 - 0x78];
    int32_t  i124;           /* +0x124 */
    uint8_t  unk128[0x278 - 0x128];
    FixWork *work278;        /* +0x278 */
} FixObj;

/* Condition argument record (+0x10/+0x14 range, +0x18 value). */
typedef struct FixRange {
    int32_t i00, i04, i08, i0C;
    float   lo;              /* +0x10 */
    float   hi;              /* +0x14 */
    float   val;             /* +0x18 */
} FixRange;

typedef struct FixRec54 { FixObj *obj; uint8_t unk04[0x54 - 4]; } FixRec54;
typedef struct FixGame { uint8_t unk000[0x324]; int32_t i324; } FixGame;

/* ---- globals (names shared with the areas that first used them) */
extern FixRec54 r3c_recs3FDC70[6];       /* 0x003FDC70 */
extern void    *g_playerObj;             /* 0x00420E98, Jack's model node */
extern float    a50_frameSeconds;        /* 0x0042C85C */

/* ---- callees (stack arguments unless stated) */
void    *sub_000ED630(int type, int id, const float *pos, const float *rot, int e);
FixObj  *sub_0001D960(void *o, int kind);
FixGame *sub_000E0770(void);
void     sub_0018E270(FixObj *obj, FixObj *c, int k);   /* obj=ESI c=EAX k=stack */
void     sub_00189DA0(void *a, void *b, int c);
void     sub_001AD7E0(float *d, const float *s);          /* normalise */
void     sub_001ADB60(float *d, const float *s, float k);
void     sub_001AD9F0(float *d, const float *a, const float *b); /* d = a - b */
void     sub_001ADAF0(float *d, const float *a, const float *b); /* d = a + b */
void     sub_001ADBA0(float *d, const float *s, float k);  /* d = s * k */
int      sub_00145940(void *obj, float x, float z, float lo, float hi);
void     sub_001459D0(void *obj, float x, float z, float v);
void     sub_00145C50(float *d, const float *s, float angle); /* rotate s about Y */
void     sub_00145F40(void *obj, int part, float *m);     /* world matrix of a part */
float    sub_001B2770(const float *a, const float *b);    /* distance */
void     sub_000F5D40(float *d, const float *s);          /* copy vector */
void    *sub_000E23F0(int a, int b);

#endif
