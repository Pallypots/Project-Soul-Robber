#ifndef A6B_H
#define A6B_H
#include "oogie.h"

/* Area a6b: second pass over 0x00060000..0x0007FFFF. All names inferred. */

/* Keyframe track (16 bytes). keys points at records of
 * a6b_trackTypes[type].stride floats; the first float of each record is a
 * time, and a negative time terminates the list. */
typedef struct A6bTrack {
    uint32_t flags;         /* +0x00 bit 0: keys owned (freed by Track_Free) */
    int32_t  type;          /* +0x04 index into a6b_trackTypes */
    float   *keys;          /* +0x08 */
    float   *cur;           /* +0x0C cached search position */
} A6bTrack;

/* 0x002E0208: track type descriptors (20 bytes each). */
typedef struct A6bTrackType {
    const char *name;                       /* +0x00 */
    int32_t stride;                         /* +0x04 floats per key */
    float (*eval)(A6bTrack *t, float x);    /* +0x08 */
    void  *fn0C;                            /* +0x0C */
    float (*length)(A6bTrack *t);           /* +0x10 */
} A6bTrackType;
extern A6bTrackType a6b_trackTypes[5];

/* Camera animation block: header then ten tracks at +0x08. */
typedef struct A6bTrackSet {
    uint8_t  unk00[4];
    uint8_t  refs;          /* +0x04 reference count */
    uint8_t  unk05[3];
    A6bTrack tracks[10];    /* +0x08 */
} A6bTrackSet;

/* y_camera.c camera animation object (0xCC bytes). */
typedef struct A6bCamAnim {
    uint8_t  hdr[0x1C];
    int32_t  version;       /* +0x1C must be 0x65 */
    A6bTrackSet set;        /* +0x20 (refs at +0x24) */
} A6bCamAnim;

/* Interpolator: kind selects a6b_lerpOps when flag bit 1 is set. */
typedef struct A6bLerp {
    uint32_t flags;         /* +0x00 */
    int32_t  kind;          /* +0x04 */
    float    a;             /* +0x08 */
    float    b;             /* +0x0C */
} A6bLerp;
typedef struct A6bLerpOp {
    const char *name;
    float (*fn)(A6bLerp *l, float t);
} A6bLerpOp;
extern A6bLerpOp a6b_lerpOps[5];        /* 0x002E0350 */

/* Tree node used by the 0x0007F2B0..0x0007F3AB helpers. */
typedef struct A6bNode {
    uint8_t  unk00[8];
    struct A6bNode *next;   /* +0x08 */
    struct A6bNode *prev;   /* +0x0C */
    struct A6bNode *parent; /* +0x10 */
    struct A6bNode *child;  /* +0x14 first child */
} A6bNode;

/* Character work object (y_character.c). */
typedef struct A6bCharRes { uint8_t unk00[0x0C]; void *handle; } A6bCharRes;
typedef struct A6bChar {
    uint8_t  unk00[0x12C];
    A6bCharRes *res;        /* +0x12C */
} A6bChar;

/* Model part list walked by 0x0007E490..0x0007E5B0. */
typedef struct A6bPartObj {
    uint8_t  unk00[8];
    int32_t  id;            /* +0x08 */
    uint8_t  unk0C[8];
    uint8_t *inst;          /* +0x14 */
} A6bPartObj;
typedef struct A6bPart {
    uint8_t  unk00[0x0C];
    uint8_t  flags;         /* +0x0C */
    uint8_t  unk0D[0x30 - 0x0D];
    A6bPartObj *obj;        /* +0x30 */
    uint8_t  unk34[8];
    struct A6bPart *next;   /* +0x3C */
} A6bPart;
typedef struct A6bPartInfo { uint8_t unk00[0x0C]; int32_t valid; float value; } A6bPartInfo;
typedef struct A6bModel { uint8_t unk00[0x5C]; A6bPart *parts; } A6bModel;

/* Record list node freed by 0x0007E880. */
typedef struct A6bRec {
    uint8_t  unk00[0x0C];
    void    *pC;            /* +0x0C */
    uint8_t  unk10[0x10];
    struct A6bRec *next;    /* +0x20 */
} A6bRec;

typedef struct A6bRef1A { uint8_t unk00[0x1A]; uint8_t refs; } A6bRef1A;

extern int32_t a6b_heaps428F00[];       /* 0x00428F00 heap ids by kind */
extern const char a6b_empty2608A2[];    /* 0x002608A2 "" */
extern const char a6b_strYomCamAnim[];  /* 0x0026F6EC "YOM Camera Animation" */
extern const char a6b_srcYCamera[];     /* 0x0026F708 */
extern const char a6b_srcYCharacter[];  /* 0x0026F730 */
extern int32_t a6b_allocCount3E9308;    /* 0x003E9308 */

void *a50_Alloc(int slot, int size, const char *file, int line);   /* 0x00053820 */
void  a50_SlotEndTemp(int slot);                                    /* 0x00053970 */
void  sub_00053880(void *p);
void *sub_000538A0(int heap, const char *file, int line);
int   sub_000374C0(int a);
int   sub_00037550(int a, int b);
void  sub_0008BCC0(void *p);
int   sub_0007DAF0(char *buf, int size, const char *fmt, void *ap);
int   sub_0007F1E0(void *p, int v, int n);
int   sub_0007F210(void *dst, const void *src, int n);
int   sub_0007F560(void *p, const char *s);
void  sub_0007E1A0(A6bCamAnim *c);
void  sub_0007EAD0(A6bNode *n);
float *sub_0007EF30(A6bTrack *t, float x);
A6bPartInfo *sub_00083120(A6bPartObj *o, int id);
void  sub_001B1190(uint8_t *inst, float v);
void  sub_001AEDD0(uint8_t *inst, float v);
float sub_001A3ED0(float x);
float sub_001A3EE0(float x);

/* recovered here */
int   a6b_Track_Free(A6bTrack *t);
float *a6b_Track_Load(A6bTrack *t, float *data);
void *a6b_HeapAlloc(int slot, int align, int size, int line, const char *file);
int   a6b_TrackSet_Free(A6bTrackSet *s);
float *a6b_TrackSet_Load(A6bTrackSet *s, float *data);
uint8_t *sub_0007E0D0(A6bCamAnim *c, uint8_t *src);
A6bNode *a6b_Node_Unlink(A6bNode *n);
void *a6b_AllocAt(int heap, int align, int size, int line, const char *file);
int   a6b_GetHeap(int kind);
void  a6b_Rec_FreeList(A6bRec *r);
#endif
