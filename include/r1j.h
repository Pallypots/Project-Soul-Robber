#ifndef R1J_H
#define R1J_H
#include "oogie.h"
#include "shared_decls.h"
#include "r1i.h"
#include <string.h>

/* Area r1j: larger game functions 0x00012000..0x00060000 (tenth pass).
   Names inferred. Register-argument mappings are in
   config/function_states_r1j.csv. */

/* float -> int truncation as the original inlines it (cvttss2si) */
#if defined(_M_IX86) || defined(_M_X64)
#include <xmmintrin.h>
#define R1J_FTOI(x) _mm_cvtt_ss2si(_mm_set_ss(x))
#else
#define R1J_FTOI(x) ((int)(x))
#endif

#ifdef _MSC_VER
#define R1J_INLINE static __inline
#else
#define R1J_INLINE static inline
#endif

/* forward copy of n bytes as n/4 dwords then n%4 bytes, one unit at a
   time (source and destination may overlap; the original uses rep movsd
   and rep movsb) */
#if defined(_M_IX86) || defined(_M_X64)
#include <intrin.h>
R1J_INLINE void r1j_CopyFwd(uint8_t *d, const uint8_t *s, uint32_t n)
{
    __movsd((unsigned long *)d, (const unsigned long *)s, n >> 2);
    __movsb(d + (n >> 2) * 4, s + (n >> 2) * 4, n & 3);
}
#else
R1J_INLINE void r1j_CopyFwd(uint8_t *d, const uint8_t *s, uint32_t n)
{
    uint32_t i, w;
    for (i = 0; i < (n >> 2); i++) {
        memcpy(&w, s + 4 * i, 4);
        memcpy(d + 4 * i, &w, 4);
    }
    for (i = n & ~3u; i < n; i++)
        d[i] = s[i];
}
#endif

/* clear n dwords at d (the original inlines rep stosd) */
#if defined(_M_IX86) || defined(_M_X64)
R1J_INLINE void r1j_Zero32(void *d, uint32_t n)
{
    __stosd((unsigned long *)d, 0, n);
}
#else
R1J_INLINE void r1j_Zero32(void *d, uint32_t n)
{
    memset(d, 0, (size_t)n * 4);
}
#endif

/* ------------------------------------------------------------ camera */
void r1j_CamInit(R1iCam *c);                    /* 0x000193F0 */

/* ------------------------------------------------------------ LZ decoder */
/* bit-stream reader state */
typedef struct R1jBits {
    int32_t   limit;            /* +0x00 byte count that triggers a refill, <0 none */
    uint32_t  u04;
    uint32_t *cur;              /* +0x08 current word */
    uint32_t  bit;              /* +0x0C next bit 0..31 */
    int32_t   bytes;            /* +0x10 bytes consumed */
    void    (*fill)(struct R1jBits *bs);   /* +0x14 refill callback */
} R1jBits;
extern const uint32_t r1j_lzBits[4];            /* 0x00260A00 field widths 2 4 6 10 */
void sub_001AB850(void);                        /* thread yield */
void r1j_LzDecode(R1jBits *bs, char mode, uint8_t *dst, uint32_t size);   /* 0x00031120 */

/* ------------------------------------------------------------ packets */
void r1j_QuadTplInit(R1iQuadTpl *p, int tex);   /* 0x00012160 */

extern uint32_t r1j_gifTag2803F0[3];            /* 0x002803F0 quad GIF tag */
extern uint32_t r1j_gifTag280400[3];            /* 0x00280400 quad register GIF tag */
void sub_001A7870(const void *s);               /* 0x001A5560(s, 0) */
void sub_001A7880(const void *s);               /* 0x001A5560(s, 1) */
uint32_t *r1j_QuadPktA(uint32_t *p, const R1iQuadTpl *s);   /* 0x00012710 */
uint32_t *r1j_QuadPktB(uint32_t *p, const R1iQuadTpl *s);   /* 0x00012B50 */

