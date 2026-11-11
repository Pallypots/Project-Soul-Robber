/* Declarations for recovered code in 0x00050000-0x0005FFFF, second pass
 * (area a5b). Reference build OOGIE-XBOX-US-RETAIL. All names INFERRED.
 * VAs in config/symbols_a5b.csv. */
#ifndef A5B_H
#define A5B_H
#include "oogie.h"
#include "a50.h"

/* ---- video timing (see a50.h) */
int  a5b_GetVideoMode(void);

/* ---- cache entries (0x003E2554, see a50.h) */
void a5b_CacheRelease(int32_t *entry);

/* ---- slot heaps */
extern int32_t a5b_heapBase;               /* 0x003E27FC */
extern int32_t a5b_heapSize;               /* 0x003E27F8 */
int32_t sub_001A8630(int size);
void   *sub_00047560(int heap, int a, int b);
void    sub_00047640(int heap);
void    sub_001B9FC0(int handle);

/* ---- effect paths */
void *sub_0008CD60(void);
int  sub_0008CDA0(void *ref);
int  a6b_Printf3(char *buf, int size, const char *fmt, ...);   /* 0x0007E070 */
extern const char a5b_strBg[];             /* 0x0026BE48 "bg" */
extern const char a5b_strHex2[];           /* 0x0026BE88 "%02x" */
extern const char a5b_strDemoEfa[];        /* 0x0026BE4C */

/* ---- streamed sound channel */
extern int32_t  a5b_sndChannel;            /* 0x002DCDB8, -1 = none */
extern int32_t  a5b_sndCount;              /* 0x002DCDBC */
extern uint16_t a5b_sndLevel;              /* 0x002DCDC0 */
void     sub_001A8650(void);
int      sub_001A8680(void);
void     sub_001A8720(void);
void     sub_001A8760(void);
void     sub_000771E0(int ch, int a, int b);
void     sub_000773A0(int ch, int a);
void     a60_ChannelStart(int ch, int (*cb)(int));
void     a60_ChannelStop(int ch);
uint16_t a60_ChannelLevel(int ch);
void     a60_ChannelSetC00(int ch);
int      a5b_SndCallback(int id);

/* ---- misc globals */
extern int32_t a5b_g3E3944, a5b_g3E393C, a5b_g3E3910, a5b_g3E3F4C, a5b_g3E3F48;

/* ---- small records in 0x0005A6D0.. */
typedef struct A5bPair { int32_t unk00; void *value; } A5bPair;
typedef struct A5bTimer {      /* 0x10 bytes */
    int32_t unk00;
    float   rate;              /* +0x04 */
    int32_t unk08;
    int32_t unk0C;
} A5bTimer;
typedef struct A5bSlot {       /* 0x14 bytes */
    int32_t used;              /* +0x00 */
    float   f04;               /* +0x04 */
    int32_t unk08;             /* +0x08 */
    int32_t id;                /* +0x0C, -1 = none */
    int32_t unk10;             /* +0x10 */
} A5bSlot;
typedef struct A5bSlotList {
    int32_t  unk00, unk04;
    int32_t  count;            /* +0x08 */
    A5bSlot *slots;            /* +0x0C */
} A5bSlotList;
void a5b_PairSet(A5bPair *p, void *value);
int  a12_List_Count(void *list);
void *a12_List_At(void *list, int i);
int  sub_0003F9C0(int a, void *b);
extern uint8_t a5b_tbl2DD450[];            /* 0x002DD450 */
extern int32_t a5b_g3E4B54, a5b_g3E4B58;
extern int32_t a5b_g2DD4D8;                /* 0x002DD4D8 */
extern int32_t a5b_g3E6040;                /* 0x003E6040 */
void sub_0005A510(void *a, void *fn);
int  sub_0005BC90(void);
int  sub_0005CAF0(void *p);
void sub_001997E0(int a, int b);
int  sub_0005C430(void *p);
int  sub_0005CD00(void *p, int a, int b);

/* ---- background jobs (0x00057E60..) */
extern uint8_t a5b_jobLists[6][16];        /* 0x003E46E0 */
void *sub_001AD560(void);
void  sub_001AA460(int h);
void  sub_001AD440(void *thread);
void *sub_0003DBC0(void *list, int (*match)(uint8_t *obj, int key), void *key);   /* a4c_ListFind */
int   a50_ObjIdIs(uint8_t *obj, int id);
int   a50_ObjKindIs(uint8_t *obj, int kind);
void  sub_0003D910(void *desc);
void  sub_001A1130(int a);
int   sub_00058B40(int a);

/* ---- 0x0005A400.. / 0x0005EB10.. */
typedef struct A5bRange {      /* 0x14 bytes */
    int32_t unk00, unk04;
    float   f08;               /* +0x08 */
    float   f0C;               /* +0x0C */
    int32_t unk10;
} A5bRange;
typedef struct A5bCell { int8_t a; int8_t n; } A5bCell;
typedef struct A5bChanSub { int32_t a; int32_t b; uint8_t c; uint8_t pad; uint16_t d; } A5bChanSub;
typedef struct A5bChan {       /* 0x1C bytes */
    A5bChanSub sub[2];
    int32_t    unk18;
} A5bChan;
extern A5bCell ***a5b_cellTables;          /* 0x003E6050 */
extern A5bChan   a5b_chans[2];             /* 0x003E6054 */
extern int32_t   a5b_g3E608C;              /* 0x003E608C */
extern int32_t   a60_mode3E64C0;           /* 0x003E64C0 */
extern const char a5b_strShock0[];         /* 0x0026CDE4 */
extern const char a5b_strShock[];          /* 0x0026CDC8 */
int  sub_0005EA60(int a, void *b, float scale);
void sub_0004ED60(int i, int a, int b);
int  a6b_Printf2(char *buf, const char *fmt, ...);             /* 0x0007E0A0 */

#endif
