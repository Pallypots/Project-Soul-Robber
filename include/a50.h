/* Declarations for recovered code in 0x00050000-0x0005FFFF (area a50).
 * Reference build OOGIE-XBOX-US-RETAIL. All names INFERRED. VAs in
 * config/symbols_a50.csv. */
#ifndef A50_H
#define A50_H
#include "oogie.h"

/* ---- streaming sound handle at 0x003E0D68 */
extern int32_t a50_streamHandle;          /* 0x003E0D68 file handle number (indexes 0x0040B210) */
extern int32_t a50_streamState;           /* 0x003E0DB8: 0 idle, 10 started, 20 failed */
int  sub_001A8330(int h);
int  sub_001A8500(int h, int which, int *out);   /* h indexes the handle table at 0x0040B210 */

/* ---- video timing */
extern int32_t     a50_videoMode;          /* 0x003E2540 */
extern const char *a50_videoModeNames[];   /* 0x002DCD58 */
extern float       a50_rateHz[];           /* 0x002DCD50: 60, 50 */
extern float       a50_timeScale;          /* 0x002DCD4C */
extern int32_t     a50_frameCounter0;      /* 0x0042C918 */
extern int32_t     a50_frameCounter1;      /* 0x0042C91C */
extern float       a50_frameUnits;         /* 0x0042C858 frame time in 1/60 s units */
extern float       a50_frameSeconds;       /* 0x0042C85C */
extern float       a50_framesPerSecond;    /* 0x0042C964 */
void sub_000527B0(void);
void sub_001BBD70(float units);

/* ---- relocatable table blob (0x00052B00) */
typedef struct A50TableEntry {   /* 0x18 bytes */
    uint8_t unk00[0x10];
    int32_t ptr;                 /* +0x10 offset, rebased to pointer */ /* XBOX32: 32-bit file offset, rebased to a 32-bit pointer in place */
    int32_t id;                  /* +0x14 */
} A50TableEntry;
typedef struct A50Table {
    uint32_t count;              /* +0x00 */
    uint8_t  unk04[0x0C];
    A50TableEntry entries[1];    /* +0x10 */
} A50Table;
typedef struct A50Blob {
    int32_t   unk00;
    int32_t   tableA;            /* +0x04 offset then pointer */ /* XBOX32: 32-bit file offset, rebased to a 32-bit pointer in place */
    int32_t   tableB;            /* +0x08 */ /* XBOX32: 32-bit file offset, rebased to a 32-bit pointer in place */
    uint32_t  flags;             /* +0x0C bit 0: rebased */
} A50Blob;

/* ---- slot memory heaps 0x003E26A8 */
extern int32_t  a50_slotHeap[9];          /* 0x003E26A8 */
extern int32_t  a50_slotSaved[9];         /* 0x003E26D0 */
extern int32_t  a50_heapStack[];          /* 0x003E26F8 */
extern int32_t  a50_heapDepth;            /* 0x003E2800 */
extern int32_t  a50_cacheEntries[];       /* 0x003E2554, 0x14 bytes each */
void *sub_00047040(int heap);
void *sub_00047390(int heap, int size, int a, int b);
void *sub_00047450(int heap, int size, int a, int b);
int   sub_000470C0(int heap);
void  sub_00047140(int heap);
void  sub_00047760(int heap, int size);
void  sub_000471B0(int heap, int size, const char *name, const char *file, int line);
void *sub_000538A0(int heap, const char *file, int line);
void *sub_000531C0(int a, int b);
void  sub_00053760(void);
extern const char a50_strHeapName[];      /* 0x0026BF14 */
extern const char a50_strHeapFile[];      /* 0x0026BED8 */

void *a50_Alloc(int slot, int size, int a, int b);   /* 0x00053820 */
void  a50_ClearCache(void);
void  a50_FreeSlotHeaps(void);

/* ---- 0x003E2808 records */
typedef struct A50Rec44 {
    uint8_t used;                /* +0x00 */
    uint8_t unk01[0x3F];
    int32_t value;               /* +0x40 */
} A50Rec44;
extern A50Rec44 a50_recs[16];             /* 0x003E2808 */
extern int32_t  a50_recCount;             /* 0x003E3908 */
void sub_0004F580(int a, int b);
void sub_0004F4E0(void);
void sub_0004F6F0(void);

/* ---- jobs */
typedef struct A50SubRange { int32_t base; uint32_t size; } A50SubRange;
extern A50SubRange a50_ranges[13];        /* 0x0026C2D0 */
extern void   *a50_loaderThread;          /* 0x003E4698 */
extern int (*a50_jobPoll)(void);          /* 0x003E3F8C */
void *sub_001AD560(void);
int  *sub_00057F30(void);
void  sub_00102FA0(int a);
void  sub_001AD540(void);

#endif