/* ------------------------------------------------------------ model blob */
typedef struct R1jTexEnt {      /* 0x18 bytes */
    const uint8_t *src;         /* +0x00 texture header (+0x20, +0x22 log2 sizes) */
    uint8_t  u04[0x0C];
    void    *handle;            /* +0x10 texture handle */
    int32_t  id;                /* +0x14 */
} R1jTexEnt;
typedef struct R1jTexTable {
    uint32_t count;             /* +0x00 */
    uint8_t  u04[0x0C];
    R1jTexEnt e[1];             /* +0x10 */
} R1jTexTable;
typedef struct R1jMeshPart {    /* 0xF0 bytes */
    uint32_t flags;             /* +0x00 bit 0 enabled, 0x20000 textured */
    uint8_t  u04[0xD4];
    int32_t  texIdx;            /* +0xD8 texture index, <0 none */
    uint32_t maskA;             /* +0xDC */
    uint32_t maskB;             /* +0xE0 */
    uint8_t  uE4[0x0C];
} R1jMeshPart;
typedef struct R1jMeshGroup {
    int32_t      count;         /* +0x00 */
    R1jMeshPart *part;          /* +0x04 */
} R1jMeshGroup;
typedef struct R1jMeshEnt {     /* 0x18 bytes */
    R1jMeshGroup *grp;          /* +0x00 */
    uint8_t  u04[0x14];
} R1jMeshEnt;
typedef struct R1jMeshTable {
    uint32_t count;             /* +0x00 */
    uint8_t  u04[0x0C];
    R1jMeshEnt e[1];            /* +0x10 */
} R1jMeshTable;
typedef struct R1jModel {
    int32_t       u00;
    R1jTexTable  *tex;          /* +0x04 */
    R1jMeshTable *mesh;         /* +0x08 */
    uint32_t      flags;        /* +0x0C */
    void         *firstTex;     /* +0x10 */
    int32_t       state;        /* +0x14 1 = loaded */
} R1jModel;
int r1j_ModelBindTextures(R1jModel *m);         /* 0x00052B60 */

void sub_00052B00(void *p);                     /* rebase blob tables */

/* ------------------------------------------------------------ save data */
typedef struct R1jSaveSlot {    /* 0x80 bytes */
    uint16_t stamp[6];          /* +0x00 time stamp, most significant first */
    uint8_t  u0C[0x74];
} R1jSaveSlot;
typedef struct R1jSave {
    uint8_t     u000000[0x122AB0];
    R1jSaveSlot slot[5];        /* +0x122AB0 */
} R1jSave;
extern R1jSave *r1j_save3E3934;                 /* 0x003E3934 */
int r1j_LatestSaveSlot(void);                   /* 0x00054860 */

/* ------------------------------------------------------------ positional sound */
typedef struct R1jSndVoice {    /* 0x18 bytes */
    uint16_t     active;        /* +0x00 */
    uint16_t     id;            /* +0x02 sound id */
    int16_t      pan;           /* +0x04 pan angle 0..359 */
    int16_t      vol;           /* +0x06 volume 0..255 */
    int32_t      handle;        /* +0x08 channel handle */
    const float *pos;           /* +0x0C source position */
    int32_t      mode;          /* +0x10 0 camera, 1 player relative */
    float        range;         /* +0x14 audible range */
} R1jSndVoice;
extern R1jSndVoice r1j_sndVoices[45];           /* 0x003DFA68 */
extern double      r1j_sndListener[3];          /* 0x003DFFE0 written by 0x00048B70 */
int  sub_0019A540(int ch);                      /* channel handle */
int  sub_0019A580(int h);                       /* sound flag byte 0 */
int  sub_0019A590(int h);                       /* sound flag byte 1 */
int  sub_00199E70(int ch);                      /* channel playing */
void sub_0019A390(int ch, int id, int pan, int vol, float range, const double *listener);
/* volume (0..255) and pan angle of a sound at pos; regargs pos=EAX vol=EDI pan=EBX */
void sub_00048B70(const float *pos, int *vol, int *pan, int mode, float range, int a3, int a4);
void r1j_SndVoicesUpdate(void);                 /* 0x00049000 */

