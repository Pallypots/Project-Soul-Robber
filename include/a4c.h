#ifndef A4C_H
#define A4C_H
#include "oogie.h"
#include "a30.h"

/* 8-byte sound slots at 0x003DFEA0, 4 entries (end bound 0x003DFEC4 seen in loops). */
typedef struct A4cSoundSlot {
    int32_t id;       /* +0x00  sound id, -1 when free */
    int32_t handle;   /* +0x04  playback handle, -1 when free */
} A4cSoundSlot;
#define A4C_SOUND_SLOTS 4

/* Memory block header: when used, +0x04 is the end of the data; otherwise +0x2C holds the size. */
typedef struct A4cBlock {
    int32_t  used;     /* +0x00 */
    uint8_t *end;      /* +0x04 */
    uint8_t  unk08[0x2C - 0x08];
    int32_t  size;     /* +0x2C */
} A4cBlock;

extern A4cSoundSlot a4c_soundSlots[];
extern int32_t      a4c_g3DFEC8;
extern int32_t      a4c_g3DFFF8;
extern int32_t      a4c_g3E0DB0, a4c_g3E0DC0, a4c_g3E0DC4, a4c_g3E0DCC;
extern void (*a4c_fnTbl2C8890[])(void);
extern int  (*a4c_fnTbl2C88AC[])(void);
extern int  (*a4c_fnTbl2C88B4[])(void);
extern int  (*a4c_fnTbl2C88BC[])(void);
extern int  (*a4c_fnTbl2C88C4[])(void);
extern int  (*a4c_fnTbl2C88CC[])(void);
extern int  (*a4c_fnTbl2C88D4[])(void);

int  sub_00057E90(void);
void sub_0019AE90(void);
int  sub_0019A040(int i);
int  sub_0019A180(int i);
int  sub_00199880(int h);
int  sub_0019A810(int h);
int  sub_0019A930(int h);
int  sub_00199850(int h);
int  sub_0019A7E0(int h);
int  sub_0019A900(int h);
void sub_00199A40(int h, int a);
void sub_0019A8B0(int h, int a);
void sub_0019AA00(int h, int a);
void sub_00199980(int h, int a);
void sub_0019AB40(int h);
void sub_0019A5A0(int ch, int v);
void sub_0019A640(int ch, int v);
void sub_0019A6A0(int ch);
int  sub_0019ADE0(int id);
int  sub_0019AD10(int id, int i);
void sub_0019AC20(int h, int i, int v);
void sub_0019B800(int h, int v);
int  sub_0019B9A0(int code);
int  sub_0019A480(int i);
void sub_0019B690(int i, int a, int b, int c, int d, int e);
int  sub_0019B6A0(int id, int a, int b);
void sub_00047DA0(int a, int b);
void a4c_StreamStop(int a);
void a4c_SoundApplyParams(int i);

/* Intrusive doubly linked list (0x0003D880 family). */
struct A4cList;
typedef struct A4cNode {
    struct A4cNode *next;    /* +0x00 */
    struct A4cNode *prev;    /* +0x04 */
    struct A4cList *owner;   /* +0x08 */
    void           *data;    /* +0x0C  compared by the default matcher */
} A4cNode;
typedef struct A4cList {
    int32_t  count;          /* +0x00 */
    A4cNode *head;           /* +0x04 */
    A4cNode *tail;           /* +0x08 */
} A4cList;
typedef int (*A4cNodeFn)(A4cNode *n, int arg);

/* 0x30-byte record inside a group header. */
typedef struct A4cRec30 {
    uint8_t unk00[0x10];
    union { int32_t i; float f; } f10;   /* +0x10 */
    union { int32_t i; float f; } f14;   /* +0x14 */
    uint8_t unk18[0x30 - 0x18];
} A4cRec30;
/* Group header: count at +0x08, four 0x30 records at +0x10, 0x20-byte data records at +0xD0. */
typedef struct A4cGroupHdr {
    uint8_t  unk00[8];
    int32_t  count;          /* +0x08 */
    uint8_t  unk0C[4];
    A4cRec30 recs[4];        /* +0x10 */
} A4cGroupHdr;

