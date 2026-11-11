#ifndef R6B_H
#define R6B_H
#include "oogie.h"
/* Area r6b: small functions (stack and register arguments) in 0x00060000..0x000D0000.
   All names inferred. Register mappings are in the comments and in
   config/function_states_r6b.csv. */

/* ------------------------------------------------------------ intrusive singly linked list */
typedef struct R6bLink { struct R6bLink *next; } R6bLink;
typedef struct R6bList {
    uint32_t count;           /* +0x00 */
    R6bLink *head;            /* +0x04 empty list points at itself */
} R6bList;

/* ------------------------------------------------------------ script processes (0x8D1xx) */
typedef struct R6bProc R6bProc;
typedef struct R6bProcState {          /* 0x00270088, 8-byte records */
    int  (*step)(R6bProc *p);          /* +0x00 returns nonzero to restart */
    void  *aux;                        /* +0x04 */
} R6bProcState;
struct R6bProc {
    uint32_t flags;           /* +0x00 bit 1: restart when done, bit 2: stopped */
    int8_t   state;           /* +0x04 index into r6b_procStates */
    uint8_t  unk05[3];
    int32_t  timer;           /* +0x08 */
    void    *ref;             /* +0x0C */
};
extern R6bProcState r6b_procStates[];  /* 0x00270088 */

/* ------------------------------------------------------------ script tasks (0x8D4xx..0x8Fxxx) */
typedef struct R6bTask {
    uint32_t flags00;         /* +0x00 */
    uint8_t  unk04[0x18 - 0x04];
    uint16_t flags18;         /* +0x18 bit 1 active, bits 2..3 mode */
    uint8_t  unk1A[2];
    void    *p1C;             /* +0x1C */
    int8_t   state;           /* +0x20 2 = idle, 3 = running */
    uint8_t  unk21[2];
    uint8_t  b23;             /* +0x23 */
    union { int32_t i24; struct { uint8_t b24, b25; } bb; } u24;  /* +0x24 */
    union { int32_t i28; void *p28; } u28;                         /* +0x28 */
    int32_t  i2C;             /* +0x2C */
    float    f30, f34;        /* +0x30 */
    uint8_t  unk38[4];
    int32_t  i3C;             /* +0x3C */
    uint8_t  unk40[4];
    float    f44;             /* +0x44 */
    uint8_t  unk48[0x120 - 0x48];
    int32_t  i120;            /* +0x120 */
    int32_t  i124;            /* +0x124 */
} R6bTask;

/* Named table header used by the demo time table task (0x0008D750). */
typedef struct R6bNamed {
    int32_t i00;              /* +0x00 */
    struct { char name[0x1C]; int32_t kind; } hdr;  /* +0x04 name, +0x20 kind */
    int32_t i24;              /* +0x24 */
    int32_t i28;              /* +0x28 */
} R6bNamed;
extern const char r6b_strDemoTimeTable[];       /* 0x00270184 "Demo Time Table" */

/* Task type descriptors returned by the getters at 0x8D410.. (opaque records). */
typedef struct R6bDesc { int32_t size; void *fn[1]; } R6bDesc;
extern R6bDesc r6b_desc2E1130, r6b_desc2E11A0, r6b_desc2E1238, r6b_desc2E12B0, r6b_desc2E1328;
extern R6bDesc r6b_desc270194, r6b_desc2701B8, r6b_desc2701DC, r6b_desc27021C, r6b_desc27026C;
extern R6bDesc r6b_desc2702AC, r6b_desc2702D0, r6b_desc270340, r6b_desc270380, r6b_desc2703A4;
extern R6bDesc r6b_desc2703E4, r6b_desc270420, r6b_desc270474, r6b_desc270498, r6b_desc2704BC;
extern R6bDesc r6b_desc2704E0, r6b_desc270504;

/* Object whose camera animation sits in u28 (0x0008E1B0). */
typedef struct R6bAnimRef { uint8_t unk00[0x5C]; int32_t i5C; } R6bAnimRef;

/* ------------------------------------------------------------ owner of a list block (0x8FF..) */
typedef struct R6bSlot48 { uint8_t unk00[0x20]; void *p20; uint8_t unk24[0x48 - 0x24]; } R6bSlot48;
typedef struct R6bBlkB0 { uint32_t w[0x2C]; } R6bBlkB0;
typedef struct R6bHolderData {
    R6bSlot48 slots[10];      /* +0x000 */
    R6bBlkB0  blk2D0;         /* +0x2D0 */
} R6bHolderData;
typedef struct R6bHolder { R6bHolderData *data; } R6bHolder;

/* refcounted handle (0x8F9xx) */
typedef struct R6bRes {
    uint8_t  unk00[4];
    uint32_t size;            /* +0x04 */
    int32_t  key;             /* +0x08 */
    void    *loaded;          /* +0x0C */
    int32_t  refs;            /* +0x10 */
} R6bRes;
typedef struct R6bRec14 { void *p; uint8_t unk04[0x10]; } R6bRec14;