/* ------------------------------------------------------------ jobs */
typedef struct R1jJob {
    int32_t  state;             /* +0x00 0 idle, 3 finished */
    int32_t  thread;            /* +0x04 thread handle, -1 none */
    int32_t  handle;            /* +0x08 slot handle, -1 none */
    int32_t  bucket;            /* +0x0C */
    void    *mem;               /* +0x10 job memory */
    int32_t  d14;               /* +0x14 */
    void   (*done)(void *arg);  /* +0x18 */
    void    *arg;               /* +0x1C */
} R1jJob;
typedef struct R1jJobNode {
    struct R1jJobNode *next;    /* +0x00 */
    uint8_t  u04[8];
    void    *data;              /* +0x0C record holding the job at +0x10 */
} R1jJobNode;
typedef struct R1jJobBucket {
    int32_t     count;          /* +0x00 */
    R1jJobNode *first;          /* +0x04 */
    uint8_t     u08[8];
} R1jJobBucket;
extern R1jJobBucket r1j_jobBuckets[6];          /* 0x003E46E0 */
extern int32_t      r1j_jobBucketCur;           /* 0x003E3F90 */
extern uint8_t      r1j_jobFree3E3F54[1];       /* 0x003E3F54 free node list */
extern R1jJob       r1j_mainJob3E3F64;          /* 0x003E3F64 */
int  sub_00057EF0(void *node, int key);         /* node's job thread == key */
void sub_00053880(void *p);                     /* free job memory */
void sub_0003D880(void *list, void *node);      /* append */
void sub_0003D8C0(void *node);                  /* unlink */
void r1j_JobsKillAll(void);                     /* 0x00058780 */

/* ------------------------------------------------------------ combo display */
extern uint32_t r1j_seqFlags37EDEC;             /* 0x0037EDEC */
extern int32_t  r1j_seqState37EDF0;             /* 0x0037EDF0 */
extern int32_t  r1j_seqState37EDF4;             /* 0x0037EDF4 */
extern int32_t  r1j_g37EE18;                    /* 0x0037EE18 */
extern int16_t  r1j_comboRank37EEBC;            /* 0x0037EEBC */
extern int16_t  r1j_combo37EEBE;                /* 0x0037EEBE */
extern int16_t  r1j_comboRankShown37EEC0;       /* 0x0037EEC0 */
extern int16_t  r1j_comboShown37EEC2;           /* 0x0037EEC2 */
extern int16_t  r1j_comboReset37EEC4;           /* 0x0037EEC4 */
extern int16_t  r1j_comboLast;                  /* 0x0037EEC6 */
extern float    r1j_comboTimer;                 /* 0x0037EEC8 frames */
extern int32_t  r1j_cmdQueue37EECC[8];          /* 0x0037EECC command queue, [0] current */
extern int32_t  r1j_comboPhase;                 /* 0x0037EEEC */
extern uint8_t  r1j_comboByte;                  /* 0x0037EEF0 */
void sub_000720A0(float *t, int mode);          /* frame countdown */
void r1j_ComboStep(void);                       /* 0x0002ACF0 */

