#ifndef AAC_H
#define AAC_H
#include "oogie.h"

/* ---------------------------------------------------------------- types */
typedef struct AacBlock4 { int32_t a, b, c, d; } AacBlock4;
/* 0x0040CF50: 0x70-byte slot records. */
typedef struct AacSlot70 {
    int32_t id;             /* +0x00, -1 = unused */
    uint8_t unk04[0x25];
    uint8_t active;         /* +0x29 */
    uint8_t unk2A[0x46];
} AacSlot70;
/* 0x0040E604: 0xB4-byte peer records (thiscall objects). */
typedef struct AacPeer {
    uint8_t unk00[0xAC];
    int32_t state;          /* +0xAC */
    int32_t value;          /* +0xB0 */
} AacPeer;
typedef struct AacDVec3 { double x, y, z; } AacDVec3;
typedef struct AacVec3 { float x, y, z; } AacVec3;
/* Short-string-optimised string: inline buffer below 16 chars. */
typedef struct AacStr {
    int32_t unk00;
    union { char buf[16]; char *ptr; } u;   /* +0x04 */
    uint32_t size;          /* +0x14 */
    uint32_t cap;           /* +0x18 */
} AacStr;
/* 0x0040EDD8: 32 thread records of 0x18 bytes (end 0x0040F0D8). */
typedef struct AacThreadRec {
    void   *handle;         /* +0x00 */
    int32_t id;             /* +0x04 */
    int32_t unk08;
    int32_t state;          /* +0x0C */
    int32_t unk10[2];
} AacThreadRec;

/* ---------------------------------------------------------------- globals */
extern AacSlot70 aac_g40CF50[];
extern AacPeer   aac_g40E604[];
extern void     *aac_g40E518[];
extern int32_t   aac_g40E698;
extern void     *aac_g40E690;
extern int32_t   aac_g365158, aac_g36515C, aac_g365160;
extern float     aac_g365170[];
extern AacDVec3  aac_g365228[];
extern AacThreadRec aac_g40EDD8[32];
extern float     aac_g40F130[];
extern float     aac_g40F140[];
extern int32_t  aac_g40B87C;
extern int32_t  aac_g3650C8;          /* current id, -1 = none */
extern int32_t  aac_g3650CC;          /* previous id */
extern uint8_t  aac_g3650D0[];
extern uint8_t  aac_g40B9A4[];
extern int32_t  aac_g40BE18;
extern int32_t  aac_g40C03C;
extern int32_t  aac_g40BF20;
extern int32_t  aac_g40C028;
extern int32_t  aac_g40BF24;
extern char     aac_g40C040[];         /* path buffer */
extern char     aac_g40C044[];
extern char     aac_g40C02C[];
extern int32_t  aac_g1E243C;
extern int32_t  aac_g1E2440;
extern int32_t  aac_g1E2444;
extern void    *aac_g40C858;           /* mutex-like handle */
extern void    *aac_g40C868;
extern int32_t  aac_g40E348;
extern int32_t  aac_g40E350;
extern int32_t  aac_g40E300;
extern uint8_t  aac_g40E6A8;

/* ---------------------------------------------------------------- callees */
void __fastcall sub_001D4350(int reg, int v);
void __fastcall sub_001D2490(int state, int v);
void OOG_STDCALL sub_001D6ED0(int, int, int, int, float, int);
int  OOG_STDCALL sub_001E543D(int, int);
int  OOG_STDCALL sub_001E4DA4(int, int);
int  OOG_STDCALL sub_001E5571(int, int, int, int);
int  sub_001BD792(void);
int  sub_001BD749(void);
int  sub_001BD5B2(void);
void sub_00079340(void);
void OOG_STDCALL sub_0025942D(int, void *);
void sub_001A8AA0(void *);
int  OOG_STDCALL sub_001BDFF2(const char *path, uint64_t *avail, uint64_t *total, uint64_t *free);
int  OOG_STDCALL sub_001BD587(int);
uint32_t OOG_STDCALL sub_001BD1CC(void *h, uint32_t ms);
int  OOG_STDCALL sub_001BCFF2(void *h);
int  sub_001AA3E0(int, int);
int  sub_001AA4D0(int, int);
int  OOG_STDCALL sub_00222726(void *, int, int, int);
int  OOG_STDCALL sub_0022275D(void *, int, int);

int  OOG_STDCALL sub_002226F3(int, void *, int);
void OOG_STDCALL sub_002224A2(void *, int);
void sub_00223F9C(void);
void OOG_STDCALL sub_002225ED(void *, void *);
int  __fastcall sub_001ACF10(AacPeer *);
int  __fastcall sub_001ACF20(AacPeer *);
void OOG_STDCALL sub_002227C3(void *, int);
int  sub_001BEE51(void);
int  OOG_STDCALL sub_002225B2(void *, int);
void sub_001AB4E0(int, int);
void sub_001C885F(void *);
int  sub_001BD50A(void);
void OOG_STDCALL sub_001BD2B6(void *);
void OOG_STDCALL sub_001BD290(void *);
void sub_001AD520(void);
int  OOG_STDCALL sub_001E522D(int, int, void *);
void OOG_STDCALL sub_001E4C33(void *, int);
void OOG_STDCALL sub_001E4CAD(void *, int);
void OOG_STDCALL sub_001E4D28(void *, int);
int  OOG_STDCALL sub_001E4BC6(int, int);
void *OOG_STDCALL sub_001E4B2D(void *out, const void *v, const void *m);   /* D3DX vec4 transform */
void a19_VecOp(float *a, float *b);                 /* 0x000F5D40 */
void sub_001AEBF0(int, int, int);

#endif