/* ------------------------------------------------------------ object of 0x7AAxx accessors */
typedef struct R6bRec20 { uint8_t a[0x10]; uint8_t b[0x10]; } R6bRec20;
typedef struct R6bObj7A {
    uint8_t  unk000[0x44];
    int32_t  i44;             /* +0x044 */
    uint8_t  unk048[0xE4 - 0x48];
    R6bRec20 recs[3];         /* +0x0E4 */
    uint8_t  blk144[0x1B8 - 0x144]; /* +0x144 */
    uint8_t  blk1B8[0x1E8 - 0x1B8]; /* +0x1B8 */
    int32_t  i1E8;            /* +0x1E8 */
    int32_t  i1EC;            /* +0x1EC */
} R6bObj7A;

/* ------------------------------------------------------------ actor slots (0x004242C0, 0x260 each) */
typedef struct R6bEnt {
    uint8_t  unk000[0x110];
    int32_t  i110;            /* +0x110 */
    uint8_t  unk114[0x11C - 0x114];
    uint32_t flags11C;        /* +0x11C */
} R6bEnt;
typedef struct R6bEnt40 { uint32_t flags; uint8_t unk04[0x40 - 4]; int32_t i40; } R6bEnt40;

/* ------------------------------------------------------------ misc */
typedef struct R6bP50Sub { uint8_t unk00[0x30]; struct { uint8_t unk00[8]; int32_t index; } sub30; } R6bP50Sub;
typedef struct R6bP50 { uint8_t unk00[0x50]; R6bP50Sub *p50; } R6bP50;
typedef struct R6bFlag8 { uint8_t unk00[8]; uint8_t flags; } R6bFlag8;
typedef struct R6bB4 { uint8_t unk00[0xB4]; uint8_t *recs; } R6bB4;

typedef int (*R6bFn1)(int a);
typedef void (*R6bFn0)(void);
extern int32_t r6b_g3E7A48;             /* 0x003E7A48 */
extern int32_t a60_res3E6540;           /* 0x003E6540 */
extern int32_t a60_mode3E64C0;          /* 0x003E64C0 */
extern uint8_t r6b_obj429050[];         /* 0x00429050 */

/* 24-byte mode records at 0x002E0680. */
typedef struct R6bModeRec { uint8_t b[0x18]; } R6bModeRec;
extern R6bModeRec a80_modeTable[];      /* 0x002E0680 */
extern int32_t a80_curMode;             /* 0x003ED51C */

/* ------------------------------------------------------------ callees */
int   sub_000AD090(void);
void  sub_0008D220(R6bProc *p);
int   sub_00089DD0(void *ref);
void  sub_00089420(void *ref);
void  a80_ForwardSub4C(void *a);
void  a80_ForwardStr(void *a);
void *a80_CurRefX0C(void);
void *a80_Sub4CX1C(void *ref);
void  sub_00089740(void *ref, int b);
void *a80_GetX04(void *p);
void  sub_0008B3E0(void *p);
void  a6b_CamAnim_Release(void *a);
void  a6b_StrCopy(char *dst, const char *src);
void *a6b_Node_Unlink(void *n);
void  sub_0008B400(void *n);
void  sub_0008BF70(void *n);
void *a5b_AllocCur(int size, int a, int tag);
void  sub_0008FB80(void *p);
void  a8c_Release102FA0(void *p);
void *a12_Table_Get(int key, int b);
void *sub_0001F930(uint32_t size, int key);
void  sub_0007F210(void *dst, const void *src, int n);
int   sub_000881B0(R6bModeRec *r);      /* r=ESI */

void  sub_001A1170(void *job);
void  sub_000BCBC0(void *p);
void  sub_00015070(void *p);
int   sub_000398D0(int a, int b);
void  sub_00084B10(int a, int b);
void  sub_00017D30(void);
void  sub_001A1130(void *job);
void  a60_Shutdown77410(void);
void  sub_001A7620(int c);
void  sub_001A7230(void);
void  sub_00034A90(int a);
void  sub_000390B0(void);
void  sub_00039B50(int a);
R6bEnt *sub_000A4290(int i);
void  sub_000A4480(int i, int v);
void  sub_000A43C0(int i, int v);
void  sub_000A41D0(R6bEnt40 *e, int v);
void  sub_001B9FC0(int h);
int   sub_000374C0(void *a);
void  sub_00037550(void *a, int b);
void  sub_00061BC0(void);
void  r4_HookPushA8(void *rec, int b);
int   sub_00080BD0(R6bFlag8 *a, int b);
int   sub_00080B40(R6bFlag8 *a, int b);  /* a=EBX */

#endif