/* ------------------------------------------------------------ HUD sequence blocks */
typedef struct R1jGauge {       /* 0x9C bytes */
    float    scaleX;            /* +0x00 */
    float    scaleY;            /* +0x04 */
    uint8_t  u08[0x94];
} R1jGauge;
typedef struct R1jSeqA {        /* 0x0037C4FC, template at 0x0037FB78 */
    uint8_t  u00[0x48];
    int32_t  queue[8];          /* +0x48 command queue, [0] current */
    int32_t  d68;               /* +0x68 */
    uint8_t  u6C[8];
    int32_t  maxHealth;         /* +0x74 */
    int32_t  health;            /* +0x78 */
    int32_t  d7C;               /* +0x7C */
    int32_t  d80;               /* +0x80 */
    uint16_t w84;               /* +0x84 */
    uint16_t w86;               /* +0x86 */
    uint8_t  u88[0x20];
    R1jGauge gauge[15];         /* +0xA8 */
    uint8_t  u9CC[0xF28 - 0x9CC];
} R1jSeqA;
typedef struct R1jSeqB { uint8_t b[0x674]; } R1jSeqB;   /* 0x0037D424, template 0x00380C48 */
typedef struct R1jSeqC { uint8_t b[0x184]; } R1jSeqC;   /* 0x0037DA98, template 0x00380AA0 */
typedef struct R1jSeqE { uint8_t b[0xD0]; } R1jSeqE;    /* 0x0037F480, template 0x003812C0 */
extern R1jSeqA r1j_seqA37C4FC, r1j_seqA37FB78;
extern R1jSeqB r1j_seqB37D424, r1j_seqB380C48;
extern R1jSeqC r1j_seqC37DA98, r1j_seqC380AA0;
extern R1jSeqE r1j_seqE37F480, r1j_seqE3812C0;
void sub_00026B50(int resume);                  /* HUD setup; regargs resume=EDI */
void sub_00026CF0(int a);                       /* regargs a=EBX */
void r1j_HudSeqSave(void);                      /* 0x0002B820 */

/* ------------------------------------------------------------ grading */
typedef struct R1jGradeThr {    /* per-chapter rank thresholds, best first */
    float    time[4];           /* +0x00 seconds */
    int16_t  combo[4];          /* +0x10 */
    int16_t  damage[4];         /* +0x18 */
    int16_t  exclaim[4];        /* +0x20 */
} R1jGradeThr;
void r1j_GradeRank(GradeBlock *g, const R1jGradeThr *t);   /* 0x00040AB0 regargs g=EAX t=ECX */

/* ------------------------------------------------------------ camera occluders */
typedef struct R1jOccObj {
    uint8_t  u00[0x34];
    uint8_t  flags34;           /* +0x34 bit 0: always see through */
} R1jOccObj;
typedef struct R1jOccItem {
    uint32_t   flags;           /* +0x00 bit 0 enabled */
    float      fade;            /* +0x04 distance, 0, or -1 */
    uint32_t   u08;
    R1jOccObj *obj;             /* +0x0C */
} R1jOccItem;
typedef struct R1jOccNode {
    struct R1jOccNode *next;    /* +0x00 */
    uint8_t     u04[8];
    R1jOccItem *data;           /* +0x0C the item, 0x10 bytes into the node */
} R1jOccNode;
typedef struct R1jOccList {
    int32_t     count;          /* +0x00 */
    R1jOccNode *first;          /* +0x04 */
    R1jOccNode *last;           /* +0x08 */
} R1jOccList;
typedef struct R1jStage {
    uint8_t  u000[0x20C];
    int32_t  mode;              /* +0x20C */
} R1jStage;
extern R1jOccList r1j_occList3DDC60;            /* 0x003DDC60 */
extern int32_t    r1j_camLock42CB04;            /* 0x0042CB04 */
extern R1jStage  *r1j_stage42C8E4;              /* 0x0042C8E4 */
extern int32_t    r1j_occRange;                 /* 0x002C454C (80) */
int  sub_0003AAF0(void *item, float *out);      /* occluder point, 0 when found */
void sub_0003DB40(void *list, void *cmp);       /* sort list */
int  sub_0003A950(void *a, void *b);            /* occluder compare */
void r1j_OccluderUpdate(void);                  /* 0x0003AF70 */