extern A4cGroupHdr *a4c_groupHdr[];     /* 0x003DDCC0, 2 entries */
extern A4cList      a4c_groupList;      /* 0x003DDCC8 */
extern uint8_t     *a4c_groupData[];    /* 0x003DDCD8 */
extern A4cRec30    *a4c_groupRecs[];    /* 0x003DDCE0 */
extern A4cNode      a4c_groupNodes[][64]; /* 0x003DDCF0 */
extern int32_t      a3c_g3DDCE8;
extern uint32_t     a3c_flags3DE4F8;
extern int32_t      a4c_sel3DE7EC[];
extern int32_t      a4c_g3DE7E4, a4c_g3DE7E8, a4c_g3DE800, a4c_g3DE804;

/* Menu option value: kind 2/3 int, 4 index, 5 bool, 6 float. */
typedef union A4cVal { int32_t i; float f; } A4cVal;
typedef struct A4cOption {
    uint8_t unk00[8];
    int32_t kind;            /* +0x08 */
    uint8_t unk0C[4];
    A4cVal  value;           /* +0x10 */
    A4cVal  min;             /* +0x14 */
    A4cVal  max;             /* +0x18 */
} A4cOption;
/* 0x24-byte menu entry; a zero first field ends the table. */
typedef struct A4cOptEntry { int32_t f00; uint8_t unk04[0x20]; } A4cOptEntry;
typedef struct A4cMenuDef {
    const char  *name;       /* +0x00 */
    void        *handler;    /* +0x04 */
    A4cOptEntry *entries;    /* +0x08 */
} A4cMenuDef;
typedef struct A4cRefCount { uint8_t unk00[4]; int32_t count; } A4cRefCount;   /* count at +0x04 */
typedef struct A4cTarget { uint8_t unk00[0x14]; int32_t f14; } A4cTarget;
typedef struct A4cMenuItem {
    uint8_t      unk00[4];
    int32_t      index;      /* +0x04 */
    uint8_t      unk08[0x20];
    int32_t      f28;        /* +0x28 */
    uint8_t      unk2C[4];
    A4cRefCount *ref;        /* +0x30 */
    A4cTarget   *target;     /* +0x34 */
    A4cMenuDef  *def;        /* +0x38 */
} A4cMenuItem;
typedef struct A4cElem {
    uint32_t flags;          /* +0x00 */
    uint8_t  unk04[0x14];
    int32_t  x;              /* +0x18 */
    int32_t  y;              /* +0x1C */
} A4cElem;
typedef struct A4cTextBox {
    uint8_t unk00[4];
    int32_t state;           /* +0x04 */
    int32_t text;            /* +0x08 */
    float   scale;           /* +0x0C */
    uint8_t unk10[0x0C];
    int32_t f1C;             /* +0x1C */
} A4cTextBox;
extern const char a4c_strFmtBracket[];   /* 0x00266FB0 "[%s]\n" */
extern const char a4c_strMenu[];         /* 0x00266FB8 "MENU" */
extern int32_t   *a4c_pg2C4B08;
extern int32_t    a4c_g2C4BA4;
void sub_0003EC30(A4cOption *o, int a, int b, int c, int d, int e);
void sub_0003F880(int a, void *p, int code);
void sub_0002E8C0(int a, int b, int c, int g, int d, int e, const char *fmt, const char *s);
int  sub_0003EF00(A4cOptEntry *e, int v);
A4cElem *sub_0003F8B0(int a, int b, int c);
void sub_00075F00(int t);
void a60_TextClear(int t);
int  sub_0003FAF0(int a, int b, int c, int d, int e, int f);

extern int32_t  a4c_mode3DF1EC;
extern int32_t  a4c_g3DFA5C;
extern uint8_t  a4c_buf2B4D84[];
extern uint32_t a4c_flagsA[];       /* 0x004133FC */
extern uint32_t a4c_flagsB[];       /* 0x00413408 */
extern int32_t  a4c_state3E0000[];
extern uint8_t  a4c_obj428F40[];
extern int32_t  a4c_g3E0DBC;
void sub_00043EE0(void);
void sub_00044B90(void);
void sub_000450F0(void);
void sub_00045480(void);
void sub_000459E0(void);
void sub_0003FCE0(void *p);
void sub_00049000(void);
void sub_00049250(void);
void sub_00047FB0(void);
void sub_000483D0(void);
void sub_00039650(void);
void sub_00037130(void);
void sub_00072EE0(void *o, int a, float t, int b);
void sub_00053880(int r);

int  sub_0003DBA0(A4cNode *n, int arg);
void sub_001A7430(void);
void sub_001B9720(void);
void a4c_ListAppend(A4cList *list, A4cNode *node);
void a4c_ListRemove(A4cNode *node);
A4cNode *a4c_ListFind(A4cList *list, A4cNodeFn fn, int arg);
#endif