/* ------------------------------------------------------------ slot heaps */
typedef struct R1jBlk {         /* block header, 0x40 bytes before the data */
    uint32_t        flags;      /* +0x00 bit 0 in use */
    struct R1jHeap *heap;       /* +0x04 */
    struct R1jBlk  *next;       /* +0x08 */
    struct R1jBlk  *prev;       /* +0x0C */
    uint8_t         link[0x0C]; /* +0x10 list link in the heap's block list */
    struct R1jBlk  *self;       /* +0x1C */
    uint32_t        size;       /* +0x20 block size with header, 64-byte units */
    uint32_t        used;       /* +0x24 user size */
    uint8_t         u28[0x14];
    uint32_t        flags3C;    /* +0x3C bit 0 stack-style heap */
} R1jBlk;
typedef struct R1jHeap {
    uint32_t  u00;
    char     *top;              /* +0x04 stack-style top */
    R1jBlk   *tail;             /* +0x08 last block */
    uint8_t   list[0x0C];       /* +0x0C block list */
    uint8_t   u18[0x18];
    int32_t   sem;              /* +0x30 lock, -1 none */
} R1jHeap;
int   sub_001AA460(int h);                      /* lock release */
int   sub_001AA520(int h);                      /* lock try, -1 busy */
void  sub_00047060(R1jHeap *h);                 /* wait for the lock; regargs h=ESI */
void *sub_00047390(R1jHeap *h, uint32_t size, const void *file, int line);
void  sub_00047640(void *p);                    /* free */
void *r1j_HeapResize(void *p, uint32_t size);   /* 0x00047760 */

/* ------------------------------------------------------------ save data load */
typedef struct R1jSaveRec {     /* 0x800 bytes */
    int32_t  mode;              /* +0x000 */
    uint8_t  u004[0x7FC];
} R1jSaveRec;
typedef struct R1jIoBuf {       /* 0x8A0 bytes */
    uint8_t    u000[0x80];
    R1jSaveRec rec;             /* +0x080 */
    uint8_t    u880[0x20];
} R1jIoBuf;
extern int32_t     r1j_ioStep3E3954;            /* 0x003E3954 */
extern R1jIoBuf   *r1j_ioBuf3E397C;             /* 0x003E397C */
extern int32_t     r1j_readOk3E3910;            /* 0x003E3910 */
extern int32_t     r1j_mode3E3950;              /* 0x003E3950 */
extern R1jSaveRec *r1j_saveRec42C7A0;           /* 0x0042C7A0 */
extern uint32_t    r1j_flags413160;             /* 0x00413160 */
extern int32_t     r1j_fadeState428F20;         /* 0x00428F20 */
extern uint8_t     r1j_fade428F40[];            /* 0x00428F40 fade object */
void     sub_001A9740(void *buf);               /* start reading the save */
uint16_t sub_00072FA0(void *obj);               /* fade running */
void     sub_00072F30(void *o, int kind, float t, uint32_t color, int z);
int      sub_00056E10(void);                    /* read status */
void     sub_000408E0(int a);
void r1j_SaveLoadStep(void);                    /* 0x00057370 */

/* ------------------------------------------------------------ menu screen textures */
extern int32_t r1j_menuTexE3E0544[13];          /* 0x003E0544 */
extern int32_t r1j_menuTexD3E0580[3];           /* 0x003E0580 */
extern void   *r1j_menuBuf3E058C;               /* 0x003E058C */
extern int32_t r1j_menuTexA3E0590[2];           /* 0x003E0590 */
extern int32_t r1j_menuCount3E059C;             /* 0x003E059C */
extern int32_t r1j_menuTexH3E05A0[5];           /* 0x003E05A0 */
extern int32_t r1j_menuTexC3E05B4[2];           /* 0x003E05B4 */
extern int32_t r1j_menuKind;                    /* 0x003E05BC page kind 0..4 */
extern int32_t r1j_menuTexG3E05C0[2];           /* 0x003E05C0 */
extern int32_t r1j_menuTexF3E05C8[2];           /* 0x003E05C8 */
extern int32_t r1j_menuTexB3E05D0[3];           /* 0x003E05D0 */
int  sub_001B9FC0(int handle);                  /* texture release */
void sub_0004F5D0(int slot);                    /* run command slot */
int  sub_000529F0(void);                        /* video mode */
void sub_001A1B90(void);
void r1j_MenuTexRelease(void);                  /* 0x00049870 */

/* ------------------------------------------------------------ title menu flow */
typedef struct R1jMenuFlow {
    int32_t mode;               /* +0x00 */
    int32_t step;               /* +0x04 */
    int32_t a;                  /* +0x08 */
    int32_t b;                  /* +0x0C */
} R1jMenuFlow;
extern R1jMenuFlow r1j_menuFlow;                /* 0x003E0000 */
extern int32_t     r1j_loading3E0540;           /* 0x003E0540 */
extern int32_t     r1j_chapter413164;           /* 0x00413164 */
extern uint32_t   *r1j_padMasks2C4AE8;          /* 0x002C4AE8 */
int      sub_00079460(void);                    /* movie playing */
uint32_t sub_0004ECD0(int pad);
uint32_t sub_0004ECE0(int pad);
uint32_t sub_0004ECF0(int pad);
uint32_t sub_0004ED00(int pad);
uint32_t sub_0004ED20(int pad);
uint32_t sub_0004ED40(int pad);
int  sub_00048A00(int a, int b);                /* start stream */
void sub_00047BF0(int a);                       /* stop stream */
int  sub_0004BE80(void);
int  sub_0004BFA0(void);
void sub_000325A0(int on);
void r1j_TitleMenuStep(void);                   /* 0x0004E1C0 */

/* ------------------------------------------------------------ graphics reset */
extern uint8_t  r1j_pkt3DE5B0[];                /* 0x003DE5B0 */
extern uint32_t r1j_test42CAE8[2];              /* 0x0042CAE8 TEST register value */
extern uint32_t r1j_test3DE680;                 /* 0x003DE680 */
extern uint32_t r1j_test3DE770;                 /* 0x003DE770 */
void sub_00014940(int a, int b, int c, int d);  /* clear screen */
void sub_0003DD30(void);                        /* fixed register packet */
void r1j_GfxReset(int interlaced);              /* 0x0003DE20 */

/* ------------------------------------------------------------ owner effects */
typedef struct R1jFxSrc {
    uint8_t  u00[0x0C];
    void    *cur;               /* +0x0C */
    uint8_t  buf[4];            /* +0x10 */
} R1jFxSrc;
typedef struct R1jFxEnt {
    struct R1jFxEnt *next;      /* +0x00 */
    uint8_t   u04[0x0C];
    int32_t   key;              /* +0x10 */
    uint8_t   u14[0x0C];
    R1jFxSrc  src;              /* +0x20 */
} R1jFxEnt;
typedef struct R1jFxOwner {
    uint32_t  u00;
    R1jFxEnt *first;            /* +0x04 */
} R1jFxOwner;
struct R1jFx;
typedef struct R1jFxNode {
    struct R1jFxNode *next;     /* +0x00 */
    uint8_t   u04[8];
    struct R1jFx *data;         /* +0x0C */
} R1jFxNode;
typedef struct R1jFx {          /* 0x2C bytes, 0x10 into its pool record */
    uint32_t  flags;            /* +0x00 bit 0 enabled */
    R1jFxSrc *src;              /* +0x04 */
    uint8_t   u08[0x0C];
    R1jFxNode link;             /* +0x14 active list link */
    float     scale;            /* +0x24 */
    int32_t   key;              /* +0x28 */
} R1jFx;
typedef struct R1jFxList {
    int32_t    count;           /* +0x00 */
    R1jFxNode *first;           /* +0x04 */
} R1jFxList;
typedef struct R1jFxChan {      /* 0x2C bytes */
    int32_t  handle;            /* +0x00 -1 free */
    int32_t  d04;               /* +0x04 */
    uint8_t  u08[0x0C];
    int32_t  key;               /* +0x14 */
    uint8_t  u18[0x14];
} R1jFxChan;
extern R1jFxList r1j_fxActive3E5AAC;            /* 0x003E5AAC */
extern uint8_t   r1j_fxPool3E4B70[];            /* 0x003E4B70 */
extern R1jFxChan r1j_fxChan3E5AD4[32];          /* 0x003E5AD4 */
void *sub_00036AD0(void *pool, int size);       /* take a pool record */
void  sub_0003D860(void *node);                 /* clear link */
void  sub_0005A400(void *fx);
void  sub_0005A6D0(void *fx, void *src);
void  sub_0005BE30(void *a);
void  sub_0005BC50(void *p);
void  sub_00048250(int h);
int   r1j_OwnerFxSet(R1jFxOwner *o, int key, int on);   /* 0x0005C580 */

/* ------------------------------------------------------------ title model */
typedef struct R1jTitleObj {
    uint8_t  u00[0x20];
    float   *mat;               /* +0x20 model matrix */
    uint8_t  u24[0x3C];
    float    pos[4];            /* +0x60 */
    float    scale[3];          /* +0x70 */
} R1jTitleObj;
typedef struct R1jSprPos {
    float x, y;                 /* +0x00 */
} R1jSprPos;
extern R1jTitleObj *r1j_titleObj3E00E8;         /* 0x003E00E8 */
extern int32_t      r1j_frame42C918;            /* 0x0042C918 frame counter */
extern R1jSprPos    r1j_logoA3E0494;            /* 0x003E0494 */
extern R1jSprPos    r1j_logoPos3E0030;          /* 0x003E0030 */
void  sub_001ADA40(void *a, const void *p);     /* matrix copy */
void  sub_001AD7C0(void *dst, const void *a, const void *b);   /* matrix multiply */
void  sub_0007A9D0(void *stage);
void  sub_0007A9F0(void *stage, void *pkt, int frame);
void  sub_00079DA0(void *stage);
void  sub_0007B060(void *stage);
void *sub_0007D1B0(void *stage, int arg);
void  sub_001B96D0(void);                       /* tick texture timers */
void  sub_000150B0(void *spr, int frame);
void *sub_00017C90(void *cmd, void *spr);
void  r1j_TitleModelDraw(int arg);              /* 0x0004AC90 */

/* ------------------------------------------------------------ HUD sequence dispatcher */
extern uint32_t r1j_seqFlagsC37DAA0;            /* 0x0037DAA0 */
extern int32_t  r1j_seqStateC37DAA4;            /* 0x0037DAA4 */
extern uint32_t r1j_seqFlags37DCF8;             /* 0x0037DCF8 */
extern int32_t  r1j_seqState37DCFC;             /* 0x0037DCFC */
extern uint32_t r1j_seqFlags37E090;             /* 0x0037E090 */
extern int32_t  r1j_seqState37E094;             /* 0x0037E094 */
extern uint32_t r1j_seqFlagsE37F480;            /* 0x0037F480 */
extern int32_t  r1j_seqStateE37F484;            /* 0x0037F484 */
extern uint32_t r1j_seqFlags37FB3C;             /* 0x0037FB3C */
extern int32_t  r1j_seqState37FB40;             /* 0x0037FB40 */
void sub_0002C150(void);
void sub_0002C1B0(void);
void sub_0002C230(void);
void sub_0002C2A0(void);
void sub_0002C300(void);
void sub_0002C370(void);
void sub_00029680(void);
void sub_00029770(void);
void sub_00029850(void);
void sub_000298C0(void);
void sub_00029DC0(void);
void sub_00029EF0(void);
void sub_0002A000(void);
void sub_0002A570(void);
void sub_0002A6C0(void);
void sub_0002A7A0(void);
void sub_0002A830(void);
void sub_0002B140(void);
void sub_0002B230(void);
void sub_0002B310(void);
void sub_0002B5A0(void);
void sub_0002B690(void);
void sub_0002B770(void);
void r1j_HudSeqStep(void);                      /* 0x0002C5E0 */

/*@NEXT@*/
#endif
